**目录**
---

<!-- TOC -->

- [LINUX相关](#linux相关)
    - [1. Linux相关命令操作](#1-linux相关命令操作)
        - [1.1. 压缩与解压缩](#11-压缩与解压缩)
        - [1.2. 时间服务器上的时间同步](#12-时间服务器上的时间同步)
    - [2. Git相关命令操作](#2-git相关命令操作)
        - [2.1. 修改默认提交编译器](#21-修改默认提交编译器)
        - [2.2. 如何提交一个空目录](#22-如何提交一个空目录)
        - [2.3. 如何修改提交的错误作者信息](#23-如何修改提交的错误作者信息)

<!-- /TOC -->

# LINUX相关

## 1. Linux相关命令操作

### 1.1. 压缩与解压缩

- 压缩
    - [ ]  tar  -cvf    jpg.tar     *.jpg   //将目录里所有jpg文件打包成tar.jpg 
    - [x]  tar  -czf    jpg.tar.gz  *.jpg   //将目录里所有jpg文件打包成jpg.tar后，并且将其用gzip压缩，生成一个gzip压缩过的包，命名为jpg.tar.gz
    - [x]  tar  -cjf    jpg.tar.bz2 *.jpg   //将目录里所有jpg文件打包成jpg.tar后，并且将其用bzip2压缩，生成一个bzip2压缩过的包，命名为jpg.tar.bz2
    - [ ]  tar  -cZf    jpg.tar.Z   *.jpg   //将目录里所有jpg文件打包成jpg.tar后，并且将其用compress压缩，生成一个umcompress压缩过的包，命名为jpg.tar.Z
    - [ ]  rar  a       jpg.rar     *.jpg   //rar格式的压缩，需要先下载rar for linux
    - [x]  zip          jpg.zip     *.jpg   //zip格式的压缩，需要先下载zip for linux
    
- 解压缩
    - [ ]  tar  -xvf    file.tar        //解压tar
    - [x]  tar  -xzvf   file.tar.gz     //解压tar.gz
    - [x]  tar  -xjvf   file.tar.bz2    //解压tar.bz2
    - [ ]  tar  -xZvf   file.tar.Z      //解压tar.Z
    - [ ]  unrar    e   file.rar        //解压rar
    - [x]  unzip        file.zip        //解压zip

### 1.2. 时间服务器上的时间同步

1.  安装ntpdate工具
```shell
    yum -y install ntp ntpdate
```
2.  设置系统时间与网络时间同步
```shell
    ntpdate cn.pool.ntp.org
```
3.  将系统时间写入硬件时间
```shell
    hwclock --systohc
```

## 2. Git相关命令操作

### 2.1. 修改默认提交编译器

```shell
    git config --global core.editor vim
```

### 2.2. 如何提交一个空目录

```shell
    find . -type d -empty -exec touch {}/.gitignore \;
```

### 2.3. 如何修改提交的错误作者信息

```shell
    git filter-branch -f --env-filter \
    "GIT_AUTHOR_NAME='Newname'; GIT_AUTHOR_EMAIL='newemail'; \
    GIT_COMMITTER_NAME='committed-name'; GIT_COMMITTER_EMAIL='committed-email';" HEAD
```
```shell
    git push origin --force --all
```