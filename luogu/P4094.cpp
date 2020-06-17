#include <iostream>
#include <cstdio>
#include <cstring>
#define N 100002
using namespace std;
struct ChairmanTree{
	int l,r,dat;
}t[N*40];
char c[N];
int n,q,i,j,lg[N],f[22][N],root[N],cnt;
int a[N],x[N],y[N],sa[N],height[N],rk[N],tsa[N],cntx[N],cnty[N];
void build(int &p,int l,int r)
{
	p=++cnt;
	if(l==r) return;
	int mid=(l+r)/2;
	build(t[p].l,l,mid);build(t[p].r,mid+1,r);
}
void insert(int &p,int pre,int l,int r,int x)
{
	p=++cnt;t[p]=t[pre];
	if(l==r){
		t[p].dat++;
		return;
	}
	int mid=(l+r)/2;
	if(x<=mid) insert(t[p].l,t[pre].l,l,mid,x);
	else insert(t[p].r,t[pre].r,mid+1,r,x);
	t[p].dat=t[t[p].l].dat+t[t[p].r].dat;
}
int ask(int p1,int p2,int l,int r,int ql,int qr)
{
	if(ql<=l&&r<=qr) return t[p1].dat-t[p2].dat;
	int mid=(l+r)/2,ans=0;
	if(ql<=mid) ans+=ask(t[p1].l,t[p2].l,l,mid,ql,qr);
	if(qr>mid) ans+=ask(t[p1].r,t[p2].r,mid+1,r,ql,qr);
	return ans;
}
int getmin(int l,int r)
{
	if(l>r) return 1<<30;
	int t=lg[r-l+1];
	return min(f[t][l],f[t][r-(1<<t)+1]);
}
bool check(int x,int a,int b,int c)
{
	int l,r,mid,L=0,R=0;
	l=1,r=rk[c];
	while(l<=r){
		mid=(l+r)/2;
		if(getmin(mid+1,rk[c])>=x) L=mid,r=mid-1;
		else l=mid+1;
	}
	l=rk[c],r=n;
	while(l<=r){
		mid=(l+r)/2;
		if(getmin(rk[c]+1,mid)>=x) R=mid,l=mid+1;
		else r=mid-1;
	}
	if(R==0||L>R) return 0;
	if(ask(root[x==0?b:b-x+1],root[a-1],1,n,L,R)>0) return 1;
	return 0;
}
int main()
{
    scanf("%d%d%s",&n,&q,c+1);
	for(i=1;i<=n;i++) a[i]=(int)(c[i]-'a'+1);
	for(i=1;i<=n;i++) cntx[a[i]]++;
	for(i=2;i<=n;i++) cntx[i]+=cntx[i-1];
	for(i=n;i>=1;i--) sa[cntx[a[i]]--]=i;
	rk[sa[1]]=1;
	for(i=2;i<=n;i++){
		rk[sa[i]]=rk[sa[i-1]];
		if(a[sa[i]]!=a[sa[i-1]]) rk[sa[i]]++;
	}
	for(j=1;rk[sa[n]]<n;j<<=1){
		for(i=0;i<=n;i++) cntx[i]=cnty[i]=0;
		for(i=1;i<=n;i++){
			x[i]=rk[i];
			y[i]=(i+j<=n)?rk[i+j]:0;
			cntx[x[i]]++;
			cnty[y[i]]++;
		}
		for(i=1;i<=n;i++){
			cntx[i]+=cntx[i-1];
			cnty[i]+=cnty[i-1];
		}
		for(i=n;i>=1;i--) tsa[cnty[y[i]]--]=i;
		for(i=n;i>=1;i--) sa[cntx[x[tsa[i]]]--]=tsa[i];
		rk[sa[1]]=1;
		for(i=2;i<=n;i++){
			rk[sa[i]]=rk[sa[i-1]];
			if(x[sa[i]]!=x[sa[i-1]]||y[sa[i]]!=y[sa[i-1]]) rk[sa[i]]++;
		}
	}
	for(i=1,j=0;i<=n;i++){
		if(j) j--;
		while(a[sa[rk[i]]+j]==a[sa[rk[i]-1]+j]&&sa[rk[i]]+j<=n) j++;
		height[rk[i]]=j;
	}
	for(i=2;i<=n;++i) lg[i]=lg[i>>1]+1;
	for(i=1;i<=n;++i) f[0][i]=height[i];
	for(i=1;i<17;++i){
		for(j=1;j<=n;++j) f[i][j]=min(f[i-1][j],f[i-1][j+(1<<(i-1))]);
	}
	build(root[0],1,n);
	for(i=1;i<=n;i++) insert(root[i],root[i-1],1,n,rk[i]);
	while(q--){
		int a,b,c,d;
		scanf("%d%d%d%d",&a,&b,&c,&d);
		int l=0,r=min(b-a+1,d-c+1),mid,ans;
		while(l<=r){
			mid=(l+r)/2;
			if(check(mid,a,b,c)) ans=mid,l=mid+1;
			else r=mid-1;
		}
		printf("%d\n",ans);
	}
	return 0;
}
