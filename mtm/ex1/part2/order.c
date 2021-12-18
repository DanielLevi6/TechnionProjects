#include "order.h"
#include "product.h"
#include "set.h"
#include "amount_set.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>

struct order_t {
    unsigned int id;
    bool shipped;
    AmountSet products;
};

Order createOrder(unsigned int id) {
    Order new_order = malloc(sizeof(*new_order));
    if (!new_order) {
        return NULL;
    }

    new_order->id = id;
    new_order->shipped = false;

    new_order->products = asCreate(productCopy, productFree, productCompareByID);
    if (!new_order->products) {
        free(new_order);
        return NULL;
    }
    return new_order;
}

ASElement copyOrder(ASElement source) {
    if (!source) {
        return NULL;
    }

    Order copy = malloc(sizeof(*copy));
    if (!copy) {
        return NULL;
    }

    copy->id = ((Order)source)->id;
    copy->shipped = ((Order)source)->shipped;

    copy->products = asCopy(((Order)source)->products);
    if (!copy->products) {
        free(copy);
        return NULL;
    }
    return copy;
}

void freeOrder(ASElement to_delete) {
    asDestroy(((Order)to_delete)->products);
    free((Order)to_delete);
}

int compareOrders(ASElement first, ASElement second) {
    if (!((Order)first) || !((Order)second)) {
        return 0;
    }
    return (((Order)first)->id) - (((Order)second)->id);
}

OrderResult changeProductAmountInOrder(Order order, const unsigned int productId, const double amount) {
    if (!order) {
        return ORDER_NULL_ARGUMENT;
    }
    for (Product iterator = asGetFirst(order->products); iterator; iterator = asGetNext(order->products)) {
        if (getProductID(iterator) == productId) {

            //18/12 19:37***********************************************************************
            if(checkAmount(amount,productGetAmountType(iterator)))
            {
                return ORDER_INVALID_AMOUNT;
            }

            /********************************7:21***********/
            if(getProductAmount(iterator)+amount<0)
            {
                asDelete(order->products,iterator);
                return ORDER_SUCCESS;
            }
            /***********************************************/
            ProductResult result = addProductAmount(iterator, amount);

            if (result == PRODUCT_NULL_ARGUMENT) {
                return ORDER_NULL_ARGUMENT;
            }// } else if (result == PRODUCT_INSUFFICIENT_AMOUNT) {
            //     return ORDER_INSUFFICIENT_AMOUNT;
            // }
            return ORDER_SUCCESS;
        }
    }

    return ORDER_PRODUCT_NOT_EXIST;
}

unsigned int getOrderID(Order order) {
    return order->id;
}

Product getFirstProductInOrder(Order order) {
    if(!order)
    {
        return NULL;
    }

    return (Product)asGetFirst(order->products);
}

Product getNextProductInOrder(Order order) {
    if(!order)
    {
        return NULL;
    }

    return (Product)asGetNext(order->products);
}

double calcPrice(Order order) {
    if(!order) {
        return 0;
    }

    double price=0;
    Product iter=asGetFirst(order->products);
    while(iter) 
    {
        price+=productGetPrice(iter,productGetAmount(iter));
        iter=asGetNext(order->products);
    }

    return price;
}

OrderResult orderAddProduct(Order order, Product product, const double amount)
{
    if(!order)
    {
        return ORDER_NULL_ARGUMENT;
    }
    if(/*amount+productGetAmount(product)<0 ||*/ checkAmount(amount,productGetAmountType(product))/* || checkAmount(amount+productGetAmount(product), productGetAmountType(product))*/ /*Because thatt's the general product. we need to check against the order's product*/)
    {
        return ORDER_INVALID_AMOUNT;
    }

    //For not adding in case there is a negative amount
    if(amount<0)
    {
        return ORDER_SUCCESS;
    }
    
    Product new_product=productCopy(product);
    productSetAmount(new_product, amount);

    asRegister(order->products,new_product);
    /**/
    asChangeAmount(order->products,new_product,productGetID(product));
    /**/

    productFree(new_product);

    return ORDER_SUCCESS;
}

AmountSet orderGetProducts(Order order) {
    return order->products;
}

bool orderIsShipped(Order order)
{
    return order->shipped;
}

void orderShippedUpdate(Order order)
{
    order->shipped=true;
}