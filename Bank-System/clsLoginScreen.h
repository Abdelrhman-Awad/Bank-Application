#pragma once
#include <iostream>
#include "clsScreen.h"
#include "clsMainMenueScreen.h"
#include "clsGlobal.h"

class clsLoginScreen : protected clsScreen
{
private:
    static bool _Login()
    {
        bool LoginFailed = false;
        short Attemps = 3;
        do
        {

            if (LoginFailed)
            {
                Attemps--;
                cout << "\nInvalid Username/Password";
                cout << "\nYou have " << Attemps << " trails to login\n";
            }

            if (Attemps == 0)
            {
                cout << "\nYour are locked After 3 failed trails\n";
                return false;
            }

            string Username, Password;

            cout << "\nEnter Username: ";
            cin >> Username;
            cout << "\nEnter Password: ";
            cin >> Password;

            CurrentUser = clsUser::Find(Username, Password);

            LoginFailed = CurrentUser.IsEmpty();

        } while (LoginFailed);

        CurrentUser.RegisterLogin();
        clsMainMenueScreen::ShowMainMenueScreen();

        return true;
    }

public:
    static bool ShowLoginScreen()
    {
        system("cls");
        _DrawScreenHeader("Login Screen");
        return _Login();
    }
};