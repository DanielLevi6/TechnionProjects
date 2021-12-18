#include "product.h"
#include <stdlib.h>
#include <string.h>
#include "amount_set.h"
#include <math.h>

#define AMOUNT_OFFSET 0.001

struct Product_t {
    char* name;
    unsigned int id;
    //price in data
    ProductData data;
    ProductAmountType amount_type;
    double amount;
    double total_incomes;

    CopyData copyData;
    FreeData freeData;
    GetProductPrice prodPrice;
};

Product productCreate(const char* name, unsigned int id, ProductData data, ProductAmountType amount_type,
                     double amount, unsigned int total_incomes, CopyData copyData,
                     FreeData freeData, GetProductPrice prodPrice)
{
    if(!name || !data)
    {
        return NULL;
    }

    Product new_product=malloc(sizeof(*new_product));
    if(!new_product)
    {
        return NULL;
    }

    new_product->name=malloc(strlen(name)+1);
    if(!new_product->name)
    {
        free(new_product);
        return NULL;
    }

    strcpy(new_product->name,name);
    if(!new_product->name)
    {
        free(new_product->name);
        free(new_product);
        return NULL;
    }

    new_product->id=id;
    new_product->amount_type=amount_type;
    new_product->amount=amount;
    new_product->total_incomes=total_incomes;
    new_product->copyData=copyData;
    new_product->freeData=freeData;
    new_product->prodPrice=prodPrice;

    //new_product->data=malloc(sizeof(data));
    new_product->data=copyData(data);

    return new_product;
}


ASElement productCopy(ASElement product)
{
    if(!((Product)product))
    {
        return NULL;
    }

    // char* new_name=malloc(strlen(((Product)product)->name)+1);
    // if(!new_name)
    // {
    //     return NULL;
    // }
    // strcpy(new_name,((Product)product)->name);


//    ProductData new_data = ((Product)product)->copyData(((Product)product)->data);
    // if (!new_data){
    //     free(new_name);
    //     return NULL;
    // }

    return productCreate(((Product)product)->name, ((Product)product)->id, ((Product)product)->data, ((Product)product)->amount_type, ((Product)product)->amount, ((Product)product)->total_incomes, ((Product)product)->copyData, ((Product)product)->freeData, ((Product)product)->prodPrice);

}

void productFree(ASElement product)
{
    if(!((Product)product))
    {
        return;
    }
    //Maybe?
    ((Product)product)->freeData(((Product)product)->data);
    free(((Product)product)->name);
    free(((Product)product));
}

int productCompareByName(Product product1, Product product2)
{
    if(!product1 || !product2)
    {
        return 0;
    }

    return strcmp(product1->name,product2->name);
}

int productCompareByID(ASElement product1, ASElement product2)
{
    if(!((Product)product1) || !((Product)product2))
    {
        return 0;
    }

    return (((Product)product1)->id)-(((Product)product2)->id);
}

unsigned int getProductID(Product product)
{
    if(!product)
    {
        return -1;
    }

    return product->id;
}

double getProductAmount(Product product)
{
    if(!product)
    {
        return -1;
    }

    return product->amount;
}

ProductResult addProductAmount(Product product, const double amount)
{
    if(!product)
    {
        return PRODUCT_NULL_ARGUMENT;
    }

    // if(product->amount+amount < 0)
    // {
    //     return PRODUCT_INSUFFICIENT_AMOUNT;
    // }

    product->amount+=amount;
    return PRODUCT_SUCCESS;
}
/********************************************************/
// ProductData productCopyData(ProductData data){
//     ProductData new_data=malloc(sizeof(*(double*)data));
//     if(!new_data)
//     {
//         return NULL;
//     }
//     memcpy(new_data,data,sizeof(*(double*)data));
//     return new_data;
// }

ProductData productGetData(Product product) {
    return product->data;
}

void productAddIncomes(Product product, unsigned int incomes) {
    if(!product) {
        return;
    }
    product->total_incomes+=incomes;
}

// void productFreeData(ProductData data){
//     if(data==NULL) {
//         return;
//     }
//     free((double*)data);
// }

double productGetPrice (Product product, const double amount){
    /*Add Check if Discount*/
    return product->prodPrice(product->data,amount);
}

// double basicGetPrice(ProductData basePrice, double amount){
//         return (*(double*)basePrice) * amount;
// }

double productGetAmount(Product product) {
    return product->amount;
}

char* productGetName(Product product) {
    return product->name;
}

unsigned int productGetID(Product product) {
    return product->id;
}

double productGetPricePerUnit(Product product) {
    return (((Product)product)->prodPrice)(((Product)product)->data,1);
}

double productGetTotalIncomes(Product product) {
    return product->total_incomes;
}

ProductAmountType productGetAmountType(Product product) {
    return product->amount_type;
}

void productSetAmount(Product new_product, double amount)
{
    if(!new_product)
    {
        return;
    }

    new_product->amount=amount;
}

// should add the case of checking amount and the added amount separately
bool checkAmount(const double amount, const ProductAmountType amountType) {

    double sub_amount=amount-floor(amount);

    return ((amountType==PRODUCT_INTEGER_AMOUNT&& (sub_amount>AMOUNT_OFFSET && sub_amount<(1-AMOUNT_OFFSET))) ||
       (amountType==PRODUCT_HALF_INTEGER_AMOUNT && (sub_amount>(0.5+AMOUNT_OFFSET) && sub_amount<(1-AMOUNT_OFFSET))) ||
       (amountType==PRODUCT_HALF_INTEGER_AMOUNT && (sub_amount<(0.5-AMOUNT_OFFSET) && sub_amount>AMOUNT_OFFSET)));
}