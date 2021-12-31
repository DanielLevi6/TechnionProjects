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

        virtual ~Citizen() {}

        unsigned int getID() const;

        string getFirstName() const;

        string getLastName() const;

        unsigned int getBirthYear() const;

        friend bool operator<(const Citizen &, const Citizen &);

        friend bool operator==(const Citizen &, const Citizen &);

        virtual ostream &printShort(ostream &) = 0;

        virtual ostream &printLong(ostream &) = 0;

        virtual Citizen *clone() const = 0;
    };

    bool operator>(const Citizen &citizen1, const Citizen &citizen2);

    bool operator<=(const Citizen &citizen1, const Citizen &citizen2);

    bool operator>=(const Citizen &citizen1, const Citizen &citizen2);

    bool operator!=(const Citizen &citizen1, const Citizen &citizen2);
}
#endif //EX2_CITIZEN_H
