#include <iostream>
#include <cstdio>
#include <cstring>
#define N 2000002
using namespace std;
char a[N],b[N],s[N];
int n,m,i,j,k,nxt[N],match[N],ex[N];
int main()
{
	cin.getline(a+1,N);
	cin.getline(b+1,N);
	n=strlen(a+1);m=strlen(b+1);
	if(n!=m){
		puts("-1 -1");
		return 0;
	}
	for(i=1;i<=n;i++) s[i]=a[n-i+1];
	for(i=n+2;i<=2*n+1;i++) s[i]=b[i-n-1];
	for(i=2;i<=2*n+1;i++){
		int match=nxt[i-1];
		while(match!=0&&s[match+1]!=s[i]) match=nxt[match];
		if(s[match+1]==s[i]) match++;
		nxt[i]=match;
	}
	for(i=1;i<=n;i++) s[i]=b[i];
	for(i=n+2;i<=2*n+1;i++) s[i]=a[i-n-1];
	ex[1]=2*n+1;
	while(s[ex[2]+2]==s[ex[2]+1]&&ex[2]+2<=2*n+1) ex[2]++;
	int p=2;
	for(i=3;i<=2*n+1;i++){
		if(ex[i-p+1]<ex[p]+p-i) ex[i]=ex[i-p+1];
		else{
			j=max(0,p+ex[p]-i);
			while(s[i+j]==s[1+j]&&i+j<=2*n+1) j++;
			ex[i]=j;p=i;
		}
	}
	i=j=-1;
	for(k=1;k<=n;k++){
		int p1=ex[n+k+1]+k,p2=nxt[2*n+1-(k-1)];
		if(n-p1+1<=p2) i=k-2,j=n-p2;
		if(a[k]!=b[n-k+1]) break;
	}
	if(i==-1) puts("-1 -1");
	else printf("%d %d\n",i,j);
	return 0;
}
