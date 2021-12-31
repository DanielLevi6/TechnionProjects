#include "Skill.h"

namespace mtm {

    int Skill::getID() const {
        return ID;
    }

    string Skill::getName() const {
        return name;
    }

    unsigned int Skill::getRequiredPoints() const {
        return requiredPoints;
    }

    ostream &operator<<(ostream &os, const Skill &skill) {
        return os << skill.name << " level: " << skill.strongLevel << std::endl;
    }

    bool operator<(const Skill &skill1, const Skill &skill2) {
        return skill1.ID < skill2.ID;
    }

    bool operator==(const Skill &skill1, const Skill &skill2) {
        return skill1.ID < skill2.ID;
    }

    Skill &Skill::operator++() {
        this->requiredPoints += 1;
        return *this;
    }

    Skill &Skill::operator+=(const int posPoints) {
        if (posPoints < 0) {
            throw NegativePoints();
        }
        this->requiredPoints += posPoints;
        return *this;
    }

    Skill &Skill::operator+(const int posPoints) {
        if (posPoints < 0) {
            throw NegativePoints();
        }

        this->requiredPoints += posPoints;
        return *this;
    }

    bool operator>(const Skill &skill1, const Skill &skill2) {
        return skill2 < skill1;
    }

    bool operator<=(const Skill &skill1, const Skill &skill2) {
        return !(skill2 < skill1);
    }

    bool operator>=(const Skill &skill1, const Skill &skill2) {
        return !(skill1 < skill2);
    }

    bool operator!=(const Skill &skill1, const Skill &skill2) {
        return !(skill1 == skill2);
    }

}
