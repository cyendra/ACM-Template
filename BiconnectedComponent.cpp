/*==============================================*\ 
 | 点双连通/割点/桥/边双连通 
 | INIT: init(n);addedge(u,v);无向图;节点编号1~n 
 | CALL: find_bcc():点双连通/割点/桥 
 |       find_block():边双连通,先要求出桥 
 |       iscut[]:割点;EdgeNode_1.cut:桥 
 |       vector<int>bcc[x]:双连通分量x所包含的节点 
 |       bccno[x]:节点x所属的点双连通分量,割点的值无意义 
 |       block[x]:节点x所属的边双连通分量 
\*==============================================*/  
struct EdgeNode_1{  
    int to;  
    int w;  
    int next;  
    bool cut;  
};  
struct Edge{  
    int u;  
    int v;  
    Edge(){}  
    Edge(int a,int b):u(a),v(b){}  
};  
struct Bcc_Graph{  
    int head[maxn];  
    EdgeNode_1 edges[maxm];  
    int edge,n;  
    void init(int n){  
        memset(head,-1,sizeof(head));  
        this->n=n;  
        edge=0;  
    }  
    void addedge(int u,int v,int c=0){  
        edges[edge].cut=0,edges[edge].w=c,edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;  
    }  
    //点双连通/割点/桥  
    int dfn[maxn],low[maxn],bccno[maxn],dfs_clock,bcc_cnt;  
    bool iscut[maxn];  
    vector<int>bcc[maxn];  
    stack<Edge>stk;  
    int dfs(int u,int fa){  
        int lowu=dfn[u]=++dfs_clock;  
        int child=0;  
        for (int i=head[u];i!=-1;i=edges[i].next){  
            int v=edges[i].to;  
            if (v==fa) continue;  
            Edge e=Edge(u,v);  
            if (!dfn[v]){  
                stk.push(e);  
                child++;  
                int lowv=dfs(v,u);  
                lowu=min(lowu,lowv);  
                if (dfn[u]<=lowv){  
                    iscut[u]=true;//割点  
                    //BEGIN 求点双连通分量  
                    bcc_cnt++;  
                    bcc[bcc_cnt].clear();  
                    Edge x;  
                    do{  
                        x=stk.top();  
                        stk.pop();  
                        if (bccno[x.u]!=bcc_cnt){  
                            bcc[bcc_cnt].push_back(x.u);  
                            bccno[x.u]=bcc_cnt;  
                        }  
                        if (bccno[x.v]!=bcc_cnt){  
                            bcc[bcc_cnt].push_back(x.v);  
                            bccno[x.v]=bcc_cnt;  
                        }  
                    }while (x.u!=u||x.v!=v);  
                    //END  
                }  
                if (dfn[u]<lowv){//cut 桥  
                    edges[i].cut=true;  
                    edges[i^1].cut=true;  
                }  
            }  
            else if (dfn[v]<dfn[u]){  
                stk.push(e);//BEGIN-END 点双连通  
                lowu=min(lowu,dfn[v]);  
            }  
        }  
        if (fa<0&&child==1) iscut[u]=0;//割点  
        low[u]=lowu;  
        return lowu;  
    }  
    void find_bcc(){  
        while (!stk.empty()) stk.pop();  
        memset(dfn,0,sizeof(dfn));  
        memset(iscut,0,sizeof(iscut));  
        memset(bccno,0,sizeof(bccno));  
        dfs_clock=bcc_cnt=0;  
        for (int i=1;i<=n;i++){  
            if (!dfn[i]) dfs(i,-1);  
        }  
    }  
    //边双连通分量  
    int block[maxn];  
    int vis[maxn];  
    int b_num;  
    void b_dfs(int u){  
        vis[u]=true;  
        block[u]=b_num;  
        for (int i=head[u];i!=-1;i=edges[i].next)  
        {  
            if (edges[i].cut) continue;  
            int v=edges[i].to;  
            if (!vis[v]) b_dfs(v);  
        }  
    }  
    void find_block(){  
        memset(block,0,sizeof(block));  
        memset(vis,0,sizeof(vis));  
        b_num=0;  
        for (int i=1;i<=n;i++){  
            if (!vis[i]){  
                b_num++;  
                b_dfs(i);  
            }  
        }  
    }  
};  
