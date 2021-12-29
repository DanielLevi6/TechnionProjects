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
}

#endif /* EXCEPTIONS_H */