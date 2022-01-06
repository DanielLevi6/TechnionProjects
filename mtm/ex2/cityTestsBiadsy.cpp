//
// Created by Muhammad Biadsy on 01/01/2022.
//
#include "City.h"
#include "exceptions.h"
#include <iostream>
#include <memory>
#include <fstream>
#include <vector>
#include "Skill.h"
#include "Citizen.h"
#include "Employee.h"
#include "Manager.h"
#include "Workplace.h"
#include "Faculty.h"


using std::cout;
using std::endl;
using std::ifstream;
using std::ofstream;
using mtm::Exception;
using namespace mtm;

const std::string FILE_PATH = "../../../testOutputsBiadsy";

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/

/**
 * Evaluates expr and continues if expr is true.
 * If expr is false, ends the test by returning false and prints a detailed
 * message about the failure.
 */
#define ASSERT_TEST(expr)                                                         \
     do {                                                                          \
         if (!(expr)) {   red();                                                         \
             printf("\nAssertion failed at %s:%d %s ", __FILE__, __LINE__, #expr);\
             red();\
            return false;                                                         \
        }                                                                         \
     } while (0)



static long NumTestsPassed = 0;

static void red() {
    system("Color C");
}

static void green() {
    system("Color A");
}

static void purple() {
    system("Color D");
}

static void blue() {
    system("Color B");
}

static void yellow () {
    system("Color E");
}

static void reset () {
    system("Color E");
}

static void printIfSuccess(long num_tests)
{
    if (0 == NumTestsPassed)
    {
        red();
    }
    if (num_tests == NumTestsPassed)
    {
        green();
    }
    else
    {
        yellow();
    }
    cout<< "####  Summary: Passed " << NumTestsPassed << " out of " << num_tests << " ####\n" << endl;
    if (0 == NumTestsPassed)
    {
        red();
    }
    if (num_tests == NumTestsPassed)
    {
        green();
    }
    else
    {
        yellow();
    }
}


#define RUN_COLORFULL_TEST(test, name, id)                  \
do {                                 \
if (test()) {                                               purple();\
cout << "Running test# " << id+1  << " " << name << "..." << " [OK]\n"; \
purple();\
++NumTestsPassed;   \
} else {                                                    red();\
cout << "Running test# " << id+1  << " " << name << "..." << " [Failed]\n"; \
red();\
}                                \
} while (0)

/*************************************************************************/
/*************************************************************************/
/*************************************************************************/


class FileFailed {
public:
    FileFailed() = default;
    ~FileFailed() = default;
};


bool matchFiles(std::string out, std::string  exp) {
    ifstream output(out);
    if (!output) {
        cout << "can't open file" << endl;
    }
    ifstream expOutput(exp);
    if (!expOutput) {
        cout << "can't open file" << endl;
    }
    while (!output.eof()) {
        char c;
        output >> std::noskipws >>c;
        char ex;
        expOutput >> std::noskipws >> ex;
        if (ex != c) {
            return false;
        }
    }
    return true;
}

#define OPEN_FILE(streamName, name) std::string fileName = name;\
std::ofstream streamName(fileName, std::ofstream::trunc | std::ofstream::in);\
if(!(streamName).is_open()){\
throw FileFailed();\
}

template <class T> void print(const T& x, ofstream& stream) { stream << x << endl; }

#define ASSERT(expr) ASSERT_TEST(expr)


/////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////*HERE START THE TESTS*//////////////////////////////////////////////
///////////////////////////////////////////////////////////////////////////////////////////////

bool testSkill() {
    OPEN_FILE(out, FILE_PATH + std::string("/printed/testSkill.txt"));
    Skill s1(1,"Python",15);
    Skill s2(2,"c++",10);
    Skill s3(3,"c",5);
    print(s1, out);
    print(s2, out);
    print(s3, out);
    print(s1.getId(), out);
    print(s1.getRequiredPoints(), out);
    s1++;
    print(s1.getRequiredPoints(), out);
    s1+=1;
    print(s1.getRequiredPoints(), out);
    s1= s1+1;
    print(s1.getRequiredPoints(), out);
    s1= 1+s1;
    print(s1.getRequiredPoints(), out);
    print(s2.getId(), out);
    print(s2.getRequiredPoints(), out);
    print(s2.getName(), out);
    ASSERT_TEST(s1 < s2);
    ASSERT_TEST(s2 >= s1);
    ASSERT_TEST(s2 > s1);
    ASSERT_TEST(s1 <= s2);
    ASSERT_TEST(s1 != s2);
    ASSERT_TEST(s2 > s1);
    Skill s70(1,"Q",10);
    ASSERT_TEST(s70 == s1);
    try
    {
        s1+=-1;
    }
    catch (mtm::NegativePoints&)
    {
        print("NegativePoints", out);
    }
    try
    {
        s1=s2+(-1);
    }
    catch (mtm::NegativePoints&)
    {
        print("NegativePoints", out);
    }
    try
    {
        s1=-2+s1;
    }
    catch (mtm::NegativePoints&)
    {
        print("NegativePoints", out);
    }
    print(s1.getRequiredPoints() , out);
    ASSERT_TEST((s1++).getRequiredPoints()==19);
    print(s1.getRequiredPoints() , out);
    s1 = 1 + s1 + 5;
    ASSERT_TEST(s1.getRequiredPoints() == 26);
    s1 = 2 + 1 + s1;
    ASSERT_TEST(s1.getRequiredPoints() == 29);
    s1 = s1 + 2 + 6;
    ASSERT_TEST(s1.getRequiredPoints() == 37);
    s1++++++;
    ASSERT_TEST(s1.getRequiredPoints() == 38);
    try
    {
        s1 = s1 + 1 + -5;
    }
    catch (mtm::NegativePoints&)
    {
        out << "NegativePoints" << endl;
    }
    try
    {
        s1 = -1 + s1 + -5;
    }
    catch (mtm::NegativePoints&)
    {
        out << "NegativePoints" << endl;
    }
    try
    {
        s1 = -1 + s1 + 4;
    }
    catch (mtm::NegativePoints&)
    {
        out << "NegativePoints" << endl;
    }
    try
    {
        s1 = 7 + s1 + -5;
    }
    catch (mtm::NegativePoints&)
    {
        out << "NegativePoints" << endl;
    }
    Skill s90 = s1;
    ASSERT_TEST(s90.getId() == s1.getId());
    ASSERT_TEST(s90.getRequiredPoints() == s1.getRequiredPoints());
    ASSERT_TEST(s90.getName() == s1.getName());
    out << s90 << endl;
    Skill copy_s1(s2);
    ASSERT_TEST(copy_s1.getId() == s2.getId());
    ASSERT_TEST(copy_s1.getRequiredPoints() == s2.getRequiredPoints());
    ASSERT_TEST(copy_s1.getName() == s2.getName());
    out << copy_s1 << endl;
    out.close();
    ASSERT(matchFiles(fileName, FILE_PATH + std::string("/expected/testSkill.txt")));
    return true;
}

bool testEmployee() {
    OPEN_FILE(out, FILE_PATH + std::string("/printed/testEmployee.txt"));
    Employee e1(1, "John", "Williams", 2002);
    Skill s1(1,"C++",0);
    Skill s2(2, "Java", 0);
    ASSERT_TEST(!e1.hasSkill(1));
    ASSERT_TEST(!e1.hasSkill(2));
    e1.learnSkill(s1);
    e1.learnSkill(s2);
    ASSERT_TEST(e1.hasSkill(1));
    ASSERT_TEST(e1.hasSkill(2));
    try
    {
        e1.learnSkill(s1);
    }
    catch (mtm::SkillAlreadyLearned&)
    {
        print("SkillAlreadyLearned", out);
    }
    Skill s5(5, "Java", 2);
    try
    {
        e1.learnSkill(s5);
    }
    catch (mtm::CanNotLearnSkill&)
    {
        print("CanNotLearnSkill", out);
    }
    try
    {
        e1.forgetSkill(5);
    }
    catch (mtm::DidNotLearnSkill&)
    {
        print("DidNotLearnSkill", out);
    }
    print("Short Print", out);
    e1.printShort(out);
    print("Long Print", out);
    e1.printLong(out);
    e1.forgetSkill(2);
    print("Long Print delete the last", out);
    e1.printLong(out);
    e1.learnSkill(s2);
    e1.forgetSkill(1);
    print("Long Print again", out);
    e1.printLong(out);
    ASSERT_TEST(e1.hasSkill(2));
    ASSERT_TEST(e1.getSalary() == 0);
    e1.setSalary(40);
    print("Long Print again set salary", out);
    e1.printLong(out);
    e1.printLong(out);
    ASSERT_TEST(e1.getScore() == 0);
    e1.setScore(6);
    print("Long Print again set score", out);
    e1.printLong(out);
    e1.setSalary(10);
    ASSERT_TEST(e1.getSalary() == 50);
    e1.setSalary(-10000);
    ASSERT_TEST(e1.getSalary()==0);
    e1.setScore(33);
    ASSERT_TEST(e1.getScore() == 39);
    e1.setScore(-500);
    ASSERT_TEST(e1.getScore() == 0);
    Citizen* clone_e1 = e1.clone();
    clone_e1->printLong(out);
    ASSERT_TEST(clone_e1->getId() == e1.getId());
    ASSERT_TEST(clone_e1->getFirstName() == e1.getFirstName());
    ASSERT_TEST(clone_e1->getLastName() == e1.getLastName());
    ASSERT_TEST(clone_e1->getBirthYear() == e1.getBirthYear());
    Employee e88(e1);
    ASSERT_TEST(e88.getId() == e1.getId());
    ASSERT_TEST(e88.getFirstName() == e1.getFirstName());
    ASSERT_TEST(e88.getLastName() == e1.getLastName());
    ASSERT_TEST(e88.getBirthYear() == e1.getBirthYear());
    e88.printLong(out);
    Employee e99 = e1;
    ASSERT_TEST(e99.getId() == e1.getId());
    ASSERT_TEST(e99.getFirstName() == e1.getFirstName());
    ASSERT_TEST(e99.getLastName() == e1.getLastName());
    ASSERT_TEST(e99.getBirthYear() == e1.getBirthYear());
    e99.printLong(out);
    e99.learnSkill(s1);
    e99.printLong(out);
    Employee* clone_e99 = e99.clone();
    ASSERT_TEST(clone_e99->getId() == e99.getId());
    ASSERT_TEST(clone_e99->getFirstName() == e99.getFirstName());
    ASSERT_TEST(clone_e99->getLastName() == e99.getLastName());
    ASSERT_TEST(clone_e99->getBirthYear() == e99.getBirthYear());
    clone_e99->printLong(out);
    out.close();
    delete clone_e1;
    delete clone_e99;
    ASSERT(matchFiles(fileName, FILE_PATH + std::string("/expected/testEmployee.txt")));
    return true;
}

bool testManager() {
    OPEN_FILE(out, FILE_PATH + std::string("/printed/testManager.txt"));
    Employee e1(1, "John", "Williams", 2002);
    Employee e2(2, "Alex", "Martinez", 2000);
    Manager m1(1,"Robert", "stark", 1980);
    try
    {
        m1.removeEmployee(1);
    }
    catch (mtm::EmployeeIsNotHired&)
    {
        print("EmployeeIsNotHired", out);
    }
    m1.addEmployee(&e2);
    try
    {
        m1.addEmployee(&e2);
    }
    catch (mtm::EmployeeAlreadyHired&)
    {
        print("EmployeeAlreadyHired", out);
    }
    m1.addEmployee(&e1);
    print("Short Print", out);
    m1.printShort(out);
    print("Long Print", out);
    m1.printLong(out);
    Citizen* clone_m1 = m1.clone();
    print("Short Print after clone", out);
    clone_m1->printShort(out);
    print("Long Print after clone", out);
    clone_m1->printLong(out);
    m1.removeEmployee(1);
    try
    {
        m1.removeEmployee(1);
    }
    catch (mtm::EmployeeIsNotHired&)
    {
        print("EmployeeIsNotHired_after_delete", out);
    }
    ASSERT_TEST(m1.getSalary() == 0);
    m1.setSalary(-50);
    ASSERT_TEST(m1.getSalary() == 0);
    m1.setSalary(55);
    ASSERT_TEST(m1.getSalary() == 55);
    Manager m6 = m1;
    ASSERT_TEST(m6 == m1);
    ASSERT_TEST(m6.getBirthYear() == m1.getBirthYear());
    ASSERT_TEST(m6.getSalary() == m1.getSalary());
    ASSERT_TEST(m6.getFirstName() == m1.getFirstName());
    ASSERT_TEST(m6.getLastName() == m1.getLastName());
    out << "test_operator_=" << endl;
    m6.printLong(out);
    Manager m77(m1);
    ASSERT_TEST(m77 == m1);
    ASSERT_TEST(m77.getBirthYear() == m1.getBirthYear());
    ASSERT_TEST(m77.getSalary() == m1.getSalary());
    ASSERT_TEST(m77.getFirstName() == m1.getFirstName());
    ASSERT_TEST(m77.getLastName() == m1.getLastName());
    out << "test_copy_constructor" << endl;
    m77.printLong(out);
    m77.addEmployee(&e1);
    out << "test_copy_constructor_after_add_employee" << endl;
    m77.printLong(out);
    out << "check_if_the_original_is_not_modified" << endl;
    m1.printLong(out);
    Manager* clone_m6 = m6.clone();
    ASSERT_TEST(*clone_m6 == m6);
    ASSERT_TEST(clone_m6->getBirthYear() == m6.getBirthYear());
    ASSERT_TEST(clone_m6->getSalary() == m6.getSalary());
    ASSERT_TEST(clone_m6->getFirstName() == m6.getFirstName());
    ASSERT_TEST(clone_m6->getLastName() == m6.getLastName());
    clone_m6->printLong(out);
    out.close();
    delete clone_m1;
    delete clone_m6;
    ASSERT(matchFiles(fileName, FILE_PATH + std::string("/expected/testManager.txt")));
    return true;
}

class Condition1{
public:
    bool operator()(Employee* emp){
        return emp->getId()>0;
    }
};

class Condition2{
public:
    bool operator()(Employee* emp){
        return emp->getScore()>9;
    }
};

bool testWorkplace() {
    OPEN_FILE(out, FILE_PATH + std::string("/printed/testWorkplace.txt"));
    WorkPlace Meta(1,"Meta", 10000, 20000);
    Employee* e1 = new Employee(1, "John", "Williams", 2002);
    Employee* e2 = new Employee(2, "Alex", "Martinez", 2000);
    Condition1 condition1;
    Condition2 condition2;
    try
    {
        Meta.hireEmployee(condition1,e1,1);
    }
    catch (mtm::ManagerIsNotHired&)
    {
        print("ManagerIsNotHired", out);
    }
    Manager* m1 = new Manager(1,"Robert", "stark", 1980);
    m1->setSalary(3);
    try
    {
        Meta.hireManager(m1);
    }
    catch (mtm::CanNotHireManager&)
    {
        print("CanNotHireManager", out);
    }
    m1->setSalary(-3);
    Meta.hireManager(m1);
    try
    {
        Meta.hireManager(m1);
    }
    catch (mtm::ManagerAlreadyHired&)
    {
        print("ManagerAlreadyHired", out);
    }
    try
    {
        Meta.hireEmployee(condition2,e1,1);
    }
    catch (mtm::EmployeeNotSelected&)
    {
        print("EmployeeNotSelected", out);
    }
    try
    {
        Meta.fireEmployee(e1->getId(),m1->getId());
    }
    catch (mtm::EmployeeIsNotHired&)
    {
        print("EmployeeIsNotHired", out);
    }
    Meta.hireEmployee(condition1,e1,m1->getId());
    try
    {
        Meta.hireEmployee(condition1,e1,m1->getId());
    }
    catch (mtm::EmployeeAlreadyHired&)
    {
        print("EmployeeAlreadyHired", out);
    }
    Meta.hireEmployee(condition1,e2,m1->getId());
    print(Meta, out);
    Manager* m2 = new Manager(6,"omar","sharafy",1990);
    Employee* e3 = new Employee(70,"Muhammad","Ghanayem",2010);
    e3->setScore(20);
    Meta.hireManager(m2);
    Meta.hireEmployee(condition2,e3,6);
    WorkPlace copy_meta = Meta;
    WorkPlace copy_constructor_meta(Meta);
    ASSERT_TEST(copy_meta.getID() == Meta.getID());
    ASSERT_TEST(copy_meta.getName() == Meta.getName());
    ASSERT_TEST(copy_meta.getWorkersSalary() == Meta.getWorkersSalary());
    ASSERT_TEST(copy_meta.getManagersSalary() == Meta.getManagersSalary());
    ASSERT_TEST(copy_constructor_meta.getID() == Meta.getID());
    ASSERT_TEST(copy_constructor_meta.getName() == Meta.getName());
    ASSERT_TEST(copy_constructor_meta.getWorkersSalary() == Meta.getWorkersSalary());
    ASSERT_TEST(copy_constructor_meta.getManagersSalary() == Meta.getManagersSalary());
    print("print_with_two_groups",out);
    print(Meta, out);
    print("print_with_two_groups_operator_=",out);
    print(copy_meta, out);
    print("print_with_two_groups_copy_constructor",out);
    print(copy_constructor_meta, out);
    copy_meta.fireManager(m1->getId());
    copy_constructor_meta.fireManager(m2->getId());
    print("print_with_two_groups_operator_=_after_delete_group_of_Robert_Stark",out);
    print(copy_meta, out);
    print("print_with_two_groups_copy_constructor_after_delete_group_of_Omar_Sharafy",out);
    print(copy_constructor_meta, out);
    print("print_with_two_groups_check_if_the_original_is_not_modified",out);
    print(Meta, out);
    Meta.fireManager(m1->getId());
    print("print_after_delete_group_of_Robert_Stark",out);
    print(Meta, out);
    Meta.fireManager(m2->getId());
    print("print_after_delete_all_groups",out);
    print(Meta, out);
    try
    {
        Meta.fireEmployee(e1->getId(),m1->getId());
    }
    catch (mtm::ManagerIsNotHired&)
    {
        print("ManagerIsNotHired_after_delete_manager" , out);
    }
    try
    {
        Meta.fireManager(m1->getId());
    }
    catch (mtm::ManagerIsNotHired&)
    {
        print("ManagerIsNotHired" , out);
    }
    out.close();
    delete e1;
    delete e2;
    delete e3;
    delete m1;
    delete m2;
    ASSERT(matchFiles(fileName, FILE_PATH + std::string("/expected/testWorkplace.txt")));
    return true;
}

class FacultyCondition1: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getId() > 0;
    }
};

