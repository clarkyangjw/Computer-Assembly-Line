#ifndef TASK_H
#define TASK_H
#include <queue>
#include <iostream>
#include "Item.h"
#include "CustomerOrder.h"

class Task : public Item {
	std::deque<CustomerOrder> m_orders;
	Task* m_pNextTask;

public:
	Task();
	Task(const std::string&);
	Task(const Task&) = delete;
	Task(Task&&) = delete;
	Task& operator=(const Task&) = delete;
	Task& operator=(Task&&) = delete;
	void runProcess(std::ostream&);
	bool moveTask();
	void setNextTask(Task&);
	bool getCompleted(CustomerOrder&);
	void validate(std::ostream&);
	Task& operator+=(CustomerOrder&&);

};



#endif
