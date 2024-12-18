#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindCurrencyScreen : protected clsScreen
{
private:
    static short _ReadOption()
    {
        cout << "Find By: [1] Code or [2] Country ? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 2, "Enter 1 or 2! ");

        return Choice;
    }

    static void _PrintCurrency(clsCurrency Currency)
    {
        cout << "\nCurrency Card:";
        cout << "\n_____________________________________\n\n";
        cout << "Country       : " << Currency.Country() << endl;
        cout << "Code          : " << Currency.CurrencyCode() << endl;
        cout << "Name          : " << Currency.CurrencyName() << endl;
        cout << "Rate(1$) =    : " << Currency.Rate() << endl;
        cout << "\n_____________________________________\n";
    }

    static void _ShowResult(clsCurrency Currency)
    {
        if (!Currency.IsEmpty())
        {
            cout << "\nCurrency Found :-)\n";
            _PrintCurrency(Currency);
        }
        else
        {
            cout << "\nCurrency Wasn't Found :-(\n";
        }
    }

public:
    static void ShowFindCurrencyScreen()
    {
        _DrawScreenHeader("Find Currency Screen");

        short Option = 1;
        Option = _ReadOption();

        if (Option == 1)
        {

            string Code;
            cout << "\nPlease Enter Currency Code: ";
            Code = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCode(Code);
            _ShowResult(Currency);
        }
        else
        {
            string Country;
            cout << "\nPlease Enter Country Name: ";
            Country = clsInputValidate::ReadString();
            clsCurrency Currency = clsCurrency::FindByCountry(Country);
            _ShowResult(Currency);
        }
    }
};