class FacultyCondition2: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getId() > 3;
    }
};

class FacultyCondition4: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getBirthYear() > 2000;
    }
};

class Condition3{
public:
    bool operator()(Employee* emp){
        return emp->getSalary() == 9;
    }
};

bool testFaculty()
{
    OPEN_FILE(out, FILE_PATH + std::string("/printed/testFaculty.txt"));
    std::vector<Faculty<Condition>> Faculties;
    FacultyCondition1 fc1;
    FacultyCondition2 fc2;
    Skill skill1(1,"Programming with c++",0);
    Skill skill2(2,"Programming with c",10);
    Faculty<Condition> faculty1(1,skill1,10,&fc1);
    Faculty<Condition> faculty2(3,skill2,10,&fc2);
    ASSERT_TEST(faculty1.getId() == 1);
    ASSERT_TEST(faculty2.getId() == 3);
    ASSERT_TEST(faculty1.getAddedPoints() == 10);
    ASSERT_TEST(faculty2.getAddedPoints() == 10);
    ASSERT_TEST(faculty1.getSkill() == skill1);
    ASSERT_TEST(faculty2.getSkill() == skill2);
    Employee e1(10, "John", "Williams", 2002);
    Employee e2(20, "Alex", "Martinez", 2000);
    Faculties.push_back(faculty1);
    Faculties.push_back(faculty2);
    for(Faculty<Condition> faculty:Faculties)
    {
        faculty.teach(&e1);
        faculty.teach(&e2);
    }
    ASSERT_TEST(e1.hasSkill(1));
    ASSERT_TEST(e2.hasSkill(2));
    FacultyCondition4 fc4;
    Faculty<Condition> faculty3(6,skill1,5,&fc1);
    Faculty<Condition> faculty4(50,skill1,5,&fc4);
    print(faculty3.getSkill() , out);
    print(faculty3.getAddedPoints() , out);
    Employee e3(90,"Muhammad","Ghanayem",1890);
    try
    {
        faculty4.teach(&e3);
    }
    catch (mtm::EmployeeNotAccepted&)
    {
        print("EmployeeNotAccepted" , out);
    }
    print("Print_Long" , out);
    e3.printLong(out);
    faculty3.teach(&e3);
    print("Print_Long_after_skill_teach" , out);
    e3.printLong(out);
    Skill skill9(800,"TEST_FACULTY_WITHOUT_CLASS_Condition",80);
    Condition3 condition3;
    Faculty<Condition3> faculty5(3,skill9,80,&condition3);
    e3.setSalary(9);
    faculty5.teach(&e3);
    print("Print_Long_e3_after_skill9_teach" , out);
    e3.printLong(out);
    Faculty<Condition> copy_faculty1 = faculty1;
    ASSERT_TEST(copy_faculty1.getId() == faculty1.getId());
    ASSERT_TEST(copy_faculty1.getSkill() == faculty1.getSkill());
    ASSERT_TEST(copy_faculty1.getAddedPoints() == faculty1.getAddedPoints());
    Employee e90(35,"Fares","Moshe",8000);
    copy_faculty1.teach(&e90);
    print("Print_Long_e90_after_copy_faculty1_teach_operator_=" , out);
    e90.printLong(out);
    Faculty<Condition> copy_constructor_faculty1(faculty1);
    ASSERT_TEST(copy_constructor_faculty1.getId() == faculty1.getId());
    ASSERT_TEST(copy_constructor_faculty1.getSkill() == faculty1.getSkill());
    ASSERT_TEST(copy_constructor_faculty1.getAddedPoints() == faculty1.getAddedPoints());
    Employee e91(8888,"Dani","Amos",8000);
    copy_constructor_faculty1.teach(&e91);
    print("Print_Long_e91_after_copy_constructor_faculty1_teach_copy_constructor" , out);
    e91.printLong(out);
    out.close();
    ASSERT(matchFiles(fileName, FILE_PATH + std::string("/expected/testFaculty.txt")));
    return true;
}

