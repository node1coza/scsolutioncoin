// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2012 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// Thanks and Credits for Technologies found in SCSolutionCoin: Bitcoin, Novacoin, Blackcoin, Bitmessage, Shadowcoin, Cryptonote
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "assert.h"

#include "chainparams.h"
#include "main.h"
#include "util.h"
#include <scrypt.h>
#include <iostream>
#include <fstream>

#include "boost/assign/list_of.hpp"

using namespace boost::assign;
using namespace std;

struct SeedSpec6 {
    uint8_t addr[16];
    uint16_t port;
};

//#include "chainparamsseeds.h"

unsigned int pnSeed[] =
{
    0x8C99202D,
    0xAE004D2D,
    0x1A3E202D,
    0x58234D2D,
};


int64_t CChainParams::GetProofOfWorkReward(int nHeight, int64_t nFees) const
{
    // miner's coin base reward
    int64_t nSubsidy = 0;
    
    if (nHeight == 3)
        nSubsidy =  500000000;
 //   else
 //   if (nHeight <= nDistributionFund)
//        nSubsidy = 2691000 * COIN;
//	else
 //   if (nHeight <= nLastFairLaunchBlock)
 //       nSubsidy = 1 * COIN;
 //   else
 //   if (nHeight <= nLastPOWBlock)
 //       nSubsidy = 2000 * COIN;
    


    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfWorkReward() : create=%s nSubsidy=%d\n", FormatMoney(nSubsidy).c_str(), nSubsidy);
    
    return nSubsidy + nFees;
};


int64_t CChainParams::GetProofOfStakeReward(int64_t nCoinAge, int64_t nFees) const
{
	//if (nHeight == 1)
	//	nSubsidy = 500000000 * COIN;
	
    // miner's coin stake reward based on coin age spent (coin-days)
    int64_t nSubsidy = nCoinAge * ZCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    
    if (pindexBest->nHeight <= nFirstYearStake)
        nSubsidy = nCoinAge * COIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else
    if (pindexBest->nHeight <= nFirstBlockHalve)
        nSubsidy = nCoinAge * SCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nSecondBlockHalve)
        nSubsidy = nCoinAge * CCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nThirdBlockHalve)
        nSubsidy = nCoinAge * KCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nFourthBlockHalve)
        nSubsidy = nCoinAge * ICOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nFifthBlockHalve)
        nSubsidy = nCoinAge * OCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nSixthBlockHalve)
        nSubsidy = nCoinAge * DCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nSeventhBlockHalve)
        nSubsidy = nCoinAge * RCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nEighthBlockHalve)
        nSubsidy = nCoinAge * ECOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nNinthBlockHalve)
        nSubsidy = nCoinAge * ACOIN_YEAR_REWARD * 33 / (365 * 33 + 8);
    else	
    if (pindexBest->nHeight <= nTenthBlockHalve)
        nSubsidy = nCoinAge * MCOIN_YEAR_REWARD * 33 / (365 * 33 + 8);


    if (fDebug && GetBoolArg("-printcreation"))
        LogPrintf("GetProofOfStakeReward(): create=%s nCoinAge=%d\n", FormatMoney(nSubsidy).c_str(), nCoinAge);
    
    return nSubsidy + nFees;
}

//
// Main network
//

// Convert the pnSeeds6 array into usable address objects.
static void convertSeed6(std::vector<CAddress> &vSeedsOut, const SeedSpec6 *data, unsigned int count)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in6_addr ip;
        memcpy(&ip, data[i].addr, sizeof(ip));
        CAddress addr(CService(ip, data[i].port));
        addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

// Convert the pnSeeds6 array into usable address objects.
static void convertSeeds(std::vector<CAddress> &vSeedsOut, unsigned int *data, unsigned int count, int port)
{
    // It'll only connect to one or two seed nodes because once it connects,
    // it'll get a pile of addresses with newer timestamps.
    // Seed nodes are given a random 'last seen time' of between one and two
    // weeks ago.
    const int64_t nOneWeek = 7*24*60*60;
    for (unsigned int i = 0; i < count; i++)
    {
        struct in_addr ip;
        memcpy(&ip, &pnSeed[i], sizeof(ip));
        CAddress addr(CService(ip, Params().GetDefaultPort()));
        addr.nTime = GetTime()-GetRand(nOneWeek)-nOneWeek;
        vSeedsOut.push_back(addr);
    }
}

