#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <iomanip>
#include <iostream>
#include "Utilities.h"

class Item {
	std::string m_name;
	std::string m_description;
	size_t m_serialNumber;
	size_t m_quantity;
	static size_t m_widthField;

public:
	Item();
	Item(const std::string&);
	const std::string& getName() const;
	const unsigned int getSerialNumber();
	const unsigned int getQuantity();
	void updateQuantity();
	void display(std::ostream& os, bool full) const;

};

#endif
