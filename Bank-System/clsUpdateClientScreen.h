#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateClientScreen : protected clsScreen
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

public:
    static void ShowUpdateClientScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::eUpdateClient))
        {
            return;
        }

        _DrawScreenHeader("Update Client Screen");

        string AccountNumber;
        cout << "\nPlease Enter Client Account Number: ";
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExiest(AccountNumber))
        {
            cout << "\nAccount Number is Not Found, Enter Another One: ";
            AccountNumber = clsInputValidate::ReadString();
        }
        clsBankClient Client = clsBankClient::Find(AccountNumber);
        _PrintClient(Client);
        cout << "\n\nUpdate Client Info\n";
        cout << "______________________\n";

        _ReadClientInfo(Client);

        clsBankClient::enSaveResults SaveResult;

        SaveResult = Client.Save();

        switch (SaveResult)
        {
        case clsBankClient::enSaveResults::svSucceded:
        {
            cout << "\nAccount Updated Successfully :-)\n";
            _PrintClient(Client);
            break;
        }
        case clsBankClient::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError account was not saved because it's Empty\n";
            break;
        }
        }
    }
};