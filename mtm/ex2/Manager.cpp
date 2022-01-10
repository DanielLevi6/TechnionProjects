#include "Manager.h"

namespace mtm {

    int Manager::getSalary() const {
        return salary;
    }

    void Manager::addEmployee(Employee *new_employee) {
        if (checkIfEmployeeExist(new_employee)) {
            throw EmployeeAlreadyHired();
        }
        employees.insert(new_employee);
    }

    void Manager::removeEmployee(unsigned int id) {
        if (!employeeIsInManager(id)) {
            throw EmployeeIsNotHired();
        }

        for (Employee *employee_iter : employees) {
            if (employee_iter->getId() == id) {
                employees.erase(employee_iter);
                break;
            }
        }

    }

    void Manager::setSalary(unsigned int added_salary) {
        this->salary += added_salary;

        if (this->salary < 0) {
            this->salary = 0;
        }
    }

    bool Manager::checkIfEmployeeExist(Employee *new_employee) const {
        for (Employee *employee_iter : employees) {
            if (employee_iter->getId() == new_employee->getId()) {
                return true;
            }
        }

        return false;
    }

    bool Manager::isHired() const {
        return hired;
    }

    Manager *Manager::clone() const {
        return new Manager(*this);
    }

    bool Manager::operator==(Manager to_compare) {
        return this->getId() == to_compare.getId();
    }

    bool Manager::employeeIsInManager(unsigned int employee_id) const //There iis a similar function
    {
        for (Employee *employee_iter : employees) {
            if (employee_iter->getId() == employee_id) {
                return true;
            }
        }

        return false;
    }

    std::ostream &Manager::printShort(std::ostream &stream) const {
        return stream << getFirstName() << " " << getLastName() << std::endl << "Salary: " << getSalary() << std::endl;
    }

    std::ostream &Manager::printLong(std::ostream &stream) const {
        if (this->employees.empty()) {
            stream << getFirstName() << " " << getLastName() << std::endl << "id - " << getId() << " birth_year - "
                   << getBirthYear() << std::endl << "Salary: " << getSalary() << std::endl;
        } else {
            stream << getFirstName() << " " << getLastName() << std::endl << "id - " << getId() << " birth_year - "
                   << getBirthYear() << std::endl << "Salary: " << getSalary() << std::endl << "Employees:"
                   << ' ' << std::endl;
            for (Employee *iter : employees) {
                stream << *iter;
            }
        }
        return stream;
    }

    void Manager::fireAllEmployees() {
        for (Employee *employee_iter : employees) {
            employee_iter->setSalary(-employee_iter->getSalary());
        }
    }


    std::ostream &operator<<(std::ostream &stream, Manager &to_print) {
        stream << "Manager " << to_print.getFirstName() << " " << to_print.getLastName() << std::endl << "id - "
               << to_print.getId() << " birth_year - " << to_print.getBirthYear() << std::endl << "Salary: "
               << to_print.getSalary() << std::endl << "Employees:" << ' ' << std::endl;
        for (Employee *iter : to_print.employees) {
            stream << *iter;
        }

        return stream;
    }

}
