#include <iostream>
#include <cstdio>
#include <cstring>
#include <vector>
#define int long long
#define N 2502
using namespace std;
const int mod=998244353;
int t,n,c,m,b[N],s[N],p[N],c0,c1,d0,d1,i,j,k,l;
int f[N],g[N],sum[N],f1[N][N],g1[N][N],cnt1,cnt2,S;
bool tag[N];
vector<int> v[N];
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
signed main()
{
	t=read();
	while(t--){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		memset(f1,0,sizeof(f1));
		memset(g1,0,sizeof(g1));
		memset(p,-1,sizeof(p));
		memset(sum,0,sizeof(sum));
		memset(tag,0,sizeof(tag));
		n=read();c=read();
		c0=read();c1=read();d0=read();d1=read();
		S=cnt1=cnt2=0;
		for(i=1;i<=c;i++) v[i].clear();
		for(i=1;i<=n;i++){
			b[i]=read();s[i]=read();
			sum[b[i]]+=s[i];
			v[b[i]].push_back(i);
			S+=s[i];
		}
		m=read();
		for(i=1;i<=m;i++){
			int x=read();
			p[x]=read();
			tag[b[x]]=1;
		}
		f[0]=g[0]=1;
		for(i=1;i<=c;i++){
			if(!tag[i]&&sum[i]!=0){
				for(j=c0;j>=sum[i];j--) f[j]=(f[j]+f[j-sum[i]])%mod;
			}
		}
		for(i=1;i<=n;i++){
			if(p[i]==-1){
				for(j=d0;j>=s[i];j--) g[j]=(g[j]+g[j-s[i]])%mod;
			}
		}
		for(i=1;i<=c0;i++) f[i]=(f[i-1]+f[i])%mod;
		for(i=1;i<=d0;i++) g[i]=(g[i-1]+g[i])%mod;
		f1[0][0]=1;
		for(i=1;i<=c;i++){
			if(tag[i]){
				cnt1=(cnt1+sum[i]<=c0)?cnt1+sum[i]:c0;
				for(j=0;j<=cnt1;j++){
					for(k=0;k<=cnt2;k++) g1[j][k]=f1[j][k];
				}
				for(j=0;j<v[i].size();j++){
					int x=v[i][j];
					if(p[x]!=-1){
						cnt2=(cnt2+s[x]<=d0)?cnt2+s[x]:d0;
						if(p[x]==1){
							for(k=0;k<=cnt1;k++){
								for(l=cnt2;l>=s[x];l--) f1[k][l]=f1[k][l-s[x]];
								for(l=s[x]-1;l>=0;l--) f1[k][l]=0;
							}
						}
						else if(p[x]>=2){
							for(k=0;k<=cnt1;k++){
								for(l=cnt2;l>=s[x];l--) f1[k][l]=(f1[k][l]+f1[k][l-s[x]])%mod;
							}
						}
						if(p[x]==3){
							for(k=0;k<=cnt1;k++){
								for(l=cnt2;l>=s[x];l--) g1[k][l]=g1[k][l-s[x]];
								for(l=s[x]-1;l>=0;l--) g1[k][l]=0;
							}
						}
						else if(p[x]<=1){
							for(k=0;k<=cnt1;k++){
								for(l=cnt2;l>=s[x];l--) g1[k][l]=(g1[k][l]+g1[k][l-s[x]])%mod;
							}
						}
					}
				}
				for(j=0;j<=cnt2;j++){
					for(k=cnt1;k>=sum[i];k--) f1[k][j]=f1[k-sum[i]][j];
					for(k=0;k<sum[i];k++) f1[k][j]=0;
				}
				for(j=0;j<=cnt1;j++){
					for(k=0;k<=cnt2;k++) f1[j][k]=(f1[j][k]+g1[j][k])%mod;
				}
			}
		}
		int ans=0;
		for(i=0;i<=cnt1;i++){
			for(j=0;j<=cnt2;j++){
				int l1=max(0LL,S-c1-i),r1=c0-i;
				int l2=max(0LL,S-d1-j),r2=d0-j;
				if(r1<l1||r2<l2) continue;
				int sumf=(f[r1]-f[l1-1]+mod)%mod,sumg=(g[r2]-g[l2-1]+mod)%mod;
				ans=(ans+sumf*sumg%mod*f1[i][j]%mod)%mod;
			}
		}
		printf("%lld\n",ans);
	}
	return 0;
}
