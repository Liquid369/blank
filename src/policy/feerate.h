// Copyright (c) 2009-2017 The Bitcoin Core developers
// Copyright (c) 2017-2020 The PIVX Developers
// Copyright (c) 2020 The Flits Developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef FLS_POLICY_FEERATE_H
#define FLS_POLICY_FEERATE_H

#include "amount.h"
#include "serialize.h"

#include <string>

extern const std::string CURRENCY_UNIT;

/**
 * Fee rate in FLS per kilobyte: CAmount / kB
 */
class CFeeRate
{
private:
    CAmount nSatoshisPerK; // unit is satoshis-per-1,000-bytes
public:
    CFeeRate() : nSatoshisPerK(0) {}
    explicit CFeeRate(const CAmount& _nSatoshisPerK) : nSatoshisPerK(_nSatoshisPerK) {}
    CFeeRate(const CAmount& nFeePaid, size_t nSize);

    CAmount GetFee(size_t size) const;                  // unit returned is satoshis
    CAmount GetFeePerK() const { return GetFee(1000); } // satoshis-per-1000-bytes

    friend bool operator<(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK < b.nSatoshisPerK; }
    friend bool operator>(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK > b.nSatoshisPerK; }
    friend bool operator==(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK == b.nSatoshisPerK; }
    friend bool operator<=(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK <= b.nSatoshisPerK; }
    friend bool operator>=(const CFeeRate& a, const CFeeRate& b) { return a.nSatoshisPerK >= b.nSatoshisPerK; }
    CFeeRate& operator+=(const CFeeRate& a) { nSatoshisPerK += a.nSatoshisPerK; return *this; }
    std::string ToString() const;

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action)
    {
        READWRITE(nSatoshisPerK);
    }
};

#endif //  FLS_POLICY_FEERATE_H
