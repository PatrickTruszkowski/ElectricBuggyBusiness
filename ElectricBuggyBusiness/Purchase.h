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
	Purchase(string, string, float);

	string GetItemName() const;
	string GetPurchaseDate() const;
	float GetItemCost() const;
};