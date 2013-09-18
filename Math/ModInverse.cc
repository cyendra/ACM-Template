/*==============================================*\ 
 | 逆元 
 | ax≡b(mod m) x=a逆×b 
 | gcd(a,m)!=1逆元不存在 
\*==============================================*/  
int modInverse(int a,int m){  
    int x,y;  
    extgcd(a,m,x,y);  
    return (m+x%m)%m;  
}  
