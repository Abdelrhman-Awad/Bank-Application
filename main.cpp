#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

struct sUser
{
    string Username;
    string Password;
    short Permissions;
    bool MarkForDelete = false;
};

struct sClient
{
    string AccountNumber;
    string PinCode;
    string Name;
    string Phone;
    double AccountBalance;
    bool MarkForDelete = false;
};

enum enMainMenueOptions
{
    eListClients = 1,
    eAddNewClient = 2,
    eDeleteClient = 3,
    eUpdateClient = 4,
    eFindClient = 5,
    eTransactions = 6,
    eManageUsers = 7,
    eLogout = 8
};

enum enTransationsMenueOptions
{
    eDeposit = 1,
    eWithdraw = 2,
    eTotalBalances = 3,
    eMainMenue = 4
};

enum enManageUsersOptions
{
    eListUsers = 1,
    eAddUser = 2,
    eDeleteUser = 3,
    eUpdateUser = 4,
    eFindUser = 5,
    eBackMainMenue = 6
};

enum enPermissions
{
    eShow = 1,
    eAdd = 2,
    eDelete = 4,
    eUpdate = 8,
    eFind = 16,
    eTransaction = 32,
    eManage = 64
};

const string ClientsFileName = "Clients.txt";
const string UsersFileName = "Users.txt";
sUser CurrentUser;

void Login();
void ShowMainMenue();
void ShowTransationsScreen();
void ShowManageUserScreen();

void PrintAccessDeniedScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "Access Denied,\n";
    cout << "You don't Have Permission To Do This,\n";
    cout << "Please Contact Your Admin.";
    cout << "\n-----------------------------------\n";
}

bool CheckUserPermissions(enPermissions Permission)
{
    return ((CurrentUser.Permissions == -1) || ((CurrentUser.Permissions & Permission) == Permission)) ? true : false;
}

vector<string> SplitString(string S1, string Delim)
{
    vector<string> vString;
    short pos = 0;
    string sWord; // define a string variable
                  // use find() function to get the position of the delimiters
    while ((pos = S1.find(Delim)) != std::string::npos)
    {
        sWord = S1.substr(0, pos); // store the word
        if (sWord != "")
        {
            vString.push_back(sWord);
        }
        S1.erase(0, pos + Delim.length()); // erase() until positon and move to next word.
    }
    if (S1 != "")
    {
        vString.push_back(S1); // it adds last word of the string.
    }
    return vString;
}

sClient ConvertLinetoRecord(string Line, string Seperator = "#//#")
{
    sClient Client;
    vector<string> vClientData;
    vClientData = SplitString(Line, Seperator);
    Client.AccountNumber = vClientData[0];
    Client.PinCode = vClientData[1];
    Client.Name = vClientData[2];
    Client.Phone = vClientData[3];
    Client.AccountBalance = stod(vClientData[4]); // cast string to double
    return Client;
}

string ConvertRecordToLine(sClient Client, string Seperator = "#//#")
{
    string stClientRecord = "";
    stClientRecord += Client.AccountNumber + Seperator;
    stClientRecord += Client.PinCode + Seperator;
    stClientRecord += Client.Name + Seperator;
    stClientRecord += Client.Phone + Seperator;
    stClientRecord += to_string(Client.AccountBalance);
    return stClientRecord;
}

