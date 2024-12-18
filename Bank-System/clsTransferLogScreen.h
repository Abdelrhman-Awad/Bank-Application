#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"

class clsTransferLogScreen : protected clsScreen
{
private:
    static void _PrintTransferLogLine(clsBankClient::stTranserLog stData)
    {
        cout << setw(8) << left << "" << "| " << left << setw(25) << stData.DateTime;
        cout << "| " << left << setw(10) << stData.SourceAccNum;
        cout << "| " << left << setw(10) << stData.DestinationAccNum;
        cout << "| " << left << setw(10) << stData.Amount;
        cout << "| " << left << setw(10) << stData.SourceBalance;
        cout << "| " << left << setw(10) << stData.DestinationBalance;
        cout << "| " << left << setw(13) << stData.Username;
    }

public:
    static void ShowTransferLogScreen()
    {

        vector<clsBankClient::stTranserLog> vTransferLog = clsBankClient::GetTransferLogList();

        string Title = "Transfer Log List Screen";
        string SubTitle = "  (" + to_string(vTransferLog.size()) + ")" + " Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "";
        cout << "\n\t________________________________________________________";
        cout << "________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(25) << "Date/Time";
        cout << "| " << left << setw(10) << "S.Acct";
        cout << "| " << left << setw(10) << "D.Acct";
        cout << "| " << left << setw(10) << "Amount";
        cout << "| " << left << setw(10) << "S.Balance";
        cout << "| " << left << setw(10) << "D.Balance";
        cout << "| " << left << setw(13) << "User";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n\n";
        if (vTransferLog.size() == 0)
        {
            cout << "\n\t\t\t\tNo Records Available in the System.";
        }
        else
        {
            for (clsBankClient::stTranserLog Record : vTransferLog)
            {
                _PrintTransferLogLine(Record);
                cout << endl;
            }
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n\n";
        }
    }
};