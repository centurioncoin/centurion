// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2013 The NovaCoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef NOVACOIN_MINER_H
#define NOVACOIN_MINER_H

#include "main.h"
#include "wallet.h"

static const uint32_t PREMINE_HEIGHT = HEIGHT_PROTOCOL_V2 + 1;
const std::vector<std::pair<const char *, const int64_t>> PREMINE =
{
    {"CQUESEK7vV5fgnKSeLndS8PELGbe4Md5ye", 500000000l * COIN},
    {"CKtdTWW9qxMYnPoDrtGA96ajkJaj5hXzf4", 100000000l * COIN},
    {"CUWXgagZHEApTMv6VKbjHZNUeSC972CHp5", 50000000l * COIN},
    {"CcGQHf4ufcQWaXPKQEHFPkkG33bEM1CtLJ", 25000000l * COIN},
    {"CX2cYTrYCXEzEzeg8ktMRd92x7GxW3XpFU", 25000000l * COIN},
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

std::unique_ptr<CBlock> generatePowBlock(CWallet *pwallet, uint64_t& nMaxTries, std::function<bool ()> fnContinue);

bool ProofOfWorkMiner(CWallet *pwallet);

#endif // NOVACOIN_MINER_H
