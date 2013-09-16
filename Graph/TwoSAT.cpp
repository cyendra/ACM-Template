/*==============================================*\ 
 | TwoSAT 
 | INIT: init(n);addedge(u,v);节点编号0~n-1 
 | CALL: add_clause(x,xval,y,yval) x=xval or y=yval 
 |       add_con(x,xval) x=xval 
 |       solve():bool;mark[i]:选取i 
\*==============================================*/  
struct TwoSAT{  
    int head[maxn*2];  
    EdgeNode edges[maxm*2];  
    int edge,n;  
    bool mark[maxn*2];  
    int S[maxn*2],c;  
    void init(int n){  
        this->n=n;  
        memset(mark,0,sizeof(mark));  
        memset(head,-1,sizeof(head));  
        edge=0;  
    }  
    void addedge(int u,int v){  
        edges[edge].to=v,edges[edge].next=head[u],head[u]=edge++;  
    }  
    // x = xval or y = yval  
    void add_clause(int x,int xval,int y,int yval){  
        x=x*2+xval;  
        y=y*2+yval;  
        addedge(x^1,y);  
        addedge(y^1,x);  
    }  
    // x = xval  
    void add_con(int x,int xval){  
        x=x*2+xval;  
        addedge(x^1,x);  
    }  
    bool dfs(int x){  
        if (mark[x^1]) return false;  
        if (mark[x]) return true;  
        mark[x]=true;  
        S[c++]=x;  
        for (int i=head[x];i!=-1;i=edges[i].next)  
            if (!dfs(edges[i].to)) return false;  
        return true;  
    }  
    bool solve(){  
        for (int i=0;i<n*2;i+=2)  
            if (!mark[i]&&!mark[i+1]){  
                c=0;  
                if (!dfs(i)){  
                    while (c>0) mark[S[--c]]=false;  
                    if (!dfs(i+1)) return false;  
                }  
            }  
        return true;  
    }  
};  
