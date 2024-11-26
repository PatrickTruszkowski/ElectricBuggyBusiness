#include "Customer.h"

// Declare customer account number vector.
vector<int> Customer::customerAccountNumberVector;

Customer::Customer(const string& firstName, const string& lastName, const string& streetAddress, const string& cityState, const string& zipcode, const string& phoneNumber)
{
	// Set the private member variables.
	this->firstName = firstName;
	this->lastName = lastName;
	this->streetAddress = streetAddress;
	this->cityState = cityState;
	this->zipcode = zipcode;
	this->phoneNumber = phoneNumber;

	// Initialize total customer spendings to $0.00.
	totalSpendings = 0.00;

	// Generate random account number.
	accountNumber = rand() % 9999 + 1;

	// Check if no other customers exist yet.
	if (!customerAccountNumberVector.empty())
	{
		bool valid = false;

		while (!valid)
		{
			// Cycle through every existing account number and check if it's already created.
			for (int currentAccountNumber : customerAccountNumberVector)
			{
				// If the generated account number was found, generate another number and check again.
				if (currentAccountNumber == accountNumber)
				{
					valid = false;

					accountNumber = rand() % 9999 + 1;

					break;
				}

				valid = true;

				// Add new account number to the static vector.
				customerAccountNumberVector.emplace_back(accountNumber);
			}
		}
	}
}

bool Customer::operator==(const Customer& otherCustomer)
{
	// Two customers are equal if both of their account numbers are the same.
	return accountNumber == otherCustomer.accountNumber;
}

void Customer::AddPurchase(const string& itemName, const string& date, const float cost)
{
	// Construct the new purchase at the beginning of the customer's purchase vector.
	purchaseVector.emplace(purchaseVector.begin(), itemName, date, cost);

	// Add the cost of the new purchase to the total spendings.
	totalSpendings += cost;
}

void Customer::DisplayData() const
{
	// Display customer's data.
	cout << "________________________________________________________________________________________________________________________________\n";
	cout << firstName << " " << lastName << "\n";
	cout << streetAddress << "\n";
	cout << cityState << ", " << zipcode << "\n";
	cout << phoneNumber << "\n\n";
	cout << "Account #" << accountNumber << "\n\n";

	// Check if the customer has any purchases.
	if (!purchaseVector.empty())
	{
		// Display the total spendings.
		cout << "\tPurchases (" << purchaseVector.size() << "): $" << totalSpendings << "\n";

		// List all customer purchases.
		for (const Purchase& purchase : purchaseVector)
		{
			cout << "\t________________________________\n";
			cout << "\t" << purchase.GetItemName() << ": $" << purchase.GetItemCost() << "\n\n";
			cout << "\t" << purchase.GetPurchaseDate() << "\n";
			cout << "\t________________________________\n\n";
		}
		cout << "________________________________________________________________________________________________________________________________\n\n";
	}
	else
	{
		cout << "\tCustomer has no purchases.\n";
		cout << "________________________________________________________________________________________________________________________________\n\n";
	}
}

void Customer::DisplayAllPurchases() const
{
	// Check if the customer has purchases.
	if (!purchaseVector.empty())
	{
		cout << "________________________________________________________________________________________________________________________________\n";
		cout << "Total: $" << totalSpendings << "\n\n";
		cout << "\tPurchases (" << purchaseVector.size() << "):\n";

		// List all purchases.
		for (const Purchase& purchase : purchaseVector)
		{
			cout << "\t________________________________\n";
			cout << "\t" << purchase.GetItemName() << ": $" << purchase.GetItemCost() << "\n\n";
			cout << "\t" << purchase.GetPurchaseDate() << "\n";
			cout << "\t________________________________\n\n";
		}

		cout << "________________________________________________________________________________________________________________________________\n\n";
	}
	else
	{
		cout << "________________________________________________________________________________________________________________________________\n";
		cout << "\tCustomer has no purchases.\n";
		cout << "________________________________________________________________________________________________________________________________\n\n";
	}
}

void Customer::SaveData(ofstream& outputFile) const
{
	// Check if customer has purchases.
	if (!purchaseVector.empty())
	{
		// Write purchase data into the save file.
		for (const Purchase& purchase : purchaseVector)
		{
			outputFile << purchase.GetItemName() << "+" << purchase.GetPurchaseDate() << "+";
		}
	}

	// Write customer's data into the save file.
	outputFile << firstName << "+" << lastName << "+" << streetAddress << "+" << cityState << "+" << zipcode << "+" << phoneNumber;
}

float Customer::GetTotalSpending() const
{
	return totalSpendings;
}

const string& Customer::GetFirstName() const
{
	return firstName;
}

const string& Customer::GetLastName() const
{
	return lastName;
}

const string& Customer::GetStreetAddress() const
{
	return streetAddress;
}

const string& Customer::GetCityState() const
{
	return cityState;
}

const string& Customer::GetZipcode() const
{
	return zipcode;
}

const string& Customer::GetPhoneNumber() const
{
	return phoneNumber;
}

int Customer::GetAccountNumber() const
{
	return accountNumber;
}

int Customer::GetPurchaseCount() const
{
	return purchaseVector.size();
}

void Customer::SetFirstName(const string& firstName)
{
	this->firstName = firstName;
}

void Customer::SetLastName(const string& lastName)
{
	this->lastName = lastName;
}

void Customer::SetStreetAddress(const string& streetAddress)
{
	this->streetAddress = streetAddress;
}

void Customer::SetCityState(const string& cityState)
{
	this->cityState = cityState;
}

void Customer::SetZipcode(const string& zipcode)
{
	this->zipcode = zipcode;
}

void Customer::SetPhoneNumber(const string& phoneNumber)
{
	this->phoneNumber = phoneNumber;
}