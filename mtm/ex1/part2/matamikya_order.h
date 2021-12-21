#ifndef MATAMIKYA_ORDER_H
#define MATAMIKYA_ORDER_H


#include "matamikya_product.h"
#include "amount_set.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>


typedef enum OrderResult_t {
    ORDER_SUCCESS = 0,
    ORDER_NULL_ARGUMENT,
    ORDER_OUT_OF_MEMORY,
    ORDER_INVALID_NAME,
    ORDER_INVALID_AMOUNT,
    ORDER_PRODUCT_ALREADY_EXIST,
    ORDER_PRODUCT_NOT_EXIST,
    ORDER_NOT_EXIST,
    ORDER_INSUFFICIENT_AMOUNT,
} OrderResult;

/** Type for representing an order */
typedef struct order_t *Order;


/**
 * productCreate: create a new Order.
 * @param id - new order id. Must be non-negative, and unique.
 * @return A new Order in case of success, and NULL otherwise (e.g.
 *     in case of an allocation error)
 */
Order orderCreate(unsigned int id);

/**
 * orderCopy: copy all the order's fields to a new order.
 * @param source - the order to copy from.
 * @return a new Order in case of success, and NULL otherwise.
 */
ASElement orderCopy(ASElement source);

/**
 * orderFree: free an order and all it's content from memory.
 * @param to_delete - the order to free from memory. A NULL value is
 *     allowed, and in that case the function does nothing.
 */
void orderFree(ASElement to_delete);

/**
 * orderCompare: compare between two orders' IDs.
 * @param first - the first order to compare
 * @param second - the second order to compare
 * @return
 *      positive integer - if first's ID is bigger than the second's.
 *      negative integer - if product1's ID is lower than the second's.
 *      zero - if the IDs are equal.
 */
int orderCompare(ASElement first, ASElement second);

/**
 * orderChangeProductAmount: change amount of product in order to
 * current amount + given amount.
 * @param order - the order to change it's product amount.
 * @param productId - the ID of the product to change it's amount.
 * @param amount - the amount to add to current product's amount.
 * @return
 *      ORDER_NULL_ARGUMENT - if order is NULL
 *      ORDER_INVALID_AMOUNT - if current amount+given amount<0
 *      or if given amount does not match to product's amount_type.
 *      ORDER_SUCCESS - if amount was changed successfully.
 */
OrderResult orderChangeProductAmount(Order order, const unsigned int productId, const double amount);

/**
 * orderGetID: return the order's ID into the id pointer.
 * @param order - the order to return it's ID.
 * @return true in case of success, false otherwise.
 */
bool orderGetID(Order order, unsigned int* id);

/**
 * orderGetFirstProduct: get the first product in the order.
 * @param order - the order to get it's first product.
 * @return if success, pointer to the first product in the order.
 * NULL otherwise.
 */
Product orderGetFirstProduct(Order order);

/**
 * orderGetNextProduct: get the next product in the order.
 * @param order - the order to get next product from.
 * @return if success, pointer to the next product in the order.
 * NULL otherwise.
 */
Product orderGetNextProduct(Order order);

/**
 * orderCalcPrice: total price of all the products in order.
 * the price per product is calculated with the prodPrice method.
 * @param order - the order to calculate it's total price.
 * @return if success, order's total price, calculated with prodPrice method.
 * NULL otherwise.
 */
double orderCalcPrice(Order order);

/**
 * orderAddProduct: add new product to order.
 * @param order - the order to add new product to.
 * @param product - the product to add to order.
 * @param amount - the product's amount to add to order.

 * @return
 *      ORDER_NULL_ARGUMENT - if order is NULL
 *      ORDER_INVALID_AMOUNT - if given amount does not match
 *      to product's amount_type.
 *      ORDER_SUCCESS - if product added successfully.
 */
OrderResult orderAddProduct(Order order, Product product, const double amount);

/**
 * orderGetProducts: get pointer to Products amount_set in order.
 * @param order - the order to get it's Products amount_set.
 * @return pointer to Products amount_set in order.
 */
AmountSet orderGetProducts(Order order);

/**
 * orderIsShipped: check if order is shipped.
 * @param order - the order to check if shipped.
 * @return true if order is shipped, false if isn't.
 */
bool orderIsShipped(Order order);

/**
 * orderShippedUpdate: update the order's shipped field to true.
 * @param order - the order to update shipped field.
 */
void orderShippedUpdate(Order order);

#endif //MATAMIKYA_ORDER_H