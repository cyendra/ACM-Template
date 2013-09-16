/*==============================================*\ 
 | Dijkstra+堆优化 
 | INIT: init(n);addedge(u,v,c);节点编号0~n 
 | CALL: dijkstra(int s);dis[]:最短路;pre[]:前驱 
\*==============================================*/  
struct HeapNode{  
    int d,u;  
    HeapNode(){}  
    HeapNode(int a,int b):d(a),u(b){}  
    bool operator<(const HeapNode& rhs) const{  
        return d>rhs.d;  
    }  
};  
struct Dijkstra{  
    EdgeNode edges[maxm];  
    int head[maxn];  
    int edge,n;  
    void init(int n){  
        this->n=n;  
        memset(head,-1,sizeof(head));  
        edge=0;  
    }  
    void addedge(int u,int v,int c){  
        edges[edge].w=c,edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;  
    }  
    bool done[maxn];  
    int dis[maxn];  
    int pre[maxn];  
    void dijkstra(int s){  
        priority_queue<HeapNode>que;  
        for (int i=0;i<=n;i++) dis[i]=INF;  
        dis[s]=0;  
        memset(done,0,sizeof(done));  
        que.push(HeapNode(0,s));  
        while (!que.empty()){  
            HeapNode x=que.top();  
            que.pop();  
            int u=x.u;  
            if (done[u]) continue;  
            done[u]=true;  
            for (int i=head[u];i!=-1;i=edges[i].next){  
                int v=edges[i].to;  
                int w=edges[i].w;  
                if (dis[v]>dis[u]+w){  
                    dis[v]=dis[u]+w;  
                    pre[v]=u;  
                    que.push(HeapNode(dis[v],v));  
                }  
            }  
        }  
    }  
};  
