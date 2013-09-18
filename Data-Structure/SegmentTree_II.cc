const int INF=0x3f3f3f;
const int MAXN=10000;
struct SegTree{
    int num[MAXN];
    int _min,_max,_sum;
    struct Tree{
        int l;
        int r;
        int max;
        int min;
        int sum;
        int add;
        int set;
    };
    Tree tree[MAXN*4];
    void push_up(int root){
        tree[root].max=max(tree[root<<1].max,tree[root<<1|1].max);
        tree[root].min=min(tree[root<<1].min,tree[root<<1|1].min);
        tree[root].sum=tree[root<<1].sum+tree[root<<1|1].sum;
    }
    void push_down(int root){
        if (tree[root].set!=-1){
            if (tree[root].l!=tree[root].r){
                //传递懒惰标记
                tree[root<<1].add=tree[root<<1|1].add=0;
                tree[root<<1].set=tree[root<<1|1].set=tree[root].set;
                //最更新大值
                tree[root<<1].max=tree[root<<1|1].max=tree[root].set;
                //更新最小值
                tree[root<<1].min=tree[root<<1|1].min=tree[root].set;
                //更新区间和
                tree[root<<1].sum=(tree[root<<1].r-tree[root<<1].l+1)*tree[root].set;
                tree[root<<1|1].sum=(tree[root<<1|1].r-tree[root<<1|1].l+1)*tree[root].set;
            }
            tree[root].set=-1;
        }
        if (tree[root].add>0){
            if (tree[root].l!=tree[root].r){
                //传递懒惰标记
                tree[root<<1].add+=tree[root].add;
                tree[root<<1|1].add+=tree[root].add;
                //更新最大值
                tree[root<<1].max+=tree[root].add;
                tree[root<<1|1].max+=tree[root].add;
                //更新最小值
                tree[root<<1].min+=tree[root].add;
                tree[root<<1|1].min+=tree[root].add;
                //更新区间和
                tree[root<<1].sum+=(tree[root<<1].r-tree[root<<1].l+1)*tree[root].add;
                tree[root<<1|1].sum+=(tree[root<<1|1].r-tree[root<<1|1].l+1)*tree[root].add;
            }
            tree[root].add=0;
        }
    }
    void build(int root,int l,int r){
        tree[root].l=l;
        tree[root].r=r;
        if(tree[root].l==tree[root].r){
            tree[root].max=num[l];
            tree[root].min=num[l];
            tree[root].sum=num[l];
            tree[root].add=0;
            tree[root].set=-1;
            return;
        }
        int mid=(l+r)/2;
        build(root<<1,l,mid);
        build(root<<1|1,mid+1,r);
        push_up(root);
    }
    void update_add(int root,int L,int R,int val){
        if(L<=tree[root].l&&R>=tree[root].r){
            tree[root].add+=val;
            tree[root].max+=val;
            tree[root].min+=val;
            tree[root].sum+=(tree[root].r-tree[root].l+1)*val;
            return;
        }
        push_down(root);
        int mid=(tree[root].l+tree[root].r)/2;
        if(L<=mid) update_add(root<<1,L,R,val);
        if(R>mid)  update_add(root<<1|1,L,R,val);
        push_up(root);
    }
    void update_set(int root,int L,int R,int val){
        if(L<=tree[root].l&&R>=tree[root].r){
            tree[root].set=val;
            tree[root].add=0;
            tree[root].max=val;
            tree[root].min=val;
            tree[root].sum=(tree[root].r-tree[root].l+1)*val;
            return;
        }
        push_down(root);
        int mid=(tree[root].l+tree[root].r)/2;
        if(L<=mid) update_set(root<<1,L,R,val);
        if (R>mid) update_set(root<<1|1,L,R,val);
        push_up(root);
    }
    void query(int root,int L,int R){
        if(L<=tree[root].l&&R>=tree[root].r){
            _min=min(_min,tree[root].min);
            _max=max(_max,tree[root].max);
            _sum+=tree[root].sum;
            return;
        }
        push_down(root);
        int mid=(tree[root].l+tree[root].r)/2;
        if(L<=mid) query(root<<1,L,R);
        if(R>mid) query(root<<1|1,L,R);
    }
};
