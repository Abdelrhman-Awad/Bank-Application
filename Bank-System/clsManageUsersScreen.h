#pragma once
#include <iostream>
#include "clsBankClient.h"
#include "clsScreen.h"
#include "clsInputValidate.h"
#include "clsUsersListScreen.h"
#include "clsAddNewUserScreen.h"
#include "clsDeleteUserScreen.h"
#include "clsUpdateUserScreen.h"
#include "clsFindUserScreen.h"

using namespace std;

class clsManageUsersScreen : protected clsScreen
{
private:
    enum enManageUsersMenueOption
    {
        eListUsers = 1,
        eAddNewUser = 2,
        eDeleteUser = 3,
        eUpdateUser = 4,
        eFindUser = 5,
        eMainMenue = 6
    };

    static short _ReadManageUsersMenueOption()
    {
        cout << setw(35) << left << "" << "Choose What Do You Want To Do? [1 to 6]? ";
        short Choice = clsInputValidate::ReadshortNumberBetween(1, 6, "Enter Number Between 1 to 6! ");

        return Choice;
    }

    static void _BackToManageUsersScreen()
    {
        cout << "\n\nPress Any Key To Go Back To Manage Users Menue...";
        system("pause>0");
        ShowManageUsersScreen();
    }

    static void _ShowListUsersScreen()
    {
        clsUsersListScreen::ShowUsersList();
    }
    static void _ShowAddNewUserScreen()
    {
        clsAddNewUserScreen::ShowAddNewUserScreen();
    }
    static void _ShowDeleteUserScreen()
    {
        clsDeleteUserScreen::ShowDeleteUserScreen();
    }
    static void _ShowUpdateUserScreen()
    {
        clsUpdateUserScreen::ShowUpdateUserScreen();
    }
    static void _ShowFindUserScreen()
    {
        clsFindUserScreen::ShowFindUserScreen();
    }

    static void _PerformManageUsersOption(enManageUsersMenueOption Option)
    {
        switch (Option)
        {
        case enManageUsersMenueOption::eListUsers:
        {
            system("cls");
            _ShowListUsersScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenueOption::eAddNewUser:
        {
            system("cls");
            _ShowAddNewUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenueOption::eDeleteUser:
        {
            system("cls");
            _ShowDeleteUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenueOption::eUpdateUser:
        {
            system("cls");
            _ShowUpdateUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenueOption::eFindUser:
        {
            system("cls");
            _ShowFindUserScreen();
            _BackToManageUsersScreen();
            break;
        }
        case enManageUsersMenueOption::eMainMenue:
        {
            break;
        }
        }
    }

public:
    static void ShowManageUsersScreen()
    {
        if (!CheckAccessRights(clsUser::enPermissions::eManageUsers))
        {
            return;
        }

        system("cls");
        _DrawScreenHeader("Manage Users Screen");
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t\tManage Users Menue" << endl;
        cout << setw(35) << left << "" << "======================================" << endl;
        cout << setw(35) << left << "" << "\t[1] List Users." << endl;
        cout << setw(35) << left << "" << "\t[2] Add New User." << endl;
        cout << setw(35) << left << "" << "\t[3] Delete User." << endl;
        cout << setw(35) << left << "" << "\t[4] Update User." << endl;
        cout << setw(35) << left << "" << "\t[5] Find User." << endl;
        cout << setw(35) << left << "" << "\t[6] Main Menue." << endl;
        cout << setw(35) << left << "" << "======================================" << endl;

        _PerformManageUsersOption((enManageUsersMenueOption)_ReadManageUsersMenueOption());
    }
};