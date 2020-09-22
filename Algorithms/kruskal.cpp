#include<iostream>
#include<algorithm>
using namespace std;

struct point{
    int x;
    int y;
    int v;
}; //д�ṹ����������� 
point a[10000];//���
 
int cmp(const point &a,const point &b){
    if(a.v<b.v) return 1;
    else return 0;
}//����Ҫ�õ��ıȽϺ��� ����С����
 
int fat[101];
int father(int x){
    if(fat[x]!=x) return fat[x]=father(fat[x]);
    else return fat[x];
}//�ҳ�һ���������ĸ����ϣ��������ĵ��� 

void unionn(int x,int y){
    int fa=father(x);
    int fb=father(y);
    if(fa!=fb) fat[fa]=fb;
}//���������ӵ������������Ϻϲ� 

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
    }//���룬��� 
    sort(a+1,a+1+k,cmp);//�������б� 
    
    for(i=1;i<=n;i++){
        fat[i]=i;
    }//��ʼ������ÿ���㿴���������� 
    
    for(i=1;i<=k;i++){
        if(father(a[i].x)!=father(a[i].y)){//������������ӵ����������ڲ�ͬ���� 
            ans+=a[i].v;//�������߼�����С������ 
            unionn(a[i].x,a[i].y);//�����������ڵļ��Ϻϲ�Ϊһ������ 
            cnt++;//��������ӵı� 
        }
        if(cnt==n-1) break;//���Ѿ���n-1���ߵ�ʱ�򣬽��� 
    }
    
    cout<<ans;
    return 0;
    
}
