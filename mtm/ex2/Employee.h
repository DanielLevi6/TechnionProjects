#ifndef EX2_EMPLOYEE_H
#define EX2_EMPLOYEE_H

#include <iostream>
#include <string>
#include "Citizen.h"
#include "Skill.h"
#include <set>
using std::endl;
using std::string;
using std::cout;
using std::ostream;
using std::set;

namespace mtm {
        /**
         * Employee: class represents Employee. Employee inherits from Citizen.
         * @contains salary- the salary that the Employee gets from his Workplace
         * @contains score- the score that the Employee earned.
         * @contains skill- set of Skills the Employee has.
         */
    class Employee : public Citizen {
        int salary;
        int score;
        set<Skill> skill;

        bool isLearned(Skill s) const;

    public:
    /**
     * Employee constructor:
     * @param ID
     * @param firstName
     * @param lastName
     * @param birthYear
     */
        Employee(int ID, string firstName, string lastName, unsigned int birthYear)
                : Citizen(ID, firstName, lastName, birthYear), salary(0), score(0) {
            skill.clear();
        }
    /**
     * Employee copy constructor:
     * @param to_copy- the Employee to copy
     * @return copy of the Employee object
     */
        Employee(const Employee& to_copy) = default;

        ~Employee() override = default;
        /**
         * getSalary:
         * return the Employee's salary.
         * @return Employee's salary.
         */
        int getSalary() const;
        /**
         * getScore:
         * return the Employee's score.
         * @return Employee's score.
         */
        int getScore() const;
        /**
         * learnSkill: try to add the skill to the Employee's set of skills.
         * @param new_skill- the Skill to learn.
         */
        void learnSkill(const Skill& new_skill);
        /**
         * forgetSkill: try to remove the skill from the Employee's set of skills.
         * @param skill_id- the ID of the Skill to forge.
         */
        void forgetSkill(int skill_id);
        /**
         * forgetSkill: checks if the skill is in the Employee's set of skills.
         * @param ID- the Skill's ID to search.
         * @return true if skill in set, false otherwise.
         */
        bool hasSkill(int ID) const;
        /**
         * setSalary: update the Employee's salary.
         * @param add_salary- the amount to add to Employee's salary.
         */
        void setSalary(int add_salary);
        /**
         * setScore: update the Employee's score.
         * @param add_score- the amount to add to Employee's score.
         */
        void setScore(int add_score);
        /**
         * printShort:
         * print short detail about Employee.
         * @param output channel std::ostream
         * @return std::ostream
         */
        ostream &printShort(ostream &) const override;
        /**
         * printLong:
         * print full detail about Employee.
         * @param output channel std::ostream
         * @return std::ostream
         */
        ostream &printLong(ostream &) const override;
        /**
          * clone:
          * create new copy for this.
          * @return pointer to new copy.
          */
        Employee *clone() const override;
        /**
         * operator< overload
         * compare between 2 Employees.
         * @return true if left lower than right.
         * @compare ID
         */
        bool operator<(const Employee& to_compare);
        /**
         * operator== overload
         * compare between 2 Employees.
         * @return true if equal, false otherwise.
         * @compare ID
         */
        bool operator==(const Employee& to_compare);

        friend std::ostream& operator<<(std::ostream& stream, Employee& to_print);
    };

    std::ostream& operator<<(std::ostream& stream, Employee& to_print);
}
#endif //EX2_EMPLOYEE_H

