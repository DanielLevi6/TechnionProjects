#ifndef EX2_SKILL_H
#define EX2_SKILL_H

#include "Exceptions.h"
#include <iostream>
#include <string>

using std::string;
using std::cout;
using std::ostream;

namespace mtm {
    class Skill {
        int ID;
        string name;
        unsigned int requiredPoints;
        unsigned int strongLevel;

    public:
        Skill(int ID, string name, unsigned int requiredPoints, unsigned int strongLevel=0)
                : ID(ID), name(name), requiredPoints(requiredPoints), strongLevel(strongLevel) {}

        Skill(const Skill& to_copy) = default;

        int getId() const;

        string getName() const;

        unsigned int getRequiredPoints() const;

        friend ostream &operator<<(ostream &, const Skill &);

        Skill operator++(int);

        Skill &operator+=(const int posPoints);

        //Skill &operator+(const int posPoints);

        friend bool operator<(const Skill&, const Skill&);
        
        friend bool operator==(const Skill&, const Skill&);

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

