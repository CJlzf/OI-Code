#include <iostream>
#include <cstdio>
#include <cstring>
#define int long long
#define N 100002
using namespace std; 
const int mod=1000000007;
const int p=233;
char s[N];
int t,n,i,l,hash[N],a[N],b[N],poww[N];
int get(int l,int r)
{
	return (hash[r]-hash[l-1]*poww[r-l+1]%mod+mod)%mod;
}
int check2(int p1,int p2)
{
	int l=0,r=p1-p2+1,mid,ans;
	while(l<=r){
		mid=(l+r)/2;
		if(get(p1,p1+mid-1)==get(p2,p2+mid-1)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
int check1(int p1,int p2)
{
	int l=0,r=p1-p2+1,mid,ans;
	while(l<=r){
		mid=(l+r)/2;
		if(get(p1-mid+1,p1)==get(p2-mid+1,p2)) ans=mid,l=mid+1;
		else r=mid-1;
	}
	return ans;
}
signed main()
{
	scanf("%lld",&t);
	while(t--){
		memset(a,0,sizeof(a));
		memset(b,0,sizeof(b));
		memset(hash,0,sizeof(hash));
		scanf("%s",s+1);
		n=strlen(s+1);
		for(i=1,poww[0]=1;i<=n;i++) poww[i]=poww[i-1]*p%mod;
		for(i=1;i<=n;i++) hash[i]=(hash[i-1]*p%mod+(int)(s[i]-'a'+1))%mod;
		for(l=1;l<=n;l++){
			for(i=l*2;i<=n;i+=l){
				int p1=i,p2=i-l,lcs=check1(p1,p2),lcp=check2(p1,p2);
				lcs=min(lcs,l);lcp=min(lcp,l);
				if(lcp+lcs>=l+1){
					int same=lcs+lcp-l-1;
					a[p2-lcs+1]++;b[p2-lcs+2*l]++;
					if(p2-lcs+same+2<=n) a[p2-lcs+same+2]--;
					if(p2-lcs+same+2*l+1<=n) b[p2-lcs+same+2*l+1]--;
				}
			}
		}
		for(i=1;i<=n;i++) a[i]+=a[i-1];
		for(i=1;i<=n;i++) b[i]+=b[i-1];
		int ans=0;
		for(i=1;i<=n;i++) ans+=b[i]*a[i+1];
		printf("%lld\n",ans);
	}
	return 0;
} 
