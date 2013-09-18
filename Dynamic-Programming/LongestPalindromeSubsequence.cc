const int maxn=1111;  
int a[maxn];  
int f[maxn][maxn];  
int n;  
int prev(int x){  
    return (x-1+n)%n;  
}  
int next(int x){  
    return (x+1)%n;  
}  
int dp(int l,int r){  
    if (l==r) return 1;  
    if (next(l)==r) return 1+(a[l]==a[r]);  
    if (f[l][r]!=-1) return f[l][r];  
    if (a[l]==a[r]) return f[l][r]=dp(next(l),prev(r))+2;  
    return f[l][r]=max(dp(next(l),r),dp(l,prev(r)));  
}  
int main()  
{  
    int ans;  
    while (~scanf("%d",&n)){  
        if (n==0) break;  
        ans=0;  
        memset(f,-1,sizeof(f));  
        for (int i=0;i<n;i++){  
            scanf("%d",&a[i]);  
        }  
        if (n==1) ans=1;  
        else if (n==2) ans=2;  
        else{  
            for (int i=0;i<n;i++){  
                ans=max(ans,dp(next(i),prev(i))+1);  
                //ans=max(ans,dp(i,prev(i)));  
                ans=max(ans,dp(next(i),i));  
            }  
        }  
        printf("%d\n",ans);  
    }  
    return 0;  
}  
