#pragma once
#include <iostream>
#include <string>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewClientScreen : protected clsScreen
{
private:
    static void _ReadClientInfo(clsBankClient &Client)
    {

        cout << "\nEnter FirstName:\n";
        Client.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName:\n";
        Client.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email:\n";
        Client.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone:\n";
        Client.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter PinCode:\n";
        Client.SetPinCode(clsInputValidate::ReadString());

        cout << "\nEnter Account Balance:\n";
        Client.SetAccountBalance(clsInputValidate::ReadFloatNumber());
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
    static void ShowAddNewClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::eAddNew))
        {
            return;
        }

        _DrawScreenHeader("Add New Client Screen");
        string AccountNumber = "";
        cout << "\nPlease Enter Account Number:\n";
        AccountNumber = clsInputValidate::ReadString();
        while (clsBankClient::IsClientExiest(AccountNumber))
        {
            cout << "Account Number is Already Used, Please Choose Another One:\n";
            AccountNumber = clsInputValidate::ReadString();
        }

        clsBankClient NewClient = clsBankClient::GetAddNewClientObject(AccountNumber);
        _ReadClientInfo(NewClient);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = NewClient.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceded:
        {
            cout << "\nAccount Added Successfully :-)\n";
            _PrintClient(NewClient);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty\n";
            break;
        }
        case clsBankClient::enSaveResults::svFaildAccountNumberExist:
        {
            cout << "\nError Account Was Not Saved Because Account Number Is Used\n";
            break;
        }
        }
    }
};
