CC = gcc
OBJS = matamikya.o matamikya_print.o matamikya_tests.o matamikya_main.o order.o product.o
OBJS2 = amount_set_str.o main_tests.o Tests.o 
EXEC = matamikya
EXEC_AS = amount_set_str

DEBUG_FLAG = -g
CFLAGS = -std=c99 -Wall -Werror -pedantic-errors -DNDEBUG
LIBS = -L. -lmtm -lm -las
TEST_PATH = ./tests/
COBJ = matamikya*.c $(TEST_PATH)matamikya*.c

$(EXEC) : $(OBJS)
	$(CC) $(DEBUG_FLAG) $(OBJS) -o $@ $(LIBS)


matamikya.o : matamikya.c matamikya.h list.h set.h amount_set.h product.h order.h set.h matamikya_print.h libas.a libmtm.a
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.c

matamikya_tests.o : tests/matamikya_tests.c matamikya.h tests/test_utilities.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $(TEST_PATH)$*.c

matamikya_main.o : tests/matamikya_tests.h tests/test_utilities.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $(TEST_PATH)$*.c

matamikya_print.o : matamikya_print.c matamikya_print.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.c

order.o : order.c order.h product.h set.h amount_set.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.c

product.o : product.c product.h amount_set.h 
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $(LIBS) $*.c
	
.amount_set_str: 
$(EXEC_AS) : $(OBJS2)
	$(CC) $(DEBUG_FLAG) $(OBJS2) -o $@ 

amount_set_str.o : amount_set_str.c amount_set_str.h 
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $*.c 

Tests.o : Tests.c Tests.h
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $*.c 

main_tests.o : main_tests.c Tests.h 
	$(CC) -c $(CFLAGS) $(DEBUG_FLAG) $*.c

clean:
	rm -f $(OBJS) $(EXEC)
	rm -f $(OBJS2) $(EXEC_AS)
	
