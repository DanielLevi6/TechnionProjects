#ifndef MANAGER_H_
#define MANAGER_H_

#include <vector>
#include <string>
#include <iostream>

namespace mtm {
	class Manager : public Citizen {

		unsigned int salary;
		std::vector<Citizen> employees;

	public:

		Manager(unsigned int id, std::string first_name, std::string last_name, unsigned int birth_year) :
			Citizen(id, first_name, last_name, birth_year), salary(0) {}

		~Manager() {}


		unsigned int getSalary() { return getSalary(); }

		bool addEmployee(Citizen* new_employee);

		bool removeEmployee(unsigned int id);

		bool setSalary(unsigned int added_salary);

		std::ostream printShort(std::ostream manager);

		std::ostream printLong(std::ostream manager);

		Manager* clone();
	};







}





#endif /*MANAGER_H_*/