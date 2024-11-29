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
void HandleCustomerSorting();
void SortCustomerVector();
Customer* HandleCustomerSelection();
void DisplayAllCustomerData();
void AddNewCustomerData();
void AddNewCustomersData();
void UpdateCustomerData(Customer*);
void AddNewPurchase(Customer*);
void AddNewPurchases(Customer*);
void RemoveCustomer(Customer*);
string GetValidName(bool);
string GetValidStreetAddress();
string GetValidZipcode();
string GetValidPhoneNumber();
string GetValidDate();
bool IsLeapYear(int);
int DaysInMonth(int, int);
int GetValidChoice(int, int, bool = true);
bool FinalizeChoice(const string&);

// Store constants to avoid typos.
const string DEFAULT_DATA_FILE_NAME = "DefaultData.txt";
const string SAVED_DATA_FILE_NAME = "SavedData.txt";

vector<Customer> customerVector;    // Stores all customers.
map<string, float> itemMap;         // Stores all key value pairs of the items for sale.
map<int, string> cityStateMap;      // Stores all key value pairs of the states and cities.
int sortingChoice = 0;              // Stores sorting option.
int sortingOrder = 0;               // Stores sorting order.
bool isRunning;                     // Program running flag.

int main()
{
    // Seed the time for generating random account numbers and set precision to two decimal points for money.
    srand(time(0));
    cout << fixed << setprecision(2);

    // Initialize maps with key value pairs and run intro sequence.
    InitializeMaps();
    Introduce();

    system("CLS");

    // Start running.
    isRunning = true;

    // Run while running flag is true.
    while (isRunning)
    {
        DisplayMainMenu();
        HandleMainMenuSelection();

        // Sort the customers after every update.
        if (!(customerVector.empty() || sortingChoice == 0))
        {
            SortCustomerVector();
        }
    }

    return 0;
}

void InitializeMaps()
{
    // Set key value pairs.
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
    // Introduce the business.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Welcome to Gordon Industries.\n";
    cout << "We sell fully built electric Gordon Buggies or parts for electric buggies in the east of the US.\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    system("Pause");

    // Let user choose what data to load if any.
    HandleDataSelection();
}

