#include "Customer.h"

int Customer::customerCount = 0;

Customer::Customer(string firstName, string lastName, string streetAddress, string city, string state, string zipcode, string phoneNumber)
{
	this->firstName = firstName;
	this->lastName = lastName;
	this->streetAddress = streetAddress;
	this->city = city;
	this->state = state;
	this->zipcode = zipcode;
	this->phoneNumber = phoneNumber;

	customerCount++;
	accountNumber = customerCount;
}

bool Customer::operator==(const Customer& otherCustomer)
{
	return accountNumber == otherCustomer.accountNumber;
}

void Customer::AddPurchase(Purchase purchase)
{
	purchaseVector.push_back(purchase);
}

void Customer::DisplayData() const
{
	cout << "________________________________________________________________________________________________________________________________\n";
	cout << firstName << " " << lastName << "\n";
	cout << streetAddress << "\n";
	cout << city << ", " << state << ", " << zipcode << "\n";
	cout << phoneNumber << "\n\n";
	cout << "Account #" << accountNumber << "\n\n";

	cout << "\tPurchases:\n\n";

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