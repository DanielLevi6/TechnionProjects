#include "WorkPlace.h"

namespace mtm {

	unsigned int WorkPlace::getID() const 
	{ 
		return workplace_id; 
	}

	std::string WorkPlace::getName() const
	{
		return workplace_name; 
	}

	unsigned int WorkPlace::getWorkersSalary() const
	{ 
		return workers_salaries; 
	}

	unsigned int WorkPlace::getManagersSalary() const
	{ 
		return managers_salaries; 
	}

	bool WorkPlace::hireManager(Manager* new_manager)
	{
		for (Manager* is_exist : managers) {
			if (*is_exist == *new_manager) {
				throw ManagerAlreadyHired();
			}
		}

		if (new_manager->isHired() || new_manager->getSalary() > 0) {
			throw CanNotHireManager();
		}

		managers.insert(new_manager);
		new_manager->setSalary(this->managers_salaries);
		//delete the hired flag?

		return true;
	}

	void WorkPlace::fireEmployee(unsigned int worker_id, unsigned int manager_id)
	{
		for (Manager* manager_iter : managers) {
			if (manager_iter->getId() == manager_id) {
				manager_iter->removeEmployee(worker_id);
				return;
			}
		}

		throw ManagerIsNotHired();
	}

	void WorkPlace::fireManager(unsigned int manager_id)
	{
		for (Manager* iter : managers) {
			if (iter->getId() == manager_id) {
				managers.erase(iter);
				return;
			}
		}

		throw ManagerIsNotHired();
	}

	bool WorkPlace::operator==(const WorkPlace& to_compare) const
	{
		return this->workplace_id == to_compare.workplace_id;
	}

	bool WorkPlace::employeeIsInWorkplace(unsigned int employee_id) const
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

	std::ostream& operator<<(std::ostream& stream, const WorkPlace& to_print)
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

	bool WorkPlace::operator<(const WorkPlace& to_compare) const
	{
		return this->workplace_id < to_compare.workplace_id;
	}







}