void HandleDataSelection()
{
    // Check if default and saved files exist.
    bool hasDefaultData = CheckDataFile(DEFAULT_DATA_FILE_NAME);
    bool hasSavedData = CheckDataFile(SAVED_DATA_FILE_NAME);
    int choice;

    // Continue to main program if there are no files to select.
    if (!hasDefaultData && !hasSavedData)
    {
        return;
    }

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Would you like to load customer data?\n\n";

    // Display option to load default data, saved data, or none if both files exist.
    if (hasDefaultData && hasSavedData)
    {
        cout << "(1)\tDefault Data\n";
        cout << "(2)\tSaved Data\n";
        cout << "(3)\tNone\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        choice = GetValidChoice(1, 3);

        // Handle which file to load.
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
    else if (hasDefaultData) // Display option to load default data or not if only default file exists.
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
    else if (hasSavedData) // Display option to load saved data or not if only saved file exists.
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

    // Try opening file, if can't open, close and return false.
    if (!inputFile)
    {
        inputFile.close();

        return false;
    }

    // Check if the file is empty.
    inputFile.seekg(0, ios::end);

    size_t fileSize = inputFile.tellg();

    inputFile.seekg(0, ios::beg);

    // If file is empty, close it and return false.
    if (fileSize == 0)
    {
        inputFile.close();

        return false;
    }

    // If all checks pass, return true saying the file exists and contain data.
    return true;
}

void LoadDataFile(const string& fileName)
{
    ifstream inputFile;

    inputFile.open(fileName);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Loading...\n\n";

    // Make temporary purchase vector to load from data file.
    vector<Purchase> purchaseVector;
    string startingName;

    // While we are not at the end of the file.
    while (!inputFile.eof())
    {
        bool isPruchase = true;

        // While the data is a purchase.
        while (isPruchase)
        {
            isPruchase = false;

            getline(inputFile, startingName, '+');

            // If the value of the first string is found in the item map, data line is a purchase, continue to read in as a purchase object.
            if (!(itemMap.find(startingName) == itemMap.end()))
            {
                isPruchase = true;

                string date;

                getline(inputFile, date, '+');

                purchaseVector.emplace_back(startingName, date, itemMap[startingName]);
            }
        }

        // If the first string is not found in the item map, read in as customer data line.
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

        // If the purchase vector has purchases, add it to the current customer.
        if (!purchaseVector.empty())
        {
            for (Purchase& purchase : purchaseVector)
            {
                customer.AddPurchase(purchase.GetItemName(), purchase.GetPurchaseDate(), purchase.GetItemCost());
            }

            // Clear purchase vector to get it ready for next data line.
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

    // Cycle through each customer and tell it to save its data.
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
    // Display all main menu options.
    cout << "Main Menu\tCustomers (" << customerVector.size() << ")\n";
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select a menu option:\n\n";

    cout << "View Customer Data\n";
    cout << "(1)\tDisplay All Customer Data\n";
    cout << "(2)\tDisplay Specific Customer Data\n";
    cout << "(3)\tDisplay All Purchases For Customer\n\n";

    cout << "Add New Data\n";

    // Show star next to adding customer when no customers exist.
    if (customerVector.empty())
    {
        cout << "(4)*\tAdd New Customer Data\n";
    }
    else
    {
        cout << "(4)\tAdd New Customer Data\n";
    }

    cout << "(5)\tAdd New Purchases\n\n";

    cout << "Organization\n";
    cout << "(6)\tSort Customer Data\n";
    cout << "(7)\tUpdate Customer Data\n";
    cout << "(8)\tSave All Customer Data\n";
    cout << "(9)\tLoad Saved Customer Data\n";
    cout << "(10)\tRemove Customer Data\n";
    cout << "(11)\tRemove All Customer Data\n\n\n";

    cout << "(12)\tExit\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void HandleMainMenuSelection()
{
    // Get a choice in range.
    int choice = GetValidChoice(1, 12);

    // Call corresponding menu option.
    switch (choice)
    {
    case 1: // Display all customer data.

        system("CLS");

        // Check if no customers exist.
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
    case 2: // Display specific customer data.

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
    case 3: // Display all purchases for a customer.

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
    case 4: // Add new customer data.

        system("CLS");

        AddNewCustomersData();

        system("CLS");

        break;
    case 5: // Add new purchases.

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
            cout << "Add Purchases To Customer\n";

            DisplayCustomerMenu();
            AddNewPurchases(HandleCustomerSelection());
        }

        system("CLS");

        break;
    case 6: // Sorting options for customers.

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
            cout << "Customer Sorting Options\n";

            HandleCustomerSorting();

            system("Pause");
        }

        system("CLS");

        break;
    case 7: // Update customer data.

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
            cout << "Update Customer's Data\n";

            DisplayCustomerMenu();
            UpdateCustomerData(HandleCustomerSelection());

            system("Pause");
        }

        system("CLS");

        break;
    case 8: // Save all customer data.

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
    case 9: // Load customer data.

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
    case 10: // Remove customer.

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
            cout << "Remove Customer Data\n";

            DisplayCustomerMenu();
            RemoveCustomer(HandleCustomerSelection());
        }

        system("CLS");

        break;
    case 11: // Remove all customer data.

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
    case 12: // Exit.

        isRunning = false;

        break;
    }
}

