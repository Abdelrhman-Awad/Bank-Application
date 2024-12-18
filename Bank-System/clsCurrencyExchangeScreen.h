#pragma once
#include <iostream>
#include <iomanip>
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsCurrenciesListScreen.h"
#include "clsFindCurrencyScreen.h"
#include "clsUpdateCurrencyRateScreen.h"
#include "clsCurrencyCalculatorScreen.h"

using namespace std;

class clsCurrencyExchangeScreen : protected clsScreen
{
private:
    enum enCurrencyExchangeOption
    {
        eShowCurrenciesList = 1,
        eFindCurrency = 2,
        eUpdateRate = 3,
        eCurrencyCalculator = 4,
        eMainMenue = 5
    };

    static short _ReadCurrencyExchangeOption()
    {
        cout << setw(35) << left << "" << "Choose What Do You Want To Do? [1 to 5]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 5, "Enter Number Between 1 to 5! ");

        return Choice;
    }

    static void _BackToCurrencyExchangeScreen()
    {
        cout << "\n\nPress Any Key To Go Back To Currency Exchange Main Menue...";
        system("pause>0");
        ShowCurrencyExchangeScreen();
    }

    static void _ShowCurrenciesListScreen()
    {
        clsCurrenciesListScreen::ShowCurrenciessList();
    }

    static void _ShowFindCurrencyScreen()
    {
        clsFindCurrencyScreen::ShowFindCurrencyScreen();
    }

    static void _ShowUpdateRateScreen()
    {
        clsUpdateCurrencyRateScreen::ShowUpdateRateScreen();
    }

    static void _ShowCurrencyCalculatorScreen()
    {
        clsCurrencyCalculatorScreen::ShowCurrencyCalculatorScreen();
    }

    static void _PerformCurrencyExchangeMenueOptions(enCurrencyExchangeOption Option)
    {
        switch (Option)
        {
        case enCurrencyExchangeOption::eShowCurrenciesList:
            system("cls");
            _ShowCurrenciesListScreen();
            _BackToCurrencyExchangeScreen();
            break;
        case enCurrencyExchangeOption::eFindCurrency:
            system("cls");
            _ShowFindCurrencyScreen();
            _BackToCurrencyExchangeScreen();
            break;
        case enCurrencyExchangeOption::eUpdateRate:
            system("cls");
            _ShowUpdateRateScreen();
            _BackToCurrencyExchangeScreen();
            break;
        case enCurrencyExchangeOption::eCurrencyCalculator:
            system("cls");
            _ShowCurrencyCalculatorScreen();
            _BackToCurrencyExchangeScreen();
            break;
        case enCurrencyExchangeOption::eMainMenue:
            break;
        }
    }

public:
    static void ShowCurrencyExchangeScreen()
    {
        system("cls");
        _DrawScreenHeader("Currency Exchange Main Screen");

        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t\tCurrency Exchange Menue" << endl;
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t[1] List Currencies." << endl;
        cout << setw(35) << left << "" << "\t[2] Find Currency." << endl;
        cout << setw(35) << left << "" << "\t[3] Update Rate." << endl;
        cout << setw(35) << left << "" << "\t[4] Currency Calculator." << endl;
        cout << setw(35) << left << "" << "\t[5] Main Menue." << endl;
        cout << setw(35) << left << "" << "======================================" << endl;

        _PerformCurrencyExchangeMenueOptions((enCurrencyExchangeOption)_ReadCurrencyExchangeOption());
    }
};