#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 1002
using namespace std;
const int inf=1<<30;
int head[N],ver[N*N*2],nxt[N*N*2],cap[N*N*2],l;
int n,S,T,i,j,t[N],a[N][N],p[N],match[N],dis[N],ans;
bool vis[N];
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
bool dfs(int x)
{
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!vis[y]){
			vis[y]=1;
			if(!match[y]||dfs(match[y])){
				match[y]=x;
				return 1;
			}
		}
	}
	return 0;
}
void hungary()
{
	for(int i=1;i<=n;i++){
		if(!match[i]){
			memset(vis,0,sizeof(vis));
			dfs(i);
		}
	}
}
bool bfs()
{
    queue<int> q;
    memset(dis,-1,sizeof(dis));
    q.push(S);
    dis[S]=0;
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
    return (dis[T]>0);
}
int dfs(int x,int flow)
{
    if(x==T||flow==0) return flow;
    int ans=0;
    for(int i=head[x];i!=-1;i=nxt[i]){
        int y=ver[i];
        if(dis[y]==dis[x]+1&&cap[i]>0){
            int a=dfs(y,min(flow,cap[i]));
            flow-=a;
            ans+=a;
            cap[i]-=a;
            cap[i^1]+=a;
        }
        if(flow==0) break;
    }
    if(flow) dis[x]=-1;
    return ans;
}
int main()
{
	n=read();
	for(i=1;i<=n;i++){
		t[i]=read();
		for(j=1;j<=t[i];j++){
			a[i][j]=read();
			insert(i,a[i][j]+n,0);
			insert(a[i][j]+n,i,0);
		}
	}
	for(i=1;i<=n;i++) p[i]=read();
	hungary();
	memset(head,-1,sizeof(head));l=0;
	T=n+1;
	for(i=1;i<=n;i++){
		for(j=1;j<=t[i];j++) insert(i,match[a[i][j]+n],inf);
	}
	for(i=1;i<=n;i++){
		if(p[i]<0) ans-=p[i],insert(S,i,-p[i]);
		else insert(i,T,p[i]);
	}
	while(bfs()) ans-=dfs(S,inf);
	printf("%d\n",-ans);
	return 0;
}
