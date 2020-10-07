
- [一，struct结构](#一struct结构)
  - [1. 有关struct的声明](#1-有关struct的声明)
    - [1.1 结构模板名](#11-结构模板名)
    - [1.2 创建结构变量](#12-创建结构变量)
    - [1.3 与typedef的配合](#13-与typedef的配合)
  - [2. 有关struct的初始化](#2-有关struct的初始化)
- [二，union联合](#二union联合)
- [三，enum枚举](#三enum枚举)
  - [3.1 enum的语法](#31-enum的语法)
  - [3.2 enum中枚举符的赋值](#32-enum中枚举符的赋值)

--------
# 一，struct结构
<br>

## 1. 有关struct的声明
### 1.1 结构模板名
```c
struct { // 结构的模板（勾勒一个结构）
	int num;
	char arr[10];
}; 
```


```c
struct book{ // book为结构模板的名称 --- 模板名
	int num;
	char arr[10];
}
```
==结构的模板名可写可不写，一般在以下情况中会写出模板名：需要重复使用该结构本身时==

-----
### 1.2 创建结构变量
```c
struct book{ 
	int num;
	char arr[10];
};

struct book library;

/*  等价于： */

struct book{ 
	int num;
	char arr[10];
} library;

/*  也等价于： */

struct{ int num;char arr[10];}  library; // 如果无创建多个声明名的需要
```

==`struct{ } ` 可以直接用作 一个类型 去使用==

----
<br><br>

### 1.3 与typedef的配合

```c
typedef struct book{  
	int num;
	char arr[10];
} LIBRARY;

typedef struct { //声明名不重要
	int num;
	char arr[10];
} LIBRARY;

```
==注意：此时花括号之后是typedef定义的struct别名，是一个类型名。区别`struct{ } xxx;` xxx为变量名==

------

## 2. 有关struct的初始化

按顺序初始化
```c
struct book library = {1, "《深入理解计算机系统》"};
```
指定成员初始化
```c
struct book library = {
	.num = 1,
	.arr = "《深入理解计算机系统》"
};
```
-----
<br><br>

-------

# 二，union联合

**union是多选一版的struct** 。struct 的变量将能同时包含有多个数据类型，union 的变量一次只能代表其中一种数据类型

union类型，可以代表联合结构中声明的各种类型中的唯一一个类型
union变量，可以存放联合结构中声明的各种类型中的唯一一个类型的变量（使用时，union变量必须调用其中某种类型的成员，union变量自身所属的类型将与该调用成员的数据类型一致）

union的内存为联合声明中占用字节最大的类型的大小

```c
union chooseOne{
	int Int;
	char Char;
};

union chooseOne Tom;
Tom.Int = 1;  // 相当于: int Tom = 1; 此时整个Tom联合结构中只有一个 1 
Tom,Int += 2; // 相当于int
Tom.Char = 'A' // 相当于: char Tom = 'A'; 此时整个Tom联合结构中只有一个 ‘A’，原先的1被删除
```

```c
struct ownerPeople{
	char peopleName[20];
	int age;
}
struct ownerCompany{
	char companyName[20];
	char leader[20];
}
union data{
		struct ownerPeople peopleInfo;
		struct ownerCompany companyInfo;
	};
	
struct carData{
	char carName[20]
	union data ownerInfo;
};

```
 也可写成匿名联合， 此时调用为 (carData benci):  `benci.peopleInof;` 而不再是`benci.ownerInfo.peopleInfo;` （union变量名略过直接使用struct结构名调用）

```c
struct carData{
	char carName[20]
	union {
		struct ownerPeople peopleInfo;
		struct ownerCompany companyInfo;
	};
};
```


-----
<br><br>

# 三，enum枚举
## 3.1 enum的语法
**限定取值的整型数据类型, 且利用枚举符来表示整型数据**（更具有好的可读性）
枚举符本质上就是整型变量，类似于`#define 枚举符 赋予的值`
```c
enum somecolor{red, orange, green}; // red/orange/green为枚举符
enum somecolor color;
```
## 3.2 enum中枚举符的赋值

```c
enum somecolor{red, orange, green}; // 默认赋值  此时{red=0, orange=1, green=3}; 从（0/前一位赋值）+ 1开始
enum somecolor{red, orange = 20, green}; // 特殊默认赋值  此时{red = 0, orange = 20, green = 21};
enum somecolor{red = 1, orange = 2, green = 3}; //分别赋值
```

<br>

==typedef 和 #define 的区别 与 union 和 enum的区别类似 （一个针对类型，一个针对值）==


