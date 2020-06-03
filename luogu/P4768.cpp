#include <map>
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
vector<pair<int,int> > fa[N],minx[N];
int head[N],ver[M*2],nxt[M*2],edge[M*2],l;
int t,n,m,q,k,s,ans,i,dis[N],f[N],minn[N],dep[N];
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
int find(int x)
{
    if(x!=f[x]) f[x]=find(f[x]);
    return f[x];
}
int main()
{
	freopen("return.in","r",stdin);
	freopen("return.out","w",stdout);
    t=read();
    while(t--){
		l=ans=0;
		memset(head,0,sizeof(head));
		for(i=1;i<=n;i++) fa[i].clear(),minx[i].clear();
        n=read();m=read();
        for(i=1;i<=m;i++){
            e[i].u=read();e[i].v=read();e[i].l=read();e[i].h=read();
            insert(e[i].u,e[i].v,e[i].l);
            insert(e[i].v,e[i].u,e[i].l);
        }
		q=read();k=read();s=read();
        Dijkstra();
        sort(e+1,e+m+1,my_comp);
        for(i=1;i<=n;i++){
            f[i]=i;minn[i]=dis[i];dep[i]=1;
            fa[i].push_back(make_pair(inf,i));
            minx[i].push_back(make_pair(inf,dis[i]));
        }
        for(i=1;i<=m;i++){
            int u=e[i].u,v=e[i].v,h=e[i].h;
            int f1=find(u),f2=find(v);
			if(f1==f2) continue;
			if(dep[f1]>dep[f2]) swap(f1,f2);
			f[f1]=f2;
			dep[f2]=max(dep[f1]+1,dep[f2]);
			fa[f1].push_back(make_pair(h,f2));
			if(minn[f2]>minn[f1]) minx[f2].push_back(make_pair(h,minn[f1])),minn[f2]=minn[f1];
        }
		for(i=1;i<=n;i++){
			sort(fa[i].begin(),fa[i].end());
			sort(minx[i].begin(),minx[i].end());
		}
		for(i=1;i<=q;i++){
			int v=read(),p=read(),f;
			v=(v+k*ans-1)%n+1;
			p=(p+k*ans)%(s+1)+1;
			while(1){
				int pos=lower_bound(fa[v].begin(),fa[v].end(),make_pair(p,0))-fa[v].begin();
				f=fa[v][pos].second;
				if(f==v) break;
				v=f;
			}
			int pos=lower_bound(minx[v].begin(),minx[v].end(),make_pair(p,0))-minx[v].begin();
			ans=minx[v][pos].second;
			printf("%d\n",ans);
		}
    }
	return 0;
}
