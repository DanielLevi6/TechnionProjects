#include "Skill.h"

namespace mtm {

    int Skill::getId() const {
        return ID;
    }

    string Skill::getName() const {
        return name;
    }

    unsigned int Skill::getRequiredPoints() const {
        return requiredPoints;
    }

    ostream &operator<<(ostream &os, const Skill &skill) {
        return os << skill.name << std::endl;
    }

    Skill Skill::operator++(int) {
        Skill copy = *this;
        this->requiredPoints += 1;
        return copy;
    }

    Skill &Skill::operator+=(const int posPoints) {
        if (posPoints < 0) {
            throw NegativePoints();
        }

        this->requiredPoints += posPoints;
        return *this;
    }

    //Skill &Skill::operator+(const int posPoints) {
    //    if (posPoints < 0) {
    //        throw NegativePoints();
    //    }

    //    this->requiredPoints += posPoints;
    //    return *this;
    //}

    Skill operator+(const Skill& skill, int points)
    {
        if (points < 0) {
            throw NegativePoints();
        }

        Skill result(skill);
        result.requiredPoints += points;

        return result;
    }

    Skill operator+(int points, const Skill& skill)
    {
        if (points < 0) {
            throw NegativePoints();
        }

        Skill result(skill);
        result.requiredPoints += points;

        return result;
    }

    bool operator<(const Skill& skill1, const Skill& skill2) {
        return skill1.ID < skill2.ID;
    }

    bool operator==(const Skill& skill1, const Skill& skill2) {
        return skill1.ID == skill2.ID;
    }

    bool operator>(const Skill &skill1, const Skill &skill2) {
        return skill1.getId() > skill2.getId();
    }

    bool operator<=(const Skill &skill1, const Skill &skill2) {
        return !(skill1 > skill2);
    }

    bool operator>=(const Skill &skill1, const Skill &skill2) {
        return !(skill1 < skill2);
    }

    bool operator!=(const Skill &skill1, const Skill &skill2) {
        return !(skill1 == skill2);
    }

}
