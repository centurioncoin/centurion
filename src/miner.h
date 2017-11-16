// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2013 The NovaCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef NOVACOIN_MINER_H
#define NOVACOIN_MINER_H

#include "main.h"
#include "wallet.h"

static const uint32_t PREMINE_HEIGHT = 719001;
static const uint32_t PREMINE_OUTPUT_length = 5;
static const uint64_t PREMINE_OUTPUT_value[] = {
    500000000 * COIN,
    100000000 * COIN,
     50000000 * COIN,
     25000000 * COIN,
     25000000 * COIN,
};
static const char PREMINE_OUTPUT_address[][35] = {
    "CQUESEK7vV5fgnKSeLndS8PELGbe4Md5ye",
    "CKtdTWW9qxMYnPoDrtGA96ajkJaj5hXzf4",
    "CUWXgagZHEApTMv6VKbjHZNUeSC972CHp5",
    "CcGQHf4ufcQWaXPKQEHFPkkG33bEM1CtLJ",
    "CX2cYTrYCXEzEzeg8ktMRd92x7GxW3XpFU",
};

/* Generate a new block, without valid proof-of-work */
CBlock* CreateNewBlock(CWallet* pwallet, bool fProofOfStake=false, int64_t* pFees = 0);

/** Modify the extranonce in a block */
void IncrementExtraNonce(CBlock* pblock, CBlockIndex* pindexPrev, unsigned int& nExtraNonce);

/** Do mining precalculation */
void FormatHashBuffers(CBlock* pblock, char* pmidstate, char* pdata, char* phash1);

/** Check mined proof-of-work block */
bool CheckWork(CBlock* pblock, CWallet& wallet, CReserveKey& reservekey);

/** Check mined proof-of-stake block */
bool CheckStake(CBlock* pblock, CWallet& wallet);

/** Base sha256 mining transform */
void SHA256Transform(void* pstate, void* pinput, const void* pinit);

inline uint64_t GetAllPremine() {
    uint64_t premine = 0;
    for(int i = 0; i < sizeof(PREMINE_OUTPUT_value)/sizeof(*PREMINE_OUTPUT_value); ++i)
        premine += PREMINE_OUTPUT_value[i];
    return premine;
}

std::unique_ptr<CBlock> generatePowBlock(CWallet *pwallet, uint64_t& nMaxTries, std::function<bool ()> fnContinue);

bool ProofOfWorkMiner(CWallet *pwallet);

#endif // NOVACOIN_MINER_H
