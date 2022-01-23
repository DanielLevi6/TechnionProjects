#ifndef CITY_H_
#define CITY_H_

#include <string>
#include <set>
#include <iterator>
#include "Citizen.h"
#include "Employee.h"
#include "exceptions.h"
#include "Faculty.h"
#include "Manager.h"
#include "Skill.h"
#include "Workplace.h"

namespace mtm {

	/**
	* WorkplaceComp: Function object for comparison between two workplaces.
	*/
    class WorkplaceComp {
    public:
        bool operator()(const Workplace *w1, const Workplace *w2) const {
            return w1->getID() < w2->getID();
        }
    };
	
	/**
	 * City: class represents a city.
	 * @contains city_name- workplace's name
	 * @contains managers- a set for storing the details of the managers in city
	 * @contains employees- a set for storing the details of the employees in city
	 * @contains faculties- a set for storing the details of the faculties in city
	 * @contains Workplaces- a set for storing the details of the Workplaces in city
	 */
	class City {

		std::string city_name;

		std::set<Manager*, ManagerComp> managers; 
		std::set<Employee*, EmployeeComp> employees; 
		std::set<Faculty<Condition>> faculties;
		std::set<Workplace*, WorkplaceComp> Workplaces;

	public:

		/**
		* City constructor:
		* @param city_name
		*/
		City(std::string city_name) : city_name(city_name){}

		~City();

		/**
		* addEmployee:
		* adds an employee to the city
		*/
		void addEmployee(int ID, string firstName, string lastName, int birthYear);

		/**
		* addManager:
		* adds a manager to the city
		*/
		void addManager(int ID, string firstName, string lastName, int birthYear);

		/**
		* addFaculty:
		* adds a faculty to the city
		*/
		void addFaculty(int faculty_id, Skill& acquired_skill, int added_points, Condition* condition);

		/**
		* createWorkplace:
		* creates a workplace in the city
		*/
		void createWorkplace(int Workplace_id, std::string Workplace_name, int workers_salaries, int managers_salaries);

		/**
		* teachAtFaculty:
		* checks if the employee is standing the approval condition of the faculty and teaches him the skill.
		*/
		void teachAtFaculty(int employee_id, int faculty_id);

		/**
		* hireEmployeeAtWorkplace:
		* A function for hiring an employee in the workplace under a specific manager if stand in the condition.
		*/
		template <class T>
		void hireEmployeeAtWorkplace(T hire_condition, int employee_id, int manager_id, int Workplace_id);

		/**
		* hireManagerAtWorkplace:
		* A function for hiring a manager in the workplace.
		*/
		void hireManagerAtWorkplace(int manager_id, int Workplace_id);

		/**
		* fireEmployeeAtWorkplace:
		* A function for firing an employee in the workplace under a specific manager.
		*/
		void fireEmployeeAtWorkplace(int employee_id, int manager_id, int Workplace_id);

		/**
		* fireManagerAtWorkplace:
		* A function for firing a manager in the workplace.
		*/
		void fireManagerAtWorkplace(int manager_id, int Workplace_id);

		/**
		* getAllAboveSalary:
		* gets a stream and a salary, and updating the stream with the description
		* of the citizens in the city who earn the specific amount of money or greater
		* (according to the order of their id)
		* @return the number of people who printed
		*/
		int getAllAboveSalary(ostream& stream, int min_salary);

		/**
		* isWorkingInTheSameWorkplace:
		* checks if two employees are working in the same workplace
		* @return true if they are, and false otherwise
		*/
		bool isWorkingInTheSameWorkplace(int employee1_id, int employee2_id);

		/**
		* printAllEmployeesWithSkill:
		* updating the stream with the details of all the employees who have the specific skill
		*/
		void printAllEmployeesWithSkill(ostream& stream, int skill_id);

	};


	template <class T>
	void City::hireEmployeeAtWorkplace(T hire_condition, int employee_id, int manager_id, int Workplace_id)
	{
		for (Employee* employee_iter : employees)
		{
			if (employee_iter->getId() == employee_id)
			{
				for (Manager* manager_iter : managers)
				{
					if (manager_iter->getId() == manager_id)
					{
						for (Workplace* Workplace_iter : Workplaces)
						{
							if (Workplace_iter->getID() == Workplace_id)
							{
							    if(manager_iter->employeeIsInManager(employee_id)){
							        return;
							    }
								try{
								    Workplace_iter->hireEmployee(hire_condition, employee_iter, manager_id);
								}
                                catch (EmployeeAlreadyHired&) {
                                    EmployeeAlreadyHired();
                                    return;
                                }
                                catch (EmployeeNotSelected&) {
                                    EmployeeNotSelected();
                                    return;
                                }
								//employee_iter->setSalary(Workplace_iter->getWorkersSalary());
								return;
							}
						}
						
						throw WorkplaceDoesNotExist();
					}
				}

				throw ManagerDoesNotExist();
			}
		}

		throw EmployeeDoesNotExist();
	}
	
}



#endif /*CITY_H_*/