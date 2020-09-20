// Copyright (c) 2014-2015 The Dash developers
// Copyright (c) 2015-2020 The PIVX developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef MASTERNODE_BUDGET_H
#define MASTERNODE_BUDGET_H

#include "base58.h"
#include "budget/budgetmanager.h"
#include "budget/budgetproposal.h"
#include "budget/budgetvote.h"
#include "budget/finalizedbudget.h"
#include "budget/finalizedbudgetvote.h"
#include "init.h"
#include "key.h"
#include "masternode.h"
#include "net.h"
#include "sync.h"
#include "util.h"

#include <atomic>
#include <univalue.h>

void DumpBudgets(CBudgetManager& budgetman);

/** Save Budget Manager (budget.dat)
 */
class CBudgetDB
{
private:
    fs::path pathDB;
    std::string strMagicMessage;

public:
    enum ReadResult {
        Ok,
        FileError,
        HashReadError,
        IncorrectHash,
        IncorrectMagicMessage,
        IncorrectMagicNumber,
        IncorrectFormat
    };

    CBudgetDB();
    bool Write(const CBudgetManager& objToSave);
    ReadResult Read(CBudgetManager& objToLoad, bool fDryRun = false);
};

#endif
