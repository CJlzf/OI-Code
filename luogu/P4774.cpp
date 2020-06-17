#include <iostream>
#include <cstdio>
#include <cstring>
#include <set>
#define int __int128
#define N 1000002
using namespace std;
multiset<int> s;
int T,n,m,i,a[N],p[N],b1[N],b[N],c[N],P[N],C[N];
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
bool check1()
{
	for(int i=1;i<=n;i++){
		if(p[i]!=1) return 0;
	}
	return 1;
}
bool check2()
{
	for(int i=1;i<=n;i++){
		if(a[i]!=p[i]) return 0;
	}
	return 1;
}
void print(int x)
{
	if(x==-1){
		printf("-1");
		return;
	}
	if(!x) return;
	print(x/10);
	putchar((char)(x%10+'0'));
}
int gcd(int a,int b)
{
	if(b==0) return a;
	return gcd(b,a%b);
}
void exgcd(int a,int b,int &x,int &y)
{
	if(b==0){
		x=1,y=0;
		return;
	}
	exgcd(b,a%b,x,y);
	int tmp=x;
	x=y;
	y=tmp-(a/b)*y;
}
int exCRT()
{
	int c=C[1],p=P[1];
	for(int i=1;i<n;i++){
		if(C[i+1]<C[i]) swap(C[i],C[i+1]),swap(P[i],P[i+1]);
		int g=gcd(P[i],P[i+1]),inv,y;
		exgcd(P[i]/g,P[i+1]/g,inv,y);
		while(inv<0) inv+=P[i+1]/g;
		if((C[i+1]-C[i])%g!=0) return -1;
		c=((C[i+1]-C[i])/g)*inv%(P[i+1]/g)*P[i]+C[i];
		p=P[i]*P[i+1]/g;
		C[i+1]=c%p;P[i+1]=p;
	}
	return c;
}
signed main()
{
	T=read();
	while(T--){
		bool flag=1;
		s.clear();
		n=read();m=read();
		for(i=1;i<=n;i++) a[i]=read();
		for(i=1;i<=n;i++) p[i]=read();
		for(i=1;i<=n;i++) b1[i]=read();
		for(i=1;i<=m;i++){
			b[i]=read();
			s.insert(b[i]);
		}
		for(i=1;i<=n;i++){
			multiset<int>::iterator it=s.upper_bound(a[i]);
			if(it!=s.begin()) it--;
			int atk=(*it),sx=0,sy=0;
			s.erase(it);
			s.insert(b1[i]);
			if(a[i]%gcd(atk,p[i])!=0) flag=0;
			exgcd(atk,p[i],sx,sy);
			C[i]=sx*(a[i]/gcd(atk,p[i]));
			P[i]=p[i]/gcd(atk,p[i]);
			C[i]=C[i]%P[i]+P[i];C[i]%=P[i];
			c[i]=atk;
			if(a[i]==p[i]) C[i]=0,P[i]=1;
		}
		int ans=0;
		if(!flag) ans=-1;
		else if(check1()){
			for(i=1;i<=n;i++) ans=max(ans,a[i]/c[i]+(a[i]%c[i]!=0));
		}
		else if(check2()){
			ans=1;
			int x,y;
			for(i=1;i<=n;i++){
				exgcd(c[i],p[i],x,y);
				ans=ans*x/gcd(ans,x);
			}
		}
		else ans=exCRT();
		print(ans);
		puts("");
	}
	return 0;
}