bool ClientExistsByAccountNumber(string AccountNumber, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode
    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            if (Client.AccountNumber == AccountNumber)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

sClient ReadNewClient()
{
    sClient Client;

    cout << "Enter Account Number? "; // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, Client.AccountNumber);

    while (ClientExistsByAccountNumber(Client.AccountNumber, ClientsFileName))
    {
        cout << "\nClient with [" << Client.AccountNumber << "] already exists, Enter another Account Number? ";
        getline(cin >> ws, Client.AccountNumber);
    }

    cout << "Enter PinCode? ";
    getline(cin, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

vector<sClient> LoadCleintsDataFromFile(string FileName)
{
    vector<sClient> vClients;
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode

    if (MyFile.is_open())
    {
        string Line;
        sClient Client;
        while (getline(MyFile, Line))
        {
            Client = ConvertLinetoRecord(Line);
            vClients.push_back(Client);
        }
        MyFile.close();
    }
    return vClients;
}

void PrintClientRecordLine(sClient Client)
{
    cout << "| " << setw(15) << left << Client.AccountNumber;
    cout << "| " << setw(10) << left << Client.PinCode;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(12) << left << Client.Phone;
    cout << "| " << setw(12) << left << Client.AccountBalance;
}

void ShowAllClientsScreen()
{

    if (!CheckUserPermissions(enPermissions::eShow))
    {
        PrintAccessDeniedScreen();
        return;
    }

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    cout << "\n\t\t\t\t\tClient List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(15) << "Accout Number";
    cout << "| " << left << setw(10) << "Pin Code";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(12) << "Phone";
    cout << "| " << left << setw(12) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    if (vClients.size() == 0)
    {

        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {
        for (sClient Client : vClients)
        {
            PrintClientRecordLine(Client);
            cout << endl;
        }
    }
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

void PrintClientCard(sClient Client)
{
    cout << "\nThe following are the client details:\n";
    cout << "-----------------------------------";
    cout << "\nAccout Number: " << Client.AccountNumber;
    cout << "\nPin Code     : " << Client.PinCode;
    cout << "\nName         : " << Client.Name;
    cout << "\nPhone        : " << Client.Phone;
    cout << "\nAccount Balance: " << Client.AccountBalance;
    cout << "\n-----------------------------------\n";
}

bool FindClientByAccountNumber(string AccountNumber, vector<sClient> vClients, sClient &Client)
{
    for (sClient C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            Client = C;
            return true;
        }
    }
    return false;
}

sClient ChangeClientRecord(string AccountNumber)
{
    sClient Client;
    Client.AccountNumber = AccountNumber;
    cout << "\n\nEnter PinCode? ";
    getline(cin >> ws, Client.PinCode);
    cout << "Enter Name? ";
    getline(cin, Client.Name);
    cout << "Enter Phone? ";
    getline(cin, Client.Phone);
    cout << "Enter AccountBalance? ";
    cin >> Client.AccountBalance;
    return Client;
}

bool MarkClientForDeleteByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    for (sClient &C : vClients)
    {
        if (C.AccountNumber == AccountNumber)
        {
            C.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sClient> SaveCleintsDataToFile(string FileName, vector<sClient> vClients)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;

    if (MyFile.is_open())
    {
        for (sClient C : vClients)
        {
            if (C.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertRecordToLine(C);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vClients;
}

void AddDataLineToFile(string FileName, string stDataLine)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out | ios::app);
    if (MyFile.is_open())
    {
        MyFile << stDataLine << endl;
        MyFile.close();
    }
}

void AddNewClient()
{
    sClient Client;
    Client = ReadNewClient();
    AddDataLineToFile(ClientsFileName, ConvertRecordToLine(Client));
}

void AddNewClients()
{
    char AddMore = 'Y';
    do
    {
        cout << "Adding New Client:\n\n";
        AddNewClient();
        cout << "\nClient Added Successfully, do you want to add more clients? y/n? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void DeleteClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        PrintClientCard(Client);
        cout << "\n\nAre you sure you want delete this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkClientForDeleteByAccountNumber(AccountNumber, vClients);
            SaveCleintsDataToFile(ClientsFileName, vClients); // Refresh Clients
            vClients = LoadCleintsDataFromFile(ClientsFileName);
            cout << "\n\nClient Deleted Successfully.";
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
}

void UpdateClientByAccountNumber(string AccountNumber, vector<sClient> &vClients)
{
    sClient Client;
    char Answer = 'n';
    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
    {

        PrintClientCard(Client);
        cout << "\n\nAre you sure you want update this client? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sClient &C : vClients)
            {
                if (C.AccountNumber == AccountNumber)
                {
                    C = ChangeClientRecord(AccountNumber);
                    break;
                }
            }
            SaveCleintsDataToFile(ClientsFileName, vClients);
            cout << "\n\nClient Updated Successfully.";
        }
    }
    else
    {
        cout << "\nClient with Account Number (" << AccountNumber << ") is Not Found!";
    }
}

string ReadClientAccountNumber()
{
    string AccountNumber = "";
    cout << "\nPlease enter AccountNumber? ";
    cin >> AccountNumber;
    return AccountNumber;
}

void ShowDeleteClientScreen()
{
    if (!CheckUserPermissions(enPermissions::eDelete))
    {
        PrintAccessDeniedScreen();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tDelete Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    DeleteClientByAccountNumber(AccountNumber, vClients);
}

void ShowUpdateClientScreen()
{

    if (!CheckUserPermissions(enPermissions::eUpdate))
    {
        PrintAccessDeniedScreen();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Client Info Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();
    UpdateClientByAccountNumber(AccountNumber, vClients);
}

void ShowAddNewClientsScreen()
{
    if (!CheckUserPermissions(enPermissions::eAdd))
    {
        PrintAccessDeniedScreen();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tAdd New Clients Screen";
    cout << "\n-----------------------------------\n";
    AddNewClients();
}

void ShowFindClientScreen()
{

    if (!CheckUserPermissions(enPermissions::eFind))
    {
        PrintAccessDeniedScreen();
        return;
    }

    cout << "\n-----------------------------------\n";
    cout << "\tFind Client Screen";
    cout << "\n-----------------------------------\n";
    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    sClient Client;
    string AccountNumber = ReadClientAccountNumber();

    if (FindClientByAccountNumber(AccountNumber, vClients, Client))
        PrintClientCard(Client);
    else
        cout << "\nClient with Account Number[" << AccountNumber << "] is not found!";
}

void ShowEndScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tProgram Ends :-)";
    cout << "\n-----------------------------------\n";
}

void GoBackToMainMenue()
{
    cout << "\n\nPress any key to go back to Main Menue...";
    system("pause>0");
    ShowMainMenue();
}

void GoBackToTransationsMenue()
{
    cout << "\n\nPress any key to go back to Transations Menue...";
    system("pause>0");
    ShowTransationsScreen();
}

void GoBackToManageUsersMenue()
{
    cout << "\n\nPress any key to go back to Manage Users Menue...";
    system("pause>0");
    ShowManageUserScreen();
}

short ReadMainMenueOption()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 8]? ";
        cin >> Choice;
    } while (Choice < 0 || Choice > 8);

    return Choice;
}

short ReadTransationsMenueOption()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 4]? ";
        cin >> Choice;
    } while (Choice < 0 || Choice > 4);

    return Choice;
}

bool DepostAmountByAccountNumber(string AccountNumber, double Amount, vector<sClient> &vClients)
{

    char Answer = 'n';

    cout << "\n\nAre you sure you want perform this transation? y/n ? ";
    cin >> Answer;

    if (Answer == 'y' || Answer == 'Y')
    {
        for (sClient &C : vClients)
        {
            if (C.AccountNumber == AccountNumber)
            {
                C.AccountBalance += Amount;
                SaveCleintsDataToFile(ClientsFileName, vClients);
                cout << "\n\nDone Successfully, The New Balance is " << C.AccountBalance << endl;

                return true;
            }
        }
    }
    return false;
}

void ShowDepositScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDeposit Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With [" << AccountNumber << "] does not exist." << endl;
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;

    do
    {
        cout << "\n\nPlease Enter Deposit Amount? ";
        cin >> Amount;
    } while (Amount < 0);

    DepostAmountByAccountNumber(AccountNumber, Amount, vClients);
}

void ShowWithdrawScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tWithdraw Screen";
    cout << "\n-----------------------------------\n";

    sClient Client;

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);
    string AccountNumber = ReadClientAccountNumber();

    while (!FindClientByAccountNumber(AccountNumber, vClients, Client))
    {
        cout << "\nClient With [" << AccountNumber << "] does not exist." << endl;
        AccountNumber = ReadClientAccountNumber();
    }

    PrintClientCard(Client);

    double Amount = 0;

    cout << "\n\nPlease Enter Withdraw Amount? ";
    cin >> Amount;

    while (Amount > Client.AccountBalance)
    {
        cout << "\nAmount Exceeds the balance, you can withdraw up to: " << Client.AccountBalance << endl;
        cout << "Please Enter Another Amount? ";
        cin >> Amount;
    }

    DepostAmountByAccountNumber(AccountNumber, Amount * -1, vClients);
}

void PrintShortClientRecord(sClient Client)
{
    cout << "| " << setw(19) << left << Client.AccountNumber;
    cout << "| " << setw(40) << left << Client.Name;
    cout << "| " << setw(30) << left << Client.AccountBalance;
}

void ShowTotalBalanceScreen()
{

    vector<sClient> vClients = LoadCleintsDataFromFile(ClientsFileName);

    cout << "\n\t\t\t\t\tBalances List (" << vClients.size() << ") Client(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(19) << "Accout Number";
    cout << "| " << left << setw(40) << "Client Name";
    cout << "| " << left << setw(30) << "Balance";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    double TotalBalances = 0;

    if (vClients.size() == 0)
    {

        cout << "\t\t\t\tNo Clients Available In the System!";
    }
    else
    {

        for (sClient Client : vClients)
        {
            TotalBalances += Client.AccountBalance;
            PrintShortClientRecord(Client);
            cout << endl;
        }
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "\t\t\t\t\tTotal Balances = " << TotalBalances;
}

void PerformTransationsOption(enTransationsMenueOptions TransationsMenueOption)
{

    switch (TransationsMenueOption)
    {
    case enTransationsMenueOptions::eDeposit:
    {
        system("cls");
        ShowDepositScreen();
        GoBackToTransationsMenue();
        break;
    }
    case enTransationsMenueOptions::eWithdraw:
    {
        system("cls");
        ShowWithdrawScreen();
        GoBackToTransationsMenue();
        break;
    }
    case enTransationsMenueOptions::eTotalBalances:
    {
        system("cls");
        ShowTotalBalanceScreen();
        GoBackToTransationsMenue();
        break;
    }
    case enTransationsMenueOptions::eMainMenue:
    {
        ShowMainMenue();
    }
    }
}

void ShowTransationsScreen()
{
    if (!CheckUserPermissions(enPermissions::eTransaction))
    {
        PrintAccessDeniedScreen();
        GoBackToMainMenue();
        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tTransations Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Deposit.\n";
    cout << "\t[2] Withdraw.\n";
    cout << "\t[3] Total Balances.\n";
    cout << "\t[4] Main Menue.\n";
    cout << "===========================================\n";

    PerformTransationsOption((enTransationsMenueOptions)ReadTransationsMenueOption());
}

short ReadManageUsersMenueOption()
{
    short Choice = 0;
    do
    {
        cout << "Choose what do you want to do? [1 to 6]? ";
        cin >> Choice;
    } while (Choice < 0 || Choice > 6);

    return Choice;
}

void PrintUserRecordLine(sUser User)
{
    cout << "| " << setw(25) << left << User.Username;
    cout << "| " << setw(20) << left << User.Password;
    cout << "| " << setw(45) << left << User.Permissions;
}

sUser ConvertUserLinetoRecord(string Line, string Seperator = "#//#")
{
    sUser User;
    vector<string> vUserDate;

    vUserDate = SplitString(Line, Seperator);

    User.Username = vUserDate[0];
    User.Password = vUserDate[1];
    User.Permissions = stoi(vUserDate[2]); // cast string to integer

    return User;
}

string ConvertUserRecordToLine(sUser User, string Seperator = "#//#")
{
    string UserRecord = "";
    UserRecord += User.Username + Seperator;
    UserRecord += User.Password + Seperator;
    UserRecord += to_string(User.Permissions);

    return UserRecord;
}

vector<sUser> LoadUsersDataFromFile(string FileName)
{
    vector<sUser> vUsers;
    fstream MyFile;
    MyFile.open(FileName, ios::in);

    if (MyFile.is_open())
    {
        string Line;
        sUser User;
        while (getline(MyFile, Line))
        {
            User = ConvertUserLinetoRecord(Line);
            vUsers.push_back(User);
        }
        MyFile.close();
    }
    return vUsers;
}

bool FindUserByUsernameAndPassword(string Username, string Password, sUser &User)
{
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);

    for (sUser U : vUsers)
    {
        if (U.Username == Username && U.Password == Password)
        {
            User = U;
            return true;
        }
    }

    return false;
}

void ShowAllUserScreen()
{
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    cout << "\n\t\t\t\t\tUsers List (" << vUsers.size() << ") User(s).";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
    cout << "| " << left << setw(25) << "User Name";
    cout << "| " << left << setw(20) << "Password";
    cout << "| " << left << setw(45) << "Permissions";
    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;

    for (sUser User : vUsers)
    {
        PrintUserRecordLine(User);
        cout << endl;
    }

    cout << "\n_______________________________________________________";
    cout << "_________________________________________\n"
         << endl;
}

bool UserExistsByUsername(string Username, string FileName)
{
    fstream MyFile;
    MyFile.open(FileName, ios::in); // read Mode
    if (MyFile.is_open())
    {
        string Line;
        sUser User;
        while (getline(MyFile, Line))
        {
            User = ConvertUserLinetoRecord(Line);
            if (User.Username == Username)
            {
                MyFile.close();
                return true;
            }
        }
        MyFile.close();
    }
    return false;
}

short ReadUserPermissions()
{
    short Permissions = 0;
    char Answer = 'n';

    cout << "\nDo you want to give full Access? y/n? ";
    cin >> Answer;

    if (toupper(Answer) == 'Y')
    {
        return -1;
    }

    cout << "\nDo you want to give Access to:\n";

    cout << "\nShow Clients List? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eShow;
    }

    cout << "\nAdd New Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eAdd;
    }

    cout << "\nDelete Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eDelete;
    }

    cout << "\nUpdate Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eUpdate;
    }

    cout << "\nFind Client? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eFind;
    }

    cout << "\nTransactions? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eTransaction;
    }

    cout << "\nManage Users? y/n? ";
    cin >> Answer;
    if (toupper(Answer) == 'Y')
    {
        Permissions += enPermissions::eManage;
    }

    return Permissions;
}

