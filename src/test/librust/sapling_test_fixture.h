// Copyright (c) 2020 The PIVX Developers
Copyright (c) 2020 The Flits Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or https://www.opensource.org/licenses/mit-license.php.

#ifndef fls_SAPLING_TEST_FIXTURE_H
#define fls_SAPLING_TEST_FIXTURE_H

#include "test/test_fls.h"

/**
 * Testing setup that configures a complete environment for Sapling testing.
 */
struct SaplingTestingSetup : public TestingSetup {
    SaplingTestingSetup();
    ~SaplingTestingSetup();
};


#endif //fls_SAPLING_TEST_FIXTURE_H
