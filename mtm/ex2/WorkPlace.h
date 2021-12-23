#ifndef WORK_PLACE_H_
#define WORK_PLACE_H_

#include <vector>
#include <string>
#include <iostream>


namespace mtm {
	class WorkPlace {

		unsigned int workplace_id;
		std::string workplace_name;
		unsigned int workers_salaries;
		unsigned int managers_salaries;

		std::vector<Manager*> managers;

	public:

		WorkPlace(unsigned int id, std::string workplace_name, unsigned int workers_salaries, unsigned int managers_salaries) :
			workplace_id(workplace_id), workplace_name(workplace_name), workers_salaries(workers_salaries), managers_salaries(managers_salaries) {}

		~WorkPlace() {}

		unsigned int getID() { return workplace_id; }

		std::string getName() { return workplace_name; }

		unsigned int getWorkersSalary() { return workers_salaries; }

		unsigned int getManagersSalary() { return managers_salaries; }

		bool hireEmployee(CondFunction, Condition, Employee* new_employee, unsigned int manager_id);

		bool hireManager(Manager* new_manager);

		bool fireEmployee(unsigned int worker_id, unsigned int manager_id);

		bool fireManager(unsigned int manager_id);

		std::ostream& operator<<(WorkPlace& to_print);

	};

}











#endif /*WORK_PLACE_H_*/#pragma once
