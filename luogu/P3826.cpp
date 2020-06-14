#include <iostream>
#include <cstdio>
#include <queue>
#define int long long
#define N 1000002
using namespace std;
priority_queue<pair<int,int> > q;
int n,m,k,l=100000,i,j,a[N],s[N],c[N],x[N],fa[N],ret[N],ans[N];
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
int find(int x)
{
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}
signed main()
{
	n=read();m=read();k=read();
	for(i=1;i<=n;i++){
		a[i]=read();s[i]=read();c[i]=read();x[i]=read();
		q.push(make_pair(a[i]+s[i],i));
	}
	for(i=1;i<=l;i++) fa[i]=i,ret[i]=m;
	while(!q.empty()){
		int i=q.top().second,val=q.top().first,d;
		q.pop();
		if(x[i]==0) d=find(l);
		else d=find(min(l,(c[i]-1)/x[i]+1));
		if(d==0) continue;
		c[i]--;ret[d]--;
		if(ret[d]==0) fa[d]=find(d-1);
		j++;
		ans[j]=ans[j-1]+val;
		if(c[i]!=0) q.push(make_pair(a[i],i));
	}
	for(i=1;i<=k;i++){
		int p=read();
		printf("%lld\n",ans[min(j,m*p)]);
	}
	return 0;
}