sUser ReadNewUser()
{
    sUser User;

    cout << "Enter Username? "; // Usage of std::ws will extract allthe whitespace character
    getline(cin >> ws, User.Username);

    while (UserExistsByUsername(User.Username, UsersFileName))
    {
        cout << "\nUser with [" << User.Username << "] already exists, Enter another Username? ";
        getline(cin >> ws, User.Username);
    }

    cout << "Enter Password? ";
    getline(cin, User.Password);

    char Answer = 'n';

    User.Permissions = ReadUserPermissions();

    return User;
}

void AddNewUser()
{
    sUser User;
    User = ReadNewUser();
    AddDataLineToFile(UsersFileName, ConvertUserRecordToLine(User));
}

void AddNewUsers()
{
    char AddMore = 'Y';
    do
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tAdd New User Screen";
        cout << "\n-----------------------------------\n";
        cout << "\nAdding New User:\n\n";
        AddNewUser();
        cout << "\nUser Added Successfully, do you want to add more User? y/n? ";
        cin >> AddMore;
    } while (toupper(AddMore) == 'Y');
}

void ShowAddNewUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tAdd New User Screen";
    cout << "\n-----------------------------------\n";
    AddNewUsers();
}

string ReadUsername()
{
    string Username = "";
    cout << "\nPlease enter Username? ";
    cin >> Username;

    return Username;
}

