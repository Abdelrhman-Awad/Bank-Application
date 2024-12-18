#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateCurrencyRateScreen : protected clsScreen
{
private:
    static float _ReadNewRate()
    {
        float NewRate = 0;
        cout << "\nEnter New Rate: ";
        NewRate = clsInputValidate::ReadFloatNumber();

        return NewRate;
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

public:
    static void ShowUpdateRateScreen()
    {
        _DrawScreenHeader("Update Currency Screen");

        string Code = "";
        cout << "\nPlease Enter Currency Code: ";
        Code = clsInputValidate::ReadString();

        while (!clsCurrency::IsCurrencyExist(Code))
        {
            cout << "\nCurrency Does Not Exist, Enter Another Code: ";
            Code = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(Code);
        _PrintCurrency(Currency);

        char Answer = 'n';
        cout << "\nAre you sure you want to update the rate of this Currency y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\nUpdate Currency Rate:";
            cout << "\n_____________________________\n";

            Currency.UpdateRate(_ReadNewRate());

            cout << "\nCurrency Rate Update Successfully :-)\n";
            _PrintCurrency(Currency);
        }
    }
};