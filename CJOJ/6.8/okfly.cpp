#include <iostream>
#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#define int long long
#define N 200002
using namespace std;
struct Edge{
	int u,v,w;
}e[N];
vector<int> v[N];
int T,n,m,i,j,fa[N],dep[N],pre[N],size[N],f[N],num[N][21][2],ans,cnt;
bool vis[N];
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
int my_comp(const Edge &x,const Edge &y)
{
	return x.w>y.w;
}
int find(int x)
{
	if(x!=f[x]) f[x]=find(f[x]);
	return f[x];
}
void dfs(int x)
{
	dep[x]=dep[fa[x]]+1;
	for(int i=0;i<v[x].size();i++){
		if(v[x][i]!=pre[x]){
			int y=(e[v[x][i]].u==x)?e[v[x][i]].v:e[v[x][i]].u;
			pre[y]=v[x][i];
			fa[y]=x;
			dfs(y);
		}
	}
}
void merge(int u,int v,int w)
{
	u=find(u),v=find(v);
	for(int i=0;i<=20;i++){
		unsigned long long tmp=0;
		int opt=(w>>i)&1;
		for(int j=0;j<=1;j++) tmp+=(unsigned long long)num[u][i][j]*num[v][i][j^opt^1];
		ans+=(1<<i)*tmp;
		for(int j=0;j<=1;j++) num[u][i][j]+=num[v][i][j];
	}
	f[v]=u;size[u]+=size[v];
}
signed main()
{
	T=read();
	while(T--){
		n=read();m=read();
		for(i=1;i<=n;i++) v[i].clear(),f[i]=i;
		memset(vis,0,sizeof(vis));
		for(i=1;i<=m;i++) e[i].u=read(),e[i].v=read(),e[i].w=read();
		sort(e+1,e+m+1,my_comp);
		for(i=1;i<=m;i++){
			int f1=find(e[i].u),f2=find(e[i].v);
			if(f1!=f2){
				vis[i]=1;
				f[f1]=f2;
				v[e[i].u].push_back(i);
				v[e[i].v].push_back(i);
			}
		}
		dfs(1);
		for(i=1;i<=n;i++){
			if(!vis[i]){
				int u=e[i].u,v=e[i].v,w=e[i].w;
				while(u!=v){
					if(dep[u]>dep[v]) swap(u,v);
					e[pre[v]].w+=w;
					v=fa[v];
				}
			}
		}
		ans=cnt=0;
		memset(num,0,sizeof(num));
		for(i=1;i<=n;i++){
			size[i]=1;
			f[i]=i;
			for(j=0;j<=20;j++) num[i][j][(i<<j)&1]++;
		}
		for(i=1;i<=m;i++){
			if(vis[i]) e[++cnt]=e[i];
		}
		sort(e+1,e+cnt+1,my_comp);
 		for(i=1;i<=cnt;i++) merge(e[i].u,e[i].v,e[i].w);
		printf("%lld\n",ans);
	}
	return 0;
}
