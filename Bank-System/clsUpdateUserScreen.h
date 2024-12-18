#pragma once
#include <iostream>
#include "clsUser.h"
#include "clsScreen.h"
#include "clsInputValidate.h"

using namespace std;

class clsUpdateUserScreen : protected clsScreen
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

    static void _ReadUserInfo(clsUser &User)
    {

        cout << "\nEnter FirstName:\n";
        User.SetFirstName(clsInputValidate::ReadString());

        cout << "\nEnter LastName:\n";
        User.SetLastName(clsInputValidate::ReadString());

        cout << "\nEnter Email:\n";
        User.SetEmail(clsInputValidate::ReadString());

        cout << "\nEnter Phone:\n";
        User.SetPhone(clsInputValidate::ReadString());

        cout << "\nEnter Password:\n";
        User.SetPassword(clsInputValidate::ReadString());

        User.SetPermissions(_ReadPermissions());
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

public:
    static void ShowUpdateUserScreen()
    {
        _DrawScreenHeader("Update User Screen");

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
        cout << "\nAre you sure you want to update this user y/n? ";
        cin >> Answer;

        if (Answer == 'y' || Answer == 'Y')
        {
            cout << "\n\nUpdate User Info:";
            cout << "\n------------------\n";

            _ReadUserInfo(User);

            clsUser::enSaveResults SaveResult;
            SaveResult = User.Save();

            switch (SaveResult)
            {
            case clsUser::enSaveResults::svSucceded:
            {
                cout << "\nUser Updated Successfully :-)\n";
                _PrintUser(User);
                break;
            }
            case clsUser::enSaveResults::svFaildEmptyObject:
            {
                cout << "\nError User was not saved Because it's Empty\n";
                break;
            }
            }
        }
    }
};