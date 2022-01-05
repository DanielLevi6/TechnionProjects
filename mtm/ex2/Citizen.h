#ifndef EX2_CITIZEN_H
#define EX2_CITIZEN_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;

namespace mtm {
    class Citizen {
        unsigned int ID;
        string firstName;
        string lastName;
        unsigned int birthYear;

    public:
        Citizen(unsigned int ID, string firstName, string lastName, unsigned int birthYear)
                : ID(ID), firstName(firstName), lastName(lastName), birthYear(birthYear) {}

        Citizen(const Citizen& to_copy) : ID(to_copy.ID), firstName(to_copy.firstName), lastName(to_copy.lastName), birthYear(to_copy.birthYear) { }

        virtual ~Citizen() {}

        unsigned int getId() const;

        string getFirstName() const;

        string getLastName() const;

        unsigned int getBirthYear() const;

        virtual ostream& printShort(ostream &) const = 0;

        virtual ostream& printLong(ostream &) const = 0;

        virtual Citizen *clone() const = 0;

        bool operator<(const Citizen&) const;

        bool operator==(const Citizen&) const;

        bool operator>(const Citizen&) const;

        bool operator<=(const Citizen&) const;

        bool operator>=(const Citizen&) const;

        bool operator!=(const Citizen&) const;
    };

    /*bool operator>(const Citizen &citizen1, const Citizen &citizen2);

    bool operator<=(const Citizen &citizen1, const Citizen &citizen2);

    bool operator>=(const Citizen &citizen1, const Citizen &citizen2);

    bool operator!=(const Citizen &citizen1, const Citizen &citizen2);*/
}
#endif //EX2_CITIZEN_H
