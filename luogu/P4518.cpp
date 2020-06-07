#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <queue>
#define N 602
#define M 1000002
using namespace std;
const double PI=acos(-1);
const double eps=1e-8;
const int inf=1<<30;
struct point{
	double a;
	int u,v,op;
}p[2*N];
int head[N],ver[M*2],nxt[M*2],cap[M*2],l;
int n,s,t,i,x[N],y[N],dis[N],flow,cnt;
double ang,R;
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
	cap[l]=0;
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
	return (dis[t]!=-1);
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
int my_comp(const point &x,const point &y)
{
	if(x.a==y.a) return x.op<y.op;
	return x.a<y.a;
}
bool check(double mid)
{
	cnt=flow=l=0;
	for(int i=s;i<=t;i++) head[i]=-1;
	for(int i=1;i<=n;i++){
		double dis=sqrt(1.0*x[i]*x[i]+1.0*y[i]*y[i]);
		if(mid+R<dis||mid+dis<R) return 0;
		if(dis+R<=mid){
			for(int j=1;j<=n;j++) insert(i,j+n,1);
		}
		else{
			double a=atan2(y[i],x[i]),b=acos(1.0*(R*R+dis*dis-mid*mid)/(2.0*dis*R));
			double l=a-b,r=a+b;
			while(l<0) l+=2.0*PI;
			while(r<0) r+=2.0*PI;
			int pl=l/ang,pr=r/ang;
			p[++cnt]=(point){l-pl*ang,i,pl+1,0};
			p[++cnt]=(point){r-pr*ang,i,pr+1,1};
			pl++;pr++;
			if(l<=r){
				for(int j=pl+1;j<=pr;j++) insert(i,j+n,1);
			}
			else{
				for(int j=pl+1;j<=n;j++) insert(i,j+n,1);
				for(int j=1;j<=pr;j++) insert(i,j+n,1);
			}
		}
	}
	for(int i=1;i<=n;i++) insert(s,i,1),insert(i+n,t,1);
	sort(p+1,p+cnt+1,my_comp);
	while(bfs()) flow+=dfs(s,inf);
	if(flow==n) return 1;
	for(int i=1;i<=cnt;i++){
		if(p[i].op==0){
			insert(p[i].u,p[i].v+n,1);
			if(bfs()) flow+=dfs(s,inf);
		}
		else{
			int u=p[i].u,v=p[i].v+n,flag=0;
			for(int j=head[u],pre=0;j!=-1;pre=j,j=nxt[j]){
				if(ver[j]==v){
					if(pre) nxt[pre]=nxt[j];
					else head[u]=nxt[j];
					if(!cap[j]) flag=1;
					break;
				}
			}
			for(int j=head[v],pre=0;j!=-1;pre=j,j=nxt[j]){
				if(ver[j]==u){
					if(pre) nxt[pre]=nxt[j];
					else head[v]=nxt[j];
					break;
				}
			}
			if(!flag) continue;
			flow--;
			for(int j=head[s];j!=-1;j=nxt[j]){
				if(ver[j]==u){
					cap[j]^=1;cap[j^1]^=1;
					break;
				}
			}
			for(int j=head[t];j!=-1;j=nxt[j]){
				if(ver[j]==v){
					cap[j]^=1;cap[j^1]^=1;
					break;
				}
			}
			if(bfs()) flow+=dfs(s,inf);
		}
		if(flow==n) return 1;
	}
	return 0;
}
int main()
{
	n=read();R=read();
	for(i=1;i<=n;i++) x[i]=read(),y[i]=read();
	t=2*n+1;ang=2.0*PI/n;
	double l=0,r=400,mid,ans;
	while(r-l>eps){
		mid=(l+r)/2;
		if(check(mid)) r=ans=mid;
		else l=mid;
	}
	printf("%.8lf\n",ans);
	return 0;
}
