//
// Unit tests
//
#include <boost/test/unit_test.hpp>

#include "main.h"
#include "base58.h"

using namespace std;

BOOST_AUTO_TEST_SUITE(SendFee_tests)

BOOST_AUTO_TEST_CASE(ThirdFee)
{
    const int nHeightCorrect = pindexBest->nHeight;
    pindexBest->nHeight = HEIGHT_PROTOCOL_V2 + 1;

    const CBitcoinAddress addressCorrect("CVBy4fjyzT2jHzqGaXDXiZSB8dfKa5dobx");
    const CTxDestination destinationAddressCorrect = addressCorrect.Get();
    CTxOut thirdFeeOutCorrect;
    thirdFeeOutCorrect.scriptPubKey.SetDestination(destinationAddressCorrect);
    thirdFeeOutCorrect.nValue = 833;

    const CBitcoinAddress addressIncorrect("CdbbsQGSVfjwz1kNXVWa5Peo6UQQbM2Fsq");
    const CTxDestination destinationAddressIncorrect = addressIncorrect.Get();
    CTxOut thirdFeeOutIncorrect;
    thirdFeeOutIncorrect.scriptPubKey.SetDestination(destinationAddressIncorrect);
    thirdFeeOutIncorrect.nValue = 834;

    int64_t fee = 2501;

    CTxOut thirdFeeOut = CTxOutForThirdFee(fee);

    //check CTxOutForThirdFee(const int64_t)
    BOOST_CHECK(thirdFeeOut.nValue == 833);
    BOOST_CHECK(thirdFeeOut.nValue != 834);

    BOOST_CHECK(thirdFeeOut.scriptPubKey == thirdFeeOutCorrect.scriptPubKey);
    BOOST_CHECK(thirdFeeOut.scriptPubKey != thirdFeeOutIncorrect.scriptPubKey);

    BOOST_CHECK(thirdFeeOut == thirdFeeOutCorrect);
    BOOST_CHECK(thirdFeeOut != thirdFeeOutIncorrect);


    CTransaction tx;
    tx.vout.push_back(thirdFeeOutIncorrect);
    tx.vout.push_back(thirdFeeOutIncorrect);

    //check ThirdFeeToOurAddress(CTransaction &, int64_t &)
    BOOST_CHECK(ThirdFeeToOurAddress(tx, fee));

    BOOST_CHECK(tx.vout.size() == 3);
    BOOST_CHECK(tx.vout.size() != 4);

    BOOST_CHECK(tx.vout.back() == thirdFeeOutCorrect);
    BOOST_CHECK(tx.vout.back() != thirdFeeOutIncorrect);

    BOOST_CHECK(fee == 1668);
    BOOST_CHECK(fee != 1669);


    //check ThirdFeeToOurAddressCheck(const CTransaction, const int64_t)
    BOOST_CHECK(!ThirdFeeToOurAddressCheck(tx, fee));

    fee = 2501;
    BOOST_CHECK(ThirdFeeToOurAddressCheck(tx, fee));

    tx.vout.pop_back();
    BOOST_CHECK(!ThirdFeeToOurAddressCheck(tx, fee));


    pindexBest->nHeight = nHeightCorrect;
}

BOOST_AUTO_TEST_SUITE_END()
