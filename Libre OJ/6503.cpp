#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#include <queue>
#define int long long
#define N 200002
using namespace std;
const int mod=998244353;
const int G=3;
vector<int> h[N];
priority_queue<pair<int,int> > q;
int n,m,k,i,j,fac[N],inv[N],p,lim,r[N],a[N],f[N],g[N],F[N];
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
int poww(int a,int b)
{
	int ans=1,base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
int C(int n,int m)
{
	return fac[n]*inv[m]%mod*inv[n-m]%mod;
}
void NTT(int *a,int n,int inv)
{
	for(int i=0;i<n;i++){
		if(i<r[i]) swap(a[i],a[r[i]]);
	}
	for(int l=2;l<=n;l<<=1){
		int mid=l/2;
		int cur=poww(G,(mod-1)/l);
		if(inv==-1) cur=poww(cur,mod-2);
		for(int i=0;i<n;i+=l){
			int omg=1;
			for(int j=0;j<mid;j++,omg=omg*cur%mod){
				int tmp=omg*a[i+j+mid]%mod;
				a[i+j+mid]=(a[i+j]-tmp+mod)%mod;
				a[i+j]=(a[i+j]+tmp)%mod;
			}
		}
	}
}
signed main()
{
	m=read();n=read();k=read();
	for(i=1;i<=m;i++) a[i]=read();
	for(i=fac[0]=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	inv[n]=poww(fac[n],mod-2);
	for(i=n-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for(i=1;i<=m;i++){
		q.push(make_pair(-a[i],i));
		for(j=0;j<a[i];j++) h[i].push_back(C(a[i],j)*fac[a[i]-1]%mod*inv[a[i]-j-1]%mod);
	}
	while(q.size()>1){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		int x=q.top().second,lx=-q.top().first;q.pop();
		int y=q.top().second,ly=-q.top().first;q.pop();
		for(i=0;i<h[x].size();i++) f[i]=h[x][i];
		for(i=0;i<h[y].size();i++) g[i]=h[y][i];
		h[x].clear();vector<int>().swap(h[x]);
		h[y].clear();vector<int>().swap(h[y]);
		int len=1,lim=0;
		while(len<lx+ly) len<<=1,lim++;
		for(i=0;i<len;i++) r[i]=(r[i>>1]>>1)|((i&1)<<(lim-1));
		NTT(f,len,1);NTT(g,len,1);
		for(i=0;i<len;i++) f[i]=f[i]*g[i]%mod;
		NTT(f,len,-1);
		int Inv=poww(len,mod-2);
		for(i=0;i<lx+ly-1;i++) h[x].push_back(f[i]*Inv%mod);
		q.push(make_pair(-lx-ly+1,x));
	}
	int x=q.top().second;
	for(i=0;i<h[x].size();i++) f[i]=h[x][i];
	for(i=0;i<=n;i++) F[i]=f[i]*fac[n-i]%mod;
	int ans=0;
	for(i=k;i<=n;i++){
		int tmp=C(i,k)*F[i]%mod;
		if((i-k)%2) ans=(ans-tmp+mod)%mod;
		else ans=(ans+tmp)%mod;
	}
	for(i=1;i<=m;i++) ans=ans*inv[a[i]]%mod;
	printf("%lld\n",ans);
	return 0;
}
