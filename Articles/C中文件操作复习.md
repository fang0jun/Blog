

- [fopen()](#fopen)
- [fputc() 和 fgetc()](#fputc-和-fgetc)
- [fgets()](#fgets)
- [fputs()](#fputs)
- [fread()和fwrite()](#fread和fwrite)
- [读写函数的区别](#读写函数的区别)
- [详解EOF](#详解eof)

|| FILE 是系统定义的一个类型，其中包含由文件的各种信息，如文件名，文件地址
|| 我们一般使用FILE *fp —— 一个文件指针来操作文件


## fopen()
|| fopen()：用来以指定的方式打开文件，其原型为：
   
```c
 FILE * fopen(const char * path, const char * mode); 
```
打开成功时返回类型为文件指针,若打开失败则返回空指针NULL
第一个参数为文件路径： `fp = fopen(./123.txt, "w")`
第二个参数mode为打开方式，有以下几种方式：
|打开方式|	说明|
|--|--|
|r	|以只读方式打开文件，该文件必须存在。
|r+|	以读/写方式打开文件，该文件必须存在。
|rb+	|以读/写方式打开一个二进制文件，只允许读/写数据。
|rt+	|以读/写方式打开一个文本文件，允许读和写。
|w|	打开只写文件，若文件存在则长度清为0，即该文件内容消失，若不存在则创建该文件。
|w+|	打开可读/写文件，若文件存在则文件长度清为零，即该文件内容会消失。若文件不存在则建立该文件。
|a	|以附加的方式打开只写文件。若文件不存在，则会建立该文件，如果文件存在，写入的数据会被加到文件尾，即文件原先的内容会被保留（EOF符保留)。
|a+|	以附加方式打开可读/写的文件。若文件不存在，则会建立该文件，如果文件存在，则写入的数据会被加到文件尾后，即文件原先的内容会被保留（原来的EOF符 不保留)。
|wb|	以只写方式打开或新建一个二进制文件，只允许写数据。
|wb+|	以读/写方式打开或建立一个二进制文件，允许读和写。
|wt+|	以读/写方式打开或建立一个文本文件，允许读写。
|at+|	以读/写方式打开一个文本文件，允许读或在文本末追加数据。
|ab+|	以读/写方式打开一个二进制文件，允许读或在文件末追加数据。

---
## fputc() 和 fgetc()

|| **fgetc()**: fgetc 是 file get char 的缩写，意思是**从指定的文件中读取一个字符到缓存区**。
经常配合使用 putchar(ch) -- 从缓存区输出一个字符到屏幕上
>它的语法为：`int fgetc (FILE *fp);`


读取成功时返回读取到的字符，读取到文件末尾或读取失败时返回EOF（EOF 是 end of file 的缩写，表示文件末尾，它的值是一个负数，往往是 -1(反正不能是char(char为正数) ) ）

<br/>

【示例】在屏幕上显示 D:\\demo.txt 文件的内容。

```c
#include<stdio.h>
int main(){
    FILE *fp;
    char ch;
  
    //如果文件不存在，给出提示并退出
    if( (fp=fopen("D:\\demo.txt","rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }

    //每次读取一个字节，直到读取完毕
    while( (ch=fgetc(fp)) != EOF ){
        putchar(ch);
    }
    putchar('\n');  //输出换行符

    if(ferror(fp)){
        puts("读取出错");
    }else{
        puts("读取成功");
    }

    fclose(fp);
    return 0;
}
```


<br/>

|| **fputc()**: fputtc 是 file output char 的缩写，意思是 **从缓存区读取一个字符到指定的文件中** 。
经常配合使用getchar()  **从键盘中读取一个字符到缓存区**
>它的语法为：`int fputc ( int ch, FILE *fp );`


【示例】从键盘输入一行字符，写入文件。

```c
#include<stdio.h>
int main(){
    FILE *fp;
    char ch;

    //判断文件是否成功打开
    if( (fp=fopen("D:\\demo.txt","wt+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }

    printf("Input a string:\n");
    //每次从键盘读取一个字符并写入文件
    while ( (ch=getchar()) != '\n' ){
        fputc(ch,fp);
    }
    fclose(fp);
    return 0;
}
```


>==   fgetc() / fputc()默认包含移动一个位置指针的功能==
>在文件内部有一个位置指针，用来指向当前读写到的位置，也就是读写到第几个字节。在文件打开时，该指针总是指向文件的第一个字节。使用 fgetc() 函数后，该指针会向后移动一个字节，所以可以连续多次使用 fgetc() 读取多个字符。





<br/>

## fgets()
|| 读字符串函数 fgets()
fgets() 函数用来从指定的文件中读取一个字符串，并保存到字符数组中（至缓存区），它的语法为：
>它的语法为：`char *fgets ( char *str, int n, FILE *fp );  // str 为字符数组，n 为要读取的字符数目，fp 为文件指针。`


tip_1：读取到的字符串会在末尾自动添加 '\0'，n 个字符也包括 '\0'。
*也就是说*：实际只读取到了 n-1 个字符，如果希望读取 100 个字符，n 的值应该为 101。
tip_2：需要重点说明的是，在读取到 n-1 个字符之前如果出现了**换行'\n'**，或者读到了**文件末尾**，则读取结束。
*也就是说*：不管 n 的值多大，fgets() 最多只能读取一行数据，不能跨行。在C语言中，没有按行读取文件的函数，我们可以借助 fgets()，将 n 的值设置地足够大，每次就可以读取到一行数据。

<br/>

【示例】一行一行地读取文件。

```c
#include <stdio.h>
#include <stdlib.h>
#define N 100
int main(){
    FILE *fp;
    char str[N+1];
    if( (fp=fopen("d:\\demo.txt","rt")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
   
    while(fgets(str, N, fp) != NULL){
        printf("%s", str);
    }

    fclose(fp);
    return 0;
}
```


<br/>
<br/>

## fputs()
fputs() 函数用来向指定的文件写入一个字符串，（至缓存区），它的用法为：

```c
int fputs( char *str, FILE *fp );
```
【示例】向上例中建立的 d:\\demo.txt 文件中追加一个字符串。
```c
#include<stdio.h>
int main(){
    FILE *fp;
    char str[102] = {0}, strTemp[100];
    if( (fp=fopen("D:\\demo.txt", "at+")) == NULL ){
        puts("Fail to open file!");
        exit(0);
    }
    printf("Input a string:");
    gets(strTemp);
    strcat(str, "\n");
    strcat(str, strTemp);
    fputs(str, fp);
    fclose(fp);
    return 0;
}
```







## fread()和fwrite()
对于 Windows 系统，使用 fread() 和 fwrite() 时应该以二进制的形式打开文件。附[《文本文件和二进制文件的差异和区别》](https://blog.csdn.net/a13352912632/article/details/108743530)

fread() 函数用来从指定文件中读取块数据。所谓块数据，也就是若干个字节的数据，可以是一个字符，可以是一个字符串，可以是多行数据，并没有什么限制（无限制的fgetc()/fgets() ）。fread() 的原型为：

```c
size_t fread ( void *ptr, size_t size, size_t count, FILE *fp );
```

fwrite() 函数用来向文件中写入块数据，它的原型为：

```c
size_t fwrite ( void * ptr, size_t size, size_t count, FILE *fp );
```

|| 对参数的说明：
>- ptr 为内存区块的指针，它可以是数组、变量、结构体等。fread() 中的 ptr 用来存放读取到的数据，fwrite() 中的  ptr 用来存放要写入的数据。
>- size：表示每个数据块的字节数。
>- count：表示要读写的数据块的块数。
>- fp：表示文件指针。
理论上，每次读写 size*count 个字节的数据。

size_t 是在 stdio.h 和 stdlib.h 头文件中使用 typedef 定义的数据类型，表示无符号整数，也即非负数，常用来表示数量。

|| 返回值：返回成功读写的块数，也即 count。如果返回值小于 count：
- 对于 fwrite() 来说，肯定发生了写入错误，可以用 ferror() 函数检测。
- 对于 fread() 来说，可能读到了文件末尾，可能发生了错误，可以用 ferror() 或 feof() 检测。

<br/>

【示例】从键盘输入一个数组，将数组写入文件再读取出来。

```c
#include<stdio.h>
#define N 5
int main(){
    //从键盘输入的数据放入a，从文件读取的数据放入b
    int a[N], b[N];
    int i, size = sizeof(int);
    FILE *fp;
    if( (fp=fopen("D:\\demo.txt", "rb+")) == NULL ){  //以二进制方式打开
        puts("Fail to open file!");
        exit(0);
    }
  
    //从键盘输入数据 并保存到数组a
    for(i=0; i<N; i++){
        scanf("%d", &a[i]);
    }
    //将数组a的内容写入到文件
    fwrite(a, size, N, fp);
    //将文件中的位置指针重新定位到文件开头
    rewind(fp);
    //从文件读取内容并保存到数组b
    fread(b, size, N, fp);
    //在屏幕上显示数组b的内容
    for(i=0; i<N; i++){
        printf("%d ", b[i]);
    }
    printf("\n");
    fclose(fp);
    return 0;
}
```

<br/>
<br/>

## 读写函数的区别

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200922213531829.png#pic_center)

<br/><br/>

## 详解EOF
|| EOF 本来表示文件末尾，意味着文件*读取* 结束，但是很多函数在读取出错时也返回 EOF，那么当返回 EOF 时，到底是文件读取完毕了还是读取出错了？我们可以借助 stdio.h 中的两个函数来判断，分别是 feof() 和 ferror()。

|| feof() 函数用来判断文件内部指针是否指向了文件末尾，它的原型是：`int feof ( FILE * fp );`
当指向文件末尾时返回非零值，否则返回零值。

|| ferror() 函数用来判断文件操作是否出错，它的原型是：`int ferror ( FILE *fp );`
出错时返回非零值，否则返回零值。

tip：需要说明的是，文件出错是非常少见的情况，上面的示例基本能够保证将文件内的数据读取完毕。如果追求完美，也可以加上判断并给出提示：
```c
if(ferror(fp)){ puts("读取出错");}
else{ puts("读取成功"); }
fclose(fp);
```

>注意：怎么记忆什么函数返回NULL还是EOF？ 函数原型中返回类型若是char 则失败返回EOF, 若返回类型是char* 则返回空指针NULL
- [fopen()](#fopen)
- [fputc() 和 fgetc()](#fputc-和-fgetc)
- [fgets()](#fgets)
- [fputs()](#fputs)
- [fread()和fwrite()](#fread和fwrite)
- [读写函数的区别](#读写函数的区别)
- [详解EOF](#详解eof)