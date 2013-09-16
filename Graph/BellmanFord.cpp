/*==============================================*\ 
 | BellmanFord+队列优化 
 | INIT: init(n);addedge(u,v,c);节点编号0~n 
 | CALL: spfa(int s):bool;dist[]:最短路 
\*==============================================*/  
struct BellmanFord{
    EdgeNode edges[maxm];
    int head[maxn],edge,n;
    bool vis[maxn];
    int outque[maxn];
    queue<int>que;
    int dis[maxn];
    void addedge(int u,int v,int c){
        edges[edge].w=c,edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;
    }
    void init(int n){
        memset(head,-1,sizeof(head));
        edge=0;
        this->n=n;
    }
    bool spfa(int s){
        int top;
        for (int i=0;i<=n;i++) dis[i]=INF;
        memset(vis,0,sizeof(vis));
        memset(outque,0,sizeof(outque));
        while (!que.empty()) que.pop();
        que.push(s);
        vis[s]=true;
        dis[s]=0;
        while (!que.empty()){
            top=que.front();
            que.pop();
            vis[top]=false;
            outque[top]++;
            if (outque[top]>n) return false;
            for (int i=head[top];i!=-1;i=edges[i].next){
                int v=edges[i].to;
                if (dis[v]==INF||dis[v]>dis[top]+edges[i].w){
                    dis[v]=dis[top]+edges[i].w;
                    if (!vis[v]){
                        vis[v]=true;
                        que.push(v);
                    }
                }
            }
        }
        return true;
    }
};
