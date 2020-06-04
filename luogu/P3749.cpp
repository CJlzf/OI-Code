#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 50002
#define M 5000002
using namespace std;
const int inf=1<<30;
int head[N],ver[M*2],nxt[M*2],cap[M*2],l;
int n,n1,m,s,t,i,j,a[N],v[N],d[102][102],dis[N],ans;
int read()
{
	char c=getchar();
	int w=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		w=w*10+c-'0';
		c=getchar();
	}
	return w*f;
}
int id(int l,int r)
{
	return l*(n-1)+r;
}
void insert(int x,int y,int z)
{
	ver[l]=y;
	cap[l]=z;
	nxt[l]=head[x];
	head[x]=l;
	l++;
	ver[l]=x;
	nxt[l]=head[y];
	head[y]=l;
	l++;
}
bool bfs()
{
	queue<int> q;
	memset(dis,-1,sizeof(dis));
	q.push(s);
	dis[s]=0;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i!=-1;i=nxt[i]){
			int y=ver[i];
			if(dis[y]==-1&&cap[i]>0){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}
	return (dis[t]>0);
}
int dfs(int x,int flow)
{
	if(x==t||flow==0) return flow;
	int ans=0;
	for(int i=head[x];i!=-1;i=nxt[i]){
		int y=ver[i];
		if(dis[y]==dis[x]+1&&cap[i]>0){
			int a=dfs(y,min(flow,cap[i]));
			flow-=a;ans+=a;
			cap[i]-=a;cap[i^1]+=a;
		}
		if(!flow) break;
	}
	if(flow) dis[x]=-1;
	return ans;
}
int main()
{
	memset(head,-1,sizeof(head));
	n=read();m=read();
	for(i=1;i<=n;i++) a[i]=read(),n1=max(n1,a[i]);
	for(i=1;i<=n;i++){
		for(j=1;j<=n-i+1;j++) d[i][i+j-1]=read();
	}
	t=n*n+n1+1;
	for(i=1;i<=n;i++){
		for(j=i;j<=n;j++){
			if(i==j) v[id(i,j)]=d[i][j]-a[i];
			else{
				if(i<n) insert(id(i,j),id(i+1,j),inf);
				if(j>1) insert(id(i,j),id(i,j-1),inf);
				v[id(i,j)]=d[i][j];
			}
		}
	}
	for(i=1;i<=n;i++){
		v[n*n+a[i]]=-m*a[i]*a[i];
		insert(id(i,i),n*n+a[i],inf);
	}
	for(i=1;i<t;i++){
		if(v[i]<0) insert(i,t,-v[i]);
		else ans+=v[i],insert(s,i,v[i]);
	}
	while(bfs()) ans-=dfs(s,inf);
	printf("%d\n",ans);
	return 0;
}
