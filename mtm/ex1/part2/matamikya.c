#include <stdlib.h>
#include "matamikya.h"
#include "amount_set.h"
#include "product.h"
#include <string.h>
#include <math.h>
#include "order.h"
#include "set.h"
#include "matamikya_print.h"

//#define AMOUNT_OFFSET 0.1

struct Matamikya_t {
    double incomes;
    AmountSet products;
    AmountSet orders;

    unsigned int order_counter;
};

Matamikya matamikyaCreate() {
    Matamikya new_storage = malloc(sizeof(*new_storage));
    if (!new_storage) {
        return NULL;
    }

    new_storage->products = asCreate(productCopy, productFree, productCompareByID);
    if(!new_storage->products) {
        matamikyaDestroy(new_storage);
        return NULL;
    }
    new_storage->orders=asCreate(copyOrder,freeOrder,compareOrders);
    new_storage->order_counter=1;
    new_storage->incomes=0;
    return new_storage;
}

void matamikyaDestroy(Matamikya matamikya) {
    if (!matamikya){
        return;
    }

    asDestroy(matamikya->orders);
    asDestroy(matamikya->products);
    free(matamikya);
}
// // should add the case of checking amount and the added amount separately
// static bool checkAmount(const double amount, const MatamikyaAmountType amountType) {

//     double sub_amount=amount-floor(amount);

