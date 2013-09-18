struct StoerWagner{  
    int mat[maxn][maxn];  
    int dis[maxn];  
    int S,T;  
    int n;  
    bool vis[maxn],del[maxn];  
    void init(int n){  
        memset(mat,0,sizeof(mat));  
        this->n=n;  
    }  
    void addedge(int u,int v,int c){  
        mat[u][v]+=c;  
        mat[v][u]+=c;  
    }  
    int search(int ct){  
        int tmp,mx,cut;  
        memset(vis,0,sizeof(vis));  
        memset(dis,0,sizeof(dis));  
        T=S=-1;  
        for (int i=0;i<n-ct;i++){  
            mx=-1;  
            for (int j=0;j<n;j++){  
                if (!vis[j]&&!del[j]&&dis[j]>mx){  
                    mx=dis[j];  
                    tmp=j;  
                }  
            }  
            S=T;  
            T=tmp;  
            cut=mx;  
            vis[T]=true;  
            for (int j=0;j<n;j++){  
                if (!vis[j]&&!del[j]){  
                    dis[j]+=mat[T][j];  
                }  
            }  
        }  
        return cut;  
    }  
    int minimumCut(){  
        int ans=INF;  
        memset(del,0,sizeof(del));  
        for (int i=0;i<n-1;i++){  
            int cut=search(i);  
            if (cut<ans) ans=cut;  
            if (ans==0) return 0;  
            del[T]=true;  
            for (int j=0;j<n;j++){  
                if (!del[j]){  
                    mat[S][j]+=mat[T][j];  
                    mat[j][S]+=mat[T][j];  
                }  
            }  
        }  
        return ans;  
    }  
};  
