#pragma once
#include "common.cpp"
#include "BitCumulativeSum.cpp"
using u32 = std::uint32_t;

class WaveletMatrix
{
    int n, sigma;
    std::vector<BitCumulativeSum> bv;

public:
    WaveletMatrix(std::vector<u32> v) : n(v.size()), sigma(std::bit_width(std::ranges::max(v)))
    {
        bv.assign(sigma, n);
        std::vector<u32> nxt_v(n);
        for (int h = sigma - 1; h >= 0; --h)
        {
            auto &B = bv[h];

            int l = 0, r = n - 1;
            for (int i = n - 1; i >= 0; i--)
                if (has_bit(v[i], h))
                {
                    B.set(i);
                    nxt_v[r--] = v[i];
                }

            B.build();

            for (u32 x : v)
                if (!has_bit(x, h))
                    nxt_v[l++] = x;
            std::swap(v, nxt_v);
        }
    }

    // k-th (0-indexed) smallest number in a[l, r)
    u32 kth_smallest(int l, int r, int k) const
    {
        u32 res = 0;
        for (int h = sigma - 1; h >= 0; --h)
        {
            const auto &B = bv[h];
            int zero_cnt = B.rank0(r) - B.rank0(l);
            if (k >= zero_cnt)
            {
                res |= 1 << h;
                k -= zero_cnt;
                l = B.rank0(n) + B.rank1(l);
                r = B.rank0(n) + B.rank1(r);
            }
            else
            {
                l = B.rank0(l);
                r = B.rank0(r);
            }
        }
        return res;
    }

    // k-th (0-indexed) largest number in a[l, r)
    u32 kth_largest(int l, int r, int k)
    {
        return kth_smallest(l, r, r - l - k - 1);
    }

    // count i s.t. i∈[l,r) && v[i]∈[0,u)
    int range_freq(int l, int r, u32 u)
    {
        if (u >= (1 << sigma))
            return r - l;
        int ret = 0;
        for (int h = sigma - 1; h >= 0; --h)
        {
            auto &B = bv[h];
            if (has_bit(u, h))
            {
                ret += B.rank0(r) - B.rank0(l);
                l = B.rank0(n) + B.rank1(l);
                r = B.rank0(n) + B.rank1(r);
            }
            else
            {
                l = B.rank0(l);
                r = B.rank0(r);
            }
        }
        return ret;
    }

    // count i s.t. i∈[l,r) && v[i]∈[d,u)
    int range_freq(int l, int r, u32 d, u32 u)
    {
        return range_freq(l, r, u) - range_freq(l, r, d);
    }
};