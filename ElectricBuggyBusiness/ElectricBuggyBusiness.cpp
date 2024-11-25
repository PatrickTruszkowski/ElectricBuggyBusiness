#include <sstream>
#include <map>
#include <algorithm>

#include "Customer.h"

using namespace std;

void InitializeMaps();
void Introduce();
void HandleDataSelection();
bool CheckDataFile(const string&);
void LoadDataFile(const string&);
void SaveAllCustomerData();
void DisplayMainMenu();
void HandleMainMenuSelection();
void DisplayCustomerMenu();
void DisplayCityStateMenu();
Customer* HandleCustomerSelection();
void DisplayAllCustomerData();
void AddNewCustomerData();
void AddNewPurchase(Customer*);
string GetValidName(bool);
string GetValidStreetAddress();
string GetValidZipcode();
string GetValidPhoneNumber();
string GetValidDate();
bool IsLeapYear(int);
int DaysInMonth(int, int);
int GetValidChoice(int, int, bool = true);
bool FinalizeChoice(const string&);

const string DEFAULT_DATA_FILE_NAME = "DefaultData.txt";
const string SAVED_DATA_FILE_NAME = "SavedData.txt";

vector<Customer> customerVector;
map<string, float> itemMap;
map<int, string> cityStateMap;
bool isRunning;

int main()
{
    srand(time(0));
    cout << fixed << setprecision(2);

    InitializeMaps();
    Introduce();

    system("CLS");

    isRunning = true;

    while (isRunning)
    {
        DisplayMainMenu();
        HandleMainMenuSelection();
    }

    return 0;
}

void InitializeMaps()
{
    itemMap["Gordon Buggy"] = 15000.00;
    itemMap["Electric Motor"] = 3000.00;
    itemMap["Brakes"] = 500.00;
    itemMap["Tires"] = 1000.00;
    itemMap["Shocks"] = 250.00;
    itemMap["Rims"] = 400.00;
    itemMap["Lights"] = 70.00;

    cityStateMap[1] = "Portland, Maine";
    cityStateMap[2] = "Concord, New Hampshire";
    cityStateMap[3] = "Boston, Massachusetts";
    cityStateMap[4] = "Providence, Rhode Island";
    cityStateMap[5] = "Hartford, Connecticut";
    cityStateMap[6] = "New York City, New York";
    cityStateMap[7] = "Newark, New Jersey";
    cityStateMap[8] = "Wilmington, Delaware";
    cityStateMap[9] = "Baltimore, Maryland";
    cityStateMap[10] = "Virginia Beach, Virginia";
    cityStateMap[11] = "Charlotte, North Carolina";
    cityStateMap[12] = "Charleston, South Carolina";
    cityStateMap[13] = "Atlanta, Georgia";
    cityStateMap[14] = "Miami, Florida";
}

void Introduce()
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Welcome to Gordon Industries.\n";
    cout << "We sell fully built electric Gordon Buggies or parts for electric buggies in the US.\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    system("Pause");

    HandleDataSelection();
}

void HandleDataSelection()
{
    bool hasDefaultData = CheckDataFile(DEFAULT_DATA_FILE_NAME);
    bool hasSavedData = CheckDataFile(SAVED_DATA_FILE_NAME);
    int choice;

    if (!hasDefaultData && !hasSavedData)
    {
        return;
    }

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Would you like to load customer data?\n\n";

    if (hasDefaultData && hasSavedData)
    {
        cout << "(1)\tDefault Data\n";
        cout << "(2)\tSaved Data\n";
        cout << "(3)\tNone\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        choice = GetValidChoice(1, 3);

        if (choice == 1)
        {
            LoadDataFile(DEFAULT_DATA_FILE_NAME);
        }
        else if (choice == 2)
        {
            LoadDataFile(SAVED_DATA_FILE_NAME);
        }
        else
        {
            return;
        }
    }
    else if (hasDefaultData)
    {
        cout << "(1)\tDefault Data\n";
        cout << "(2)\tNone\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        choice = GetValidChoice(1, 2);

        if (choice == 1)
        {
            LoadDataFile(DEFAULT_DATA_FILE_NAME);
        }
        else
        {
            return;
        }
    }
    else if (hasSavedData)
    {
        cout << "(1)\tSaved Data\n";
        cout << "(2)\tNone\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        choice = GetValidChoice(1, 2);

        if (choice == 1)
        {
            LoadDataFile(SAVED_DATA_FILE_NAME);
        }
        else
        {
            return;
        }
    }

    system("Pause");
}

