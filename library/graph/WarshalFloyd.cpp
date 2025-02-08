#pragma once
#include "common.cpp"
#include "graph/Graph.cpp"

template<class WG, class T=WG::weight_type>
vector<vector<T>> warshal_floyd(WG &g){
    static constexpr T INF=numeric_limits<T>::max()/2;
    vector<vector<T>> res(g.n, vector<T>(g.n, INF));
    rep(i,g.n)res[i][i]=0;
    rep(i,g.n){
        for(auto [to,weight]: g.edges[i]){
            chmin(res[i][to], weight);
        }
    }
    rep(k,g.n){
        rep(i,g.n){
            rep(j,g.n){
                chmin(res[i][j], res[i][k]+res[k][j]);
            }
        }
    }
    return res;
}