
# open() and close()

|| 函数概述

-  fopen() 是 C 标准库中的**函数**，而 open() 是 Linux 中的**系统调用**函数
- 头文件：#include <sys/types.h>    #include <sys/stat.h>    #include <fcntl.h >#include <unistd.h>
- 定义函数
   - int open(const char *pathname, int flags);
    - int open(const char *pathname, int flags, mode_t mode);

>如果未创建文件，则open（）调用**返回-1**；如果成功创建，则返回数字> = 0，即**文件描述符**。(fopen返回的是一个文件指针)

<br/>

|| 参数相关
- 第一个参数路径
- 第二个参数是打开方式：指令如下

	|指令| 说明 |
	|--|--|
	|O_RDONLY（r）| 以只读方式打开文件
	|O_WRONLY（w）| 以只写方式打开文件
	|O_RDWR （r+）| 以可读写方式打开文件. 上述三种旗标是互斥的, 也就是不可同时使用, 但可与下列的旗标利用OR(|)运算符组合.
	|----------|---------------------------------------------------------------|
	|O_APPEND（a）| 当读写文件时会从文件尾开始移动, 也就是所写入的数据会以附加的方式加入到文件后面.
	|O_CREAT| 若欲打开的文件**不存在**则自动建立该文件.
	|O_EXCL| 如果O_CREAT 也被设置, 此指令会去**检查文件是否存在**. 文件若不存在则建立该文件, 否则将导致打开文件错误. 此外, 若O_CREAT 与O_EXCL 同时设置, 并且欲打开的文件为符号连接, 则会打开文件失败.
	|O_TRUNC| 若文件**存在**并且以可写的方式打开时, 此旗标会令文件长度清为0, 而原来存于该文件的资料也会消失.

	>tip:以上前三种flagO_RDONLY,O_WRONLY, RDWR是互斥的，但可以搭配OR(|)与下面flag一起使用

<br/>

-  第三个参数mode权限设置：
**该参数只有在建立新文件时才会生效，即当flag为O_CREAT时使用mode设置**

	| 指令 | 说明 |
	|--|--|
	|S_IRWXU00700 权限| 代表该文件所有者具有可读、可写及可执行的权限.
	|S_IRUSR 或S_IREAD00400 权限| 代表该文件所有者具有可读取的权限.
	|S_IWUSR 或S_IWRITE, 00200 权限|代表该文件所有者具有可写入的权限.
	|S_IXUSR 或S_IEXEC, 00100 权限| 代表该文件所有者具有可执行的权限.
	|S_IRWXG 00070 权限|代表该文件用户组具有可读、可写及可执行的权限.
	|S_IRGRP 00040 权限| 代表该文件用户组具有可读的权限.
	|S_IWGRP 00020 权限| 代表该文件用户组具有可写入的权限.
	|S_IXGRP 00010 权限| 代表该文件用户组具有可执行的权限.
	|S_IRWXO 00007 权限| 代表其他用户具有可读、可写及可执行的权限.
	|S_IROTH 00004 权限| 代表其他用户具有可读的权限
	|S_IWOTH 00002 权限| 代表其他用户具有可写入的权限.
	|S_IXOTH 00001 权限| 代表其他用户具有可执行的权限.


<br/>

 **creat()**
此外，还有一个单独的**int creat**（char *名称，int perms）系统调用专门用于创建文件。 它的用法等效于使用O_WRONLY |调用open（）。 O_CREAT | O_TRUNC。

<br/>

**close()**
int close（int fd）; 关闭描述符编号为fd的文件。 成功返回0，如果发生错误则返回-1。
完成使用文件的操作后，必须关闭文件。

---------

<br/><br/>

# read() and write()
|| 函数概述


- 从文件描述符号为fd的文件读取到大小为len的buf指向的存储区中（联系fread()）
```c
int read（int fd，char * buf，int len）； 
```

- 从大小为len的存储区buf写入文件描述符编号为fd的文件
```c
int write（int fd，const char * buf，int len）; 
```



>read（）和write（）在出错时**返回-1**，在成功时**返回传输的字节数**。

-------
<br/>



# 实操:代码示例

## 1 将in.txt文件中的内容写入到out.txt文件中（一个一个字符写入）
```c
#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/types.h>

void error(char *str, char *filename){
        printf(str, filename); exit(-1);
}

int main(){
        int f1, f2,n;
        char buf, file1[] = "in.txt", file2[] = "out.txt";
        if((f1 = open(file1, O_RDONLY)) == -1 ) error("Error open file %s" ,file1);
        if((f2 = open(file2, O_CREAT|O_WRONLY|O_TRUNC)) == -1) error("Error open file %s" ,file2);
        while ((n = read(f1, &buf, 1)) > 0) // 调用read，一个一个字符读
                if(write(f2, &buf, n) != n)  error("error write in file %s", file2);
        if(n < 0) error("error read from file %s", file1);
        close(f1); close(f2);
       
        return 0;

}
```

## 2 将in.txt文件中的内容写入到out.txt文件中（数组写入）

```c
#include <stdio.h>
#include<stdlib.h> 
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#define bsize 10
 void error(char * str, char*filename)
{	printf(str,filename); exit(-1); }
 int main(void)
 { int f1,f2,n;  char buf[bsize], file1[]="in.txt",file2[]="out.txt"; 
	if ((f1 = open(file1, O_RDONLY)) == -1) 
		error("Error open file %s", file1); 
	if ((f2 = open(file2, O_CREAT|O_WRONLY|O_TRUNC,0644)) == -1)          
       error("Error open file %s", file2); 
	while ((n = read(f1, buf, bsize)) > 0) 
		if (write(f2, buf, n ) != n) 
	       error("error write in file %s",file2);
	if (n<0) error("error read from file %s",file1);
		close( f1); close(f2); 
return 0; 
}
```