#pragma once
#include "common.cpp"
#include "graph/Graph.cpp"

pair<vector<int>,vector<int>> BFS(Graph &g, int s = 0) {
    static constexpr int INF=numeric_limits<int>::max()/2;
    vector<int> d(g.n,INF), prev(g.n,-1);
    queue<int> q;
    d[s] = 0;
    q.emplace(s);
    while(!q.empty()){
        auto v = q.front();
        q.pop();
        for(auto to: g.edges[v]){
            if(d[to]>d[v]+1){
                d[to] = d[v]+1;
                prev[to]=v;
                q.emplace(to);
            }
        }
    }
    return {d,prev};
}