bool FindUserByUsername(string Username, vector<sUser> vUsers, sUser &User)
{
    for (sUser U : vUsers)
    {
        if (U.Username == Username)
        {
            User = U;
            return true;
        }
    }
    return false;
}

void PrintUserCard(sUser User)
{
    cout << "\nThe following are the User details:\n";
    cout << "-----------------------------------";
    cout << "\nUsername    : " << User.Username;
    cout << "\nPassword    : " << User.Password;
    cout << "\nPermissions : " << User.Permissions;
    cout << "\n-----------------------------------\n";
}

bool MarkUserForDeleteByUsername(string Username, vector<sUser> &vUsers)
{
    for (sUser &U : vUsers)
    {
        if (U.Username == Username)
        {
            U.MarkForDelete = true;
            return true;
        }
    }
    return false;
}

vector<sUser> SaveUsersDataToFile(string FileName, vector<sUser> vUsers)
{
    fstream MyFile;
    MyFile.open(FileName, ios::out); // overwrite
    string DataLine;

    if (MyFile.is_open())
    {
        for (sUser U : vUsers)
        {
            if (U.MarkForDelete == false)
            {
                // we only write records that are not marked for delete.
                DataLine = ConvertUserRecordToLine(U);
                MyFile << DataLine << endl;
            }
        }
        MyFile.close();
    }
    return vUsers;
}

