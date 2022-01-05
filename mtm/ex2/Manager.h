#ifndef MANAGER_H_
#define MANAGER_H_

#include <set>
#include <string>
#include <iostream>
#include "Citizen.h"
#include "Employee.h"
#include "exceptions.h" //Maybe exception and not exceptions

namespace mtm {

	class Manager : public Citizen {

		unsigned int salary;
		bool hired;
		std::set<Employee> employees;

	public:

		Manager(unsigned int id, std::string first_name, std::string last_name, unsigned int birth_year) :
			Citizen(id, first_name, last_name, birth_year), salary(0), hired(false) { }

		Manager(const Manager& to_copy) : Citizen(to_copy.getId(),to_copy.getFirstName(),to_copy.getLastName(),to_copy.getBirthYear()), salary(to_copy.salary), hired(to_copy.hired), employees(to_copy.employees)
		{ }

		~Manager() {}

		unsigned int getSalary() const;

		void addEmployee(Employee* new_employee);

		void removeEmployee(unsigned int id);

		void setSalary(unsigned int added_salary);

		bool checkIfEmployeeExist(Employee* new_employee) const;

		bool isHired() const;

		Manager* clone() const override;

		bool operator==(Manager to_compare);

		bool employeeIsInManager(unsigned int employee_id) const;

		ostream& printShort(ostream& stream) const override;

		ostream& printLong(ostream& stream) const override;

		friend std::ostream& operator<<(std::ostream& stream, Manager& to_print);

	};

	std::ostream& operator<<(std::ostream& stream, Manager& to_print);



}





#endif /*MANAGER_H_*/