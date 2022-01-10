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

    void Employee::learnSkill(const Skill& new_skill) {
        if (this->isLearned(new_skill)) {
            throw SkillAlreadyLearned();
        }
        //what condition??
        else if (this->getScore() < new_skill.getRequiredPoints()) {
            throw CanNotLearnSkill();
        }
        this->skill.insert(new_skill);
    }

    void Employee::forgetSkill(int skill_id) {
        for (const Skill& skill_iter : skill)
        {
            if (skill_iter.getId()==skill_id && this->isLearned(skill_iter)) {
                this->skill.erase(skill_iter);
                return;
            }
        }
        throw DidNotLearnSkill();
    }


    bool Employee::hasSkill(unsigned int ID) const {
        for (set<Skill>::iterator i = skill.begin(); i != skill.end(); i++) {
            if (i->getId() == ID) {
                return true;
            }
        }
        return false;
    }

    void Employee::setSalary(int add_salary) 
    {
        this->salary += add_salary;

        if (this->salary < 0)
        {
            this->salary = 0;
        }
    }

    void Employee::setScore(int add_score) 
    {
        this->score += add_score;

        if (this->score < 0)
        {
            this->score = 0;
        }
    }

    ostream &Employee::printShort(ostream &os = cout) const {
        return os << getFirstName() << " " << getLastName() << endl << "Salary: " << getSalary() << " Score: " << getScore() << endl;
    }

    ostream &Employee::printLong(ostream &os = cout) const {

        if (this->skill.empty()){
            os << getFirstName() << " " << getLastName() << endl <<
               "id - " << getId() << " birth_year - " << getBirthYear() << endl <<
               "Salary: " << getSalary() << " Score: " << getScore() << endl;
        }
        else {
            os << getFirstName() << " " << getLastName() << endl <<
               "id - " << getId() << " birth_year - " << getBirthYear() << endl <<
               "Salary: " << getSalary() << " Score: " << getScore() <<
               " Skills: "<< endl;
            for (const auto &s : skill) {
                os << s.getName() << endl;
            }
        }
        return os;
    }

    Employee *Employee::clone() const {
        return new Employee(*this);
    }

    bool Employee::operator<(const Employee& to_compare)
    {
        return this->getId() < to_compare.getId();
    }

    bool Employee::operator==(const Employee& to_compare)
    {
        return this->getId() == to_compare.getId();
    }

    std::ostream& operator<<(std::ostream& stream, Employee& to_print)
    {
        return stream << to_print.getFirstName() << " " << to_print.getLastName() << std::endl << "Salary: " << to_print.getSalary() << " Score: " << to_print.getScore() << std::endl;
    }
}