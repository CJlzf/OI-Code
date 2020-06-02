#include <iostream>
#include <cstdio>
#include <vector>
#define N 50002
using namespace std;
const int inf=1<<30;
struct object{
    int id,w,v;
}a[N];
struct query{
    int id,l,r;
}q[N];
struct SegmentTree{
    int l,r;
}t[N*4];
vector<object> v[N*4];
vector<query> v1[N*4];
char op[8];
int T,n,m,p,i,l[N],r[N],que[N*3],head=70000,tail=70000,cnt,ans[N],f[N],f1[N];
void insert(int p,int l,int r,int x,int v)
{
	v1[p].push_back(q[v]);
    if(l==r) return;
    int mid=(l+r)/2;
    if(x<=mid) insert(p*2,l,mid,x,v);
    else insert(p*2+1,mid+1,r,x,v);
}
void change(int p,int l,int r,int ql,int qr,int x)
{
    if(ql<=l&&r<=qr){
		v[p].push_back(a[x]);
		return;
    }
    int mid=(l+r)/2;
    if(ql<=mid) change(p*2,l,mid,ql,qr,x);
    if(qr>mid) change(p*2+1,mid+1,r,ql,qr,x);
}
void dp(int x,int l,int r)
{
    if(l>r) return; 
    int g[502];
    for(int i=0;i<=p;i++) g[i]=f[i];
    for(int i=0;i<v[x].size();i++){
		int w=v[x][i].w,V=v[x][i].v;
		for(int j=0;j<=p;j++) f1[j]=-inf;
		for(int j=0;j<=p;j++){
			f1[(j+w)%p]=max(f[(j+w)%p],f1[(j+w)%p]);
		    if(f[j]!=-inf) f1[(j+w)%p]=max(f1[(j+w)%p],f[j]+V);
		}
		for(int j=0;j<=p;j++) f[j]=f1[j];
    }
	for(int i=0;i<v1[x].size();i++){
		int l=v1[x][i].l,r=v1[x][i].r,id=v1[x][i].id;
		for(int j=l;j<=r;j++) ans[id]=max(ans[id],f[j]);
	}
    if(l!=r){
		int mid=(l+r)/2;
		dp(x*2,l,mid);
		dp(x*2+1,mid+1,r);
    } 
    for(int i=0;i<p;i++) f[i]=g[i];
}
int main()
{
    scanf("%d%d%d",&T,&m,&p);
    for(i=1;i<=p;i++) f[i]=-inf;
    for(i=1;i<=m;i++) ans[i]=-inf;
    for(i=1;i<=m;i++) ans[i]=-inf;
    for(i=1;i<=m;i++){
		scanf("%s",op);
		if(op[0]=='Q'&&op[1]=='U'){
			cnt++;
			scanf("%d%d",&q[cnt].l,&q[cnt].r);
			q[cnt].id=cnt;
			insert(1,1,m,i,cnt);
		} 
		else if(op[0]=='I'&&op[1]=='F'){
			n++;
			scanf("%d%d",&a[n].w,&a[n].v);
			a[n].id=n;
			que[--head]=n;
			l[n]=i;
		}
		else if(op[0]=='I'&&op[1]=='G'){
			n++;
	    	scanf("%d%d",&a[n].w,&a[n].v);
	    	a[n].id=n;
	    	que[tail++]=n;
	    	l[n]=i;
		}
		else if(op[0]=='D'&&op[1]=='F'){
	    	r[que[head]]=i;
			head++;
		}
		else{
	    	tail--;
	    	r[que[tail]]=i;
		}
	}
    for(i=1;i<=n;i++){
		if(r[i]==0) r[i]=m;
		change(1,1,m,l[i],r[i],i);
    }
    dp(1,1,m);
    for(i=1;i<=cnt;i++){
		if(ans[i]==-inf) puts("-1");
		else printf("%d\n",ans[i]);
    }
    return 0;
}
