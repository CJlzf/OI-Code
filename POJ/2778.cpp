#include <iostream>
#include <cstdio>
#include <cstring>
#include <string>
#include <queue>
#define int long long
using namespace std;
const int mod=100000;
struct Matrix{
	int a[102][102],n,m;
}f;
struct AC{
	int val,fa,son[4],s;
	bool e;
}t[102];
int n,m,cnt,i,j;
string s;
Matrix operator * (Matrix a,Matrix b){
	Matrix c;
	memset(c.a,0,sizeof(c.a));
	c.n=a.n;c.m=a.m;
	for(int i=0;i<=c.n;i++){
		for(int k=0;k<=b.n;k++){
			if(!a.a[i][k]) continue;
			for(int j=0;j<=c.m;j++){
				if(!b.a[k][j]) continue;
				c.a[i][j]=(c.a[i][j]+a.a[i][k]*b.a[k][j]%mod)%mod;
			}
		}
	}
	return c;
}
int get(char c)
{
	if(c=='A') return 0;
	if(c=='T') return 1;
	if(c=='C') return 2;
	return 3;
}
void insert(string s)
{
	int l=s.length(),k=0;
	for(int i=0;i<l;i++){
		AC &node=t[k];
		int p=get(s[i]);
		if(!node.son[p]){
			cnt++;
			t[cnt].val=p;
			t[cnt].fa=k;
			node.son[p]=cnt;
		}
		k=node.son[p];
		if(i==l-1) t[k].e=1;
	}
}
void bfs()
{
	queue<int> q;
	q.push(0);
	while(!q.empty()){
		int x=q.front();
		q.pop();
		int suf=t[x].fa?t[t[t[x].fa].s].son[t[x].val]:0;
		AC &node=t[x];
		if(t[suf].e) node.e=1;
		for(int i=0;i<4;i++){
			int y=node.son[i];
			if(y) q.push(y);
			else node.son[i]=t[suf].son[i];
		}
		node.s=suf;
	}
}
Matrix poww(Matrix a,int b)
{
	Matrix ans=a,base=a;
	b--;
	while(b){
		if(b&1) ans=ans*base;
		base=base*base;
		b>>=1;
	}
	return ans;
}
signed main()
{
	cin>>m>>n;
	for(i=1;i<=m;i++){
		cin>>s;
		insert(s);
	}
	bfs();
	for(i=0;i<=cnt;i++){
		for(j=0;j<4;j++){
			if(!t[t[i].son[j]].e) f.a[i][t[i].son[j]]++;
		}
	}
	f.n=f.m=cnt;
	f=poww(f,n);
	int ans=0;
	for(i=0;i<=cnt;i++) ans=(ans+f.a[0][i])%mod;
	printf("%lld\n",ans);
	return 0;
}
