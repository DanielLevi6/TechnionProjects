#include "Employee.h"
namespace mtm {
//get Employee's salary
    unsigned int Employee::getSalary() const {
        return this->salary;
    }

    int Employee::getScore() const {
        return this->score;
    }

//if skill already in list skill
    bool Employee::isLearned(const Skill s) const {
        auto search = this->skill.find(s);
        if (search != skill.end()) {
            return true;
        }
        return false;
    }

    void Employee::learnSkill(Skill new_skill) {
        if (this->isLearned(new_skill)) {
            throw SkillAlreadyLearned();
        }
            //what condition??
        else if (false) {
            throw CanNotLearnSkill();
        }
        this->skill.insert(new_skill);
    }

    void Employee::forgetSkill(const Skill &to_forget_skill) {
        if (this->isLearned(to_forget_skill)) {
            this->skill.erase(to_forget_skill);
        } else {
            throw DidNotLearnSkill();
        }
    }


    bool Employee::hasSkill(unsigned int ID) const {
        for (int i = skill.begin()->getID(); i != skill.end()->getID(); i++) {
            if (i == ID) {
                return true;
            }
        }
        return false;
    }

    void Employee::setSalary(int add_salary) {
        this->salary += add_salary;
    }

    void Employee::setScore(int add_score) {
        this->score += add_score;
    }

    ostream &Employee::printShort(ostream &os = cout) const {
        return os << "\n" << getFirstName() << " " << getLastName() << endl;
    }

    ostream &Employee::printLong(ostream &os = cout) const {
        os << "\n" << getFirstName() << " " << getLastName() <<
           "\nid - " << getId() << " birth_year - " << getBirthYear() <<
           "\nSalary: " << getSalary() << " Score: " << getScore() <<
           " Skills:\n" << endl;
        for (const auto & s : skill) {
            os << s.getName() << "\n" << endl;
        }
        return os;
    }

    Employee *Employee::clone() const {
        return new Employee(*this);
    }

    std::ostream& operator<<(std::ostream& stream, Employee& to_print)
    {
        return stream << to_print.getFirstName() << " " << to_print.getLastName() << std::endl << "Salary: " << to_print.getSalary() << " Score: " << to_print.getScore() << std::endl;
    }
}