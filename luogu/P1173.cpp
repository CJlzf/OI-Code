#include <iostream>
#include <cstdio>
#include <algorithm>
#include <queue>
#include <cstring>
#include <cmath>
#define N 100002
#define P 1000117
using namespace std;
pair<int,int> p[N];
int dx[4]={1,-1,0,0},dy[4]={0,0,1,-1};
int head[N*25],ver[N*100],nxt[N*100],l;
int T,n,m,c,i,dfn[N*25],low[N*25],vis[N*25],cnt,cntp,col,tim;
bool cut[N*25],tag[N*25];
struct Hash{
	int h[P],x[N*100],y[N*100],id[N*100],nxt[N*100],l;
	void clear()
	{
		memset(h,0,sizeof(h));l=0;
	}
	void insert(int tx,int ty,int t)
	{
		int hash=(1LL*tx*(n-1)+ty)%P;
		l++;
		x[l]=tx;y[l]=ty;id[l]=t;
		nxt[l]=h[hash];h[hash]=l;
	}
	int ask(int tx,int ty)
	{
		int hash=(1LL*tx*(n-1)+ty)%P;
		for(int i=h[hash];i;i=nxt[i]){
			if(x[i]==tx&&y[i]==ty) return id[i];
		}
		return 0;
	}
}mp,e;
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
bool find(int x,int y)
{
	int pos=lower_bound(p+1,p+c+1,make_pair(x,y))-p;
	return (p[pos].first==x&&p[pos].second==y);
}
bool in(int x,int y,int u,int d,int l,int r)
{
	return x>=u&&x<=d&&y>=l&&y<=r;
}
void insert(int x,int y)
{
	l++;
	ver[l]=y;
	nxt[l]=head[x];
	head[x]=l;
}
bool check()
{
	if(1LL*n*m-c<=1) return 0;
	if(1LL*n*m-c>=3) return 1;
	for(int x=1;x<=n;x++){
		for(int y=1;y<=m;y++){
			if(find(x,y)) continue;
			for(int i=0;i<4;i++){
				int tx=x+dx[i],ty=y+dy[i];
				if(in(tx,ty,1,n,1,m)&&!find(tx,ty)) return 0;
			}
		}
	}
	return 1;
}
void link(int x,int y)
{
	for(int i=-2;i<=2;i++){
		for(int j=-2;j<=2;j++){
			int tx=x+i,ty=y+j;
			if(!in(tx,ty,1,n,1,m)||find(tx,ty)) continue;
			int p1=mp.ask(tx,ty);
			if(!p1) p1=++cntp,mp.insert(tx,ty,p1);
			int tmp=p1;
			if(in(tx+1,ty,max(1,x-2),min(n,x+2),max(1,y-2),min(m,y+2))&&!find(tx+1,ty)){
				int p2=mp.ask(tx+1,ty);
				if(!p2) p2=++cntp,mp.insert(tx+1,ty,p2);
				if(p1>p2) swap(p1,p2);
				if(!e.ask(p1,p2)){
					e.insert(p1,p2,1);
					insert(p1,p2);insert(p2,p1);
				}
			}
			if(in(tx,ty+1,max(1,x-2),min(n,x+2),max(1,y-2),min(m,y+2))&&!find(tx,ty+1)){
				int p2=mp.ask(tx,ty+1);
				if(!p2) p2=++cntp,mp.insert(tx,ty+1,p2);
				if(p1>p2) swap(p1,p2);
				if(!e.ask(p1,p2)){
					e.insert(p1,p2,1);
					insert(p1,p2);insert(p2,p1);
				}
			}
			if(abs(i)<=1&&abs(j)<=1) tag[tmp]=1;
		}
	}
}
void bfs(int s)
{
	queue<int> q;
	q.push(s);vis[s]=col;
	while(!q.empty()){
		int x=q.front();
		q.pop();
		for(int i=head[x];i;i=nxt[i]){
			int y=ver[i];
			if(!vis[y]){
				vis[y]=col;
				q.push(y);
			}
		}
	}
}
bool judge()
{
	for(int i=1;i<=cntp;i++){
		if(!vis[i]){
			col++;
			bfs(i);
		}
	}
	for(int i=1;i<=c;i++){
		int x=p[i].first,y=p[i].second,co=-1;
		for(int j=-2;j<=2;j++){
			for(int k=-2;k<=2;k++){
				int tx=x+j,ty=y+k;
				if(!in(tx,ty,1,n,1,m)||find(tx,ty)) continue;
				int id=mp.ask(tx,ty);
				if(co==-1) co=vis[id];
				else if(co!=vis[id]) return 0;
			}
		}
	}
	return 1;
}
void Tarjan(int x,int pre)
{
    int son=0;
    dfn[x]=low[x]=++tim;
    for(int i=head[x];i;i=nxt[i]){
        int y=ver[i];
        if(dfn[y]==0){
            son++;
            Tarjan(y,x);
            low[x]=min(low[x],low[y]);
            if(low[y]>=dfn[x]){
                if(cut[x]==0) cnt++;
                cut[x]=1;
            }
        }
        else if(dfn[y]<dfn[x]&&y!=pre) low[x]=min(low[x],dfn[y]);
    }
    if(pre==0&&son==1) cnt--,cut[x]=0;
}
int main()
{
	T=read();
	while(T--){
		mp.clear();e.clear();
		l=tim=col=cnt=cntp=0;
		memset(tag,0,sizeof(tag));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(cut,0,sizeof(cut));
		memset(vis,0,sizeof(vis));
		memset(head,0,sizeof(head));
		n=read();m=read();c=read();
		for(i=1;i<=c;i++){
			int x=read(),y=read();
			p[i]=make_pair(x,y);
		}
		sort(p+1,p+c+1);
		p[c+1]=make_pair(0,0);
		if(!check()){
			puts("-1");
			continue;
		}
 		for(i=1;i<=c;i++) link(p[i].first,p[i].second);
		if(!judge()){
			puts("0");
			continue;
		}
		if(n==1||m==1){
			puts("1");
			continue;
		}
		bool flag=0;
		for(i=1;i<=cntp;i++){
			if(!dfn[i]) Tarjan(i,0);
		}
		for(i=1;i<=cntp;i++){
			if(tag[i]&&cut[i]){
				puts("1");
				flag=1;
				break;
			}
		}
		if(!flag) puts("2");
	}
	return 0;
}