class CMainParams : public CChainParams {
public:
    CMainParams() {
        strNetworkID = "main";
        
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfc;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0x0d;
        pchMessageStart[3] = 0x69;
        
        vAlertPubKey = ParseHex("0442199e1ba91b8d726160247ff58cf8aa8030054e778c496a1271d190414d1e5babeb9fbb2ec594cbde7d299cb2d529f9dcee06d180315eec72c532b40dff1e5f");
        
        nDefaultPort = 51332;
        nRPCPort = 51333;
        
        nFirstPosv2Block = 5;
        
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 20); // "standard" scrypt target limit for proof of work, results with 0,000244140625 proof-of-work difficulty
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 48);
        
        const char* pszTimestamp = "www.coins.live/Monero Support for the Ledger Hardware Wallet Inches Closer to Completion";
        CTransaction txNew;
        txNew.nTime = GENESIS_BLOCK_TIME;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 0 << CBigNum(42) << std::vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].SetEmpty();
        
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = GENESIS_BLOCK_TIME;
        genesis.nBits    = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce   = 0; //1516190701;

        hashGenesisBlock = genesis.GetHash();
        //LogPrintf("genesis.BuildMerkleTree() = %s \n", genesis.BuildMerkleTree().ToString().c_str());
        //LogPrintf("Genesis.getHash() = %s \n", genesis.GetHash().ToString().c_str());
        //LogPrintf(" A:%s\n B:%d\n", hashGenesisBlock.ToString().c_str(), uint256("0xb91368e61be846b46b73aaf60d57773355206959d39687065a35209de4ca998f").ToString().c_str());
        assert(hashGenesisBlock == uint256("0xb91368e61be846b46b73aaf60d57773355206959d39687065a35209de4ca998f"));
        
        assert(genesis.hashMerkleRoot == uint256("0x87ea4671d2c81fa31ce0f60a56f5bc1d26bd93238f288165994c02412b68c72e"));


        vSeeds.push_back(CDNSSeedData("scsolutioncoin.net", "scsolutioncoin.net"));
        
        
        base58Prefixes[PUBKEY_ADDRESS] = list_of(25)                    .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(26)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(184)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0xa3)(0xBC)(0x13)(0xc7).convert_to_container<std::vector<unsigned char> >();  // need to change, to  
        base58Prefixes[EXT_SECRET_KEY] = list_of(0xa3)(0xCB)(0x1D)(0x53).convert_to_container<std::vector<unsigned char> >();  // need to change to 
        
        //convertSeed6(vFixedSeeds, pnSeed6_main, ARRAYLEN(pnSeed6_main));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);
        
        // 1 Year aprox = 501257 blocks /  4 Year aprox = 2005028 blocks
        nTenthBlockHalve = 14556453; // + 4 year blocks average                  x 0.05
        nNinthBlockHalve = 12551425; // + 4 year blocks average                   x 0.1
        nEighthBlockHalve = 10546397; // + 4 year blocks average                  x 0.25
        nSeventhBlockHalve = 8541369; // + 4 year blocks average                 x 0.5
        nSixthBlockHalve = 6536341; // + 4 year blocks average                      x 1
        nFifthBlockHalve = 4531313; // + 4 year blocks average                       x 2
        nFourthBlockHalve = 2526285; // + 1 year blocks average                    x 2.5
        nThirdBlockHalve = 2025028; // + 1 year blocks average                      x 5
        nSecondBlockHalve = 1523771; // + 1 year blocks average                   x 10
        nFirstBlockHalve = 1022514; // + 1 year blocks average - 10k blockupdt x 20
        nFirstYearStake = 531257;  // 501257 blocks/year + 20k blocks(nov 30) + 10 k blocksupdate x 69
        
        nLastPOWBlock = 4;
        nLastFairLaunchBlock = 30;
        nDistributionFund = 1;
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const std::vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    std::vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;

