#include <iostream>
#include <cstdio>
#include <cmath>
#include <algorithm>
#define N 602
using namespace std;
const int mod=1000000007;
int n,m,G,L,q,x,i,j,s[N],nums[1<<16],cnts,p[N],nump[N],cntp;
int f[N][1<<16],g[N][1<<16],h[N][1<<16],ans[1<<16];
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
int cal(int x)
{
	int s1=0,s2=0;
	for(int i=1;i<=cntp;i++){
		int cnt=0;
		while(x%p[i]==0) x/=p[i],cnt++;
		if(cnt==0) s1|=(1<<(i-1));
		else if(cnt==nump[i]) s2|=(1<<(i-1));
	}
	return s1|(s2<<cntp);
}
int poww(int a,int b)
{
	long long ans=1,base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod;
		b>>=1;
	}
	return ans;
}
void FWT(int *p,int op)
{
	for(int i=1;i<m;i<<=1){
		for(int q=i<<1,j=0;j<m;j+=q){
			for(int k=0;k<i;k++){
				if(op==1) p[i+j+k]=(p[i+j+k]+p[j+k])%mod;
				else p[i+j+k]=(p[i+j+k]-p[j+k]+mod)%mod;
			}
		}
	}
}
signed main()
{
	n=read();G=read();L=read();
	q=read();
	if(L%G){
		for(i=1;i<=q;i++) puts("0");
		return 0;
	}
	int L1=L,G1=G;
	n/=G;L/=G;
	int tmp=L;
	for(i=2;i<=tmp;i++){
		if(tmp%i==0){
			p[++cntp]=i;
			while(tmp%i==0) tmp/=i,nump[cntp]++;
		}
	}
	if(tmp>1) p[++cntp]=tmp,nump[cntp]=1;
	for(i=1;i<=n;i++){
		if(L%i==0){
		    int S=cal(i);
		    if(!nums[S]) s[++cnts]=S;
		    nums[S]++;
		}
	}
	sort(s+1,s+cnts+1);
	m=(1<<(2*cntp))-1;
	f[0][0]=g[cnts+1][0]=1;
	for(i=1;i<=cnts;i++){
		int p=(poww(2,nums[s[i]])-1+mod)%mod;
		for(j=0;j<=m;j++){
			f[i][j]=1LL*(f[i][j]+f[i-1][j])%mod;
			f[i][j|s[i]]=1LL*(f[i][j|s[i]]+1LL*f[i-1][j]*p%mod)%mod;
		}
	}
	for(i=cnts;i>=1;i--){
		int p=(poww(2,nums[s[i]])-1+mod)%mod;
		for(j=0;j<=m;j++){
			g[i][j]=1LL*(g[i][j]+g[i+1][j])%mod;
			g[i][j|s[i]]=1LL*(g[i][j|s[i]]+1LL*g[i+1][j]*p%mod)%mod;
		}
	}
	for(i=0;i<=cnts+1;i++) FWT(f[i],1),FWT(g[i],1);		
	for(i=1;i<=cnts;i++){
		for(j=0;j<=m;j++) h[i][j]=1LL*(h[i][j]+1LL*f[i-1][j]*g[i+1][j]%mod)%mod;
	}
	for(i=1;i<=cnts;i++) FWT(h[i],-1);
	for(i=1;i<=cnts;i++){
		for(j=0;j<=m;j++){
			if((j|s[i])==m) ans[i]=1LL*(ans[i]+h[i][j])%mod;
		}
		ans[i]=1LL*ans[i]*poww(2,nums[s[i]]-1)%mod;
	}
	while(q--){
		int x=read();
		if(x%G1||L1%x||x/G1>n) puts("0");
		else{
			x/=G1;
			int S=cal(x);
			int pos=lower_bound(s+1,s+cnts+1,S)-s;
			printf("%lld\n",ans[pos]);
		}
	}
	return 0;
}