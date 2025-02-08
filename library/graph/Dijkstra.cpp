#pragma once
#include "common.cpp"
#include "graph/Graph.cpp"

template<class WG, class T=WG::weight_type>
pair<vector<T>,vector<int>> dijkstra(WG &g, int s = 0){
    static constexpr T INF=numeric_limits<T>::max()/2;
    vector<T> d(g.n, INF);
    vector<int> prev(g.n,-1);
    priority_queue<pair<T,int>,vector<pair<T,int>>, greater<pair<T,int>>> q;
    d[s]=0;
    q.emplace(0,s);
    while(!q.empty()){
        auto [now, index] = q.top();
        q.pop();
        if(d[index]<now)continue;
        for(auto [to,weight]: g.edges[index]){
            if(d[to]>now+weight){
                d[to] = now+weight;
                prev[to] = index;
                q.emplace(d[to],to);
            }
        }
    }
    return {d,prev};
}