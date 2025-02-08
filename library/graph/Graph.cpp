#pragma once
#include "common.cpp"

class Graph{
public:
    int n;
    vector<vector<int>> edges;
    Graph(int _n):n(_n){
        edges.resize(n);
    }
    void add_edge(int from, int to){
        assert(0<=from&&from<n);
        assert(0<=to&&to<n);
        edges[from].emplace_back(to);
    }
};

template<class T>
class WeightedGraph{
public:
    int n;
    using weight_type = T;
    vector<vector<pair<int,T>>> edges;

    WeightedGraph(int _n):n(_n){
        edges.resize(n);
    }
    void add_edge(int from, int to, T weight){
        assert(0<=from&&from<n);
        assert(0<=to&&to<n);
        edges[from].emplace_back(make_pair(to, weight));
    }
};