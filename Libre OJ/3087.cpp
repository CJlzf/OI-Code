#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 100002
#define M 500002
using namespace std;
struct node{
	long long dis,id;
	node(long long _dis,long long _id){
		dis=_dis;
		id=_id;
	}
	bool operator < (const node &a) const{
		return dis>a.dis;
	}
};
long long head[N],ver[M],nxt[M],edge[M],l,u[M],v[M],w[M];
long long t,i,n,m,k,d[N],dis[2][N],col[2][N];
bool vis[N];
void insert(int x,int y,long long z)
{
	l++;
	ver[l]=y;
	edge[l]=z;
	nxt[l]=head[x];
	head[x]=l;
}
void Dijkstra(int opt)
{
	priority_queue<node> q;
	for(int i=1;i<=n;i++){
		dis[opt][i]=1LL<<50;
		vis[i]=0;
	}
	for(int i=1;i<=k;i++){
	    dis[opt][d[i]]=0;
		col[opt][d[i]]=d[i];
		q.push(node(0,d[i]));
	}
	while(!q.empty()){
		int x=q.top().id;
		q.pop();
		if(!vis[x]){
			vis[x]=1;
			for(int i=head[x];i;i=nxt[i]){
				int y=ver[i];
				if(dis[opt][y]>dis[opt][x]+edge[i]){
					dis[opt][y]=dis[opt][x]+edge[i];
					col[opt][y]=col[opt][x];
					q.push(node(dis[opt][y],y));
				}
			}
		}
	}
}
int main()
{
	cin>>t;
	while(t--){
		l=0;
		memset(head,0,sizeof(head));
		cin>>n>>m>>k;
		for(i=1;i<=m;i++){
			cin>>u[i]>>v[i]>>w[i];
		    if(u[i]!=v[i]) insert(u[i],v[i],w[i]);
		}
		for(i=1;i<=k;i++) cin>>d[i];
		Dijkstra(0);
		l=0;
		memset(head,0,sizeof(head));
		for(i=1;i<=m;i++){
			if(u[i]!=v[i]) insert(v[i],u[i],w[i]);
		}
		Dijkstra(1);
		long long ans=1LL<<50;
		for(i=1;i<=m;i++){
			if(col[0][u[i]]!=col[1][v[i]]&&col[0][u[i]]&&col[1][v[i]]) ans=min(ans,dis[0][u[i]]+dis[1][v[i]]+w[i]);
		}
		cout<<ans<<endl;
	}
	return 0;
}
