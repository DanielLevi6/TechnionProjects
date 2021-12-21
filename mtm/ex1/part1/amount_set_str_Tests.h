#include <stdio.h>
#include "amount_set_str.h"

#define RUN_TEST(test) \
do { \
 printf("Running " #test "... \t\t"); \
 if (test()) { \
 printf("[OK]"); \
 } \
 printf("\n"); \
} while(0);

#define FAIL() printf("[Failure in %s() LINE %d]\n", __func__, __LINE__);


/*
* The following functions are being tested:
*   asCreate           - Creates a new empty set
*   asDestroy          - Deletes an existing set and frees all resources
*   asCopy             - Copies an existing set
*   asGetSize          - Returns the size of the set
*   asContains         - Checks if an element exists in the set
*   asGetAmount        - Returns the amount of an element in the set
*   asRegister         - Add a new element into the set
*   asChangeAmount     - Increase or decrease the amount of an element in the set
*   asDelete           - Delete an element completely from the set
*   asClear            - Deletes all elements from target set
*   asGetFirst         - Sets the internal iterator to the first element
*                        in the set, and returns it.
*   asGetNext          - Advances the internal iterator to the next element
*                        and returns it.
*   AS_FOREACH         - A macro for iterating over the set's elements
*/

bool testCreate();

bool testDestroy();

bool testCopy();

bool testGetSize();

bool testContains();

bool testGetAmount();

bool testRegister();

bool testChangeAmount();

bool testDelete();

bool testClear();

bool testGetFirst();

bool testGetNext();

