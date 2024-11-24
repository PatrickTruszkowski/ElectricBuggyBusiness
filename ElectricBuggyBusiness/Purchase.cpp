#include "Purchase.h"

Purchase::Purchase(const string& itemName, const string& date, const float cost)
{
	this->itemName = itemName;
	this->date = date;
	this->cost = cost;
}

const string& Purchase::GetItemName() const
{
	return itemName;
}

const string& Purchase::GetPurchaseDate() const
{
	return date;
}

float Purchase::GetItemCost() const
{
	return cost;
}