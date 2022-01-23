#ifndef MANAGER_H_
#define MANAGER_H_

#include <set>
#include <string>
#include <iostream>
#include "Citizen.h"
#include "Employee.h"
#include "exceptions.h"

namespace mtm {

    class EmployeeComp {
    public:
        bool operator()(const Employee *e1, const Employee *e2) const {
            return e1->getId() < e2->getId();
        }
    };
    /**
     * Manager: class represents Manager. Manager inherits from Employee.
     * @contains salary- the salary that the Manager gets from his Workplace
     * @contains employees- set of Employees working under the manager.
     */
	class Manager : public Citizen {

		int salary;
		std::set<Employee*, EmployeeComp> employees;

	public:
        /**
         * Manager constructor:
         * @param id
         * @param firstName
         * @param lastName
         * @param birthYear
         */
		Manager(int id, std::string first_name, std::string last_name, int birth_year) :
			Citizen(id, first_name, last_name, birth_year), salary(0) { }
        /**
         * Manager copy constructor:
         * @param to_copy- the Manager to copy
         * @return copy of the Manager object
         */
		Manager(const Manager& to_copy) : Citizen(to_copy.getId(),to_copy.getFirstName(),to_copy.getLastName(),to_copy.getBirthYear()), salary(to_copy.salary), employees(to_copy.employees)
		{ }

		~Manager() {}
        /**
         * getSalary:
         * return the Manager's salary.
         * @return Manager's salary.
         */
		int getSalary() const;
        /**
         * addEmployee:
         * add employee to the Manager's set of employees.
         * @param new_employee- the Employee to add.
         */
		void addEmployee(Employee* new_employee);
        /**
         * removeEmployee:
         * remove employee from the Manager's set of employees.
         * @param id- the id of the Employee to remove.
         */
		void removeEmployee(int id);
        /**
         * setSalary:
         * update the Manager's salary.
         * @param added_salary- the amount to add to Manager's salary.
         */
		void setSalary(int added_salary);
        /**
         * setSalary:
         * check if Employee is in the Manager's set of employees.
         * @param new_employee- the employee to find.
         */
		bool checkIfEmployeeExist(Employee* new_employee) const;
        /**
          * clone:
          * create new copy for this.
          * @return pointer to new copy.
          */
		Manager* clone() const override;
        /**
         * operator== overload
         * compare between 2 Managers.
         * @return true if equal, false otherwise.
         * @compare ID
         */
		bool operator==(Manager to_compare);

		bool employeeIsInManager(int employee_id) const;
        /**
         * printShort:
         * print short detail about Manager.
         * @param output channel std::ostream
         * @return std::ostream
         */
		ostream& printShort(ostream& stream) const override;
        /**
         * printLong:
         * print full detail about Manager.
         * @param output channel std::ostream
         * @return std::ostream
         */
		ostream& printLong(ostream& stream) const override;

		friend std::ostream& operator<<(std::ostream& stream, Manager& to_print);
        /**
         * fireAllEmployees:
         * remove all employees from employees set and update their salary.
         * @param salary - the salary to reduce from all employees.
         */
		void fireAllEmployees(int salary);
	};

	std::ostream& operator<<(std::ostream& stream, Manager& to_print);


}

#endif /*MANAGER_H_*/