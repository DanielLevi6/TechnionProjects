#include "amount_set_str_Tests.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static AmountSet generateSet() {
    AmountSet new_set = asCreate();
    char a[7][14] = {"Pear", "Banana", "Strawberry", "Melon", "Soda", "Water", "Juice"};
    for (int i = 0; i < 7; ++i) {
        asRegister(new_set, a[i]);
    }
    return new_set;
}

/***********************************************************************************************************/

bool testCreate() {
    bool is_fail = false;
    AmountSet new_set = asCreate();
    if (!new_set) {
        FAIL();
        is_fail = true;
    }
    asDestroy(new_set);
    return is_fail ? false : true;
}


bool testCopy() {
    bool is_fail = false;
    //NULL set
    if (asCopy(NULL) != NULL) {
        FAIL();
        is_fail = true;
    }

    //Normal
    AmountSet new_set = generateSet();
    AmountSet copy_set = asCopy(new_set);
    if (!copy_set) {
        FAIL();
        is_fail = true;
    }
    asDestroy(copy_set);
    asDestroy(new_set);
    return is_fail ? false : true;
}


bool testGetSize() {
    bool is_fail = false;

    //NULL Set
    if (asGetSize(NULL) != -1) {
        FAIL();
        is_fail = true;
    }

    //NORMAL
    int size = 7;
    AmountSet new_set = generateSet();
    if (size != asGetSize(new_set)) {
        FAIL();
        is_fail = true;

    }
    asDestroy(new_set);
    return is_fail ? false : true;

}

bool testContains() {
    bool is_fail = false;

    //NULL Set
    if (asContains(NULL, "Banana")) {
        FAIL();
        is_fail = true;
    }

    AmountSet new_set = generateSet();
    //Element exists
    if (!asContains(new_set, "Banana")) {
        FAIL();
        is_fail = true;

    }

    //Element does not exists
    if (asContains(new_set, "Mango")) {
        FAIL();
        is_fail = true;

    }

    asDestroy(new_set);
    return is_fail ? false : true;

}


bool testGetAmount() {
    bool is_fail = false;

    //NULL Set
    double out_amount = 0;
    if (asGetAmount(NULL, "Banana", &out_amount) != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;
    }

    double amount = 20;
    AmountSet new_set = generateSet();

    //Element exists
    asChangeAmount(new_set, "Banana", amount);
    asGetAmount(new_set, "Banana", &out_amount);
    if (out_amount != amount) {
        FAIL();
        is_fail = true;
    }

    //Element does not exists
    if (asGetAmount(new_set, "Mango", &out_amount) != AS_ITEM_DOES_NOT_EXIST) {
        FAIL();
        is_fail = true;
    }

    asDestroy(new_set);
    return is_fail ? false : true;
}

bool testRegister() {
    bool is_fail = false;

    //NULL Set
    if (asRegister(NULL, "Milk") != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;
    }

    AmountSet new_set = generateSet();
    //NULL ELEMENT
    if (asRegister(new_set, NULL) != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;
    }

    /*Element does not exists*/
    //Add to beginning
    asRegister(new_set, "Apple");
    if (!asContains(new_set, "Apple")) {
        FAIL();
        is_fail = true;
    }
    //Add to mid
    asRegister(new_set, "Kiwi");
    if (!asContains(new_set, "Kiwi")) {
        FAIL();
        is_fail = true;
    }
    //Add to end
    asRegister(new_set, "Zebra");
    if (!asContains(new_set, "Zebra")) {
        FAIL();
        is_fail = true;
    }

    /*Element does exists*/
    //Mid
    if (asRegister(new_set, "Banana") != AS_ITEM_ALREADY_EXISTS) {
        FAIL();
        is_fail = true;
    }
    //Beginning
    if (asRegister(new_set, "Apple") != AS_ITEM_ALREADY_EXISTS) {
        FAIL();
        is_fail = true;
    }

    asDestroy(new_set);
    return is_fail ? false : true;
}


bool testChangeAmount() {
    bool is_fail = false;
    AmountSet new_set = generateSet();
    double num = 5;
    //NULL SET
    if (asChangeAmount(NULL, "Milk", num) != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;

    }
    //NULL ELEMENT
    if (asChangeAmount(new_set, NULL, num) != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;

    }

    //change amount Normal
    int pos_amount = 20;
    asChangeAmount(new_set, "Banana", pos_amount);
    double amount = 0;
    asGetAmount(new_set, "Banana", &amount);
    if (amount != pos_amount) {
        FAIL();
        is_fail = true;
    }

    //change amount to negative amount
    double neg_amount = -100;
    if (asChangeAmount(new_set, "Banana", neg_amount) != AS_INSUFFICIENT_AMOUNT) {
        FAIL();
        is_fail = true;
    }

    //Element does not exists
    if (asChangeAmount(new_set, "banana", pos_amount) != AS_ITEM_DOES_NOT_EXIST) {
        FAIL();
        is_fail = true;
    }

    asDestroy(new_set);
    return is_fail ? false : true;
}


bool testDelete() {
    bool is_fail = false;
    AmountSet new_set = generateSet();

    //NULL SET
    if (asDelete(NULL, "Banana") != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;
    }

    //NULL Element
    if (asDelete(new_set, NULL) != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;
    }

    //Element does not exists
    if (asDelete(new_set, "Kiwi") != AS_ITEM_DOES_NOT_EXIST) {
        FAIL();
        is_fail = true;
    }

    //Element does exists
    asDelete(new_set, "Juice");
    if (asContains(new_set, "Juice")) {
        FAIL();
        is_fail = true;
    }
    //Element does exist && first in set
    asDelete(new_set, "Banana");
    if (asContains(new_set, "Juice")) {
        FAIL();
        is_fail = true;
    }

    asDestroy(new_set);
    return is_fail ? false : true;

}

bool testClear() {
    bool is_fail = false;
    AmountSet new_set = generateSet();

    //NULL SET
    if (asClear(NULL) != AS_NULL_ARGUMENT) {
        FAIL();
        is_fail = true;
    }

    //Clear and Expect size==0;
    asClear(new_set);
    if (asGetSize(new_set) != 0) {
        FAIL();
        is_fail = true;
    }

    asDestroy(new_set);
    return is_fail ? false : true;
}

bool testGetFirst() {
    bool is_fail = false;
    AmountSet new_set = generateSet();

    //Empty SET
    AmountSet empty_set = asCreate();
    if (asGetFirst(empty_set)!=(char*) NULL){
        FAIL();
        is_fail = true;
    }
    asDestroy(empty_set);

    //NULL SET
    if (asGetFirst(NULL) != NULL) {
        FAIL();
        is_fail = true;
    }

    //Normal
    if (strcmp(asGetFirst(new_set), "Banana") != 0) {
        FAIL();
        is_fail = true;
    }

    asDestroy(new_set);
    return is_fail ? false : true;
}

bool testGetNext() {
    bool is_fail = false;
    AmountSet new_set = generateSet();


    //Empty SET
    AmountSet empty_set = asCreate();
    if (asGetNext(empty_set)!=(char*) NULL){
        FAIL();
        is_fail = true;
    }
    asDestroy(empty_set);

    //NULL SET
    if (asGetNext(NULL) != NULL) {
        FAIL();
        is_fail = true;
    }

    //Normal
    char * next_node = asGetNext(new_set);
    if (strcmp(next_node,"Juice")!=0){
        FAIL();
        is_fail = true;
    }
    asDestroy(new_set);
    return is_fail ? false : true;
}
