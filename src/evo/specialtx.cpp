
// Copyright (c) 2017 The Dash Core developers
// Copyright (c) 2020 The fls Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "evo/specialtx.h"

#include "chain.h"
#include "chainparams.h"
#include "clientversion.h"
#include "consensus/validation.h"
#include "primitives/block.h"

bool CheckSpecialTxNoContext(const CTransaction& tx, CValidationState& state)
{
    bool hasExtraPayload = tx.hasExtraPayload();

    if (tx.IsNormalType()) {
        // Type-0 txes don't have extra payload
        if (hasExtraPayload) {
            return state.DoS(100, error("%s: Type 0 doesn't support extra payload", __func__),
                             REJECT_INVALID, "bad-txns-type-payload");
        }
        // Normal transaction. Nothing to check
        return true;
    }

    // Special txes need at least version 2
    if (!tx.isSaplingVersion()) {
        return state.DoS(100, error("%s: Type %d not supported with version %d", __func__, tx.nType, tx.nVersion),
                         REJECT_INVALID, "bad-txns-type-version");
    }

    // --- From here on, tx has nVersion>=2 and nType!=0

    // Cannot be coinbase/coinstake tx
    if (tx.IsCoinBase() || tx.IsCoinStake()) {
        return state.DoS(10, error("%s: Special tx is coinbase or coinstake", __func__),
                         REJECT_INVALID, "bad-txns-special-coinbase");
    }

    // Special txes must have a non-empty payload
    if (!hasExtraPayload) {
        return state.DoS(100, error("%s: Special tx (type=%d) without extra payload", __func__, tx.nType),
                         REJECT_INVALID, "bad-txns-payload-empty");
    }

    // Size limits
    if (tx.extraPayload->size() > MAX_SPECIALTX_EXTRAPAYLOAD) {
        return state.DoS(100, error("%s: Special tx payload oversize (%d)", __func__, tx.extraPayload->size()),
                         REJECT_INVALID, "bad-txns-payload-oversize");
    }

    switch (tx.nType) {
    /* per-tx-type non-contextual checking */
    }

    return state.DoS(10, error("%s: special tx %s with invalid type %d", __func__, tx.GetHash().ToString(), tx.nType),
                     REJECT_INVALID, "bad-tx-type");
}

bool CheckSpecialTx(const CTransaction& tx, const CBlockIndex* pindexPrev, CValidationState& state)
{
    assert(pindexPrev != nullptr);

    if (!CheckSpecialTxNoContext(tx, state)) {
        // pass the state returned by the function above
        return false;
    }

    if (tx.IsNormalType()) {
        // nothing to check
        return true;
    }

    // !TODO: Add enforcement-height check

    switch (tx.nType) {
    /* per-tx-type contextual checking */
    }

    // should never get here, as we already checked the type in CheckSpecialTxNoContext
    return state.DoS(10, error("%s: special tx %s with invalid type %d", __func__, tx.GetHash().ToString(), tx.nType),
                     REJECT_INVALID, "bad-tx-type");
}

bool ProcessSpecialTxsInBlock(const CBlock& block, const CBlockIndex* pindex, CValidationState& state, bool fJustCheck)
{
    // check special txes
    for (const CTransactionRef& tx: block.vtx) {
        if (!CheckSpecialTx(*tx, pindex->pprev, state)) {
            // pass the state returned by the function above
            return false;
        }
    }
    // !TODO: Process batch of special txes in deterministic manager
    return true;
}

bool UndoSpecialTxsInBlock(const CBlock& block, const CBlockIndex* pindexPrev)
{
    /* undo special txes in batches */
    return true;
}

