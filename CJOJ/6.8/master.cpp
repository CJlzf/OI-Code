#include <bits/stdc++.h>
#define N 500002
using namespace std;
const int Mod=49999991;
int P,mod;
struct Hash{
	int id[Mod+2],stk[Mod+2],top; 
	Hash(){top=0;}
	void clear()
	{ 
		while(top) id[stk[top--]]=0; 
	}
	void insert(int x,int num)
	{
		id[x]=num;
		stk[++top]=x;
	}
	int find(int x) { return id[x]; }
}d; 
struct matrix{
	int x1,y1,x2,y2;
}a[N];
struct node{
	int x,id,op;
}p[2*N];
int n,X,Y,i,bx[2*N],by[2*N],mx,my,poww[N];
long long ans1,ans2,cnt[2*N];
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
int my_comp(const node &a,const node &b)
{
	return a.x<b.x;
}
long long solve(int *b,int lim)
{
	memset(cnt,0,sizeof(cnt));
	int num=0;
	long long ans=0,s=0;
	d.clear();
	sort(p+1,p+2*n+1,my_comp);
	p[2*n+1].x=lim;
	d.insert(s,++num);cnt[num]+=b[p[1].x];
	int i=1,j=1;
	while(i<=2*n){
		j=i;
		while(j<2*n&&p[j+1].x==p[j].x) j++;
		for(int k=i;k<=j;k++){
			if(p[k].op==1) s=(s+poww[p[k].id-1])%mod;
			else s=(s-poww[p[k].id-1]+mod)%mod;
		}
		if(!d.find(s)) d.insert(s,++num);
		cnt[d.find(s)]+=b[p[j+1].x]-b[p[i].x];
		i=j+1;
	}
	for(int i=1;i<=num;i++) ans=max(ans,cnt[i]);
	return ans;
}
signed main()
{
	srand(time(0));
	mod=49999991;P=233;
	n=read();X=read();Y=read();
	bx[++mx]=0;bx[++mx]=X;
	by[++my]=0;by[++my]=Y;
	poww[0]=1;
	for(i=1;i<=n;i++) poww[i]=1LL*poww[i-1]*P%mod;
	for(i=1;i<=n;i++){
		int x1=read(),y1=read(),x2=read(),y2=read();
		a[i].x1=min(x1,x2);a[i].y1=min(y1,y2);
		a[i].x2=max(x1,x2);a[i].y2=max(y1,y2);
		bx[++mx]=a[i].x1;bx[++mx]=a[i].x2;
		by[++my]=a[i].y1;by[++my]=a[i].y2;
	}
	sort(bx+1,bx+mx+1);
	sort(by+1,by+my+1);
	mx=unique(bx+1,bx+mx+1)-bx-1;
	my=unique(by+1,by+my+1)-by-1;
	for(i=1;i<=n;i++){
		a[i].x1=lower_bound(bx+1,bx+mx+1,a[i].x1)-bx;
		a[i].x2=lower_bound(bx+1,bx+mx+1,a[i].x2)-bx;
		a[i].y1=lower_bound(by+1,by+my+1,a[i].y1)-by;
		a[i].y2=lower_bound(by+1,by+my+1,a[i].y2)-by;
	}
	for(i=1;i<=n;i++){
		p[2*i-1]=(node){a[i].y1,i,1};
		p[2*i]=(node){a[i].y2,i,-1};
	}
	ans1=solve(by,my);
	for(i=1;i<=n;i++){
		p[2*i-1]=(node){a[i].x1,i,1};
		p[2*i]=(node){a[i].x2,i,-1};
	}
	ans2=solve(bx,mx);
	printf("%lld\n",ans1*ans2);
	return 0;
}
