// Name: Jiawei Yang
// Seneca Student ID: 121134183
// Seneca email: jyang210@myseneca.ca
// Date of completion: October 25, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#include "LineManager.h"

LineManager::LineManager() : m_cntCustomerOrder{ 0 } {

}

LineManager::LineManager(const char* fileName, std::vector<Task*>& tasks, std::vector<CustomerOrder>& custOrders) : m_cntCustomerOrder{ 0 } {
	std::ifstream file(fileName);
	Utilities utilities;
	std::string record;
	if (!file) {
		throw std::string("Unable to open [") + fileName + "] file.";
	}
	while (!file.eof()) {
		std::getline(file, record);
		std::string start, next;
		size_t position = 0;
		bool more;
		start = utilities.extractToken(record, position, more);
		next = utilities.extractToken(record, position, more);
		for (size_t i = 0; i < tasks.size(); i++) {
			if (tasks[i]->getName().compare(start) == 0) {
				for (size_t j = 0; j < tasks.size(); j++) {
					if (tasks[j]->getName().compare(next) == 0) {
						tasks[i]->setNextTask(*tasks[j]);
						break;
					}
				}
				if (stratingTask <= 0) {
					stratingTask = i;
				}
				if (next == "") {
					endingTask = i;
				}
				break;
			}
		}
	}
	file.close();
	for (auto& customerOrder : custOrders) {
		this->ToBeFilled.push_front(std::move(customerOrder));
	}
	for (auto& task : tasks) {
		this->AssemblyLine.push_back(task);
	}
	this->m_cntCustomerOrder = this->ToBeFilled.size();
}

bool LineManager::run(std::ostream& os) {
	bool result = true;
	if (!this->ToBeFilled.empty()) {
		*this->AssemblyLine[stratingTask] += std::move(this->ToBeFilled.back());
		this->ToBeFilled.pop_back();
		this->m_cntCustomerOrder--;
	}
	for (size_t i = 0; i < this->AssemblyLine.size(); i++) {
		this->AssemblyLine[i]->runProcess(os);
	}
	CustomerOrder temOrder;
	if (this->AssemblyLine[endingTask]->getCompleted(temOrder)) {
		this->Completed.push_back(std::move(temOrder));
	}
	for (size_t i = 0; i < this->AssemblyLine.size(); i++) {
		if (this->AssemblyLine[i]->moveTask()) {
			result = false;
		}
	}
	return result;
}

void LineManager::displayCompleted(std::ostream& os) const {
	for (auto& order : this->Completed) {
		order.display(os);
	}
	for (auto& order : this->ToBeFilled) {
		order.display(os);
	}
}

void LineManager::validateTasks() const {
	for (size_t i = 0; i < this->AssemblyLine.size(); i++) {
		this->AssemblyLine[i]->validate(std::cout);
	}
}




