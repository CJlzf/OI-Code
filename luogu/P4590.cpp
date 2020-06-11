#include <iostream>
#include <cstdio>
#include <cstring>
#define N 1002
using namespace std;
const int mod=1000000007;
char s[N];
int n,k,i,j,f[2][1<<15][3],x,g1[N],g2[N],cnt[1<<15],ans[N];
int count(int x)
{
	int ans=0;
	for(int i=0;(1<<i)<=x;i++){
		if(x&(1<<i)) ans++;
	}
	return ans;
}
void trans1(int x)
{
	for(int i=0;i<k;i++) g1[i+1]=(x>>i)&1;
	for(int i=1;i<=k;i++) g1[i]+=g1[i-1];
}
int trans2()
{
	int ans=0;
	for(int i=0;i<k;i++) ans|=((g2[i+1]-g2[i])<<i);
	return ans;
}
void dp(int x,int j,int l2,char c,int &v)
{
	trans1(j);
	for(int i=1;i<=k;i++) g2[i]=max(max(g1[i],g2[i-1]),g1[i-1]+(c==s[i]));
	int now=trans2();
	(f[x][now][l2]+=v)%=mod;
}
int main()
{
	scanf("%d%d%s",&n,&k,s+1);
	for(i=0;i<(1<<k);i++) cnt[i]=count(i);
	f[0][0][0]=1;
	for(i=1;i<=n;i++){
		x^=1;
		memset(f[x],0,sizeof(f[x]));
		for(j=0;j<(1<<k);j++){
			if(f[x^1][j][0]!=0){
				dp(x,j,1,'N',f[x^1][j][0]);
				dp(x,j,0,'O',f[x^1][j][0]);
				dp(x,j,0,'I',f[x^1][j][0]);
			}
			if(f[x^1][j][1]!=0){
				dp(x,j,1,'N',f[x^1][j][1]);
				dp(x,j,2,'O',f[x^1][j][1]);
				dp(x,j,0,'I',f[x^1][j][1]);
			}
			if(f[x^1][j][2]!=0){
				dp(x,j,1,'N',f[x^1][j][2]);
				dp(x,j,0,'O',f[x^1][j][2]);
			}
		}
	}
	for(i=0;i<(1<<k);i++){
		for(j=0;j<3;j++) ans[cnt[i]]=(ans[cnt[i]]+f[x][i][j])%mod;
	}
	for(i=0;i<=k;i++) printf("%d\n",ans[i]);
	return 0;
}