class FacultyCondition3: public Condition{
    bool operator()(Employee* employee) override{
        return employee->hasSkill(1);
    }
};

class FacultyCondition5: public Condition{
    bool operator()(Employee* employee) override{
        return employee->getId() >= 79;
    }
};

class HiringCondition {
public:
    bool operator()(Employee *emp) {
        return emp->getScore() > 5;
    }
};

class HiringCondition1 {
public:
    bool operator()(Employee *emp) {
        return emp->getScore() >= 0;
    }
};

bool testCity()
{
    OPEN_FILE(out, FILE_PATH + std::string("/printed/testCity.txt"));
    City city ("TLV");
    Skill skill1(1,"Programming with c++",0);
    Skill skill2(2,"Programming with c",10);
    city.addEmployee(11, "John", "Williams", 2002);
    city.addEmployee(12, "Alex", "Martinez", 2000);
    city.addEmployee(13, "Lionel", "Smith", 2000);
    city.addManager(104,"Mohamad","Masarwa",1998);
    FacultyCondition1 fc1;
    FacultyCondition3 fc3;
    city.addFaculty(1001, skill1, 10, &fc1);
    city.addFaculty(1002, skill2, 15, &fc3);
    city.teachAtFaculty(11,1001);
    city.teachAtFaculty(11,1002);
    city.teachAtFaculty(12,1001);
    city.teachAtFaculty(13,1001);
    city.createWorkplace(10001, "Meta", 10000, 20000);
    city.hireManagerAtWorkplace(104,10001);
    HiringCondition hiringCondition;
    city.hireEmployeeAtWorkplace(hiringCondition, 11, 104, 10001);
    city.hireEmployeeAtWorkplace(hiringCondition, 12, 104, 10001);
    city.hireEmployeeAtWorkplace(hiringCondition, 13, 104, 10001);
    ASSERT_TEST(city.isWorkingInTheSameWorkplace(11,13));
    ASSERT_TEST(city.isWorkingInTheSameWorkplace(11,12));
    ASSERT_TEST(city.isWorkingInTheSameWorkplace(12,13));
    city.fireEmployeeAtWorkplace(12,104,10001);
    print("printAllAboveSalary output: " ,out);
    city.getAllAboveSalary(out,1000);
    print("printAllEmployeesWithSkill output",out);
    city.printAllEmployeesWithSkill(out, 1);
    city.fireManagerAtWorkplace(104,10001);
    print( "printAllAboveSalary output: " ,out);
    city.getAllAboveSalary(out,1000);
    print( "printAllEmployeesWithSkill output" ,out);
    city.printAllEmployeesWithSkill(out, 1);
    try
    {
        city.addEmployee(11,"can_not_add","lets_try",0);

    }
    catch (mtm::EmployeeAlreadyExists&)
    {
        out << "CitizenAlreadyExists" << endl;
    }
    try
    {
        city.addManager(104,"can_not_add","lets_try",10000);
    }
    catch (mtm::ManagerAlreadyExists&)
    {
        out << "CitizenAlreadyExists" << endl;
    }
    try
    {
        city.addFaculty(1001, skill1, 10, &fc1);
    }
    catch (mtm::FacultyAlreadyExists&)
    {
        out << "FacultyAlreadyExists" << endl;
    }
    try
    {
        city.createWorkplace(10001, "Meta", 10000, 20000);
    }
    catch (mtm::WorkplaceAlreadyExists&)
    {
        out << "WorkplaceAlreadyExists" << endl;
    }
    Employee e7(900,"amir","mahmod",1997);
    try
    {
        city.teachAtFaculty(900,1001);
    }
    catch (mtm::EmployeeDoesNotExist&)
    {
        out << "EmployeeDoesNotExist" << endl;
    }
    try
    {
        city.teachAtFaculty(11,80);
    }
    catch (mtm::FacultyDoesNotExist&)
    {
        out << "FacultyDoesNotExist" << endl;
    }
    try
    {
        city.hireEmployeeAtWorkplace(hiringCondition,11,104,5000);
    }
    catch (mtm::WorkplaceDoesNotExist&)
    {
        out << "WorkplaceDoesNotExist" << endl;
    }
    try
    {
        city.hireEmployeeAtWorkplace(hiringCondition,11,700,10001);
    }
    catch (mtm::ManagerDoesNotExist&)
    {
     out << "ManagerDoesNotExist" << endl;
    }
    try
    {
        city.hireEmployeeAtWorkplace(hiringCondition,60000,104,10001);
    }
    catch (mtm::EmployeeDoesNotExist&)
    {
        out << "EmployeeDoesNotExist" << endl;
    }
    try
    {
        city.hireManagerAtWorkplace(104,12000);
    }
    catch (mtm::WorkplaceDoesNotExist&)
    {
        out << "WorkplaceDoesNotExist" << endl;
    }
    try
    {
        city.hireManagerAtWorkplace(7000,10001);
    }
    catch (mtm::ManagerDoesNotExist&)
    {
        out << "ManagerDoesNotExist" << endl;
    }
    try
    {
        city.fireEmployeeAtWorkplace(90,104,10001);
    }
    catch (mtm::EmployeeDoesNotExist&)
    {
        out << "EmployeeDoesNotExist" << endl;
    }
    try
    {
    city.fireEmployeeAtWorkplace(11,200,10001);
    }
    catch (mtm::ManagerDoesNotExist&)
    {
        out << "ManagerDoesNotExist" << endl;
    }
    try
    {
        city.fireEmployeeAtWorkplace(11,104,2000000);
    }
    catch (mtm::WorkplaceDoesNotExist&)
    {
        out << "WorkplaceDoesNotExist" << endl;
    }
    try
    {
        city.fireManagerAtWorkplace(111,10001);
    }
    catch (mtm::ManagerDoesNotExist&)
    {
        out << "ManagerDoesNotExist" << endl;
    }
    try
    {
        city.fireManagerAtWorkplace(104,1233);
    }
    catch (mtm::WorkplaceDoesNotExist&)
    {
        out << "WorkplaceDoesNotExist" << endl;
    }
    try
    {
        city.addEmployee(104,"citizen_already_exists","chack",1999);
    }
    catch (mtm::EmployeeAlreadyExists&)
    {
        out << "CitizenAlreadyExists" << endl;
    }
    ASSERT_TEST(city.getAllAboveSalary(out,0) == 4);
    ASSERT_TEST(city.getAllAboveSalary(out,5000) == 0);
    City copy_city = city;
    out << "test operator = getAllAboveSalary" << endl;
    ASSERT_TEST(copy_city.getAllAboveSalary(out,0) == city.getAllAboveSalary(out,0));
    out << "test operator = printAllEmployeesWithSkill" << endl;
    city.printAllEmployeesWithSkill(out,1);
    copy_city.printAllEmployeesWithSkill(out,1);
    copy_city.hireManagerAtWorkplace(104,10001);
    out << "test operator = getAllAboveSalary check if the original does not modified" << endl;
    ASSERT_TEST(copy_city.getAllAboveSalary(out,10000)-1 == city.getAllAboveSalary(out,10000));
    copy_city.addEmployee(79,"Adi","Williams",1790);
    HiringCondition1 hiringCondition1;
    copy_city.hireEmployeeAtWorkplace(hiringCondition1,79,104,10001);
    ASSERT_TEST(copy_city.getAllAboveSalary(out,10000)-2 == city.getAllAboveSalary(out,10000));
    Skill skill3(88,"run_c++_tests",10);
    FacultyCondition5 facultyCondition5;
    copy_city.addFaculty(1003,skill3,20,&facultyCondition5);
    copy_city.teachAtFaculty(79,1003);
    out << "test operator = printAllEmployeesWithSkill check if the original does not modified" << endl;
    city.printAllEmployeesWithSkill(out,88);
    copy_city.printAllEmployeesWithSkill(out,88);
    City copy_constructor_city(city);
    out << "test copy constructor getAllAboveSalary" << endl;
    ASSERT_TEST(copy_constructor_city.getAllAboveSalary(out,0) == city.getAllAboveSalary(out,0));
    out << "test copy constructor printAllEmployeesWithSkill" << endl;
    city.printAllEmployeesWithSkill(out,1);
    copy_constructor_city.printAllEmployeesWithSkill(out,1);
    copy_constructor_city.hireManagerAtWorkplace(104,10001);
    out << "test copy constructor getAllAboveSalary check if the original does not modified" << endl;
    ASSERT_TEST(copy_constructor_city.getAllAboveSalary(out,10000)-1 == city.getAllAboveSalary(out,10000));
    copy_constructor_city.addEmployee(400,"Fahd","Williams",9999);
    copy_constructor_city.hireEmployeeAtWorkplace(hiringCondition1,400,104,10001);
    ASSERT_TEST(copy_constructor_city.getAllAboveSalary(out,10000)-2 == city.getAllAboveSalary(out,10000));
    copy_constructor_city.addFaculty(1003,skill3,20,&facultyCondition5);
    copy_constructor_city.teachAtFaculty(400,1003);
    out << "test copy constructor printAllEmployeesWithSkill check if the original does not modified" << endl;
    city.printAllEmployeesWithSkill(out,88);
    copy_constructor_city.printAllEmployeesWithSkill(out,88);
    copy_constructor_city.addManager(7001,"Muhammad","Biadsy",5000);
    out << "test copy constructor getAllAboveSalary check if the original does not modified added another manager" << endl;
    ASSERT_TEST(copy_constructor_city.getAllAboveSalary(out,0)-2 == city.getAllAboveSalary(out,0));
    out.close();
    ASSERT_TEST(matchFiles(fileName, FILE_PATH + std::string("/expected/testCity.txt")));
    return true;
}

