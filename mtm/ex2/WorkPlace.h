#ifndef WORK_PLACE_H_
#define WORK_PLACE_H_

#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <iostream>
#include "Manager.h"

namespace mtm {
	class WorkPlace {

		unsigned int workplace_id;
		std::string workplace_name;
		unsigned int workers_salaries;
		unsigned int managers_salaries;

		std::set<Manager*> managers;

	public:

		WorkPlace(unsigned int id, std::string workplace_name, unsigned int workers_salaries, unsigned int managers_salaries) :
			workplace_id(workplace_id), workplace_name(workplace_name), workers_salaries(workers_salaries), managers_salaries(managers_salaries) {}

		~WorkPlace() {}

		unsigned int getID() { return workplace_id; }

		std::string getName() { return workplace_name; }

		unsigned int getWorkersSalary() { return workers_salaries; }

		unsigned int getManagersSalary() { return managers_salaries; }

		template <typename Condition>
		bool hireEmployee(Condition condition, Employee* new_employee, unsigned int manager_id)
		{
			if (!condition(new_employee)/*Maybe need to get Employee and not Employee* */) {
				throw EmployeeNotSelected();
			}
			Manager copy(manager_id);
			std::iterator<std::set<Manager*>,Manager*> copy_iter = managers.find(copy);
			if (!copy_iter) {
				throw ManagerIsNotHired();
			}
			if(copy_iter
		}

		bool hireManager(Manager* new_manager);

		bool fireEmployee(unsigned int worker_id, unsigned int manager_id);

		bool fireManager(unsigned int manager_id);

		std::ostream& operator<<(WorkPlace& to_print);

	};

}











#endif /*WORK_PLACE_H_*/#pragma once
