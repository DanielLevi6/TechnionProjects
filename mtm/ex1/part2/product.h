#ifndef MATAMIKYA_PRODUCT_H
#define MATAMIKYA_PRODUCT_H


#include <stdlib.h>
#include <string.h>
#include "amount_set.h"
#include <math.h>

#define AMOUNT_OFFSET 0.001
#define ERROR -1


/** Type for specifying what is a valid amount for a product.
 * For a PRODUCT_INTEGER_AMOUNT product, a valid amount is an amount which is
 * within 0.001 of an integer.
 * For a PRODUCT_HALF_INTEGER_AMOUNT product, a valid amount is an amount which is
 * within 0.001 of a half-integer.
 * For PRODUCT_ANY_AMOUNT, any amount is valid.
 */
typedef enum ProductAmountType_t {
    PRODUCT_INTEGER_AMOUNT,
    PRODUCT_HALF_INTEGER_AMOUNT,
    PRODUCT_ANY_AMOUNT,
} ProductAmountType;

typedef enum ProductResult_t {
    PRODUCT_SUCCESS = 0,
    PRODUCT_NULL_ARGUMENT,
    PRODUCT_INVALID_AMOUNT,
    PRODUCT_INSUFFICIENT_AMOUNT,
} ProductResult;

/** Type for representing a Product */
typedef struct Product_t *Product;

/** Type for additional costume data of a product */
typedef void *ProductData;

/**
 * Type of function for copying a product's custom data.
 *
 * Such a function receives a ProductData, creates a new ProductData
 * object, and returns a pointer to the new object. If the function fails for
 * any reason, it returns PRODUCT_NULL_ARGUMENT.
 */
typedef ProductData (*CopyData)(ProductData);

/**
 * Type of function for freeing a product's custom data.
 *
 * Such a function receives a ProductData object and frees it. The
 * ProductData can be NULL, in which case the function does nothing.
 */
typedef void (*FreeData)(ProductData);

/**
 * Type of function for calculating the price of a product.
 *
 * Such a function receives the product's custom data (a ProductData) and an
 * amount (a double), and returns the price (a double) of purchasing the given
 * quantity of the given product.
 */
typedef double (*GetProductPrice)(ProductData, const double amount);


/**
 * productCreate: create a new Product.
 * @param name - name of the product. Must be non-empty.
 * @param id - new product id. Must be non-negative, and unique.
 * @param data - additional costume data for the product.
 * @param amount_type - defines what are valid amounts for this product.
 * @param amount - the initial amount of the product.
 * @param total_incomes - total incomes of the product.
 * @param copyData - function pointer to be used for copying product's additional
 *      data.
 * @param freeData - function pointer to be used for free product data.
 * @param prodPrice - function pointer to be used for getting the price of some
 *      product.
 * @return A new Product in case of success, and NULL otherwise (e.g.
 *     in case of an allocation error)
 */
Product productCreate(const char* name, unsigned int id, ProductData data, ProductAmountType amount_type,
                      double amount, double total_incomes, CopyData copyData,
                      FreeData freeData, GetProductPrice prodPrice);

/**
 * productCopy: copy all the product's fields to a new Product.
 * @param product - the product to copy from.
 * @return a new Product in case of success, and NULL otherwise.
 */
ASElement productCopy(ASElement product);

/**
 * productFree: free a product and all it's content from memory.
 * @param product - the product to free from memory. A NULL value is
 *     allowed, and in that case the function does nothing.
 */
void productFree(ASElement product);

/**
 * productCompareByID: compare between two products' IDs.
 * @param product1 - the first product to compare
 * @param product2 - the second product to compare
 * @return
 *      positive integer - if product1's ID is bigger than product2's ID.
 *      negative integer - if product1's ID is lower than product2's ID.
 *      zero - if the IDs are equal or one of the parameters is NULL.
 */
int productCompareByID(ASElement product1, ASElement product2);

/**
 * getProductID: return the Product's ID.
 * @param product - the product to return it's ID.
 * 		  id - the pointer that will hold the product's id
 * @return true in case of success, and false otherwise.
 */
