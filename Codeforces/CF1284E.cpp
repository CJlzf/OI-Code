#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cmath>
#define int long long
#define N 10002
using namespace std;
const long double PI=acos(-1.0L);
long double x[N],y[N],a[N];
int n,i,j;
long long ans;
signed main()
{
	scanf("%lld",&n);
	for(i=1;i<=n;i++) scanf("%Lf%Lf",&x[i],&y[i]);
	ans=1LL*n*(n-1)*(n-2)*(n-3)*(n-4)/24;
	for(i=1;i<=n;i++){
		int m=0,p=1;
		for(j=1;j<=n;j++){
			if(i==j) continue;
			a[++m]=atan2(x[j]-x[i],y[j]-y[i]);
		}
		sort(a+1,a+m+1);
		for(j=1;j<=m;j++){
			while(p<m+j){
				long double ang=a[(p%m)?p%m:m]-a[j];
				if(ang<0) ang+=2.0*PI;
				if(ang<PI) p++;
				else break;
			}
			ans-=1LL*(p-j-1)*(p-j-2)*(p-j-3)/6;
		}
	}
	printf("%lld\n",ans);
	return 0;
}