void DeleteUserByUsername(string Username, vector<sUser> &vUsers)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUsername(Username, vUsers, User))
    {
        PrintUserCard(User);
        cout << "\n\nAre you sure you want delete this User? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            MarkUserForDeleteByUsername(Username, vUsers);
            SaveUsersDataToFile(UsersFileName, vUsers); // Refresh Clients
            vUsers = LoadUsersDataFromFile(UsersFileName);
            cout << "\n\nUser Deleted Successfully.";
        }
    }
    else
    {
        cout << "\nUser with Username (" << Username << ") is Not Found!";
    }
}

bool IsAdmin(string Username)
{
    return (Username == "Admin") ? true : false;
}

void ShowDeleteUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tDelete User Screen";
    cout << "\n-----------------------------------\n";
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();

    if (IsAdmin(Username))
    {
        cout << "\nYou Cannot Delete This User.\n";
        return;
    }

    DeleteUserByUsername(Username, vUsers);
}

sUser ChangeUserRecord(string Username)
{
    sUser User;
    User.Username = Username;
    cout << "\n\nEnter Password? ";
    getline(cin >> ws, User.Password);

    User.Permissions = ReadUserPermissions();

    return User;
}

void UpdateUserByUsername(string Username, vector<sUser> &vUsers)
{
    sUser User;
    char Answer = 'n';
    if (FindUserByUsername(Username, vUsers, User))
    {

        PrintUserCard(User);
        cout << "\n\nAre you sure you want update this user? y/n ? ";
        cin >> Answer;
        if (Answer == 'y' || Answer == 'Y')
        {
            for (sUser &U : vUsers)
            {
                if (U.Username == Username)
                {
                    U = ChangeUserRecord(Username);
                    break;
                }
            }
            SaveUsersDataToFile(UsersFileName, vUsers);
            cout << "\n\nUser Updated Successfully.";
        }
    }
    else
    {
        cout << "\nUser With Username (" << Username << ") is Not Found!";
    }
}

void ShowUpdateUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tUpdate Users Screen";
    cout << "\n-----------------------------------\n";
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    string Username = ReadUsername();
    UpdateUserByUsername(Username, vUsers);
}

void ShowFindUserScreen()
{
    cout << "\n-----------------------------------\n";
    cout << "\tFind User Screen";
    cout << "\n-----------------------------------\n";
    vector<sUser> vUsers = LoadUsersDataFromFile(UsersFileName);
    sUser User;
    string Username = ReadUsername();
    if (FindUserByUsername(Username, vUsers, User))
        PrintUserCard(User);
    else
        cout << "\nUser with Username[" << Username << "] is not found!";
}

