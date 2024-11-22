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
void DisplayCustomerMenu();
Customer* HandleCustomerSelection();
void DisplayAllCustomerData();
int GetValidChoice(int, int);
bool FinalizeChoice(string);

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

                getline(inputFile, date, ',');

                purchaseVector.emplace_back(startingName, date, itemMap[startingName]);
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
    cout << "(2)\tDisplay All Purchases For Customer\n";
    cout << "(3)\tSave All Customer Data\n";
    cout << "(4)\tLoad Saved Customer Data\n";
    cout << "(5)\tRemove All Customer Data\n";
    cout << "(6)\tExit\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void HandleMainMenuSelection()
{
    int choice = GetValidChoice(1, 6);

    switch (choice)
    {
    case 1:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";
        }
        else
        {
            DisplayAllCustomerData();
        }

        system("Pause");
        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    case 2:

        system("CLS");

        if (customerVector.empty())
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";
        }
        else
        {
            DisplayCustomerMenu();
            HandleCustomerSelection()->DisplayAllPurchases();
        }

        system("Pause");
        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    case 3:

        system("CLS");

        SaveAllCustomerData();

        system("Pause");
        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    case 4:

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

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    case 5:

        system("CLS");

        if (!customerVector.empty())
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
        else
        {
            cout << "________________________________________________________________________________________________________________________________\n";
            cout << "There are no customers in the database.\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");
        }

        system("CLS");

        DisplayMainMenu();
        HandleMainMenuSelection();

        break;
    case 6:

        cout << "Exiting...\n\n";

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

Customer* HandleCustomerSelection()
{
    int choice = GetValidChoice(1, customerVector.size());

    return &customerVector.at(choice - 1);
}

void DisplayAllCustomerData()
{
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

bool FinalizeChoice(string confirmationText)
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