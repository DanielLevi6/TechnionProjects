#include "matamikya_product.h"

struct Product_t {
    char* name;
    unsigned int id;
    ProductData data;
    ProductAmountType amount_type;
    double amount;
    double total_incomes;

    CopyData copyData;
    FreeData freeData;
    GetProductPrice prodPrice;
};

/**
 * productCreate: create a new Product.
 */
Product productCreate(const char* name, unsigned int id, ProductData data, ProductAmountType amount_type,
                     double amount, double total_incomes, CopyData copyData,
                     FreeData freeData, GetProductPrice prodPrice)
{
    if(!name || !data || !copyData || !freeData || !prodPrice) {
        return NULL;
    }

    Product new_product=malloc(sizeof(*new_product));
    if(!new_product) {
        return NULL;
    }

    new_product->name=malloc(strlen(name)+1);
    if(!new_product->name) {
        free(new_product);
        return NULL;
    }

    strcpy(new_product->name,name);

    new_product->id=id;
    new_product->amount_type=amount_type;
    new_product->amount=amount;
    new_product->total_incomes=total_incomes;
    new_product->copyData=copyData;
    new_product->freeData=freeData;
    new_product->prodPrice=prodPrice;

    new_product->data=copyData(data);

    return new_product;
}

/**
 * productCopy: copy all the product's fields to a new Product.
 */
ASElement productCopy(ASElement product)
{
    if(!((Product)product)) {
        return NULL;
    }

    return productCreate(((Product)product)->name, ((Product)product)->id, ((Product)product)->data,
             ((Product)product)->amount_type, ((Product)product)->amount, ((Product)product)->total_incomes,
              ((Product)product)->copyData, ((Product)product)->freeData, ((Product)product)->prodPrice);

}

/**
 * productFree: free a product and all it's content from memory.
 */
void productFree(ASElement product)
{
    if(!((Product)product)) {
        return;
    }

    ((Product)product)->freeData(((Product)product)->data);
    free(((Product)product)->name);
    free(((Product)product));
}

/**
 * productCompareByID: compare between two products' IDs.
 */
int productCompareByID(ASElement product1, ASElement product2)
{
    //We want that if there is a NULL sent to the function
    //so the AmountSet wouldn't add it to the set(as the case with an identical element)
    if(!((Product)product1) || !((Product)product2)) {
        return 0;
    }

    return (((Product)product1)->id)-(((Product)product2)->id);
}

/**
 * productGetID: return the Product's ID.
 */
bool productGetID(Product product, unsigned int* id)
{
    if(!product) {
        return false;
    }

    *id = product->id;
    return true;
}

/**
 * productAddAmount: add amount to product's current amount.
 */
ProductResult productAddAmount(Product product, const double amount)
{
    if(!product) {
        return PRODUCT_NULL_ARGUMENT;
    }

    if(product->amount + amount < 0) {
        return PRODUCT_INSUFFICIENT_AMOUNT;
    }

    product->amount+=amount;
    return PRODUCT_SUCCESS;
}

/**
 * productGetData: get product's data.
 */
ProductData productGetData(Product product) 
{
    if(!product) {
        return NULL;
    }

    return product->data;
}

/**
 * productAddIncomes: update product's total_incomes.
 */
void productAddIncomes(Product product, double incomes) 
{
    if(!product) {
        return;
    }

    product->total_incomes+=incomes;
}

/**
 * productGetPrice: get product's calculated price.
 */
double productGetPrice (Product product, const double amount)
{
    if(!product) {
        return ERROR;
    }

    return product->prodPrice(product->data,amount);
}

/**
 * productGetAmount: get product's current amount.
 */
double productGetAmount(Product product) 
{
    if(!product) {
        return ERROR;
    }

    return product->amount;
}

/**
 * productGetName: get product's name.
 */
char* productGetName(Product product) 
{
    if(!product) {
        return NULL;
    }

    return product->name;
}

/**
 * productGetPricePerUnit: get product's price per 1 unit.
 */
double productGetPricePerUnit(Product product) 
{
    if(!product) {
        return ERROR;
    }

    return (((Product)product)->prodPrice)(((Product)product)->data,1);
}

/**
 * productGetTotalIncomes: get product's total incomes.
 */
double productGetTotalIncomes(Product product) 
{
    if(!product) {
        return ERROR;
    }

    return product->total_incomes;
}

/**
 * productGetAmountType: get product's amount_type,
 */
ProductAmountType productGetAmountType(Product product) 
{
    if(!product) {
        return ERROR;
    }

    return product->amount_type;
}

/**
 * productSetAmount: update product's amount to the given amount.
 */
void productSetAmount(Product new_product, double amount)
{
    if(!new_product || amount < 0) {
        return;
    }

    new_product->amount=amount;
}

/**
 * productCheckAmount: check if the given amount matches to the product's amount type,
 * with deviation of 0.001.
 */
ProductResult productCheckAmount(const double amount, const ProductAmountType amountType) 
{

    double sub_amount=amount-(double)floor(amount);

    if ((amountType==PRODUCT_INTEGER_AMOUNT&& (sub_amount>AMOUNT_OFFSET && sub_amount<(1-AMOUNT_OFFSET))) ||
       (amountType==PRODUCT_HALF_INTEGER_AMOUNT && (sub_amount>(0.5+AMOUNT_OFFSET) && sub_amount<(1-AMOUNT_OFFSET))) ||
       (amountType==PRODUCT_HALF_INTEGER_AMOUNT && (sub_amount<(0.5-AMOUNT_OFFSET) && sub_amount>AMOUNT_OFFSET))) {
           return PRODUCT_INVALID_AMOUNT;
       }
    
    return PRODUCT_SUCCESS;
}