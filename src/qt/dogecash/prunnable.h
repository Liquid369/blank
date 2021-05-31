// Copyright (c) 2019 The PIVX Developers
// Copyright (c) 2020 The PIVX Developers
// Copyright (c) 2020 The DogeCash Developers


// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DOGEC_CORE_NEW_GUI_PRUNNABLE_H
#define DOGEC_CORE_NEW_GUI_PRUNNABLE_H

class Runnable {
public:
    virtual void run(int type) = 0;
    virtual void onError(QString error, int type) = 0;
};

#endif //DOGEC_CORE_NEW_GUI_PRUNNABLE_H
