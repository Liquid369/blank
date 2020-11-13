// Copyright (c) 2020 The PIVX developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef PIVX_SAPLING_OPERATION_H
#define PIVX_SAPLING_OPERATION_H

#include "amount.h"
#include "sapling/transaction_builder.h"
#include "operationresult.h"
#include "primitives/transaction.h"
#include "wallet/wallet.h"

struct TxValues;

struct ShieldedRecipient
{
    const libzcash::SaplingPaymentAddress address;
    const CAmount amount;
    const std::string memo;
    ShieldedRecipient(const libzcash::SaplingPaymentAddress& _address, const CAmount& _amount, const std::string& _memo) :
        address(_address),
        amount(_amount),
        memo(_memo)
    {}
};

struct SendManyRecipient
{
    const Optional<ShieldedRecipient> shieldedRecipient;
    const Optional<CTxOut> transparentRecipient;

    bool IsTransparent() const { return transparentRecipient != nullopt; }
    bool IsShielded() const { return !IsTransparent(); }

    // Prevent default empty initialization
    SendManyRecipient() = delete;

    // Shielded recipient
    SendManyRecipient(const libzcash::SaplingPaymentAddress& address, const CAmount& amount, const std::string& memo):
        shieldedRecipient(ShieldedRecipient(address, amount, memo))
    { }

    // Transparent recipient: P2PKH
    SendManyRecipient(const CTxDestination& dest, const CAmount& amount):
        transparentRecipient(CTxOut(amount, GetScriptForDestination(dest)))
    {}

    // Transparent recipient: P2CS
    SendManyRecipient(const CKeyID& ownerKey, const CKeyID& stakerKey, const CAmount& amount):
        transparentRecipient(CTxOut(amount, GetScriptForStakeDelegation(stakerKey, ownerKey)))
    {}

    // !TODO: Transparent recipient: multisig and OP_RETURN
};

class FromAddress {
public:
    explicit FromAddress() {};
    explicit FromAddress(const CTxDestination& _fromTaddr) : fromTaddr(_fromTaddr) {};
    explicit FromAddress(const libzcash::SaplingPaymentAddress& _fromSapaddr) : fromSapAddr(_fromSapaddr) {};

    bool isFromTAddress() const { return IsValidDestination(fromTaddr); }
    bool isFromSapAddress() const { return fromSapAddr.is_initialized(); }

    CTxDestination fromTaddr{CNoDestination()};
    Optional<libzcash::SaplingPaymentAddress> fromSapAddr{nullopt};
};

class SaplingOperation {
public:
    explicit SaplingOperation(const Consensus::Params& consensusParams, int chainHeight) : txBuilder(consensusParams, chainHeight) {};
    explicit SaplingOperation(TransactionBuilder& _builder) : txBuilder(_builder) {};

    ~SaplingOperation() { delete tkeyChange; }

    OperationResult build();
    OperationResult send(std::string& retTxHash);
    OperationResult buildAndSend(std::string& retTxHash);

    void setFromAddress(const CTxDestination&);
    void setFromAddress(const libzcash::SaplingPaymentAddress&);
    // In case of no addressFrom filter selected, it will accept any utxo in the wallet as input.
    SaplingOperation* setSelectTransparentCoins(const bool select) { selectFromtaddrs = select; return this; };
    SaplingOperation* setSelectShieldedCoins(const bool select) { selectFromShield = select; return this; };
    SaplingOperation* setRecipients(std::vector<SendManyRecipient>& vec) { recipients = std::move(vec); return this; };
    SaplingOperation* setFee(CAmount _fee) { fee = _fee; return this; }
    SaplingOperation* setMinDepth(int _mindepth) { assert(_mindepth >= 0); mindepth = _mindepth; return this; }
    SaplingOperation* setTxBuilder(TransactionBuilder& builder) { txBuilder = builder; return this; }
    SaplingOperation* setTransparentKeyChange(CReserveKey* reserveKey) { tkeyChange = reserveKey; return this; }

    CTransaction getFinalTx() { return finalTx; }

    // Public only for unit test coverage
    bool getMemoFromHexString(const std::string& s, std::array<unsigned char, ZC_MEMO_SIZE> memoRet, std::string& error);

private:
    FromAddress fromAddress;
    // In case of no addressFrom filter selected, it will accept any utxo in the wallet as input.
    bool selectFromtaddrs{false};
    bool selectFromShield{false};
    std::vector<SendManyRecipient> recipients;
    std::vector<COutput> transInputs;
    std::vector<SaplingNoteEntry> shieldedInputs;
    int mindepth{5}; // Min default depth 5.
    CAmount fee{DEFAULT_SAPLING_FEE}; // Hardcoded fee for now.

    // transparent change
    CReserveKey* tkeyChange{nullptr};

    // Builder
    TransactionBuilder txBuilder;
    CTransaction finalTx;

    OperationResult loadUtxos(TxValues& values);
    OperationResult loadUnspentNotes(TxValues& txValues,
                                     libzcash::SaplingExpandedSpendingKey& expsk,
                                     uint256& ovk);
    OperationResult checkTxValues(TxValues& txValues, bool isFromtAddress, bool isFromShielded);
};

#endif //PIVX_SAPLING_OPERATION_H
