#ifndef MANAGER_H_
#define MANAGER_H_

#include <set>
#include <string>
#include <iostream>
#include "Citizen.h"
#include "Exception.h"

namespace mtm {

	class Manager : public Citizen {

		unsigned int salary;
		std::set<Employee> employees;

	public:

		Manager(unsigned int id, std::string first_name="", std::string last_name="", unsigned int birth_year=0) :
			Citizen(id, first_name, last_name, birth_year), salary(0) { }

		Manager(Manager& to_copy) = default;

		~Manager() {}


		unsigned int getSalary() { return getSalary(); }

		void addEmployee(Employee* new_employee) {
			if (!Employee) {
				throw NullArgument();
			}

			if (employees.find(new_employee)) {
				throw EmployeeAlreadyHired();
			}
			employees.insert(new_employee);
		}

		void removeEmployee(unsigned int id) {
			Employee employee_to_compare(id);
			if (!employees.find(employee_to_compare)) {
				throw EmployeeNotHired();
			}
			employees.erase(employee_to_compare);
		}

		void setSalary(unsigned int added_salary)
		{
			this->salary += added_salary;
		}

		Manager* clone()
		{
			return new Manager(*this);
		}
	};

	std::ostream printShort(std::ostream stream, Manager manager)
	{
		return << "Short_Print" << manager.getFirstName() << " " << manager.getLastName() << std::endl << "Salary: " << manager.getSalary() << std::endl;
	}

	std::ostream printLong(std::ostream stream, Manager manager)
	{
		return << "Long Print" << manager.getFirstName() << " " << manager.getLastName() << std::endl << "id: " << manager.getId() << "birth_year: " << manager.getBirthYear() << std::endl << "Salary: " << manager.getSalary() << endl;
	}





}





#endif /*MANAGER_H_*/