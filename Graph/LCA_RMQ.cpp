#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>

using namespace std;
const int INF=0x3f3f3f;
const int maxn=111111;
const int maxm=111111;
int n,m;

struct EDGENODE{
    int to;
    int w;
    int next;
};
struct SGRAPH{
    int head[maxn];
    EDGENODE edges[maxm];
    int edge;
    void init(){
        memset(head,-1,sizeof(head));
        edge=0;
    }
    void addedge(int u,int v,int c){
        edges[edge].w=c,edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;
    }
    //------------
    int d[maxn][20];
    //元素从1编号到n
    void makeRmqIndex(int A[],int n){
        for(int i=1;i<=n;i++) d[i][0]=i;
        for(int j=1;(1<<j)<=n;j++)
            for(int i=1;i+(1<<j)-1<=n;i++)
                d[i][j] = A[d[i][j-1]] < A[d[i+(1<<(j-1))][j-1]]? d[i][j-1]:d[i+(1<<(j-1))][j-1];
    }
    int rmqIndex(int L,int R,int A[])
    {
        int k=0;
        while ((1<<(k+1))<=R-L+1) k++;
        return A[d[L][k]]<A[d[R-(1<<k)+1][k]]? d[L][k]:d[R-(1<<k)+1][k];
    }
    //---------------------
    int E[maxn*2],R[maxn],D[maxn*2],mn;
    void dfs(int u,int p,int d){
        E[++mn]=u;
        D[mn]=d;
        R[u]=mn;
        for (int i=head[u];i!=-1;i=edges[i].next){
            int v=edges[i].to;
            if (v==p) continue;
            dfs(v,u,d+1);
            E[++mn]=u;
            D[mn]=d;
        }
    }
    void LCA_init(){
        mn=0;
        memset(R,0,sizeof(R));
        dfs(1,-1,1);
        makeRmqIndex(D,mn);
        getd(1,-1,0);
    }
    int LCA(int u,int v){
        if (R[u]>=R[v]) return E[rmqIndex(R[v],R[u],D)];
        else return E[rmqIndex(R[u],R[v],D)];

    }
    //--------------------
    int deep[maxn];
    void getd(int u,int p,int w){
        deep[u]=w;
        for (int i=head[u];i!=-1;i=edges[i].next){
            int v=edges[i].to;
            if (v==p) continue;
            getd(v,u,w+edges[i].w);
        }
    }
    int getDis(int u,int v){
        int lca=LCA(u,v);
        return deep[u]+deep[v]-deep[lca]*2;
    }
    int done(int x,int y,int z){
        int ans=INF,res=0;
        int lca1,lca2;

        lca1=LCA(x,y);
        res=deep[x]+deep[y]-deep[lca1]*2;
        lca2=LCA(lca1,z);
        res+=deep[lca1]+deep[z]-deep[lca2]*2;
        ans=min(ans,res);

        lca1=LCA(x,z);
        res=deep[x]+deep[z]-deep[lca1]*2;
        lca2=LCA(lca1,y);
        res+=deep[lca1]+deep[y]-deep[lca2]*2;
        ans=min(ans,res);

        lca1=LCA(y,z);
        res=deep[y]+deep[z]-deep[lca1]*2;
        lca2=LCA(lca1,x);
        res+=deep[lca1]+deep[x]-deep[lca2]*2;
        ans=min(ans,res);

        return ans;
    }
}solver;
