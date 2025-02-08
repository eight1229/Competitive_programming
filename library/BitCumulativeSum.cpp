#pragma once
#include "common.cpp"
using u64 = std::uint64_t;

bool has_bit(u64 x, int i) { return (x >> i) & 1; }

class BitCumulativeSum
{
    inline static constexpr int w = 64;
    std::vector<u64> block; // bit列をwごとに保持
    std::vector<int> sum;             // 累積和
public:
    BitCumulativeSum() = default;
    BitCumulativeSum(int n) : block(n / w + 1, 0), sum(1, 0)
    {
        sum.reserve(block.size() + 1);
    }

    void set(int i) { block[i / w] |= 1LL << (i % w); }

    void build()
    {
        for (const auto &b : block)
            sum.push_back(sum.back() + __builtin_popcountll(b));
    }

    int rank1(int r) const
    {
        return sum[r / w] + __builtin_popcountll(block[r / w] & ((1LL << (r % w)) - 1));
    }
    int rank0(int r) const { return r - rank1(r); }
};