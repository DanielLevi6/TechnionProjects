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
    class Employee : public Citizen {
        unsigned int salary;
        int score;
        set<Skill> skill;

        bool isLearned(Skill s) const;

    public:
        Employee(unsigned int ID, string firstName, string lastName, unsigned int birthYear)
                : Citizen(ID, firstName, lastName, birthYear), salary(0), score(0) {
            skill.clear();
        }

        Employee(const Employee& to_copy) = default;

        ~Employee() override = default;

        unsigned int getSalary() const;

        int getScore() const;

        void learnSkill(Skill new_skill);

        void forgetSkill(const Skill &to_forget_skill);

        bool hasSkill(unsigned int ID) const;

        void setSalary(int add_salary);

        void setScore(int add_score);

        ostream &printShort(ostream &) const override;

        ostream &printLong(ostream &) const override;

        Employee *clone() const override;

        friend std::ostream& operator<<(std::ostream& stream, Employee& to_print);
    };

    std::ostream& operator<<(std::ostream& stream, Employee& to_print);
}
#endif //EX2_EMPLOYEE_H

