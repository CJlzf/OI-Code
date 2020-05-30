#include <iostream>
#include <cstdio>
#define N 100002
using namespace std;
int n,m,i,l[N],r[N];
double d[N],s[N];
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
int main()
{
    n=read();
    for(i=1;i<=n;i++){
        l[i]=read();r[i]=read();
        m=max(m,r[i]);
    }
    m++;
    for(i=1;i<=n;i++){
        d[l[i]+1]+=1.0/(r[i]-l[i]);
        d[r[i]+1]-=1.0/(r[i]-l[i]);
    }
    for(i=1;i<=m;i++) d[i]+=d[i-1];
    for(i=1;i<=m;i++) s[i]=s[i-1]+d[i];
    for(i=1;i<=m;i++) s[i]=s[i-1]+(s[i]+s[i+1])/2;
    for(i=1;i<=n;i++){
        double ans=1.0*n-(s[r[i]-1]-s[l[i]-1])/(r[i]-l[i])+0.5;
        printf("%.8lf\n",ans);
    }
    return 0;
}