#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1000002
using namespace std;
int n,i,j,a[N],b[N],f[N][2][2],cnta,cntb,tmp=1<<30,ans[N];
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
	for(i=1;i<=2*n;i++) a[i]=read();
	for(i=1;i<=2*n;i++) b[i]=read();
	f[1][0][0]=f[1][1][1]=1;
	for(i=2;i<=2*n;i++){
		if(a[i-1]<=a[i]){
			f[i][0][0]=max(f[i][0][0],f[i-1][0][0]+1);
			f[i][0][1]=max(f[i][0][1],f[i-1][0][1]);
		}
		if(b[i-1]<=a[i]){
			f[i][0][0]=max(f[i][0][0],f[i-1][1][0]+1);
			f[i][0][1]=max(f[i][0][1],f[i-1][1][1]);
		}
		if(a[i-1]<=b[i]){
			f[i][1][0]=max(f[i][1][0],f[i-1][0][0]);
			f[i][1][1]=max(f[i][1][1],f[i-1][0][1]+1);
		}
		if(b[i-1]<=b[i]){
			f[i][1][0]=max(f[i][1][0],f[i-1][1][0]);
			f[i][1][1]=max(f[i][1][1],f[i-1][1][1]+1);
		}
	}
	for(i=2*n;i>=1;i--){
		if(n<=f[i][0][0]+cnta&&n<=f[i][0][1]+cntb&&a[i]<=tmp){
			ans[i]=0;
			tmp=a[i];
			cnta++;
		}
		else if(n<=f[i][1][0]+cnta&&n<=f[i][1][1]+cntb&&b[i]<=tmp){
			ans[i]=1;
			tmp=b[i];
			cntb++;
		}
		else{
			puts("-1");
			return 0;
		}
	}
	for(i=1;i<=2*n;i++){
		if(ans[i]==0) putchar('A');
		else putchar('B');
	}
	puts("");
	return 0;
}
