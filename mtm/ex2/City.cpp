#include "City.h"



namespace mtm {


	void City::addEmployee(unsigned int ID, string firstName, string lastName, unsigned int birthYear)
	{
		for (Employee* iter : employees) {
			if ((*iter).getId() == ID) {
				throw CitizenAlreadyExists();
			}
		}
        for (Manager* m_iter : managers) {
            if ((*m_iter).getId() == ID) {
                throw CitizenAlreadyExists();
            }
        }

		employees.insert(new Employee(ID, firstName, lastName, birthYear));
	}

	void City::addManager(unsigned int ID, string firstName, string lastName, unsigned int birthYear)
	{
	    /**why new manager? never accessed*/
		//Manager* new_manager = new Manager(ID, firstName, lastName, birthYear);
		for (Manager* iter : managers) {
			if ((*iter).getId() == ID) {
				throw CitizenAlreadyExists();
			}
		}
        for (Employee* iter : employees) {
            if ((*iter).getId() == ID) {
                throw CitizenAlreadyExists();
            }
        }
		managers.insert(new Manager(ID,firstName,lastName,birthYear));
	}

	//Need to be changed to a generic condition
	void City::addFaculty(unsigned int faculty_id, Skill& acquired_skill, unsigned int added_points, Condition* condition)
	{
		for (const Faculty<Condition>& iter : faculties) {
			if (iter.getId() == faculty_id) {
				throw FacultyAlreadyExists();
			}
		}

		faculties.insert(Faculty<Condition>(faculty_id,acquired_skill,added_points, condition));
	}

	void City::createWorkplace(unsigned int workplace_id, std::string workplace_name, unsigned int workers_salaries, unsigned int managers_salaries)
	{
		for (WorkPlace* iter : workplaces) {
			if (iter->getID() == workplace_id) {
				throw WorkplaceAlreadyExists();
			}
		}

		workplaces.insert(new WorkPlace(workplace_id, workplace_name, workers_salaries, managers_salaries));
	}

	void City::teachAtFaculty(unsigned int employee_id, unsigned int faculty_id)
	{
		for (Employee* employee_iter : employees) {
			if (employee_iter->getId() == employee_id) {
				for (const Faculty<Condition>& faculty_iter : faculties) {
					if (faculty_iter.getId() == faculty_id) {
						faculty_iter.teach(employee_iter);
						//employee_iter->setScore(employee_iter->getScore() + faculty_iter.getAddedPoints());
						return;
					}
				}

				throw FacultyDoesNotExist();
			}
		}

		throw EmployeeDoesNotExist();
	}

	void City::hireManagerAtWorkplace(unsigned int manager_id, unsigned int workplace_id)
	{
		for (Manager* manager_iter : managers)
		{
			if (manager_iter->getId() == manager_id)
			{
				for (WorkPlace* workplace_iter : workplaces)
				{
					if (workplace_iter->getID() == workplace_id)
					{

                        try{
                            workplace_iter->hireManager(manager_iter);
                        }
                        catch(ManagerAlreadyHired&){
                            ManagerAlreadyExists();
                        }
                        catch (CanNotHireManager&) {
                            CanNotHireManager();
                        }
                        return;
					}
				}

				throw WorkplaceDoesNotExist();
			}
		}

		throw ManagerDoesNotExist();
	}

	void City::fireEmployeeAtWorkplace(unsigned int employee_id, unsigned int manager_id, unsigned int workplace_id)
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
								workplace_iter->fireEmployee(employee_id, manager_id);

								//zero fired employee salary
                                employee_iter->setSalary(-employee_iter->getSalary());
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

	void City::fireManagerAtWorkplace(unsigned int manager_id, unsigned int workplace_id)
	{
		for (Manager* manager_iter : managers)
		{
			if (manager_iter->getId() == manager_id)
			{
				for (WorkPlace* workplace_iter : workplaces)
				{
					if (workplace_iter->getID() == workplace_id)
					{
						workplace_iter->fireManager(manager_id);

						//fire all his employees
                        (*manager_iter).fireAllEmployees(workplace_iter->getWorkersSalary());
                        
						return;
					}
				}

				throw WorkplaceDoesNotExist();
			}
		}

		throw ManagerDoesNotExist();
	}


	int City::getAllAboveSalary(ostream& stream, unsigned int min_salary)
	{
		set<Manager*, ManagerComp>::iterator manager_iter = managers.begin();
		set<Employee*, EmployeeComp>::iterator employee_iter = employees.begin();

		int counter = 0;

		while (manager_iter!=managers.end() || employee_iter!=employees.end())
		{
			if (/*if iterator is nullptr??*/employee_iter == employees.end() || manager_iter != managers.end() && (*manager_iter)->getId() < (*employee_iter)->getId())
			{
				if ((*manager_iter)->getSalary() >= min_salary)
				{
					(*manager_iter)->printShort(stream);
					++counter;
				}
				manager_iter++;
			}
			else
			{
				if (employee_iter != employees.end() && (*employee_iter)->getSalary() >= min_salary)
				{
					(*employee_iter)->printShort(stream);
					++counter;
				}
				employee_iter++;
			}
		}

		return counter;
	}

	bool City::isWorkingInTheSameWorkplace(unsigned int employee1_id, unsigned int employee2_id)
	{
		bool employee1_exist = false;
		bool employee2_exist = false;

		for (Employee* employee_iter : employees)
		{
			if (employee_iter->getId() == employee1_id)
			{
				employee1_exist = true;
			}
			if (employee_iter->getId() == employee2_id)
			{
				employee2_exist = true;
			}
		}

		if (!(employee1_exist && employee2_exist))
		{
			throw EmployeeDoesNotExist();
		}

		bool employee1_in_workplace = false;
		bool employee2_in_workplace = false;

		for (WorkPlace* workplace_iter : workplaces)
		{
			employee1_in_workplace = workplace_iter->employeeIsInWorkplace(employee1_id);
			employee2_in_workplace = workplace_iter->employeeIsInWorkplace(employee2_id);

			if (employee1_in_workplace && employee2_in_workplace)
			{
				return true;
			}

			employee1_in_workplace = false;
			employee2_in_workplace = false;

		}

		return false;

	}

	void City::printAllEmployeesWithSkill(ostream& stream, unsigned int skill_id)
	{
		for (Employee* employee_iter : employees)
		{
			if (employee_iter->hasSkill(skill_id))
			{
				employee_iter->printShort(stream);
			}
		}
	}

}

