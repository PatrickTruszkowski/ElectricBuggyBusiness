#include <iostream>
#include <sstream>

#include "Customer.h"

using namespace std;

void Introduce();
void LoadDataFile(string);
int GetValidChoice(int, int);

const string DEFAULT_DATA_FILE_NAME = "DefaultData.txt";
const string SAVED_DATA_FILE_NAME = "SavedData.txt";

vector<Customer> customerVector;

int main()
{
    srand(time(0));

    Introduce();

    system("Pause");
    system("CLS");

    return 0;
}

void Introduce()
{
    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Welcome to Gordon Industries.\n";
    cout << "We sell fully built electric Gordon Buggies or parts for electric buggies.\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    system("Pause");

    cout << "________________________________________________________________________________________________________________________________\n";
    cout << "Would you like to load default customer data or saved customer data?\n\n";
    cout << "(1)\tDefault\n";
    cout << "(2)\tSaved\n";
    cout << "________________________________________________________________________________________________________________________________\n\n";

    int choice;

    choice = GetValidChoice(1, 2);

    if (choice == 1)
    {
        LoadDataFile(DEFAULT_DATA_FILE_NAME);
    }
    else
    {
        LoadDataFile(SAVED_DATA_FILE_NAME);
    }
}

void LoadDataFile(string fileName)
{
    cout << "LoadDataFile(" << fileName << ")\n";
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