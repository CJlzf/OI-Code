#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
#define N 100002
#define M 1502
using namespace std;
const int mod=1000000007;
int n,m,a,b,k,p,i,j,x,suml[M][M],l[M][M],f[N],d[N],sum1[N],sum2[N],fac[N],inv[N];
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
signed main()
{
	scanf("%lld%lld%lld%lld%lld",&n,&m,&a,&b,&k);
	p=a*poww(b,mod-2)%mod;
	for(i=1,fac[0]=1;i<=k;i++) fac[i]=fac[i-1]*i%mod;
	inv[k]=poww(fac[k],mod-2);
	for(i=k-1;i>=0;i--) inv[i]=inv[i+1]*(i+1)%mod;
	for(i=0;i<=k;i++) d[i]=C(k,i)*poww(p,i)%mod*poww((1-p+mod)%mod,k-i)%mod;
	suml[0][m]=f[0]=1;
	for(i=1;i<=m;i++) sum1[i]=(sum1[i-1]+d[i-1])%mod;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++) sum2[j]=(sum2[j-1]+d[j-1]*l[i-1][j]%mod)%mod;
		for(j=1;j<=m;j++) suml[i][j]=d[m-j]*(((f[i-1]-l[i-1][m-j+1]+mod)%mod*sum1[j]%mod-sum2[j]+mod)%mod)%mod;
		for(j=1;j<=m;j++){
			l[i][j]=(l[i][j-1]+suml[i][j-1])%mod;
			f[i]=(f[i]+suml[i][j])%mod;
		}
	}
	printf("%lld\n",f[n]);
	return 0;
}
