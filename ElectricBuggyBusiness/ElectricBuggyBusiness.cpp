#include <sstream>
#include <map>

#include "Customer.h"

using namespace std;

void InitializeItems();
void Introduce();
void HandleDataSelection();
bool CheckDataFile(string);
void LoadDataFile(string);
void SaveAllCustomerData();
void DisplayMainMenu();
void HandleMainMenuSelection();
void DisplayAllCustomerData();
int GetValidChoice(int, int);

const string DEFAULT_DATA_FILE_NAME = "DefaultData.txt";
const string SAVED_DATA_FILE_NAME = "SavedData.txt";

vector<Customer> customerVector;
map<string, float> itemMap;

int main()
{
    srand(time(0));
    cout << fixed << setprecision(2);

    InitializeItems();
    Introduce();

    system("Pause");
    system("CLS");

    DisplayMainMenu();
    HandleMainMenuSelection();

    return 0;
}

void InitializeItems()
{
    itemMap["Gordon Buggy"] = 15000.00;
    itemMap["Electric Motor"] = 3000.00;
    itemMap["Brakes"] = 500.00;
    itemMap["Tires"] = 1000.00;
    itemMap["Shocks"] = 250.00;
    itemMap["Rims"] = 400.00;
    itemMap["Lights"] = 70.00;
}

void Introduce()
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Welcome to Gordon Industries.\n";
    cout << "We sell fully built electric Gordon Buggies or parts for electric buggies.\n";
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
        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();
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
    }
}

bool CheckDataFile(string fileName)
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

void LoadDataFile(string fileName)
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

            getline(inputFile, startingName, ',');

            if (!(itemMap.find(startingName) == itemMap.end()))
            {
                isPruchase = true;

                string date;
                float cost;

                getline(inputFile, date, ',');

                cost = itemMap[startingName];

                purchaseVector.emplace_back(startingName, date, cost);
            }
        }

        string lastName;
        string streetAddress;
        string city;
        string state;
        string zipcode;
        string phoneNumber;

        getline(inputFile, lastName, ',');
        getline(inputFile, streetAddress, ',');
        getline(inputFile, city, ',');
        getline(inputFile, state, ',');
        getline(inputFile, zipcode, ',');
        getline(inputFile, phoneNumber, ',');

        Customer customer(startingName, lastName, streetAddress, city, state, zipcode, phoneNumber);

        if (!purchaseVector.empty())
        {
            for (Purchase& purchase : purchaseVector)
            {
                customer.AddPurchase(purchase);
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
    if (customerVector.empty())
    {
        cout << "________________________________________________________________________________________________________________________________\n";
        cout << "There are no customers in the database.\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        return;
    }

    ofstream outputFile;

    outputFile.open(SAVED_DATA_FILE_NAME);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Saving...\n\n";

    for (Customer& customer : customerVector)
    {
        customer.SaveData(outputFile);

        if (!(customer == customerVector.at(customerVector.size() - 1)))
        {
            outputFile << ",";
        }
    }

    outputFile.close();

    cout << "All customer data successfully saved!\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void DisplayMainMenu()
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "(1)\tDisplay All Customer Data\n";
    cout << "(2)\tSave All Customer Data\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void HandleMainMenuSelection()
{
    int choice = GetValidChoice(1, 2);

    switch (choice)
    {
    case 1:

        system("CLS");

        DisplayAllCustomerData();

        system("Pause");
        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    case 2:

        system("CLS");

        SaveAllCustomerData();

        system("Pause");
        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    }
}

void DisplayAllCustomerData()
{
    if (customerVector.empty())
    {
        cout << "________________________________________________________________________________________________________________________________\n";
        cout << "There are no customers in the database.\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        return;
    }

    for (const Customer& customer : customerVector)
    {
        customer.DisplayData();
    }
}

int GetValidChoice(int minimum, int maximum)
{
    int choice;
	string choiceInput;
    bool valid;

    do
    {
        valid = false;

        cout << "Input: ";

        getline(cin, choiceInput);

        stringstream stringStream(choiceInput);

        if (stringStream >> choice)
        {
            if (stringStream.eof())
            {
                if (choice < minimum || choice > maximum)
                {
                    valid = false;

                    cout << "Please enter a menu option number between " << minimum << " and " << maximum << ".\n\n";
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