void PerformManageUsersOption(enManageUsersOptions ManageMenueOption)
{
    switch (ManageMenueOption)
    {
    case enManageUsersOptions::eListUsers:
    {
        system("cls");
        ShowAllUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eAddUser:
    {
        system("cls");
        ShowAddNewUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eDeleteUser:
    {
        system("cls");
        ShowDeleteUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eUpdateUser:
    {
        system("cls");
        ShowUpdateUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eFindUser:
    {
        system("cls");
        ShowFindUserScreen();
        GoBackToManageUsersMenue();
        break;
    }
    case enManageUsersOptions::eBackMainMenue:
    {
        ShowMainMenue();
    }
    }
}

void ShowManageUserScreen()
{

    if (!CheckUserPermissions(enPermissions::eManage))
    {
        PrintAccessDeniedScreen();
        GoBackToMainMenue();
        return;
    }

    system("cls");
    cout << "===========================================\n";
    cout << "\t\tManage Users Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] List Users.\n";
    cout << "\t[2] Add New User.\n";
    cout << "\t[3] Delete User.\n";
    cout << "\t[4] Update User.\n";
    cout << "\t[5] Find User.\n";
    cout << "\t[6] Main Menue.\n";
    cout << "===========================================\n";

    PerformManageUsersOption((enManageUsersOptions)ReadManageUsersMenueOption());
}

void PerfromMainMenueOption(enMainMenueOptions MainMenueOption)
{
    switch (MainMenueOption)
    {
    case enMainMenueOptions::eListClients:
    {
        system("cls");
        ShowAllClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eAddNewClient:
    {
        system("cls");
        ShowAddNewClientsScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eDeleteClient:
    {
        system("cls");
        ShowDeleteClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eUpdateClient:
    {
        system("cls");
        ShowUpdateClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eFindClient:
    {
        system("cls");
        ShowFindClientScreen();
        GoBackToMainMenue();
        break;
    }
    case enMainMenueOptions::eTransactions:
    {
        system("cls");
        ShowTransationsScreen();
        break;
    }
    case enMainMenueOptions::eManageUsers:
    {
        system("cls");
        ShowManageUserScreen();
        break;
    }
    case enMainMenueOptions::eLogout:
    {
        Login();
        break;
    }
    }
}

void ShowMainMenue()
{
    system("cls");
    cout << "===========================================\n";
    cout << "\t\tMain Menue Screen\n";
    cout << "===========================================\n";
    cout << "\t[1] Show Client List.\n";
    cout << "\t[2] Add New Client.\n";
    cout << "\t[3] Delete Client.\n";
    cout << "\t[4] Update Client Info.\n";
    cout << "\t[5] Find Client.\n";
    cout << "\t[6] Transactions.\n";
    cout << "\t[7] Manage Users.\n";
    cout << "\t[8] Logout.\n";
    cout << "===========================================\n";
    PerfromMainMenueOption((enMainMenueOptions)ReadMainMenueOption());
}

bool LoadUserInfo(string Username, string Password)
{
    return FindUserByUsernameAndPassword(Username, Password, CurrentUser) ? true : false;
}

void Login()
{

    bool LoginFailed = false;
    string Username, Password;

    do
    {
        system("cls");
        cout << "\n-----------------------------------\n";
        cout << "\tLogin Screen";
        cout << "\n-----------------------------------\n";

        if (LoginFailed)
        {
            cout << "\nInvalid Username/Password!\n";
        }

        cout << "\nEnter Username? ";
        cin >> Username;
        cout << "Enter Password? ";
        cin >> Password;

        LoginFailed = !LoadUserInfo(Username, Password);

    } while (LoginFailed);

    ShowMainMenue();
}

int main()
{
    Login();
    system("pause>0");
    return 0;
}
