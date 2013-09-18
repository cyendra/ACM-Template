#include <iostream>
#include <cstring>
#include <algorithm>
#include <cstdio>
using namespace std;

typedef unsigned long long ULL;

const int SIZE = 100003;
const int SEED = 13331;
const int MAX_N = 50000 + 10;
char s[MAX_N];
struct HASH{
    ULL H[MAX_N];
    ULL XL[MAX_N];
    int len;
    HASH(){}
    void build(char *s){
        len=strlen(s);
        H[len]=0;
        XL[0]=1;
        for (int i=len-1;i>=0;i--){
            H[i]=H[i+1]*SEED+s[i];
            XL[len-i]=XL[len-i-1]*SEED;
        }
    }
    ULL hash(int i,int L){
        return H[i]-H[i+L]*XL[L];
    }
}hs;
