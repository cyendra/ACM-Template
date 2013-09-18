int d[maxn][20];  
//元素从1编号到n  
void makeRmqIndex(int A[],int n){  
    for(int i=1;i<=n;i++) d[i][0]=i;  
    for(int j=1;(1<<j)<=n;j++)  
        for(int i=1;i+(1<<j)-1<=n;i++)  
            d[i][j] = A[d[i][j-1]] < A[d[i+(1<<(j-1))][j-1]]? d[i][j-1]:d[i+(1<<(j-1))][j-1];  
}  
int rmqIndex(int L,int R,int A[])  
{  
    int k=0;  
    while ((1<<(k+1))<=R-L+1) k++;  
    return A[d[L][k]]<A[d[R-(1<<k)+1][k]]? d[L][k]:d[R-(1<<k)+1][k];  
}  