/*The functions for the tests should be added here*/
bool (*tests[]) (void) = {
        testSkill,
        testEmployee,
        testManager,
        testWorkplace,
        testFaculty,
        testCity,
};

#define NUMBER_TESTS ((long)(sizeof(tests)/sizeof(*tests)))

/*The names of the test functions should be added here*/
const char* testNames[NUMBER_TESTS] = {
        "testSkill",
        "testEmployee",
        "testManager",
        "testWorkplace",
        "testFaculty",
        "testCity",
};

int main(int argc, char *argv[])
{
    blue();
    cout << "Running Tests C++ ..." << endl;
    blue();
    long number_tests = NUMBER_TESTS;
    if (argc == 1)
    {
        for (long test_idx = 0; test_idx < number_tests; test_idx++)
        {
            RUN_COLORFULL_TEST(tests[test_idx], testNames[test_idx], test_idx);
        }
        printIfSuccess(number_tests);
    }
    else if (argc != 2)
    {
        cout << "Usage: city <test index>\n" << endl;
        return 0;
    }
    else
    {
        long test_idx = strtol(argv[1], NULL, 10);
        if (test_idx < 1 || test_idx > NUMBER_TESTS)
        {
            cout << "Invalid test index %ld\n" << test_idx << endl;
            return 0;
        }
        number_tests = 1;
        RUN_COLORFULL_TEST(tests[test_idx - 1], testNames[test_idx - 1], test_idx - 1);
    }
    blue();
    cout << "@@@@ by Muhammad Biadsy GOOD LUCK @@@@" << endl;
    blue();
    return 0;
}