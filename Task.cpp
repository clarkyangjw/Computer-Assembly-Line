// Name: Jiawei Yang
// Seneca Student ID: 121134183
// Seneca email: jyang210@myseneca.ca
// Date of completion: October 25, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "Task.h"

Task::Task() : m_pNextTask{ nullptr } {

}

Task::Task(const std::string& record) : Item(record), m_pNextTask{ nullptr } {

}

void Task::runProcess(std::ostream& os) {
	if (!this->m_orders.empty() && !this->m_orders.back().getOrderFillState()) {
		this->m_orders.back().fillItem(*this, os);
	}
}

bool Task::moveTask() {
	bool result = false;
	if (!this->m_orders.empty()) {
		if (this->m_orders.back().getItemFillState(this->getName()) && this->m_pNextTask) {
			*this->m_pNextTask += std::move(this->m_orders.back());
			this->m_orders.pop_back();
		}
		result = true;
	}
	return result;
}

void Task::setNextTask(Task& task) {
	this->m_pNextTask = &task;
}

bool Task::getCompleted(CustomerOrder& custOrder) {
	bool result = false;
	if (!this->m_orders.empty()) {
		custOrder = std::move(this->m_orders.back());
		this->m_orders.pop_back();
		result = true;
	}
	return result;
}

void Task::validate(std::ostream& os) {
	os << this->getName() << " --> ";
	if (this->m_pNextTask == nullptr) {
		os << "END OF LINE" << std::endl;
	}
	else {
		os << this->m_pNextTask->getName() << std::endl;
	}
}

Task& Task::operator+=(CustomerOrder&& custOrder) {
	this->m_orders.push_front(std::move(custOrder));
	return *this;
}

