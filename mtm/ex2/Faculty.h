#ifndef FACULTY_H_
#define FACULTY_H_

#include "Skill.h"
#include "Employee.h"
#include "exceptions.h"

namespace mtm {

	/**
	* An abstract class for representing a faculty condition
	*/
	class Condition {
	public:
		virtual bool operator()(Employee* employee) = 0;
	};

	/**
	* Faculty: a class represents a faclty with a generic condition for approval.
	* @contains faculty_id- unique faculty Identification number
	* @contains acquired_skill- the skill that acquired when studying in the faculty
	* @contains added_points- the points that added for the citizen that studying in the faculty
	* @contains condition- the condition for approval to the faculty
	*/
	template <class T>
	class Faculty {

		int faculty_id;
		Skill acquired_skill;
		int added_points;
		T* condition;

	public:

		/**
		* Faculty constructor:
		* @param faculty_id
		* @param acquired_skill
		* @param added_points
		* @param condition
		*/
		Faculty(int faculty_id, Skill& acquired_skill, int added_points, T* condition) :faculty_id(faculty_id), acquired_skill(acquired_skill), added_points(added_points), condition(condition) {}

		/**
		 * Faculty copy constructor:
		 * @param to_copy- the Faculty to copy
		 * @return copy of the Faculty object
		 */
		Faculty(const Faculty& to_copy) = default;

		~Faculty() = default;

        /**
         * getSkill:
         * return the skill that the faculty gives for it's students.
         * @return Skill
         */
		Skill getSkill() const;

		/**
		 * getId:
		 * return the Faculty's ID.
		 * @return Faculty ID
		 */
		int getId() const;

		/**
		 * getAddedPoints:
		 * return the points that the faculty gives for it's students.
		 * @return added_points
		 */
		int getAddedPoints() const;

		/**
		 * teach:
		 * checks if the employee is standing the approval condition of the faculty and teaches him the skill.
		 */
		void teach(Employee* candidate) const;

		/**
		* operator==:
		* overloading of the comparison between two facultys.
		* @return true if the two faculty's id are equal, and false otherwise
		*/
		bool operator==(const Faculty& to_compare) const;

		/**
		* operator<:
		* overloading of the < operator between two facultys.
		* @return true if the first faculty's id is smaller than the second one, and false otherwise
		*/
		bool operator<(const Faculty& to_compare) const;

	};

	template <class T>
	Skill Faculty<T>::getSkill() const
	{
		return this->acquired_skill;
	}

	template <class T>
	int Faculty<T>::getId() const
	{
		return this->faculty_id;
	}

	template <class T>
	int Faculty<T>::getAddedPoints() const
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