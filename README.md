checkpass
=========
Checks a username/password combination on OpenBSD.  The username and password
are read from stdin.  checkpass is meant to be called from other programs.

Input
-----
Input should be the username, a null byte, the password, and another null byte,
something like
```bash
printf "myuser\000passw0rd\000" | ./checkpass
```

Output
------
Either `Ok.` or `Fail.` will be printed to the standard output, and the return
value will be set to indicate success (0) or failure (non-zero).

Building
--------
The included `build.sh` script may be used to build checkpass.  There are no
external dependencies (except OpenBSD).  Of note, though it uses `pledge(2)`
and `explicit_bzero(3)`, so older installs of OpenBSD may require a bit of 
tweaking of the source code.

Installation
------------
As checkpass needs to be root to work, it is advisable to do something like the
following to install it
```bash
cp ./checkpass /usr/local/sbin
chown root:trusted /usr/local/sbin/checkpass
chmod 4550 /usr/local/sbin/checkpass
```