//
// Testnet
//

class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        strNetworkID = "test";
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0x0a;
        pchMessageStart[1] = 0xa9;
        pchMessageStart[2] = 0x7a;
        pchMessageStart[3] = 0x0f;
        
        
        nFirstPosv2Block = 5;
        
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 16);
        bnProofOfStakeLimit = CBigNum(~uint256(0) >> 20);
        bnProofOfStakeLimitV2 = CBigNum(~uint256(0) >> 16);
        
        vAlertPubKey = ParseHex("04c25398b68bca9178e6b2ff4cddc8188608b9274921539e65af6e3b3199fbd8d3d9069d2c154aa3dbd54f89cd0bd8c04f0ba39bb100bc8ae25af2cf7fae21fd6c");
        nDefaultPort = 51333;
        nRPCPort = 52333;
        strDataDir = "testnet";

        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        //LogPrintf("Testnet Genesis.getHash() = %s \n", genesis.GetHash().ToString().c_str());
        //LogPrintf(" TestnetA:%s\n TestnetB:%d\n", hashGenesisBlock.ToString().c_str(), uint256("0xb91368e61be846b46b73aaf60d57773355206959d39687065a35209de4ca998f").ToString().c_str());
        assert(hashGenesisBlock == uint256("0x291f4148480c7426b2fef13c37fe6a9404ea0bc8df3d1d99f7ae2c506fbe7f8c"));

        vFixedSeeds.clear();
        vSeeds.clear();

        base58Prefixes[PUBKEY_ADDRESS] = list_of(25)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SCRIPT_ADDRESS] = list_of(26)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[SECRET_KEY]     = list_of(196)                   .convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x05)(0x33)(0x12)(0xBC).convert_to_container<std::vector<unsigned char> >();
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x33)(0x11)(0x46).convert_to_container<std::vector<unsigned char> >();
        
        //convertSeed6(vFixedSeeds, pnSeed6_test, ARRAYLEN(pnSeed6_test));
        convertSeeds(vFixedSeeds, pnSeed, ARRAYLEN(pnSeed), nDefaultPort);

        //nLastPOWBlock = 0x00;
    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        strNetworkID = "regtest";
        pchMessageStart[0] = 0xab;
        pchMessageStart[1] = 0x4b;
        pchMessageStart[2] = 0xe3;
        pchMessageStart[3] = 0xaa;
        bnProofOfWorkLimit = CBigNum(~uint256(0) >> 1);
        genesis.nTime = 1516190701;
        genesis.nBits  = bnProofOfWorkLimit.GetCompact();
        genesis.nNonce = 0;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 52333;
        strDataDir = "regtest";
        //LogPrintf("Regtest Genesis.getHash() = %s \n", genesis.GetHash().ToString().c_str());
        //LogPrintf(" RegTestA:%s\n RegTestB:%d\n", hashGenesisBlock.ToString().c_str(), uint256("0xb91368e61be846b46b73aaf60d57773355206959d39687065a35209de4ca998f").ToString().c_str());
        assert(hashGenesisBlock == uint256("0x676f3e112bdba6f49722c1d90933cf241b053d4899ece42effeb330e3780404b"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

const CChainParams &TestNetParams() {
    return testNetParams;
}

const CChainParams &MainNetParams() {
    return mainParams;
}

void SelectParams(CChainParams::Network network)
{
    switch (network)
    {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    };
};

bool SelectParamsFromCommandLine()
{
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest)
    {
        return false;
    };

    if (fRegTest)
    {
        SelectParams(CChainParams::REGTEST);
    } else
    if (fTestNet)
    {
        SelectParams(CChainParams::TESTNET);
    } else
    {
        SelectParams(CChainParams::MAIN);
    };
    
    return true;
}

void write_to_log(const std::string &text)
{
   std::ofstream hashes_log("hashes.log");
                hashes_log << text;
}
