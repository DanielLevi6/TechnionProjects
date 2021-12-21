#include "order.h"


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
    if(!to_delete)
    {
        return;
    }

    asDestroy(((Order)to_delete)->products);
    free((Order)to_delete);
}

int compareOrders(ASElement first, ASElement second) {
    //We want that if there is a NULL sent to the function
    //so the AmountSet wouldn't add it to the set(as the case with an identical element)
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
        unsigned int iterator_id = productId + 1; //We want it to be different from the productId at first
        if (getProductID(iterator , &iterator_id) && iterator_id == productId) {
            if(checkAmount(amount, productGetAmountType(iterator)) == PRODUCT_INVALID_AMOUNT){
                return ORDER_INVALID_AMOUNT;
            }

            if(getProductAmount(iterator)+amount<0)
            {
                asDelete(order->products,iterator);
                return ORDER_SUCCESS;
            }

            ProductResult result = addProductAmount(iterator, amount);

            if (result == PRODUCT_NULL_ARGUMENT) {
                return ORDER_NULL_ARGUMENT;
            }
            
            return ORDER_SUCCESS;
        }
    }

    return ORDER_PRODUCT_NOT_EXIST;
}

bool getOrderID(Order order, unsigned int* id) {
    if(!order)
    {
        return NULL;
    }

    *id = order->id;
    return true;
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
    if(checkAmount(amount,productGetAmountType(product)) == PRODUCT_INVALID_AMOUNT)
    {
        return ORDER_INVALID_AMOUNT;
    }

    //For not adding in case there is a negative amount
    if(amount<0)
    {
        return ORDER_SUCCESS;
    }
    
    Product new_product=productCopy(product);
    if(!new_product)
    {
        return ORDER_OUT_OF_MEMORY;
    }

    productSetAmount(new_product, amount);

    asRegister(order->products,new_product);

    unsigned int product_id = 0; //We want it to be different from the productId at first
    getProductID(product , &product_id);
    asChangeAmount(order->products,new_product,product_id);//Ordeering the set by the id


    productFree(new_product);//After adding it to the amount set< it can be deleted

    return ORDER_SUCCESS;
}

AmountSet orderGetProducts(Order order) {
    if(!order)
    {
        return NULL;
    }

    return order->products;
}

bool orderIsShipped(Order order)
{
    if(!order)
    {
        return NULL;
    }

    return order->shipped;
}

void orderShippedUpdate(Order order)
{
    if(!order)
    {
        return;
    }

    order->shipped=true;
}