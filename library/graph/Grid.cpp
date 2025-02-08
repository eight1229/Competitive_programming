#pragma once
#include "common.cpp"
#include "graph/Graph.cpp"

template<typename T, auto cost = [](int i, int j, T vi, T v2, int d){ return 1;}>
class Grid{
    const int h,w;
    optional<T> ban;
    static constexpr pair<int,int> d4[4]={{1,0},{0,1},{-1, 0},{0, -1}};
    template<typename vecvecT> void build(const vecvecT&grid){
        rep(i,h)rep(j,w){
            int p=id(i,j);
            v[p]=grid[i][j];
            if(ban and v[p]==ban.value())continue;
            rep(d,4){
                int i2=i+d4[d].first,j2=j+d4[d].second;
                if(in(i2,j2) and (!ban or ban.value()!=grid[i2][j2]))
                G.add_edge(p,id(i2,j2),cost(p,id(i2,j2),v[p],grid[i2][j2], d));
            }
        }
    }
public:
    vector<T> v;
    WeightedGraph<int> G;
    bool in(int i,int j)const{
        return 0<=i and i<h and 0<=j and j<w;
    }
    int id(int i,int j)const{
        assert(in(i,j));
        return i*w+j;
    }
    pair<int,int> r2(int a)const{
        assert(0<=a and a<h*w);
        return {a/w,a%w};
    }

    Grid(const vector<vector<T>>&grid,const optional<T>&ban=nullopt):h(grid.size()),w(grid[0].size()),ban(ban),v(h*w),G(h*w){ build(grid); }
    Grid(const vector<string>&s,const optional<T>&ban=nullopt):h(s.size()),w(s[0].size()),ban(ban),v(h*w),G(h*w){
        static_assert(is_same<T,char>::value,"value_type==char");
        build(s);
    }
    
    int find(const T&c)const{
        rep(i,h*w)if(v[i]==c)return i;
        return -1;
    }
};