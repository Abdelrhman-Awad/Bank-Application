#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsWithdrawScreen : protected clsScreen
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
    static void ShowWitdrawScreen()
    {
        _DrawScreenHeader("Withdraw Screen");

        string AccountNumber = _ReadAccountNumber();

        while (!clsBankClient::IsClientExiest(AccountNumber))
        {
            cout << "\nClient with[" << AccountNumber << "] does not exist.\n";
            AccountNumber = _ReadAccountNumber();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        double Amount = 0;
        cout << "\nPlease Enter Withdraw Amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        char Answer = 'n';
        cout << "\nAre You sure you want to perform this transaction? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Withdraw(Amount))
            {
                cout << "\nAmount Witdrawed Successfully.\n";
                cout << "\nNew Balance is: " << Client.AccountBalance() << endl;
            }
            else
            {
                cout << "\nCannot Withdraw, Insuffecient Balance!\n";
                cout << "\nAmount To Withdraw is: " << Amount << endl;
                cout << "\nYour Balance is: " << Client.AccountBalance() << endl;
            }
        }
        else
        {
            cout << "\nOperation was cancelled.\n";
        }
    }
};