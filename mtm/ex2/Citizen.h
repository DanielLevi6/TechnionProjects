#ifndef EX2_CITIZEN_H
#define EX2_CITIZEN_H

#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;

namespace mtm {
    /**
     * Citizen: class represents Citizen.
     * @contains ID- unique citizen Identification number
     * @contains firstName- citizen's first name
     * @contains lastName- citizen's last name
     * @contains birthYear- citizen's birth year
     */
    class Citizen {
        int ID;
        string firstName;
        string lastName;
        int birthYear;

    public:
        /**
         * Citizen constructor:
         * @param ID
         * @param firstName
         * @param lastName
         * @param birthYear
         */
        Citizen(int ID, string firstName, string lastName, int birthYear)
                : ID(ID), firstName(firstName), lastName(lastName), birthYear(birthYear) {}
    /**
     * Citizen copy constructor:
     * @param to_copy- the Citizen to copy
     * @return copy of the Citizen object
     */
        Citizen(const Citizen& to_copy) : ID(to_copy.ID), firstName(to_copy.firstName), lastName(to_copy.lastName), birthYear(to_copy.birthYear) { }

        virtual ~Citizen() {}
        /**
         * getID:
         * return the Citizen's ID.
         * @return Citizen ID
         */
        int getId() const;
        /**
         * getFirstName:
         * return the Citizen's first name.
         * @return Citizen first name.
         */
        string getFirstName() const;
        /**
         * getLastName:
         * return the Citizen's last name.
         * @return Citizen last name.
         */
        string getLastName() const;
        /**
         * getBirthYear:
         * return the Citizen's birth year.
         * @return Citizen birth year.
         */
        int getBirthYear() const;
        /**
         * printShort:
         * print short detail about Citizen.
         * @param output channel std::ostream
         * @return std::ostream
         */
        virtual ostream& printShort(ostream &) const = 0;
        /**
         * printLong:
         * print full detail about Citizen.
         * @param output channel std::ostream
         * @return std::ostream
         */
        virtual ostream& printLong(ostream &) const = 0;
        /**
         * clone:
         * create new copy for this.
         * @return pointer to new copy.
         */
        virtual Citizen *clone() const = 0;
        /**
         * operator< overload
         * compare between 2 citizens.
         * @return true if left lower than right.
         * @compare ID
         */
        bool operator<(const Citizen&) const;
        /**
         * operator== overload
         * compare between 2 citizens.
         * @return true if equal, false otherwise.
         * @compare ID
         */
        bool operator==(const Citizen&) const;
        /**
         * operator< overload
         * compare between 2 citizens.
         * @return true if left bigger than right.
         * @compare ID
         */
        bool operator>(const Citizen&) const;
        /**
         * operator< overload
         * compare between 2 citizens.
         * @return true if left lower or equal to right.
         * @compare ID
         */
        bool operator<=(const Citizen&) const;
        /**
         * operator< overload
         * compare between 2 citizens.
         * @return true if left bigger or equal to right.
         * @compare ID
         */
        bool operator>=(const Citizen&) const;
        /**
         * operator== overload
         * compare between 2 citizens.
         * @return true if not equal, false otherwise.
         * @compare ID
         */
        bool operator!=(const Citizen&) const;
    };

}
#endif //EX2_CITIZEN_H
