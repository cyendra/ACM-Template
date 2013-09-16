int pa[maxn];
void makeset(int n){
    for (int i=0;i<=n;i++) pa[i]=i;
}
int findset(int x){
    if (x!=pa[x]) pa[x]=findset(pa[x]);
    return pa[x];
}
void unionset(int x,int y){
    x=findset(x);
    y=findset(y);
    if (x!=y) pa[x]=y;
}
