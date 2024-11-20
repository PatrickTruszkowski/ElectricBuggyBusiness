#include "Customer.h"

Customer::Customer(vector<Purchase> purchaseVector, string firstName, string lastName, string streetAddress, string city, string state, string zipcode, string phoneNumber)
{
	this->purchaseVector = purchaseVector;
	this->firstName = firstName;
	this->lastName = lastName;
	this->streetAddress = streetAddress;
	this->city = city;
	this->state = state;
	this->zipcode = zipcode;
	this->phoneNumber = phoneNumber;

	accountNumber = rand() % 9999 + 1;
}