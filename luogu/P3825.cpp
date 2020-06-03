#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100002
#define M 600002
using namespace std;
struct event{
	int i,j,ci,cj;
}a[N];
char c[N];
int head[N],ver[M],nxt[M],l;
int n,d,m,i,x[N],cntx,c1[N],c2[N],dfn[N],low[N],sccno[N],s[N],tim,cnt,top,ans[N];
bool flag;
int get(char c)
{
	if(c=='A') return 1;
	if(c=='B') return 2;
	return 3;
}
void insert(int x,int y)
{
	l++;
	ver[l]=y;
	nxt[l]=head[x];
	head[x]=l;
}
void Tarjan(int x)
{
	dfn[x]=low[x]=++tim;
	s[++top]=x;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(!dfn[y]){
			Tarjan(y);
			low[x]=min(low[x],low[y]);
		}
		else if(!sccno[y]) low[x]=min(low[x],dfn[y]);
	}
	if(dfn[x]==low[x]){
		cnt++;
		while(1){
			int y=s[top--];
			sccno[y]=cnt;
			if(y==x) break;
		}
	}
}
void dfs(int p)
{
	if(flag) return;
	if(p==cntx+1){
		l=cnt=tim=0;
		memset(head,0,sizeof(head));
		memset(dfn,0,sizeof(dfn));
		memset(low,0,sizeof(low));
		memset(sccno,0,sizeof(sccno));
		for(int i=1;i<=m;i++){
			if(c1[a[i].i]!=a[i].ci&&c2[a[i].i]!=a[i].ci) continue;
			else if(c1[a[i].j]!=a[i].cj&&c2[a[i].j]!=a[i].cj){
				if(c1[a[i].i]==a[i].ci) insert(a[i].i,a[i].i+n);
				else insert(a[i].i+n,a[i].i);
			}
			else{
				int u=(c1[a[i].i]==a[i].ci)?a[i].i:a[i].i+n;
				int v=(c1[a[i].j]==a[i].cj)?a[i].j:a[i].j+n;
				int u1=(u<=n)?u+n:u-n,v1=(v<=n)?v+n:v-n;
				insert(u,v);insert(v1,u1);
			}
		}
		for(int i=1;i<=2*n;i++){
			if(!dfn[i]) Tarjan(i);
		}
		for(int i=1;i<=n;i++){
			if(sccno[i]==sccno[n+i]) return;
		}
		flag=1;
		for(int i=1;i<=n;i++){
			if(sccno[i]<sccno[n+i]) ans[i]=c1[i];
			else ans[i]=c2[i];
		}
		return;
	}
	c1[x[p]]=2;c2[x[p]]=3;
	dfs(p+1);
	c1[x[p]]=1;c2[x[p]]=3;
	dfs(p+1);
}
int main()
{
	scanf("%d%d%s%d\n",&n,&d,c+1,&m);
	for(i=1;i<=m;i++){
		char c1,c2;
		scanf("%d %c %d %c",&a[i].i,&c1,&a[i].j,&c2);
		a[i].ci=get(c1);
		a[i].cj=get(c2);
	}
	for(i=1;i<=n;i++){
		if(c[i]=='x') x[++cntx]=i;
		else if(c[i]=='a') c1[i]=2,c2[i]=3;
		else if(c[i]=='b') c1[i]=1,c2[i]=3;
		else c1[i]=1,c2[i]=2;
	}
	dfs(1);
	if(!flag) puts("-1");
	else{
		for(i=1;i<=n;i++){
			if(ans[i]==1) putchar('A');
			else if(ans[i]==2) putchar('B');
			else putchar('C');
		}
	}
	return 0;
}
