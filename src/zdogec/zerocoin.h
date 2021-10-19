// Copyright (c) 2017-2020 The PIVX Developers
// Copyright (c) 2020 The Deviant Developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DEV_ZEROCOIN_H
#define DEV_ZEROCOIN_H

#include "uint256.h"
#include "libzerocoin/bignum.h"

uint256 GetPubCoinHash(const CBigNum& bnValue);

#endif //DEV_ZEROCOIN_H
