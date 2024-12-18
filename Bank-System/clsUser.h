#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include "clsPerson.h"
#include "clsString.h"
#include "clsDate.h"

using namespace std;

class clsUser : public clsPerson
{

private:
    enum enMode
    {
        eEmptyMode = 1,
        eUpdateMode = 2,
        eAddNewMode = 3
    };

    enMode _Mode;
    string _Username;
    string _Password;
    int _Permissions;
    bool _MarkForDelete = false;

    static clsUser _ConvertLineToUserObject(string Line, string Seperator = "#//#")
    {
        vector<string> vUserData;
        vUserData = clsString::Split(Line, Seperator);

        return clsUser(enMode::eUpdateMode, vUserData[0], vUserData[1], vUserData[2], vUserData[3], vUserData[4], clsString::DecryptText(vUserData[5]), stoi(vUserData[6]));
    }

    static clsUser _GetEmptyUserObject()
    {
        return clsUser(enMode::eEmptyMode, "", "", "", "", "", "", 0);
    }

    static string _ConvertUserObjectToLine(clsUser User, string Seperator = "#//#")
    {
        string strUserRecord = "";
        strUserRecord += User.FirstName() + Seperator;
        strUserRecord += User.LastName() + Seperator;
        strUserRecord += User.Email() + Seperator;
        strUserRecord += User.Phone() + Seperator;
        strUserRecord += User.Username() + Seperator;
        strUserRecord += clsString::EncryptText(User.Password()) + Seperator;
        strUserRecord += to_string(User.Permissions());

        return strUserRecord;
    }

    static vector<clsUser> _LoadUsersDataFromFile()
    {
        vector<clsUser> vUsers;

        fstream MyFile;
        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                vUsers.push_back(User);
            }

