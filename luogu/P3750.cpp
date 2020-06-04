#include <iostream>
#include <cstdio>
#define int long long
#define N 100002
using namespace std;
const int mod=100003;
int n,k,i,j,a[N],f[N],cnt,ans;
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
signed main()
{
	n=read();k=read();
	for(i=1;i<=n;i++) a[i]=read();
	for(i=n;i>=1;i--){
		if(a[i]){
			cnt++;
			for(j=1;j*j<=i;j++){
				if(i%j==0){
					a[j]^=1;
					if(j*j!=i) a[i/j]^=1;
				}
			}
		}
	}
	for(i=n;i>=1;i--){
		f[i]=(f[i+1]*(n-i)%mod+n)%mod;
		f[i]=f[i]*poww(i,mod-2)%mod;
	}
	if(cnt<=k) ans=cnt;
	else{
		for(i=cnt;i>k;i--) ans=(ans+f[i])%mod;
		ans=(ans+k)%mod;
	}
	for(i=1;i<=n;i++) ans=ans*i%mod;
	printf("%lld\n",ans);
	return 0;
}
