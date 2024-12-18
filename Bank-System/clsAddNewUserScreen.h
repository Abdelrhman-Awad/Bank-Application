#pragma once
#include <iostream>
#include <string>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsAddNewUserScreen : protected clsScreen
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

    static int _ReadPermissions()
    {
        int Permissions = 0;
        char Answer = 'n';

        cout << "\nEnter Permissions:\n";
        cout << "\nDo you want to give Full Access? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            return (int)clsUser::enPermissions::eAll;
        }

        cout << "\nDo You want To give Access to: \n";
        cout << "\nShow Client List? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eShowClientList;
        }

        cout << "\nAdd New Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eAddNew;
        }

        cout << "\nDelete Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eDeleteClient;
        }

        cout << "\nUpdate Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eUpdateClient;
        }

        cout << "\nFind Client? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eFindClient;
        }

        cout << "\nTransactions? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eTransactions;
        }

        cout << "\nManage Users? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eManageUsers;
        }

        cout << "\nLogin Register? y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            Permissions += (int)clsUser::enPermissions::eLoginRegister;
        }

        return Permissions;
    }

    static void _ReadUserInfo(clsUser &User)
    {
        cout << "\nEnter FirstName: ";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName: ";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email: ";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone: ";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password: ";
        User.SetPassword(clsInputValidate::ReadString());

        User.SetPermissions(_ReadPermissions());
    }

public:
    static void ShowAddNewUserScreen()
    {
        _DrawScreenHeader("Add New User Screen");

        string Username = "";

        cout << "\nPlease Enter Username: ";
        Username = clsInputValidate::ReadString();

        while (clsUser::IsUserExist(Username))
        {
            cout << "\nUsername Is Already Used, Choose Another One: ";
            Username = clsInputValidate::ReadString();
        }

        clsUser User1 = clsUser::GetAddNewUserObject(Username);
        _ReadUserInfo(User1);

        clsUser::enSaveResults SaveResult;

        SaveResult = User1.Save();

        switch (SaveResult)
        {
        case clsUser::enSaveResults::svSucceded:
        {
            cout << "\nUser Added Successfully :-)\n";
            _PrintUser(User1);
            break;
        }
        case clsUser::enSaveResults::svFaildEmptyObject:
        {
            cout << "\nError User was not saved Because it's Empty\n";
            break;
        }
        case clsUser::enSaveResults::svFaildUserExist:
        {
            cout << "\nError User was not saved Because Username is Used\n";
            break;
        }
        }
    }
};