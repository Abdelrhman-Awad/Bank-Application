#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsGlobal.h"

using namespace std;

class clsTransferScreen : protected clsScreen
{
private:
    static void _PrintBriefCleintCard(clsBankClient Client)
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFull Name   : " << Client.FullName();
        cout << "\nAcc. Number : " << Client.AccountNumber();
        cout << "\nBalance     : " << Client.AccountBalance();
        cout << "\n___________________\n";
    }

    static string _ReadAccountNumber(string Message = "\nPlease Enter Account Number: ")
    {
        string AccountNumber;

        cout << Message;
        AccountNumber = clsInputValidate::ReadString();

        while (!clsBankClient::IsClientExiest(AccountNumber))
        {
            cout << "\nAccount Number is Not Found, Enter Another One: ";
            AccountNumber = clsInputValidate::ReadString();
        }

        return AccountNumber;
    }

    static double _ReadAmount(clsBankClient SourceClient)
    {
        double Amount = 0;

        cout << "\nEnter Transfer Amount? ";
        Amount = clsInputValidate::ReadDblNumber();

        if (Amount > SourceClient.AccountBalance())
        {
            cout << "\nAmoutn Exceeds the Available Balance, Enter Another Amount: ";
            Amount = clsInputValidate::ReadDblNumber();
        }

        return Amount;
    }

public:
    static void ShowTransferScreen()
    {
        _DrawScreenHeader("Transfer Screen");

        clsBankClient SourceClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Trasfer From: "));
        _PrintBriefCleintCard(SourceClient);

        clsBankClient DestinationClient = clsBankClient::Find(_ReadAccountNumber("\nPlease Enter Account Number To Trasfer To: "));
        _PrintBriefCleintCard(DestinationClient);

        double Amount = _ReadAmount(SourceClient);

        char Answer = 'n';
        cout << "\nAre you sure you want to perform this operation? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (SourceClient.Transfer(Amount, DestinationClient,CurrentUser.Username()))
            {
                cout << "\nTransfer Done Successfully\n";
            }
            else
            {
                cout << "\nTransfer Failed \n";
            }
        }
        _PrintBriefCleintCard(SourceClient);
        _PrintBriefCleintCard(DestinationClient);
    }
};