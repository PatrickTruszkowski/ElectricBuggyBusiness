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
};