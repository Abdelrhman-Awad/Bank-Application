#pragma once
#include <iostream>
#include "clsCurrency.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsCurrencyCalculatorScreen : protected clsScreen
{
private:
    static float _ReadAmount()
    {
        float Amount = 0;
        cout << "\nEnter Amount To Exchange: ";
        Amount = clsInputValidate::ReadFloatNumber();

        return Amount;
    }

    static void _PrintCurrencyCard(clsCurrency Currency, string Title)
    {
        cout << Title;
        cout << "\n_____________________________________\n\n";
        cout << "Country       : " << Currency.Country() << endl;
        cout << "Code          : " << Currency.CurrencyCode() << endl;
        cout << "Name          : " << Currency.CurrencyName() << endl;
        cout << "Rate(1$) =    : " << Currency.Rate() << endl;
        cout << "_____________________________________\n";
    }

    static clsCurrency _GetCurrency(string Message)
    {
        string Code = "";

        cout << Message;
        Code = clsInputValidate::ReadString();
        while (!clsCurrency::IsCurrencyExist(Code))
        {
            cout << "\nCurrency Does Not Exist, Enter Another Code: ";
            Code = clsInputValidate::ReadString();
        }
        clsCurrency Currency = clsCurrency::FindByCode(Code);

        return Currency;
    }

    static void _PrintCalculationResult(float Amount, clsCurrency Currency1, clsCurrency Currency2)
    {
        _PrintCurrencyCard(Currency1, "\nConvert From:");
        float AmountInUSD = Currency1.ConvertToUSD(Amount);

        cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInUSD << " USD" << endl;

        if (Currency2.CurrencyCode() == "USD")
        {
            return;
        }

        cout << "\nConverting From USD To:";
        _PrintCurrencyCard(Currency2, "\nTo:");

        float AmountInCurrency2 = Currency1.ConvertToOtherCurrency(Amount, Currency2);
        cout << Amount << " " << Currency1.CurrencyCode() << " = " << AmountInCurrency2 << " " << Currency2.CurrencyCode() << endl;
    }

public:
    static void ShowCurrencyCalculatorScreen()
    {
        char Answer = 'y';
        while (Answer == 'y' || Answer == 'Y')
        {
            system("cls");
            _DrawScreenHeader("Currency Calculator Screen");
            clsCurrency CurrencyFrom = _GetCurrency("\nPlease Enter Currency1 Code: ");
            clsCurrency CurrencyTo = _GetCurrency("\nPlease Enter Currency2 Code: ");
            float Amount = _ReadAmount();

            _PrintCalculationResult(Amount, CurrencyFrom, CurrencyTo);

            cout << "\n\nDo you want to perform another calculation y/n? ";
            cin >> Answer;
        }
    }
};