bool CheckDataFile(const string& fileName)
{
    ifstream inputFile;

    inputFile.open(fileName);

    if (!inputFile)
    {
        inputFile.close();

        return false;
    }

    inputFile.seekg(0, ios::end);

    size_t fileSize = inputFile.tellg();

    inputFile.seekg(0, ios::beg);

    if (fileSize == 0)
    {
        inputFile.close();

        return false;
    }

    return true;
}

void LoadDataFile(const string& fileName)
{
    ifstream inputFile;

    inputFile.open(fileName);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Loading...\n\n";

    vector<Purchase> purchaseVector;
    string startingName;

    while (!inputFile.eof())
    {
        bool isPruchase = true;

        while (isPruchase)
        {
            isPruchase = false;

            getline(inputFile, startingName, '+');

            if (!(itemMap.find(startingName) == itemMap.end()))
            {
                isPruchase = true;

                string date;

                getline(inputFile, date, '+');

                purchaseVector.emplace_back(startingName, date, itemMap[startingName]);
            }
        }

        string lastName;
        string streetAddress;
        string cityState;
        string zipcode;
        string phoneNumber;

        getline(inputFile, lastName, '+');
        getline(inputFile, streetAddress, '+');
        getline(inputFile, cityState, '+');
        getline(inputFile, zipcode, '+');
        getline(inputFile, phoneNumber, '+');

        Customer customer(startingName, lastName, streetAddress, cityState, zipcode, phoneNumber);

        if (!purchaseVector.empty())
        {
            for (Purchase& purchase : purchaseVector)
            {
                customer.AddPurchase(purchase.GetItemName(), purchase.GetPurchaseDate(), purchase.GetItemCost());
            }

            purchaseVector.clear();
        }

        customerVector.push_back(customer);
    }

    inputFile.close();

    cout << "Data successfully loaded!\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void SaveAllCustomerData()
{
    ofstream outputFile;

    outputFile.open(SAVED_DATA_FILE_NAME);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Saving...\n\n";

    for (Customer& customer : customerVector)
    {
        customer.SaveData(outputFile);

        if (!(customer == customerVector.at(customerVector.size() - 1)))
        {
            outputFile << "+";
        }
    }

    outputFile.close();

    cout << "All customer data successfully saved!\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void DisplayMainMenu()
{
    cout << "Main Menu\n";
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select a menu option:\n\n";
    cout << "(1)\tDisplay All Customer Data\n";
    cout << "(2)\tDisplay Specific Customer Data\n";
    cout << "(3)\tDisplay All Purchases For Customer\n";
    cout << "(4)\tAdd New Customer Data\n";
    cout << "(5)\tAdd New Purchase\n";
    cout << "(6)\tSave All Customer Data\n";
    cout << "(7)\tLoad Saved Customer Data\n";
    cout << "(8)\tRemove All Customer Data\n";
    cout << "(9)\tExit\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void HandleMainMenuSelection()
{
    int choice = GetValidChoice(1, 9);

    switch (choice)
    {
    case 1:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }
        else
        {
            DisplayAllCustomerData();

            system("Pause");
        }

        system("CLS");

        break;
    case 2:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }
        else
        {
            cout << "View Customer's Data\n";

            DisplayCustomerMenu();
            HandleCustomerSelection()->DisplayData();

            system("Pause");
        }

        system("CLS");

        break;
    case 3:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }
        else
        {
            cout << "View All Customer's Purchases\n";

            DisplayCustomerMenu();
            HandleCustomerSelection()->DisplayAllPurchases();

            system("Pause");
        }

        system("CLS");

        break;
    case 4:

        system("CLS");

        AddNewCustomerData();

        system("Pause");

        system("CLS");

        break;
    case 5:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }
        else
        {
            cout << "Add Purchase To Customer\n";

            DisplayCustomerMenu();
            AddNewPurchase(HandleCustomerSelection());

            system("Pause");
        }

        system("CLS");

        break;
    case 6:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }
        else
        {
            SaveAllCustomerData();

            system("Pause");
        }

        system("CLS");

        break;
    case 7:

        system("CLS");

        if (CheckDataFile(SAVED_DATA_FILE_NAME))
        {
            if (customerVector.empty())
            {
                LoadDataFile(SAVED_DATA_FILE_NAME);

                system("Pause");
            }
            else
            {
                if (FinalizeChoice("Loading saved data will override current data. Are you sure you want to proceed?"))
                {
                    customerVector.clear();

                    LoadDataFile(SAVED_DATA_FILE_NAME);

                    system("Pause");
                }
            }
        }
        else
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There is no saved data.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }

        system("CLS");

        break;
    case 8:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }
        else
        {
            if (FinalizeChoice("Are you sure you want to remove all customer data?"))
            {
                cout << "________________________________________________________________________________________________________________________________\n";
                cout << "Removing all customer data...\n\n";

                customerVector.clear();

                cout << "All customer data successfully removed!\n";
                cout << "________________________________________________________________________________________________________________________________\n\n";

                system("Pause");
            }
        }

        system("CLS");

        break;
    case 9:

        isRunning = false;

        break;
    }
}

