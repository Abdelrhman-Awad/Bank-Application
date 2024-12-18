#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "clsString.h"

using namespace std;

class clsCurrency
{
private:
    enum enMode
    {
        eEmptyMode = 1,
        eUpdateMode = 2
    };
    enMode _Mode;

    string _Country;
    string _CurrencyCode;
    string _CurrencyName;
    float _Rate;

    static clsCurrency _ConvertLineToCurrencyObject(string Line, string Seperator = "#//#")
    {
        vector<string> vDataLine = clsString::Split(Line, Seperator);

        return clsCurrency(enMode::eUpdateMode, vDataLine[0], vDataLine[1], vDataLine[2], stof(vDataLine[3]));
    }

    static vector<clsCurrency> _LoadCurrencyDataFromFile()
    {

        vector<clsCurrency> vCurrencyData;
        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);
                vCurrencyData.push_back(Currency);
            }
            MyFile.close();
        }

        return vCurrencyData;
    }

    string _ConvertCurrencyObjectToLine(clsCurrency Currency, string Seperator = "#//#")
    {
        string stDataLine = "";

        stDataLine += Currency.Country() + Seperator;
        stDataLine += Currency.CurrencyCode() + Seperator;
        stDataLine += Currency.CurrencyName() + Seperator;
        stDataLine += to_string(Currency.Rate());

        return stDataLine;
    }

    void _SaveCurrencyDataToFile(vector<clsCurrency> vCurrencyData)
    {
        fstream Myfile;
        Myfile.open("Currencies.txt", ios::out);

        string Line;

        if (Myfile.is_open())
        {
            for (clsCurrency C : vCurrencyData)
            {
                Line = _ConvertCurrencyObjectToLine(C);
                Myfile << Line << endl;
            }

            Myfile.close();
        }
    }

    void _Update()
    {

        vector<clsCurrency> vCurrencyData = _LoadCurrencyDataFromFile();

        for (clsCurrency &C : vCurrencyData)
        {
            if (C.CurrencyCode() == _CurrencyCode)
            {
                C = *this;
                break;
            }
        }
        _SaveCurrencyDataToFile(vCurrencyData);
    }

    static clsCurrency _GetEmptyCurrencyObject()
    {
        return clsCurrency(enMode::eEmptyMode, "", "", "", 0);
    }

public:
    clsCurrency(enMode Mode, string Country, string CurrencyCode, string CurrencyName, float Rate)
    {
        _Mode = Mode;
        _Country = Country;
        _CurrencyCode = CurrencyCode;
        _CurrencyName = CurrencyName;
        _Rate = Rate;
    }

    string Country()
    {
        return _Country;
    }

    string CurrencyCode()
    {
        return _CurrencyCode;
    }

    string CurrencyName()
    {
        return _CurrencyName;
    }

    void UpdateRate(float NewRate)
    {
        _Rate = NewRate;
        _Update();
    }

    float Rate()
    {
        return _Rate;
    }

    bool IsEmpty()
    {
        return (_Mode == enMode::eEmptyMode);
    }

    static clsCurrency FindByCode(string CurrencyCode)
    {
        CurrencyCode = clsString::UpperAllString(CurrencyCode);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                if (Currency.CurrencyCode() == CurrencyCode)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static clsCurrency FindByCountry(string Country)
    {
        Country = clsString::UpperAllString(Country);

        fstream MyFile;
        MyFile.open("Currencies.txt", ios::in);

        if (MyFile.is_open())
        {
            string Line;

            while (getline(MyFile, Line))
            {
                clsCurrency Currency = _ConvertLineToCurrencyObject(Line);

                if (clsString::UpperAllString(Currency.Country()) == Country)
                {
                    MyFile.close();
                    return Currency;
                }
            }
            MyFile.close();
        }
        return _GetEmptyCurrencyObject();
    }

    static bool IsCurrencyExist(string Code)
    {
        clsCurrency Currency = clsCurrency::FindByCode(Code);
        return (!Currency.IsEmpty());
    }

    static vector<clsCurrency> GetCurrenciesList()
    {
        return _LoadCurrencyDataFromFile();
    }

    float ConvertToUSD(float Amount)
    {
        return (float)(Amount / _Rate);
    }

    float ConvertToOtherCurrency(float Amount, clsCurrency Currency)
    {
        float AmountInUSD = ConvertToUSD(Amount);
        if (Currency.CurrencyCode() == "USD")
        {
            return AmountInUSD;
        }

        return (float)(AmountInUSD * Currency.Rate());
    }
};