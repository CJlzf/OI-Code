#include <iostream>
#include <cstdio>
#define N 1000002
using namespace std;
int head[N],ver[N*2],nxt[N*2],l;
int n,t,m,i,f[N],g[N],d[N],sum[N],fa[N];
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
void insert(int x,int y)
{
	l++;
	ver[l]=y;
	nxt[l]=head[x];
	head[x]=l;
}
void dfs(int x,int pre)
{
	int max1=0,max2=0;
	fa[x]=pre;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y!=pre){
			dfs(y,x);
			d[x]++;
			if(f[y]>=max1) max2=max1,max1=f[y];
			else if(f[y]>max2) max2=f[y];
		}
	}
	f[x]=max2+d[x];
}
void dp(int x,int pre)
{
	if(x!=t) sum[x]=sum[pre]+d[x]-1;
	g[x]=sum[pre]+f[x]+1-(pre!=m);
	for(int i=head[x];i;i=nxt[i]){
		if(ver[i]!=pre) dp(ver[i],x);
	}
}
bool check(int x)
{
	int p=m,pre=0,ans=0,ret=x,dep=0;
	while(p){
		int cnt=0;
		dep++;
		for(int i=head[p];i;i=nxt[i]){
			int y=ver[i];
			if(y!=fa[p]&&y!=pre) cnt+=(g[y]>ret);
		}
		ans+=cnt;ret-=cnt;
		if(ans>dep||ret<0) return 0;
		pre=p;p=fa[p];
	}
	return 1;
}
int main()
{
	n=read();t=read();m=read();
	for(i=1;i<n;i++){
		int u=read(),v=read();
		insert(u,v);
		insert(v,u);
	}
	dfs(t,0);
	f[t]=0;
	dp(t,0);
	int l=0,r=n,mid,ans;
	while(l<=r){
		mid=(l+r)/2;
		if(check(mid)) ans=mid,r=mid-1;
		else l=mid+1;
	}
	printf("%d\n",ans);
	return 0;
}
