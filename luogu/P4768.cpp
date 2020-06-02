#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#include <vector>
#define N 200002
#define M 400002
using namespace std;
const int inf=1<<30;
struct Edge{
    int u,v,l,h;
}e[M];
struct event{
    int p,x;
    event(int _p,int _x){
        p=_p;x=_x;
    }
};
vector<event> fa[N],minx[N];
int head[N],ver[M*2],nxt[M*2],edge[M*2],l;
int t,n,m,q,k,s,ans,i,dis[N];
int read()
{
    char c=getchar();
    int w=0;
    while(c<'0'||c>'9') c=getchar();
    while(c<='9'&&c>='0'){
        w=w*10+c-'0';
        c=getchar();
    }
    return w;
}
void insert(int x,int y,int z)
{
    l++;
    ver[l]=y;
    edge[l]=z;
    nxt[l]=head[x];
    head[x]=l;
}
void Dijkstra()
{
    priority_queue<pair<int,int> > q;
    memset(dis,0x3f,sizeof(dis));
    q.push(make_pair(0,1));
    dis[1]=0;
    while(!q.empty()){
        int x=q.top().second,d=-q.top().first;
        q.pop();
        if(d!=dis[x]) continue;
        for(int i=head[x];i;i=nxt[i]){
            int y=ver[i];
            if(dis[y]>dis[x]+edge[i]){
                dis[y]=dis[x]+edge[i];
                q.push(make_pair(-dis[y],y));
            }
        }
    }
}
int my_comp(const Edge &x,const Edge &y)
{
    return x.h>y.h;
}
int main()
{
    t=read();
    while(t--){
        n=read();m=read();
        for(i=1;i<=m;i++){
            e[i].u=read();e[i].v=read();e[i].l=read();e[i].h=read();
            insert(e[i].u,e[i].v,e[i].l);
            insert(e[i].v,e[i].u,e[i].l);
        }
        Dijkstra();
        sort(e+1,e+m+1,my_comp);
        for(i=1;i<=n;i++){
            fa[i].push_back(event(inf,i));
            minx[i].push_back(event(inf,dis[i]));
        }
        for(i=m;i>=1;i--){

        }
    }
}