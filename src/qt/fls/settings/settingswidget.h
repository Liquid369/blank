// Copyright (c) 2019-2020 The PIVX Developers
Copyright (c) 2020-2021 The Flits Developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef SETTINGSWIDGET_H
#define SETTINGSWIDGET_H

#include <QWidget>
#include "qt/fls/pwidget.h"
#include "qt/fls/settings/settingsbackupwallet.h"
#include "qt/fls/settings/settingsexportcsv.h"
#include "qt/fls/settings/settingsbittoolwidget.h"
#include "qt/fls/settings/settingssignmessagewidgets.h"
#include "qt/fls/settings/settingswalletrepairwidget.h"
#include "qt/fls/settings/settingswalletoptionswidget.h"
#include "qt/fls/settings/settingsmainoptionswidget.h"
#include "qt/fls/settings/settingsdisplayoptionswidget.h"
#include "qt/fls/settings/settingsmultisendwidget.h"
#include "qt/fls/settings/settingsinformationwidget.h"
#include "qt/fls/settings/settingsconsolewidget.h"

class flsGUI;

QT_BEGIN_NAMESPACE
class QDataWidgetMapper;
QT_END_NAMESPACE

namespace Ui {
class SettingsWidget;
}

class SettingsWidget : public PWidget
{
    Q_OBJECT

public:
    explicit SettingsWidget(flsGUI* parent);
    ~SettingsWidget();

    void loadClientModel() override;
    void loadWalletModel() override;
    void setMapper();
    void showDebugConsole();
    void showInformation();
    void openNetworkMonitor();

Q_SIGNALS:
    /** Get restart command-line parameters and handle restart */
    void handleRestart(QStringList args);

private Q_SLOTS:
    // File
    void onFileClicked();
    void onBackupWalletClicked();
    void onSignMessageClicked();

    // Wallet Configuration
    void onConfigurationClicked();
    void onBipToolClicked();
    void onMultisendClicked();
    void onExportCSVClicked();

    // Options
    void onOptionsClicked();
    void onMainOptionsClicked();
    void onWalletOptionsClicked();
    void onDisplayOptionsClicked();

    void onDiscardChanges();

    // Tools
    void onToolsClicked();
    void onInformationClicked();
    void onDebugConsoleClicked();
    void onWalletRepairClicked();

    // Help
    void onHelpClicked();
    void onAboutClicked();
    void onResetAction();
    void onSaveOptionsClicked();

private:
    Ui::SettingsWidget *ui{nullptr};
    int navAreaBaseHeight{0};

    SettingsBackupWallet *settingsBackupWallet{nullptr};
    SettingsExportCSV *settingsExportCsvWidget{nullptr};
    SettingsBitToolWidget *settingsBitToolWidget{nullptr};
    SettingsSignMessageWidgets *settingsSingMessageWidgets{nullptr};
    SettingsWalletRepairWidget *settingsWalletRepairWidget{nullptr};
    SettingsWalletOptionsWidget *settingsWalletOptionsWidget{nullptr};
    SettingsMainOptionsWidget *settingsMainOptionsWidget{nullptr};
    SettingsDisplayOptionsWidget *settingsDisplayOptionsWidget{nullptr};
    SettingsMultisendWidget *settingsMultisendWidget{nullptr};
    SettingsInformationWidget *settingsInformationWidget{nullptr};
    SettingsConsoleWidget *settingsConsoleWidget{nullptr};

    QDataWidgetMapper* mapper{nullptr};

    QList<QPushButton*> options;
    // Map of: menu button -> sub menu items
    QMap <QPushButton*, QWidget*> menus;

    void selectOption(QPushButton* option);
    bool openStandardDialog(const QString& title = "", const QString& body = "", const QString& okBtn = "OK", const QString& cancelBtn = "");
    void selectMenu(QPushButton* btn);
};

#endif // SETTINGSWIDGET_H
