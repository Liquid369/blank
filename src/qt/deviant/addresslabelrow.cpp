// Copyright (c) 2019 The PIVX Developers
// Copyright (c) 2020 The PIVX Developers
// Copyright (c) 2020 The Deviant Developers


// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "qt/deviant/addresslabelrow.h"
#include "qt/deviant/forms/ui_addresslabelrow.h"

AddressLabelRow::AddressLabelRow(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AddressLabelRow)
{
    ui->setupUi(this);
    ui->lblAddress->setProperty("cssClass", "text-list-body1");
    ui->lblLabel->setProperty("cssClass", "text-list-title1");
}

void AddressLabelRow::init(bool isLightTheme, bool isHover)
{
    updateState(isLightTheme, isHover, false);
}

void AddressLabelRow::updateView(QString address, QString label)
{
    ui->lblAddress->setText(address);
    ui->lblLabel->setText(label);
}

void AddressLabelRow::updateState(bool isLightTheme, bool isHovered, bool isSelected)
{
    ui->lblDivisory->setStyleSheet("background-color:#18171D");
    ui->btnMenu->setVisible(isHovered);
}

void AddressLabelRow::enterEvent(QEvent *)
{
    ui->btnMenu->setVisible(true);
    update();
}

void AddressLabelRow::leaveEvent(QEvent *)
{
    ui->btnMenu->setVisible(false);
    update();
}

AddressLabelRow::~AddressLabelRow()
{
    delete ui;
}
