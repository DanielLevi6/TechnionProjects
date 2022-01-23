#include "Workplace.h"

namespace mtm {

	int Workplace::getID() const
	{ 
		return workplace_id; 
	}

	std::string Workplace::getName() const
	{
		return workplace_name; 
	}

	int Workplace::getWorkersSalary() const
	{ 
		return workers_salaries; 
	}

	int Workplace::getManagersSalary() const
	{ 
		return managers_salaries; 
	}

	bool Workplace::hireManager(Manager* new_manager)
	{
		for (Manager* is_exist : managers) {
			if (*is_exist == *new_manager) {
				throw ManagerAlreadyHired();
			}
		}

		if ( new_manager->getSalary() > 0) {
			throw CanNotHireManager();
		}
        new_manager->setSalary(this->managers_salaries);
		this->managers.insert(new_manager);

		return true;
	}

	void Workplace::fireEmployee(int worker_id, int manager_id)
	{
		for (Manager* manager_iter : managers) {
			if (manager_iter->getId() == manager_id) {
				manager_iter->removeEmployee(worker_id);
				//update Fired employee salary?
				return;
			}
		}

		throw ManagerIsNotHired();
	}

	void Workplace::fireManager(int manager_id)
	{
		for (Manager* iter : managers) {
			if (iter->getId() == manager_id) {
				iter->setSalary(-iter->getSalary());
			    managers.erase(iter);
				return;
			}
		}

		throw ManagerIsNotHired();
	}

	bool Workplace::operator==(const Workplace& to_compare) const
	{
		return this->workplace_id == to_compare.workplace_id;
	}

	bool Workplace::employeeIsInWorkplace(int employee_id) const
	{
		for (Manager* manager_iter : managers)
		{
			if (manager_iter->employeeIsInManager(employee_id))
			{
				return true;
			}
		}

		return false;
	}

	std::ostream& operator<<(std::ostream& stream, const Workplace& to_print)
	{
		stream << "Workplace name - " << to_print.getName();

		if (!to_print.managers.empty())
		{
			stream << " Groups:" ;
		}
		stream << endl;
		for (Manager* iter : to_print.managers) {
			stream << *iter;
		}

		return stream;
	}

	bool Workplace::operator<(const Workplace& to_compare) const
	{
		return this->workplace_id < to_compare.workplace_id;
	}

}