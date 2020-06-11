#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 5000002
using namespace std;
struct node{
	int x,y,r,d;
}a[N];
int n,i,j,k,l,u,d=1<<30,pre[N],nxt[N],head=1,cnt[N],q[N],t;
double ans;
bool vis[N];
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
	if(a.y==b.y) return a.x<b.x;
	return a.y<b.y;
}
void del(int x)
{
	if(head==x) head=nxt[x];
	nxt[pre[x]]=nxt[x];
	pre[nxt[x]]=pre[x];
	vis[x]=1;
}
int main()
{
	n=read();
	for(i=1;i<=n;i++){
		a[i].x=read();a[i].y=read();a[i].d=read();
		a[i].r=a[i].x+a[i].d;
		pre[i]=i-1;nxt[i]=i+1;
		d=min(d,a[i].y);
		u=max(u,a[i].y+a[i].d);
	}
	sort(a+1,a+n+1,my_comp);
	int now=0,last;
	for(i=1;i<=n&&a[i].y==d;i++){
		for(j=a[i].x;j<a[i].r;j++){
			if(!cnt[j]) now++;
			cnt[j]++;
		}
	}
	for(i=d+1;i<=u;i++){
		last=now;t=0;
		for(j=head;j<=n&&a[j].y<i;j=nxt[j]){
			a[j].r--;
			if(a[j].r==a[j].x-1) del(j);
			else{
				if(cnt[a[j].r]==1) now--;
				cnt[a[j].r]--;
				q[++t]=j;
			}
		}
		ans+=0.5*(last+now);
		for(j=head;j<=n&&a[j].y<=i;j=nxt[j]){
			if(a[j].y==i){
				for(k=1;k<=t;k++){
					if(vis[q[k]]) continue;
					if(a[j].x>=a[q[k]].x&&a[j].r<=a[q[k]].r){
						del(j);
						break;
					}
					else if(a[j].x<=a[q[k]].x&&a[j].r>=a[q[k]].r){
						del(q[k]);
						for(l=a[q[k]].x;l<a[q[k]].r;l++){
							if(cnt[l]==1) now--;
							cnt[l]--;
						}
					}
				}
				if(k>t){
					for(l=a[j].x;l<a[j].r;l++){
						if(cnt[l]==0) now++;
						cnt[l]++;
					}
				}
			}
		}
	}
	printf("%.1lf\n",ans);
	return 0;
}
