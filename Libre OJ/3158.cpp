#include <iostream>
#include <cstdio>
#include <cstring>
#define N 200002
using namespace std;
int T,n,k,l,i,a[N],b[N];
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
    T=read();
    while(T--){
        n=read();k=read();l=read();
        for(i=1;i<=n;i++) a[i]=read();
        for(i=1;i<=n;i++) b[i]=read();
    }
}