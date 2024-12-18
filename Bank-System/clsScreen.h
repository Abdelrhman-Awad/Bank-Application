#pragma once
#include <iostream>
#include <string>
#include <iomanip>
#include "clsGlobal.h"
#include "clsDate.h"

using namespace std;

class clsScreen
{

protected:
    static void _DrawScreenHeader(string Title, string SubTitle = "")
    {

        cout << setw(35) << left << "" << "____________________________________________\n"
             << endl;
        cout << setw(35) << left << "" << "\t\t" << Title << endl;
        if (SubTitle != "")
        {
            cout << "\n\t\t\t\t\t\t" << SubTitle << endl;
        }
        cout << setw(35) << left << "" << "____________________________________________\n"
             << endl;

        cout << setw(35) << left << "" << "User: " << CurrentUser.Username() << endl;
        cout << setw(35) << left << "" << "Date: " << clsDate::DateToString(clsDate()) << "\n\n";
    }

    static bool CheckAccessRights(clsUser::enPermissions Permission)
    {
        if (!CurrentUser.CheckAccessPermissions(Permission))
        {
            cout << setw(35) << left << "" << "______________________________________\n"
                 << endl;
            cout << setw(35) << left << "" << "  Access Denied! Contact Your Admin." << endl;
            cout << setw(35) << left << "" << "______________________________________\n"
                 << endl;

            return false;
        }
        return true;
    }
};