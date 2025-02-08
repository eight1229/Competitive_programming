#pragma once
#include "common.cpp"
#include "graph/Graph.cpp"

template<class WG, class T=WG::weight_type>
pair<vector<T>,vector<int>> BFS01(WG &g, int s = 0) {
    static constexpr int INF=numeric_limits<T>::max()/2;
    vector<T> d(g.n,INF);
    vector<int> prev(g.n,-1);
    deque<pair<T,int>> q;
    d[s] = 0;
    q.emplace_back(0,s);
    while(!q.empty()){
        auto [now,index] = q.front();
        q.pop_front();
        if(d[index]<now)continue;
        for(auto [to,weight]: g.edges[index]){
            assert(weight == 0 || weight ==1);
            if(d[to]>now+weight){
                d[to] =now+weight;
                prev[to]=index;
                if(weight == 0){
                    q.emplace_front(d[to],to);
                }else{
                    q.emplace_back(d[to],to);
                }
            }
        }
    }
    return {d,prev};
}