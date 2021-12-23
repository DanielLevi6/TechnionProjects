#ifndef FACULTY_H_
#define FACULTY_H_


namespace mtm {
	class Faculty {


	public:

		Faculty(Condition, Skill& acquired_skill, unsigned int added_points);

		~Faculty();

		Skill getSkill();

		unsigned int getId();

		unsigned int getAddedPoints();

		bool teach(Employee& candidate);

	};










}


#endif /*FACULTY_H_*/