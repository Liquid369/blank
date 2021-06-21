// Copyright (c) 2018 The PIVX Developers
// Copyright (c) 2020 The PIVX Developers
// Copyright (c) 2020 The Rubus Developers


// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RBX_INVALID_H
#define RBX_INVALID_H

#include <set>
#include <string>

class COutPoint;
class UniValue;

namespace invalid_out
{
    extern std::set<COutPoint> setInvalidOutPoints;

    UniValue read_json(const std::string& jsondata);

    bool ContainsOutPoint(const COutPoint& out);
    bool LoadOutpoints();
}

#endif //RBX_INVALID_H
