#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#include <algorithm>
#define N 200002
#define M 400002
using namespace std;
struct Edge{
    int u,v,w,h;
}e[M];
struct SegmentTree{
    int l,r,fa;
}t[N*40];
int head[N],ver[M*2],nxt[M*2],edge[M*2],l;
int T,n,m,q,k,s,i,v0,p0,dis[N],dep[N],w[N],cnt;
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
int build(int l,int r)
{
	int p=++cnt,mid=(l+r)/2;
	if(l==r){
		t[p].fa=l;
		return p;
	}
	t[p].l=build(1,mid);
	t[p].r=build(mid+1,r);
	return p;
}
int query(int p,int l,int r,int v,int root)
{
	if(l==r){
		if(t[p].fa==l) return p;
		return query(root,1,n,t[p].fa,root);
	}
	int mid=(l+r)/2;
	if(v<=mid) return query(t[p].l,l,mid,v,root);
	else return query(t[p].r,mid+1,r,v,root);
}
int insert(int pre,int l,int r,int f1,int f2)
{
	int p=++cnt,mid=(l+r)/2;
	t[p]=t[pre];
	if(l==r){
		t[p].fa=f1;
		return p;
	}
	if(f2<=mid) t[p].l=insert(t[pre].l,l,mid,f1,f2);
	else t[p].r=insert(t[pre].r,mid+1,r,f1,f2);
	return p;
}
int my_comp(const Edge &x,const Edge &y)
{
    return x.w>y.w;
}
int main()
{
    T=read();
    while(T--){
        n=read();m=read();
        for(i=1;i<=m;i++){
            e[i].u=read();e[i].v=read();e[i].w=read();e[i].h=read();
            insert(e[i].u,e[i].v,e[i].w);
            insert(e[i].v,e[i].u,e[i].w);
        }
        q=read();k=read();s=read();
        Dijkstra();
        sort(e+1,e+m+1,my_comp);
        for(i=1;i<=m;i++) w[i]=e[i].w;
        sort(w+1,w+n+1);
        int T=unique(w+1,w+n+1)-w;
        w[T+1]=s+1;
        
    }
}