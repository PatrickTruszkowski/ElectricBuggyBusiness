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
	static int customerCount;

	vector<Purchase> purchaseVector;
	string firstName;
	string lastName;
	string streetAddress;
	string city;
	string state;
	string zipcode;
	string phoneNumber;
	int accountNumber;

public:
	Customer(string, string, string, string, string, string, string);

	bool operator==(const Customer&);

	void AddPurchase(Purchase);
	void DisplayData() const;
	void SaveData(ofstream&) const;
};