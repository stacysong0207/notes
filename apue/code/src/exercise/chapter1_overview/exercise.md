# 习题

## 1.1. 在系统上验证，除根目录外，目录.和..是不同的。

```shell
[stanley@stanleyAPUE code]$ pwd
/home/stanley/Git/notes/apue/code
[stanley@stanleyAPUE code]$ ls -ahl . ..
.:
total 36K
drwxrwxr-x.  9 stanley stanley 4.0K Oct 31 16:13 .
drwxrwxr-x.  5 stanley stanley 4.0K Nov  1 18:42 ..
drwxrwxr-x.  2 stanley stanley 4.0K Oct 27 09:43 bin
drwxrwxr-x.  2 stanley stanley 4.0K Oct 31 15:58 include
drwxrwxr-x.  2 stanley stanley 4.0K Oct 31 15:58 lib
drwxrwxr-x.  2 stanley stanley 4.0K Oct 31 17:03 out
-rw-rw-r--.  1 stanley stanley    0 Oct 27 09:43 README.md
drwxrwxr-x.  2 stanley stanley 4.0K Oct 27 09:43 res
drwxrwxr-x.  3 stanley stanley 4.0K Oct 27 09:43 shell
drwxrwxr-x. 24 stanley stanley 4.0K Nov  2 16:39 src

..:
total 24K
drwxrwxr-x.  5 stanley stanley 4.0K Nov  1 18:42 .
drwxr-xr-x. 11 stanley stanley 4.0K Nov  2 16:31 ..
drwxrwxr-x.  9 stanley stanley 4.0K Oct 31 16:13 code
drwxrwxr-x.  2 stanley stanley 4.0K Nov  1 16:55 notes
-rw-rw-r--.  1 stanley stanley  308 Nov  1 18:42 README.md
drwxrwxr-x.  2 stanley stanley 4.0K Oct 27 09:43 res
```

```shell
[stanley@stanleyAPUE /]$ pwd
/
[stanley@stanleyAPUE /]$ clear
[stanley@stanleyAPUE /]$ pwd
/
[stanley@stanleyAPUE /]$ ls -ahl . ..
.:
total 110K
dr-xr-xr-x.  25 root root 4.0K Oct 30 09:50 .
dr-xr-xr-x.  25 root root 4.0K Oct 30 09:50 ..
-rw-r--r--.   1 root root    0 Oct 30 09:50 .autofsck
dr-xr-xr-x.   2 root root 4.0K Sep 26 03:11 bin
dr-xr-xr-x.   5 root root 1.0K Sep 12 15:13 boot
drwx------.   3 root root 4.0K Aug 23 03:33 .dbus
drwxr-xr-x.  20 root root 3.8K Oct 30 09:51 dev
drwxr-xr-x. 122 root root  12K Nov  2 03:28 etc
drwxr-xr-x.   3 root root 4.0K Aug 23 03:48 home
dr-xr-xr-x.  11 root root 4.0K Sep 12 15:32 lib
dr-xr-xr-x.   9 root root  12K Sep 26 03:11 lib64
drwx------.   2 root root  16K Aug 23 03:20 lost+found
drwxr-xr-x.   2 root root 4.0K Oct 25 13:17 media
drwxr-xr-x.   2 root root    0 Oct 30 09:51 misc
drwxr-xr-x.   3 root root 4.0K Oct 25 13:14 mnt
drwxr-xr-x.   2 root root    0 Oct 30 09:51 net
drwxr-xr-x.   3 root root 4.0K Aug 23 03:29 opt
dr-xr-xr-x. 204 root root    0 Oct 30 09:50 proc
dr-xr-x---.  10 root root 4.0K Oct 25 13:07 root
dr-xr-xr-x.   2 root root  12K Oct 25 13:13 sbin
drwxr-xr-x.   7 root root    0 Oct 30 09:50 selinux
drwxr-xr-x.   2 root root 4.0K Sep 23  2011 srv
drwxr-xr-x   13 root root    0 Oct 30 09:50 sys
drwxrwxrwt.  22 root root 4.0K Nov  2 17:17 tmp
drwxr-xr-x.  13 root root 4.0K Aug 23 03:21 usr
drwxr-xr-x.  22 root root 4.0K Aug 23 03:28 var

..:
total 110K
dr-xr-xr-x.  25 root root 4.0K Oct 30 09:50 .
dr-xr-xr-x.  25 root root 4.0K Oct 30 09:50 ..
-rw-r--r--.   1 root root    0 Oct 30 09:50 .autofsck
dr-xr-xr-x.   2 root root 4.0K Sep 26 03:11 bin
dr-xr-xr-x.   5 root root 1.0K Sep 12 15:13 boot
drwx------.   3 root root 4.0K Aug 23 03:33 .dbus
drwxr-xr-x.  20 root root 3.8K Oct 30 09:51 dev
drwxr-xr-x. 122 root root  12K Nov  2 03:28 etc
drwxr-xr-x.   3 root root 4.0K Aug 23 03:48 home
dr-xr-xr-x.  11 root root 4.0K Sep 12 15:32 lib
dr-xr-xr-x.   9 root root  12K Sep 26 03:11 lib64
drwx------.   2 root root  16K Aug 23 03:20 lost+found
drwxr-xr-x.   2 root root 4.0K Oct 25 13:17 media
drwxr-xr-x.   2 root root    0 Oct 30 09:51 misc
drwxr-xr-x.   3 root root 4.0K Oct 25 13:14 mnt
drwxr-xr-x.   2 root root    0 Oct 30 09:51 net
drwxr-xr-x.   3 root root 4.0K Aug 23 03:29 opt
dr-xr-xr-x. 204 root root    0 Oct 30 09:50 proc
dr-xr-x---.  10 root root 4.0K Oct 25 13:07 root
dr-xr-xr-x.   2 root root  12K Oct 25 13:13 sbin
drwxr-xr-x.   7 root root    0 Oct 30 09:50 selinux
drwxr-xr-x.   2 root root 4.0K Sep 23  2011 srv
drwxr-xr-x   13 root root    0 Oct 30 09:50 sys
drwxrwxrwt.  22 root root 4.0K Nov  2 17:17 tmp
drwxr-xr-x.  13 root root 4.0K Aug 23 03:21 usr
drwxr-xr-x.  22 root root 4.0K Aug 23 03:28 var
```


