#include "Customer.h"

Customer::Customer(const string& firstName, const string& lastName, const string& streetAddress, const string& city, const string& state, const string& zipcode, const string& phoneNumber)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->streetAddress = streetAddress;
	this->city = city;
	this->state = state;
	this->zipcode = zipcode;
	this->phoneNumber = phoneNumber;

	totalSpendings = 0.00;

	accountNumber = rand() % 9999 + 1;
}

bool Customer::operator==(const Customer& otherCustomer)
{
	return accountNumber == otherCustomer.accountNumber;
}

void Customer::AddPurchase(const Purchase purchase)
{
	purchaseVector.push_back(purchase);

	totalSpendings += purchase.GetItemCost();
}

void Customer::DisplayData() const
{
	cout << "________________________________________________________________________________________________________________________________\n";
	cout << firstName << " " << lastName << "\n";
	cout << streetAddress << "\n";
	cout << city << ", " << state << ", " << zipcode << "\n";
	cout << phoneNumber << "\n\n";
	cout << "Account #" << accountNumber << "\n\n";

	cout << "\tPurchases:\n";

	for (const Purchase& purchase : purchaseVector)
	{
		cout << "\t________________________________\n";
		cout << "\t" << purchase.GetItemName() << ": $" << purchase.GetItemCost() << "\n\n";
		cout << "\t" << purchase.GetPurchaseDate() << "\n";
		cout << "\t________________________________\n\n";
	}
	cout << "________________________________________________________________________________________________________________________________\n\n";
}

void Customer::DisplayAllPurchases() const
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

void Customer::SaveData(ofstream& outputFile) const
{
	if (!purchaseVector.empty())
	{
		for (const Purchase& purchase : purchaseVector)
		{
			outputFile << purchase.GetItemName() << "," << purchase.GetPurchaseDate() << ",";
		}
	}

	outputFile << firstName << "," << lastName << "," << streetAddress << "," << city << "," << state << "," << zipcode << "," << phoneNumber;
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