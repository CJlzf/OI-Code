#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long 
#define N 5002
using namespace std;
int n,m,k,a[N],b1[N],b2[N],cnt1,cnt2,i,j;
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
int gcd(int a,int b)
{
    if(a%b) return gcd(b,a%b);
    return b;
}
int my_comp(const int &a,const int &b)
{
    return a>b;
}
signed main()
{
    n=read();
    for(i=1;i<=n;i++) a[i]=read();
    sort(a+1,a+n+1,my_comp);
    m=read();
    while(m--){
        int ans=0;
        k=read();
        if(k==0){
            for(i=1;i<=n;i++) ans+=a[i]*a[i];
        }
        else{
            int l=n/gcd(n,k);
            for(i=1;i<=n;i+=l){
                cnt1=cnt2=0;
                for(j=i;j<=i+l-1;j++){
                    if((j-i+1)%2) b1[++cnt1]=a[j];
                    else b2[++cnt2]=a[j];
                }		
                for(j=1;j<=cnt2;j++) b1[++cnt1]=b2[cnt2-j+1];
                for(j=1;j<=cnt1;j++){
                    if(j<cnt1) ans+=b1[j]*b1[j+1];
                    else ans+=b1[j]*b1[1];
                }
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