void DisplayCustomerMenu()
{
    int count = 1;

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select a customer:\n\n";

    for (const Customer& customer : customerVector)
    {
        cout << "(" << count << ")\t" << customer.GetFirstName() << " " << customer.GetLastName() << "\n";

        count++;
    }

    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void DisplayCityStateMenu()
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select customer's city and state: ";

    cout << "\n\n";

    for (const auto& pair : cityStateMap)
    {
        cout << "(" << pair.first << ")\t" << pair.second << "\n";
    }
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

Customer* HandleCustomerSelection()
{
    int choice = GetValidChoice(1, customerVector.size());

    return &customerVector.at(choice - 1);
}

void DisplayAllCustomerData()
{
    cout << "All Customers (" << customerVector.size() << ")\n";

    for (const Customer& customer : customerVector)
    {
        customer.DisplayData();
    }
}

void AddNewCustomerData()
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Add new customer data:\n\n";

    string firstName;
    string lastName;
    string streetAddress;
    string cityState;
    string zipcode;
    string phoneNumber;

    firstName = GetValidName(true);
    lastName = GetValidName(false);

    if (!customerVector.empty())
    {
        for (const Customer& customer : customerVector)
        {
            if (firstName == customer.GetFirstName() && lastName == customer.GetLastName())
            {
                cout << "\nCustomer already exists.\n\n";

                return;
            }
        }
    }

    DisplayCityStateMenu();
    int choice = GetValidChoice(1, 14);

    cityState = cityStateMap[choice];

    cout << "\n";

    streetAddress = GetValidStreetAddress();
    zipcode = GetValidZipcode();
    phoneNumber = GetValidPhoneNumber();
    
    customerVector.emplace_back(firstName, lastName, streetAddress, cityState, zipcode, phoneNumber);

    cout << "\nCustomer data successfully added!\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    customerVector.at(customerVector.size() - 1).DisplayData();
}

void AddNewPurchase(Customer* customerPtr)
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select an item:\n\n";

    int count = 1;

    for (const auto& pair : itemMap)
    {
        cout << "(" << count << ")\t" << pair.first << ", $" << pair.second << "\n";

        count++;
    }

    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, itemMap.size());

    count = 1;

    string itemName;
    float cost = 0.00;

    for (const auto& pair : itemMap)
    {
        if (count == choice)
        {
            itemName = pair.first;
            cost = pair.second;

            break;
        }

        count++;
    }

    string date = GetValidDate();

    customerPtr->AddPurchase(itemName, date, cost);

    cout << "\nPurchase of " << itemName << ", $" << cost << " was added to customer " << customerPtr->GetFirstName() << " " << customerPtr->GetLastName() << ".\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

string GetValidName(bool isFirst)
{
    string name;
    bool valid = false;

    do
    {
        if (isFirst)
        {
            cout << "Enter customer's first name: ";
        }
        else
        {
            cout << "Enter customer's last name: ";
        }
        getline(cin, name);

        valid = !name.empty() && none_of(name.begin(), name.end(), ::isdigit);

        if (name.empty())
        {
            cout << "Customer's name cannot blank.\n\n";
        }
        else
        {
            if (!valid)
            {
                cout << "Customer's name cannot be or contain numbers.\n\n";
            }
        }

    } while (!valid);

    return name;
}

