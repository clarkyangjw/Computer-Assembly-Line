#include "CustomerOrder.h"

size_t CustomerOrder::m_widthField{ 0 };

CustomerOrder::CustomerOrder() : m_name{ '\0' }, m_product{ '\0' }, m_cntItem{ 0 }, m_lstItem{ nullptr }{

}

CustomerOrder::CustomerOrder(const std::string& record) : m_name{ '\0' }, m_product{ '\0' }, m_cntItem{ 0 }, m_lstItem{ nullptr } {
	Utilities utilities;
	size_t position = 0;
	bool more;
	this->m_name = utilities.extractToken(record, position, more);
	this->m_product = utilities.extractToken(record, position, more);
	this->m_cntItem = utilities.numDelimiter(record) - 1;
	this->m_lstItem = new(std::nothrow) ItemInfo * [this->m_cntItem];
	if (this->m_lstItem != nullptr) {
		for (size_t i = 0; i < this->m_cntItem; i++) {
			this->m_lstItem[i] = new(std::nothrow) ItemInfo(utilities.extractToken(record, position, more));
		}
	}
	if (!more) {
		this->m_widthField = utilities.getFieldWidth();
	}
}

CustomerOrder::CustomerOrder(const CustomerOrder& custOrder) : m_name{ '\0' }, m_product{ '\0' }, m_cntItem{ 0 }, m_lstItem{ nullptr } {
	throw "Cannot make copies.";
}

CustomerOrder::CustomerOrder(CustomerOrder&& custOrder) noexcept : m_name{ '\0' }, m_product{ '\0' }, m_cntItem{ 0 }, m_lstItem{ nullptr }  {
	*this = std::move(custOrder);
}

CustomerOrder& CustomerOrder::operator=(CustomerOrder&& custOrder) noexcept {
	if (this != &custOrder) {
		for (size_t i = 0; i < this->m_cntItem; i++) {
			delete this->m_lstItem[i];
		}
		delete[] this->m_lstItem;
		this->m_name = custOrder.m_name;
		this->m_product = custOrder.m_product;
		this->m_cntItem = custOrder.m_cntItem;
		this->m_lstItem = custOrder.m_lstItem;
		custOrder.m_name = { '\0' };
		custOrder.m_product = { '\0' };
		custOrder.m_cntItem = 0;
		custOrder.m_lstItem = nullptr;
	}
	return *this;
}

CustomerOrder::~CustomerOrder() {
	for (size_t i = 0; i < this->m_cntItem; i++) {					//delete every element in the array of m_lstItem
		delete this->m_lstItem[i];
	}
	delete[] this->m_lstItem;												//delete the pointer that points to the array
}

bool CustomerOrder::getItemFillState(std::string item) const {
	bool flag = true;
	for (size_t i = 0; i < this->m_cntItem; i++) {
		if (this->m_lstItem[i]->m_itemName.compare(item) == 0) {		//if there are more than one identical item being used. 
			flag = this->m_lstItem[i]->m_fillState;								//if the last identical element is filled, all identical elements are filled. 
			break;
		}
	}
	return flag;
}

bool CustomerOrder::getOrderFillState() const {
	bool flag = true;
	for (size_t i = 0; i < this->m_cntItem; i++) {       //returns true if all the items in the order have been filled
		if (!this->m_lstItem[i]->m_fillState) {
			flag = false;
			break;
		}
	}
	return flag;
}

void CustomerOrder::fillItem(Item& item, std::ostream& os) {
	for (size_t i = 0; i < this->m_cntItem; i++) {
		if (this->m_lstItem[i]->m_itemName.compare(item.getName()) == 0) {
			if (item.getQuantity() >= 1) {
				item.updateQuantity();
				this->m_lstItem[i]->m_serialNumber = item.getSerialNumber();
				this->m_lstItem[i]->m_fillState = true;
				os << "Filled " << this->m_name << ", " << this->m_product << "[" << this->m_lstItem[i]->m_itemName << "]" << std::endl;
			}
			else {
				os << "Unable to fill " << this->m_name << ", " << this->m_product << "[" << this->m_lstItem[i]->m_itemName << "]" << std::endl;
			}
		}
	}
}

void CustomerOrder::display(std::ostream& os) const {
	os << this->m_name << " - " << this->m_product << std::endl;
	for (size_t i = 0; i < this->m_cntItem; i++) {
		os << '[' << std::setw(6) << std::setfill('0') << std::right << this->m_lstItem[i]->m_serialNumber << "] " << std::setfill(' ') << std::left
			<< std::setw(this->m_widthField) << this->m_lstItem[i]->m_itemName << " - ";
		if (this->m_lstItem[i]->m_fillState) {
			os << "FILLED" << std::endl;
		}
		else {
			os << "MISSING" << std::endl;
		}
	}
}
