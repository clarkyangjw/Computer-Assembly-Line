#include "Item.h"

size_t Item::m_widthField{ 0 };

Item::Item() : m_name{ '\0' }, m_description{ '\0' }, m_serialNumber{ 0 }, m_quantity{ 0 } {

}

Item::Item(const std::string& record) : m_name{ '\0' }, m_description{ '\0' }, m_serialNumber{ 0 }, m_quantity{ 0 }  {
	Utilities utilities;
	size_t position = 0;
	bool more;
	this->m_name = utilities.extractToken(record, position, more);
	this->m_serialNumber = std::stoi(utilities.extractToken(record, position, more));
	this->m_quantity = std::stoi(utilities.extractToken(record, position, more));
	this->m_description = utilities.extractToken(record, position, more);
	if (!more) {																												//if there is no token being extracted, update width field.
		this->m_widthField = utilities.getFieldWidth();
	}
}

const std::string& Item::getName() const {
	return this->m_name;
}

const unsigned int Item::getSerialNumber() {
	return this->m_serialNumber++;
}

const unsigned int Item::getQuantity() {
	return this->m_quantity;
}

void Item::updateQuantity() {
	if (this->m_quantity >= 1) {
		this->m_quantity--;		//if quantity less than 1, do nothing; else decrement 1.
	}
}

void Item::display(std::ostream& os, bool full) const {
	if (full) {
		os << std::setw(this->m_widthField) << std::left << this->m_name
			<< std::right << " [" << std::setw(6) << std::setfill('0') << this->m_serialNumber << "] " << std::setfill(' ')
			<< std::left << "Quantity: " << std::setw(this->m_widthField) << this->m_quantity
			<< " Description: " << this->m_description << std::endl;
	}
	else {
		os << std::setw(this->m_widthField) << std::left << this->m_name
			<< std::right << " [" << std::setw(6) << std::setfill('0') << this->m_serialNumber << "] " << std::setfill(' ') << std::endl;
	}
}

