#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsDepositeScreen.h"
#include "clsWithdrawScreen.h"
#include "clsTotalBalancesScreen.h"
#include "clsTransferScreen.h"
#include "clsTransferLogScreen.h"

using namespace std;

class clsTransactionsScreen : protected clsScreen
{
private:
    enum enTransactionsMenueOption
    {
        eDeposite = 1,
        eWithdraw = 2,
        eShowTotalBalances = 3,
        eTransfer = 4,
        eShowTranserLogScreen = 5,
        eShowMainMenue = 6
    };

    static short _ReadTransactionsMenueOption()
    {
        cout << setw(35) << left << "" << "Choose What Do You Want To Do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 6, "Enter Number Between 1 to 6!");

        return Choice;
    }

    static void _BackToTransactionMenueScreen()
    {
        cout << "\n\nPress Any Key To Go Back To Transactions Menue...\n"
             << endl;
        system("pause>0");
        ShowTransactionsScreen();
    }

    static void _ShowDepositeScreen()
    {
        clsDepositeScreen::ShowDepositeScreen();
    }
    static void _ShowWithdrawScreen()
    {
        clsWithdrawScreen::ShowWitdrawScreen();
    }
    static void _ShowTotalBalancesScreen()
    {
        clsTotalBalancesScreen::ShowTotalBalances();
    }
    static void _ShowTransferScreen()
    {
        clsTransferScreen::ShowTransferScreen();
    }
    static void _ShowTransferLogScreen()
    {
        clsTransferLogScreen::ShowTransferLogScreen();
    }

    static void _PerformTransactionOption(enTransactionsMenueOption Option)
    {
        switch (Option)
        {
        case enTransactionsMenueOption::eDeposite:
            system("cls");
            _ShowDepositeScreen();
            _BackToTransactionMenueScreen();
            break;
        case enTransactionsMenueOption::eWithdraw:
            system("cls");
            _ShowWithdrawScreen();
            _BackToTransactionMenueScreen();
            break;
        case enTransactionsMenueOption::eShowTotalBalances:
            system("cls");
            _ShowTotalBalancesScreen();
            _BackToTransactionMenueScreen();
            break;
        case enTransactionsMenueOption::eTransfer:
            system("cls");
            _ShowTransferScreen();
            _BackToTransactionMenueScreen();
            break;
        case enTransactionsMenueOption::eShowTranserLogScreen:
            system("cls");
            _ShowTransferLogScreen();
            _BackToTransactionMenueScreen();
            break;
        case enTransactionsMenueOption::eShowMainMenue:
            break;
        }
    }

public:
    static void ShowTransactionsScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::eTransactions))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("Transactions Screen");
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t\tTransactions Menue" << endl;
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t[1] Deposite." << endl;
        cout << setw(35) << left << "" << "\t[2] Withdraw." << endl;
        cout << setw(35) << left << "" << "\t[3] Total Balances." << endl;
        cout << setw(35) << left << "" << "\t[4] Transfer." << endl;
        cout << setw(35) << left << "" << "\t[5] Transfer Log." << endl;
        cout << setw(35) << left << "" << "\t[6] Main Menue." << endl;
        cout << setw(35) << left << "" << "======================================" << endl;

        _PerformTransactionOption((enTransactionsMenueOption)_ReadTransactionsMenueOption());
    }
};