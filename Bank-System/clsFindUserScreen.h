#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsFindUserScreen : protected clsScreen
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
    static void ShowFindUserScreen()
    {
        _DrawScreenHeader("Find User Screen");

        string Username = "";
        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (!clsUser::IsUserExist(Username))
        {
            cout << "\nUsername is Not Exist, Enter Another one: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User = clsUser::Find(Username);

        if (!User.IsEmpty())
        {
            cout << "\nUser Found :-) \n";
        }
        else
        {
            cout << "\nUser Was Not Found :-(\n";
        }
        _PrintUser(User);
    }
};