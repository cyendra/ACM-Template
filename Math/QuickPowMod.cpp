/*==============================================*\ 
 | 快速幂 
\*==============================================*/  
LL modPow(LL x,LL n,LL mod){  
    if (n==0) return 1;  
    LL res=modPow(x*x%mod,n/2,mod);  
    if (n&1) res=res*x%mod;  
    return res;  
}  
