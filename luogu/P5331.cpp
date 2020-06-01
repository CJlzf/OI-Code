#include <iostream>
#include <cstdio>
#include <cmath>
#include <cstring>
#include <queue>
#include <algorithm>
#define int long long
#define N 100002
using namespace std;
const int inf=1<<30;
struct SegmentTree{
    int l,r;
}t[2][N*40];
int head[N],ver[N*2],nxt[N*2],cap[N*2],cost[N*2],l;
int n,m,w,S,T,i,j,a[N],b[N],dis[N],vis[N],now,ans,cnt,num,root[2][N],id[N];
bool in[N];
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
void insert(int x,int y,int z,int w)
{
    ver[l]=y;
    cap[l]=z;
    cost[l]=w;
    nxt[l]=head[x];
    head[x]=l;
    l++;
    ver[l]=x;
    cost[l]=-w;
    nxt[l]=head[y];
    head[y]=l;
    l++;
}
void SPFA()
{
    queue<int> q;
    memset(dis,0x3f,sizeof(dis));
    q.push(T);
    in[T]=1;dis[T]=0;
    while(!q.empty()){
        int x=q.front();
        q.pop();
        for(int i=head[x];i!=-1;i=nxt[i]){
            int y=ver[i];
            if(dis[y]>dis[x]+cost[i^1]&&cap[i^1]){
                dis[y]=dis[x]+cost[i^1];
                if(!in[y]){
                    in[y]=1;
                    q.push(y);
                }
            }
        }
        in[x]=0;
    }
}
int dfs(int x,int flow)
{
    vis[x]=now;
    if(x==T||flow==0) return flow;
    int ans=0;
    for(int i=head[x];i!=-1;i=nxt[i]){
        int y=ver[i];
        if(dis[x]==dis[y]+cost[i]&&cap[i]&&vis[y]!=now){
            int a=dfs(y,min(flow,cap[i]));
            flow-=a;
            ans+=a;
            cap[i]-=a;
            cap[i^1]+=a;
        }
        if(!flow) break;
    }
    return ans;
}
bool change()
{
    int del=inf;
    for(int i=0;i<=num;i++){
        if(vis[i]==now){
            for(int j=head[i];j!=-1;j=nxt[j]){
                int y=ver[j];
                if(vis[y]!=now&&cap[j]) del=min(del,dis[y]+cost[j]-dis[i]);
            }
        }
    }
    if(del==inf) return 0;
    for(int i=0;i<=num;i++){
        if(vis[i]==now) dis[i]+=del;
    }
    return 1;
}
void zkw()
{
    SPFA();
    do{
        int flow=0;
        do{
            now++;
            flow=dfs(S,inf);
            ans+=flow*dis[S];
        }while(flow);
    }while(change());
}
void build(int op,int &p,int pre,int l,int r,int x,int y)
{
    p=++cnt;id[p]=++num;
    t[op][p].l=t[op][pre].l;t[op][p].r=t[op][pre].r;
    if(l==r){
        insert(id[p],y,inf,op==0?-b[x]:b[x]);
        return;
    }
    int mid=(l+r)/2;
    if(x<=mid) build(op,t[op][p].l,t[op][pre].l,l,mid,x,y);
    else build(op,t[op][p].r,t[op][pre].r,mid+1,r,x,y);
    if(t[op][p].l!=0) insert(id[p],id[t[op][p].l],inf,0);
    if(t[op][p].r!=0) insert(id[p],id[t[op][p].r],inf,0);
}
void link(int op,int p,int l,int r,int ql,int qr,int x,int w)
{
    if(!p) return;
    if(ql<=l&&r<=qr){
        insert(x,id[p],1,op==0?w:-w);
        return;
    }
    int mid=(l+r)/2;
    if(t[op][p].l&&ql<=mid) link(op,t[op][p].l,l,mid,ql,qr,x,w);
    if(t[op][p].r&&qr>mid) link(op,t[op][p].r,mid+1,r,ql,qr,x,w);
}
signed main()
{
    memset(head,-1,sizeof(head));
    n=read();w=read();
    for(i=1;i<=n;i++) a[i]=b[i]=read();
    sort(b+1,b+n+1);
    m=unique(b+1,b+n+1)-b-1;
    for(i=1;i<=n;i++) a[i]=lower_bound(b+1,b+m+1,a[i])-b;
    T=num=2*n+1;
    for(i=1;i<=n;i++){
        insert(S,i+n,1,0);
        insert(i+n,T,1,w);  
        insert(i,T,1,0);
    }
    for(i=1;i<=n;i++){
        build(0,root[0][i],root[0][i-1],1,m,a[i],i);
        build(1,root[1][i],root[1][i-1],1,m,a[i],i);
    }
    for(i=2;i<=n;i++){
        link(0,root[0][i-1],1,m,1,a[i],n+i,b[a[i]]);
        link(1,root[1][i-1],1,m,a[i]+1,m,n+i,b[a[i]]);
    }
    zkw();
    printf("%lld\n",ans);
    return 0;
}