#include "City.h"
#include "Exceptions.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include "WorkPlace.h"
#include "Faculty.h"


using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using mtm::Exception;
using namespace mtm;

class FacultyCondition1: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getId() >= 0;
    }
};

class FacultyCondition2: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getId() > 3;
    }
};

class FacultyCondition4: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getBirthYear() > 1980;
    }
};

class Condition3{
public:
    bool operator()(Employee* emp){
        return emp->getSalary() == 9;
    }
};

class HiringCondition {
public:
    bool operator()(Employee *emp) {
        return emp->getScore() >=0;
    }
};

class HiringCondition1 {
public:
    bool operator()(Employee *emp) {
        return emp->getScore() >= 10;
    }
};


int main(){
    City Scranton ("Scranton");
    Scranton.addEmployee(1, "Jim", "Halpert", 1990);
    Scranton.addEmployee(2, "Dwight", "Schrute", 1985);
    Scranton.addEmployee(3, "Pam", "Beesly", 1991);
    Scranton.addEmployee(4, "Andy", "Bernard", 1987);
    Scranton.addEmployee(5, "Roy", "Anderson", 1990);
    Scranton.addManager(10, "Michael", "Scott", 1980);
    Scranton.addManager(11, "Jan", "Levinson", 1979);

    Skill warehouse(11,"Warehouse",0);
    Skill reception (12, "reception", 10);
    Skill sales (13, "Sales",15);
    FacultyCondition1 FC1;
    FacultyCondition4 FC4;

    Scranton.addFaculty(100,warehouse,20, &FC1);
    Scranton.addFaculty(200,sales,20, &FC4);

    Scranton.createWorkplace(1000, "Dunder Mifflin", 1000, 2000);
    Scranton.createWorkplace(2000, "White Paper", 1000, 2000);

    Scranton.teachAtFaculty(1,100);
    Scranton.teachAtFaculty(1,200);

    Scranton.hireManagerAtWorkplace(10,1000);
    HiringCondition hiringCondition;
    Scranton.hireEmployeeAtWorkplace(hiringCondition, 1, 10,1000);
    Scranton.hireEmployeeAtWorkplace(hiringCondition, 2, 10,1000);
    Scranton.hireManagerAtWorkplace(11,1000);
    Scranton.hireEmployeeAtWorkplace(hiringCondition,2,11,1000);
    Scranton.teachAtFaculty(2,100);
    Scranton.fireManagerAtWorkplace(11,1000);
    Scranton.hireEmployeeAtWorkplace(hiringCondition,3,10,1000);

    return 1;
}