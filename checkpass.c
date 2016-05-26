/*
 * checkpass.c
 * Program to check a username/password pair on OpenBSD
 * By J. Stuart McMurray
 * Created 20160525
 * Last Modified 20160525
 */
#include <sys/types.h>

#include <bsd_auth.h>
#include <err.h>
#include <login_cap.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define BUFSIZE 4096

ssize_t fill_buf(void*, ssize_t);

int main(int argc, char **argv) {
        char buf[BUFSIZE];
        char *pass;
        int i, ret;

        if (-1 == pledge("exec getpw proc rpath stdio", NULL))
                err(5, "pledge");

        explicit_bzero(buf, sizeof(buf));

        /* Read the username and password from stdin */
        if (4 > fill_buf(buf, sizeof(buf)))
                errx(2, "not enough input data");

        /* Make sure buffer is null-terminated */
        if ('\0' != buf[sizeof(buf)-1])
                errx(3, "not enough buffer space");

        /* Find password */
        pass = NULL;
        for (i = 0; i < sizeof(buf)-1; ++i) {
                if ('\0' == buf[i]) {
                        pass = buf+i+1;
                        break;
                }
        }
        if (NULL == pass)
                errx(4, "password not found");

        /* Check password */
        ret = auth_userokay(buf, NULL, NULL, pass);
        explicit_bzero(buf, sizeof(buf));
        if (0 != ret) {
                printf("Ok.\n");
                return 0;
        }
        printf("Fail.\n");
        return 4;
}

/* fill_buf fills the buffer starting at buf with up to n bytes, or until stdin
 * reaches eof.  The buffer isn't guaranteed to be null-terminated.  The number
 * of bytes read is returned. */
ssize_t
fill_buf(void *buf, ssize_t n) {
        ssize_t ret;
        ssize_t tot;

        tot = 0;

        /* Read bytes while we still have buffer space */
        while (tot < n) {
                ret = read(STDIN_FILENO, (char*)buf+tot, n-tot);

                if (-1 == ret)
                        err(1, "read");
                else if (0 == ret)
                        return tot;

                tot += ret;
        }

        return tot;
}
