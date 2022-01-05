#ifndef WORK_PLACE_H_
#define WORK_PLACE_H_

#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <iostream>
#include "Manager.h"
#include "Faculty.h"
#include "Employee.h"

namespace mtm {
	class WorkPlace {

		unsigned int workplace_id;
		std::string workplace_name;
		unsigned int workers_salaries;
		unsigned int managers_salaries;

		std::set<Manager*> managers;

	public:

		WorkPlace(unsigned int workplace_id, std::string workplace_name, unsigned int workers_salaries, unsigned int managers_salaries) :
			workplace_id(workplace_id), workplace_name(workplace_name), workers_salaries(workers_salaries), managers_salaries(managers_salaries) {}

		~WorkPlace() {}

		unsigned int getID();

		std::string getName();

		unsigned int getWorkersSalary();

		unsigned int getManagersSalary();

		template <typename T>
		bool hireEmployee(T condition, Employee* new_employee, unsigned int manager_id);

		bool hireManager(Manager* new_manager);

		void fireEmployee(unsigned int worker_id, unsigned int manager_id);

		void fireManager(unsigned int manager_id);

		bool operator==(const WorkPlace& to_compare) const;

		bool employeeIsInWorkplace(unsigned int employee_id) const;

		bool operator<(const WorkPlace& to_compare) const;

		friend std::ostream& operator<<(std::ostream& stream, WorkPlace& to_print);

	};
	
	std::ostream& operator<<(std::ostream& stream, WorkPlace& to_print);


	template <typename T>
	bool WorkPlace::hireEmployee(T condition, Employee* new_employee, unsigned int manager_id)
	{
		if (!condition(new_employee)/*Maybe need to get Employee and not Employee* */) {
			throw EmployeeNotSelected();
		}

		for (Manager* manager_iter : managers)
		{
			if (manager_iter->getId() == manager_id)
			{
				if (manager_iter->employeeIsInManager(new_employee->getId()))
				{
					throw EmployeeAlreadyHired();
				}

				manager_iter->addEmployee(new_employee);
				return true;
			}
		}

		throw ManagerIsNotHired();

	}

}











#endif /*WORK_PLACE_H_*/#pragma once
