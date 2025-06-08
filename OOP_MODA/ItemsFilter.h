#pragma once
#include "Item.h"
#include "MyVector.hpp"

class ItemsFilter
{
public:
	virtual void filter(MyVector<Item>& items) = 0;
	virtual ~ItemsFilter() = default;
};

class FilterByRating: public ItemsFilter
{
public:
	virtual void filter(MyVector<Item>& items) override;
};

class FilterByPrice : public ItemsFilter
{
	bool ascending;

public:
	FilterByPrice(bool ascending);
	virtual void filter(MyVector<Item>& items) override;
};

class FilterByName : public ItemsFilter
{
public:
	virtual void filter(MyVector<Item>& items) override;
};