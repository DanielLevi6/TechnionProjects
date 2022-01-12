CC = g++
OBJS =  Skill.o Citizen.o Employee.o Manager.o Faculty.o Workplace.o city.o Test.o exceptions.o
EXEC = prog
DEBUG_FLAG = #-g
CFLAGS = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
LIBS = -Isolution -Iprovided
TEST_PATH = ./provided/city_test.cpp
SOL_PATH = solution/*.cpp
OUTPUT = ../testOutputsBiadsy/printed


$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ $(LIBS)


Skill.o : Skill.cpp Skill.h exceptions.h
    $(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

Citizen.o : Citizen.cpp Citizen.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

Employee.o : Employee.cpp Employee.h Skill.h Citizen.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

Manager.o : Manager.cpp Manager.h exceptions.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

Faculty.o : Faculty.cpp Faculty.h Employee.h exceptions.h skill.h

Workplace.o : Workplace.cpp Workplace.h employee.h faculty.h manager.h

city.o : city.cpp city.h employee.h faculty.h manager.h workplace.h skill.h



Test.o : Test.cpp
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

