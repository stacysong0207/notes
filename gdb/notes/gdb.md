**目录**
---

<!-- TOC -->

- [GDB调试学习笔记](#gdb调试学习笔记)
    - [前言](#前言)
    - [1. GDB概述](#1-gdb概述)
        - [1.1. 一个调试案例](#11-一个调试案例)

<!-- /TOC -->

# GDB调试学习笔记

## 前言

makefile基于自动化体系中重要的一笔，所有打算花点时间整理一下，文章摘自博客地https://blog.csdn.net/haoel/article/details/2879

## 1. GDB概述

GDB是GNU开源组织发布的一个强大的UNIX下的程序调试工具。或许，各位比较喜欢那种图形界面方式的，像VC、BCB等IDE的调试，但如果你是在UNIX平台下做软件，你会发现GDB这个调试工具有比VC、BCB的图形化调试器更强大的功能。所谓“寸有所长，尺有所短”就是这个道理。

一般来说，GDB主要帮忙你完成下面四个方面的功能：

1.  启动你的程序，可以按照你的自定义的要求随心所欲的运行程序。
2.  可让被调试的程序在你所指定的调置的断点处停住。（断点可以是条件表达式）
3.  当程序被停住时，可以检查此时你的程序中所发生的事。
4.  动态的改变你程序的执行环境。

从上面看来，GDB和一般的调试工具没有什么两样，基本上也是完成这些功能，不过在细节上，你会发现GDB这个调试工具的强大，大家可能比较习惯了图形化的调试工具，但有时候，命令行的调试工具却有着图形化工具所不能完成的功能。让我们一一看来。

### 1.1. 一个调试案例

源程序：tst.c
```c
#include <stdio.h>

int func(int n)
{
    int sum = 0, i;
    for(i = 0; i < n; i++) {
        sum += i;
    }
    return sum;
}

void main()
{
    int i;
    long result = 0;
    for(i = 1; i <= 100; i++) {
        result += i;
    }
    printf("result[1-100] = %d /n", result);
    printf("result[1-250] = %d /n", func(250));
}
```
编译生成执行文件：（Linux下）
```shell
> cc -g tst.c -o tst
```
使用GDB调试：
```shell
> gdb tst           <---------- 启动GDB

GNU gdb (GDB) Red Hat Enterprise Linux (7.2-92.el6)
Copyright (C) 2010 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>...
Reading symbols from ..../notes/gdb/code/src/tst...done.
(gdb) l 1           <-------------------- l命令相当于list，从第一行开始例出原码。
1	#include <stdio.h>
2	
3	int func(int n)
4	{
5	    int sum = 0, i;
6	    for (i = 0; i < n; i++)
7	    {
8	        sum += i;
9	    }
10	    return sum;
(gdb)               <-------------------- l命令相当于list，从第一行开始例出原码。
11	}
12	
13	
14	main()
15	{
16	    int i;
17	    long result = 0;
18	    for (i = 1; i <= 100; i++)
19	    {
20	        result += i;
(gdb) break 16      <-------------------- 设置断点，在源程序第16行处。
Breakpoint 1 at 0x4004fa: file gdb_00001_tst.c, line 16.
(gdb) break func    <-------------------- 设置断点，在函数func()入口处。
Breakpoint 2 at 0x4004cb: file gdb_00001_tst.c, line 5.
(gdb) info break    <-------------------- 设置断点，在函数func()入口处。
Num     Type           Disp Enb Address            What
1       breakpoint     keep y   0x00000000004004fa in main at gdb_00001_tst.c:16
2       breakpoint     keep y   0x00000000004004cb in func at gdb_00001_tst.c:5
(gdb) r             <--------------------- 运行程序，run命令简写
Starting program: ..../notes/gdb/code/src/tst 

Breakpoint 1, main () at gdb_00001_tst.c:17
17	    long result = 0;
Missing separate debuginfos, use: debuginfo-install glibc-2.12-1.212.el6.x86_64
(gdb) n             <--------------------- 单条语句执行，next命令简写。
18	    for (i = 1; i <= 100; i++)
(gdb) n
20	        result += i;
(gdb) n
18	    for (i = 1; i <= 100; i++)
(gdb) n
20	        result += i;
(gdb) c             <--------------------- 继续运行程序，continue命令简写。
Continuing.
result[1-100] = 5050           <---------- 程序输出。

Breakpoint 2, func (n=250) at gdb_00001_tst.c:5
5	    int sum = 0, i;
(gdb) n
6	    for (i = 0; i < n; i++)
(gdb) p i           <--------------------- 打印变量i的值，print命令简写。
$1 = 52
(gdb) n
8	        sum += i;
(gdb) n
6	    for (i = 0; i < n; i++)
(gdb) p sum
$2 = 0
(gdb) n
8	        sum += i;
(gdb) p i
$3 = 1
(gdb) n
6	    for (i = 0; i < n; i++)
(gdb) p sum
$4 = 1
(gdb) bt            <--------------------- 查看函数堆栈。
#0  func (n=250) at gdb_00001_tst.c:6
#1  0x0000000000400541 in main () at gdb_00001_tst.c:23
(gdb) finish
Run till exit from #0  func (n=250) at gdb_00001_tst.c:6
0x0000000000400541 in main () at gdb_00001_tst.c:23
23	    printf("result[1-250] = %d \n", func(250));
Value returned is $5 = 31125
(gdb) c             <--------------------- 继续运行。
Continuing.
result[1-250] = 31125          <---------- 程序输出。

Program exited with code 027.
(gdb) q             <--------------------- 退出gdb。
```
好了，有了以上的感性认识，还是让我们来系统地认识一下gdb吧。