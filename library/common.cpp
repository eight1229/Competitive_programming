#pragma once
#include <bits/stdc++.h>
#include <atcoder/all>

using namespace std;
using namespace atcoder;
using ll=long long;
using ld=long double;
#define rep(i,n) for(ll i=0;i<n;i++)
#define irep(i,n) for(ll i=0;i<=n;i++)
#define reps(i,j,n) for(ll i=j;i<n;i++)
#define repr(i,n) for(ll i=n-1;i>=0;i--)
#define bit(i,n) for(ll i=0;i<(1<<n);i++)
#define dbl(i) fixed << setprecision(15) << i
#define all(a) a.begin(),a.end()
#define st(a) sort(a.begin(),a.end())
#define rst(a) sort(a.rbegin(),a.rend())
using P=pair<ll,ll>;
const ll mod=1000000007;
const ll mod1=998244353;
const ll inf=1e9;
const ll linf=1e18;

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
class UnionFind {
public:
    vector <ll> par; // 各元の親を表す配列
    vector <ll> siz; // 素集合のサイズを表す配列(1 で初期化)

    UnionFind(ll sz_): par(sz_), siz(sz_, 1LL) {
        for (ll i = 0; i < sz_; ++i) par[i] = i; // 初期では親は自分自身
    }
    void init(ll sz_) {
        par.resize(sz_);
        siz.assign(sz_, 1LL);  // resize だとなぜか初期化されなかった
        for (ll i = 0; i < sz_; ++i) par[i] = i; // 初期では親は自分自身
    }
    ll root(ll x) { // 根の検索
        while (par[x] != x) {
            x = par[x] = par[par[x]]; // x の親の親を x の親とする
        }
        return x;
    }
    bool unite(ll x, ll y) {
        x = root(x);
        y = root(y);
        if (x == y) return false;
        // merge technique（データ構造をマージするテク．小を大にくっつける）
        if (siz[x] < siz[y]) swap(x, y);
        siz[x] += siz[y];
        par[y] = x;
        return true;
    }

    bool same(ll x, ll y) { // 連結判定
        return root(x) == root(y);
    }

    ll size(ll x) { // 素集合のサイズ
        return siz[root(x)];
    }
};
vector<ll> enum_divisors(ll N) {
    vector<ll> res;
    for (ll i = 1; i * i <= N; ++i) {
        if(N % i == 0) {
            res.push_back(i);
            if (N/i != i) res.push_back(N/i);
        }
    }
    sort(res.begin(), res.end());
    return res;
}
vector<pair<long long, long long> > prime_factorize(long long N) {
    vector<pair<long long, long long> > res;
    for (long long a = 2; a * a <= N; ++a) {
        if (N % a != 0) continue;
        long long ex = 0; // 指数

        // 割れる限り割り続ける
        while (N % a == 0) {
            ++ex;
            N /= a;
        }

        // その結果を push
        res.push_back({a, ex});
    }

    // 最後に残った数について
    if (N != 1) res.push_back({N, 1});
    return res;
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
