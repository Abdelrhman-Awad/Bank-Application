#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsPerson.h"
#include "clsString.h"

using namespace std;

class clsBankClient : public clsPerson
{
private:
    enum enMode
    {
        EmptyMode = 1,
        UpdateMode = 2,
        AddNewMode = 3
    };
    enMode _Mode;

    string _AccountNumber;
    string _PinCode;
    float _AccountBalance;
    bool _MarkForDelete = false;

    static clsBankClient _ConvertLineToClientObject(string Line, string Seperator = "#//#")
    {
        vector<string> vClientData;
        vClientData = clsString::Split(Line, Seperator);

        return clsBankClient(enMode::UpdateMode, vClientData[0], vClientData[1], vClientData[2], vClientData[3], vClientData[4], vClientData[5], stod(vClientData[6]));
    }

    static clsBankClient _GetEmptyClientObject()
    {
        return clsBankClient(enMode::EmptyMode, "", "", "", "", "", "", 0);
    }

    static vector<clsBankClient> _LoadClientsDateFromFile()
    {
        vector<clsBankClient> vClients;
        fstream MyFile;
        MyFile.open("Clients.txt", ios::in); // read Mode

        if (MyFile.is_open())
        {
            string Line;
            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                vClients.push_back(Client);
            }
            MyFile.close();
        }
        return vClients;
    }

    static string _ConverClientObjectToLine(clsBankClient Client, string Seperator = "#//#")
    {

        string stClientRecord = "";
        stClientRecord += Client.FirstName() + Seperator;
        stClientRecord += Client.LastName() + Seperator;
        stClientRecord += Client.Email() + Seperator;
        stClientRecord += Client.Phone() + Seperator;
        stClientRecord += Client.AccountNumber() + Seperator;
        stClientRecord += Client.PinCode() + Seperator;
        stClientRecord += to_string(Client.AccountBalance());

        return stClientRecord;
    }

    static void _SaveClientDataToFile(vector<clsBankClient> vClients)
    {

        fstream MyFile;
        MyFile.open("Clients.txt", ios::out);

        string DataLine;

        if (MyFile.is_open())
        {

            for (clsBankClient C : vClients)
            {
                if (C._MarkForDelete == false)
                {
                    DataLine = _ConverClientObjectToLine(C);
                    MyFile << DataLine << endl;
                }
            }

            MyFile.close();
        }
    }

    void _Update()
    {
        vector<clsBankClient> vClients;
        vClients = _LoadClientsDateFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C.AccountNumber() == AccountNumber())
            {
                C = *this;
                break;
            }
        }
        _SaveClientDataToFile(vClients);
    }

    void _AddDateLineToFile(string DataLine)
    {
        fstream MyFile;
        MyFile.open("Clients.txt", ios::out | ios::app);
        if (MyFile.is_open())
        {
            MyFile << DataLine << endl;
            MyFile.close();
        }
    }

    void _AddNew()
    {
        _AddDateLineToFile(_ConverClientObjectToLine(*this));
    }

    string _PrepareTransferRecord(double Amount, clsBankClient DestinationClient, string Username, string Seperator = "#//#")
    {
        string Record = "";
        Record += clsDate::GetSystemDateTimeString() + Seperator;
        Record += _AccountNumber + Seperator;
        Record += DestinationClient.AccountNumber() + Seperator;
        Record += to_string(Amount) + Seperator;
        Record += to_string(_AccountBalance) + Seperator;
        Record += to_string(DestinationClient.AccountBalance()) + Seperator;
        Record += Username;

        return Record;
    }

    void _SaveTransferLog(double Amount, clsBankClient DestinationClient, string Username)
    {

        string Record = _PrepareTransferRecord(Amount, DestinationClient, Username);
        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::out | ios::app);

        if (MyFile.is_open())
        {
            MyFile << Record << endl;
            MyFile.close();
        }
    }

public:
    struct stTranserLog;

private:
    static stTranserLog _GetTranserLog(string Line)
    {
        stTranserLog stTranserRecord;
        vector<string> stDataLine = clsString::Split(Line, "#//#");

        stTranserRecord.DateTime = stDataLine[0];
        stTranserRecord.SourceAccNum = stDataLine[1];
        stTranserRecord.DestinationAccNum = stDataLine[2];
        stTranserRecord.Amount = stod(stDataLine[3]);
        stTranserRecord.SourceBalance = stod(stDataLine[4]);
        stTranserRecord.DestinationBalance = stod(stDataLine[5]);
        stTranserRecord.Username = stDataLine[6];

        return stTranserRecord;
    }

