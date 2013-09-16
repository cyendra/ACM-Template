/*==============================================*\ 
 | 最小费用最大流 
 | INIT: prepare(n,S,T);addedge(u,v,f,c);编号0~n-1 
 | CALL: spfaflow():int 
\*==============================================*/  
struct edgenode_1{  
    int to;//边的指向  
    int flow;//边的容量  
    int cost;//边的费用  
    int next;//链表的下一条边  
};  
struct MinCost{  
    edgenode_1 edges[maxm];  
    int node,src,dest,edge;//node节点数，src源点，dest汇点，edge边数  
    int head[maxn],p[maxn],dis[maxn],q[maxn],vis[maxn];  
    //head链表头，p记录可行流上节点对应的反向边，dis计算距离  
    void prepare(int _node=0,int _src=0,int _dest=0){  
        node=_node,src=_src,dest=_dest;  
        memset(head,-1,sizeof(head));  
        memset(vis,0,sizeof(vis));  
        edge=0;  
    }  
    void addedge(int u,int v,int f,int c){  
        edges[edge].flow=f;edges[edge].cost=c;edges[edge].to=v;  
        edges[edge].next=head[u];head[u]=edge++;  
        edges[edge].flow=0;edges[edge].cost=-c;edges[edge].to=u;  
        edges[edge].next=head[v];head[v]=edge++;  
    }  
    bool spfa(){  
        int i,u,v,l,r=0,tmp;  
        for (i=0;i<node;i++) dis[i]=INF;  
        dis[q[r++]=src]=0;  
        p[src]=p[dest]=-1;  
        for (l=0;l!=r;((++l>=maxn)?l=0:l)){  
            for (i=head[u=q[l]],vis[u]=false;i!=-1;i=edges[i].next){  
                if (edges[i].flow&&dis[v=edges[i].to]>(tmp=dis[u]+edges[i].cost)){  
                    dis[v]=tmp;  
                    p[v]=i^1;  
                    if (vis[v]) continue;  
                    vis[q[r++]=v]=true;  
                    if (r>=maxn) r=0;  
                }  
            }  
        }  
        return p[dest]>=0;  
    }  
    int spfaflow(){  
        int i,ret=0,delta;  
        while (spfa()){//按记录原路返回求流量  
            for (i=p[dest],delta=INF;i>=0;i=p[edges[i].to]){  
                delta=min(delta,edges[i^1].flow);  
            }  
            for (int i=p[dest];i>=0;i=p[edges[i].to]){  
                edges[i].flow+=delta;  
                edges[i^1].flow-=delta;  
            }  
            ret+=delta*dis[dest];  
        }  
        return ret;  
    }  
};  
