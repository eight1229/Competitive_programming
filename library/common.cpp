#pragma once
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using ll=long long;
using ld=long double;

#define OVERLOAD_REP(_1, _2, _3, name, ...) name
#define REP1(i, n) for(ll i=0;i<ll(n); i++)
#define REP2(i, l, r) for(ll i=ll(l);i<ll(r); i++)
#define rep(...) OVERLOAD_REP(__VA_ARGS__, REP2, REP1)(__VA_ARGS__)

#define reps(i,l,r) for(ll i=ll(l);i<ll(r); i++)
#define repr(i,n) for(ll i=ll(n-1);i>=0;i--)
#define bit(i,n) for(ll i=0;i<(1ll<<n);i++)
#define dbl(i) fixed << setprecision(15) << i
#define all(a) a.begin(),a.end()
#define st(a) sort(a.begin(),a.end())
#define rst(a) sort(a.rbegin(),a.rend())
using P=pair<ll,ll>;

const int inf=1073741823;
const ll linf=1ll<<60;

template <typename T>
bool chmin(T &a, const T &b) {
    if (a > b) {
        a = b;
        return true;
    }
    return false;
}
template <typename T>
bool chmax(T &a, const T& b) {
    if (a < b) {
        a = b;
        return true;
    }
    return false;
}

template <typename T>
T pow(T a, T n){
    T x = 1;
    while(n > 0){//全てのbitが捨てられるまで。
        if(n&1){//1番右のbitが1のとき。
        x = x*a;
        }
        a = a*a;
        n >>= 1;//bit全体を右に1つシフトして一番右を捨てる。
    }
    return x;
}
//xのn乗(mod)
long long mpow(long long x, long long n,ll m) {
    ll ret=1;
    x%=m;
    while (n > 0) {
        if (n & 1) ret =ret*x % m;  // n の最下位bitが 1 ならば x^(2^i) をかける
        x = x * x % m;
        n >>= 1;  // n を1bit 左にずらす
    }
    return ret;
}
