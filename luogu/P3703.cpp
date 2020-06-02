#include <iostream>
#include <cstdio>
#define N 100002
using namespace std;
struct SegmentTree{
	int dat,add;
}t[N*4];
int head[N],ver[N*2],nxt[N*2],l;
int n,m,i,son[N][2],fa[N],in[N],out[N],dep[N],pos[N],f[N][21],cnt;
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
	in[x]=++cnt;pos[cnt]=x;
	f[x][0]=pre;
	dep[x]=dep[pre]+1;
	for(int i=head[x];i;i=nxt[i]){
		int y=ver[i];
		if(y!=pre) dfs(y,x);
	}
	out[x]=cnt;
}
void update(int p)
{
	t[p].dat=max(t[p*2].dat,t[p*2+1].dat);
}
void spread(int p)
{
	if(t[p].add){
		t[p*2].dat+=t[p].add;t[p*2].add+=t[p].add;
		t[p*2+1].dat+=t[p].add;t[p*2+1].add+=t[p].add;
		t[p].add=0;
	}
}
void build(int p,int l,int r)
{
	if(l==r){
		t[p].dat=dep[pos[l]];
		return;
	}
	int mid=(l+r)/2;
	build(p*2,l,mid);
	build(p*2+1,mid+1,r);
	update(p);
}
void change(int p,int l,int r,int ql,int qr,int x)
{
	if(ql<=l&&r<=qr){
		t[p].dat+=x;t[p].add+=x;
		return;
	}
	int mid=(l+r)/2;
	spread(p);
	if(ql<=mid) change(p*2,l,mid,ql,qr,x);
	if(qr>mid) change(p*2+1,mid+1,r,ql,qr,x);
	update(p);
}
int ask1(int p,int l,int r,int x)
{
	if(l==r) return t[p].dat;
	int mid=(l+r)/2;
	spread(p);
	if(x<=mid) return ask1(p*2,l,mid,x);
	else return ask1(p*2+1,mid+1,r,x);
}
int ask2(int p,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[p].dat;
	int mid=(l+r)/2,ans=0;
	spread(p);
	if(ql<=mid) ans=max(ans,ask2(p*2,l,mid,ql,qr));
	if(qr>mid) ans=max(ans,ask2(p*2+1,mid+1,r,ql,qr));
	return ans;
}
void init()
{
	dfs(1,0);
	for(int i=1;i<=n;i++) fa[i]=f[i][0];
	for(int j=0;j<=19;j++){
		for(int i=1;i<=n;i++) f[i][j+1]=f[f[i][j]][j];
	}
	build(1,1,n);
}
int LCA(int u,int v)
{
	if(dep[u]>dep[v]) swap(u,v);
	int tmp=dep[v]-dep[u];
	for(int i=0;(1<<i)<=tmp;i++){
		if((1<<i)&tmp) v=f[v][i];
	}
	if(u==v) return u;
	for(int i=19;i>=0;i--){
		if(f[u][i]!=f[v][i]) u=f[u][i],v=f[v][i];
	}
	return f[u][0];
}
bool unroot(int x)
{
	return son[fa[x]][0]==x||son[fa[x]][1]==x;
}
void rotate(int x)
{
	int y=fa[x],z=fa[y],p=(son[y][1]==x),w=son[x][p^1];
	if(unroot(y)) son[z][son[z][1]==y]=x;
	son[x][p^1]=y;son[y][p]=w;
	if(w) fa[w]=y;
	fa[y]=x;fa[x]=z;
}
void splay(int x)
{
	int y=x,z;
	while(unroot(x)){
		y=fa[x];z=fa[y];
		if(unroot(y)) rotate((son[z][1]==y)^(son[y][1]==x)?x:y);
		rotate(x);
	}
}
int findroot(int x)
{
	while(son[x][0]) x=son[x][0];
	return x;
}
void access(int x)
{
	for(int y=0;x;y=x,x=fa[x]){
		splay(x);
		if(son[x][1]){
			int p=findroot(son[x][1]);
			change(1,1,n,in[p],out[p],1);
		}
		if(y){
			int p=findroot(y);
			change(1,1,n,in[p],out[p],-1);
		}
		son[x][1]=y;
	}
}
int main()
{
	n=read();m=read();
	for(i=1;i<n;i++){
		int u=read(),v=read();
		insert(u,v);
		insert(v,u);
	}
	init();
	for(i=1;i<=m;i++){
		int op=read();
		if(op==1){
			int x=read();
			access(x);
		}
		else if(op==2){
			int x=read(),y=read(),lca=LCA(x,y);
			printf("%d\n",ask1(1,1,n,in[x])+ask1(1,1,n,in[y])-2*ask1(1,1,n,in[lca])+1);
		}
		else{
			int x=read();
			printf("%d\n",ask2(1,1,n,in[x],out[x]));
		}
	}
	return 0;
}
