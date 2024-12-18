#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsDeleteUserScreen : protected clsScreen
{
private:
    static void _PrintUser(clsUser User)
    {
        cout << "\nUser Card:";
        cout << "\n_______________________";
        cout << "\nFirstName   : " << User.FirstName();
        cout << "\nLastName    : " << User.LastName();
        cout << "\nFull Name   : " << User.FullName();
        cout << "\nEmail       : " << User.Email();
        cout << "\nPhone       : " << User.Phone();
        cout << "\nUsername    : " << User.Username();
        cout << "\nPassword    : " << User.Password();
        cout << "\nPermissions : " << User.Permissions();
        cout << "\n_______________________\n";
    }

public:
    static void ShowDeleteUserScreen()
    {
        _DrawScreenHeader("Delete User Screen");

        string Username = "";
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is Not Exist, Enter Another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(Username);
        _PrintUser(User);

        char Answer = 'n';
        cout << "\nAre you sure you want to delete this user y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            if (User.Delete())
            {
                cout << "\nUser Was Deleted Successfully.\n";
                _PrintUser(User);
            }
            else
            {
                cout << "\nError, Something Wrong Happended\n";
            }
        }
    }
};