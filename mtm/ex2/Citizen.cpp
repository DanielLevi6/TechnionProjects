#include "Citizen.h"

namespace mtm {

    int Citizen::getId() const {
        return this->ID;
    }

    string Citizen::getFirstName() const {
        return this->firstName;
    }

    string Citizen::getLastName() const {
        return this->lastName;
    }

    int Citizen::getBirthYear() const {
        return this->birthYear;
    }

    bool Citizen::operator<(const Citizen &citizen2) const {
        return this->ID < citizen2.ID;
    }

    bool Citizen::operator==(const Citizen &citizen2) const {
        return this->ID == citizen2.ID;
    }

    bool Citizen::operator>(const Citizen &citizen2) const {
        return !(*this < citizen2 || *this == citizen2);
    }

    bool Citizen::operator<=(const Citizen &citizen2) const {
        return !(*this > citizen2);
    }

    bool Citizen::operator>=(const Citizen &citizen2) const {
        return !(*this < citizen2);
    }

    bool Citizen::operator!=(const Citizen &citizen2) const {
        return !(*this == citizen2);
    }
}
