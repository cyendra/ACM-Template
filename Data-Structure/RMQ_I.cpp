int d[maxn][20];  
//元素从1编号到n  
void RMQ_init(int A[],int n){  
    for (int i=1;i<=n;i++) d[i][0]=A[i];  
    for (int j=1;(1<<j)<=n;j++)  
        for (int i=1;i+(1<<j)-1<=n;i++)  
            d[i][j]=min(d[i][j-1],d[i+(1<<(j-1))][j-1]);  
}  
int RMQ(int L,int R){  
    int k=0;  
    while ((1<<(k+1))<=R-L+1) k++;  
    return min(d[L][k],d[R-(1<<k)+1][k]);  
}  
