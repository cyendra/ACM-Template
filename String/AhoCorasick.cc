const int CHARSET = 26;
const int MAX_N_NODES = int(3e5) + 10;

struct Aho_Corasick{
    struct Node{
        Node *next[CHARSET];
        Node *fail;
        int count;//记录当前前缀是完整单词出现的个数
        Node(){
            memset(next,0,sizeof(next));
            fail = NULL;
            count = 0;
        }
        void clear(){
            memset(next,0,sizeof(next));
            fail = NULL;
            count = 0;
        }
    };
    Node *root;
    Node nodePool[MAX_N_NODES], *cur;
    Node* newNode(){
        Node* t=cur++;
        t->clear();
        return t;
    }
    void init(){
        cur=nodePool;
        root=newNode();
    }
    void insert(char *str){
        Node* p=root;
        int i=0,index;
        while(str[i]){
            index=str[i]-'a';
            if(p->next[index]==NULL) p->next[index]=newNode();
            p=p->next[index];
            i++;
        }
        p->count++;
    }
    void build_ac_automation(){
        int i;
        queue<Node*>Q;
        root->fail=NULL;
        Q.push(root);
        while(!Q.empty()){
            Node* temp=Q.front();
            Q.pop();
            Node* p=NULL;
            for(i=0;i<CHARSET;i++){
                if(temp->next[i]!=NULL){//寻找当前子树的失败指针
                    p = temp->fail;
                    while(p!=NULL){
                        if(p->next[i]!=NULL){//找到失败指针
                            temp->next[i]->fail=p->next[i];
                            break;
                        }
                        p=p->fail;
                    }
                    if(p==NULL) temp->next[i]->fail=root;//无法获取，当前子树的失败指针为根
                    Q.push(temp->next[i]);
                }
            }
        }
    }
    int query(char *str){//询问str中包含n个关键字中多少种即匹配
        int i=0,cnt=0,index;
        Node* p = root;
        while(str[i]){
            index=str[i]-'a';
            while(p->next[index]==NULL&&p!=root) p=p->fail;//失配
            p=p->next[index];
            if(p==NULL) p = root;//失配指针为根
            Node* temp = p;
            while(temp!=root&&temp->count!=-1){//寻找到当前位置为止是否出现关键字
                cnt+=temp->count;
                temp->count=-1;
                temp=temp->fail;
            }
            i++;
        }
        return cnt;
    }
};
