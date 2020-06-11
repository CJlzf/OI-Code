#include <iostream>
#include <cstdio>
#include <algorithm>
#define int long long
#define N 100002
using namespace std;
struct point{
	int x,y;
}a[N],b[N],c[N],e1[N],e2[N];
int n,m,q,cnt,i;
int operator * (point a,point b){return a.x*b.y-a.y*b.x;}
point operator + (point a,point b){return (point){a.x+b.x,a.y+b.y};}
point operator - (point a,point b){return (point){a.x-b.x,a.y-b.y};}
int read()
{
	char c=getchar();
	int w=0,f=1;
	while(c<'0'||c>'9'){
		if(c=='-') f=-1;
		c=getchar();
	}
	while(c<='9'&&c>='0'){
		w=w*10+c-'0';
		c=getchar();
	}
	return w*f;
}
int cmp1(const point &a,const point &b)
{
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}
int cmp2(const point &a,const point &b)
{
	int la=a.x*a.x+a.y*a.y,lb=b.x*b.x+b.y*b.y;
	if(a*b==0) return la<lb;
	return a*b>0;
}
void Convex(point *a,int &n)
{
	sort(a+1,a+n+1,cmp1);
	point v=a[1];
	for(int i=1;i<=n;i++) a[i]=a[i]-v;
	sort(a+2,a+n+1,cmp2);
	int top=0,s[N];
	s[++top]=1;
	for(int i=2;i<=n;i++){
		while(top>=2&&(a[i]-a[s[top-1]])*(a[s[top]]-a[s[top-1]])>=0) top--;
		s[++top]=i;
	}
	for(int i=1;i<=top;i++) a[i]=a[s[i]]+v;
	n=top;
}
void Minkowski()
{
	for(int i=1;i<n;i++) e1[i]=a[i+1]-a[i];
	for(int i=1;i<m;i++) e2[i]=b[i+1]-b[i];
	e1[n]=a[1]-a[n];e2[m]=b[1]-b[m];
	int i=1,j=1;
	c[++cnt]=a[1]+b[1];
	while(i<=n&&j<=m){
		cnt++;
		if(e1[i]*e2[j]>=0) c[cnt]=c[cnt-1]+e1[i],i++;
		else c[cnt]=c[cnt-1]+e2[j],j++;
	}
	while(i<=n) cnt++,c[cnt]=c[cnt-1]+e1[i],i++;
	while(j<=m) cnt++,c[cnt]=c[cnt-1]+e2[j],j++;
}
signed main()
{
	n=read();m=read();q=read();
	for(i=1;i<=n;i++) a[i].x=read(),a[i].y=read();
	for(i=1;i<=m;i++) b[i].x=-read(),b[i].y=-read();
	Convex(a,n);Convex(b,m);
	Minkowski();
	Convex(c,cnt);
	point tmp=c[1];
	for(i=1;i<=cnt;i++) c[i]=c[i]-tmp;
	for(i=1;i<=q;i++){
		point v;
		v.x=read();v.y=read();
		v=v-tmp;
		if(v*c[2]>0||c[cnt]*v>0) puts("0");
		else{
			int pos=lower_bound(c+1,c+cnt+1,v,cmp2)-c;
			if((c[pos>1?pos-1:n]-c[pos])*(v-c[pos])>0) puts("0");
			else puts("1");
		}
	}
	return 0;
}
