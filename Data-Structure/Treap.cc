#include <iostream>  
#include <ctime>  
#include <cstdlib>  
#include <cstdio>  
#include <cstring>  
#include <vector>  
using namespace std;  
  
struct Node{  
    Node* ch[2];//左右子树  
    int fix;//优先级。数值越大，优先级越高  
    int key;  
    int size;//以它为根的子树的总结点数  
    bool operator<(const Node& rhs) const {  
        return fix<rhs.fix;  
    }  
    int cmp(int x) const{  
        if (x==key) return -1;  
        return x<key?0:1;  
    }  
    //名次树  
    void maintain(){  
        size=1;  
        if (ch[0]!=NULL) size+=ch[0]->size;  
        if (ch[1]!=NULL) size+=ch[1]->size;  
    }  
};  
  
struct Treap{  
    Node* root;  
    Treap(){  
        srand(time(0));  
        root=NULL;  
    }  
    void removetree(Node* &t){  
        if (t->ch[0]!=NULL) removetree(t->ch[0]);  
        if (t->ch[1]!=NULL) removetree(t->ch[1]);  
        delete t;  
        t=NULL;  
    }  
    void clear(){  
        srand(time(0));  
        removetree(root);  
    }  
    Node* newNode(int v){  
        Node* t=new Node;  
        t->key=v;  
        t->ch[0]=t->ch[1]=NULL;  
        t->fix=rand();  
        t->size=1;  
        return t;  
    }  
    //d=0代表左旋,d=1代表右旋  
    void rotate(Node* &o,int d){  
        Node* k=o->ch[d^1];  
        o->ch[d^1]=k->ch[d];  
        k->ch[d]=o;  
        o->maintain();  
        k->maintain();  
        o=k;  
    }  
    //在以o为根的子树中插入键值x,修改o  
    void insert(Node* &o,int x){  
        if (o==NULL) o=newNode(x);  
        else{  
            int d=o->cmp(x);  
            if (d==-1) d=1;  
            insert(o->ch[d],x);  
            if (o->ch[d]>o) rotate(o,d^1);  
        }  
        o->maintain();  
    }  
    void remove(Node* &o,int x){  
        int d=o->cmp(x);  
        if (d==-1){  
            Node* u=o;  
            if (o->ch[0]!=NULL&&o->ch[1]!=NULL){  
                int d2=(o->ch[0]>o->ch[1]?1:0);  
                rotate(o,d2);  
                remove(o->ch[d2],x);  
            }else{  
                if (o->ch[0]==NULL) o=o->ch[1];  
                else if (o->ch[1]==NULL) o=o->ch[0];  
                delete u;  
            }  
        }  
        else remove(o->ch[d],x);  
        if (o!=NULL) o->maintain();  
    }  
    bool find(Node* o,int x){  
        while (o!=NULL){  
            int d=o->cmp(x);  
            if (d==-1) return 1;  
            else o=o->ch[d];  
        }  
        return 0;  
    }  
    //第k大的值  
    int kth(Node* o,int k){  
        if (o==NULL||k<=0||k>o->size) return 0;  
        int s=(o->ch[1]==NULL?0:o->ch[1]->size);  
        if (k==s+1) return o->key;  
        else if (k<=s) return kth(o->ch[1],k);  
        else return kth(o->ch[0],k-s-1);  
    }  
    void merge(Node* &src){  
        if (src->ch[0]!=NULL) merge(src->ch[0]);  
        if (src->ch[1]!=NULL) merge(src->ch[1]);  
        insert(root,src->key);  
        delete src;  
        src=NULL;  
    }  
};  
