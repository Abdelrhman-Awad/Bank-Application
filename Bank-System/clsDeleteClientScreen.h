#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteClientScreen : protected clsScreen
{
private:
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
    static void ShowDeleteClientScreen()
    {

        if (!CheckAccessRights(clsUser::enPermissions::eDeleteClient))
        {
            return;
        }

        _DrawScreenHeader("Delete Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number: ";
        AccountNumber = clsInputValidate::ReadString();
        while (!clsBankClient::IsClientExiest(AccountNumber))
        {
            cout << "\nAccount Number is Not Found, Enter Another One: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this client y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (Client.Delete())
            {
                cout << "\nClient Deleted Successfully.\n";
                _PrintClient(Client);
            }
            else
            {
                cout << "\nError, Something Wrong Happened.\n";
            }
        }
    }
};
