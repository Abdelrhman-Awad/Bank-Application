#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"

class clsLoginRegisterScreen : protected clsScreen
{
private:
    static void _PrintInfoRecordLine(clsUser::stLoginRegisterRecord LoginRegisterRecord)
    {
        cout << setw(8) << left << "" << "| " << left << setw(40) << LoginRegisterRecord.DateTime;
        cout << "| " << left << setw(20) << LoginRegisterRecord.Username;
        cout << "| " << left << setw(17) << LoginRegisterRecord.Password;
        cout << "| " << left << setw(20) << LoginRegisterRecord.Permissions;
    }

public:
    static void ShowLoginRegisterList()
    {

        if (!CheckAccessRights(clsUser::enPermissions::eLoginRegister))
        {
            return;
        }

        vector<clsUser::stLoginRegisterRecord> vRegisterLogin = clsUser::GetLoginRegisterList();

        string Title = "Login Register List Screen";
        string SubTitle = "  (" + to_string(vRegisterLogin.size()) + ")" + " Record(s).";

        _DrawScreenHeader(Title, SubTitle);

        cout << setw(8) << left << "";
        cout << "\n\t________________________________________________________";
        cout << "________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(40) << "Date/Time";
        cout << "| " << left << setw(20) << "Username";
        cout << "| " << left << setw(17) << "Password";
        cout << "| " << left << setw(20) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_________________________________________\n\n";
        if (vRegisterLogin.size() == 0)
        {
            cout << "\n\t\t\t\tNo Records Available in the System.";
        }
        else
        {
            for (clsUser::stLoginRegisterRecord Record : vRegisterLogin)
            {
                _PrintInfoRecordLine(Record);
                cout << endl;
            }
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_________________________________________\n\n";
        }
    }
};