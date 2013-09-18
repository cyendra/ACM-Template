struct BIT{  
    int n;  
    int tree[maxn];  
    void init(int n){  
        this->n=n;  
        memset(tree,0,sizeof(tree));  
    }  
    int lowbit(int x){  
        return x&(-x);  
    }  
    void add(int x,int val){  
        for (int i=x;i<=n;i+=lowbit(i)) tree[i]+=val;  
    }  
    int query(int x){  
        int ret=0;  
        for (int i=x;i>0;i-=lowbit(i)) ret+=tree[i];  
        return ret;  
    }  
    //离散 p=lower_bound(b+1,b+n+1,a[i])-b;  
    //逆序数 x=(n-i+1)-query(p);add(p,1);  
};  