string GetValidStreetAddress()
{
    string streetAddress;

    do
    {
        cout << "Enter customer's street address: ";
        getline(cin, streetAddress);

        if (streetAddress.empty())
        {
            cout << "Address cannot be blank.\n";
        }

    } while (streetAddress.empty());

    return streetAddress;
}

string GetValidZipcode()
{
    string zipcode;
    bool valid = false;

    do
    {
        cout << "Enter customer's zipcode (5 Digits): ";
        getline(cin, zipcode);

        // Check if all characters in the string are digits.
        valid = !zipcode.empty() && all_of(zipcode.begin(), zipcode.end(), ::isdigit) && zipcode.length() == 5;

        if (!valid)
        {
            cout << "Zipcode must be 5 digits.\n";
        }

    } while (!valid);

    return zipcode;
}

string GetValidPhoneNumber()
{
    string phoneNumber;
    bool valid = false;

    do
    {
        cout << "Enter customer's phone number (Only Numbers, 10 Digits): ";
        getline(cin, phoneNumber);

        valid = !phoneNumber.empty() && all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit) && phoneNumber.length() == 10;

        if (!valid)
        {
            cout << "Phone number must be 10 digits.\n";
        }

    } while (!valid);

    for (size_t index = 0; index < phoneNumber.size(); index++)
    {
        if (index == 3 || index == 7)
        {
            phoneNumber.insert(index, 1, '-');
        }
    }

    return phoneNumber;
}

string GetValidDate()
{
    string date;
    bool valid = false;

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select a month:\n\n";
    cout << "(1)\tJanuary\n";
    cout << "(2)\tFebruary\n";
    cout << "(3)\tMarch\n";
    cout << "(4)\tApril\n";
    cout << "(5)\tMay\n";
    cout << "(6)\tJune\n";
    cout << "(7)\tJuly\n";
    cout << "(8)\tAugust\n";
    cout << "(9)\tSeptember\n";
    cout << "(10)\tOctober\n";
    cout << "(11)\tNovember\n";
    cout << "(12)\tDecember\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int month = GetValidChoice(1, 12);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select a year:\n\n";
    cout << "(1)\t2019\n";
    cout << "(2)\t2020\n";
    cout << "(3)\t2021\n";
    cout << "(4)\t2022\n";
    cout << "(5)\t2023\n";
    cout << "(6)\t2024\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, 6);
    int year = 2019 + (choice - 1);

    int daysInMonth = DaysInMonth(month, year);
    int day;

    cout << "\nEnter day (1 - " << daysInMonth << "): ";
    day = GetValidChoice(1, daysInMonth, false);

    date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

    return date;
}

bool IsLeapYear(int year)
{
    if (year % 4 == 0)
    {
        if (year % 100 == 0)
        {
            if (year % 400 == 0)
            {
                return true;
            }

            return false;
        }

        return true;
    }

    return false;
}

int DaysInMonth(int month, int year)
{
    switch (month)
    {
    case 1:
    case 3:
    case 5:
    case 7:
    case 8:
    case 10:
    case 12:
        return 31;
    case 4:
    case 6:
    case 9:
    case 11:
        return 30;
    case 2:
        if (IsLeapYear(year))
        {
            return 29;
        }
        else
        {
            return 28;
        }
    }
}

int GetValidChoice(int minimum, int maximum, bool prompt)
{
    int choice;
	string choiceInput;
    bool valid;

    do
    {
        valid = false;

        if (prompt)
        {
            cout << "Input: ";
        }

        getline(cin, choiceInput);

        stringstream stringStream(choiceInput);

        if (stringStream >> choice)
        {
            if (stringStream.eof())
            {
                if (choice < minimum || choice > maximum)
                {
                    valid = false;

                    cout << "Please enter a number between " << minimum << " and " << maximum << ".\n\n";
                }
                else
                {
                    valid = true;
                }
            }
            else
            {
                valid = false;

                cout << "Please enter a menu option number.\n\n";
            }
        }
        else
        {
            valid = false;

            cout << "Please enter a menu option number.\n\n";
        }

    } while (!valid);

    return choice;
}

bool FinalizeChoice(const string& confirmationText)
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "! " << confirmationText << " !\n\n";
    cout << "(1)\tNo\n";
    cout << "(2)\tYes\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, 2);

    if (choice == 1)
    {
        return false;
    }

    return true;
}