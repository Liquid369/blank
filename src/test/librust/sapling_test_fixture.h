// Copyright (c) 2020 The PIVX Developers
// Copyright (c) 2020 The DogeCash Developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef DOGEC_SAPLING_TEST_FIXTURE_H
#define DOGEC_SAPLING_TEST_FIXTURE_H

#include "test/test_dogecash.h"

/**
 * Testing setup that configures a complete environment for Sapling testing.
 */
struct SaplingTestingSetup : public TestingSetup {
    SaplingTestingSetup();
    ~SaplingTestingSetup();
};


#endif //DOGEC_SAPLING_TEST_FIXTURE_H
