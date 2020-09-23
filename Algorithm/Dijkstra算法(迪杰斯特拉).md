
# 算法描述

|描述：

  Dijkstra(迪杰斯特拉)算法是典型的单源最短路径算法，用于计算一个节点到其他所有节点的最短路径。主要特点是以起始点为中心向外层层扩展，直到扩展到终点为止。由for循环可知，其时间复杂度是O（n^2）。



|原理：  

  在已知图的邻接矩阵 net.vexs[i ] [j](无向网，含权值的图）的条件下，通过遍历已知图的所有路径，用 dis[i] 数组来记录到i点的最短路径，然后在循环中不断判断更替。首先，将所有点的集合分为俩部分，一边是已经遍历过的，另外一边是没有遍历过的，分别用mark[i]=1、mark[i]=0来表示。**层层扩散，实时比较和更新最短路径**



|代码通解：

​	在下面代码中，先将赋予初始值dis[i]=INF(无穷大)、mark[i]=0（未标记），而后单独将源点（x）所联通的路径权值 net.arcs[x] [i]赋予dis[i](<INF称为初始化），i为联通的点，暂定为到i的最短路径，标记mark[x]=1，即已经遍历;然后，在一个for遍历了所有节点的大循环里面：①寻找遍历到点联通路径（与之相连线的点）中权值最小的一条； 标记遍历点； ②修正最短路径；

所有点遍历完成后，dis[i]也在不断的修正中得到真正的最小值，即最短路径。



# 算法实现 

```c++
#include<bits/stdc++.h>

#define INF 100//INF为比图中任何权值都大的数
#define maxSize 7   //图的顶点数
#define number 12   //图的边数
using namespace std;
typedef struct {//图的定义
	int edges[maxSize][maxSize];//邻接矩阵的定义
	int n, e;   //分别为顶点数和边数
}MGraph;


/*迪杰斯特拉算法代码，函数结束时dist[]存放了v点到其余各顶点的最短路径长度，path[]中保存从V到各顶点的最短路径*/
#define MAXSIZE 20
#define PLACENUM 12
#define INF 9999           // 此处定义999为无穷大
 
struct
{
    int vexnum,arcnum;  //节点数和边数
    int vexs[MAXSIZE];      // 节点名
    int arcs[MAXSIZE][MAXSIZE];   //俩个节点之间的值
} net;
/*补充的结构体net,2019.7.3*/
 
void Dijkstra(int x,int y)      // x为源点，y为终点
{
    int i,j,k;
    int min;
    int u;   //下一个放入集合p的点
    int dis[net.vexnum];   //  最短路径
    int mark[net.vexnum];   //   被mark的便是已经遍历,未被mark的便是未遍历
    /*首先进行最短路径初始化*/
    for(i=0; i<net.vexnum; i++)
    {
        mark[i] = 0;
        dis[i] = net.arcs[x][i];
    }
 
 
    mark[x]=1;          // 标记源点
    
    
    for(k=0; k<net.vexnum; k++)          // for 大循环
    {
        min = INF;   //  min初始化最大值，便于后来数据替换（每一个点的出度入度判断）
        
        /*寻找遍历到点联通路径（与之相连线的点）中权值最小的一条； 标记遍历点；*/
        for(i=0; i<net.vexnum; i++)
        {
            if(mark[i]==0&&min>dis[i])      //判断未遍历点 且 被赋值的最短路径（dis[i]<INF），未被赋值的点     //                                                     应当min==dis[i]=INF
            {
               min = dis[i];             //在已知赋值最短路径中，寻找权值最小的点并将他作为下一个遍历 
               u=i;                            //点u点
            }
        }
 
 
        mark[u]=1;      //标记u点，下面u修正将会以最短路径进行辐射
 
        /*修正最短路径*/
        for(i=0;i<net.vexnum;i++)
        {
            if(!mark[i]&&dis[i]>dis[u]+net.arcs[u][i])                 // ！mark[i]判断不去走回头路，        
                                                                                             /*dis[i]>dis[u]+net.arcs[u][i]有俩个用途：①若u链接的是x源点没有赋值最短路径的点，那么这里可以赋值②若是赋值过的点，那么可以判断是上一个dis[i]（此时是被赋值过的）是不是真正的最短路径，即修正。*/
 
            {
                dis[i] = dis[u] + net.arcs[u][i];      //若A->C比A->B->C更长那么A->B->C则是到C的最短路径，下图将解释。
         
                   }
             }
    }
     printf("最短路径值为：             %d",dis[y]);
}
```

