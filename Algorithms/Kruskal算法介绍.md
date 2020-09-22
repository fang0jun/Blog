[1.Kruskal算法介绍](1.Kruskal算法介绍)

[2.模板实现](2.模板实现)

[3.例题](3.例题)

<br/>

# 1.Kruskal算法介绍
克鲁斯卡尔算法可以称为“加边法”，初始最小生成树边数为0，每迭代一次就选择一条满足条件的最小代价边，加入到最小生成树的边集合里。 
1. 把图中的所有边按代价从小到大排序； 
2. 把图中的n个顶点看成独立的n棵树组成的森林； 
3. 按权值从小到大选择边，所选的边连接的两个顶点ui,viui,vi,应属于两颗不同的树，则成为最小生成树的一条边，并将这两颗树合并作为一颗树。 
4. 重复(3),直到所有顶点都在一颗树内或者有n-1条边为止。
![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914103548705.png?#pic_center)

**总结：==从小开始加，确保无回路(树)==**


<br/>
<br/>
|| 区别普利姆最小生成树算法：普利姆算法从顶点的角度为出发点。时间复杂度为O(n^2)。**更适合于稠密度更高的连通网**。
而克鲁斯卡尔算法从边的角度求最小生成树，时间复杂度为O(eloge)，**更适合于稠密度更高的连通网**。

<br/>
|| 判断是否会产生回路的方法为：
在初始状态下给每个顶点赋予不同的标记，对于遍历过程的每条边，其都有两个顶点，判断这两个顶点的标记是否一致，如果一致，说明它们本身就处在一棵树中，如果继续连接就会产生回路；如果不一致，说明它们之间还没有任何关系，可以连接。

<br/>
<br/>

# 2.模板实现
```cpp
//最小生成树（Kruskal算法）
#include<iostream>
#include<algorithm>
using namespace std;

struct point{
    int x;
    int y;
    int v;
}; //写结构体用来构造边 
point a[10000];//存边
 
int cmp(const point &a,const point &b){
    if(a.v<b.v) return 1;
    else return 0;
}//快排要用到的比较函数 ，从小到大
 
int fat[101];
int father(int x){
    if(fat[x]!=x) return fat[x]=father(fat[x]);
    else return fat[x];
}//找出一个点属于哪个集合（找这个点的爹） 

void unionn(int x,int y){
    int fa=father(x);
    int fb=father(y);
    if(fa!=fb) fat[fa]=fb;
}//将被边连接的两个独立集合合并 

int main(){
    int i,j,n,m,k=0,ans=0,cnt=0;
    cin>>n;
    for(i=1;i<=n;i++)
    for(j=1;j<=n;j++)
    {
        cin>>m;
        if(m!=0){
            k++;
            a[k].x=i;
            a[k].y=j;
            a[k].v=m;
        }
    }//输入，存边 
    sort(a+1,a+1+k,cmp);//快排所有边 
    
    for(i=1;i<=n;i++){
        fat[i]=i;
    }//初始化，将每个点看做独立集合 
    
    for(i=1;i<=k;i++){
        if(father(a[i].x)!=father(a[i].y)){//如果这条边连接的两个点属于不同集合 
            ans+=a[i].v;//将这条边加入最小生成树 
            unionn(a[i].x,a[i].y);//将两个点所在的集合合并为一个集合 
            cnt++;//计数已添加的边 
        }
        if(cnt==n-1) break;//当已经有n-1条边的时候，结束 
    }
    
    cout<<ans;
    return 0;
    
}
```
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

<br/>


# 3.例题
![在这里插入图片描述](https://img-blog.csdnimg.cn/2020091411260018.png?x-oss-process=image/watermark,type_ZmFuZ3poZW5naGVpdGk,shadow_10,text_aHR0cHM6Ly9ibG9nLmNzZG4ubmV0L2ExMzM1MjkxMjYzMg==,size_16,color_FFFFFF,t_70#pic_center)

![image](https://user-images.githubusercontent.com/50513297/93366530-dff1fd00-f87d-11ea-83a8-467987d70f88.png)
///////////////////////////////////////////////解法
![image](https://user-images.githubusercontent.com/50513297/93366570-ef714600-f87d-11ea-9a43-89c0d48a4628.png)
![image](https://user-images.githubusercontent.com/50513297/93366586-f304cd00-f87d-11ea-9168-416c41ccaf82.png)


![在这里插入图片描述](https://img-blog.csdnimg.cn/20200914112752712.png?#pic_center)





