#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"

using namespace std;

class clsUsersListScreen : protected clsScreen
{
private:
    static void _PrintUserRecordLine(clsUser User)
    {
        cout << setw(8) << left << "" << "| " << left << setw(12) << User.Username();
        cout << "| " << left << setw(25) << User.FullName();
        cout << "| " << left << setw(12) << User.Phone();
        cout << "| " << left << setw(20) << User.Email();
        cout << "| " << left << setw(10) << User.Password();
        cout << "| " << left << setw(12) << User.Permissions();
    }

public:
    static void ShowUsersList()
    {

        vector<clsUser> vUsers = clsUser::GetUserList();

        string Title = "User List Screen";
        string SubTitle = "  (" + to_string(vUsers.size()) + ")" + " User(s).";

        _DrawScreenHeader(Title, SubTitle);
        cout << setw(8) << left << "";
        cout << "\n\t________________________________________________________";
        cout << "______________________________________________\n\n";
        cout << setw(8) << left << "" << "| " << left << setw(12) << "User Name";
        cout << "| " << left << setw(25) << "Full Name";
        cout << "| " << left << setw(12) << "Phone";
        cout << "| " << left << setw(20) << "Email";
        cout << "| " << left << setw(10) << "Password";
        cout << "| " << left << setw(12) << "Permissions";
        cout << setw(8) << left << "" << "\n\t_______________________________________________________";
        cout << "_______________________________________________\n\n";
        if (vUsers.size() == 0)
        {
            cout << "\n\t\t\t\tNo Users Available in the System.";
        }
        else
        {
            for (clsUser C : vUsers)
            {
                _PrintUserRecordLine(C);
                cout << endl;
            }
            cout << setw(8) << left << "" << "\n\t_______________________________________________________";
            cout << "_______________________________________________\n\n";
        }
    }
};