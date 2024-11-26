#pragma once

#include <iostream>
#include <iomanip>
#include <vector>
#include <ctime>
#include <fstream>

#include "Purchase.h"

using namespace std;

class Customer
{
private:
	static vector<int> customerAccountNumberVector;

	vector<Purchase> purchaseVector;
	string firstName;
	string lastName;
	string streetAddress;
	string cityState;
	string zipcode;
	string phoneNumber;
	int accountNumber;
	float totalSpendings;

public:
	Customer(const string&, const string&, const string&, const string&, const string&, const string&);

	bool operator==(const Customer&);

	void AddPurchase(const string&, const string&, const float);
	void DisplayData() const;
	void DisplayAllPurchases() const;
	void SaveData(ofstream&) const;
	float GetTotalSpending() const;
	const string& GetFirstName() const;
	const string& GetLastName() const;
	const string& GetStreetAddress() const;
	const string& GetCityState() const;
	const string& GetZipcode() const;
	const string& GetPhoneNumber() const;
	int GetAccountNumber() const;
	int GetPurchaseCount() const;
	void SetFirstName(const string&);
	void SetLastName(const string&);
	void SetStreetAddress(const string&);
	void SetCityState(const string&);
	void SetZipcode(const string&);
	void SetPhoneNumber(const string&);
};