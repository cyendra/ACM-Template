#include <iostream>
#include <cstring>
using namespace std;
const int maxn=11111;
const int maxh=10000019;
int head[maxh];
int next[maxh];
long long st[maxn];
void hash_init(){
    memset(head,0,sizeof(head));
}

int hash(long long p,int prime=10000019){
    int h;
    //hash操作
    h=p%prime;
    return h;
}

bool add_hash(int s){
    int h=hash(st[s]);
    int u=head[h];
    while(u){
        //if (memcmp(st[u],st[s],sizeof(st[s]))==0) return 0;
        //if (strcmp(st[u],st[s])==0) return 0;
        if (st[u]==st[s]) return 0;
        u=next[u];
    }
    next[s]=head[h];
    head[h]=s;
    return 1;
}

bool search_hash(long long p){
    int h=hash(p);
    int u=head[h];
    while (u){
        //if (memcmp(st[u],p,sizeof(st[u]))==0) return 1;
        //if (strcmp(st[u],str)==0) return 1;
        if (st[u]==p) return 1;
        u=next[u];
    }
    return 0;
}
