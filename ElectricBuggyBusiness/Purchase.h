#pragma once

#include <string>

using namespace std;

class Purchase
{
private:
	string itemName;
	string date;
	float cost;

public:
	Purchase(const string&, const string&, const float);

	const string& GetItemName() const;
	const string& GetPurchaseDate() const;
	float GetItemCost() const;
};