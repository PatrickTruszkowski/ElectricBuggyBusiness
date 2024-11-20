#pragma once

#include <vector>
#include <ctime>

#include "Purchase.h"

using namespace std;

class Customer
{
private:
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
	Customer(vector<Purchase>, string, string, string, string, string, string, string);
};