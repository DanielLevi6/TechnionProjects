#include "City.h"



namespace mtm {

	City::~City(){
		for (Manager* m_iter : managers) {
			delete m_iter;
		}
		for (Employee* e_iter : employees) {
			delete e_iter;
		}
		for (Workplace* w_iter : Workplaces) {
			delete w_iter;
		}
	}

	void City::addEmployee(int ID, string firstName, string lastName, int birthYear)
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

	void City::addManager(int ID, string firstName, string lastName, int birthYear)
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
	void City::addFaculty(int faculty_id, Skill& acquired_skill, int added_points, Condition* condition)
	{
		for (const Faculty<Condition>& iter : faculties) {
			if (iter.getId() == faculty_id) {
				throw FacultyAlreadyExists();
			}
		}

		faculties.insert(Faculty<Condition>(faculty_id,acquired_skill,added_points, condition));
	}

	void City::createWorkplace(int Workplace_id, std::string Workplace_name, int workers_salaries, int managers_salaries)
	{
		for (Workplace* iter : Workplaces) {
			if (iter->getID() == Workplace_id) {
				throw WorkplaceAlreadyExists();
			}
		}

		Workplaces.insert(new Workplace(Workplace_id, Workplace_name, workers_salaries, managers_salaries));
	}

	void City::teachAtFaculty(int employee_id, int faculty_id)
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

	void City::hireManagerAtWorkplace(int manager_id, int Workplace_id)
	{
		for (Manager* manager_iter : managers)
		{
			if (manager_iter->getId() == manager_id)
			{
				for (Workplace* Workplace_iter : Workplaces)
				{
					if (Workplace_iter->getID() == Workplace_id)
					{

                        try{
                            Workplace_iter->hireManager(manager_iter);
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

	void City::fireEmployeeAtWorkplace(int employee_id, int manager_id, int Workplace_id)
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
								Workplace_iter->fireEmployee(employee_id, manager_id);

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

	void City::fireManagerAtWorkplace(int manager_id, int Workplace_id)
	{
		for (Manager* manager_iter : managers)
		{
			if (manager_iter->getId() == manager_id)
			{
				for (Workplace* Workplace_iter : Workplaces)
				{
					if (Workplace_iter->getID() == Workplace_id)
					{
						Workplace_iter->fireManager(manager_id);

						//fire all his employees
                        (*manager_iter).fireAllEmployees(Workplace_iter->getWorkersSalary());
                        
						return;
					}
				}

				throw WorkplaceDoesNotExist();
			}
		}

		throw ManagerDoesNotExist();
	}


	int City::getAllAboveSalary(ostream& stream, int min_salary)
	{
		set<Manager*, ManagerComp>::iterator manager_iter = managers.begin();
		set<Employee*, EmployeeComp>::iterator employee_iter = employees.begin();

		int counter = 0;

		while (manager_iter!=managers.end() || employee_iter!=employees.end())
		{
			if (/*if iterator is nullptr??*/employee_iter == employees.end() || (manager_iter != managers.end() && (*manager_iter)->getId() < (*employee_iter)->getId()))
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

	bool City::isWorkingInTheSameWorkplace(int employee1_id, int employee2_id)
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

		bool employee1_in_Workplace = false;
		bool employee2_in_Workplace = false;

		for (Workplace* Workplace_iter : Workplaces)
		{
			employee1_in_Workplace = Workplace_iter->employeeIsInWorkplace(employee1_id);
			employee2_in_Workplace = Workplace_iter->employeeIsInWorkplace(employee2_id);

			if (employee1_in_Workplace && employee2_in_Workplace)
			{
				return true;
			}

			employee1_in_Workplace = false;
			employee2_in_Workplace = false;

		}

		return false;

	}

	void City::printAllEmployeesWithSkill(ostream& stream, int skill_id)
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

