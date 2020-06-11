#include <iostream>
#include <cstdio>
#include <cstring>
#define N 202
using namespace std;
const int mod=998244353;
int t,m,K,i,j,k,cnt=1,n1[N][N],n2[N][N][N],inv[10],ans[N];
long long n;;
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
	int a[N][N];
	int* operator [](int i) { return a[i]; }
}p[N];
Matrix operator * (Matrix a,Matrix b)
{
	Matrix c;
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++) c[i][j]=0;
	}
	for(int i=1;i<=cnt;i++){
		for(int j=1;j<=cnt;j++){
			__int128 t=0;
			for(int k=1;k<=cnt;k++) t+=1ll*a[i][k]*b[k][j];
			c[i][j]=t%mod;
		}
	}
	return c;
}
void multi(int x)
{
	int tmp[N]={0};
	for(int i=1;i<=cnt;i++){
		__int128 t=0;
		for(int j=1;j<=cnt;j++) t=t+1ll*ans[j]*p[x][j][i];
		tmp[i]=t%mod;
	}
	for(int i=1;i<=cnt;i++) ans[i]=tmp[i];
}
int poww(int a,int b)
{
	int ans=1,base=a;
	while(b){
		if(b&1) ans=1ll*ans*base%mod;
		base=1ll*base*base%mod;
		b>>=1;
	}
	return ans;
}
int main()
{
	t=read();m=read();K=read();
	for(i=1;i<=K+1;i++) inv[i]=poww(i,mod-2);
	p[0][1][1]=1;
	if(m==1){
		p[0][2][1]=p[0][2][2]=1;
		p[0][3][1]=p[0][3][2]=p[0][3][3]=inv[2];
		cnt=3;
	}
	else if(m==2){
		for(i=0;i<=K;i++){
			for(j=0;j<=K;j++){
				if(i+j<=K) n1[i][j]=++cnt;
			}
		}
		for(i=0;i<=K;i++){
			for(j=0;j<=K;j++){
				if(i+j<=K){
					long long x=inv[i+j+1];
					p[0][n1[i][j]][1]=p[0][n1[i][j]][n1[i][j]]=x;
					if(i) p[0][n1[i][j]][n1[i-1][j]]=x*i%mod;
					if(j){
						if(i+j<K) p[0][n1[i][j]][n1[i+1][j]]=x*j%mod;
						else p[0][n1[i][j]][n1[i+1][j-1]]=x*j%mod;
					}
				}
			}
		}
	}
	else if(m==3){
		for(i=0;i<=K;i++){
			for(j=0;j<=K;j++){
				for(k=0;k<=K;k++){
					if(i+j+k<=K) n2[i][j][k]=++cnt;
				}
			}
		}
		for(i=0;i<=K;i++){
			for(j=0;j<=K;j++){
				for(k=0;k<=K;k++){
					if(i+j+k<=K){
						long long x=inv[i+j+k+1];
						p[0][n2[i][j][k]][1]=p[0][n2[i][j][k]][n2[i][j][k]]=x;
						if(i) p[0][n2[i][j][k]][n2[i-1][j][k]]=x*i%mod;
						if(j){
							if(i+j+k<K) p[0][n2[i][j][k]][n2[i+1][j-1][k+1]]=x*j%mod;
							else p[0][n2[i][j][k]][n2[i+1][j-1][k]]=x*j%mod;
						}
						if(k){
							if(i+j+k<K) p[0][n2[i][j][k]][n2[i][j+1][k]]=x*k%mod;
							else p[0][n2[i][j][k]][n2[i][j+1][k-1]]=x*k%mod;
						}
					}
				}
			}
		}
	}
	for(i=1;i<=60;i++) p[i]=p[i-1]*p[i-1];
	for(i=1;i<=t;i++){
		n=read();
		memset(ans,0,sizeof(ans));
		ans[3]=1;
		for(j=0;(1LL<<j)<=n;j++){
			if(n&(1LL<<j)) multi(j);
		}
		printf("%lld\n",ans[1]);
	}
	return 0;
}
