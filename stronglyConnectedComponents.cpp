/*==============================================*\ 
 | 强连通分量-Tarjan 
 | INIT: init(n);addedge(u,v);节点编号0~n-1 
 | CALL: find_scc();sccno[x]:节点x所属强连通分量 
\*==============================================*/  
struct Tarjan{  
    int head[maxn];  
    EdgeNode edges[maxm];  
    int edge,n;  
    void init(int n){  
        memset(head,-1,sizeof(head));  
        this->n=n;  
        edge=0;  
    }  
    void addedge(int u,int v,int c=0){  
        edges[edge].w=c,edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;  
    }  
    int pre[maxn],lowlink[maxn],sccno[maxn],scc_cnt,dfs_clock;  
    stack<int>stk;  
    void dfs(int u){  
        pre[u]=lowlink[u]=++dfs_clock;  
        stk.push(u);  
        for (int i=head[u];i!=-1;i=edges[i].next){  
            int v=edges[i].to;  
            if (!pre[v]){  
                dfs(v);  
                lowlink[u]=min(lowlink[u],lowlink[v]);  
            }  
            else if (!sccno[v]){  
                lowlink[u]=min(lowlink[u],pre[v]);  
            }  
        }  
        if (lowlink[u]==pre[u]){  
            scc_cnt++;  
            int x;  
            do{  
                x=stk.top();  
                stk.pop();  
                sccno[x]=scc_cnt;  
            }while (x!=u);  
        }  
    }  
    void find_scc(){  
        dfs_clock=scc_cnt=0;  
        memset(sccno,0,sizeof(sccno));  
        memset(pre,0,sizeof(pre));  
        while (!stk.empty()) stk.pop();  
        for (int i=0;i<n;i++) if (!pre[i]) dfs(i);  
    }  
};  
