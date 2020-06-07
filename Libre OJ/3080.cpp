#include <iostream>
#include <cstdio>
#define N 602
#define ll long long
using namespace std;
const int mod=998244353;
int dx[8]={-2,-1,1,2,2,1,-1,-2},dy[8]={-1,-2,-2,-1,1,2,2,1};
int n,m,q,i,j,k,l;
ll  w[9],g[N][N],a[202][202][N],cnt,c[N][N],b[N],x[N];
ll sumw;
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
ll poww(ll a,ll b)
{
	ll ans=1,base=a;
	while(b){
		if(b&1) ans=1LL*ans*base%mod;
		base=1LL*base*base%mod;
		b>>=1;
	}
	return ans;
}
bool in(int x,int y)
{
	return (x>=1&&x<=n&&y>=1&&y<=m);
}
void Gauss(int n)
{
	for(int i=1;i<=n;i++){
		for(int j=i;j<=n;j++){
			if(c[j][i]>0){
				for(int k=1;k<=n;k++) swap(c[i][k],c[j][k]);
				swap(b[i],b[j]);
			}
		}
		for(int j=1;j<=n;j++){
			if(i==j) continue;
			int t=1ll*c[j][i]*poww(c[i][i],mod-2)%mod;
			for(int k=i;k<=n;k++) c[j][k]=1LL*(c[j][k]-c[i][k]*t%mod+mod)%mod;
			b[j]=1LL*(b[j]-b[i]*t%mod+mod)%mod;
		}
	}
	for(int i=1;i<=n;i++) x[i]=1LL*b[i]*poww(c[i][i],mod-2)%mod;
}
signed main()
{
	n=read();m=read();
	for(i=0;i<8;i++) w[i]=read(),sumw+=w[i];
	sumw=poww(sumw,mod-2);
	for(i=0;i<8;i++) w[i]=1LL*w[i]*sumw%mod;
	ll inv=poww(w[4],mod-2);
	for(i=1;i<=2;i++){
		for(j=1;j<=m;j++) a[i][j][++cnt]=1;
	}
	for(i=3;i<=n;i++) a[i][1][++cnt]=1;
	for(i=1;i<=n;i++){
		for(j=1;j<=m;j++){
			int x=i+dx[4],y=j+dy[4];
			for(k=1;k<=cnt+1;k++) a[x][y][k]=1LL*(a[x][y][k]+a[i][j][k])%mod;
			for(k=0;k<8;k++){
				if(k==4) continue;
				int tx=i+dx[k],ty=j+dy[k];
				if(in(tx,ty)){
					for(l=1;l<=cnt+1;l++) a[x][y][l]=1LL*(a[x][y][l]-a[tx][ty][l]*w[k]%mod+mod)%mod;
				}
			}
			a[x][y][cnt+1]=1LL*(a[x][y][cnt+1]+mod-1)%mod;
			for(k=1;k<=cnt+1;k++) a[x][y][k]=1LL*a[x][y][k]*inv%mod;
		}
	}
	int tot=0;
	for(i=n+1;i<=n+2;i++){
		for(j=2;j<=m+1;j++){
			tot++;
			for(k=1;k<=cnt;k++) c[tot][k]=a[i][j][k];
			b[tot]=1LL*(mod-a[i][j][cnt+1])%mod;
		}
	}
	for(i=3;i<=n;i++){
		tot++;
		for(k=1;k<=cnt;k++) c[tot][k]=a[i][m+1][k];
		b[tot]=1LL*(mod-a[i][m+1][cnt+1])%mod;
	}
	Gauss(cnt);
	q=read();
	while(q--){
		int sx=read(),sy=read();ll ans=0;
		for(i=1;i<=cnt;i++) ans=1LL*(ans+a[sx][sy][i]*x[i]%mod)%mod;
		ans=(ans+a[sx][sy][cnt+1])%mod;
		printf("%lld\n",ans);
	}
	return 0;
}
