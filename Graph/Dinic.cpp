/*==============================================*\ 
 | Dinic最大流 
 | INIT: prepare(n,S,T);addedge(u,v,c);节点0~n 
 | CALL: Dinic_flow():int 
\*==============================================*/  
struct edgenode{  
    int to,flow,next;  
};  
struct Dinic{  
    int node,src,dest,edge;  
    int head[maxn],work[maxn],dis[maxn],q[maxn];  
    edgenode edges[maxm];  
    void prepare(int _node,int _src,int _dest){  
        node=_node,src=_src,dest=_dest;  
        memset(head,-1,sizeof(head));  
        edge=0;  
    }  
    void addedge(int u,int v,int c){  
        edges[edge].flow=c,edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;  
        edges[edge].flow=0,edges[edge].to=u,edges[edge].next=head[v],head[v]=edge++;  
    }  
    bool Dinic_bfs(){  
        int i,u,v,l,r=0;  
        for (i=0; i<node; i++) dis[i]=-1;  
        dis[q[r++]=src]=0;  
        for (l=0; l<r; l++){  
            for (i=head[u=q[l]]; i!=-1; i=edges[i].next){  
                if (edges[i].flow&&dis[v=edges[i].to]<0){  
                    dis[q[r++]=v]=dis[u]+1;  
                    if (v==dest) return true;  
                }  
            }  
        }  
        return false;  
    }  
    int Dinic_dfs(int u,int exp){  
        if (u==dest) return exp;  
        for (int &i=work[u],v,tmp; i!=-1; i=edges[i].next){  
            if (edges[i].flow&&dis[v=edges[i].to]==dis[u]+1&&  
                (tmp=Dinic_dfs(v,min(exp,edges[i].flow)))>0){  
                edges[i].flow-=tmp;  
                edges[i^1].flow+=tmp;  
                return tmp;  
            }  
        }  
        return 0;  
    }  
    int Dinic_flow(){  
        int i,ret=0,delta;  
        while (Dinic_bfs()){  
            for (i=0;i<node;i++) work[i]=head[i];  
            while (delta=Dinic_dfs(src,INF)) ret+=delta;  
        }  
        return ret;  
    }  
};  
