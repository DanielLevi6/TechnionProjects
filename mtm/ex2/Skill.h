#ifndef EX2_SKILL_H
#define EX2_SKILL_H

#include "Exceptions.h"
#include <iostream>
#include <string>
using std::string;
using std::cout;
using std::ostream;
using namespace mtm;

class Skill {
    int ID;
    string name;
    unsigned int requiredPoints;
    unsigned int strongLevel;

public:
    Skill(int ID, string name, unsigned int requiredPoints, unsigned int strongLevel)
            : ID(ID), name(name), requiredPoints(requiredPoints), strongLevel(strongLevel) {}

    int getID() const;

    string getName() const;

    unsigned int getRequiredPoints() const;

    friend ostream &operator<<(ostream &, const Skill &);

    friend bool operator<(const Skill &, const Skill &);

    friend bool operator==(const Skill &, const Skill &);

    Skill &operator++();

    Skill &operator+=(const int posPoints);

    Skill &operator+(const int posPoints);

};

#endif //EX2_SKILL_H

