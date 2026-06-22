#ifndef VENDOR_H
#define VENDOR_H
#include <string>
using namespace std;
class Vendor
{
private:
    int vendorid;
    string vendorname;
    string contactnumber;
    string address;
    string status;
public:
    Vendor(int vendorid,
           string vendorname,
           string contactnumber,
           string address,string status);
    int getVendorid() const;
    string getVendorname() const;
    string getContactnumber() const;
    string getaddress() const;
    string getstatus() const;
};
#endif