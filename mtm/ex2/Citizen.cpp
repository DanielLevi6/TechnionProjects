#include "Citizen.h"


bool operator>(const Citizen &citizen1, const Citizen &citizen2);

bool operator<=(const Citizen &citizen1, const Citizen &citizen2);

bool operator>=(const Citizen &citizen1, const Citizen &citizen2);

bool operator!=(const Citizen &citizen1, const Citizen &citizen2);



unsigned int Citizen::getID() const{
    return this->ID;
}

string Citizen::getFirstName() const{
    return this->firstName;
}

string Citizen::getLastName() const{
    return this->lastName;
}

unsigned int Citizen::getBirthYear() const{
    return this->birthYear;
}

bool operator<(const Citizen &citizen1, const Citizen &citizen2){
    return citizen1.ID <citizen2.ID;
}

bool operator==(const Citizen &citizen1, const Citizen &citizen2){
    return citizen1.ID ==citizen2.ID;
}

bool operator>(const Citizen &citizen1, const Citizen &citizen2){
    return citizen2<citizen1;
}

bool operator<=(const Citizen &citizen1, const Citizen &citizen2){
    return !(citizen2<citizen1);
}

bool operator>=(const Citizen &citizen1, const Citizen &citizen2){
    return !(citizen1<citizen2);
}

bool operator!=(const Citizen &citizen1, const Citizen &citizen2){
    return !(citizen1==citizen2);
}

