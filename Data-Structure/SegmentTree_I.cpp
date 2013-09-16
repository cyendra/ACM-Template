const int MAXN=255111;
struct SegmentTree{
    int num[MAXN];
    struct Tree{
        int l;
        int r;
        int min;
    };
    Tree tree[MAXN*4];
    void push_up(int root){
        tree[root].min=min(tree[root<<1].min,tree[root<<1|1].min);
    }
    void build(int root,int l,int r){
        tree[root].l=l;
        tree[root].r=r;
        if(tree[root].l==tree[root].r){
            tree[root].min=num[l];
            return;
        }
        int mid=(l+r)/2;
        build(root<<1,l,mid);
        build(root<<1|1,mid+1,r);
        push_up(root);
    }
    void update(int root,int pos,int val){
        if(tree[root].l==tree[root].r){
            tree[root].min=val;
            return;
        }
        int mid=(tree[root].l+tree[root].r)/2;
        if(pos<=mid) update(root<<1,pos,val);
        else update(root<<1|1,pos,val);
        push_up(root);
    }
    int query(int root,int L,int R){
        if(L<=tree[root].l&&R>=tree[root].r) return tree[root].min;
        int mid=(tree[root].l+tree[root].r)/2,ret=INF;
        if(L<=mid) ret=min(ret,query(root<<1,L,R));
        if(R>mid) ret=min(ret,query(root<<1|1,L,R));
        return ret;
    }
    void init(int n,int d){
        for (int i=1;i<=n;i++) num[i]=d;
        build(1,1,n);
    }
};
