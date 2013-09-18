void LXS(int* a,int* f,int n)  
{  
    vector<int>d;  
    int l,r;  
    REP(i,n)  
    {  
        //l=lower_bound(d.begin(),d.end(),a[i])-d.begin();  
        r=upper_bound(d.begin(),d.end(),a[i])-d.begin();  
        if (r==sz(d)) d.push_back(a[i]);  
        else d[r]=a[i];  
        f[i]=r+1;  
    }  
}  
