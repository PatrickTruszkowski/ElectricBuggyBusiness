#include "Customer.h"

vector<int> Customer::customerAccountNumberVector;

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

	if (!customerAccountNumberVector.empty())
	{
		bool valid = false;

		while (!valid)
		{
			for (int currentAccountNumber : customerAccountNumberVector)
			{
				if (currentAccountNumber == accountNumber)
				{
					valid = false;

					accountNumber = rand() % 9999 + 1;

					break;
				}

				valid = true;

				customerAccountNumberVector.emplace_back(accountNumber);
			}
		}
	}
}

bool Customer::operator==(const Customer& otherCustomer)
{
	return accountNumber == otherCustomer.accountNumber;
}

void Customer::AddPurchase(const string& itemName, const string& date, const float cost)
{
	purchaseVector.emplace(purchaseVector.begin(), itemName, date, cost);

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
		cout << "\tPurchases (" << purchaseVector.size() << "): $" << totalSpendings << "\n";

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
		cout << "Total: $" << totalSpendings << "\n\n";
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