#include <iostream>
#include <cstdio>
#define N 100002
using namespace std;
struct SegmentTree{
	int l,r,fa,size;
}t[N*40];
int n,m,i,num[N*2],cnt;
int build(int l,int r)
{
	int p=++cnt,mid=(l+r)/2;
	if(l==r){
		t[p].fa=l;
		return p;
	}
	t[p].l=build(1,mid);
	t[p].r=build(mid+1,r);
	return p;
}
int query(int p,int l,int r,int v,int root)
{
	if(l==r){
		if(t[p].fa==l) return p;
		return query(root,1,n,t[p].fa,root);
	}
	int mid=(l+r)/2;
	if(v<=mid) return query(t[p].l,l,mid,v,root);
	else return query(t[p].r,mid+1,r,v,root);
}
int insert(int pre,int l,int r,int f1,int f2)
{
	int p=++cnt,mid=(l+r)/2;
	t[p]=t[pre];
	if(l==r){
		t[p].fa=f1;
		return p;
	}
	if(f2<=mid) t[p].l=insert(t[pre].l,l,mid,f1,f2);
	else t[p].r=insert(t[pre].r,mid+1,r,f1,f2);
	return p;
}
void add(int p,int l,int r,int v)
{
	if(l==r){
		t[p].size++;
		return;
	}
	int mid=(l+r)/2;
	if(v<=mid) add(t[p].l,l,mid,v);
	else add(t[p].r,mid+1,r,v);
}
int main()
{
	cin>>n>>m;
	num[0]=build(1,n);
	for(i=1;i<=m;i++){
		int op,a,b;
		cin>>op;
		if(op==1){
			cin>>a>>b;
			num[i]=num[i-1];
			int f1=query(num[i],1,n,a,num[i]),f2=query(num[i],1,n,b,num[i]);
			if(f1==f2) continue;
			if(t[f1].size<t[f2].size) swap(f1,f2);
			num[i]=insert(num[i-1],1,n,t[f1].fa,t[f2].fa);
			if(t[f1].size==t[f2].size) add(num[i],1,n,t[f1].fa);
		}
		else if(op==2){
			cin>>a;
			num[i]=num[a];
		}
		else{
			cin>>a>>b;
			num[i]=num[i-1];
			if(query(num[i],1,n,a,num[i])==query(num[i],1,n,b,num[i])) cout<<"1"<<endl;
			else cout<<"0"<<endl;
		}
	}
	return 0;
}
