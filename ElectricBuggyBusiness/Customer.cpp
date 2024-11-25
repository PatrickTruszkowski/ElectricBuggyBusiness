#include "Customer.h"

Customer::Customer(const string& firstName, const string& lastName, const string& streetAddress, const string& cityState, const string& zipcode, const string& phoneNumber)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->streetAddress = streetAddress;
	this->cityState = cityState;
	this->zipcode = zipcode;
	this->phoneNumber = phoneNumber;

	totalSpendings = 0.00;

	accountNumber = rand() % 9999 + 1;
}

bool Customer::operator==(const Customer& otherCustomer)
{
	return accountNumber == otherCustomer.accountNumber;
}

void Customer::AddPurchase(const string& itemName, const string& date, const float cost)
{
	purchaseVector.emplace_back(itemName, date, cost);

	totalSpendings += cost;
}

void Customer::DisplayData() const
{
	cout << "________________________________________________________________________________________________________________________________\n";
	cout << firstName << " " << lastName << "\n";
	cout << streetAddress << "\n";
	cout << cityState << ", " << zipcode << "\n";
	cout << phoneNumber << "\n\n";
	cout << "Account #" << accountNumber << "\n\n";

	if (!purchaseVector.empty())
	{
		cout << "\tPurchases (" << purchaseVector.size() << "):\n";

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
	if (!purchaseVector.empty())
	{
		cout << "________________________________________________________________________________________________________________________________\n";
		cout << "Total: $" << totalSpendings << "\n";

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
	if (!purchaseVector.empty())
	{
		for (const Purchase& purchase : purchaseVector)
		{
			outputFile << purchase.GetItemName() << "+" << purchase.GetPurchaseDate() << "+";
		}
	}

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