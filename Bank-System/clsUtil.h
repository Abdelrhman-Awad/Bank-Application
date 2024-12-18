#pragma once

#include <iostream>
#include <string>
#include "clsDate.h"

using namespace std;

class clsUtil
{
public:
    enum enCharType
    {
        SmallLetter = 1,
        CapitalLetter = 2,
        SpecialCharacter = 3,
        Digit = 4,
        MixChars = 5
    };

    static void Srand()
    {
        srand((unsigned)time(NULL));
    }

    static int RandomNumber(int From, int To)
    {
        int RandomNumber = rand() % (To - From + 1) + From;
        return RandomNumber;
    }

    static char GetRandomCharacter(enCharType CharType)
    {
        if (CharType == MixChars)
        {
            CharType = enCharType(RandomNumber(1, 4));
        }
        switch (CharType)
        {
        case enCharType::SmallLetter:
            return char(RandomNumber(97, 122));
            break;
        case enCharType::CapitalLetter:
            return char(RandomNumber(65, 90));
            break;
        case enCharType::SpecialCharacter:
            return char(RandomNumber(33, 47));
            break;
        case enCharType::Digit:
            return char(RandomNumber(48, 57));
            break;
        default:
            return char(RandomNumber(65, 90));
            break;
        }
    }

    static string GenerateWord(enCharType CharType, short Length)
    {
        string Word = "";

        for (int i = 1; i <= Length; i++)
        {
            Word += GetRandomCharacter(CharType);
        }

        return Word;
    }

    static string GenerateKey(enCharType CharType)
    {
        string Key = "";

        Key = GenerateWord(CharType, 4) + "-";
        Key += GenerateWord(CharType, 4) + "-";
        Key += GenerateWord(CharType, 4) + "-";
        Key += GenerateWord(CharType, 4);

        return Key;
    }

    static void GenerateKeys(short NumberOfKeys, enCharType CharType)
    {
        for (int i = 1; i <= NumberOfKeys; i++)
        {
            cout << "Key [" << i << "] : " << GenerateKey(CharType) << endl;
        }
    }

    static void Swap(int &num1, int &num2)
    {
        int temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    static void Swap(bool &num1, bool &num2)
    {
        bool temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    static void Swap(double &num1, double &num2)
    {
        double temp;
        temp = num1;
        num1 = num2;
        num2 = temp;
    }

    static void Swap(string &S1, string &S2)
    {
        string temp;
        temp = S1;
        S1 = S2;
        S2 = temp;
    }

    static void Swap(char &C1, char &C2)
    {
        char temp;
        temp = C1;
        C1 = C2;
        C2 = temp;
    }

    static void Swap(clsDate &Date1, clsDate &Date2)
    {
        clsDate::SwapDates(Date1, Date2);
    }

    static void FillArrayWithRandomNumbers(int Arr[100], int ArrLength, int From, int To)
    {
        for (int i = 0; i < ArrLength; i++)
            Arr[i] = RandomNumber(From, To);
    }

    static void FillArrayWithRandomWords(string Arr[100], int ArrLength, enCharType CharType, short WordLength)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Arr[i] = GenerateWord(CharType, WordLength);
        }
    }

    static void FillArrayWithRandomKeys(string Arr[100], int ArrLength, enCharType CharType)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Arr[i] = GenerateKey(CharType);
        }
    }

    static void ShuffleArray(int Arr[100], int ArrLength)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Swap(Arr[RandomNumber(1, ArrLength) - 1], Arr[RandomNumber(1, ArrLength) - 1]);
        }
    }

    static void ShuffleArray(string Arr[100], int ArrLength)
    {
        for (int i = 0; i < ArrLength; i++)
        {
            Swap(Arr[RandomNumber(1, ArrLength) - 1], Arr[RandomNumber(1, ArrLength) - 1]);
        }
    }

    static string EncryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] + EncryptionKey);
        }
        return Text;
    }

    static string DecryptText(string Text, short EncryptionKey)
    {

        for (int i = 0; i < Text.length(); i++)
        {
            Text[i] = char((int)Text[i] - EncryptionKey);
        }
        return Text;
    }

    static string Tabs(short NumberOfTabs)
    {
        string t = "";

        for (short i = 0; i < NumberOfTabs; i++)
        {
            t += "\t";
        }

        return t;
    }
    static string NumberToText(int Number)
    {

        if (Number == 0)
        {
            return "";
        }

        if (Number >= 1 && Number <= 19)
        {
            string arr[] = {"", "One", "Two", "Three", "Four", "Five", "Six", "Seven",
                            "Eight", "Nine", "Ten", "Eleven", "Twelve", "Thirteen", "Fourteen",
                            "Fifteen", "Sixteen", "Seventeen", "Eighteen", "Nineteen"};

            return arr[Number] + " ";
        }

        if (Number >= 20 && Number <= 99)
        {
            string arr[] = {"", "", "Twenty", "Thirty", "Forty", "Fifty", "Sixty", "Seventy", "Eighty", "Ninety"};
            return arr[Number / 10] + " " + NumberToText(Number % 10);
        }

        if (Number >= 100 && Number <= 199)
        {
            return "One Hundred " + NumberToText(Number % 100);
        }

        if (Number >= 200 && Number <= 999)
        {
            return NumberToText(Number / 100) + "Hundreds " + NumberToText(Number % 100);
        }

        if (Number >= 1000 && Number <= 1999)
        {
            return "One Thousand " + NumberToText(Number % 1000);
        }

        if (Number >= 2000 && Number <= 999999)
        {
            return NumberToText(Number / 1000) + "Thousands " + NumberToText(Number % 1000);
        }

        if (Number >= 1000000 && Number <= 1999999)
        {
            return "One Million " + NumberToText(Number % 1000000);
        }

        if (Number >= 2000000 && Number <= 999999999)
        {
            return NumberToText(Number / 1000000) + "Millions " + NumberToText(Number % 1000000);
        }

        if (Number >= 1000000000 && Number <= 1999999999)
        {
            return "One Billion " + NumberToText(Number % 1000000000);
        }
        else
        {
            return NumberToText(Number / 1000000000) + "Billions " + NumberToText(Number % 1000000000);
        }
    }
};