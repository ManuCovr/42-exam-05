#pragma once
#include <string>
#include <iostream>
#include <algorithm>

class bigint {
    std::string nbr;
public:
    bigint() : nbr("0") {}
    bigint(size_t num) : nbr(std::to_string(num)) {}
    bigint(std::string num) : nbr(num) {}

    friend std::ostream &operator<<(std::ostream &os, const bigint &b) { return os << b.nbr; }

    std::string add_string(const std::string s1, const std::string s2) const {
        int i = s1.size() - 1, j = s2.size() - 1, carry = 0;
        std::string res;
        while (i >= 0 || j >= 0 || carry) {
            int sum = (i >= 0 ? s1[i--] - '0' : 0) + (j >= 0 ? s2[j--] - '0' : 0) + carry;
            res.push_back(sum % 10 + '0');
            carry = sum / 10;
        }
        std::reverse(res.begin(), res.end());
        return res;
    }

    bigint  operator+ (const bigint b)  const { return bigint(add_string(nbr, b.nbr)); }
    bigint  operator+=(bigint b)              { nbr = add_string(nbr, b.nbr); return *this; }
    bigint &operator++()                      { *this += bigint(1); return *this; }
    bigint  operator++(int)                   { bigint tmp(nbr); ++(*this); return tmp; }

    bigint  operator<< (size_t sh) const { return nbr == "0" ? bigint(nbr) : bigint(nbr + std::string(sh, '0')); }
    bigint &operator<<=(size_t sh)       { if (nbr != "0") nbr += std::string(sh, '0'); return *this; }
    bigint &operator>>=(const bigint sh) {
        if (bigint(nbr.size()) < sh) nbr = "0";
        else { bigint i(0); while (i < sh) { nbr = nbr.substr(0, nbr.size() - 1); ++i; } }
        if (nbr.empty()) nbr = "0";
        return *this;
    }

    bool operator< (const bigint &b) const { return nbr.size() != b.nbr.size() ? nbr.size() < b.nbr.size() : nbr < b.nbr; }
    bool operator> (const bigint &b) const { return b < *this; }
    bool operator==(const bigint &b) const { return nbr == b.nbr; }
    bool operator!=(const bigint &b) const { return !(b == *this); }
    bool operator>=(const bigint &b) const { return !(*this < b); }
    bool operator<=(const bigint &b) const { return !(*this > b); }
};
