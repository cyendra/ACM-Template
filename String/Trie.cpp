const int CHARSET = 26;
const int MAX_N_NODES = int(3e5) + 10;
struct TrieNode
{
    TrieNode* next[CHARSET];
    int num;//记录是不是一个单词
    int value;//记录单词出现的次数
    TrieNode(){
       memset(next,0,sizeof(next));
       value=0;
       num=0;
    }
    void clear(){
       memset(next,0,sizeof(next));
       value=0;
       num=0;
    }
}*root;
TrieNode nodePool[MAX_N_NODES],*cur;
TrieNode* newNode(){
	TrieNode* t = cur++;
	t->clear();
	return t;
}
void trieInit() {
	cur=nodePool;
	root=newNode();
}
//插入：
void insert(char* s){
    TrieNode* p=root;
    int k=0;
    while(s[k]!='\0'){
        if(!p->next[s[k]-'a']) p->next[s[k]-'a']=newNode();
        p=p->next[s[k]-'a'];
        p->num++;
        k++;
    }
    p->value=1;
}
//查找
int find(char* s){
    TrieNode* p=root;
    int k=0;
    while(s[k]!='\0'&&p->next[s[k]-'a']){
        p=p->next[s[k]-'a'];
        k++;
    }
    if(s[k]=='\0') return p->num;
    return 0;
}
//DP查找
void dpfind(char* s,int pos){
    TrieNode* p=root;
    int k=0;
    while(s[k]!='\0'&&p->next[s[k]-'a']){
        p=p->next[s[k]-'a'];
        if (p->value==1){
            //do something like dp...
            //f[pos+k+1]=(f[pos+k+1]+f[pos])%MOD;
        }
        k++;
    }
}
