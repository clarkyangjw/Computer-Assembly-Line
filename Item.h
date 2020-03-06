// Name: Jiawei Yang
// Seneca Student ID: 121134183
// Seneca email: jyang210@myseneca.ca
// Date of completion: October 25, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

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
