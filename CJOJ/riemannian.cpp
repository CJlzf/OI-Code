#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;
const long long mod=998244353;
int T,i;
long long ansa,ansb,n;
long long read()
{
    char c=getchar();
    long long w=0;
    while(c<'0'||c>'9') c=getchar();
        while(c<='9'&&c>='0'){
	    w=w*10+c-'0';
	    c=getchar();
    }
    return w;
}
struct Matrix{
    int n,m;
    long long a[4][4];
}s,t;
Matrix operator * (Matrix a,Matrix b)
{
    Matrix c;
    memset(c.a,0,sizeof(c.a));
    for(int i=1;i<=a.n;i++){
    	for(int j=1;j<=a.m;j++){
	        for(int k=1;k<=b.n;k++) c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%mod)%mod;
	    }
    }
    c.n=a.n;c.m=a.m;
    return c;
}
Matrix poww(Matrix a,long long b)
{
    Matrix ans=a,base=a;
    b--;
    while(b){
	    if(b&1) ans=ans*base;
	    base=base*base;
	    b>>=1;
    }
    return ans;
}
signed main()
{
    T=read();
    s.n=1;s.m=3;
    s.a[1][3]=1;
    t.n=t.m=3;
    t.a[1][1]=t.a[1][2]=t.a[3][1]=2;
    t.a[2][1]=t.a[3][2]=t.a[3][3]=1;
    for(i=1;i<=T;i++) n[i]=read();
    sort(n+1,n+T+1);
    for(i=1;i<=T;i++){
        int k=n[i]-n[i-1];

    }
    printf("%lld %lld\n",ansa,ansb);
    return 0;
}