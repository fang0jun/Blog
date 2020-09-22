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
