#include "Manager.h"

namespace mtm {

	unsigned int Manager::getSalary() const
	{
		return salary;
	}

	void Manager::addEmployee(Employee* new_employee)
	{
		if (checkIfEmployeeExist(new_employee)) {
			throw EmployeeAlreadyHired();
		}

		employees.insert(*new_employee);
		
		
	}

	void Manager::removeEmployee(unsigned int id)
	{
		Employee employee_to_compare(id,"","",0);
		if (!employeeIsInManager(id)) {
			throw EmployeeIsNotHired();
		}
		employees.erase(employee_to_compare);
	}

	void Manager::setSalary(unsigned int added_salary)
	{
		this->salary += added_salary;
	}

	bool Manager::checkIfEmployeeExist(Employee* new_employee) const
	{
		for (const Employee& manager_iter : employees)
		{
			if (manager_iter.getId() == new_employee->getId())
			{
				return true;
			}
		}

		return false;
	}

	bool Manager::isHired() const
	{
		return hired;
	}

	Manager* Manager::clone() const
	{
		return new Manager(*this);
	}

	bool Manager::operator==(Manager to_compare)
	{
		return this->getId() == to_compare.getId();
	}

	bool Manager::employeeIsInManager(unsigned int employee_id) const //There iis a similar function
	{
		for (const Employee& manager_iter : employees)
		{
			if (manager_iter.getId() == employee_id)
			{
				return true;
			}
		}

		return false;
	}

	std::ostream& Manager::printShort(std::ostream& stream) const
	{
		return stream << "Short_Print" << getFirstName() << " " << getLastName() << std::endl << "Salary: " << getSalary() << std::endl;
	}

	std::ostream& Manager::printLong(std::ostream& stream) const
	{
		return stream << "Long Print" << getFirstName() << " " << getLastName() << std::endl << "id: " << getId() << "birth_year: " << getBirthYear() << std::endl << "Salary: " << getSalary() << endl;
	}

	std::ostream& operator<<(std::ostream& stream, Manager& to_print)
	{
		stream << "Manager " << to_print.getFirstName() << " " << to_print.getLastName() << std::endl << "id - " << to_print.getId() << " birth_year - " << to_print.getBirthYear() << std::endl << "Salary: " << to_print.getSalary() << std::endl << "Employees:" << std::endl;
		for (Employee iter : to_print.employees) {
			stream << iter;
		}

		return stream;
	}

}