public:
    clsBankClient(enMode Mode, string FirstName, string LastName, string Email, string Phone, string AccountNumber, string PinCode, float AccountBalance) : clsPerson(FirstName, LastName, Email, Phone)
    {
        _Mode = Mode;
        _AccountNumber = AccountNumber;
        _PinCode = PinCode;
        _AccountBalance = AccountBalance;
    }

    struct stTranserLog
    {
        string DateTime;
        string SourceAccNum;
        string DestinationAccNum;
        double Amount;
        double SourceBalance;
        double DestinationBalance;
        string Username;
    };

    bool IsEmpty()
    {
        return (_Mode == enMode::EmptyMode);
    }

    // Read Only Property
    string AccountNumber()
    {
        return _AccountNumber;
    }

    bool MarkForDelete()
    {
        return _MarkForDelete;
    }

    void SetPinCode(string PinCode)
    {
        _PinCode = PinCode;
    }

    string PinCode()
    {
        return _PinCode;
    }

    void SetAccountBalance(float AccountBalance)
    {
        _AccountBalance = AccountBalance;
    }

    float AccountBalance()
    {
        return _AccountBalance;
    }

    void Print()
    {
        cout << "\nClient Card:";
        cout << "\n___________________";
        cout << "\nFirstName   : " << FirstName();
        cout << "\nLastName    : " << LastName();
        cout << "\nFull Name   : " << FullName();
        cout << "\nEmail       : " << Email();
        cout << "\nPhone       : " << Phone();
        cout << "\nAcc. Number : " << _AccountNumber;
        cout << "\nPassword    : " << _PinCode;
        cout << "\nBalance     : " << _AccountBalance;
        cout << "\n___________________\n";
    }

    static clsBankClient Find(string AccountNumber)
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static clsBankClient Find(string AccountNumber, string PinCode)
    {
        fstream MyFile;

        MyFile.open("Clients.txt", ios::in);
        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsBankClient Client = _ConvertLineToClientObject(Line);
                if (Client.AccountNumber() == AccountNumber && Client.PinCode() == PinCode)
                {
                    MyFile.close();
                    return Client;
                }
            }
            MyFile.close();
        }
        return _GetEmptyClientObject();
    }

    static bool IsClientExiest(string AccountNumber)
    {
        clsBankClient Client = Find(AccountNumber);
        return (!Client.IsEmpty());
    }

    enum enSaveResults
    {
        svFaildEmptyObject = 1,
        svSucceded = 2,
        svFaildAccountNumberExist = 3
    };

    enSaveResults Save()
    {
        switch (_Mode)
        {
        case enMode::EmptyMode:
        {

            return enSaveResults::svFaildEmptyObject;
            break;
        }
        case enMode::UpdateMode:
        {
            _Update();
            return enSaveResults::svSucceded;
            break;
        }

        case enMode::AddNewMode:
        {
            if (IsClientExiest(_AccountNumber))
            {
                return enSaveResults::svFaildAccountNumberExist;
            }
            else
            {

                _AddNew();
                _Mode = enMode::UpdateMode;
                return enSaveResults::svSucceded;
            }
            break;
        }
        }
    }

    static clsBankClient GetAddNewClientObject(string AccountNumber)
    {
        return clsBankClient(enMode::AddNewMode, "", "", "", "", AccountNumber, "", 0);
    }

    bool Delete()
    {
        vector<clsBankClient> vClients;
        vClients = _LoadClientsDateFromFile();

        for (clsBankClient &C : vClients)
        {
            if (C._AccountNumber == _AccountNumber)
            {
                C._MarkForDelete = true;
                break;
            }
        }

        _SaveClientDataToFile(vClients);
        *this = _GetEmptyClientObject();

        return true;
    }

    static vector<clsBankClient> GetClientsList()
    {
        return _LoadClientsDateFromFile();
    }

    static double GetTotalBalances()
    {
        vector<clsBankClient> vClients = _LoadClientsDateFromFile();

        double TotalBalances = 0;

        for (clsBankClient C : vClients)
        {
            TotalBalances += C.AccountBalance();
        }

        return TotalBalances;
    }

    void Deposite(double Amount)
    {
        if (Amount < 0)
        {
            return;
        }
        _AccountBalance += Amount;
        Save();
    }

    bool Withdraw(double Amount)
    {
        if (Amount > _AccountBalance || Amount < 0)
        {
            return false;
        }
        else
        {
            _AccountBalance -= Amount;
            Save();
            return true;
        }
    }

    bool Transfer(double Amount, clsBankClient &DestinationClient, string Username)
    {
        if (Amount > _AccountBalance || _AccountNumber == DestinationClient.AccountNumber() || Amount < 0)
        {
            return false;
        }

        Withdraw(Amount);
        DestinationClient.Deposite(Amount);
        _SaveTransferLog(Amount, DestinationClient, Username);
        return true;
    }

    static vector<stTranserLog> GetTransferLogList()
    {
        vector<stTranserLog> vTransferLogs;
        stTranserLog Record;

        fstream MyFile;
        MyFile.open("TransferLogs.txt", ios::in);

        string Line;

        if (MyFile.is_open())
        {
            while (getline(MyFile, Line))
            {
                Record = _GetTranserLog(Line);
                vTransferLogs.push_back(Record);
            }
            MyFile.close();
        }

        return vTransferLogs;
    }
};