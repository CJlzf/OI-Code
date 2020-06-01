#include <iostream>
#include <cstdio>
#include <cstring>
#include <queue>
#define N 1000002
using namespace std;
const long long inf=1LL<<50;
struct node{
    int w,id;
    node(int _w,int _id){
        w=_w;id=_id;
    }
    bool operator < (const node &a) const{
        return a.w>w;
    }
};
priority_queue<node> A1,A2,B1,B2,AB;
int T,n,k,l,flow,i,a[N],b[N],vis[N];
long long ans;
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
	freopen("sequence.in","r",stdin);
	freopen("sequence.out","w",stdout);
    T=read();
    while(T--){
        while(A1.size()) A1.pop();
        while(A2.size()) A2.pop();
        while(B1.size()) B1.pop();
        while(B2.size()) B2.pop();
        while(AB.size()) AB.pop();
        memset(vis,0,sizeof(vis));
        ans=flow=0;
        n=read();k=read();l=read();
        for(i=1;i<=n;i++) a[i]=read(),A1.push(node(a[i],i));
        for(i=1;i<=n;i++) b[i]=read(),B1.push(node(b[i],i));
        for(i=1;i<=k-l;i++){
            int A=A1.top().w,pa=A1.top().id;
            int B=B1.top().w,pb=B1.top().id;
            ans+=A+B;
            vis[pa]|=1;vis[pb]|=2;
            A1.pop();B1.pop();
        }
        while(A1.size()) A1.pop();
        while(B1.size()) B1.pop();
        for(i=1;i<=n;i++){
            if(vis[i]==2) A1.push(node(a[i],i));
            if(vis[i]==0||vis[i]==2) A2.push(node(a[i],i));
            if(vis[i]==1) B1.push(node(b[i],i));
            if(vis[i]==0||vis[i]==1) B2.push(node(b[i],i));
            if(vis[i]==0) AB.push(node(a[i]+b[i],i));
            if(vis[i]==3) flow++;
        }
        for(i=k-l+1;i<=k;i++){
            while(A1.size()&&vis[A1.top().id]!=2) A1.pop();
            while(A2.size()&&(vis[A2.top().id]&1)) A2.pop();
            while(B1.size()&&vis[B1.top().id]!=1) B1.pop();
            while(B2.size()&&(vis[B2.top().id]&2)) B2.pop();
            while(AB.size()&&vis[AB.top().id]) AB.pop();
            if(flow){
                flow--;
                int pa=A2.top().id,pb=B2.top().id;
                ans+=a[pa]+b[pb];
                vis[pa]|=1;vis[pb]|=2;
                if(vis[pa]!=3) B1.push(node(b[pa],pa));
                if(vis[pb]!=3) A1.push(node(a[pb],pb));
                if(pa==pb) flow++;
                else{
                    if(vis[pa]==3) flow++;
                    if(vis[pb]==3) flow++;
                }
            }
            else{
                long long ans1=0,ans2=0,ans3=0;
				int s1=0,s2=0;
                if(!AB.empty()) ans1=AB.top().w;
                if(!B1.empty()&&!A2.empty()){
                    int pa=A2.top().id,pb=B1.top().id;
                    ans2=a[pa]+b[pb];
                    if(vis[pa]==2) s1=1;
                }
                if(!A1.empty()&&!B2.empty()){
                    int pa=A1.top().id,pb=B2.top().id;
                    ans3=a[pa]+b[pb];
                    if(vis[pb]==1) s2=1;
                }
                int maxx=max(ans1,max(ans2,ans3));
                ans+=maxx;
                if(ans2==ans3&&ans2==maxx){
                    if(s1==1){
                        int pa=A2.top().id,pb=B1.top().id;
                        vis[pa]|=1;vis[pb]|=2;
                        if(vis[pa]!=3) B1.push(node(b[pa],pa));
                        else flow++;
                    }
                    else{
                        int pa=A1.top().id,pb=B2.top().id;
                        vis[pa]|=1;vis[pb]|=2;
                        if(vis[pb]!=3) A1.push(node(a[pb],pb));
                        else flow++;
                    }
                }
                else{
                    if(ans1==maxx){
                        int p=AB.top().id;
                        vis[p]=3;
                    }
                    else if(ans2==maxx){
                        int pa=A2.top().id,pb=B1.top().id;
                        vis[pa]|=1;vis[pb]|=2;
                        if(vis[pa]!=3) B1.push(node(b[pa],pa));
                        else flow++;
                    }
                    else{
                        int pa=A1.top().id,pb=B2.top().id;
                        vis[pa]|=1;vis[pb]|=2;
                        if(vis[pb]!=3) A1.push(node(a[pb],pb));
                        else flow++;
                    }
                }	
            }
        }
        printf("%lld\n",ans);
    }
    return 0;
}
