#pragma once
using ll=long long;
ll extgcd(ll a,ll b,ll &x,ll &y){
    if(b==0){
        x=1;
        y=0;
        return a;
    }
    ll res=extgcd(b,a%b,x,y);
    ll old=x;
    x=y;
    y=old-y*(a/b);
    return res;
}