void DisplayCustomerMenu()
{
    int count = 1;

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select a customer:\n\n";

    // Cycle and number each customer.
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

    // Display all cities and states.
    for (const auto& pair : cityStateMap)
    {
        cout << "(" << pair.first << ")\t" << pair.second << "\n";
    }
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void HandleCustomerSorting()
{
    // Display sorting base menu.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select sorting base:\n\n";
    cout << "(1)\tAccount Number\n";
    cout << "(2)\tPurchase Count\n";
    cout << "(3)\tTotal Spendings\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    sortingChoice = GetValidChoice(1, 3);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select an order:\n\n";
    cout << "(1)\tAsceding\n";
    cout << "(2)\tDescending\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    sortingOrder = GetValidChoice(1, 2);

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Sorting...\n\n";

    // Bubble sort customers.
    SortCustomerVector();

    cout << "Sorting complete!\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void SortCustomerVector()
{
    // Bubble sort based on sorting choice.
    switch (sortingChoice)
    {
    case 1: // Sort based on account number.

        // Sort in ascending order.
        if (sortingOrder == 1)
        {
            for (unsigned int i = 0; i < customerVector.size(); ++i)
            {
                for (unsigned int j = 0; j < customerVector.size() - 1; ++j)
                {
                    if (customerVector.at(j).GetAccountNumber() > customerVector.at(j + 1).GetAccountNumber())
                    {
                        Customer smallerCustomer = customerVector.at(j + 1);

                        customerVector.at(j + 1) = customerVector.at(j);
                        customerVector.at(j) = smallerCustomer;
                    }
                }
            }
        }
        else // Sort in descending order.
        {
            for (unsigned int i = 0; i < customerVector.size(); ++i)
            {
                for (unsigned int j = 0; j < customerVector.size() - 1; ++j)
                {
                    if (customerVector.at(j).GetAccountNumber() < customerVector.at(j + 1).GetAccountNumber())
                    {
                        Customer biggerCustomer = customerVector.at(j + 1);

                        customerVector.at(j + 1) = customerVector.at(j);
                        customerVector.at(j) = biggerCustomer;
                    }
                }
            }
        }

        break;
    case 2: // Sort based on purchase count.

        if (sortingOrder == 1)
        {
            for (unsigned int i = 0; i < customerVector.size(); ++i)
            {
                for (unsigned int j = 0; j < customerVector.size() - 1; ++j)
                {
                    if (customerVector.at(j).GetPurchaseCount() > customerVector.at(j + 1).GetPurchaseCount())
                    {
                        Customer smallerCustomer = customerVector.at(j + 1);

                        customerVector.at(j + 1) = customerVector.at(j);
                        customerVector.at(j) = smallerCustomer;
                    }
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < customerVector.size(); ++i)
            {
                for (unsigned int j = 0; j < customerVector.size() - 1; ++j)
                {
                    if (customerVector.at(j).GetPurchaseCount() < customerVector.at(j + 1).GetPurchaseCount())
                    {
                        Customer biggerCustomer = customerVector.at(j + 1);

                        customerVector.at(j + 1) = customerVector.at(j);
                        customerVector.at(j) = biggerCustomer;
                    }
                }
            }
        }

        break;
    case 3: // Sort based on total spendings.

        if (sortingOrder == 1)
        {
            for (unsigned int i = 0; i < customerVector.size(); ++i)
            {
                for (unsigned int j = 0; j < customerVector.size() - 1; ++j)
                {
                    if (customerVector.at(j).GetTotalSpending() > customerVector.at(j + 1).GetTotalSpending())
                    {
                        Customer smallerCustomer = customerVector.at(j + 1);

                        customerVector.at(j + 1) = customerVector.at(j);
                        customerVector.at(j) = smallerCustomer;
                    }
                }
            }
        }
        else
        {
            for (unsigned int i = 0; i < customerVector.size(); ++i)
            {
                for (unsigned int j = 0; j < customerVector.size() - 1; ++j)
                {
                    if (customerVector.at(j).GetTotalSpending() < customerVector.at(j + 1).GetTotalSpending())
                    {
                        Customer biggerCustomer = customerVector.at(j + 1);

                        customerVector.at(j + 1) = customerVector.at(j);
                        customerVector.at(j) = biggerCustomer;
                    }
                }
            }
        }

        break;
    }
}

Customer* HandleCustomerSelection()
{
    int choice = GetValidChoice(1, customerVector.size());

    // Return the memory address of the selected customer.
    return &customerVector.at(choice - 1);
}

void DisplayAllCustomerData()
{
    // Display customer count and current sorting option.
    cout << "All Customers (" << customerVector.size() << ")\tSorting: ";

    if (sortingChoice != 0)
    {
        if (sortingOrder == 1)
        {
            cout << "Ascending ";
        }
        else
        {
            cout << "Descending ";
        }

        switch (sortingChoice)
        {
        case 1:

            cout << "Account Number\n";

            break;
        case 2:

            cout << "Purchase Count\n";

            break;
        case 3:

            cout << "Total Spendings\n";

            break;
        }
    }
    else
    {
        cout << "Unsorted\n";
    }

    // Display each customers data.
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

    // Check if this customer already exists in the database.
    if (!customerVector.empty())
    {
        for (const Customer& customer : customerVector)
        {
            // Return to main menu if the user is trying to add the same customer.
            if (firstName == customer.GetFirstName() && lastName == customer.GetLastName())
            {
                cout << "\nCustomer already exists.\n\n";

                return;
            }
        }
    }

    // Get the city and state selected.
    DisplayCityStateMenu();
    int choice = GetValidChoice(1, 14);

    cityState = cityStateMap[choice];

    cout << "\n";

    // Get valid data for each.
    streetAddress = GetValidStreetAddress();
    zipcode = GetValidZipcode();
    phoneNumber = GetValidPhoneNumber();
    
    // Construct new customer in the customer vector.
    customerVector.emplace(customerVector.begin(), firstName, lastName, streetAddress, cityState, zipcode, phoneNumber);

    cout << "\nCustomer data successfully added!\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    // Display newly added customer.
    customerVector.at(0).DisplayData();
}

void AddNewCustomersData()
{
    // Add new customer.
    AddNewCustomerData();

    // Prompt user if they want to add another customer.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Add another customer?:\n\n";
    cout << "(1)\tYes\n";
    cout << "(2)\tNo\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, 2);

    if (choice == 1)
    {
        system("CLS");

        // Call function recursively.
        AddNewCustomersData();
    }
}

void UpdateCustomerData(Customer* customerPtr)
{
    // Show selected customer's data.
    customerPtr->DisplayData();

    // Prompt which data to update.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select customer data:\n\n";
    cout << "(1)\tFirst Name\n";
    cout << "(2)\tLast Name\n";
    cout << "(3)\tStreet Address\n";
    cout << "(4)\tCity & State\n";
    cout << "(5)\tZipcode\n";
    cout << "(6)\tPhone Number\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, 6);

    switch (choice)
    {
    case 1: // Update first name.

        cout << "________________________________________________________________________________________________________________________________\n";

        customerPtr->SetFirstName(GetValidName(true));

        cout << "\nCustomer's first name was changed to " << customerPtr->GetFirstName() << ".\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        break;
    case 2: // Update last name.

        cout << "________________________________________________________________________________________________________________________________\n";

        customerPtr->SetLastName(GetValidName(false));

        cout << "\nCustomer's last name was changed to " << customerPtr->GetLastName() << ".\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        break;
    case 3: // Update street address.

        cout << "________________________________________________________________________________________________________________________________\n";

        customerPtr->SetStreetAddress(GetValidStreetAddress());

        cout << "\nCustomer's street address was changed to " << customerPtr->GetStreetAddress() << ".\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        break;
    case 4: // Update city & state.

        DisplayCityStateMenu();
        customerPtr->SetCityState(cityStateMap[GetValidChoice(1, 14)]);

        cout << "\nCustomer's city and state was changed to " << customerPtr->GetCityState() << ".\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        break;
    case 5: // Update zipcode.

        cout << "\n________________________________________________________________________________________________________________________________\n";

        customerPtr->SetZipcode(GetValidZipcode());

        cout << "\nCustomer's zipcode was changed to " << customerPtr->GetZipcode() << ".\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        break;
    case 6: // Update phone number.

        cout << "________________________________________________________________________________________________________________________________\n";

        customerPtr->SetPhoneNumber(GetValidPhoneNumber());

        cout << "\nCustomer's phone number was changed to " << customerPtr->GetPhoneNumber() << ".\n";
        cout << "________________________________________________________________________________________________________________________________\n\n";

        break;
    }
}

void AddNewPurchase(Customer* customerPtr)
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select an item:\n\n";

    int count = 1;

    // Display all items using map.
    for (const auto& pair : itemMap)
    {
        cout << "(" << count << ")\t" << setw(14) << pair.first << "|$" << pair.second << "\n";

        count++;
    }

    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, itemMap.size());

    count = 1;

    string itemName;
    float cost = 0.00;

    // Set corresponding key value pairs.
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

    // Add the purchase to the customer.
    customerPtr->AddPurchase(itemName, date, cost);

    cout << "\nPurchase of " << itemName << ", $" << cost << " was added to customer " << customerPtr->GetFirstName() << " " << customerPtr->GetLastName() << ".\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";
}

void AddNewPurchases(Customer* customerPtr)
{
    // Add new purchase.
    AddNewPurchase(customerPtr);

    // Prompt for input of another purchase.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Add another purchase?:\n\n";
    cout << "(1)\tYes\n";
    cout << "(2)\tNo\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice = GetValidChoice(1, 2);

    if (choice == 1)
    {
        system("CLS");

        // Call function recursively.
        AddNewPurchases(customerPtr);
    }
}

void RemoveCustomer(Customer* customerPtr)
{
    string customerName = customerPtr->GetFirstName() + " " + customerPtr->GetLastName();

    // Ensure the user really wants to continue with this action.
    if (!FinalizeChoice("Are you sure you want to remove " + customerName + "?"))
    {
        return;
    }

    // Cycle through the customer vector and remove the matching customer.
    for (Customer& customer : customerVector)
    {
        if (customer == *customerPtr)
        {
            customerVector.erase(remove(customerVector.begin(), customerVector.end(), customer), customerVector.end());

            cout << "\n" << customerName << "'s data successfully removed!\n";
            cout << "________________________________________________________________________________________________________________________________\n\n";

            system("Pause");

            return;
        }
    }
}

string GetValidName(bool isFirst)
{
    string name;
    bool valid = false;

    do
    {
        // Prompt user to enter the name.
        if (isFirst)
        {
            cout << "Enter customer's first name: ";
        }
        else
        {
            cout << "Enter customer's last name: ";
        }
        getline(cin, name);

        // Check if the input is not empty and if there are no digits in the name.
        valid = !name.empty() && none_of(name.begin(), name.end(), ::isdigit);

        // Tell user what's wrong.
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

    } while (!valid); // Repeat until it's valid.

    // Return the valid name.
    return name;
}

string GetValidStreetAddress()
{
    string streetAddress;

    do
    {
        cout << "Enter customer's street address: ";
        getline(cin, streetAddress);

        // Tell user what's wrong.
        if (streetAddress.empty())
        {
            cout << "Address cannot be blank.\n\n";
        }

    } while (streetAddress.empty()); // Repeat while the input is empty.

    // Return valid street address.
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

        // Check if the input is not empty, no characters, and is 5 numbers long.
        valid = !zipcode.empty() && all_of(zipcode.begin(), zipcode.end(), ::isdigit) && zipcode.length() == 5;

        // Tell user what's wrong.
        if (!valid)
        {
            cout << "Zipcode must be numbers and be 5 digits.\n\n";
        }

    } while (!valid);

    // Return valid zipcode.
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

        // Check if the input is not empty, no characters, and is 10 numbers long.
        valid = !phoneNumber.empty() && all_of(phoneNumber.begin(), phoneNumber.end(), ::isdigit) && phoneNumber.length() == 10;

        if (!valid)
        {
            cout << "Phone number must numbers and be 10 digits.\n\n";
        }

    } while (!valid);

    // Insert hyphens in proper places.
    for (size_t index = 0; index < phoneNumber.size(); index++)
    {
        if (index == 3 || index == 7)
        {
            phoneNumber.insert(index, 1, '-');
        }
    }

    // Return valid phone number.
    return phoneNumber;
}

string GetValidDate()
{
    string date;

    // Display all months.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select month of purchase:\n\n";
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

    // Display all possible purchase years.
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Select year of purchase:\n\n";
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

    // Prompt user to enter a valid day based on month and if it was a leap year.
    cout << "\nEnter day of purchase (1 - " << daysInMonth << "): ";
    day = GetValidChoice(1, daysInMonth, false);

    // Format date.
    date = to_string(month) + "/" + to_string(day) + "/" + to_string(year);

    // Return valid date.
    return date;
}

bool IsLeapYear(int year)
{
    // Determine if year is a leap year.
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
    // Determine how many days are in the month based on year.
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

        // Check if the input is within range, is numbers only, and is not empty.
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
    // Display confirmation.
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