#include <iostream>
#include <cstdio>
#define N 1000002
#define T 1000001 
using namespace std;
const int inf=1<<30;
struct SegmentTree{
    int dat,cnt,add;
}t[N*4];
int n,m,v,i,a[N];
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
void update(int p)
{
    t[p].cnt=0;
    t[p].dat=min(t[p*2].dat,t[p*2+1].dat);
    if(t[p].dat==t[p*2].dat) t[p].cnt+=t[p*2].cnt;
    if(t[p].dat==t[p*2+1].dat) t[p].cnt+=t[p*2+1].cnt;
}
void spread(int p)
{
    if(t[p].add){
        t[p*2].dat+=t[p].add;t[p*2].add+=t[p].add;
        t[p*2+1].dat+=t[p].add;t[p*2+1].add+=t[p].add;
        t[p].add=0;
    }
}
void build(int p,int l,int r)
{
    if(l==r){
        if(vis[l]) t[p].cnt=1,t[p].dat=1;
        else t[p].dat=inf;
        return;
    }
    int mid=(l+r)/2;
    build(p*2,l,mid);
    build(p*2+1,mid+1,r);
    update(p);
}
void change1(int p,int l,int r,int ql,int qr,int x)
{
    if(ql<=l&&r<=qr){
        t[p].dat+=x;t[p].add+=x;
        return;
    }
    int mid=(l+r)/2;
    spread(p);
    if(ql<=mid) change1(p*2,l,mid,ql,qr,x);
    if(qr>mid) change1(p*2+1,mid+1,r,ql,qr,x);
    update(p);
}
void change2(int p,int l,int r,int x)
{
    if(l==r){
        if(vis[l]) t[p].cnt=1,t[p].dat=1;
        else t[p].cnt=0,t[p].dat=inf;
        return;
    }
    int mid=(l+r)/2;
    spread(p);
    if(x<=mid) change2(p*2,l,mid,x);
    else change2(p*2+1,mid+1,r,x);
    update(p);
}
int main()
{
    //aaaa
    n=read();m=read();
    for(i=1;i<=n;i++) a[i]=read(),vis[a[i]]=1;
    a[0]=T;
    for(i=0;i<=n;i++) change1(1,0,T,min(a[i],a[i+1]),max(a[i],a[i+1])-1,1);
    build(1,0,T);
    for(i=1;i<=m;i++){
        int x=read(),y=read();
        change1(1,0,T,min(a[x-1],a[x]),max(a[x-1],a[x]),-1);
        change1(1,0,T,min(a[x+1],a[x]),max(a[x+1],a[x]),-1);
        vis[a[x]]=0;vis[y]=1;
        change2(1,0,T,a[x]);change2(1,0,T,y);
        a[x]=y;
        change1(1,0,T,min(a[x-1],a[x]),max(a[x-1],a[x]),1);
        change1(1,0,T,min(a[x+1],a[x]),max(a[x+1],a[x]),1);
        if(t[1].dat==1) printf("%d\n",t[1].cnt);
        else puts("1");
    }
    return 0;
}