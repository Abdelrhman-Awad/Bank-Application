#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDepositeScreen : protected clsScreen
{

private:
    static string _ReadAccountNumber()
    {
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        return AccountNumber;
    }

    static void _PrintClient(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << Client.FirstName();
        cout << "\nLastName    : " << Client.LastName();
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nEmail       : " << Client.Email();
        cout << "\nPhone       : " << Client.Phone();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nPassword    : " << Client.PinCode();
        cout << "\nBalance     : " << Client.AccountBalance();
        cout << "\n___________________\n";
    }

public:
    static void ShowDepositeScreen()
    {
        _DrawScreenHeader("Deposite Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExiest(AccountNumber))
        {
            cout << "\nClient with[" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Deposite Amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\nAre You sure you want to perform this transaction? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Client.Deposite(Amount);
            cout << "\nAmount Deposited Successfully.\n";
            cout << "\nNew Balance is: " << Client.AccountBalance() << endl;
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};