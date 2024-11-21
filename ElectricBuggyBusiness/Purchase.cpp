#include "Purchase.h"

Purchase::Purchase(string itemName, string date, float cost)
{
	this->itemName = itemName;
	this->date = date;
	this->cost = cost;
}

string Purchase::GetItemName() const
{
	return itemName;
}

string Purchase::GetPurchaseDate() const
{
	return date;
}

float Purchase::GetItemCost() const
{
	return cost;
}