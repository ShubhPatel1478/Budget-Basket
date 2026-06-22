#include "Vendor.h"
Vendor::Vendor(int vendorid,
               string vendorname,
               string contactnumber,
               string address,string status)
{
    this->vendorid = vendorid;
    this->vendorname = vendorname;
    this->contactnumber = contactnumber;
    this->address = address;
    this->status=status;
}
int Vendor::getVendorid() const
{
    return vendorid;
}
string Vendor::getVendorname() const
{
    return vendorname;
}
string Vendor::getContactnumber() const
{
    return contactnumber;
}
string Vendor::getaddress() const
{
    return address;
}
string Vendor::getstatus() const
{
    return status;
}