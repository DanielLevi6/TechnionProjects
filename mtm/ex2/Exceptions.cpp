#include "exceptions.h"
#include "exceptions.h"

namespace mtm {

    using std::string; 


    const string NegativePoints::what() {
        return string("NegativePoints");
    }

    const string SkillAlreadyLearned::what() {
        return string("SkillAlreadyLearned");
    }

    const string CanNotLearnSkill::what() {
        return string("CanNotLearnSkill");
    }

    const string DidNotLearnSkill::what() {
        return string("DidNotLearnSkill");
    }

    const string OutOfMemory::what() {
        return string("OutOfMemory");
    }

    const string EmployeeAlreadyHired::what() {
        return string("EmployeeAlreadyHired");
    }

    const string EmployeeNotSelected::what() {
        return string("EmployeeNotSelected");
    }

    const string ManagerIsNotHired::what() {
        return string("ManagerIsNotHired");
    }

    const string ManagerAlreadyHired::what() {
        return string("ManagerAlreadyHired");
    }

    const string CanNotHireManager::what() {
        return string("CanNotHireManager");
    }

    const string EmployeeIsNotHired::what() {
        return string("EmployeeIsNotHired");
    }

    const string EmployeeNotAccepted::what() {
        return string("EmployeeNotAccepted");
    }

    const string EmployeeAlreadyExists::what() {
        return string("EmployeeAlreadyExists");
    }

    const string ManagerAlreadyExists::what() {
        return string("ManagerAlreadyExists");
    }

    const string FacultyAlreadyExists::what() {
        return string("FacultyAlreadyExists");
    }

    const string WorkplaceAlreadyExists::what() {
        return string("WorkplaceAlreadyExists");
    }

    const string EmployeeDoesNotExist::what() {
        return string("EmployeeDoesNotExist");
    }

    const string FacultyDoesNotExist::what() {
        return string("FacultyDoesNotExist");
    }

    const string ManagerDoesNotExist::what() {
        return string("ManagerDoesNotExist");
    }

    const string WorkplaceDoesNotExist::what() {
        return string("WorkplaceDoesNotExist");
    }

    const string CitizenAlreadyExists::what() {
        return string("CitizenAlreadyExists");
    }

}