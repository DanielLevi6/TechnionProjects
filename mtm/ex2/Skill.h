#ifndef EX2_SKILL_H
#define EX2_SKILL_H

#include "Exceptions.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;

namespace mtm {
    /**
     * Skill: class represents skill. Any citizen can acquire a skill if he has
     * bigger or equal points than requiredPoints.
     * @contains ID- unique skill Identification number
     * @contains name- skill's name
     * @contains requiredPoints- the required points to acquire the skill
     */
    class Skill {
        int ID;
        string name;
        unsigned int requiredPoints;

    public:
        /**
         * Skill constructor:
         * @param ID
         * @param name
         * @param requiredPoints
         */
        Skill(int ID, string name, unsigned int requiredPoints)
                : ID(ID), name(name), requiredPoints(requiredPoints) {}
        /**
         * Skill copy constructor:
         * @param to_copy- the skill to copy
         * @return copy of the Skill object
         */
        Skill(const Skill& to_copy) = default;
        /**
         * getID:
         * return the Skill object's ID.
         * @return Skill object's ID
         */
        int getId() const;
        /**
         * getName:
         * return the Skill object's name.
         * @return Skill object's name
         */
        string getName() const;
        /**
         * getRequiredPoints:
         * return the Skill RequiredPoints.
         * @return Skill object's RequiredPoints
         */
        unsigned int getRequiredPoints() const;
        /**
         * operator<< overload
         * @format
         * name
         */
        friend ostream &operator<<(ostream &, const Skill &);
        /**
         * operator++ overload
         * add 1 to skill's RequiredPoints
         */
        Skill operator++(int);
        /**
         * operator+= overload
         * @param posPoints- points to add to skill's RequiredPoints.
         */
        Skill &operator+=(const int posPoints);
        /**
         * operator< overload
         * compare between 2 skills.
         * @return true if left lower than right.
         * @compare ID
         */
        friend bool operator<(const Skill&, const Skill&);
        /**
         * operator== overload
         * compare between 2 skills.
         * @return true if equal, false otherwise.
         * @compare ID
         */
        friend bool operator==(const Skill&, const Skill&);
        /**
         * operator+ overload
         * @param points- points to add to skill's RequiredPoints
         */
        friend Skill operator+(const Skill& skill, int points);

        friend Skill operator+(int points, const Skill& skill);

    };

    ostream& operator<<(ostream&, const Skill&);

    Skill operator+(const Skill& skill, int points);

    Skill operator+(int points, const Skill& skill);

    bool operator<(const Skill&, const Skill&);

    bool operator==(const Skill&, const Skill&);

    bool operator>(const Skill &skill1, const Skill &skill2);

    bool operator<=(const Skill &skill1, const Skill &skill2);

    bool operator>=(const Skill &skill1, const Skill &skill2);

    bool operator!=(const Skill &skill1, const Skill &skill2);

}
#endif //EX2_SKILL_H

