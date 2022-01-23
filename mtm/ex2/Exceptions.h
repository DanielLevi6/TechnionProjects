#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <exception>
#include <string>

namespace mtm {

    class Exception : public std::exception {
    };

    class NegativePoints : public Exception {
    public:
        NegativePoints() = default;

        const std::string what();
    };

    class SkillAlreadyLearned : public Exception {
    public:
        SkillAlreadyLearned() = default;

        const std::string what();
    };

    class CanNotLearnSkill : public Exception {
    public:
        CanNotLearnSkill() = default;

        const std::string what();
    };

    class DidNotLearnSkill : public Exception {
    public:
        DidNotLearnSkill() = default;

        const std::string what();
    };

    class OutOfMemory : public Exception {
    public:
        OutOfMemory() = default;

        const std::string what();
    };

    class EmployeeAlreadyHired : public Exception {
    public:
        EmployeeAlreadyHired() = default;

        const std::string what();
    };

    class EmployeeNotSelected : public Exception {
    public:
        EmployeeNotSelected() = default;

        const std::string what();
    };

    class ManagerIsNotHired : public Exception {
    public:
        ManagerIsNotHired() = default;

        const std::string what();
    };

    class ManagerAlreadyHired : public Exception {
    public:
        ManagerAlreadyHired() = default;

        const std::string what();
    };

    class CanNotHireManager : public Exception {
    public:
        CanNotHireManager() = default;

        const std::string what();
    };

    class EmployeeIsNotHired : public Exception {
    public:
        EmployeeIsNotHired() = default;

        const std::string what();
    };

    class EmployeeNotAccepted : public Exception {
    public:
        EmployeeNotAccepted() = default;

        const std::string what();
    };

    class EmployeeAlreadyExists : public Exception {
    public:
        EmployeeAlreadyExists() = default;

        const std::string what();
    };

    class ManagerAlreadyExists : public Exception {
    public:
        ManagerAlreadyExists() = default;

        const std::string what();
    };

    class FacultyAlreadyExists : public Exception {
    public:
        FacultyAlreadyExists() = default;

        const std::string what();
    };

    class WorkplaceAlreadyExists : public Exception {
    public:
        WorkplaceAlreadyExists() = default;

        const std::string what();
    };

    class EmployeeDoesNotExist : public Exception {
    public:
        EmployeeDoesNotExist() = default;

        const std::string what();
    };

    class FacultyDoesNotExist : public Exception {
    public:
        FacultyDoesNotExist() = default;

        const std::string what();
    };

    class ManagerDoesNotExist : public Exception {
    public:
        ManagerDoesNotExist() = default;

        const std::string what();
    };

    class WorkplaceDoesNotExist : public Exception {
    public:
        WorkplaceDoesNotExist() = default;

        const std::string what();
    };

    class CitizenAlreadyExists : public Exception {
    public:
        CitizenAlreadyExists() = default;

        const std::string what();
    };
}

#endif /* EXCEPTIONS_H */