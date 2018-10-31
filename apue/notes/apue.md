**目录**
---

<!-- TOC -->

- [APUE学习笔记](#apue学习笔记)
    - [1. 限制](#1-限制)
        - [1.1. sysconf、pathconf和fpathconf](#11-sysconfpathconf和fpathconf)
    - [2. 选项](#2-选项)
        - [2.1. POSIX.1 3种处理选项的方法(可移植程序依赖这些可选的支持功能)](#21-posix1-3种处理选项的方法可移植程序依赖这些可选的支持功能)
        - [2.2. 选项平台支持情况](#22-选项平台支持情况)
    - [3. FILE I/O](#3-file-io)
        - [3.1. 常用函数](#31-常用函数)
        - [3.2. 文件描述符](#32-文件描述符)
        - [3.3. open和openat](#33-open和openat)
        - [3.4. creat](#34-creat)
        - [3.5. close](#35-close)
        - [3.6. lseek](#36-lseek)
        - [3.7. read](#37-read)
        - [3.8. write](#38-write)
        - [3.9. I/O的效率](#39-io的效率)
        - [3.10 文件共享](#310-文件共享)
        - [3.11. 原子操作](#311-原子操作)
        - [3.12. dup和dup2](#312-dup和dup2)
        - [3.13. sync、fsync和fdatasync](#313-syncfsync和fdatasync)
        - [3.14. fcntl](#314-fcntl)
        - [3.15. ioctl](#315-ioctl)
        - [3.16. /dev/fd](#316-devfd)
    - [4. 文件和目录](#4-文件和目录)
        - [4.1. stat、fstat、fstatat和lstat](#41-statfstatfstatat和lstat)
        - [4.2. 文件类型](#42-文件类型)
        - [4.3. 设置用户ID和设置组ID](#43-设置用户id和设置组id)
        - [4.4. 文件访问权限](#44-文件访问权限)
        - [4.5. 新文件和目录的所有权](#45-新文件和目录的所有权)
        - [4.6. 函数access和faccessat](#46-函数access和faccessat)
        - [4.7. umask](#47-umask)
        - [4.8. chmod、fchmod和fchmodat](#48-chmodfchmod和fchmodat)
        - [4.9. 粘着位](#49-粘着位)
        - [4.10. chown、fchown、fchownat和lchown](#410-chownfchownfchownat和lchown)
        - [4.11 文件长度](#411-文件长度)
        - [4.12. 文件截断](#412-文件截断)
        - [4.13. 文件系统](#413-文件系统)
        - [4.14. link、linkat、unlink、unlinkat和remove](#414-linklinkatunlinkunlinkat和remove)
        - [4.15. rename和renameat](#415-rename和renameat)
        - [4.16. 符号链接](#416-符号链接)
        - [4.17 创建和读取符号链接](#417-创建和读取符号链接)
        - [4.18. 文件的时间](#418-文件的时间)
        - [4.19. futimens、utimensat和utimes](#419-futimensutimensat和utimes)
        - [4.20 mkdir、mkdirat和rmdir](#420-mkdirmkdirat和rmdir)
        - [4.21. 读目录](#421-读目录)
        - [4.22. chdir、fchdir和getcwd](#422-chdirfchdir和getcwd)
        - [4.23. 设备特殊文件](#423-设备特殊文件)
        - [4.24. 文件访问权限位小结](#424-文件访问权限位小结)
    - [5. 标准I/O库](#5-标准io库)
        - [5.1. 流和FILE对象](#51-流和file对象)
        - [5.2. 标准输入、标准输出和标准错误](#52-标准输入标准输出和标准错误)
        - [5.3. 缓冲](#53-缓冲)
        - [5.4. 打开流](#54-打开流)
        - [5.5 读和写流](#55-读和写流)
            - [5.5.1. 输入函数](#551-输入函数)
            - [5.5.2. 输出函数](#552-输出函数)
        - [5.6. 每次一行I/O](#56-每次一行io)
        - [5.7. 标准I/O的效率](#57-标准io的效率)
        - [5.8. 二进制I/O](#58-二进制io)
        - [5.9. 定位流](#59-定位流)
        - [5.10. 格式化I/O](#510-格式化io)
            - [5.10.1 格式化输出](#5101-格式化输出)
            - [5.10.2 格式化输入](#5102-格式化输入)
        - [5.11 实现细节](#511-实现细节)
        - [5.12. 临时文件](#512-临时文件)
    - [6. 系统数据文件和信息](#6-系统数据文件和信息)
    - [7. 进程环境](#7-进程环境)
    - [8. 进程控制](#8-进程控制)
    - [9. 进程关系](#9-进程关系)
    - [10. 信号](#10-信号)
    - [11. 线程](#11-线程)
    - [12. 线程控制](#12-线程控制)
    - [13. 守护进程](#13-守护进程)
    - [14. 高级I/O](#14-高级io)
    - [15. 进程间通信](#15-进程间通信)
    - [16. 网络IPC：套接字](#16-网络ipc套接字)
    - [17. 高级进程间通信](#17-高级进程间通信)
    - [18. 终端I/O](#18-终端io)
    - [19. 伪终端](#19-伪终端)
    - [20. 数据库函数库](#20-数据库函数库)
    - [21. 与网络打印机通信](#21-与网络打印机通信)

<!-- /TOC -->

# APUE学习笔记

## 1. 限制

### 1.1. sysconf、pathconf和fpathconf

章节2.5.4
```c
#include <unistd.h>

long sysconf(int name);
long pathconf(const char* pathname, int name);	//路径名
long fpathconf(int fd, int name);	//文件描述符

所有函数返回值，若成功，返回相应值；若出错，返回-1
```

## 2. 选项

### 2.1. POSIX.1 3种处理选项的方法(可移植程序依赖这些可选的支持功能)

1. 编译时选项定义在<unistd.h>
2. 与文件或目录无关的运行时选项用sysconf函数来判断
3. 与文件或目录有关的运行时选项通过调用pathconf或fpathconf函数来判断

### 2.2. 选项平台支持情况

1. 如果符号常量没有定义或者定义值为-1，那么该平台在编译时并不支持相应选项。但是有一种可能，即在已支持该选项的新系统上运行老的应用时，即使该选项在应用编译时未被支持，但如今新系统运行时检查会显示该选项已被支持。
2. 如果符号常量的定义值大于0，那么该平台支持相应选项。
3. 如果符号常量的定义值为0，那必须调用sysconf、pathconf或fpathconf来判断相应选项是否收到支持。

## 3. FILE I/O

### 3.1. 常用函数

open、read、write、lseed以及close

### 3.2. 文件描述符

文件描述符变化范围 **0 ~ OPEN_MAX - 1**
0 标准输入	**STDIN_FILENO**
1 标准输出	**STDOUT_FILENO**
2 标准错误	**STDERR_FILENO**

### 3.3. open和openat

<a id="open"></a>
```c
#include <fcntl.h>

/**
 * @param	path	要打开或创建文件的名字
 * @param	oflag	打开文件时的参数选项
 * @param	mode_t	文件访问权限
 * @return	fd	文件描述符
 * @return	-1	出错
 */
int open(const char *path, int oflag, ... /* mode_t mode */);

/**
 * @param	fd	要打开的文件描述符
 * @param	path	要打开或创建文件的名字
 * @param	oflag	打开文件时的参数选项
 * @param	mode_t	文件访问权限
 * @return	fd	文件描述符
 * @return	-1	出错
 */
int openat(int fd, const char *path, int oflag, ... /* mode_t mode */);
```

<a id="oflag">**oflag参数**</a>
```c
O_RDONLY		只读打开
O_WRONLY		只写打开
O_RDWR			读写打开
	-- 大多数实现将O_RDONLY定义为0，O_WRONLY定义为1，O_RDWR定义为2
O_EXEC			只执行打开
O_SEARCH		只搜索打开(应用于目录)
	-- O_SEARCH用来验证在目录打开时它的搜索权限

*以上5个常量必须制定一个且只能指定一个，以下是可选的。

O_APPEND		每次写是都追加到文件尾。
O_CLOEXEC		把FD_CLOEXEC常量设置为文件描述符标志。
O_CREAT			若此文件不存在则创建它。在使用此选项时，open函数需同时说明第三个参数mode
			(openat函数需要说明第4个参数mode)，用mode指定该文件的访问权限。
O_DIRECTORY		如果path引用的不是目录，则出错。
O_EXCL			如果同时制定了O_CREAT，而文件已经存在，则出错。用此可以测试一个文件是否
			存在，如果不存在，则创建此文件，这使测试和创建两者成为一个原子操作。
O_NOCTTY		如果path引用的是终端设备，则不将该设备分配作为此进程的控制终端。
O_NOFOLLOW		如果path引用的是一个符号连接，则出错。
O_NONBLOCK		如果path引用的是一个FIFO，一个块特殊文件或一个字符特殊文件，则此选项为
			文件的本次打开操作和后续的I/O操作设置非阻塞方式
O_SYNC			使每次write等待物理I/O操作完成，包括由该write操作引起的文件属性更新所需的I/O。
O_TRUNC			如果此文件存在，而且为只写或读写成功打开，则将其长度截断为0.
O_TTY_INIT		如果打开一个还未打开的终端设备，设置非标准termios参数值，使其符合Single
			UNIX Specification。
O_DSYNC			使每次write要等待物理I/O操作完成，但是如果该写操作并不影响读取刚写入的
			数据，则不需要等待文件属性被更新。
O_RSYNC			使每一个以文件描述符作为参数进行的read操作等待，直至所有对文件同一部分
			挂起的写操作都完成。
```
由open和openat函数返回的文件描述符一定是最小的未用的描述符数值。

fd参数把open和openat函数区分开，共有3种可能性：
(1) path参数指定的是绝对路径名，在这种情况下，fd参数被忽略，openat函数就相当于open函数
(2) path参数指定的是相对路径名，fd参数指出了相对路径名在文件系统中的开始地址。fd参数是通过打开相对路径名所在的目录来获取。
(3) path参数指定了相对路径名，fd参数具有特殊值AT_FDCWD。在这种情况下吗，路径名在当前工作目录中获取，openat函数在操作上与open函数类似。

### 3.4. creat

<a id="creat"></a>
```c
#include <fcntl.h>

/**
 * @param	path	要创建文件的名字
 * @param	mode_t	文件访问权限
 * @return	fd	文件描述符
 * @return	-1	出错 
 */
int creat(const char *path, mode_t mode);
```
注意，此函数等效于:
```c
open(path, O_WRONLY | O_CREAT | O_TRUNC, mode);
```
creat的一个不足之处是它以只写方式打开所创建的文件，在提供open的新版本之前，如果要创建一个临时文件，并要先写该文件，然后又读该文件，则必须先调用creat，close，然后再调用open，现在则可用下列方式调用open实现：
```c
open(path, O_RDWR | O_CREAT | O_TRUNC, mode);
```

### 3.5. close

```c
#include <unistd.h>

/**
 * @param	fd	要关闭的文件描述符
 * @return	0	成功
 * @return	-1	失败
 */
int close(int fd);
```
关闭一个文件时还会释放该进程加在该文件上的所有记录锁。
当一个进程终止时，内核自动关闭它所有的打开文件。

### 3.6. lseek

<a id="lseek"></a>
```c
#include <unistd.h>

/**
 * @param	fd	要操作的文件描述符
 * @param	offset	偏移量
 * @param	whence	设置
 * @return	新的文件偏移量
 * @return	-1
 */
off_t lseek(int fd, off_t offset, int whence);
```
对参数offset的解释与参数whence的值有关.
- 若whence是SEEK_SET，则该文件的偏移量设置为距文件开始处offset个字节。
- 若whence是SEEK_CUR，则该文件的偏移量设置为其当前值加offset，offset可为正或负。
- 若whence是SEEK_END，则该文件的偏移量设置为文件长度加offset，oggset可为正或负。
```c
off_t currpos;
currpos = lseek(fd, 0, SEEK_CUR);
```
如果文件描述符指向的是一个管道、FIFO或网络套接字，则lseek返回-1，并将errno设置为ESPIPE。

文件偏移量可以大于文件的当前长度，在这种情况下，对该文件的下次写将加长该文件，并在文件中构成一个空洞，这一点是允许的。位于文件中但没有写过的字节都被读为0.
文件中的空洞并不要求在磁盘上占用存储区。具体处理方式与文件系统的实现有关，当定位到超出文件尾端之后写时，对于新写的数据需要分配磁盘块，但是对于原文件尾部和新开始写位置之间的部分则不需要分配磁盘块。
```shell
od -c file.hole
```
使用od命令观察该文件的实际内容。命令行中的-c标志表示以字符方式打印文件内容。

因为lseek使用的偏移量是off_t类型表示的，所以允许具体实现根据各自特定的平台自行选择大小合适的数据类型。现今大多数平台提供两组接口处理文件偏移量，一组使用32位文件偏移量，另一组使用64位文件偏移量。

| 选项名称                | 说明                                      | name参数             |
| ---------------------- | ----------------------------------------- | ------------------- |
| _POSIX_V7_ILP32_OFF32  | int、long、指针和off_t类型是32位            | _SC_V7_ILP32_OFF32  |
| _POSIX_V7_ILP32_OFFBIG | int、long、指针类型是32位，off_t类型至少64位 | _SC_V7_ILP32_OFFBIG |
| _POSIX_V7_LP64_OFF64   | int类型32位，long、指针和off_t类型是64位     | _SC_V7_LP64_OFF64   |
| _POSIX_V7_LP64_OFFBIG  | int类型32位，long、指针和off_t类型至少是64位 | _SC_V7_LP64_OFFBIG  |

### 3.7. read

<a id="read"></a>
```c
#include <unistd.h>

/**
 * @param	fd	要读取的文件描述符
 * @param	buf	读取数据存放的缓冲区
 * @param	nbytes	读取字节数
 * @return	读到的字节数，若已读到文件尾，返回0
 * @return	-1	出错
 */
ssize_t read(int fd, void *buf, size_t nbytes);
```
read函数原型
```c
int read(int fd, char *buf, unsigned nbytes);
```
- 为了与ISO C一致，第2个参数由char *改为void *。在ISO C中，类型void *用于表示通用指针。
- 其次，返回值必须是一个带符号的整型(ssize_t)，以保证能够返回正整数字节数、0或-1。
- 最后，第3个参数在历史上是一个无符号整型，这允许一个16位的实现一次读或写的数据。新的基本系统数据类型ssize_t以提供带符号的返回值。

### 3.8. write

<a id="write"></a>
```c
#include <unistd.h>

/**
 * @param	fd	要写入的文件描述符
 * @param	buf	写入数据存放的缓冲区
 * @param	nbytes	写入字节数
 * @return	返回已写的字节数
 * @return	-1	出错
 */
ssize_t write(int fd, const void *buf, size_t nbytes);
```
其返回值通常与参数nbytes的值相同，否则表示出错。

### 3.9. I/O的效率

### 3.10 文件共享

内核使用3种数据结构表示打开文件，它们之间的关系决定了在文件共享方面一个进程对另一个进程可能产生的影响。
(1) 每个进程在进程中都有一个记录项，记录项中包含一张打开文件描述符表，可将其视为一个矢量，每个描述符占用一项。与每个文件描述符相关联的是：
	a. 文件描述符标志(close_on_exec)。
	b. 指向一个文件表项的指针。
(2) 内核为所有打开文件维持一张文件表。每个文件表包含：
	a. 文件状态标志(读、写、添写、同步和非阻塞等)。
	b. 当前文件偏移量。
	c. 指向该文件v节点表项的指针。
(3) 每个打开文件(或设备)都有一个v节点(v-node)结构。v节点包含了文件类型和对此文件进行各种操作函数的指针。对于大多数文件，v节点还包含了该文件的i节点(i-node，索引节点)。这些信息是在打开文件时从磁盘上读入内存的，所有，文件的所有相关信息都是随时可用的。例如，i节点包含了文件的所有者、文件长度、指向文件实际数据块在磁盘上所在位置的指针等。

Linux没有使用v节点，而是使用了通用i节点结构。虽然两种实现有所不同，但在概念上，v节点和i节点是一样的。两者都指向文件系统特有的i节点结构。
Linux没有将相关的数据结构分为i节点和v节点，而是采用了一个与文件系统相关的i节点和一个与文件系统无关的i节点。

打开文件的内核数据结构:
![内核数据结构][1]

两个独立进程各自打开同一个文件
![同一文件结构图][2]

每个进程都有自己的文件表项，是因为这可以使每个进程都有它自己的对该文件的当前偏移量。

**注意**，文件描述符标志和文件状态标志在作用范围的区别，前者只用于一个进程的一个描述符，而后者则应用与指向该给定文件表项的任何进程中的所有描述符。

### 3.11. 原子操作

1. 追加到一个文件
考虑一个进程，它要将数据追加到一个文件尾端。早期的UNIX系统版本并不支持open的O_APPEND选项，所以程序被编写成下列形式：
```c
if(lseek(fd, OL, 2) < 0) {		/* position to EOF */
	err_sys("lseek error");
}
if(100 != write(fd, buf, 100)) {	/* and write */
	err_sys("write error");
}
```
2. 函数pread和pwirte
```c
#include <unistd.h>

/**
 * @param	fd	要读取的文件描述符
 * @param	buf	读取数据存放的缓冲区
 * @param	nbytes	读取字节数
 * @param	offset	读文件前文件偏移量
 * @return	读到的字节数，若已读到文件尾，返回0
 * @return	-1	出错
 */
ssize_t pread(int fd, void *buf, size_t nbytes, off_t offset);

/**
 * @param	fd	要写入的文件描述符
 * @param	buf	写入数据存放的缓冲区
 * @param	nbytes	写入字节数
 * @param	offset	写文件前文件偏移量
 * @return	返回已写的字节数
 * @return	-1	出错
 */
ssize_t pwrite(int fd, const void *buf, size_t nbytes, off_t offset);
```
调用pread相当于调用lseek后调用read
- 调用pread时，无法终端其定位和读操作。
- 不更新当前文件偏移量

调用pwrite相当于调用lseek后调用write

3. 创建一个文件
```c
if((fd = open(pathname, O_WRONLY)) < 0) {
	if(ENOENT == errno) {
		if((fd = creat(path, mode)) < 0) {
			err_sys("creat error");
		}
	}
}
```

一般而言，**原子操作**指的是由多步组成的一个操作。

### 3.12. dup和dup2

下面两个函数都可用来复制一个现有的文件描述符
```c
#include <unistd.h>

/**
 * @param	fd	要复制的文件描述符
 * @return	新的文件描述符
 * @return	-1	出错
 */
int dup(int fd);

/**
 * @param	fd	要复制的文件描述符
 * @param	fd2	新的文件描述符
 * @return	新的文件描述符
 * @return	-1	出错
 */
int dup2(int fd, int fd2);
```
dup返回的新文件描述符一定是当前可用文件描述符中的最小数值。
dup2可以用fd2指定新的描述符的值。如果fd2已经打开，则先将其关闭。若fd等于fd2，则dup2返回fd2，而不关闭它。否则，fd2的FD_CLOEXEC文件描述符标志就被清楚，这样fd2在进程调用exec时是打开状态。
```c
dup(fd);

//等价于：
fcntl(fd, F_DUPFD, 0);
```
```c
dup2(fd, fd2);

//等价于：
fcntl(fd, F_DUPFD, fd2);
```
在后一种情况中，dup2并不完全等同于close加上fcntl。它们之间的区别具体如下：
- dup2是一个原子操作，而close和fcntl包括两个函数调用。有可能在close和fcntl之间调用了信号捕捉函数，它可能修改文件描述符。如果不同的线程改变了文件描述符的话也会出现相同的问题。
- dup2和fcntl有一些不同的errno。

### 3.13. sync、fsync和fdatasync

当内核需要重用缓冲区来存放其他磁盘块数据时，它会把所有延迟写数据块写入磁盘。为了保证磁盘上实际文件系统与缓冲区中内容的一致性，UNIX系统提供了sync、fsync和fdatasync三个函数。
```c
#include <unistd.h>

/**
 * @param	fd	同步文件描述符
 * @return	0	成功
 * @return	-1	出错
 */ 
int fsync(int fd);

/**
 * @param	fd	同步文件描述符
 * @return	0	成功
 * @return	-1	出错
 */ 
int fdatasync(int fd);

//sync只是将所有修改过的块缓冲区排入队列，然后就返回，他并不等待实际写磁盘操作结束。
void sync(void);
```
通常，成为update的系统守护进程周期性调用(一般每隔30秒)sync函数，这就保证了定期冲洗(flush)内核块缓冲区。
fsync函数只对由文件描述符fd指定的一个文件起作用，并且等待写磁盘操作结束才返回。fsync可用于数据库这样的应用程序，这种应用程序需要确保修改过的块立即写到磁盘上。
fdatasync函数类似于fsync，但它只影响文件的数据部分，而除数据外，fsync还会永不更新文件的属性。

### 3.14. fcntl

fcntl可以改变已经打开文件的属性。
```c
#include <fcntl.c>

/**
 * @param	fd	要修改文件的文件描述符
 * @param	cmd	命令
 * @param	arg	参数
 * @return	依赖cmd
 * @return	-1	出错
 */
int fcntl(int fd, int cmd, ... /* int arg */);
```
fcntl函数有以下5种功能：
1. 复制一个已有的文件描述符(cmd=F_DUPFD或F_DUPFD_CLOEXEC)。
2. 获取/设置文件描述符标志(cmd=F_GETFD或F_SETFD)。
3. 获取/设置文件状态标志(cmd=F_GETFL或F_SETFL)。
4. 获取/设置异步I/O所有权(cmd=F_GETOWN或F_SETOWN)。
5. 获取/设置记录锁(cmd=F_GETLK、F_SETLK或F_SETLKW)。

*F_DUPFD*
- 复制文件描述符fd。新文件描述符作为函数值返回。它是尚未打开的各描述符中大于等于第3个参数值(取为整数值)中各值的最小值。新描述符与fd共享同一文件表项。但是，新描述符有它自己的一套描述符标志，其FD_CLOEXEC文件描述符标志被消除(这表示该描述符在exec时仍保持有效)。

*F_DUPFD_CLOEXEC*
- 复制文件描述符，设置与新描述符关联的FD_CLOEXEC文件描述符标志的值，返回新文件描述符。

*F_GETFD*
- 对应与fd的文件描述符标志作为函数值返回。当前只定义了一份文件描述符标志FD_CLOEXEC。

*F_SETFD*
- 对于fd设置文件描述符标志。新标志值按第3个参数(取为整数值)设置。

*F_GETFL*
- 对应于fd的文件状态标志作为函数值返回。我们在说明open函数时，已描述了文件状态标志。遗憾的是，5个访问方式标志(O_RDONLY、O_WRONLY、O_RDWR、O_EXEC以及O_SEARCH)并不各占1位(如前所述，由于历史原因，前3个标志的值分别是0、1和2.这5个值互斥、一个文件的访问方式只能取这5个值之一)。因此首先必须用屏蔽字O_ACCMODE取得访问方式位，然后将结果与这5个值中的每一个相比较。

*F_SETFL*
- 将文件状态标志设置为第3个参数的值(取为整数值)。可以更改的几个标志是：O_APPEND、O_NONBLOCK、O_SYNC、O_DSYNC、O_RSYNC、O_FSYNC和O_ASYNC。

*F_GETOWN*
- 获取当前接受SIGIO和SIGURG信号的进程ID或者进程组ID。

*F_SETOWN*
- 设置接受SIGIO和SIGURG信号的进程ID或进程组ID。正的arg指定一个进程ID，负的arg表示等于arg绝对值的一个进程组ID。

### 3.15. ioctl

```c
#include <unistd.h>     /* System V */
#include <sys/ioctl.h>  /* BSD and Linux */

/**
 * @param   fd
 * @param   request
 * @return  其他值      成功
 * @return  -1          出错
 */
int ioctl(int fd, int request, ...);    /* POSIX.1 */
int ioctl(int fd, unsigned long request, ...);
```
在此原型中，我们表示的只是ioctl函数本身所要求的头文件。通常，还要求另外的设备专用头文件。例如，除POSIX.1所说明的基本操作之外，终端I/O的ioctl命令都需要头文件\<termios.h>。

| 类别      | 变量名  | 头文件              | ioctl数 |
| -------- | ------- | ------------------ | :-----: |
| 盘标号    | DTOxxx  | \<sys/disklabel.h> | 4       |
| 文件I/O   | FIOxxx  | \<sys/filio.h>     | 14      |
| 磁盘I/O   | MTIOxxx | \<sys/mtio.h>      | 11      |
| 套接字I/O | SIOxxx  | \<sys/sockio.h>    | 73      |
| 终端I/O   | TIOxxx  | \<sys/ttycom.h>    | 43      |

FreeBSD中通用的ioctl操作

### 3.16. /dev/fd

较新的系统都提供名为/dev/fd的目录，其目录项是名为0、1、2等的文件。打开文件/dev/fd/n等效于复制描述符n(假定描述符n是打开的)。
```c
fd = open("/dev/fd/0", mode);
```
等效于：
```c
fd = dup(0);
```
所以描述符0和fd共享同一文件表项。例如，若描述符0先前被打开为只读，那么我们只能对fd进行读操作。即使系统忽略打开模式，而且下列调用是成功的：
```c
fd = open("/dev/fd/0", O_RDWR);
```
我们仍然不能对fd进行写操作。

/dev/fd文件主要由shell使用，它允许使用路径名作为调用参数的程序，能用处理其他路径名的相同方式处理标准输入和输出。例如，**cat**命令对其命令行参数采用了一种特殊处理，它将单独的一个字符“-”解释为标准输入。
```shell
filter file2 | cat file1 - file3 | lpr
```
```shell
filter file2 | cat file1 /dev/fd/0 file3 | lpr
```

## 4. 文件和目录

### 4.1. stat、fstat、fstatat和lstat

```c
#include <sys/stat.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

//返回pathname文件相关的信息结构
int stat(const char *restrict pathname, struct stat *restrict buf);

//获得已在描述符fd上打开文件的有关信息
int fstat(int fd, struct stat *buf);

//与stat类似，但是当命名的文件是一个符号链接时，返回该符号链接的信息，而不是由该符号链接引用的文件的信息
int lstat(const char *restrict pathname, struct stat *restrict buf);

//为一个相对于当前打开目录(由fd参数指向)的路径名返回文件统计信息
int fstatat(int fd, const char *restrict pathname, struct stat *restrict buf, int flag);
```
fstatat中flag参数控制着是否跟随着一个符号链接。当AT_SYMLINK_NOFOLLOW标志被设置时，fstatat不会跟随符号链接，而是返回符号链接本身的信息。否则，在默认情况下，返回的是符号链接所指向的实际文件的信息。如果fd参数的值是AT_FDCWD，并且pathname参数是一个相对路径名，fstatat会计算相对于当前目录的pathname参数。如果pathname是一个绝对路径，fd参数就会被忽略。这两种情况下，根据flag的取值，fstatat的作用就跟stat和lstat一样。

struct <a id="stat">stat结构</a>
```c
struct stat {
    mode_t              st_mode;    /* file type & mode (permissions) */
    ino_t               st_ino;     /* i-node number (serial number) */
    dev_t               st_dev;     /* device number (file system) */
    dev_t               st_rdev;    /* device number for special files */
    nlink_t             st_nlink;   /* numer of links */
    uid_t               st_uid;     /* user ID of owner */
    gid_t               st_gid;     /* group ID for owner */
    off_t               st_size;    /* size in bytes, for regular files */
    struct timespec     st_atime;   /* time of last access */
    struct timespec     st_mtime;   /* time of last modification */
    struct timespec     st_ctime;   /* time of last file status change */
    blksize_t           st_blksize; /* best I/O block size */
    blkcnt_t            st_blocks;  /* number of disk blocks allocated */
}
```
<a id="timespec">timespec结构</a>类型按照秒和纳秒定义了时间，至少包括下面两个字段：
```c
time_t tv_sec;
long tv_nsec;
```

### 4.2. 文件类型

文件类型：
1. 普通文件
2. 目标文件
3. 块特殊文件
    这种类型的文件提供对设备（如磁盘）带缓冲的访问，每次访问以固定长度为单位进行。
4. 字符特殊文件
    这种类型的文件提供对设备不带缓冲区的访问，每次访问长度可变。系统中所有设备要么是字符特殊文件，要么是块特殊文件。
5. FIFO
    这这种类型的文件用于进程间通信，有时也称为命名管道。
6. 套接字(socket)
    这种类型的文件用于进程间的网络通信。套接字也可用于在一台宿主机上进程之间的非网络通信。
7. 符号链接(symbolic link)
    这种类型的文件指向另一个文件。

文件类型信息包含在stat结构的st_mode成员中。

| 宏         | 文件类型     |
| ---------- | ----------- |
| S_ISREG()  | 普通文件     |
| S_ISDIR()  | 目录文件     |
| S_ISCHR()  | 字符特殊文件 |
| S_ISBLK()  | 块特殊文件   |
| S_ISFIFO() | 管道或FIFO   |
| S_ISLNK()  | 符号链接     |
| S_ISSOCK() | 套接字      |

\<sys/stat.h>中的文件类型宏

| 宏            | 对象的类型   |
| ------------- | ----------- |
| S_TYPEUSMQ()  | 消息队列     |
| S_TYPEISSEM() | 信号量      |
| S_TYPEISSHM() | 共享存储对象 |

\<sys/stat.h>中IPC类型宏
它们的参数并非st_mode，而是指向stat结构的指针。

早期的UNIX版本并不提供S_ISxxx宏，于是需要就st_mode与屏蔽字S_IFMT进行逻辑“与”运算，然后与名为S_IFxxx的常量相比较。大多数系统在文件\<sys/stat.h>中定义了此屏蔽字和相关的常量。
```c
#define S_ISDIR (mode) (((mode) & S_IFMT) == S_IFDIR)
```

### 4.3. 设置用户ID和设置组ID

与一个进程相关联的ID有6个或更多
- **实际用户ID和实际组ID**标识我们究竟是谁。这两个字段在登录时取自口令文件中的登录项。
- **有效用户ID、有效组ID以及附属组ID**决定了我们的文件访问权限。
- **保存的设置用户ID和保存的设置组ID**在执行一个程序时包含了有效用户ID和有效组ID的副本。

通常有效用户ID等于实际用户ID，有效组ID等于实际组ID。

文件模式字中**设置用户ID**(set-user-ID)位和**设置组ID**(set-group-ID)位。

### 4.4. 文件访问权限

<a id="file_access9">9个访问权限位</a>，\<sys/stat.h>

| st_mode屏蔽                   | 含义                        |
| ----------------------------- | -------------------------- |
| S_IRUSR<br>S_IWUSR<br>S_IXUSR | 用户读<br>用户写<br>用户执行 |
| S_IRGRP<br>S_IWGRP<br>S_IXGRP | 组读<br>组写<br>组执行       |
| S_IROTH<br>S_IWOTH<br>S_IXOTH | 其他读<br>其他写<br>其他执行 |

术语用户指的是文件所有者（owner）。**chmod**命令用户修改这9个权限位。该命令允许我们用u表示用户（所有者），用g表示组，用o表示其他。
这3类访问权限(即读、写及执行)以各种方式由不同的函数使用。使用方式汇总如下：
-   第一个规则是，我们用名字打开任意类型的文件时，对该名字中包含的每一个目录，包括它可能隐含的当前工作目录都应具有执行权限。这就是为什么对于目录其执行权限位常被称为搜索位的原因。
    例如，为了打开文件/usr/include/stdio.h，需要对目录/，/usr和/usr/include具有执行权限。然后，需要具有对文件本身的适当权限，这取决与以何种模式打开它(只读、读-写等)。
    如果当前目录是/usr/include，那么为了打开文件stdio.h，需要对当前目录有执行权限。这是隐含当前目录的一个示例。打开stdio.h文件与打开./stdio.h作用相同。
    **注意**，目录的读权限和执行权限的意义是不相同的。读权限允许我们读目录，获得在该目录中所有文件名的列表。当一个目录是我们要访问文件的路径名的一个组成部分时，对该目录的执行权限使我们可以通过该目录（也就是搜索该目录，寻找一个特定的文件名）。
-   对于一个文件的读权限决定了我们是否能够打开现有文件进行读操作。这与open函数的O_RDONLY和O_RDWR标志相关。
-   对于一个文件的写权限决定了我们是否能够打开现有文件进行写操作。这与open函数的O_WRONLY和O_RDWR标志相关。
-   为了在open函数中对一个文件指定O_TRUNC标志，必须对该文件具有写权限。
-   为了在一个目录中创建一个新文件，必须对该目录具有写权限和执行权限。
-   为了删除一个现有文件，必须对包含该文件的目录具有写权限和执行权限。对该文件本身则不需要有读、写权限。
-   如果用7个exec函数中的任何一个执行某个文件，那必须对该文件具有执行权限。该文件还必须是一个普通文件。

进程每次打开、创建或删除一个文件时，内核就进行文件访问权限测试，而这种测试可能涉及文件的所有者（st_uid和st_gid）、进程的有效ID（有效用户ID和有效组ID）以及进程的附属组ID（若支持的话）。两个所有者ID是文件的性质，而两个有效ID和附属组ID则是进程的性质。内核进行的测试具体如下。
1.  若进程的有效用户ID是0（超级用户），则允许访问。这给予了超级用户对整个文件系统进行处理的最充分的自由。
2.  若进程的有效用户ID等于文件的所有者ID（也就是进程拥有此文件），那么如果所有者适当的访问权限位被设置，则允许访问；否则拒绝访问。*适当的访问权限位*指的是，若进程为读而打开该文件，则用户读位应为1；若进程为写而打开该文件，则用户写位应为1，；若进程将执行该文件，则用户执行位应为1。
3.  若进程的有效用户组ID或进程的附属组ID之一等于文件的组ID，那么如果组适当的访问权限位被设置，则允许访问；否则拒绝访问。
4.  若其他用户适当的访问权限位被设置，则允许访问；否则拒绝访问。

### 4.5. 新文件和目录的所有权

open和creat创建新文件时，新文件的用户ID设置为进程的有效用户ID。关于组ID，POSIX.1允许事先选择下列之一作为新文件的组ID。
1.  新文件的组ID可以是进程的有效组ID。
2.  新文件的组ID可以是它所在目录的组ID。

### 4.6. 函数access和faccessat

access和faccessat函数是按实际用ID和实际组ID进行访问权限测试的。
```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int addess(const char *pathname, int mode);

int faccessat(int fd, const char *pathname, int mode, int flag);
```
其中，如果测试文件是否已经存在，mode就为F_OK；否则下表所列常量的按位或。

| mode | 说明        |
| ---- | ----------- |
| R_OK | 测试读权限   |
| W_OK | 测试写权限   |
| X_OK | 测试执行权限 |

faccessat函数与access函数在下面两种情况是相同的：
一种是pathname参数为绝对路径，另一种是fd参数取值为AT_FDCWD而pathname参数为相对路径。
否则，faccessat计算相对与打开目录（由fd参数指向）的pathname。
flag参数可以用来改变faccessat的行为，如果flag设置为AT_EACCESS，访问检查用的是调用进程的有效用户ID和有效组ID，而不是实际用户ID和实际组ID。

### 4.7. umask

umask函数为进程设置文件模式创建屏蔽字，并返回之前的值。
```c
#include <sys/stat.h>

/**
 * @return 之前文件模式创建的屏蔽字
 */
mode_t umask(mode_t cmask);
```
其中cmask由<a href="#file_access9">权限位表</a>表中列出的9个常量(S_IRUSR、S_IWUSR等)中的若干个按位“或”构成的。

<a id="umask_access">umask文件访问权限位</a>

| 屏蔽位 | 含义    |
| ----- | ------- |
| 0400  | 用户读   |
| 0200  | 用户写   |
| 0100  | 用户执行 |
| 0040  | 组读     |
| 0020  | 组写     |
| 0010  | 组执行   |
| 0004  | 其他读   |
| 0002  | 其他写   |
| 0001  | 其他执行 |

常用的几种umask值是002、022和027。002阻止其他用户写入你的文件。022阻止同组成员和其他成员写入你的文件。027阻止同组成员写你的文件以及其他用户读、写和执行你的文件。

符号格式指定许可的权限(即在文件创建屏蔽字中为0的位)而非拒绝的权限(即在文件创建屏蔽字中的为1的位)。
```shell
$ umask
002
$ umask -S
u=rwx,g=rwx,o=rx
$ umask 027
$ umask -S
u=rwx,g=rx,o=
```

### 4.8. chmod、fchmod和fchmodat

这3个函数使我们可以更改现有文件的访问权限
<a id="chmod"></a>
```c
#include <sys/stat/h>

/**
 * @return 0    成功
 * @return -1    失败
 */

int chmod(const char *pathname, mode_t mode);
int fchmod(int fd, mode_t mode);
int fchmodat(int fd, const char * pathname, mode_t mode, int flag);
```
chmod在指定的文件上进行操作。
fchmod在已打开的文件上进行操作。
fchmodat函数与chmod函数在下面两种情况下是相同的：
一种是pathname参数为绝对路径，
另一种是fd参数取值为AT_FDCWD而pathname参数为相对路径。
否则，fchmodat计算相对于打开目录(由fd参数指定)的pathname。flag参数可以用于改变fchmodat的行为，当设置了AT_SYMLINK_NOFOLLOW标志时，fchmodat并不会跟随符号链接。

<a id="chmod_mode">chmod函数的mode常量表</a>

| mode                                                                         | 说明                                                                          |
| ---------------------------------------------------------------------------- | ---------------------------------------------------------------------------- |
| S_ISUID<br>S_ISGID<br>S_ISVTX                                                | 执行时设置用户ID<br>执行时设置组ID<br>保存正文（粘着位）                         |
| S_IRWXU<br>&nbsp;&nbsp;S_IRUSR<br>&nbsp;&nbsp;S_IWUSR<br>&nbsp;&nbsp;S_IXUSR | 用户（所有者）读、写和执行<br>用户(所有者)读<br>用户(所有者)写<br>用户(所有者)执行 |
| S_IRWXG<br>&nbsp;&nbsp;S_IRGRP<br>&nbsp;&nbsp;S_IWGRP<br>&nbsp;&nbsp;S_IXGRP | 组读、写和执行<br>组读<br>组写<br>组执行                                        |
| S_IRWXO<br>&nbsp;&nbsp;S_IROTH<br>&nbsp;&nbsp;S_IWOTH<br>&nbsp;&nbsp;S_IXOTH | 其他读、写和执行<br>其他读<br>其他写<br>其他执行                                 |

chmod函数的mode常量表取自<a href="#file_access9">权限位表</a>，另外加了6个。

```shell
$ ls -l foo bar
-rw-------. 1 stanley stanley 0 Oct 16 20:50 bar
-rw-rw-rw-. 1 stanley stanley 0 Oct 16 20:50 foo
```
通过c_00015_chmod.c chmod 处理完后 
```shell
$ ls -l foo bar
-rw-r--r--. 1 stanley stanley 0 Oct 16 20:50 bar
-rw-rwSrw-. 1 stanley stanley 0 Oct 16 20:50 foo
```
ls命令将组执行权限表示为S，它表示设置组ID位已经设置，同时，组执行位未设置。
chmod函数更新的只是i节点最近一次被更改的时间。
chmod函数在系列条件下自动清楚两个权限位：
-   Solaris等系统对于普通文件的粘着位赋予了特殊含义，在这些系统上如果我们试图设置普通文件的粘着位（S_ISVTX）而且又没有超级用户权限，那么mode中的粘着位自动被关闭。这意味着只有超级用户才能设置普通文件的粘着位。这样做的理由是防止恶意用户设置粘着位，由此影响系统性能。
-   新创建文件的组ID可能不是调用进程所属的组。新文件的组ID可能是父目录的组ID。特别地，如果新文件的组ID不等于进程的有效组ID或者进程附属组ID中的一个，而且进程没有超级用户权限，那么设置组ID位会被自动被关闭。这就防止了用户创建一个设置组ID文件，而该文件是由并非该用户所属的组拥有的。

### 4.9. 粘着位

S_ISVTX位被称为粘着位（sticky bit）。
如果一个可执行程序的这一位被设置了，那么当该程序第一次被执行，在其终止时，程序正文部分的一个副本仍被保存在交换区（程序的正文部分是机器指令）。这使得下次执行该程序时能较快地将其装载入内存。
后来的UNIX版本称它为**保存正文位**（saved-test bit），因此也就有了常量S_ISVTX。现今较新的UNIX系统大多数都被指了虚拟存储系统以及快速文件系统，所以不再需要使用这种技术。

如果对一个目录设置粘着位，只有对该目录具有写权限的用户并且满足系列条件之一，才能删除或重命名该目录下的文件：
-   拥有此文件
-   拥有此目录
-   是超级用户

目录/tmp和/var/tmp是设置粘着位的典型候选者——任何用户都可在这两个目录中创建文件。任意用户（用户、组和其他）对这两个目录的权限通常都是读、写和执行。但是用户不能删除或者重命名属于其他人的文件。

### 4.10. chown、fchown、fchownat和lchown

下面几个chown函数可用于更改文件的用户ID和组ID。如果两个参数owner或group中的任意一个是-1，则对应的ID不变。
<a id="chown"></a><a id="lchown"></a>
```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int chown(const char *pathname, uid_t owner, gid_t group);
int fchown(int fd, uid_t owner, gid_t group);
int fchownat(int fd, const char *pathname, uid_t owner, gid_t group, int flag);
int lchown(const char *pathname, uid_t owner, gid_t group);
```
除了所引用的文件时符号链接以外，这4个函数的操作类似。在符号链接情况下，lchown和fchownat（设置了AT_SYMLINK_NOFOLLOW标志）更改符号链接本身的所有者，而不是该符号链接所指向的文件的所有者。
fchown函数改变fd参数指向的打开文件的所有者，既然它在一个已经打开的文件上操作，就不能用于改变符号连接的所有者。
fchownat函数与chown或者lchown函数在下面两种情况下是相同的：
一种是pathname参数为绝对路径。
另一种是fd参数取值为AT_FDCWD而pathname参数为相对路径。
在这两种情况下，如果flag参数中设置了AT_SYMLINK_NOFOLLOW标志，fchownat与lchown行为相同。如果fd参数中清除了AT_SYMLINK_NOFOLOW标志，则fchownat与chown行为相同。如果fd参数设置为打开目录的文件描述符，并且pathname参数是一个相对路径名，fchownat函数计算相对于打开目录的pathname。
若_POSIX_CHOWN_RESTRICTED对指定的文件生效，则
1.  只有超级用户进程能改变该文件的用户ID
2.  如果进程拥有此文件（其有效用户ID等于该文件的用户ID），参数owner等于-1或文件的用户ID，并且参数group等于进程的有效组ID或进程的附属组ID之一，那么一个非超级用户进程可以更改该文件的组ID。

### 4.11 文件长度

<a href="#stat">stat结构</a>成员st_size表示以字节为单位的文件的长度。此字段只对普通文件、目录文件和符号链接有意义。
对于普通文件：其文件长度可以是0，在开始读这个文件时，将得到文件结束（end-of-file）指示。
对于目录文件：文件长度通常是一个数（如16或512）的整数倍。
对于符号链接：文件长度是在文件名中的实际字节数。
当我们将st_blksize用于读操作时，读一个文件所需的时间量最少。为了提高效率，标准I/O库也试图一次读、写st_blksize个字节。
>应当了解的是，不同的UNIX版本其st_block所用的可能不是512字节的块。使用此值并不是可移植的。

<font size="5"><b>文件的空洞</b></font>
空洞是由所设置的偏移量超过文件尾端，并写入某些数据后造成的。
```shell
$ ls -l file.hole 
-rw-r--r--. 1 stanley stanley 16394 Oct 15 12:33 file.hole

$ du -s file.hole 
8 file.hole

$ od -c file.hole 
0000000   a   b   c   d   e   f   g   h   i   j  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0  \0
*
0040000   A   B   C   D   E   F   G   H   I   J
0040012
```

>在Linux上，报告的块数单位取决于是否设置了环境变量POSIXLY_CORRECT。当设置了该环境变量，du命令报告的是1024字节块的块数；没有设置该环境变量是，du命令报告的是512字节快的块数。

```shell
$ wc -c file.hole 
16394 file.hole
```
带-c选项的wc命令计算文件中的字符集（字节）。

如果使用实用程序（如cat）复制这个文件，那么所有的这些空洞都会被填满，其中所有实际数据字节皆填写为0。
```shell
$ cat file.hole > file.hole.copy
$ ls -l file.hole*
-rw-r--r--. 1 stanley stanley 16394 Oct 15 12:33 file.hole
-rw-rw-r--. 1 stanley stanley 16394 Oct 17 17:30 file.hole.copy

$ du -s file.hole*
8	file.hole
20	file.hole.copy
```

### 4.12. 文件截断

<a id="truncate"></a>
```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1    失败
 */

int truncate(const char *pathname, off_t length);
int ftruncate(int fd, off_t length);
```
这两个函数讲一个现有的文件长度截断为length。如果该文件以前的长度大于length，则超过length以外的数据就不能再访问。如果以前的长度小于length，文件长度将增加，在以前的文件尾端核心的文件尾端之前的数据将读作0（也就是可能在文件创建了一个空洞）。

### 4.13. 文件系统

UNIX文件系统的基本结构。
自己i节点和指向i节点的目录项之间的区别。

目前，正在使用的UNIX文件系统有多种实现。例如，Solaris支持多种不同类型的磁盘文件系统：传统的基本BSD的UNIX文件系统（成为UFS），读、写DOS格式软盘的文件系统（称为PCFS），以及读CD的文件系统（成为HSFS）。UFS是以Berkeley快速文件系统为基础的。

>   大部分UNIX文件系统支持大小写敏感的文件名。在Mac OS X 上，HFS文件系统是大小写保留的，并且是大小写不敏感比较的。

我么可以把一个磁盘分成一个或多个分区。每个分区可以包括一个文件系统。i节点是固定长度的记录项，它包含有关的大部分信息。

<a id="file_system">磁盘、分区和文件系统</a>

![文件系统][3]

<a id="cylinder_i_data">较详细的柱面组的i节点和数据块</a>

![i节点和数据块][4]

-   图中两个目录项指向同一个i节点。每个i节点中都有一个链接计数，其值是指向该i节点的目录项数。只有当链接计数减少至0时，才可删除该文件（也就是可以释放该文件占用的数据块）。这就是为什么“解除对一个文件的链接”操作并不总是意味着“释放该文件占用的磁盘块”的原因。这也是为什么删除一个目录项的函数被称之为unlink而不是delete的原因。在<a href="#stat">stat结构</a>中，链接计数包含在st_nlink成员中，其基本系统数据类型是nlink_t，这种链接类型成为硬链接。其中POSIX.1常量LINK_MAX制定了一个文件链接数的最大值。
-   另外一种链接类型为符号链接（symbolic link）。符号链接文件的实际内容（在数据块中）包含了该符号链接所指向的文件的名字。在下面的例子中，目录项中的文件名是3个字符的字符串lib，而在该文件中包含7字节的数据usr/lib：
    ```shell
    lrwxrwxrwx 1 root       7 Sep 25 07:14 lib -> usr/lib
    ```
    该i节点中的文件类型S_IFLNK，于是系统知道这是一个符号链接。
-   i节点包含了文件有关的所有信息：文件类型、文件访问权限位、文件长度和指向文件数据块的指针等。<a href="#stat">stat结构</a>中的大多数信息都取自i节点。只有两项重要数据存放在目录项中：文件名和i节点编号。其他数据项（如文件名长度和目录记录长度）并不是本书关心的。i节点编号的数据类型是ino_t。
-   因为目录项中的i节点指向同一文件系统中的相应i节点，一个目录项不能指向另一个文件系统的i节点。这就是为什么ln命令（构造一个指向一个现有文件的新目录项）不能跨越文件系统的原因。
-   当在不更换文件系统的情况下为一个文件重命名是，该文件的实际内容并未移动，只需构造一个指向现有i节点的新目录项，并删除老的目录项。链接计数不会改变。例如，为将文件/usr/lib/foo重命名为/usr/foo，如果目录usr/lib和/usr在同一文件系统中，则文件foo的内容无需移动。就是mv命令的通常操作方式。

我们说明了普通文件的链接计数概念，但是对于目录文件的链接计数字段又如何呢？假定我们在工作目录中构造了一个新目录：
```shell
$mkdir testdir
```

<a id="icon5">创建了目录testdir后的文件系统实例</a>

![testdir系统文件实例][5]

上图显示了其结果。注意，该图显式地显示了.和..目录项。
编号2549的i节点，其类型字段表示它是一个目录，链接计数为2。任何一个叶目录（不包含任何其他目录的目录）的链接数总是2，数值2来自命名该目录（testdir）的目录项以及在该目录项中的.项。编号为1267的i节点，其类型字段表示它是一个目录，链接数大于等于3.它大于或等于3的原因是，至少有3个目录项指向它：一个是命名它的目录项（在图中没有表示出来），第二个是在该目录中的.项，第三个是在其子目录testdir中的..项。注意，在父目录中的每一个子目录都使该父目录的链接计数增加1。

### 4.14. link、linkat、unlink、unlinkat和remove

任何一个文件可以有多个目录项指向其i节点。创建一个指向现有文件的链接的方法是使用link函数或者linkat函数。
<a id="link"></a>
```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1   出错
 */

int link(const char *existingpath, const char *newpath);
int linkat(int efd, const char *existingpath, int nfd, const char *newpath, int flag);
```
这两个函数创建一个新目录项newpath，它引用现有文件existingpath。如果newpath已经存在，则返回出错。只创建newpath中的最后一个分量，路径中的其他部分应当已经存在。
linkat函数，现有文件通过efd和existingpath参数指定，新的路径名通过nfd和newpath参数指定的。默认情况下，如果两个路径名中任一个是相对路径，那么它需要通过相对于对应的文件描述符进行计算。如果两个描述符中的任一个设置为**AT_FDCWD**，那么相对应的路径名（如果它是相对路径）就通过相对于当前目录进行计算。如果任意路径名是绝对路径。相应的文件描述符就会被忽略。
当现有文件是**符号链接**时，由flag参数来控制linkat函数是创建指向现有符号**链接的链接**，还是创建指向现有符号链接**所指向的文件的链接**。如果flag参数中设置了AT_SYMLINK_FOLLOW标志，就创建指向符号链接**目标的链接**。如果这个标志被清除了，则创建一个指向符号链接**本身的链接**。

为了删除一个现有的目录项，可以调用unlink函数。
<a id="unlink"></a>
```c
#include <unistd.h>

int unlink(const char *pathname);
int unlinkat(int fd, const char *pathname, int flag);
```
这两个函数删除目录项，并将由pathname所引用文件的链接数减1。如果对该文件还有其他链接，则认可通过其他链接访问该文件的数据。如果出错，则不对该文件做任何更改。
为了解除对文件的链接，必须对包含该目录项的目录具有写和执行权限。如果对该目录设置了粘着位，则对该目录必须具有写权限，并且具备下面三个条件之一：
-   拥有该文件
-   拥有该目录
-   具有超级用户权限
只有当链接数达到0时，该文件的内容才可被删除。另一个条件也会阻止删除文件的内容——只要有进程打开了该文件，其内容也不能被删除。关闭一个文件时，内核首先检查打开该文件的进程个数；如果这个计数达到0，内核再去检查其链接计数；如果计数也是0，那么就删除该文件的内容。
fd参数给出了一种方法，使调用进程可以改变unlinkat函数的默认行为。当AT_REMOVEDIR标志被设置时，unlinkat函数可以类似与rmdir一样删除目录。如果这个标志被清除，unlinkat与unlink执行同样的操作。

```shell
$ ls -l tempfile                查看文件大小
-rw-rw-r--. 1 stanley stanley 4000000004 Oct 18 11:27 tempfile

$ df /home/                     查看可用磁盘统建
Filesystem     1K-blocks     Used Available Use% Mounted on
/dev/sda3       28565504 15321728  11786064  57% /

$ ./c_00016_unlink &            在后台运行程序
[1] 3765                        shell打印其进程ID

$ file unlinked                 删除文件链接

ls -l tempfile                  观察文件是否仍然存在
ls: cannot access tempfile: No such file or directory

$ df /home                      检查可用磁盘空间有无变化
Filesystem     1K-blocks     Used Available Use% Mounted on
/dev/sda3       28565504 15321728  11786064  57% /

$ done                          程序执行结束，关闭所有打开文件
df /home                        检查可用磁盘空间有无变化

Filesystem     1K-blocks     Used Available Use% Mounted on
/dev/sda3       28565504 11415472  15692320  43% /
[1]+  Done                    ./c_00016_unlink
                                已用空间由57%变为43%
```

unlink的这种特性经常被程序用来确保即使是在程序崩溃时，它所创建的临时文件与不会遗留下来。进程用open和creat创建一个文件，然后立即调用unlink，因为该文件仍旧是打开的，所以不会将其内容删除。只有当进程关闭该文件或终止时（在这种情况下，内核关闭该进程所打开的全部文件），该文件的内容才被删除。

我们也可以用remove函数解除对一个文件或目录的链接。对于文件，remove的功能与unlink相同。对于目录，remove的功能与rmdir相同。
<a id="remove"></a>
```c
#include <stdio.h>

/**
 * @return 0    成功
 * @return -1    失败
 */
int remove(const char *pathname);
```

### 4.15. rename和renameat

文件或目录可以用rename函数或者renameat函数进行重命名。
<a id="rename"></a>
```c
#include <stdio.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int rename(const char *oldname, const char *newname);
int renameat(int oldfd, const char *oldname, int newfd, const char *newname);
```
使用oldname是指文件、目录还是符号链接，有几种情况需要加以说明。
1.  如果oldname指的是一个文件而不是目录，那么为该文件或符号链接重命名。在这种情况下，如果newname已存在，则它不能引用一个目录。如果newname已存在，而且不是一个目录，则先改该目录项删除然后将oldname重命名为newname。对包含oldname的目录以及包含newname的目录，调用进程必须具有写权限，因为将更改这两个目录。
2.  如若oldname指的是一个目录，那么为该目录重命名。如果newname已存在，则它必须引用一个目录，而且该目录应当是空目录（空目录指的是目录项中只有.和..项）。如果newname存在（而且是一个空目录），则先将其删除，然后将oldname重命名为newname。另外，当为一个目录重命名时，newname不能包含oldname作为其路径前缀。例如，不能将/usr/foo重命名为/usr/foo/testdir，因为旧名字（/usr/foo）是新名字的路径前缀，因而不能将其删除。
3.  如果oldname或newname引用符号链接，则处理的符号链接本身，而不是它所引用的文件。
4.  不能对.和..重命名。更确切地说，.和..都不能出现在oldname和newname的最后部分。
5.  作为一个特例，如果oldname和newname引用同一个文件，则函数不做任何更改而返回成功。

### 4.16. 符号链接

符号链接是对一个文件的间接指针，它与上一节所属的硬链接有所不同，硬链接直接指向文件的i节点。
-   硬链接通常要求链接和文件位于同一文件系统中。
-   只有超级用户才能创建指向目录的硬链接（在底层文件系统支持的情况下）。

若函数具有处理符号链接的功能，则其路径名参数引用由符号链接指向文件。否则，一个路径名参数引用链接本身，而不是由该链接指向的文件。

<a id="ln_deal">各个函数对符号链接的处理</a>

-   不跟随符号链接的函数：
    - [x]   lchown
    - [x]   lstat
    - [x]   readlink
    - [x]   remove
    - [x]   rename
    - [x]   unlink

-   跟随符号链接的函数：
    - [x]   access
    - [x]   chdir
    - [x]   chmod
    - [x]   creat
    - [x]   exec
    - [x]   link
    - [x]   open
    - [x]   opendir
    - [x]   pathconf
    - [x]   stat
    - [x]   truncate

上表的一个例外是，同时用O_CREAT和O_EXCL两者调用open函数。在此情况下，若路径名引用符号链接，open将出错返回，errno设置为EEXIST。这种处理方式的意图是堵塞一个安全性漏洞，以防止具有特权的进程被诱骗写错误的文件。

使用符号链接可能在文件系统中引入循环。大多数查找路径名的函数在这种情况下发生时都将出错返回，errno值为ELOOP。
```shell
$ mkdir foo
$ touch foo/a
$ ln -s ../foo foo/testdir
$ ls -l foo/
total 0
-rw-rw-r--. 1 stanley stanley 0 Oct 18 15:38 a
lrwxrwxrwx. 1 stanley stanley 6 Oct 18 15:38 testdir -> ../foo
```

![构成循环的符号链接testdir][6]

图中圆表示目录，正方形表示一个文件。
这样一个循环是很容易消除的。因为unlink并不跟随符号链接，所以可以用unlink文件foo/testdir。但是如果创建了一个构成这样循环的硬链接，那么就很难消除它。这就是为什么link函数不允许构造指向目录的硬链接的原因。

用open打开文件时，如果传递给open函数的路径名制定了一个符号链接，那么open跟随此链接到达所指定的文件。若次符号链接所指向的文件并不存在，则open返回出错，表示它不能打开该文件。
```shell
$ ln -s /no/such/file myfile
$ ls myfile 
myfile
$ cat myfile 
cat: myfile: No such file or directory
$ ls -l myfile
lrwxrwxrwx. 1 stanley stanley 13 Oct 18 16:29 myfile -> /no/such/file
```
ls -l 选项给我们两个提示：第一个字符是1，它表示这是一个符号链接，而->也表明这是一个符号链接。ls命令还有另一个选项-F，它会在符号链接的文件名后加一个@符号，在未使用-l选项时，这可以帮助我们识别出符号链接。

### 4.17 创建和读取符号链接

```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int symlink(const char *actulpath, const char *sympath);
int symlinkat(const char *actulpath, int fd, const char *sympath);
```
函数创建一个指向actulpath的新目录项sympath。在创建此符号链接时，并不要求actulpath已经存在。

因为open函数跟随符号链接，所以需要有一种方法打开该链接本身，并读该连接中的名字。
```c
#include <unistd.h>

/**
 * @return 读取的字节数     成功
 * @return -1              失败
 */

ssize_t readlink(const char *restrict pathname, char *restrict buf, size_t bufsize);
ssize_t readlinkat();
```
关于restrict<sup>[解释](https://baike.baidu.com/item/restrict/7384270?fr=aladdin)</sup>关键字的解释。C语言中的一种类型限定符（Type Qualifiers），用于告诉编译器，对象已经被指针所引用，不能通过除该指针外所有其他直接或间接的方式修改该对象的内容。

两个函数组合了open、read和close的所有操作。如果函数成功执行，则返回读入buf的字节数。在buf中返回的符号链接内容不以nul字符终止。

### 4.18. 文件的时间

对于把时间戳记录在秒级的文件系统来说，纳秒这个字段就会被填充为0.对于时间戳的记录精度高于秒级的文件系统来说，不足秒的值被转换成纳秒并记录在纳秒这个字段中。
对每个文件维护3个时间字段。

<a id="file_timefield">与每个文件相关的3个时间值</a>

| 字段    | 说明                   | 例子         | ls选项 |
| ------- | --------------------- | ------------ | ------ |
| st_atim | 文件数据的最后访问时间  | read         | -u     |
| st_mtim | 文件数据的最后修改时间  | write        | 默认   |
| st_ctim | i节点状态的最后更改时间 | chmod、chown | -c     |

修改时间（st_mtim）是文件内容最后一次被修改的时间。状态更改时间（st_ctim）是该文件的i节点最后一次被修改的时间。

访问时间常常用来删除在一定时间范围内没有被访问过的文件。
修改时间和状态更改时间可被用来归档那些内容已经修改过或i几点已经被更改过的文件。
ls 系统默认（-l或-t选项调用时）是按文件的修改时间的先后排序显示。-i选项使ls命令按访问时间排序。-c选项使ls命令按状态更改时间排序。

<a id="time_amc">各种函数对访问、修改和状态更改时间的作用</a>

<table>
    <tr>
        <td rowspan='2' align='middle' valign='middle'>函数</td>
        <td colspan='3' align='middle'>引用的文件或目录</td>
        <td colspan='3' align='middle'>所引用的文件或目录的父目录</td>
        <td rowspan='2' align='middle' valign='middle'>节</td>
        <td rowspan='2' align='middle' valign='middle'>备注</td>
    </tr>
    <tr>
        <td align='middle'>a</td>
        <td align='middle'>m</td>
        <td align='middle'>c</td>
        <td align='middle'>a</td>
        <td align='middle'>m</td>
        <td align='middle'>c</td>
    </tr>
    <tr>
        <td align='left'>
            chmod、fchmod<br>
            chown、fchown<br>
            creat<br>
            creat<br>
            exec<br>
            lchown<br>
            link<br>
            mkdir<br>
            mkfifo<br>
            open<br>
            open<br>
            pipe<br>
            read<br>
            remove<br>
            remove<br>
            rename<br>
            rmdir<br>
            truncate、ftruncate<br>
            unlink<br>
            utimes、utimesat、futimens<br>
            write<br>
        </td>
        <td align='middle'>
            <br>
            <br>
            &radic;<br>
            <br>
            &radic;<br>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            &radic;<br>
            &radic;<br>
            <br>
            <br>
            <br>
            <br>
            <br><br>
            &radic;<br>
            <br>
        </td>
        <td align='middle'>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            <br>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            <br>
            <br>
            <br>
            <br>
            &radic;<br>
            <br>
            &radic;<br>
            &radic;<br>
        </td>
        <td align='middle'>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            &radic;<br>
            <br>
            &radic;<br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
        </td>
        <td align='middle'>
        </td>
        <td align='middle'>
            <br>
            <br>
            &radic;<br>
            <br>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            &radic;<br>
            <br>
            <br>
            <br>
        </td>
        <td align='middle'>
            <br>
            <br>
            &radic;<br>
            <br>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            <br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            &radic;<br>
            <br>
            &radic;<br>
            <br>
            <br>
            <br>
        </td>
        <td align='middle'>
            <a href="#chmod">chmod</a><br>
            <a href="#chown">chown</a><br>
            <a href="#creat">creat</a><br>
            <a href="#creat">creat</a><br>
            <a href="#exec">exec</a><br>
            <a href="#lchown">lchown</a><br>
            <a href="#link">link</a><br>
            <a href="#mkdir">mkdir</a><br>
            <a href="#mkfifo">mkfifo</a><br>
            <a href="#open">open</a><br>
            <a href="#open">open</a><br>
            <a href="#pipe">pipe</a><br>
            <a href="#read">read</a><br>
            <a href="#remove">remove</a><br>
            <a href="#remove">remove</a><br>
            <a href="#rename">rename</a><br>
            <a href="#rmdir">rmdir</a><br>
            <a href="#truncate">truncate</a><br>
            <a href="#unlink">unlink</a><br>
            <a href="#utimes">utimes</a><br>
            <a href="#write">write</a><br>
        </td>
        <td align='middle'>
            <br>
            <br>
            O_CREAT 新文件<br>
            O_TRUNC 现有文件<br>
            <br>
            <br>
            第二个参数的父目录<br>
            <br>
            <br>
            O_CREAT 新文件<br>
            O_TRUNC 现有文件<br>
            <br>
            <br>
            删除文件=unlink<br>
            删除目录=rmdir<br>
            对于两个参数<br>
            <br>
            <br>
            <br>
            <br>
            <br>
        </td>
    </tr>
</table>

### 4.19. futimens、utimensat和utimes

futimens和utimensat函数可以指定那妙计精度的时间戳。用到的数据结构与<a href="#stat">stat</a>函数族相同的<a href="#timespec">timespec</a>结构。
<a id="futimens"></a><a id="futimensat"></a>
```c
#include <sys/stat.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int futimens(int fd, const struct timespec times[2]);
int futimensat(int fd, const char *path, const struct timespec times[2], int flag);
```
这两个函数的times数组的第一个元素包含访问时间，第二元素包含修改时间。这两个时间值是日历时间。这是自特定时间（1970年1月1日 00:00:00）以来所经过的描述。不足秒的部分用纳秒显示。
时间戳可以按下列4种方式之一进行指定。
1.  如果times参数是一个空指针，则访问时间和修改时间两者都设置成当前时间。
2.  如果times参数指向两个<a href="#timespec">timespec</a>结构的数组，任一数组元素的tv_nsec字段的值为UTIME_NOW，相应的时间戳就设置为当前时间，忽略相应的tc_sec字段。
3.  如果times参数指向两个<a href="#timespec">timespec</a>结构的数组，任一数组元素的tv_nsec字段的值为UTIME_OMIT，相应的时间戳保持不变，忽略相应的tv_sec字段。
4.  如果times参数指向两个<a href="#timespec">timespec</a>结构的数组，且tv_nsec字段的值为既不是UTIME_NOW也不是UTIME_OMIT，在这种情况下，相应的时间戳设置为相应的tv_sec和tv_nsec字段的值。

执行这些函数所要求的优先权取决于times参数的值。
-   如果times是一个空指针，或者任一tv_nsec字段设为UTIME_NOW，则进程的有效用户ID必须等于该文件的所有者ID；进程对该文件必须具有写权限，或者进程是一个超级用户进程。
-   如果times是非空指针，并且任一tv_nsec字段的值既不是UTIME_NOW也不是UTIME_OMIT，则进程的有效用户ID必须等于该文件的所有者ID，或者进程必须是一个超级用户进程。对文件只具有写权限是不够的。
-   如果times是非空指针，并且两个tv_nsec字段的值都为UTIME_OMIT，就不执行任何的权限检查。

futimens需要打开文件来更改它的时间。
utimensat提供了一种使用文件名更改文件时间的方法。pathname参数是相对于fd参数进行计算的，fd要么是打开目录的文件描述符，要么是设置为特殊值AT_FDCWD（强制通过相当于调用进程的当前目录计算pathname）。如果pathname制定了绝对路径，那么fd参数被忽略。

utimensat的flag参数可用于进一步修改默认行为。如果设置了AT_SYMLINK_NOFOLLOW标志，则符号链接本身的时间就会被修改（如果路径名指向符号链接）。默认的行为是跟随符号链接，并把文件的时间改成符号链接的时间。

<a id="utimes"></a>
```c
#include <sys/time.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int utimes(const char *pathname, const struct timeval timesp[2]);
```
<a id="timeval"></a>
struct timeval {
    time_t      tv_sec;     /* seconds 秒 */
    long        tv_usec;    /* microseconds 微秒 */
}
**注意**，我们不能对状态更改时间st_ctim（i节点最近被修改的时间）指定一个值。因为调用utimes函数时，此字段会被自动更新。

futimens函数实例。

使用带O_TRUNC选项的open函数将文件长度截断为0，但不更改其访问及修改时间。为了做到这一点，首相用stat函数得到这些时间，然后截断文件，最后在用futimens函数重置这个这两个时间。

```shell
$ cat changemod 
这是一个测试文件 changemod
$ cat times
这是一个测试文件 times
$ ls -l changemod times 
-rw-rw-r--. 1 stanley stanley 25 Oct 19 15:56 changemod
-rw-rw-r--. 1 stanley stanley  0 Oct 19 15:55 times
$ ls -lu changemod times 
-rw-rw-r--. 1 stanley stanley 25 Oct 19 16:08 changemod
-rw-rw-r--. 1 stanley stanley  0 Oct 19 16:08 times
$ date
Fri Oct 19 16:08:47 CST 2018
$ ./
c_00017_futimens  foo/              
$ ./c_00017_futimens changemod times 
$ ls -l changemod times 
-rw-rw-r--. 1 stanley stanley 0 Oct 19 15:55 changemod
-rw-rw-r--. 1 stanley stanley 0 Oct 19 15:55 times
$ ls -lu changemod times 
-rw-rw-r--. 1 stanley stanley 0 Oct 19 16:08 changemod
-rw-rw-r--. 1 stanley stanley 0 Oct 19 16:08 times
$ cat changemod 
$ cat times
```

### 4.20 mkdir、mkdirat和rmdir

用mkdir和mkdirat函数创建目录，用rmdir函数删除目录。
<a id="mkdir"></a><a id="mkdirat"></a>
```c
#include <sys/stat.h>

/**
 * @return 0    成功
 * @return -1   出错
 */

int mkdir(const char *pathname, mode_t mode);
int mkdirar(int fd, const char *pathname, mode_t mode);
```
这两个函数创建一个新的空目录。其中.和..目录项是自动创建的。
常见的错误是指定与文件相同的mode（只指定读、写权限）。但是，对于目录通常至少要设一个**执行权限位**，以允许访问该目录的文件名。
创建目录的命令mkdir必须由根用户拥有，而且对它设置了设置用户ID位。要通过一个进程创建一个目录，必须用system函数调用mkdir命令。

用rmdir函数可以删除一个空目录。
<a id="rmdir"></a>
```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1   出错
 */
int rmdir(const char *pathname);
```

### 4.21. 读目录

对某个目录具有访问权限的任一用户都可以读取目录，但是，为了防止文件系统产生混乱，只有内核才能写目录。
<a id="opendir"></a><a id="fopendior"></a><a id="readdir"></a><a id="rewinddir"></a><a id="closedir"></a><a id="telldir"></a><a id="seekdir"></a>
```c
#include <drient.h>

/**
 * @return 指针      成功
 * @return NULL     失败
 */
DIR *opendir(const char * pathname);
DIR *fopendior(int fd);

/**
 * @return 指针      成功
 * @return NULL     目录尾或失败
 */
struct dirent *readdir(DIR *dp);

void rewinddir(DIR *dp);

/**
 * @return 0    成功
 * @return -1   失败
 */
int closedir(DIR *dp);

/**
 * @return 与dp关联的目录中的当前位置
 */
long telldir(DIR *dp);

void seekdir(DIR *dp, long loc);
```
fopendior函数可以把打开文件描述符转换成目录处理函数需要的DIR结构。

实现对dirent结构所做的定义至少包含两个成员。
```c
ino_t d_ino;        // i-node number
char d_name[];      // null-terminated filename
```

遍历层次结构的函数ftw、nftw。ftw跟随符号链接，nftw不跟随符号链接。

### 4.22. chdir、fchdir和getcwd

每个进程都有一个当前工作目录，此目录是搜索所有相对路径名的起点。

chdir或fchdir函数可以用来更改当前工作目录
<a id="chdir"></a><a id="fchdir"></a>
```c
#include <unistd.h>

/**
 * @return 0    成功
 * @return -1   失败
 */

int chdir(const char *pathname);
int fchdir(int fd);
```

案例结果
```shell
> pwd
/notes/apue/code/bin
> ./c_00019_chdir 
chdir to /tmp succeeded
> pwd
/notes/apue/code/bin
```

Linux内核可以确定完成路径名。完整路径名的各个部分分布在mount表和dcahe表中，然后进行重新组装，比如在读取/proc/self/cew符号链接时。

getcwd获取当前工作目录的完整的绝对路径名
```c
#include <unistd.h>

/**
 * @param buf       缓冲区地址
 * @param size      缓冲区的长度(字节为单位)
 * @return buf      成功
 * @return NULL     失败
 */
char *getcwd(char *buf, size_t size);
```
buf缓冲区必须有足够的长度以容纳绝对路径名再加上一个终止null字符，否则返回错误。

chdir跟随符号链接，但是当getcwd沿目录树上溯遇到符号链接时，它并不了解该目录由符号链接所指向。

当一个应用程序需要在文件系统中返回到它工作的出发点时，getcwd函数是有用的，在更换工作目录之前，我们可以调用getcwd函数先将其保存起来。在完成了处理后，就可将所保存的原工作目录路径名作为调用参数传送给chdir，这样就返回了文件系统的出发点。

### 4.23. 设备特殊文件

st_dev和st_rdev这两个字段有关规则：
-   每个文件系统所在的存储设备都有其主、次设备号表示。设备号所用的数据类型是基本系统数据类型dev_t。主设备号标识设备驱动设备，有时编码为与其通信的外设板；次设备号标识特定的子设备。
-   我们通常可以使用两个宏：major和minor来访问主、次设备号，大多数实现都定义这两个宏。
    **注意**基于BSD的UNIX系统将它们定义在\<sys/types>中。Solaris在\<sys/mkdev.h>中定义了它们的函数原型，因为在\<sys/sysmacros.h>中的宏定义都弃用了。Linux将它们定义在\<sys/sysmacros.h>中，而该头文件又包含在\<sys/type.h>中。Centos6.9 需要包含\<sys/sysmacros.h>头文件。
-   系统中与每个文件名关联的st_dev值是文件系统的设备号，该文件系统包含了一文件名以及与其对应的i节点。
-   只有字符特殊文件和块特殊文件才有st_rdev值。此值包含实际设备的设备号。

```shell
> ./c_00021_devrdev / /home/stanley/ /dev/tty[01]
/: dev = 8/3
/home/stanley/: dev = 8/3
/dev/tty0: dev = 0/5 (character) rdev = 4/0
/dev/tty1: dev = 0/5 (character) rdev = 4/1

> mount
/dev/sda3 on / type ext4 (rw)
proc on /proc type proc (rw)
sysfs on /sys type sysfs (rw)
devpts on /dev/pts type devpts (rw,gid=5,mode=620)
tmpfs on /dev/shm type tmpfs (rw,rootcontext="system_u:object_r:tmpfs_t:s0")
/dev/sda1 on /boot type ext4 (rw)
none on /proc/sys/fs/binfmt_misc type binfmt_misc (rw)

> ls -l /dev/tty[01] /dev/sda[34]
brw-rw----. 1 root disk 8, 3 Oct 26 09:38 /dev/sda3
crw--w----. 1 root tty  4, 0 Oct 26 09:38 /dev/tty0
crw--w----. 1 root tty  4, 1 Oct 26 09:38 /dev/tty1
```
/dev/tty[01] 属于shell正则表达式语言以缩短所需的输入量。shell将字符串/dev/tty[01]扩展为 /dev/tty0 /dev/tty1。

### 4.24. 文件访问权限位小结

所有文件访问权限位如下图表示:
最后<a href="#file_access9">9个常量</a>可以分成如下3组：
```c
S_IRWXU = S_IRUSR | S_IWUSR | S_IXUSR
S_IRWXG = S_IRGRP | S_IWGRP | S_IXGRP
S_IRWXO = S_IROTH | S_IWOTH | S_IXOTH
```

<a id="file_access9_sum">文件访问权限位小结</a>

| 常量                                                                                       | 说明                       | 对普通文件的影响 | 对目录的影响 |
| ----------------------------------------------------------------------------------------- | -------------------------- | ------------------------------------------------------------------------------------ | ----------------------------------------------------------------------------- |
| <a id="S_ISUID">S_ISUID</a><br><a id="S_ISGID">S_ISGID</a>                                | 设置用户ID<br>设置组ID       | 执行时设置有效用户ID<br>若组执行位设置，则执行时设置有效组ID；否则使强制性锁起作用（若支持） | （未使用）<br>将在目录中创建的新文件的组ID设置为目录的组ID |
| <a id="S_ISVTX">S_ISVTX</a>                                                               | 粘着位                      | 在交换区缓存程序正文（若支持）                            | 限制在目录中删除和重命名文件 |
| <a id="S_IRUSR">S_IRUSR</a><br><a id="S_IWUSR">S_IWUSR</a><br><a id="S_IXUSR">S_IXUSR</a> | 用户读<br>用户写<br>用户执行 | 许可用户读文件<br>许可用户写文件<br>许可用户执行文件        | 许可用户读文件项<br>许可用户在目录中删除和创建文件<br>许可用户在目录中搜索给定文件名 |
| <a id="S_IRGRP">S_IRGRP</a><br><a id="S_IWGRP">S_IWGRP</a><br><a id="S_IXGRP">S_IXGRP</a> | 组读<br>组写<br>组执行       | 许可组读文件<br>许可组写文件<br>许可组执行文件             | 许可组读文件项<br>许可组在目录中删除和创建文件<br>许可组在目录中搜索给定文件名      |
| <a id="S_IROTH">S_IROTH</a><br><a id="S_IWOTH">S_IWOTH</a><br><a id="S_IXOTH">S_IXOTH</a> | 其他读<br>其他写<br>其他执行 | 许可其他读文件<br>许可其他写文件<br>许可其他执行文件        | 许可其他读文件项<br>许可其他在目录中删除和创建文件<br>许可其他在目录中搜索给定文件名 |

## 5. 标准I/O库

### 5.1. 流和FILE对象

对于标准I/O库，它们的操作是围绕流（stream）进行的。

对于ASCII字符表，一个字符用一个字节表示。对于国际字符集，一个字符可用多个字节表示。标准I/O文件流可用于单字节或多字节（“宽”）字符集。流的定向决定了所读、写的字符是单字节还是多字节的。一个流在创建时，并没有定向。在未使用的流上使用一个多字节的I/O函数，则将该流的定向设置为宽定向。单字节同理。

fwide函数可用于设置流的定向。
<a id="fwide"></a>
```c
#include <stdio.h>
#include <wchar.h>

/**
 * @return 正值     流是宽定向的
 * @return 复制     流是字节定向的
 * @return 0        流是为定向的
 */
int fwide(FILE *fp, int mode);
```
根据mode参数的不同值，fwide函数执行不同的工作。
-   mode参数值为负，fwide将试图使指定的流是字节定向的。
-   mode参数值为正，fwide将试图使指定的流是宽定向的。
-   mode参数值为0，fwide将试图使指定的流是宽定向的。

**注意**，fwide并不改变已定向流的定向，而且fwide**无出错返回**。我们唯一可依靠的是，在调用fwide前先清楚errno，从fwide返回时检查errno的值。

当打开一个流是，标准I/O函数<a href="#fopen">fopen</a>返回一个指向FILE对象的指针。
FILE对象包含了标准I/O库为管理该流需要的所有信息，包括用于实际I/O的文件描述符、指向用于该缓冲区的指针、缓冲区的长度、当前在缓冲区中的字符数以及出错标志等。

### 5.2. 标准输入、标准输出和标准错误

对一个进程预定义了3个流，并且这3个流可以自动地被进程使用，他们是：标准输入、标准输出和标准错误。
分别与文件描述符STDIN_FILENO、STDOUT_FILENO和STDERR_FILENO所引用的相同。预定义为stdin、stdout和stderr。

### 5.3. 缓冲

标准I/O库提供缓冲的目的是尽可能减少使用read和write调用的次数。
标准I/O提供了一下3种类型的缓冲。
1.  全缓冲。在这种情况下，在填满标准I/O缓冲区后才进行实际I/O操作。对于驻留在磁盘上的文件通常是由标准I/O库实施全缓冲的。在一个流上执行第一次I/O操作时，相关标准I/O函数通常调用malloc获得需使用的缓冲区。
    术语冲洗（flush）说明标准I/O缓冲区的写操作。缓冲区可由标准I/O例程自动冲洗（例如，当填满一个缓冲区时），或者可以调用函数fflush冲洗一个流。在UNIX系统中，flush有两种意思。在标准I/O库方面，flush（冲洗）意味着将缓冲区中的内容写到磁盘上（该缓冲区可能只是部分填满的）。在终端驱动程序方面（例如，tcflush函数），flush（刷清）表示丢弃已存储在缓冲区中的数据。
2.  行缓冲。在这种情况下，当在输入和输出中遇到换行符时，标准I/O库执行I/O操作。这允许我们一次输出一个字符（用标准库I/O函数fputc），但只有在写了一行之后才进行实际I/O操作。当流涉及终端时，通常使用行缓冲。
    对于行缓冲有两个限制：
    -   因为标准库I/O库用来收集每一行的缓冲区的长度是固定的，所有只要填满了缓冲区，那么即使还没有写一个换行符，也进行I/O操作。
    -   任何时候只要通过标准I/O库要求从（a）一个不带缓冲的流，或者（b）一个行缓冲的流（它从内核请求需要数据）得到输入数据，那么就会冲洗所有行缓冲输出流。
3.  不带缓冲。标准I/O库不对字符进行缓冲存储。例如，若用标准I/O函数fputs写15个字符到不带缓冲的流中，我们就期望这15个字符能立即输出，很可能s会用write函数将这些字符写到相关联的打开文件中。标准错误流stderr通常是不带缓冲的，这就使得出错信息可以尽快显示出来，而不管它们是否含有一个换行符。

ISO C要求下列缓冲特征。
-   当且晋档标准输入和标准输出并不指向交互式设备时，它们才是全缓冲的。
-   标准错误绝不会是全缓冲的。
很多系统默认下列类型缓冲：
-   标准错误是不带缓冲的。
-   若是指向终端设备的流，则是行缓冲的；否则是全缓冲的。

下列两个函数中的一个更改缓冲类型
<a id="setbuf"></a><a id="setvbuf"></a>
```c
#include <stdio.h>

/**
 * @return 0        成功
 * @return 非0      失败
 */

void setbuf(FILE *restrict fp, char *restrict buf);
int setvbuf(FILE *restrict fp, char *restrict buf, int mode, size_t size);
```
这些函数一定要在流已经被打开后调用，而且也应在对该执行任何一个其他操作之前调用。
setbuf函数打开或关闭缓冲机制。为了带缓冲进行I/O，参数buf必须指向一个长度为BUFSIZ的缓冲区（\<stdio.h>中）。通常在此之后该流就是全缓冲的，但是如果该流与一个终端设备相关，那么某些系统也可将其设置为行缓冲。为了关闭缓冲，将buf设置为NULL。
使用setvbuf，我们可以精确地说明所需的缓冲类型。这是根据mode参数实现的：
-   _IOFBF  全缓冲
-   _IOLBF  行缓冲
-   _IONBF  不带缓冲
如果指定一个不带缓冲的流，则忽略buf和size参数。
如果该流是带缓冲的，而buf是NULL，则标准I/O库将自动地为该流分别适配相当长度的缓冲区。适当长度指的是由常量BUFSIZ所指定的值。

<table>
    <tr align='middle' valign='middle'>
        <td>函数</td>
        <td>mode</td>
        <td>buf</td>
        <td>缓冲区及长度</td>
        <td>缓冲类型</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td rowspan='2'>setbuf</td>
        <td rowspan='2'></td>
        <td>非空</td>
        <td>长度为BUFSIZ的用户缓冲区buf</td>
        <td>全缓冲或行缓冲</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td>NULL</td>
        <td>（无缓冲区）</td>
        <td>不带缓冲</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td rowspan='5'>setvbuf</td>
        <td rowspan='2'>_IOFBF</td>
        <td>非空</td>
        <td>长度为size的用户缓冲区buf</td>
        <td rowspan='2'>全缓冲</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td>NULL</td>
        <td>合适长度的系统缓冲区buf</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td rowspan='2'>_IOFBF</td>
        <td>非空</td>
        <td>长度为size的用户缓冲区buf</td>
        <td rowspan='2'>行缓冲</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td>NULL</td>
        <td>合适长度的系统缓冲区buf</td>
    </tr>
    <tr align='middle' valign='middle'>
        <td>_IONBF</td>
        <td>（忽略）</td>
        <td>（无缓冲区）</td>
        <td>无缓冲区</td>
    </tr>
</table>

强制冲洗一个流。
<a id="fflush"></a>
```c
#include <stdio.h>

/**
 * @return 0        成功
 * @return EOF      失败
 */
int fflush(FILE *fp);
```
此函数使该流所有未写的数据都被传送至内核。作为一种特殊情形，如果fp是NULL，则此函数将导致所有输出流被冲洗。

### 5.4. 打开流

<a id="fopen"></a><a id="freopen"></a><a id="fdopen"></a>
```c
#include <stdio.h>

/**
 * @return 文件指针      成功
 * @return NULL         失败
 */

FILE *fopen(const char *restrict pathname, const char *restrict type);
FILE *freopen(const char *restrict pathname, const char *restrict type, FILE *restrict fp);
FILE *fdopen(int fd, const char *type);
```
type参数指定对该I/O流的读、写方式。

| type         | 说明                                | open标志 |
| -----------  | ----------------------------------- | -------- |
| r或rb        | 为读而打开                           | <a href="#oflag">`O_RDONLY`</a> |
| w或wb        | 把文件截断至0长，或为写而创建         | <a href="#oflag">`O_WRONLY|O_CREAT|O_TRUNC`</a> |
| a或ab        | 追加；为在文件尾写而打开，成为写而创建 | <a href="#oflag">`O_WRONLY|O_CREAT|O_APPEND`</a> |
| r+或r+b或rb+ | 为读和写而打开                       | <a href="#oflag">`O_RDWR`</a> |
| w+或w+b或wb+ | 把文件截断至0长，或为读和写而打开      | <a href="#oflag">`O_RDWR|O_CREAT|O_TRUNC`</a> |
| a+或a+b或ab+ | 为在文件尾读和写而打开或创建          | <a href="#oflag">`O_RDWR|O_CREAT|O_APPEND`</a> |

使用字符b作为type的一部分，这使得标准I/O系统可以区分文本文件和二进制文件。
当用追加写类型打开一个文件后，每次写都将数据写到文件的当前尾端位。如果有多个进程用哪个标准I/O追加写方式打开同一文件，那么来自每个进程的数据都将正确地写到文件中。
以读和写类型打开一个文件时（type+号），具有下列限制。
-   如果中间没有fflush、fseek、fsetpos或rewind，则在输出的后面不能直接跟随输入。
-   如果中间没有fssek、fsetpos或rewind，或者一个输入操作没有达到文件尾端，则在输入操作后不能直接跟随输出。

| 限制                                  | r                    | w                    | a                      | r+                         | w+                         | a+                            |
| ------------------------------------- | -------------------- | -------------------- | ---------------------- | -------------------------- | -------------------------- | ----------------------------- |
| 文件必须已存在<br>放弃文件以前的内容     | &radic; <br><br>     | <br>&radic;          |                        | &radic; <br><br>           | <br>&radic;                |                               |
| 流可以读<br>流可以写<br>流只可在尾端处写 | &radic; <br><br><br> | <br>&radic; <br><br> | <br>&radic;<br>&radic; | &radic;<br>&radic;<br><br> | &radic;<br>&radic;<br><br> | &radic;<br>&radic;<br>&radic; |

除非流引用终端设备，否则按系统默认，流被打开时是全缓冲的。
<a id="fclose"></a>
```c
#include <stdio.h>

/**
 * @return 0        成功
 * @return EOF      失败
 */
int fclose(FILE *fp);
```

### 5.5 读和写流

1.  每次一个字符的I/O。一次读或写一个字符。如果流是带缓冲的，则标准I/O函数处理所有缓冲。
2.  每次一行的I/O。如果想要一次读和写一行，则使用fgets和fputs。每行都以一个换行符终止。当调用fgets时，应说明能处理的最大行长。
3.  直接I/O。fread和fwrite函数支持这种类型的I/O。

#### 5.5.1. 输入函数

<a id="getc"></a><a id="fgetc"></a><a id="getchar"></a>
```c
#include <stdio.h>

/**
 * @return 下一个字符    成功
 * @return EOF          已到达文件尾端或出错
 */

int getc(FILE *fp);
int fgetc(FILE *fp);
int getchar(void);
```
getchar等同于getc(stdin)。getc可被实现为宏，fgetc不能实现为宏。
1.  getc的参数不应当是具有副作用的表达式，因为它可能会被计算多次。
2.  fgetc一定是一个函数，所以可以得到其地址。这就允许将fgetc的地址作为一个参数传送给另一个参数。
3.  因为fgetc所需时间很可能比调用getc要长。
不管是出错还是到达文件尾端，这3个函数都返回同样的值。
<a id="ferror"></a><a id="feof"></a><a id="clearerr"></a>
```c
#include <stdio.h>

/**
 * @return 非0（真）    条件为真
 * @return 0（假）      条件为假
 */

int ferror(FILE *fp);
int feof(FILE *fp);

void clearerr(FILE *fp);
```
大多数实现中，每个流在FILE对象中维护了两个标志：
-   出错标志
-   文件结束标志

调用clearerr可以清除这两个标志。
从流中读取数据以后，可以调用ungetc将字符再压送回流中。
<a id="ungetc"></a>
```c
#include <stdio.h>

int ungetc(int c, FILE *fp);
```

#### 5.5.2. 输出函数

<a id="putc"></a><a id="fputc"></a><a id="putchar"></a>
```c
#include <stdio.h>

/**
 * @return c        成功
 * @return EOF      失败
 */

int putc(int c, FILE *fp);
int fputc(int c, FILE *fp);
int puchar(int c);
```
输出函数与输入函数一样，putchar等同于putc(c, stdout)...

### 5.6. 每次一行I/O

<a id="fgets"></a><a id="gets"></a>
```c
#include <stdio.h>

/**
 * @return buf      成功
 * @return NULL     已达文件尾端或出错
 */

char *fgets(char *restrict buf, int n, FILE *restrict fp);
char *gets()char *buf;
```
gets从标准输入读，而fgets从指定的流读。~~gets~~不建议使用,使用gets时不能指定缓冲区的长度，可能造成缓冲区溢出。

<a id="fputs"></a><a id="puts"></a>
```c
#include <stdio.h>

/**
 * @return 非负值   成功
 * @return EOF     失败
 */

int fputs(const char *restrict str, FILE *restrict fp);
int puts(const char *str);
```
尽量使用fputs，而不要使用~~puts~~，puts比fputs要多写一个换行符在结尾。

### 5.7. 标准I/O的效率

标准I/O与直接调用read和write函数相比并不慢多少。对于大多数比较复杂的应用程序，最主要的用户CPU时间是由应用本身的各种处理消耗的，而不是由标准I/O例程消耗的。

### 5.8. 二进制I/O

<a id="fread"></a><a id="fwrite"></a>
```c
#include <stdio.h>

/**
 * @return 读或写的对象数
 */

size_t fread(void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
size_t fwrite(const void *restrict ptr, size_t size, size_t nobj, FILE *restrict fp);
```
两种常见用法：
1.  读或写一个二进制数组。将2~5个元素写到文件上。
    ```c
    float data[10];

    if(4 != fwrite(&data[2], sizeof(float), 4, fp)) {
        err_sys("fwrite error");
    }
    ```
    size为每个数组元素的长度，nobj为欲写的元素个数。
2.  读或写一个结构。
    ```c
    struct {
        short count;
        long total;
        char name[NAMESIZE];
    } item;
    
    if(1 != fwrite(&item, sizeof(item), 1, fp)) {
        err_sys("fwite, error");
    }
    ```
    size为结构的长度，nobj为1（要写的对象个数）。

对于读，如果出错或到达文件尾端，则此数字可以少于nobj。在这种情况，应调用ferror或feof以判断究竟是哪一种情况。对于写，如果返回值少于所要求的nobj，则出错。

fread和fwrite不具有跨平台性，甚至在同一平台也有可能会出现不同的情况，取决于结构体的结构优化和存储方式。

### 5.9. 定位流

3种定位标准I/O流的方法：
1.  ftel和fseek 它们假定文件的位置可以存放在一个长整形中。
2.  ftello和fseeko 它们使用off_t数据类型代替了长整形。
3.  fgetpos和fsetpos 它们使用一个抽象数据类型fpos_t记录文件的位置，这种数据类型可以根据需要定义为一个足够大的数，用以记录文件位置。
需要非UNIX系统上运行的应用程序应当使用fgetpos和fsetpos。

<a id="ftell"></a><a id="fseek"></a><a id="rewind"></a>
```c
#include <stdio.h>

/**
 * @return 当前文件位置指示     成功
 * @return -1L                 出错
 */
long ftell(FILE *fp);

/**
 * @return 0        成功
 * @return -1       失败
 */
int fseek(FILE *fp, long offset, int whence);

void rewind(FILE *fp);
```
whence与<a href="#lseek">lseek</a>函数中的设置相同。
对于文本文件，它们的文件当前位置可能不以简单的字节偏移量来度量。这主要也是在非UNIX系统中，它们可能以不同的格式存放文本文件。为了定位一个文本文件，whence一定要是SEEK_SET，而且offset只有两种值：0（后退到文件的起始位置），或是对该文件的ftell所返回的值。使用rewind函数也可将一个流设置到文件的起始位置。

<a id="ftello"></a><a id="fseeko"></a>
```c
#include <stdio.h>

/**
 * @return 当前文件位置     成功
 * @return (off_t)-1       失败
 */
off_t ftello(FILE *fp);

/**
 * @return 0        成功
 * @return -1       失败
 */
int fseeko(FILE *fp, off_t offset, int whence);
```

<a id="fgetpos"></a><a id="fsetpos"></a>
```c
#include <stdio.h>

/**
 * @return 0        成功
 * @return 非0      失败
 */

int fgetpos(FILE *restrict fp, fpos_t *restrict pos);
int fsetpos(FILE *fp, const fpos_t *pos);
```

### 5.10. 格式化I/O

#### 5.10.1 格式化输出

<a id="printf"></a><a id="fprintf"></a><a id="dprintf"></a><a id="sprintf"></a><a id="snprintf"></a>
```c
#include <stdio.h>

/**
 * @return 输出字符数    成功
 * @return 负值         输出出错
 */
int printf(const char *restrict format, ...);                                   //将格式化数据写到标准输出
int fprintf(FILE *restrict fp, const char *restrict format, ...);               //写至指定流
int dprintf(int fd, const char *restrict format, ...);                          //写至指定的文件描述符

/**
 * @todo   将格式化的字符送入数组buf中
 * @return 存入数组的字符数     成功
 * @return 负值                编码出错
 * @description                可能会造成有buf指向的缓冲区的溢出
 */
int sprintf(char *restrict buf, const char *restrict format, ...);              

/**
 * @todo   在该数组的尾端自动加一个null字节，但该字节不包括在返回值中
 * @return 将要存入数组的字符数     若缓冲区足够大
 * @return 负值                   编码出错
 */
int snprintf(char *restrict buf, size_t n, const char *restrict format, ...);
```
转换说明： `%[flags][fldwidth][precision][lenmodifier]convtype`
-   flags

    | 标志   | 说明                                               |
    | :-:    | ------------------------------------------------- |
    | '      | （撇号）将整数按千位分组字符                         |
    | -      | 在字段内左对齐输出                                  |
    | +      | 总是显示带符号转换的正负号                           |
    | (空格) | 如果第一个字符不是正负号，则在其前面加一个空格         |
    | #      | 指定另一种转换形式（例如，对于十六进制格式，加0x前缀） |
    | 0      | 添加前导0（而非空格）进行填充                        |

-   fldwidth 说明最小字段宽度。转换后参数字符数若小于宽度，则多余字符位置用空格填充，字段宽度是一个非负十进制数，或者是一个型号（*）。
-   precision 说明整数转换后最少输出数字位数、浮点数转换后小数点后的最少位数、字符串转换后最大字节数。精度是一个点（.），其后跟随一个可选的非负十进制数或一个星号（*）。
-   lenmodifier 参数长度。

    | 长度修饰符 | 说明                                               |
    | :-------: | -------------------------------------------------- |
    | hh        | 将相应的参数按`signed`或`unsigned char`类型输出      |
    | h         | 将相应的参数按`signed`或`unsigned short`类型输出     |
    | l         | 将相应的参数按`signed`或`unsigned long`类型输出      |
    | ll        | 将相应的参数按`signed`或`unsigned long long`类型输出 |
    | j         | `inmax_t`或`uintmax_t`                             |
    | z         | `size_t`                                           |
    | t         | `ptrdiff_t`                                        |
    | L         | `long double`                                      |
    
-   convtype 不是可选的。它控制如何解释参数。

    | 转换类型 | 说明                                                                  |
    | :------: | -------------------------------------------------------------------- |
    | d、i     | 有符号十进制                                                          |
    | o        | 无符号八进制                                                          |
    | u        | 无符号十进制                                                          |
    | x、X     | 无符号十六进制                                                        |
    | f、F     | 双精度浮点数                                                          |
    | e、E     | 指数格式双精度浮点数                                                   |
    | g、G     | 根据转换后的值解释为f、F、e或E                                          |
    | a、A     | 十六进制指数格式双精度浮点数                                            |
    | c        | 字符（若带长度修饰符l，为宽字符）                                       |
    | s        | 字符串（若带长度修饰符l，为宽字符）                                     |
    | p        | 指向void的指针                                                        |
    | n        | 到目前为止，此printf调用输出的字符的数目将被写入到指针所指向的带符号整型中 |
    | %        | 一个%字符                                                             |
    | C        | 宽字符（等效于lc）                                                     |
    | S        | 宽字符串（等效于ls）                                                   |

根据常规的转换说明，转换是按照它们出现在format参数之后的顺序应用于参数的。一种替代的转换说明语法也允许显示地用`%n$`序列来表示第n个参数的形式来命名参数。

5中printf族变体：
<a id="vprintf"></a><a id="vfprintf"></a><a id="vdprintf"></a><a id="vsprintf"></a><a id="vsnprintf"></a>
```c
#include <stdarg.h>
#include <stdio.h>

/**
 * @return 输出字符数    成功
 * @return 负值         输出出错
 */
int vprintf(const char *restrict format, va_list arg);
int vfprintf(FILE *restrict fp, const char *restrict format, va_list arg);
int vdprintf(int fd, const char *restrict format, va_list arg);

/**
 * @return 存入数组的字符数     成功
 * @return 负值                编码出错
 */
int vsprintf(char *restrict buf, const char *restrict format, va_list arg);              

/**
 * @return 将要存入数组的字符数     若缓冲区足够大
 * @return 负值                   编码出错
 */
int vsnprintf(char *restrict buf, size_t n, const char *restrict format, va_list arg);
```

#### 5.10.2 格式化输入

<a id="scanf"></a><a id="fscanf"></a><a id="sscanf"></a>
```c
#include <stdio.h>

/**
 * @return 赋值的输入项数    成功
 * @return EOF              输入出错或在任一转换前已达到文件尾端
 */

int scanf(const char *restrict format, ...);
int fscanf(FILE *restrict fp, const char *restrict format, ...);
int sscanf(const char *restrict buf, const char *restrict format, ...);
```
转换说明： `%[*][fldwidth][m][lenmodifier]convtype`
-   \*可选星号（*）用于抑制转换。按照转换说明的其余部分对输入进行转换，但转换结果并不存放在参数中。
-   fldwidth 最大宽度。
-   lenmodifier 说明要转换结果赋值的参数大小。
-   convtype 字段类似于printf族的转换类型字段。

    | 转换类型              | 说明                                                         |
    | :-------------------: | ----------------------------------------------------------- |
    | d                     | 有符号十进制，基数为10                                        |
    | i                     | 有符号十进制，基数由输入格式决定                               |
    | o                     | 无符号八进制（输入可选地有符号）                               |
    | u                     | 无符号十进制，基数为10（数可选地有符号）                        |
    | x、X                  | 无符号十六进制（输入可选地有符号）                              |
    | a、A、e、E、f、F、g、G | 浮点数                                                        |
    | c                     | 字符（若带长度修饰符l，为宽字符）                               |
    | s                     | 字符串（若带长度修饰符l，为宽字符）                             |
    | [                     | 匹配列出的字符序列，以]终止                                    |
    | [^                    | 匹配除列出以外的所有字符，以]终止                               |
    | p                     | 指向void的指针                                                |
    | n                     | 到目前为止该函数调用读取的字符数将被写入到指针所指向的无符号整型中 |
    | %                     | 一个%符号                                                     |
    | C                     | 宽字符（等效于lc）                                             |
    | S                     | 宽字符串（等效于ls）                                           |

-   m 赋值分配符。它可用于%c、%s以及%[转换符，迫使内存缓冲区分配空间以接纳转换字符串。

scanf函数族同样支持另外一种转换说明。允许显示地命名参数：序列`%n$`代表了第n个参数。
可变参数scanf族。
<a id="vscanf"></a><a id="vfscanf"></a><a id="vsscanf"></a>
```c
#include <stdarg.h>
#include <stdio.h>

/**
 * @return 赋值的输入项数    成功
 * @return EOF              输入出错或在任一转换前已达到文件尾端
 */

int vscanf(const char *restrict format, va_list arg);
int vfscanf(FILE *restrict fp, const char *restrict format, va_list arg);
int vsscanf(const char *restrict buf, const char *restrict format, va_list arg);
```

### 5.11 实现细节

在UNIX胸痛中，标准I/O库最终都要调用FILE I/O例程，每个标准I/O流都有一个与其相关联的文件描述符。
<a id="fileno"></a>
```c
#include <stdio.h>

/**
 * @return 与该流相关的文件描述符
 */
int fileno(FILE *fp);
```
实现参考书籍 Plauger[1992]The Standard C Library第12章提供了标准I/O库一种实现的全部源代码。

[GNU标准I/O库下载地址][glibc]

分析variousio.c运行结果
```shell
> ./variousio 
enter any character         ----按下回车

one line to standard error
stream = stdin, line buffered, buffer size = 1024
stream = stdout, line buffered, buffer size = 1024
stream = stderr, unbuffered, buffer size = 1
stream = /etc/passwd, fully buffered, buffer size = 4096
```

```shell
> ./variousio < /etc/group > std.out 2> std.err
> cat std.err 
one line to standard error
> cat std.out 
enter any character
stream = stdin, fully buffered, buffer size = 4096
stream = stdout, fully buffered, buffer size = 4096
stream = stderr, unbuffered, buffer size = 1
stream = /etc/passwd, fully buffered, buffer size = 4096
```
Centos系统默认是：标准输入、输出连至终端时，它们是行缓冲的。
当将这两个流重新定向到普通文件时，它们就变成是全缓冲的，其缓冲区长度是该文件系统有限选用的I/O长度。（<a href="#stat">stat</a>结构中得到的st_blksize值）。
标准错误是不带缓冲的。普通文件是按系统默认全缓冲的。

### 5.12. 临时文件

ISO C标准 创建临时文件。

<a id="tmpnam"></a><a id="tmpfile"></a>
```c
#include <stdio.h>

/**
 * @return 指向唯一路径名的指针
 */
char *tmpnam(cahr *ptr);

/**
 * @return 文件指针     成功
 * @return NULL        失败
 */
FILE *tmpfile(void);
```
tmpnam函数产生一个与现有文件名不同的一个有效吕景明字符串。每次调用它时，都产生一个不同的路径名，最多调用次数是TMP_MAX。

-   ptr为NULL。 所产生的路径名存放在一个静态区中，指向该静态区的指针作为函数值返回。后续调用tmpnam时，会重写该静态区（这意味着，如果我们调用此函数多次，而且还想保存路径名，则我们应当保存该路径名的副本）。
-   ptr不为NULL。则认为它应该是指向长度至少是L_tmpnam个字符的数组。所产生的路径名存放在该数组中，ptr也作为函数值返回。

tmpfile创建一个临时二进制文件（wb+），在关闭该文件或程序时将自动删除这种文件。
tmpfile通常先调用tmpnam产生一个唯一的路径名，然后，用该路径名创建一个文件，并立即unlink它。

XSI扩展两个处理临时文件的函数。

<a id="mkdtemp"></a><a id="mkstemp"></a>
```c
#include <stdlib.h>

/**
 * @return 指向目录名的指针     成功
 * @return NULL                出错
 */
char *mkdtemp(char *template);

/**
 * @return 文件描述符           成功
 * @return -1                   出错
 */
int mkstemp(char *template);
```
mkdtemp用来创建一个临时目录。
mkstemp用来创建一个临时文件。
与tmpfile不同，mkstemp创建的临时文件并不会自动删除。如果希望从文件系统命名空间中删除该文件，必须自己对它解除链接。
使用tmpnam和mkdtemp在返回唯一的路径名和用该名字创建文件之间存在一个时间窗口，在这个时间窗口中，另一个进程可以用相同的名字创建文件。incident应该使用tmpfile和mkstemp函数。

## 6. 系统数据文件和信息
## 7. 进程环境
## 8. 进程控制
## 9. 进程关系
## 10. 信号
## 11. 线程
## 12. 线程控制
## 13. 守护进程
## 14. 高级I/O
## 15. 进程间通信
## 16. 网络IPC：套接字
## 17. 高级进程间通信
## 18. 终端I/O
## 19. 伪终端
## 20. 数据库函数库
## 21. 与网络打印机通信


<!-- 下面为超链接地址 -->

<a id="exec"></a>
<a id="mkfifo"></a>
<a id="pipe"></a>

[1]: https://github.com/stanleyguo0207/notes/blob/master/apue/res/icon1.png
[2]: https://github.com/stanleyguo0207/notes/blob/master/apue/res/icon2.png
[3]: https://github.com/stanleyguo0207/notes/blob/master/apue/res/icon3.png
[4]: https://github.com/stanleyguo0207/notes/blob/master/apue/res/icon4.png
[5]: https://github.com/stanleyguo0207/notes/blob/master/apue/res/icon5.png
[6]: https://github.com/stanleyguo0207/notes/blob/master/apue/res/icon6.png
[glibc]: http://ftp.gnu.org/gnu/glibc/