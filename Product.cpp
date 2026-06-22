#include "Product.h"
Product::Product(int productid,
                 string name,
                 string category,
                 string brand,
                 double buyingprice,
                 double sellingprice,
                 int quantity,
                 int vendorid)
{
    this->productid=productid;
    this->name=name;
    this->category=category;
    this->brand=brand;
    this->buyingprice=buyingprice;
    this->sellingprice=sellingprice;
    this->quantity=quantity;
    this->vendorid=vendorid;
}
int Product::getproductid() const
{
    return productid;
}
string Product::getname() const
{
    return name;
}
string Product::getcategory() const
{
    return category;
}
string Product::getbrand() const
{
    return brand;
}
double Product::getsellingprice() const
{
    return sellingprice;
}
int Product::getvendorid() const
{
    return vendorid;
}
int Product::currentstock() const
{
    return quantity;
}
void Product::addstock(int qty){
    (this->quantity)=(this->quantity)+qty;
}
bool Product::reducestock(int qty){
    if(quantity<qty)
        return false;
    quantity-=qty;
    return true;
}
