// Copyright (c) 2017-2020 The PIVX Developers
// Copyright (c) 2020 The DogeCash Developers

// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef RECEIVEWIDGET_H
#define RECEIVEWIDGET_H

#include "qt/dogecash/pwidget.h"
#include "addresstablemodel.h"
#include "qt/dogecash/furabstractlistitemdelegate.h"
#include "qt/dogecash/addressfilterproxymodel.h"

#include <QSpacerItem>
#include <QWidget>
#include <QPixmap>

class DOGECGUI;
class SendCoinsRecipient;

namespace Ui {
class ReceiveWidget;
}

QT_BEGIN_NAMESPACE
class QModelIndex;
QT_END_NAMESPACE

class ReceiveWidget : public PWidget
{
    Q_OBJECT

public:
    explicit ReceiveWidget(DOGECGUI* parent);
    ~ReceiveWidget();

    void loadWalletModel() override;

public Q_SLOTS:
    void onRequestClicked();
    void onMyAddressesClicked();
    void onNewAddressClicked();

private Q_SLOTS:
    void changeTheme(bool isLightTheme, QString &theme) override ;
    void onLabelClicked();
    void onCopyClicked();
    void refreshView(const QModelIndex& tl, const QModelIndex& br);
    void refreshView(QString refreshAddress = QString());
    void handleAddressClicked(const QModelIndex &index);
    void onSortChanged(int idx);
    void onSortOrderChanged(int idx);
private:
    Ui::ReceiveWidget *ui{nullptr};

    FurAbstractListItemDelegate *delegate{nullptr};
    AddressTableModel* addressTableModel{nullptr};
    AddressFilterProxyModel *filter{nullptr};

    QSpacerItem *spacer{nullptr};

    // Cached last address
    SendCoinsRecipient *info{nullptr};
    // Cached qr
    QPixmap *qrImage{nullptr};

    // Cached sort type and order
    AddressTableModel::ColumnIndex sortType = AddressTableModel::Label;
    Qt::SortOrder sortOrder = Qt::AscendingOrder;

    void updateQr(QString& address);
    void updateLabel();
    void showAddressGenerationDialog(bool isPaymentRequest);
    void sortAddresses();
    void onTransparentSelected(bool transparentSelected);

    bool isShowingDialog{false};
    // Whether the main section is presenting a shielded address or a regular one
    bool shieldedMode{false};

};

#endif // RECEIVEWIDGET_H
