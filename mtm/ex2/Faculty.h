#ifndef FACULTY_H_
#define FACULTY_H_

#include "Skill.h"
#include "Employee.h"
#include "exceptions.h"

namespace mtm {

	class Condition {
	public:
		virtual bool operator()(Employee* employee) = 0;
	};

	template <class T>
	class Faculty {

		unsigned int faculty_id;
		Skill acquired_skill;
		unsigned int added_points;
		T* condition;

	public:

		Faculty(unsigned int faculty_id, Skill& acquired_skill, unsigned int added_points, T* condition) :faculty_id(faculty_id), condition(condition), acquired_skill(acquired_skill), added_points(added_points) {}

		Faculty(const Faculty& to_copy) = default;

		~Faculty() = default;

		Skill getSkill() const;

		unsigned int getId() const;

		unsigned int getAddedPoints() const;

		void teach(Employee* candidate) const;

		bool operator==(const Faculty& to_compare) const;

		bool operator<(const Faculty& to_compare) const;

	};

	template <class T>
	Skill Faculty<T>::getSkill() const
	{
		return this->acquired_skill;
	}

	template <class T>
	unsigned int Faculty<T>::getId() const
	{
		return this->faculty_id;
	}

	template <class T>
	unsigned int Faculty<T>::getAddedPoints() const
	{
		return this->added_points;
	}

	template <class T>
	void Faculty<T>::teach(Employee* candidate) const
	{
		if (!(*this->condition)(candidate)) {
			throw EmployeeNotAccepted();
		}

		try {
            candidate->learnSkill(this->acquired_skill);
        }
		catch(const SkillAlreadyLearned&){
            return;
		}
        catch (const CanNotLearnSkill&) {
            return;
        }

		candidate->setScore(this->added_points);
    }

	template <class T>
	bool Faculty<T>::operator==(const Faculty& to_compare) const
	{
		return this->faculty_id == to_compare.faculty_id;
	}

	template <class T>
	bool Faculty<T>::operator<(const Faculty& to_compare) const
	{
		return this->faculty_id < to_compare.faculty_id;
	}

}


#endif /*FACULTY_H_*/