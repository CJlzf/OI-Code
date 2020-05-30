#include <iostream>
#include <cstdio>
#include <vector>
#define N 200002
using namespace std;
struct star{
    int x,w;
    star(int _x,int _w){
        x=_x;w=_w;
    }
};
vector<star> s[N];
vector<int> v[N];
int n,i,j,f[2][N],c[N],ans;
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
int lowbit(int x)
{
    return x&(-x);
}
int ask(int x)
{
    int ans=0;
    for(int i=x;i>=1;i-=lowbit(i)) ans+=c[i];
    return ans;
}
void add(int x,int y)
{
    for(int i=x;i<=n+1;i+=lowbit(i)) c[i]+=y;
}
int find(int op,int x)
{
    if(f[op][x]!=x) f[op][x]=find(op,f[op][x]);
    return f[op][x];
}
int main()
{
    n=read();
    for(i=1;i<=n;i++){
        int h=read();
        v[h].push_back(i);
    }
    for(i=1;i<=n;i++){
        int x=read(),y=read(),w=read();
        s[y].push_back(star(x,w));
    }
    for(i=1;i<=n+1;i++) f[0][i]=f[1][i]=1;
    for(i=1;i<=n;i++){
        for(j=0;j<s[i].size();j++){
            int x=s[i][j].x,w=s[i][j].w;
            int maxx=ask(x);
            if(w>maxx){
                ans+=maxx;
                add(find(0,x)+1,w-maxx);
                add(find(1,x),maxx-w);
            }
            else ans+=w;
        }
        for(j=0;j<v[i].size();j++){
            int pos=v[i][j];
            int f1=find(0,pos),f2=find(0,pos-1);
            if(f1!=f2) f[0][f1]=f2;
            int f3=find(1,pos),f4=find(1,pos+1);
            if(f3!=f4) f[1][f3]=f4;
        }
    }
}