            MyFile.close();
        }
        return vUsers;
    }

    static void _SaveUsersDataToFile(vector<clsUser> vUsers)
    {

        fstream MyFile;
        MyFile.open("Users.txt", ios::out);

        string Line;
        if (MyFile.is_open())
        {

            for (clsUser User : vUsers)
            {
                if (User.MarkForDelete() == false)
                {
                    Line = _ConvertUserObjectToLine(User);
                    MyFile << Line << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsUser> vUsers;
        vUsers = _LoadUsersDataFromFile();

        for (clsUser &User : vUsers)
        {
            if (User.Username() == _Username)
            {
                User = *this;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);
    }

    void _AddDataLineToFile(string DataLine)
    {
        fstream MyFile;
        MyFile.open("Users.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    void _AddNew()
    {
        _AddDataLineToFile(_ConvertUserObjectToLine(*this));
    }

    string _PrapareLoginRecord(string Seperator = "#//#")
    {
        string LoginRecord = "";

        LoginRecord += clsDate::GetSystemDateTimeString() + Seperator;
        LoginRecord += this->Username() + Seperator;
        LoginRecord += clsString::EncryptText(this->Password()) + Seperator;
        LoginRecord += to_string(this->Permissions());

        return LoginRecord;
    }

public:
    struct stLoginRegisterRecord;

private:
    static stLoginRegisterRecord _ConvertLoginRegisterLineToRecord(string Line, string Seperator = "#//#")
    {
        vector<string> LoginRegisterDataLine = clsString::Split(Line, Seperator);

        stLoginRegisterRecord LoginRegisterRecord;

        LoginRegisterRecord.DateTime = LoginRegisterDataLine[0];
        LoginRegisterRecord.Username = LoginRegisterDataLine[1];
        LoginRegisterRecord.Password = clsString::DecryptText(LoginRegisterDataLine[2]);
        LoginRegisterRecord.Permissions = stoi(LoginRegisterDataLine[3]);

        return LoginRegisterRecord;
    }

public:
    clsUser(enMode Mode, string FirstName, string LastName, string Email, string Phone, string Username, string Password, int Permissions) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _Username = Username;
        _Password = Password;
        _Permissions = Permissions;
    }

    enum enPermissions
    {
        eAll = -1,
        eShowClientList = 1,
        eAddNew = 2,
        eDeleteClient = 4,
        eUpdateClient = 8,
        eFindClient = 16,
        eTransactions = 32,
        eManageUsers = 64,
        eLoginRegister = 128
    };

    struct stLoginRegisterRecord
    {
        string DateTime;
        string Username;
        string Password;
        int Permissions;
    };

    void SetUsername(string Username)
    {
        _Username = Username;
    }

    string Username()
    {
        return _Username;
    }

    void SetPassword(string Password)
    {
        _Password = Password;
    }

    string Password()
    {
        return _Password;
    }

    void SetPermissions(int Permissions)
    {
        _Permissions = Permissions;
    }

    int Permissions()
    {
        return _Permissions;
    }

    bool MarkForDelete()
    {
        return _MarkForDelete;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::eEmptyMode);
    }

    static clsUser Find(string Username)
    {
        fstream MyFile;

        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.Username() == Username)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static clsUser Find(string Username, string Password)
    {
        fstream MyFile;

        MyFile.open("Users.txt", ios::in);

        if (MyFile.is_open())
        {

            string Line;

            while (getline(MyFile, Line))
            {
                clsUser User = _ConvertLineToUserObject(Line);
                if (User.Username() == Username && User.Password() == Password)
                {
                    MyFile.close();
                    return User;
                }
            }
            MyFile.close();
        }

        return _GetEmptyUserObject();
    }

    static bool IsUserExist(string Username)
    {
        clsUser User = Find(Username);

        return (!User.IsEmpty());
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 1,
        svSucceded = 2,
        svFaildUserExist = 3
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::eEmptyMode:
        {
            return enSaveResults::svFaildEmptyObject;

            break;
        }
        case enMode::eUpdateMode:
        {
            _Update();
            return enSaveResults::svSucceded;

            break;
        }
        case enMode::eAddNewMode:
        {
            if (clsUser::IsUserExist(_Username))
            {
                return enSaveResults::svFaildUserExist;
            }
            else
            {

                _AddNew();
                _Mode = enMode::eUpdateMode;
                return enSaveResults::svSucceded;
            }
            break;
        }
        }
    }

    bool Delete()
    {
        vector<clsUser> vUsers;
        vUsers = _LoadUsersDataFromFile();

        for (clsUser &User : vUsers)
        {
            if (User.Username() == _Username)
            {
                User._MarkForDelete = true;
                break;
            }
        }

        _SaveUsersDataToFile(vUsers);
        *this = _GetEmptyUserObject();

        return true;
    }

    static clsUser GetAddNewUserObject(string Username)
    {
        return clsUser(enMode::eAddNewMode, "", "", "", "", Username, "", 0);
    }

    static vector<clsUser> GetUserList()
    {
        return _LoadUsersDataFromFile();
    }

    bool CheckAccessPermissions(enPermissions Permission)
    {
        if (this->_Permissions == enPermissions::eAll)
        {
            return true;
        }

        if ((this->_Permissions & Permission) == Permission)
        {
            return true;
        }
        else
        {
            return false;
        }
    }

    void RegisterLogin()
    {
        string strDateLine = _PrapareLoginRecord();

        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << strDateLine << endl;
            MyFile.close();
        }
    }

    static vector<stLoginRegisterRecord> GetLoginRegisterList()
    {
        vector<stLoginRegisterRecord> vLoginRegisterRecord;
        fstream MyFile;
        MyFile.open("LoginRegister.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            stLoginRegisterRecord Logs;
            string Line;
            while (getline(MyFile, Line))
            {
                Logs = _ConvertLoginRegisterLineToRecord(Line);
                vLoginRegisterRecord.push_back(Logs);
            }
            MyFile.close();
        }
        return vLoginRegisterRecord;
    }
};