#ifndef PRODUCT_H
#define PRODUCT_H
#include <string>
using namespace std;
class Admin;
class Product{
private:
    int productid;
    string name;
    string category;
    string brand;
    double buyingprice;
    double sellingprice;
    int quantity;
    int vendorid;
    friend class Admin;
public:
    Product(int productid,
            string name,
            string category,
            string brand,
            double buyingprice,
            double sellingprice,
            int quantity,
            int vendorid);
    int getproductid() const;
    string getname() const;
    string getcategory() const;
    string getbrand() const;
    double getsellingprice() const;
    int getvendorid() const;
    int currentstock() const;
    void addstock(int qty);
    bool reducestock(int qty);
};
#endif