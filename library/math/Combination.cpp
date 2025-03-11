#pragma once
#include "common.cpp"
template <class Type>
class Comb {
public:
    ll n;
    vector<Type> v;
    Comb(ll _n): v(_n+1){
        n=_n;
        v[0]=1;
        for(int i=1;i<=n;i++){
            v[i]=v[i-1]*i;
        }
    }
    Type nCk(ll n,ll k){
        if(n<k)return 0;
        if(n<0 || k<0)return 0;
        return v[n]*v[n-k].inv()*v[k].inv();
    }
    Type nHk(ll n,ll k){
        return nCk(n+k-1,n-1);
    }
};