#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsClientsListScreen.h"
#include "clsAddNewClientScreen.h"
#include "clsDeleteClientScreen.h"
#include "clsUpdateClientScreen.h"
#include "clsFindClientScreen.h"
#include "clsTransactionsScreen.h"
#include "clsManageUsersScreen.h"
#include "clsGlobal.h"
#include "clsLoginRegisterScreen.h"
#include "clsCurrencyExchangeScreen.h"

using namespace std;

class clsMainMenueScreen : protected clsScreen
{
private:
    enum enMainMenueOption
    {
        eShowClientList = 1,
        eAddNewClient = 2,
        eDeleteClient = 3,
        eUpdateClient = 4,
        eFindClient = 5,
        eTransactions = 6,
        eManageUsers = 7,
        eLoginRegister = 8,
        eCurrencyExchange = 9,
        eLogout = 10
    };

    static short _ReadMainMenueOption()
    {
        cout << setw(35) << left << "" << "Choose What Do You Want To Do? [1 to 10]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 10, "Enter Number Between 1 to 10! ");

        return Choice;
    }

    static void _BackToMainMenueScreen()
    {
        cout << "\n\nPress Any Key To Go Back To Main Menue...";
        system("pause>0");
        ShowMainMenueScreen();
    }

    static void _ShowAllClientsScreen()
    {
        clsClientsListScreen::ShowClientsList();
    }

    static void _ShowAddNewClientScreen()
    {
        clsAddNewClientScreen::ShowAddNewClientScreen();
    }

    static void _ShowDeleteClientScreen()
    {
        clsDeleteClientScreen::ShowDeleteClientScreen();
    }
    static void _ShowUpdateClientScreen()
    {
        clsUpdateClientScreen::ShowUpdateClientScreen();
    }
    static void _ShowFindClientScreen()
    {
        clsFindClientScreen::ShowFindClientScreen();
    }
    static void _ShowTransactionsMenue()
    {
        clsTransactionsScreen::ShowTransactionsScreen();
    }
    static void _ShowManageUsersMenue()
    {
        clsManageUsersScreen::ShowManageUsersScreen();
    }
    static void _ShowLoginRegisterScreen()
    {
        clsLoginRegisterScreen::ShowLoginRegisterList();
    }
    static void _ShowCurrencyExchangeScreen()
    {
        clsCurrencyExchangeScreen::ShowCurrencyExchangeScreen();
    }
    static void _Logout()
    {
        CurrentUser = clsUser::Find("", "");
    }

    static void _PerformMainMenueOptions(enMainMenueOption Option)
    {
        switch (Option)
        {
        case enMainMenueOption::eShowClientList:
            system("cls");
            _ShowAllClientsScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eAddNewClient:
            system("cls");
            _ShowAddNewClientScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eDeleteClient:
            system("cls");
            _ShowDeleteClientScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eUpdateClient:
            system("cls");
            _ShowUpdateClientScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eFindClient:
            system("cls");
            _ShowFindClientScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eTransactions:
            system("cls");
            _ShowTransactionsMenue();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eManageUsers:
            system("cls");
            _ShowManageUsersMenue();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eLoginRegister:
            system("cls");
            _ShowLoginRegisterScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eCurrencyExchange:
            system("cls");
            _ShowCurrencyExchangeScreen();
            _BackToMainMenueScreen();
            break;
        case enMainMenueOption::eLogout:
            system("cls");
            _Logout();
            break;
        }
    }

public:
    static void ShowMainMenueScreen()
    {
        system("cls");
        _DrawScreenHeader("Main Screen");
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t\tMain Menue" << endl;
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t[1] Show Client List." << endl;
        cout << setw(35) << left << "" << "\t[2] Add New Client." << endl;
        cout << setw(35) << left << "" << "\t[3] Delete Client." << endl;
        cout << setw(35) << left << "" << "\t[4] Update Client Info." << endl;
        cout << setw(35) << left << "" << "\t[5] Find Client." << endl;
        cout << setw(35) << left << "" << "\t[6] Transactions." << endl;
        cout << setw(35) << left << "" << "\t[7] Manage Users." << endl;
        cout << setw(35) << left << "" << "\t[8] Login Register." << endl;
        cout << setw(35) << left << "" << "\t[9] Currency Exchange." << endl;
        cout << setw(35) << left << "" << "\t[10] Logout." << endl;
        cout << setw(35) << left << "" << "======================================" << endl;

        _PerformMainMenueOptions((enMainMenueOption)_ReadMainMenueOption());
    }
};