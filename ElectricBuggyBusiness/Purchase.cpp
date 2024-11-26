#include "Purchase.h"

Purchase::Purchase(const string& itemName, const string& date, const float cost)
{
	// Construct purchase object.
	this->itemName = itemName;
	this->date = date;
	this->cost = cost;
}

bool Purchase::operator>(const Purchase& otherPurchase)
{
	// One purchase is greater than the other if ones cost is greater.
	return cost > otherPurchase.cost;
}

bool Purchase::operator<(const Purchase& otherPurchase)
{
	// One purchase is less than the other if ones cost is less.
	return cost < otherPurchase.cost;
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