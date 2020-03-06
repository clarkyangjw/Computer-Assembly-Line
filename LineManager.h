// Name: Jiawei Yang
// Seneca Student ID: 121134183
// Seneca email: jyang210@myseneca.ca
// Date of completion: October 25, 2019
//
// I confirm that I am the only author of this file
//   and the content was created entirely by me.

#ifndef LINEMANAGER_H
#define LINEMANAGER_H

#include <vector>
#include <string>
#include <fstream>
#include "Task.h"
#include "Utilities.h"

class LineManager {
	std::vector<Task*> AssemblyLine;
	std::deque<CustomerOrder> ToBeFilled;
	std::deque<CustomerOrder> Completed;
	unsigned int m_cntCustomerOrder;
	int stratingTask = -1;
	int endingTask = -1;

public:
	LineManager();
	LineManager(const char*, std::vector<Task*>&, std::vector<CustomerOrder>&);
	bool run(std::ostream&);
	void displayCompleted(std::ostream&) const;
	void validateTasks() const;
};

#endif