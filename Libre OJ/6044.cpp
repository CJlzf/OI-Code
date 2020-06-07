#include <iostream>
#include <cstdio>
#define int long long
#define N 500002
using namespace std;
int n,k,mod,i,fac[N];
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
	return fac[n]*poww(fac[m],mod-2)%mod*poww(fac[n-m],mod-2)%mod;
}
signed main()
{
	scanf("%lld%lld%lld",&n,&k,&mod);
	fac[0]=1;
	for(i=1;i<=n;i++) fac[i]=fac[i-1]*i%mod;
	int ans=poww(k,n-k-1)*poww(n-k,k-1)%mod;
	printf("%lld\n",ans*C(n-1,k-1)%mod);
	return 0;
}
