cmake_minimum_required(VERSION 3.17)
project(ex2)
include(CTest)
enable_testing()
set(CMAKE_CXX_STANDARD 11)
set(MTM_FLAGS_DEBUG "-std=c++11 -Wall -Werror -pedantic-errors -L.")
set(MTM_FLAGS_RELEASE "$(MTM_FLAGS_DEBUG) -DNDEBUG")

add_executable(ex2 Skill.cpp Skill.h 
					Citizen.cpp Citizen.h 
					Employee.cpp Employee.h 
					City.cpp City.h 
					exceptions.cpp exceptions.h
					Faculty.h 
					WorkPlace.cpp WorkPlace.h 
					Manager.cpp Manager.h
        test.cpp)



set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)