//     return ((amountType==MATAMIKYA_INTEGER_AMOUNT&& (sub_amount>AMOUNT_OFFSET && sub_amount<(1-AMOUNT_OFFSET))) ||
//        (amountType==MATAMIKYA_HALF_INTEGER_AMOUNT && (sub_amount>(0.5+AMOUNT_OFFSET) && sub_amount<(1-AMOUNT_OFFSET))) ||
//        (amountType==MATAMIKYA_HALF_INTEGER_AMOUNT && (sub_amount<(0.5-AMOUNT_OFFSET) && sub_amount>AMOUNT_OFFSET)));
// }

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice) {
    if(!matamikya||!name||!customData||!copyData||!freeData||!prodPrice) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    if(strlen(name)==0|| name[0]<'0'|| (name[0]>'9'&&name[0]<'A') || (name[0]>'Z'&&name[0]<'a') || name[0]>'z')
    {
        return MATAMIKYA_INVALID_NAME;
    }

    if(checkAmount(amount, amountType) /*check if right*/|| amount<0)
    {
        return MATAMIKYA_INVALID_AMOUNT;
    }

    Product new_product=productCreate(name,id,customData,amountType,amount,0, copyData, freeData, prodPrice);
    if(!new_product)
    {
        return MATAMIKYA_OUT_OF_MEMORY;
    }

    AmountSetResult result=asRegister(matamikya->products, new_product);
    /**/
    asChangeAmount(matamikya->products,new_product,productGetID(new_product));
    /**/
    productFree(new_product);

    if(result==AS_NULL_ARGUMENT || result==AS_OUT_OF_MEMORY)
    {
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    if(result==AS_ITEM_ALREADY_EXISTS)
    {
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    return MATAMIKYA_SUCCESS;
}

//recheck
MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount) {
    if(!matamikya)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    for(Product iterator=asGetFirst(matamikya->products) ; iterator ; iterator = asGetNext(matamikya->products))
    {
        if(getProductID(iterator)==id)
        {
            if(checkAmount(amount, productGetAmountType(iterator)) || checkAmount(amount+productGetAmount(iterator), productGetAmountType(iterator)))
            {
                return MATAMIKYA_INVALID_AMOUNT;
            }
            if (productGetAmount(iterator)+amount<0) {
                return MATAMIKYA_INSUFFICIENT_AMOUNT;
            }
            ProductResult result=addProductAmount(iterator,amount); //Can be cchanged to a set operation

            if(result==PRODUCT_NULL_ARGUMENT)
            {
                return MATAMIKYA_NULL_ARGUMENT;
            }
            // else if(result==PRODUCT_INSUFFICIENT_AMOUNT)
            // {
            //     return MATAMIKYA_INSUFFICIENT_AMOUNT;
            // }
            return MATAMIKYA_SUCCESS;
        }
    }

    return MATAMIKYA_PRODUCT_NOT_EXIST;
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id) {
    if(!matamikya)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    for(Order iterator=asGetFirst(matamikya->orders);iterator;iterator=asGetNext(matamikya->orders))
    {
        /*There are more efficient ways to do that*/
        for(Product product_iterator=asGetFirst(orderGetProducts(iterator));product_iterator;product_iterator=asGetNext(orderGetProducts(iterator)))
        {
            if(getProductID(product_iterator)==id)
            {
                asDelete(orderGetProducts(iterator),product_iterator);
                break;
            }
        }
    }

    for(Product iterator=asGetFirst(matamikya->products);iterator;iterator=asGetNext(matamikya->products))
    {
        if(getProductID(iterator)==id){
            matamikya->incomes-=productGetTotalIncomes(iterator); // 19/12 6:13
            asDelete(matamikya->products,iterator);
            return MATAMIKYA_SUCCESS;
        }
    }
    return MATAMIKYA_PRODUCT_NOT_EXIST;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya){
    if(!matamikya){
        return 0;
    }
    Order new_order = createOrder(matamikya->order_counter);
    if (!new_order){
        return 0;
    }

    asRegister(matamikya->orders, new_order);
    /**/
    asChangeAmount(matamikya->orders, new_order, getOrderID(new_order));
    /**/
    freeOrder(new_order);
    return matamikya->order_counter++;
}

static Order searchInOrders(Matamikya matamikya, const unsigned int orderId){
    if(!matamikya)
    {
        return NULL;
    }

    for(Order iterator=asGetFirst(matamikya->orders);iterator;iterator=asGetNext(matamikya->orders))
    {
        if(getOrderID(iterator)==orderId && !orderIsShipped(iterator)/*Added by daniel 5:49 19/12*/){
            return iterator;
        }
    }
    return NULL;
}

static Product searchInProducts(Matamikya matamikya, const unsigned int productId){
    if(!matamikya)
    {
        return NULL;
    }

    for(Product iterator=asGetFirst(matamikya->products);iterator;iterator=asGetNext(matamikya->products))
    {
        if(getProductID(iterator)==productId){
            return iterator;
        }
    }
    return NULL;
}

//recheck
MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                                              const unsigned int productId, const double amount){
    if(!matamikya){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    
    Order order=searchInOrders(matamikya, orderId);
    OrderResult result = changeProductAmountInOrder(order, productId, amount);
    if(result==ORDER_NULL_ARGUMENT)
    {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    else if (result==ORDER_INVALID_AMOUNT){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    Product product=searchInProducts(matamikya,productId);
    if(result==ORDER_PRODUCT_NOT_EXIST)
    {
        
        if(product)
        {
            /*****************************************************/
            //9/12 6:04

            if(amount==0)
            {
                return MATAMIKYA_SUCCESS;
            }

            /*****************************************************/
            result = orderAddProduct(order,product,amount);
            if(result==ORDER_INVALID_AMOUNT)
            {
                return MATAMIKYA_INVALID_AMOUNT;
            }
            return MATAMIKYA_SUCCESS;
        }
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }

    //might be a problem. we need to check this in the product of the order. not the general product
    // if(checkAmount(amount,productGetAmountType(product)) || checkAmount(amount+productGetAmount(product), productGetAmountType(product)))
    // {
    //     return MATAMIKYA_INVALID_AMOUNT;
    // }


    // if(result==ORDER_INSUFFICIENT_AMOUNT)
    // {
    //     return MATAMIKYA_INSUFFICIENT_AMOUNT;
    // }
    return MATAMIKYA_SUCCESS;

}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId) {
    if(!matamikya)
    {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    Order order=searchInOrders(matamikya,orderId);
    if(!order)
    {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    for(Product iterator=getFirstProductInOrder(order);iterator;iterator=getNextProductInOrder(order)) {
        Product warehouse_product=searchInProducts(matamikya,getProductID(iterator));
        double warehouse_product_amount=productGetAmount(warehouse_product);
        if(getProductAmount(iterator)>warehouse_product_amount) {
            return MATAMIKYA_INSUFFICIENT_AMOUNT;
        }
    }

    for(Product iterator=getFirstProductInOrder(order);iterator;iterator=getNextProductInOrder(order)) {
        Product warehouse_product=searchInProducts(matamikya,getProductID(iterator));// if NULL
        double amount_to_decrease=getProductAmount(iterator);
        double incomes=productGetPrice(warehouse_product,amount_to_decrease);
        matamikya->incomes+=incomes;
        productAddIncomes(warehouse_product,incomes);

        productSetAmount(warehouse_product,getProductAmount(warehouse_product)-amount_to_decrease);
    }

    orderShippedUpdate(order);

    //The Error
    //freeOrder((ASElement)order);

    return MATAMIKYA_SUCCESS;

}

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId) {
    if(!matamikya) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    Order to_delete=searchInOrders(matamikya,orderId);
    if(!to_delete)
    {
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    AmountSetResult result=asDelete(matamikya->orders,to_delete);
    if(result==AS_NULL_ARGUMENT) {
        return MATAMIKYA_NULL_ARGUMENT;
    } else if(result==AS_ITEM_DOES_NOT_EXIST) {//not neccessary. if it won't find the order it will exit in the previous if
        return MATAMIKYA_ORDER_NOT_EXIST;
    } else {
        return MATAMIKYA_SUCCESS;
    }
}

MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output) {
    if(!matamikya||!output) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    fprintf(output,"Inventory Status:\n");
    Product iter=asGetFirst(matamikya->products);
    while(iter) {
        mtmPrintProductDetails(productGetName(iter),productGetID(iter),productGetAmount(iter),productGetPricePerUnit(iter),output);
        iter=asGetNext(matamikya->products);
    }

    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output) {
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
        mtmPrintProductDetails(productGetName(iter),productGetID(iter),productGetAmount(iter),productGetPrice(iter,productGetAmount(iter)),output);
        iter=asGetNext(orderGetProducts(found));
    }

    mtmPrintOrderSummary(calcPrice(found), output);

    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output) {
    if(!matamikya||!output) {
        return MATAMIKYA_NULL_ARGUMENT;
    }

    fprintf(output,"Best Selling Product:\n");
    
    Product iter=asGetFirst(matamikya->products);
    if(iter==NULL) {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }
    bool productsNotSold=true;

    double max_incomes=productGetTotalIncomes(iter);
    
    while(iter) {
        if(max_incomes < productGetTotalIncomes(iter)) {
            max_incomes=productGetTotalIncomes(iter);
        }
        iter=asGetNext(matamikya->products);
    }

    iter=asGetFirst(matamikya->products);
    while(iter) {
        if(max_incomes > 0 && (max_incomes-productGetTotalIncomes(iter)<=0.001) && (max_incomes-productGetTotalIncomes(iter)>=-0.001)) {
            mtmPrintIncomeLine(productGetName(iter),productGetID(iter),productGetTotalIncomes(iter),output);
            productsNotSold=false;
            break;
        }
        iter=asGetNext(matamikya->products);
    }

    if(productsNotSold)
    {
        fprintf(output, "none\n");
        return MATAMIKYA_SUCCESS;
    }

    return MATAMIKYA_SUCCESS;
}