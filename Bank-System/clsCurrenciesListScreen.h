#pragma once
#include <iostream>
#include <string>
#include "clsCurrency.h"
#include "clsScreen.h"

using namespace std;

class clsCurrenciesListScreen : protected clsScreen
{
private:
    static void _PrintCurrencyRecordLine(clsCurrency Currency)
    {
        cout << setw(8) << left << "" << "| " << left << setw(30) << Currency.Country();
        cout << "| " << left << setw(8) << Currency.CurrencyCode();
        cout << "| " << left << setw(40) << Currency.CurrencyName();
        cout << "| " << left << setw(12) << Currency.Rate();
    }

public:
    static void ShowCurrenciessList()
    {

        vector<clsCurrency> vCurrencies = clsCurrency::GetCurrenciesList();

        string Title = "Currencies List Screen";
        string SubTitle = "  (" + to_string(vCurrencies.size()) + ")" + " Currency.";

        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "";
        cout << "\n\t________________________________________________________";
        cout << "________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(30) << "Country";
        cout << "| " << left << setw(8) << "Code";
        cout << "| " << left << setw(40) << "Name";
        cout << "| " << left << setw(12) << "Rate/(1$)";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n\n";
        if (vCurrencies.size() == 0)
        {
            cout << "\n\t\t\t\tNo Currencies Available in the System.";
        }
        else
        {
            for (clsCurrency C : vCurrencies)
            {
                _PrintCurrencyRecordLine(C);
                cout << endl;
            }
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n\n";
        }
    }
};