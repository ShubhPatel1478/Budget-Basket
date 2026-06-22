
#include "Admin.h"
#include "Product.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <cstdio>
#include <sstream>
using namespace std;
int getNextEmployeeId()
{
    ifstream file("users.txt");
    if(!file)
    {
        return 1;
    }
    int id;
    int lastId = 0;
    string role;
    string username;
    string password;
    string name;
    while(file >> id >> role >> username >> password)
    {
        getline(file >> ws, name);
        lastId = max(lastId, id);
    }
    return lastId + 1;
}
void Admin::deactivatevendor()
{
    int vendorid;
    cout << "\n===== DEACTIVATE VENDOR =====\n";
    cout << "Enter Vendor ID : ";
    cin >> vendorid;
    ifstream file("vendors.txt");
    if(!file)
    {
        cout << "\nUnable to open vendors.txt\n";
        return;
    }
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        string name;
        string contact;
        string address;
        string status;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, contact, '|');
        getline(ss, address, '|');
        getline(ss, status, '|');
        if(stoi(id) == vendorid)
        {
            found = true;
            status = "INACTIVE";
        }

        temp << id << "|"
             << name << "|"
             << contact << "|"
             << address << "|"
             << status << '\n';
    }
    file.close();
    temp.close();
    if(!found)
    {
        remove("temp.txt");
        cout << "\nVendor ID not found.\n";
        return;
    }
    remove("vendors.txt");
    rename("temp.txt", "vendors.txt");
    cout << "\nVendor Deactivated Successfully.\n";
}
void Admin::activatevendor()
{
    int vendorid;
    cout << "\n===== ACTIVATE VENDOR =====\n";
    cout << "Enter Vendor ID : ";
    cin >> vendorid;
    ifstream file("vendors.txt");
    if(!file)
    {
        cout << "\nUnable to open vendors.txt\n";
        return;
    }
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        string name;
        string contact;
        string address;
        string status;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, contact, '|');
        getline(ss, address, '|');
        getline(ss, status, '|');
        if(stoi(id) == vendorid)
        {
            found = true;
            status = "ACTIVE";
        }
        temp << id << "|"
             << name << "|"
             << contact << "|"
             << address << "|"
             << status << '\n';
    }
    file.close();
    temp.close();
    if(!found)
    {
        remove("temp.txt");
        cout << "\nVendor ID not found.\n";
        return;
    }
    remove("vendors.txt");
    rename("temp.txt", "vendors.txt");
    cout << "\nVendor Activated Successfully.\n";
}
int getNextVendorId()
{
    ifstream file("vendors.txt");
    if(!file)
    {
        return 1;
    }
    int lastId = 0;
    string line;
    while(getline(file, line))
    {
        size_t pos = line.find('|');
        if(pos != string::npos)
        {
            int id = stoi(line.substr(0, pos));
            lastId = max(lastId, id);
        }
    }
    return lastId + 1;
}
int getNextProductId()
{
    ifstream file("products.txt");
    if(!file)
    {
        return 101;
    }
    int lastId=100;
    string line;
    while(getline(file, line))
    {
        size_t pos = line.find('|');
        if(pos != string::npos)
        {
            int id=stoi(line.substr(0, pos));
            lastId=max(lastId, id);
        }
    }
    return lastId + 1;
}
bool vendorIdExists(int vendorid)
{
    ifstream file("vendors.txt");
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id, name, contact, address, status;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, contact, '|');
        getline(ss, address, '|');
        getline(ss, status, '|');
        if(stoi(id)==vendorid &&
           status=="ACTIVE")
        {
            return true;
        }
    }
    return false;
}
bool productExists(string name,
                   string brand)
{
    ifstream file("products.txt");
    if(!file)
    {
        return false;
    }
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        string productName;
        string category;
        string productBrand;
        getline(ss, id, '|');
        getline(ss, productName, '|');
        getline(ss, category, '|');
        getline(ss, productBrand, '|');
        if(productName==name &&
           productBrand==brand)
        {
            return true;
        }
    }
    return false;
}
bool vendorExists(string vendorname,
                  string contactnumber)
{
    ifstream file("vendors.txt");
    if(!file)
    {
        return false;
    }
    string line;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        string existingName;
        string existingContact;
        string existingAddress;
        string existingStatus;
        getline(ss, id, '|');
        getline(ss, existingName, '|');
        getline(ss, existingContact, '|');
        getline(ss, existingAddress, '|');
        getline(ss, existingStatus, '|');
        if(existingName == vendorname &&
           existingContact == contactnumber)
        {
            return true;
        }
    }
    return false;
}
void Admin::menu()
{
    int choice;
    do
    {
        cout << "\n====================================\n";
        cout << "          ADMIN PANEL\n";
        cout << "====================================\n";
        cout << "1. View Products\n";
        cout << "2. Add Product\n";
        cout << "3. Update Product\n";
        cout << "4. Delete Product\n";
        cout << "5. View Vendors\n";
        cout << "6. Add Vendor\n";
        cout << "7. Deactivate Vendor\n";
        cout << "8. Activate Vendor\n";
        cout << "9. Add Employee\n";
        cout << "10. Remove Employee\n";
        cout << "11. Logout\n";
        cin >> choice;
        switch(choice)
        {
            case 1:
                viewproducts();
                break;
            case 2:
                addproduct();
                break;
            case 3:
                updateproduct();
                break;
            case 4:
                deleteproduct();
                break;
            case 5:
                viewvendors();
                break;
            case 6:
                addvendor();
                break;
            case 7:
                deactivatevendor();
                break;
            case 8:
                activatevendor();
                break;
            case 9:
                addemployee();
                break;
            case 10:
                removeemployee();
                break;
            case 11:
                cout<< "\nLogging Out...\n";
                return;
            default:
            {
             cout<<"\nInvalid Choice\n";
             break;
            }
        }
    }while(true);
}
void Admin::viewproducts()
{
    ifstream file("products.txt");
    if(!file)
    {
        cout << "\nUnable to open products.txt\n";
        return;
    }
    string line;
    cout << "\n========== PRODUCTS ==========\n";
    while(getline(file, line))
    {
        cout << line << endl;
    }
}
void Admin::viewvendors()
{
    ifstream file("vendors.txt");
    if(!file)
    {
        cout << "\nUnable to open vendors.txt\n";
        return;
    }
    string line;
    cout << "\n=====================================================================\n";
    cout << "ID\tNAME\t\tCONTACT\t\tADDRESS\t\tSTATUS\n";
    cout << "=====================================================================\n";
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        string name;
        string contact;
        string address;
        string status;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, contact, '|');
        getline(ss, address, '|');
        getline(ss, status, '|');
        cout << id << "\t"
             << name << "\t\t"
             << contact << "\t"
             << address << "\t\t"
             << status << endl;
    }
    file.close();
}
void Admin::addvendor()
{
    int vendorid = getNextVendorId();
    string vendorname;
    string contactnumber;
    string address;
    cout << "\n===== ADD VENDOR =====\n";
    cout << "Generated Vendor ID : "
         << vendorid << endl;
    cin.ignore();
    cout << "Vendor Name : ";
    getline(cin, vendorname);
    cout << "Contact Number : ";
    getline(cin, contactnumber);
    cout << "Address : ";
    getline(cin, address);
    if(vendorExists(vendorname, contactnumber))
    {
        cout << "\nVendor already exists.\n";
        return;
    }
    ofstream file("vendors.txt", ios::app);
    if(!file)
    {
        cout << "\nUnable to open vendors.txt\n";
        return;
    }
    file.seekp(0, ios::end);
    if(file.tellp() > 0)
    {
        file << '\n';
    }
    file << vendorid << "|"
         << vendorname << "|"
         << contactnumber << "|"
         << address<< "|"<<"ACTIVE";
    file.close();
    cout << "\nVendor Added Successfully.\n";
}
void Admin::addproduct()
{
    int productid = getNextProductId();
    string name;
    string category;
    string brand;
    double buyingprice;
    double sellingprice;
    int quantity;
    int vendorid;
    cout << "\n===== ADD PRODUCT =====\n";
    cout << "Generated Product ID : "
         << productid << endl;
    cin.ignore();
    cout << "Name : ";
    getline(cin, name);
    cout << "Category : ";
    getline(cin, category);
    cout << "Brand : ";
    getline(cin, brand);
    if(productExists(name, brand))
    {
        cout << "\nProduct already exists.\n";
        return;
    }
    cout<<"Buying Price : ";
    cin>>buyingprice;
    cout<<"Selling Price : ";
    cin>>sellingprice;
    cout<<"Quantity : ";
    cin>>quantity;
    cout<<"Vendor ID : ";
    cin>>vendorid;
    if(!vendorIdExists(vendorid))
    {
        cout << "\nVendor ID does not exist.\n";
        return;
    }
    Product p(
        productid,
        name,
        category,
        brand,
        buyingprice,
        sellingprice,
        quantity,
        vendorid
    );
    ofstream file("products.txt", ios::app);
    if(!file)
    {
        cout << "\nUnable to open products.txt\n";
        return;
    }
    file << productid << "|"
         << name << "|"
         << category << "|"
         << brand << "|"
         << buyingprice << "|"
         << sellingprice << "|"
         << quantity << "|"
         << vendorid << "\n";
    file.close();
    cout<<"\nProduct Added Successfully.\n";
}
void Admin::updateproduct()
{
    int productid;
    cout << "\n===== UPDATE PRODUCT =====\n";
    cout << "Enter Product ID : ";
    cin >> productid;
    ifstream file("products.txt");
    if(!file)
    {
        cout << "\nUnable to open products.txt\n";
        return;
    }
    ofstream temp("temp.txt");
    string line;
    bool found=false;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        string name;
        string category;
        string brand;
        string buyingprice;
        string sellingprice;
        string quantity;
        string vendorid;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, brand, '|');
        getline(ss, buyingprice, '|');
        getline(ss, sellingprice, '|');
        getline(ss, quantity, '|');
        getline(ss, vendorid, '|');
        if(stoi(id) == productid)
        {
            found = true;
            double newSellingPrice;
            int newQuantity;
            cout << "\nCurrent Selling Price : "
                 << sellingprice << endl;
            cout << "Current Quantity : "
                 << quantity << endl;
            cout << "New Selling Price : ";
            cin >> newSellingPrice;
            cout << "New Quantity : ";
            cin >> newQuantity;
            sellingprice = to_string(newSellingPrice);
            quantity = to_string(newQuantity);
        }
        temp << id << "|"
             << name << "|"
             << category << "|"
             << brand << "|"
             << buyingprice << "|"
             << sellingprice << "|"
             << quantity << "|"
             << vendorid << '\n';
    }
    file.close();
    temp.close();
    if(!found)
    {
        remove("temp.txt");

        cout << "\nProduct ID not found.\n";
        return;
    }
    remove("products.txt");
    rename("temp.txt", "products.txt");
    cout << "\nProduct Updated Successfully.\n";
}
void Admin::deleteproduct()
{
    int productid;
    cout << "\n===== DELETE PRODUCT =====\n";
    cout << "Enter Product ID : ";
    cin >> productid;
    ifstream file("products.txt");
    if(!file)
    {
        cout << "\nUnable to open products.txt\n";
        return;
    }
    ofstream temp("temp.txt");
    string line;
    bool found = false;
    while(getline(file, line))
    {
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if(stoi(id) == productid)
        {
            found = true;
            continue;
        }
        temp << line << '\n';
    }
    file.close();
    temp.close();
    if(!found)
    {
        remove("temp.txt");
        cout << "\nProduct ID not found.\n";
        return;
    }
    remove("products.txt");
    rename("temp.txt", "products.txt");
    cout << "\nProduct Deleted Successfully.\n";
}
void Admin::addemployee()
{
    int employeeId =getNextEmployeeId();
    string username;
    string password;
    string fullname;
    cout << "\n===== ADD EMPLOYEE =====\n";
    cout << "Generated Employee ID : "
         << employeeId << endl;
    cout << "Username : ";
    cin >> username;
    cout << "Password : ";
    cin >> password;
    cin.ignore();
    cout << "Full Name : ";
    getline(cin, fullname);
    ofstream file("users.txt", ios::app);
    if(!file)
    {
        cout << "\nUnable to open users.txt\n";
        return;
    }
    file.seekp(0, ios::end);
    if(file.tellp()>0)
    {
    file << '\n';
    }
    file << employeeId << " "
         << "EMPLOYEE "
         << username << " "
         << password << " "
         << fullname << '\n';
    file.close();
    cout << "\nEmployee Added Successfully.\n";
}
void Admin::removeemployee()
{
    int employeeId;
    cout << "\n===== REMOVE EMPLOYEE =====\n";
    cout << "Enter Employee ID : ";
    cin >> employeeId;
    ifstream file("users.txt");
    if(!file)
    {
        cout << "\nUnable to open users.txt\n";
        return;
    }
    ofstream temp("temp.txt");
    int id;
    string role;
    string username;
    string password;
    string fullname;
    bool found=false;
    while(file >> id >> role >> username >> password)
    {
        getline(file >> ws, fullname);
        if(id == employeeId &&
           role == "EMPLOYEE")
        {
            found = true;
            continue;
        }
        temp << id << " "
             << role << " "
             << username << " "
             << password << " "
             << fullname << '\n';
    }
    file.close();
    temp.close();
    if(!found)
    {
        remove("temp.txt");
        cout << "\nEmployee ID not found.\n";
        return;
    }
    remove("users.txt");
    rename("temp.txt", "users.txt");
    cout << "\nEmployee Removed Successfully.\n";
}

