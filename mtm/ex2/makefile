CC = g++
OBJS =  Skill.o Citizen.o Employee.o City_test.o
EXEC = prog
DEBUG_FLAG = #-g
CFLAGS = -std=c++11 -Wall -Werror -pedantic-errors -DNDEBUG
LIBS = -Isolution -Iprovided
TEST_PATH = ./provided/city_test.cpp
SOL_PATH = solution/*.cpp



$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ $(LIBS) $(TEST_PATH) $(SOL_PATH)


Skill.o : Skill.cpp Skill.h exceptions.h
    $(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

Citizen.o : Citizen.cpp Citizen.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

Employee.o : Employee.cpp Employee.h Skill.h Citizen.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.cpp