bool getProductID(Product product, unsigned int* id);

/**
 * getProductAmount: return the Product's amount.
 * @param product - the product to return it's amount.
 * @return the product's amount in case of success, -1 otherwise.
 */
double getProductAmount(Product product);

/**
 * addProductAmount: add amount to product's current amount.
 * @param product - the product to change it's amount.
 * @param amount - the amount to add to current product's amount.
 * @return
 *      PRODUCT_NULL_ARGUMENT - if product is NULL
 *      PRODUCT_INSUFFICIENT_AMOUNT - if the amount of the product is smaller then what we need to reduce
 *      PRODUCT_SUCCESS - if amount was changed successfully.
 */
ProductResult addProductAmount(Product product, const double amount);

/**
 * productGetData: get product's data.
 * @param product - the product to get it's data.
 * @return pointer to product's data in case of success, and NULL otherwise.SS
 */
ProductData productGetData(Product product);

/**
 * productAddIncomes: update product's total_incomes.
 * add current total incomes with given incomes.
 * @param product - the product to update it's total incomes.
 * @param product - the given income to add with current
 * products' total incomes.
 */
void productAddIncomes(Product product, double incomes);

/**
 * productGetPrice: get product's calculated price.
 * the price is being calculated with the prodPrice method.
 * @param amount - the quantity of the given product to calculate.
 * @return product's price which was calculated with prodPrice method in case of success, and -1 otherwise.
 */
double productGetPrice (Product product, const double amount);

/**
 * productGetAmount: get product's current amount.
 * @param product - the product to get it's amount.
 * @return product's current amount in case of success, and -1 otherwise.
 */
double productGetAmount(Product product);

/**
 * productGetName: get product's name.
 * @param product - the product to get it's name.
 * @return product's name in case of success, and NULL otherwise.
 */
char* productGetName(Product product);

/**
 * productGetPricePerUnit: get product's price per 1 unit.
 * @param product - the product to get it's price per unit.
 * @return product's price per 1 unit in case of success, and -1 otherwise.
 */
double productGetPricePerUnit(Product product);

/**
 * productGetTotalIncomes: get product's total incomes.
 * @param product - the product to get it's total incomes.
 * @return product's total incomes in case of success, and -1 otherwise.
 */
double productGetTotalIncomes(Product product);

/**
 * productGetAmountType: get product's amount_type,
 * specifying what is a valid amount for a product.
 * PRODUCT_INTEGER_AMOUNT - a valid amount is an amount which is
 * within 0.001 of an integer.
 * PRODUCT_HALF_INTEGER_AMOUNT - a valid amount is an amount which is
 * within 0.001 of a half-integer.
 * PRODUCT_ANY_AMOUNT - any amount is valid.
 * @param product - the product to get it's amount_type.
 * @return product's amount_type in case of success, and -1 otherwise.
 */
ProductAmountType productGetAmountType(Product product);

/**
 * productSetAmount: update product's amount to the given amount.
 * @param product - the product to update it's amount.
 * @param amount - the amount to update the product's amount to.
 */
void productSetAmount(Product new_product, double amount);

/**
 * checkAmount: check if the given amount matches to the product's amount type,
 * with deviation of 0.001.
 * @param amount - the amount to check if matches to the product's amount_type.
 * @param amountType - specifying what is a valid amount for a product.
 * PRODUCT_INTEGER_AMOUNT - a valid amount is an amount which is
 * within 0.001 of an integer.
 * PRODUCT_HALF_INTEGER_AMOUNT - a valid amount is an amount which is
 * within 0.001 of a half-integer.
 * PRODUCT_ANY_AMOUNT - any amount is valid.
 * @return
 *      PRODUCT_SUCCESS - if the given amount matches to the product's amount type
 *      with deviation of 0.001.
 *      PRODUCT_INVALID_AMOUNT - otherwise.
 */
ProductResult checkAmount(const double amount, const ProductAmountType amountType);

#endif //MATAMIKYA_PRODUCT_H