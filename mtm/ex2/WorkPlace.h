#ifndef WORK_PLACE_H_
#define WORK_PLACE_H_

#include <set>
#include <iterator>
#include <algorithm>
#include <string>
#include <iostream>
#include "Manager.h"
#include "Employee.h"

namespace mtm {

	/**
	* ManagerComp: Function object for comparison between two managers.
	*/
    class ManagerComp {
    public:
        bool operator()(const Manager *m1, const Manager *m2) const {
            return m1->getId() < m2->getId();
        }
    };

	/**
	 * Workplace: class represents a workplace.
	 * @contains workplace_id- unique workplace Identification number
	 * @contains workplace_name- workplace's name
	 * @contains workers_salaries- worker salary in the workplace
	 * @contains managers_salaries- manager salary in the workplace
	 */
    class Workplace {

		int workplace_id;
		std::string workplace_name;
		int workers_salaries;
		int managers_salaries;

		std::set<Manager*, ManagerComp> managers;

	public:

		/**
		* Workplace constructor:
		* @param workplace_id
		* @param workplace_name
		* @param workers_salaries
		* @param managers_salaries
		*/
		Workplace(int workplace_id, std::string workplace_name, int workers_salaries, int managers_salaries) :
			workplace_id(workplace_id), workplace_name(workplace_name), workers_salaries(workers_salaries), managers_salaries(managers_salaries) {}

		~Workplace() {}

		/**
		* getID: 
		* return the Workplace's ID.
		* @return Workplace ID
		*/
		int getID() const;

		/**
		* getName:
		* return the Workplace's name.
		* @return Workplace name.
		*/
		std::string getName() const;

		/**
		* getWorkersSalary:
		* return the worker salary in the workplace.
		* @return workers_salaries.
		*/
		int getWorkersSalary() const;

		/**
		* getManagersSalary:
		* return the manager salary in the workplace.
		* @return managers_salaries.
		*/
		int getManagersSalary() const;

		/**
		* hireEmployee:
		* A function for hiring an employee in the workplace under a specific manager if stand in the condition.
		* @return true if employee was hired and false otherwise.
		*/
		template <typename T>
		bool hireEmployee(T condition, Employee* new_employee, int manager_id);

		/**
		* hireManager:
		* A function for hiring a manager in the workplace.
		* @return true if manager was hired and false otherwise.
		*/
		bool hireManager(Manager* new_manager);

		/**
		* fireEmployee:
		* A function for firing an employee in the workplace under a specific manager.
		*/
		void fireEmployee(int worker_id, int manager_id);

		/**
		* fireManager:
		* A function for firing a manager in the workplace.
		*/
		void fireManager(int manager_id);

		/**
		* operator==:
		* overloading of the comparison between two workplaces.
		* @return true if the two workplace's id are equal, and false otherwise
		*/
		bool operator==(const Workplace& to_compare) const;

		/**
		* employeeIsInWorkplace:
		* Checks if an employee is working in the workplace.
		* @return true if the employee is working in the workplace, and false otherwise.
		*/
		bool employeeIsInWorkplace(int employee_id) const;

		/**
		* operator<:
		* overloading of the < operator between two workplaces.
		* @return true if the first workplace's id is smaller than the second one, and false otherwise
		*/
		bool operator<(const Workplace& to_compare) const;

		/**
		* operator<<:
		* overloading of the << operator.
		* @return a stream with all the information that the workplace contains
		*/
		friend std::ostream& operator<<(std::ostream& stream, const Workplace& to_print);

	};
	
	std::ostream& operator<<(std::ostream& stream, const Workplace& to_print);


	template <typename T>
	bool Workplace::hireEmployee(T condition, Employee* new_employee, int manager_id)
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
				new_employee->setSalary(this->workers_salaries);
				return true;
			}
		}

		throw ManagerIsNotHired();

	}

}

#endif /*WORK_PLACE_H_*/
