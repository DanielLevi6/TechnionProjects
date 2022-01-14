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
#include "WorkPlace.h"

namespace mtm {

    class WorkPlaceComp {
    public:
        bool operator()(const WorkPlace *w1, const WorkPlace *w2) const {
            return w1->getID() < w2->getID();
        }
    };

	class City {

		std::string city_name;

		std::set<Manager*, ManagerComp> managers; //maybe needs a sorted structure
		std::set<Employee*, EmployeeComp> employees; //maybe needs a sorted structure
		std::set<Faculty<Condition>> faculties;
		std::set<WorkPlace*, WorkPlaceComp> workplaces;

	public:

		City(std::string city_name) : city_name(city_name){}

		~City() = default;

		void addEmployee(unsigned int ID, string firstName, string lastName, unsigned int birthYear);

		void addManager(unsigned int ID, string firstName, string lastName, unsigned int birthYear);

		void addFaculty(unsigned int faculty_id, Skill& acquired_skill, unsigned int added_points, Condition* condition);

		void createWorkplace(unsigned int workplace_id, std::string workplace_name, unsigned int workers_salaries, unsigned int managers_salaries);

		void teachAtFaculty(unsigned int employee_id, unsigned int faculty_id);

		template <class T>
		void hireEmployeeAtWorkplace(T hire_condition, unsigned int employee_id, unsigned int manager_id, unsigned int workplace_id);

		void hireManagerAtWorkplace(unsigned int manager_id, unsigned int workplace_id);

		void fireEmployeeAtWorkplace(unsigned int employee_id, unsigned int manager_id, unsigned int workplace_id);

		void fireManagerAtWorkplace(unsigned int manager_id, unsigned int workplace_id);

		int getAllAboveSalary(ostream& stream, unsigned int min_salary);

		bool isWorkingInTheSameWorkplace(unsigned int employee1_id, unsigned int employee2_id);

		void printAllEmployeesWithSkill(ostream& stream, unsigned int skill_id);

	};


	template <class T>
	void City::hireEmployeeAtWorkplace(T hire_condition, unsigned int employee_id, unsigned int manager_id, unsigned int workplace_id)
	{
		for (Employee* employee_iter : employees)
		{
			if (employee_iter->getId() == employee_id)
			{
				for (Manager* manager_iter : managers)
				{
					if (manager_iter->getId() == manager_id)
					{
						for (WorkPlace* workplace_iter : workplaces)
						{
							if (workplace_iter->getID() == workplace_id)
							{
							    if(manager_iter->employeeIsInManager(employee_id)){
							        return;
							    }
								try{
								    workplace_iter->hireEmployee(hire_condition, employee_iter, manager_id);
								}
                                catch (EmployeeAlreadyHired&) {
                                    EmployeeAlreadyHired();
                                    return;
                                }
                                catch (EmployeeNotSelected&) {
                                    EmployeeNotSelected();
                                    return;
                                }
								//employee_iter->setSalary(workplace_iter->getWorkersSalary());
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