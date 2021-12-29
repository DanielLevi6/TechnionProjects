#include "Exceptions.h"

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
}