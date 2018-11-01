**目录**
---

<!-- TOC -->

- [GDB调试学习笔记](#gdb调试学习笔记)
    - [前言](#前言)
    - [1. GDB概述](#1-gdb概述)
        - [1.1. 一个调试案例](#11-一个调试案例)
    - [2. GDB使用](#2-gdb使用)
    - [3. GDB命令概貌](#3-gdb命令概貌)
        - [3.1. GDB中运行UNIX的shell程序](#31-gdb中运行unix的shell程序)
        - [3.2. 在GDB中运行程序](#32-在gdb中运行程序)
        - [3.3. 调试已运行的程序](#33-调试已运行的程序)
        - [3.4. 暂停/恢复程序](#34-暂停恢复程序)
            - [3.4.1. 设置断点（BreakPoint）](#341-设置断点breakpoint)
            - [3.4.2. 设置观察点（WatchPoint）](#342-设置观察点watchpoint)
            - [3.4.3. 设置捕捉点（CatchPoint）](#343-设置捕捉点catchpoint)
            - [3.4.4. 维护停止点](#344-维护停止点)
            - [3.4.5. 停止条件维护](#345-停止条件维护)
            - [3.4.6. 为停止点设定运行命令](#346-为停止点设定运行命令)
            - [3.4.7. 断点菜单](#347-断点菜单)
            - [3.4.8. 恢复程序运行和单步调试](#348-恢复程序运行和单步调试)
            - [3.4.9. 信号（Signals）](#349-信号signals)
            - [3.4.10. 线程（Thread Stops）](#3410-线程thread-stops)
        - [3.5. 查看栈信息](#35-查看栈信息)
        - [3.6. 查看源程序](#36-查看源程序)
            - [3.6.1. 显示源代码](#361-显示源代码)
            - [3.6.2. 搜索源代码](#362-搜索源代码)
            - [3.6.3. 指定源文件的路径](#363-指定源文件的路径)
            - [3.6.4. 源代码的内存](#364-源代码的内存)
        - [3.7. 查看运行时数据](#37-查看运行时数据)
            - [3.7.1. 表达式](#371-表达式)
            - [3.7.2. 程序变量](#372-程序变量)

<!-- /TOC -->

# GDB调试学习笔记

## 前言

**更多学习笔记见**https://github.com/stanleyguo0207/notes

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

## 2. GDB使用

一般来说GDB主要调试的是C/C++的程序。要调试C/C++的程序，首先在编译时，我们必须要把调试信息加到可执行文件中。使用编译器（cc/gcc/g++）的 **-g** 参数可以做到这一点。如：
```shell
> cc -g hello.c -o hello
> g++ -g hello.cpp -o hello
```
如果没有 **-g**，你将看不见程序的函数名、变量名，所代替的全是运行时的内存地址。当你用 **-g** 把调试信息加入之后，并成功编译目标代码以后，让我们来看看如何用gdb来调试他。

启动GDB的方法有以下几种：
1.  ```gdb <program>```

    program也就是你的执行文件，一般在当然目录下。

2.  ```gdb <program> core```

    用gdb同时调试一个运行程序和core文件，core是程序非法执行后core dump后产生的文件。

3.  ```gdb <program> \<PID>```

    如果你的程序是一个服务程序，那么你可以指定这个服务程序运行时的进程ID。gdb会自动attach上去，并调试他。program应该在**PATH**环境变量中搜索得到。

GDB启动时，可以加上一些GDB的启动开关，详细的开关可以用gdb -help查看。我在下面只例举一些比较常用的参数：

-   ```-symbols <file>```
    ```-s \<file>```

    从指定文件中读取符号表。

-   ```-se \<file>```

    从指定文件中读取符号表信息，并把他用在可执行文件中。

-   ```-core <file>```
    ```-c \<file>```

    调试时core dump的core文件。

-   ```-directory <directory>```
    ```-d <directory>```

    加入一个源文件的搜索路径。默认搜索路径是环境变量中PATH所定义的路径。

## 3. GDB命令概貌

启动gdb后，就你被带入gdb的调试环境中，就可以使用gdb的命令开始调试程序了，gdb的命令可以使用help命令来查看，如下所示：
```shell
GNU gdb (GDB) Red Hat Enterprise Linux (7.2-92.el6)
Copyright (C) 2010 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.  Type "show copying"
and "show warranty" for details.
This GDB was configured as "x86_64-redhat-linux-gnu".
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
(gdb) help
List of classes of commands:

aliases -- Aliases of other commands
breakpoints -- Making program stop at certain points
data -- Examining data
files -- Specifying and examining files
internals -- Maintenance commands
obscure -- Obscure features
running -- Running the program
stack -- Examining the stack
status -- Status inquiries
support -- Support facilities
tracepoints -- Tracing of program execution without stopping the program
user-defined -- User-defined commands

Type "help" followed by a class name for a list of commands in that class.
Type "help all" for the list of all commands.
Type "help" followed by command name for full documentation.
Type "apropos word" to search for commands related to "word".
Command name abbreviations are allowed if unambiguous.
(gdb) 
```
gdb的命令很多，gdb把之分成许多个种类。help命令只是例出gdb的命令种类，如果要看种类中的命令，可以使用help \<class> 命令，如：help breakpoints，查看设置断点的所有命令。也可以直接help \<command>来查看命令的帮助。

gdb中，输入命令时，可以不用打全命令，只用打命令的前几个字符就可以了，当然，命令的前几个字符应该要标志着一个唯一的命令，在Linux下，你可以敲击两次TAB键来补齐命令的全称，如果有重复的，那么gdb会把其例出来。

-   示例一：在进入函数func时，设置一个断点。可以敲入break func，或是直接就是b func
    ```shell
    (gdb) b func
    Breakpoint 1 at 0x8048458: file hello.c, line 10.
    ```

-   示例二：敲入b按两次TAB键，你会看到所有b打头的命令：
    ```shell
    (gdb) b
    backtrace  break      bt
    (gdb)
    ```

-   示例三：只记得函数的前缀，可以这样：
    ```shell
    (gdb) b make_ <按TAB键>
    （再按下一次TAB键，你会看到:）
    make_a_section_from_file     make_environ
    make_abs_section             make_function_type
    make_blockvector             make_pointer_type
    make_cleanup                 make_reference_type
    make_command                 make_symbol_completion_list
    (gdb) b make_
    ```
    GDB把所有make开头的函数全部例出来给你查看。

-   示例四：调试C++的程序时，有可以函数名一样。如：
    ```shell
    (gdb) b 'bubble( M-? 
    bubble(double,double)    bubble(int,int)
    (gdb) b 'bubble(
    ```
    你可以查看到C++中的所有的重载函数及参数。（注：M-?和“按两次TAB键”是一个意思）

要退出gdb时，只用发quit或命令简称q就行了。

### 3.1. GDB中运行UNIX的shell程序

在gdb环境中，你可以执行UNIX的shell的命令，使用gdb的shell命令来完成：
```shell
shell <command string>
```
调用UNIX的shell来执行\<command string>，环境变量SHELL中定义的UNIX的shell将会被用来执行\<command string>，如果SHELL没有定义，那就使用UNIX的标准shell：/bin/sh。（在Windows中使用Command.com或cmd.exe）

还有一个gdb命令是make：
```shell
make <make-args> 
```
可以在gdb中执行make命令来重新build自己的程序。这个命令等价于“shell make \<make-args>”。

### 3.2. 在GDB中运行程序

当以gdb \<program>方式启动gdb后，gdb会在PATH路径和当前目录中搜索\<program>的源文件。如要确认gdb是否读到源文件，可使用**l**或**list**命令，看看gdb是否能列出源代码。

在gdb中，运行程序使用**r**或是**run**命令。程序的运行，你有可能需要设置下面四方面的事。

1.  程序运行参数。<br>
    ```set args``` 可指定运行时参数。（如：set args 10 20 30 40 50）
    ```show args``` 命令可以查看设置好的运行参数。

2.  运行环境。<br>
    ```path <dir>``` 可设定程序的运行路径。
    ```show paths``` 查看程序的运行路径。
    ```set environment varname [=value]``` 设置环境变量。如：```set env USER=stanley```
    ```show environment [varname]``` 查看环境变量。

3.  工作目录。
    ```cd <dir>``` 相当于shell的cd命令。
    ```pwd``` 显示当前的所在目录。

4.  程序的输入输出。
    ```info terminal``` 显示你程序用到的终端的模式。
    使用重定向控制程序输出。如：```run > outfile```
    tty命令可以指写输入输出的终端设备。如：```tty /dev/ttyb```

### 3.3. 调试已运行的程序

1.  在UNIX下用ps查看正在运行的程序的PID（进程ID），然后用```gdb <program> PID```格式挂接正在运行的程序。
2.  先用```gdb <program>```关联上源代码，并进行gdb，在gdb中用attach命令来挂接进程的PID。并用**detach**来取消挂接的进程。

### 3.4. 暂停/恢复程序

调试程序中，暂停程序运行是必须的，GDB可以方便地暂停程序的运行。你可以设置程序的在哪行停住，在什么条件下停住，在收到什么信号时停往等等。以便于你查看运行时的变量，以及运行时的流程。

当进程被gdb停住时，你可以使用```info program```来查看程序的是否在运行，进程号，被暂停的原因。

在gdb中，我们可以有以下几种暂停方式：**断点**（BreakPoint）、**观察点**（WatchPoint）、**捕捉点**（CatchPoint）、**信号**（Signals）、**线程停止**（Thread Stops）。如果要恢复程序运行，可以使用**c**或是**continue**命令。

#### 3.4.1. 设置断点（BreakPoint）

我们用break命令来设置断点。正面有几点设置断点的方法:

-   ```break <function> ```

    在进入指定函数时停住。C++中可以使用class::function或function(type,type)格式来指定函数名。
-   ```break <linenum>```

    在指定行号停住。
-   ```break +offset```
    ```break -offset```

    在当前行号的前面或后面的offset行停住。offiset为自然数。

-   ```break filename:linenum```
    
    在源文件filename的linenum行处停住。

-   ```break filename:function```
    
    在源文件filename的function函数的入口处停住。

-   ```break *address```
    
    在程序运行的内存地址处停住。

-   ```break```

    break命令没有参数时，表示在下一条指令处停住。

-   ```break ... if <condition>```

    ...可以是上述的参数，condition表示条件，在条件成立时停住。比如在循环境体中，可以设置```break if i=100```，表示当i为100时停住程序。

查看断点时，可使用info命令，如下所示：（注：n表示断点号）
-   ```info breakpoints [n]```
-   ```info break [n]```

#### 3.4.2. 设置观察点（WatchPoint）

观察点一般来观察某个表达式（变量也是一种表达式）的值是否有变化了，如果有变化，马上停住程序。我们有下面的几种方法来设置观察点：

-   ```watch <expr>```

    为表达式（变量）expr设置一个观察点。一量表达式值有变化时，马上停住程序。

-   ```rwatch <expr>```

    当表达式（变量）expr被读时，停住程序。

-   ```awatch <expr>```

    当表达式（变量）的值被读或被写时，停住程序。

-   ```info watchpoints```

    列出当前所设置了的所有观察点。

#### 3.4.3. 设置捕捉点（CatchPoint）

你可设置捕捉点来补捉程序运行时的一些事件。如：载入共享库（动态链接库）或是C++的异常。设置捕捉点的格式为：
```shell
catch <event>
```
当event发生时，停住程序。event可以是下面的内容：
1.  ```throw``` 一个C++抛出的异常。（throw为关键字）
2.  ```catch``` 一个C++捕捉到的异常。（catch为关键字）
3.  ```exec``` 调用系统调用exec时。（exec为关键字，目前此功能只在HP-UX下有用）
4.  ```fork``` 调用系统调用fork时。（fork为关键字，目前此功能只在HP-UX下有用）
5.  ```vfork``` 调用系统调用vfork时。（vfork为关键字，目前此功能只在HP-UX下有用）
6.  ```load``` 或 ```load <libname>``` 载入共享库（动态链接库）时。（load为关键字，目前此功能只在HP-UX下有用）
7.  ```unload``` 或 ```unload <libname>``` 卸载共享库（动态链接库）时。（unload为关键字，目前此功能只在HP-UX下有用）

```shell
tcatch <event>
```
只设置一次捕捉点，当程序停住以后，应点被自动删除。

#### 3.4.4. 维护停止点

上面说了如何设置程序的停止点，GDB中的停止点也就是上述的三类。在GDB中，如果你觉得已定义好的停止点没有用了，你可以使用**delete**、**clear**、**disable**、**enable**这几个命令来进行维护。

-   ```clear```

    清除所有的已定义的停止点。

-   ```clear <function>```
    ```clear <filename:function>```

    清除所有设置在函数上的停止点。

-   ```clear <linenum>```
    ```clear <filename:linenum>```

    清除所有设置在指定行上的停止点。

-   ```delete [breakpoints] [range...]```

    删除指定的断点，breakpoints为断点号。如果不指定断点号，则表示删除所有的断点。range 表示断点号的范围（如：3-7）。其简写命令为d。

比删除更好的一种方法是**disable**停止点，**disable**了的停止点，GDB不会删除，当你还需要时，**enable**即可，就好像回收站一样。

-   ```disable [breakpoints] [range...]```

    **disable**所指定的停止点，**breakpoints**为停止点号。如果**什么都不指定**，表示disable所有的停止点。简写命令是**dis**.

-   ```enable [breakpoints] [range...]```

    enable所指定的停止点，breakpoints为停止点号。

-   ```enable [breakpoints] once range...```

    enable所指定的停止点一次，当程序停止后，该停止点马上被GDB自动**disable**。

-   ```enable [breakpoints] delete range...```

    enable所指定的停止点一次，当程序停止后，该停止点马上被GDB自动删除。

#### 3.4.5. 停止条件维护

前面在说到设置断点时，我们提到过可以设置一个条件，当条件成立时，程序自动停止，这是一个非常强大的功能，这里，我想专门说说这个条件的相关维护命令。一般来说，为断点设置一个条件，我们使用if关键词，后面跟其断点条件。并且，条件设置好后，我们可以用condition命令来修改断点的条件。（只有break和watch命令支持if，catch目前暂不支持if）
-   ```condition <bnum> <expression>```

    修改断点号为bnum的停止条件为expression。

-   ```condition <bnum>```

    清除断点号为bnum的停止条件。

还有一个比较特殊的维护命令ignore，你可以指定程序运行时，忽略停止条件几次。
-   ```ignore <bnum> <count>```

    表示忽略断点号为bnum的停止条件count次。

#### 3.4.6. 为停止点设定运行命令

我们可以使用GDB提供的command命令来设置停止点的运行命令。也就是说，当运行的程序在被停止住时，我们可以让其自动运行一些别的命令，这很有利行自动化调试。对基于GDB的自动化调试是一个强大的支持。
```shell
commands [bnum]
... command-l ist ...
end
```
为断点号bnum指写一个命令列表。当程序被该断点停住时，gdb会依次运行命令列表中的命令。
例如：
```shell
break foo if x>0
commands
printf "x is %d/n",x
continue
end
```
断点设置在函数foo中，断点条件是x>0，如果程序被断住后，也就是，一旦x的值在foo函数中大于0，GDB会自动打印出x的值，并继续运行程序。

如果你要清除断点上的命令序列，那么只要简单的执行一下commands命令，并直接在打个end就行了

#### 3.4.7. 断点菜单

在C++中，可能会重复出现同一个名字的函数若干次（函数重载），在这种情况下，break \<function>不能告诉GDB要停在哪个函数的入口。当然，你可以使用break \<function(type)>也就是把函数的参数类型告诉GDB，以指定一个函数。否则的话，GDB会给你列出一个断点菜单供你选择你所需要的断点。你只要输入你菜单列表中的编号就可以了。如：
```shell
(gdb) b String::after
[0] cancel
[1] all
[2] file:String.cc; line number:867
[3] file:String.cc; line number:860
[4] file:String.cc; line number:875
[5] file:String.cc; line number:853
[6] file:String.cc; line number:846
[7] file:String.cc; line number:735

> 2 4 6
Breakpoint 1 at 0xb26c: file String.cc, line 867.
Breakpoint 2 at 0xb344: file String.cc, line 875.
Breakpoint 3 at 0xafcc: file String.cc, line 846.
Multiple breakpoints were set.
Use the "delete" command to delete unwanted breakpoints.
(gdb)
```
可见，GDB列出了所有after的重载函数，你可以选一下列表编号就行了。0表示放弃设置断点，1表示所有函数都设置断点。

#### 3.4.8. 恢复程序运行和单步调试

当程序被停住了，你可以用continue命令恢复程序的运行直到程序结束，或下一个断点到来。也可以使用step或next命令单步跟踪程序。

-   ```continue [ignore-count]```
    ```c [ignore-count]```
    ```fg [ignore-count]```

    恢复程序运行，直到程序结束，或是下一个断点到来。ignore-count表示忽略其后的断点次数。continue，c，fg三个命令都是一样的意思。

-   ```step <count>```

    单步跟踪，如果有函数调用，他会**进入该函数**。进入函数的前提是，此函数被编译有debug信息。很像VC等工具中的**step in**。后面可以加count也可以不加，不加表示一条条地执行，加表示执行后面的count条指令，然后再停住。

-   ```next <count>```

    同样单步跟踪，如果有函数调用，他**不会进入该函数**。很像VC等工具中的**step over**。后面可以加count也可以不加，不加表示一条条地执行，加表示执行后面的count条指令，然后再停住。

-   ```set step-mode```
    ```set step-mode on```
    
    打开step-mode模式，于是，在进行单步跟踪时，程序不会因为没有debug信息而不停住。这个参数有很利于查看机器码。

-   ```set step-mod off```

    关闭step-mode模式。

-   ```finish```

    运行程序，直到当前函数完成返回。并打印函数返回时的**堆栈地址**和**返回值及参数值**等信息。

-   ```until``` 或 ```u```

    当你厌倦了在一个循环体内单步跟踪时，这个命令可以运行程序直到**退出循环体**。

-   ```stepi``` 或 ```si```
    ```nexti``` 或 ```ni```

    单步跟踪一条机器指令！一条程序代码有可能由数条机器指令完成，stepi和nexti可以**单步执行机器指令**。与之一样有相同功能的命令是“display/i $pc” ，当运行完这个命令后，单步跟踪会在打出程序代码的同时打出机器指令（也就是**汇编代码**）

#### 3.4.9. 信号（Signals）

信号是一种**软中断**，是一种处理异步事件的方法。一般来说，操作系统都支持许多信号。尤其是UNIX，比较重要应用程序一般都会处理信号。UNIX定义了许多信号，比如SIGINT表示中断字符信号，也就是Ctrl+C的信号，SIGBUS表示硬件故障的信号；SIGCHLD表示子进程状态改变信号；SIGKILL表示终止程序运行的信号，等等。信号量编程是UNIX下非常重要的一种技术。

GDB有能力在你调试程序的时候处理任何一种信号，你可以告诉GDB需要处理哪一种信号。你可以要求GDB收到你所指定的信号时，马上停住正在运行的程序，以供你进行调试。你可以用GDB的handle命令来完成这一功能。
```shell
handle <signal> <keywords...>
```
在GDB中定义一个信号处理。信号\<signal>可以以SIG开头或不以SIG开头，可以用定义一个要处理信号的范围（如：SIGIO-SIGKILL，表示处理从SIGIO信号到SIGKILL的信号，其中包括SIGIO，SIGIOT，SIGKILL三个信号），也可以使用关键字all来标明要处理所有的信号。一旦被调试的程序接收到信号，运行程序马上会被GDB停住，以供调试。其\<keywords>可以是以下几种关键字的一个或多个。

-   ```nostop```

    当被调试的程序收到信号时，GDB不会停住程序的运行，但会打出消息告诉你收到这种信号。

-   ```stop```

    当被调试的程序收到信号时，GDB会停住你的程序。

-   ```print```

    当被调试的程序收到信号时，GDB会显示出一条信息。

-   ```noprint```

    当被调试的程序收到信号时，GDB不会告诉你收到信号的信息。

-   ```pass```
    ```noignore```

    当被调试的程序收到信号时，GDB不处理信号。这表示，GDB会把这个信号交给被调试程序会处理。

-   ```nopass```
    ```ignore```

    当被调试的程序收到信号时，GDB不会让被调试程序来处理这个信号。

-   ```info signals```
    ```info handle```

    查看有哪些信号在被GDB检测中。

#### 3.4.10. 线程（Thread Stops）

如果你程序是多线程的话，你可以定义你的断点是否在所有的线程上，或是在某个特定的线程。GDB很容易帮你完成这一工作。
```shell
break <linespec> thread <threadno>
break <linespec> thread <threadno> if ...
```
**linespec**指定了断点设置在的源程序的行号。**threadno**指定了线程的ID，注意，**这个ID是GDB分配的**，你可以通过“**info threads**”命令来查看正在运行程序中的线程信息。如果你不指定thread \<threadno>则表示你的断点设在所有线程上面。你还可以为某线程指定断点条件。如：
```shell
(gdb) break frik.c:13 thread 28 if bartab > lim
```
当你的程序被GDB停住时，所有的运行线程都会被停住。这方便你你查看运行程序的总体情况。而在你恢复程序运行时，所有的线程也会被恢复运行。那怕是主进程在被单步调试时。

### 3.5. 查看栈信息

当程序被停住了，你需要做的第一件事就是查看程序是在哪里停住的。当你的程序调用了一个函数，函数的地址，函数参数，函数内的局部变量都会被压入“栈”（Stack）中。你可以用GDB命令来查看当前的栈中的信息。

下面是一些查看函数调用栈信息的GDB命令：

```backtrace```
```bt```

打印当前的函数调用栈的所有信息。如：
```shell
(gdb) bt
#0  func (n=250) at tst.c:6
#1  0x08048524 in main (argc=1, argv=0xbffff674) at tst.c:30
#2  0x400409ed in __libc_start_main () from /lib/libc.so.6
```
从上可以看出函数的调用栈信息：__libc_start_main --> main() --> func()

```backtrace <n>``` ```bt <n>```

n是一个正整数，表示只打印栈顶上n层的栈信息。

```backtrace <-n>``` ```bt <-n>```

-n表一个负整数，表示只打印栈底下n层的栈信息。

如果你要查看某一层的信息，你需要在切换当前的栈，一般来说，程序停止时，最顶层的栈就是当前栈，如果你要查看栈下面层的详细信息，首先要做的是切换当前栈。

```frame <n>``` ```f <n>```

n是一个从0开始的整数，是栈中的层编号。比如：frame 0，表示栈顶，frame 1，表示栈的第二层。

```up <n>```

表示向栈的上面移动n层，可以不打n，表示向上移动一层。 

```down <n>```

表示向栈的下面移动n层，可以不打n，表示向下移动一层。

上面的命令，都会打印出移动到的栈层的信息。如果你不想让其打出信息。你可以使用这三个命令:

```select-frame <n>```对应于 frame 命令。

```up-silently <n>```对应于 up 命令。

```down-silently <n>```对应于 down 命令。

查看当前栈层的信息，你可以用以下GDB命令：

```frame``` 或 ```f```

会打印出这些信息：栈的层编号，当前的函数名，函数参数值，函数所在文件及行号，函数执行到的语句。

```info frame```
```info f```

这个命令会打印出更为详细的当前栈层的信息，只不过，大多数都是运行时的内内地址。比如：函数地址，调用函数的地址，被调用函数的地址，目前的函数是由什么样的程序语言写成的、函数参数地址及值、局部变量的地址等等。如：
```shell
(gdb) info f
Stack level 0, frame at 0xbffff5d4:
eip = 0x804845d in func (tst.c:6); saved eip 0x8048524
called by frame at 0xbffff60c
source language c.
Arglist at 0xbffff5d4, args: n=250
Locals at 0xbffff5d4, Previous frame's sp is 0x0
Saved registers:
ebp at 0xbffff5d4, eip at 0xbffff5d8
```

```info args```

打印出当前函数的参数名及其值。

```info locals```

打印出当前函数中所有局部变量及其值。

```info catch```

打印出当前的函数中的异常处理信息。

### 3.6. 查看源程序

#### 3.6.1. 显示源代码

GDB 可以打印出所调试程序的源代码，当然，在程序编译时一定要加上-g的参数，把源程序信息编译到执行文件中。不然就看不到源程序了。当程序停下来以后，GDB会报告程序停在了那个文件的第几行上。你可以用list命令来打印程序的源代码。还是来看一看查看源代码的GDB命令吧。

-   ```list <linenum>```

    显示程序第linenum行的周围的源程序。

-   ```list <function>```

    显示函数名为function的函数的源程序。

-   ```list```

    显示当前行后面的源程序。

-   ```list -```

    显示当前行前面的源程序。

一般是打印当前行的上5行和下5行，如果显示函数是是上2行下8行，默认是10行，当然，你也可以定制显示的范围，使用下面命令可以设置一次显示源程序的行数。

-   ```set listsize <count>```

    设置一次显示源代码的行数。

-   ```show listsize```

    查看当前listsize的设置。

list命令还有下面的用法：

-   ```list <first>, <last>```

    显示从first行到last行之间的源代码。

-   ```list , <last>```

    显示从当前行到last行之间的源代码。

-   ```list +```

    往后显示源代码。

一般来说在list后面可以跟以下这们的参数：

```shell
<linenum>               行号。
<+offset>               当前行号的正偏移量。
<-offset>               当前行号的负偏移量。
<filename:linenum>      哪个文件的哪一行。
<function>              函数名。
<filename:function>     哪个文件中的哪个函数。
<*address>              程序运行时的语句在内存中的地址。
```

#### 3.6.2. 搜索源代码

不仅如此，GDB还提供了源代码搜索的命令：

```forward-search <regexp>```
```search <regexp>```

向前面搜索。

``reverse-search <regexp> ``

全部搜索。

其中，\<regexp>就是正则表达式，也主一个字符串的匹配模式，关于正则表达式，我就不在这里讲了，还请各位查看相关资料。

#### 3.6.3. 指定源文件的路径

某些时候，用-g编译过后的执行程序中只是包括了源文件的名字，没有路径名。GDB提供了可以让你指定源文件的路径的命令，以便GDB进行搜索。

```directory <dirname ... > ```
```dir <dirname ... > ```

加一个源文件路径到当前路径的前面。如果你要指定多个路径，UNIX下你可以使用“:”，Windows下你可以使用“;”。

```directory```

清除所有的自定义的源文件搜索路径信息。

```show directories```

显示定义了的源文件搜索路径。

#### 3.6.4. 源代码的内存

你可以使用info line命令来查看源代码在内存中的地址。info line后面可以跟“行号”，“函数名”，“文件名:行号”，“文件名:函数名”，这个命令会打印出所指定的源码在运行时的内存地址，如：
```shell
(gdb) info line gdb_00001_tst.c:func
Line 4 of "gdb_00001_tst.c" starts at address 0x4004c4 <func> and ends at 0x4004cb <func+7>.
```
还有一个命令（disassemble）你可以查看源程序的当前执行时的机器码，这个命令会把目前内存中的指令dump出来。如下面的示例表示查看函数func的汇编代码。
```shell
(gdb) disassemble func
Dump of assembler code for function func:
0x00000000004004c4 <+0>:	push   %rbp
0x00000000004004c5 <+1>:	mov    %rsp,%rbp
0x00000000004004c8 <+4>:	mov    %edi,-0x14(%rbp)
0x00000000004004cb <+7>:	movl   $0x0,-0x8(%rbp)
0x00000000004004d2 <+14>:	movl   $0x0,-0x4(%rbp)
0x00000000004004d9 <+21>:	jmp    0x4004e5 <func+33>
0x00000000004004db <+23>:	mov    -0x4(%rbp),%eax
0x00000000004004de <+26>:	add    %eax,-0x8(%rbp)
0x00000000004004e1 <+29>:	addl   $0x1,-0x4(%rbp)
0x00000000004004e5 <+33>:	mov    -0x4(%rbp),%eax
0x00000000004004e8 <+36>:	cmp    -0x14(%rbp),%eax
0x00000000004004eb <+39>:	jl     0x4004db <func+23>
0x00000000004004ed <+41>:	mov    -0x8(%rbp),%eax
0x00000000004004f0 <+44>:	leaveq 
0x00000000004004f1 <+45>:	retq   
End of assembler dump.
```

### 3.7. 查看运行时数据

在你调试程序时，当程序被停住时，你可以使用print命令（简写命令为p），或是同义命令inspect来查看当前程序的运行数据。print命令的格式是：

```print <expr>```
```print /<f> <expr>```

\<expr>是表达式，是你所调试的程序的语言的表达式（GDB可以调试多种编程语言），\<f>是输出的格式，比如，如果要把表达式按16进制的格式输出，那么就是/x。

#### 3.7.1. 表达式

print和许多GDB的命令一样，可以接受一个表达式，GDB会根据当前的程序运行的数据来计算这个表达式，既然是表达式，那么就可以是当前程序运行中的const常量、变量、函数等内容。可惜的是GDB不能使用你在程序中所定义的宏。

表达式的语法应该是当前所调试的语言的语法，由于C/C++是一种大众型的语言，所以，本文中的例子都是关于C/C++的。（而关于用GDB调试其它语言的章节，我将在后面介绍）

在表达式中，有几种GDB所支持的操作符，它们可以用在任何一种语言中。

`@`

是一个和数组有关的操作符，在后面会有更详细的说明。

`::`

指定一个在文件或是一个函数中的变量。

`{<type>} <addr>`

表示一个指向内存地址\<addr>的类型为type的一个对象。

#### 3.7.2. 程序变量

在GDB中，你可以随时查看以下三种变量的值：

1.  全局变量（所有文件可见的）
2.  静态全局变量（当前文件可见的）
3.  局部变量（当前Scope可见的）

如果你的局部变量和全局变量发生冲突（也就是重名），一般情况下是局部变量会隐藏全局变量，也就是说，如果一个全局变量和一个函数中的局部变量同名时，如果当前停止点在函数中，用print显示出的变量的值会是函数中的局部变量的值。如果此时你想查看全局变量的值时，你可以使用“::”操作符：

`file::variable`
`function::variable`

可以通过这种形式指定你所想查看的变量，是哪个文件中的或是哪个函数中的。例如，查看文件f2.c中的全局变量x的值：
```shell
(gdb) p 'f2.c'::x
```

当然，“::”操作符会和C++中的发生冲突，GDB能自动识别“::” 是否C++的操作符，所以你不必担心在调试C++程序时会出现异常。

另外，需要注意的是，如果你的程序编译时开启了优化选项，那么在用GDB调试被优化过的程序时，可能会发生某些变量不能访问，或是取值错误码的情况。这个是很正常的，因为优化程序会删改你的程序，整理你程序的语句顺序，剔除一些无意义的变量等，所以在GDB调试这种程序时，运行时的指令和你所编写指令就有不一样，也就会出现你所想象不到的结果。对付这种情况时，需要在编译程序时关闭编译优化。一般来说，几乎所有的编译器都支持编译优化的开关，例如，GNU的C/C++编译器GCC，你可以使用“-gstabs”选项来解决这个问题。关于编译器的参数，还请查看编译器的使用说明文档。