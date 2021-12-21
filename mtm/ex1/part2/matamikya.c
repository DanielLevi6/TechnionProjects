#include <string.h>
#include <stdlib.h>
#include <math.h>
#include "matamikya_print.h"
#include "amount_set.h"
#include "matamikya.h"
#include "matamikya_product.h"
#include "matamikya_order.h"

#define OFFSET 0.001

struct Matamikya_t {

    AmountSet products;
    AmountSet orders;

    double incomes;
    unsigned int order_counter;
};

/**
 * matamikyaCreate: create an empty Matamikya warehouse.
 */
Matamikya matamikyaCreate() 
{
    Matamikya new_storage = malloc(sizeof(*new_storage));
    if (!new_storage) {
        return NULL;
    }

    new_storage->products = asCreate(productCopy, productFree, productCompareByID);
    if(!new_storage->products) {
        matamikyaDestroy(new_storage);
        return NULL;
    }

    new_storage->orders=asCreate(orderCopy,orderFree,orderCompare);
    if(!new_storage) {
        matamikyaDestroy(new_storage);
        return NULL;        
    }

    new_storage->incomes=0;
    new_storage->order_counter=1;

    return new_storage;
}

/**
 * matamikyaDestroy: free a Matamikya warehouse, and all its contents, from memory.
 */
void matamikyaDestroy(Matamikya matamikya) 
{
    if (!matamikya) {
        return;
    }

    asDestroy(matamikya->products);
    asDestroy(matamikya->orders);

    free(matamikya);
}

/**
 * mtmNewProduct: add a new product to a Matamikya warehouse.
 */
MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice) 
{

    if(!matamikya||!name||!customData||!copyData||!freeData||!prodPrice) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    if(strlen(name)==0|| name[0]<'0'|| (name[0]>'9'&&name[0]<'A') || (name[0]>'Z'&&name[0]<'a') || name[0]>'z') {
        return MATAMIKYA_INVALID_NAME;
    }

    if(productCheckAmount(amount, amountType) == PRODUCT_INVALID_AMOUNT || amount < 0) {
        return MATAMIKYA_INVALID_AMOUNT;
    }

    Product new_product=productCreate(name,id,customData,amountType,amount,0, copyData, freeData, prodPrice);
    if(!new_product) {
        return MATAMIKYA_OUT_OF_MEMORY;
    }

    AmountSetResult result=asRegister(matamikya->products, new_product);
    
    asChangeAmount(matamikya->products,new_product,id);
    
    productFree(new_product);

    if(result==AS_OUT_OF_MEMORY) {
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    if(result==AS_ITEM_ALREADY_EXISTS) {
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    return MATAMIKYA_SUCCESS;
}

/**
 * mtmChangeProductAmount: increase or decrease the amount of an *existing* product in a Matamikya warehouse.
 * if 'amount' < 0 then this amount should be decreased from the matamikya warehouse.
 * if 'amount' > 0 then this amount should be added to the matamikya warehouse.
 * if 'amount' = 0 then nothing should be done.
 * please note:
 * If the amount to decrease is larger than the product's amount in the
 * warehouse, then the product's amount is not changed, and a proper error-code
 * is returned.
 * If the amount is equal to the product's amount in the
 * warehouse,then the product will remain inside the warehouse 
 * with amount of zero.
 */
MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount) 
{
    if(!matamikya) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    for(Product iterator=asGetFirst(matamikya->products) ; iterator ; iterator = asGetNext(matamikya->products)) {
        unsigned int iterator_id = id + 1; //We want it to be different from the id at first
        if (productGetID(iterator , &iterator_id) && iterator_id == id) {
            if(productCheckAmount(amount, productGetAmountType(iterator)) == PRODUCT_INVALID_AMOUNT || 
                productCheckAmount(amount+productGetAmount(iterator), productGetAmountType(iterator)) 
                    == PRODUCT_INVALID_AMOUNT) {
                return MATAMIKYA_INVALID_AMOUNT;
            }
            if (productGetAmount(iterator)+amount<0) {
                return MATAMIKYA_INSUFFICIENT_AMOUNT;
            }

            ProductResult result=productAddAmount(iterator,amount);

            if(result==PRODUCT_NULL_ARGUMENT) {
                return MATAMIKYA_NULL_ARGUMENT;
            }

            return MATAMIKYA_SUCCESS;
        }
    }

    return MATAMIKYA_PRODUCT_NOT_EXIST;
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id) 
{
    if(!matamikya) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    for(Order iterator=asGetFirst(matamikya->orders);iterator;iterator=asGetNext(matamikya->orders)) {
        for(Product product_iterator=asGetFirst(orderGetProducts(iterator));
                product_iterator;product_iterator=asGetNext(orderGetProducts(iterator))) {

            unsigned int iterator_id = id + 1; //We want it to be different from the id at first
            if (productGetID(product_iterator , &iterator_id) && iterator_id == id) {
                asDelete(orderGetProducts(iterator),product_iterator);
                break;
            }
        }
    }

    for(Product iterator=asGetFirst(matamikya->products);iterator;iterator=asGetNext(matamikya->products)) {
        unsigned int iterator_id = id + 1; //We want it to be different from the id at first
        if (productGetID(iterator , &iterator_id) && iterator_id == id) {
            matamikya->incomes-=productGetTotalIncomes(iterator);
            asDelete(matamikya->products,iterator);
            return MATAMIKYA_SUCCESS;
        }
    }
    return MATAMIKYA_PRODUCT_NOT_EXIST;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya)
{
    if(!matamikya) {
        return 0;
    }
    Order new_order = orderCreate(matamikya->order_counter);
    if (!new_order) {
        return 0;
    }

    asRegister(matamikya->orders, new_order);

    unsigned int order_id = 0; //We want it to be different from the productId at first
    orderGetID(new_order , &order_id);
    asChangeAmount(matamikya->orders,new_order,order_id);//Ordering the set by the id

    orderFree(new_order);

    return matamikya->order_counter++;
}

static Order searchInOrders(Matamikya matamikya, const unsigned int order_id)
{
    if(!matamikya) {
        return NULL;
    }

    for(Order iterator=asGetFirst(matamikya->orders);iterator;iterator=asGetNext(matamikya->orders)) {
        unsigned int iterator_id = order_id + 1; //We want it to be different from the productId at first
        if(orderGetID(iterator , &iterator_id) && iterator_id == order_id && !orderIsShipped(iterator)) {
            return iterator;
        }
    }
    return NULL;
}

static Product searchInProducts(Matamikya matamikya, const unsigned int product_id)
{
    if(!matamikya) {
        return NULL;
    }

    for(Product iterator=asGetFirst(matamikya->products);iterator;iterator=asGetNext(matamikya->products)) {
        unsigned int iterator_id = product_id + 1; //We want it to be different from the productId at first
        if (productGetID(iterator , &iterator_id) && iterator_id == product_id) {
            return iterator;
        }
    }
    return NULL;
}

MatamikyaResult mtmorderChangeProductAmount(Matamikya matamikya, const unsigned int orderId,
                                              const unsigned int productId, const double amount)
{
    if(!matamikya) {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    
    Order order=searchInOrders(matamikya, orderId);
    OrderResult result = orderChangeProductAmount(order, productId, amount);
    if(result==ORDER_NULL_ARGUMENT) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    else if (result==ORDER_INVALID_AMOUNT) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    Product product=searchInProducts(matamikya,productId);
    if(result==ORDER_PRODUCT_NOT_EXIST) {
        
        if(product) {
            if(amount==0) {
                return MATAMIKYA_SUCCESS;
            }

            result = orderAddProduct(order,product,amount);
            if(result==ORDER_INVALID_AMOUNT) {
                return MATAMIKYA_INVALID_AMOUNT;
            }
            return MATAMIKYA_SUCCESS;
        }
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }

    return MATAMIKYA_SUCCESS;

}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId) 
{
    if(!matamikya) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    Order order=searchInOrders(matamikya,orderId);
    if(!order) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    for(Product iterator=orderGetFirstProduct(order);iterator;iterator=orderGetNextProduct(order)) {
        unsigned int iterator_id = 0;
        productGetID(iterator , &iterator_id);
        Product warehouse_product=searchInProducts(matamikya,iterator_id);
        double warehouse_product_amount=productGetAmount(warehouse_product);
        if(productGetAmount(iterator)>warehouse_product_amount) {
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
    }

    for(Product iterator=orderGetFirstProduct(order);iterator;iterator=orderGetNextProduct(order)) {
        unsigned int iterator_id = 0;
        productGetID(iterator , &iterator_id);
        Product warehouse_product=searchInProducts(matamikya,iterator_id);
        double amount_to_decrease=productGetAmount(iterator);
        double incomes=productGetPrice(warehouse_product,amount_to_decrease);
        matamikya->incomes+=incomes;
        productAddIncomes(warehouse_product,incomes);

        productSetAmount(warehouse_product,productGetAmount(warehouse_product)-amount_to_decrease);
    }

    orderShippedUpdate(order);

    return MATAMIKYA_SUCCESS;

}

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId) 
{
    if(!matamikya) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    Order to_delete=searchInOrders(matamikya,orderId);
    if(!to_delete) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    AmountSetResult result=asDelete(matamikya->orders,to_delete);
    if(result==AS_NULL_ARGUMENT) {
        return MATAMIKYA_NULL_ARGUMENT;
    } else if(result==AS_ITEM_DOES_NOT_EXIST) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    } else {
        return MATAMIKYA_SUCCESS;
    }
}

MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output) 
{
    if(!matamikya||!output) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    fprintf(output,"Inventory Status:\n");
    Product iter=asGetFirst(matamikya->products);
    while(iter) {
        unsigned int product_id = 0;
        productGetID(iter , &product_id);
        mtmPrintProductDetails(productGetName(iter),product_id,
                                productGetAmount(iter),productGetPricePerUnit(iter),output);
        iter=asGetNext(matamikya->products);
    }

    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output) 
{
    if(!matamikya||!output) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    Order found=searchInOrders(matamikya,orderId);
    if(!found) {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }

    mtmPrintOrderHeading(orderId,output);
    
    Product iter=asGetFirst(orderGetProducts(found));
    while(iter) {
        unsigned int product_id = 0;
        productGetID(iter , &product_id);
        mtmPrintProductDetails(productGetName(iter),product_id,productGetAmount(iter),
                                productGetPrice(iter,productGetAmount(iter)),output);
        iter=asGetNext(orderGetProducts(found));
    }

    mtmPrintOrderSummary(orderCalcPrice(found), output);

    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output) 
{
    if(!matamikya||!output) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    fprintf(output,"Best Selling Product:\n");
    
    Product iter=asGetFirst(matamikya->products);
    if(iter==NULL) {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }
    bool products_not_sold=true;

    double max_incomes=productGetTotalIncomes(iter);
    
    while(iter) {
        if(max_incomes < productGetTotalIncomes(iter)) {
            max_incomes=productGetTotalIncomes(iter);
        }
        iter=asGetNext(matamikya->products);
    }

    iter=asGetFirst(matamikya->products);
    while(iter) {
        if(max_incomes > 0 && (max_incomes-productGetTotalIncomes(iter)<=OFFSET) &&
                                 (max_incomes-productGetTotalIncomes(iter)>=-OFFSET)) {
            unsigned int product_id = 0;
            productGetID(iter , &product_id);
            mtmPrintIncomeLine(productGetName(iter),product_id,productGetTotalIncomes(iter),output);
            products_not_sold=false;
            break;
        }
        iter=asGetNext(matamikya->products);
    }

    if(products_not_sold) {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }

    return MATAMIKYA_SUCCESS;
}