
- [一.【什么是】KMP](#一什么是kmp)
- [二.【为什么】可以移位？](#二为什么可以移位)
  - [1.从公式推导来说](#1从公式推导来说)
  - [2.从直观来说](#2从直观来说)
- [三.【怎么实现】](#三怎么实现)
  - [3.对移位规则的实现：Next[]](#3对移位规则的实现next)
  - [4.【一句话总结】实现KMP的算法流程：判异同 和 移位找前缀](#4一句话总结实现kmp的算法流程判异同-和-移位找前缀)
    - [<font color=red>1.KMP实现：  Si,Tj位判异同，相等时S,T同进位，相异时T移位进行前缀匹配，看能否最终匹配全部字符串](#font-colorred1kmp实现-sitj位判异同相等时st同进位相异时t移位进行前缀匹配看能否最终匹配全部字符串)
    - [<font color=red>2.构建Next[]：找Next[j+1]，就是Tj,Tk判异同，看能否扩充T[1, j]任一子前缀 (移位找子前缀)](#font-colorred2构建next找nextj1就是tjtk判异同看能否扩充t1-j任一子前缀-移位找子前缀)
  - [5.具体代码实现和解释](#5具体代码实现和解释)
  - [附：修正后的Next代码](#附修正后的next代码)


# 一.【什么是】KMP
**KMP是利用公共前后缀进行移位匹配的匹配算法。在失配时固定主串指针i (i无需回溯)，依据Next[]将模式串向后移动与匹配指针对齐**

对比朴素暴力匹配法O(nm)，KPM匹配更高效O(n+m)




实现过程：
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200928145916596.gif#pic_center)
<br><br>

-------
# 二.【为什么】可以移位？


## 1.从公式推导来说


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200928134405124.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70#pic_center)
<br><br>

## 2.从直观来说

>为了方便叙述，声明了几个名词
>把模板T在指针j之前字符构成的子串，姑且先称之为“已配对模式子串”，把已配对模式子串的开头前k-1项，和j前k-1项，称为模板j前子串的“前缀”和“后缀”

已知主串Si的前x项已经和“已配对模式子串”完全相等, 在第i项时Tj与Si相异, 现在考虑移位问题。

既然i前面部分已完全相等，Si的前x项中每个位置都已经和“已配对模板子串”的对应位置一一对应了(此时“已配对模板子串”的“前后缀”，也是Si前的前x项的前后缀 ），如果一个一个移位的话大多情况下都是在“已配对模式子串”开头部分就已经无法对应，但是有一种特殊情况除外  --- 当“前缀”等于“后缀” 时，将“已配对模式子串”的“前缀” 直接 移到主串S的“后缀”对应位置，以此达到了快速移位，减少无意义匹配的目的

==综上所述：移位的k只与模式T自身相关（与模式T的公共前后缀相关）==

<br><br>

-------

# 三.【怎么实现】

## 3.对移位规则的实现：Next[]

<font color = red>**模式T的移位是为了前后缀匹配**

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200928142331942.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70#pic_center)

<br><br>

-------

## 4.【一句话总结】实现KMP的算法流程：判异同 和 移位找前缀

就干两件事情：**判异同** 和 **移位找前缀** 

因为构建Next数组本质上也是使用KPM匹配(主串和模式都为原模式T)，所以为了更普适Next的实现，调整了一下KPM和Next数组的实现流程图

### <font color=red>1.KMP实现：  Si,Tj位判异同，相等时S,T同进位，相异时T移位进行前缀匹配，看能否最终匹配全部字符串
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200928145224852.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70#pic_center)

### <font color=red>2.构建Next[]：找Next[j+1]，就是Tj,Tk判异同，看能否扩充T[1, j]任一子前缀 (移位找子前缀)

找Next[j+1]，就是Tj，Tk判异同，相等时返回原前缀长+1（等效于扩充了前缀），相异时移位往前找T[1, j]所有子前缀，最终获得每个j上的Next[j]值
tip:扩充前缀（即前缀后一位Tk与Tj相等）

![在这里插入图片描述](https://img-blog.csdnimg.cn/20200928145231785.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70#pic_center)


<br><br>

-------

## 5.具体代码实现和解释
```cpp
#include<bits/stdc++.h>
using namespace std;

void get_next(string T, int next[]){  // T中T[0]储存的是T的字符串长度
        int i = 1, j = 0; // i为T中指针，j为next数组下标
        Next[1] = 0;

        while(i < T[0]){ // j即保存了Ti配位的位置，也通过 j-1 保存了最大公共子串的字符数
                if(j == 0 || T[i] == T[j]) {i++;j++;Next[i] = j;}
                else j = Next[j];
        }



}


int KMP(string S, string T, int pos){ // T中T[0]储存的是T的字符串长度
        int i = pos; int j = 1;
        while(i <= S.length && j <= S.length){
                if(j==0 || T[j] == S[i]) {++i; ++j;}
                else j = next[j];
        }
        if(j > T[0]) return i - T[0];
        else return 0;

}

int main(){



        return 0;
}

```

## 附：修正后的Next代码
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200928160840666.png?#pic_center)

```cpp
#include<bits/stdc++.h>
using namespace std;

int* getNext2(int Next[], string T){
	int j = 0; Next[1] = 0;
	int i = 1;
	while(i < string.length()){
		if(j = 0 || T[i] == T[j]) {
			j++; i++;
			if(T[i] != T[j]) Next[i] = j;
			else  next[i] = next[j]; // 等于前一位
		}
		else j = Next[j];
		
	} 
	
}
```
