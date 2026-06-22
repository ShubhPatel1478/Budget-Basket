#include "Employee.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdio>
#include <algorithm>
using namespace std;
struct BillItem
{
    int productId;
    string productName;
    int quantity;
    int unitPrice;
    int lineTotal;
};
bool productExists(int productId)
{
    ifstream file("products.txt");
    if(!file)
    {
        return false;
    }
    string line;
    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }
        stringstream ss(line);
        string id;
        getline(ss, id, '|');
        if(id.empty())
        {
            continue;
        }
        if(stoi(id) == productId)
        {
            return true;
        }
    }
    return false;
}
bool customerExists(int customerId)
{
    ifstream file("customers.txt");
    if(!file)
    {
        return false;
    }
    int id;
    string username;
    string password;
    string mobile;
    string name;
    while(file >> id >> username >> password >> mobile)
    {
        getline(file >> ws, name);
        if(id == customerId)
        {
            return true;
        }
    }
    return false;
}
int getNextBillId()
{
    ifstream file("bills.txt");
    if(!file)
    {
        return 1;
    }
    int lastId = 0;
    string line;
    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }
        size_t pos = line.find('|');
        if(pos != string::npos)
        {
            int id = stoi(line.substr(0, pos));
            lastId = max(lastId, id);
        }
    }
    return lastId + 1;
}
void Employee::menu()
{
    int choice;
    do
    {
        cout << "\n====================================\n";
        cout << "        EMPLOYEE PANEL\n";
        cout << "====================================\n";
        cout << "1. View Products\n";
        cout << "2. Search Product\n";
        cout << "3. Update Stock\n";
        cout << "4. Generate Bill\n";
        cout << "5. Logout\n";
        cout << "\nEnter Choice : ";
        cin >> choice;
        switch(choice)
        {
            case 1:
                viewproducts();
                break;
            case 2:
                searchproduct();
                break;
            case 3:
                updatestock();
                break;
            case 4:
                generatebill();
                break;
            case 5:
                cout << "\nLogging Out...\n";
                return;
            default:
                cout << "\nInvalid Choice\n";
        }
    } while(true);
}
void Employee::viewproducts()
{
    ifstream file("products.txt");
    if(!file)
    {
        cout << "\nUnable to open products.txt\n";
        return;
    }
    string line;
    cout << "\n========================================================================\n";
    cout << "ID\tNAME\tCATEGORY\tBRAND\tPRICE\tQTY\n";
    cout << "========================================================================\n";
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
        cout << id << "\t"
             << name << "\t"
             << category << "\t"
             << brand << "\t"
             << sellingprice << "\t"
             << quantity << endl;
    }
    file.close();
}
void Employee::searchproduct()
{
    int productid;
    cout << "\nEnter Product ID : ";
    cin >> productid;
    ifstream file("products.txt");
    if(!file)
    {
        cout << "\nUnable to open products.txt\n";
        return;
    }
    string line;
    bool found = false;
    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }
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
        if(id.empty())
        {
            continue;
        }
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
            cout << "\n========== PRODUCT FOUND ==========\n";
            cout << "ID            : " << id << endl;
            cout << "Name          : " << name << endl;
            cout << "Category      : " << category << endl;
            cout << "Brand         : " << brand << endl;
            cout << "Selling Price : " << sellingprice << endl;
            cout << "Quantity      : " << quantity << endl;
            break;
        }
    }
    file.close();
    if(!found)
    {
        cout << "\nProduct Not Found\n";
    }
}
void Employee::updatestock()
{
    int productid;
    cout << "\n===== UPDATE STOCK =====\n";
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
            cout << "\nCurrent Stock : "
                 << quantity << endl;
            int newStock;
            cout << "Enter New Stock : ";
            cin >> newStock;
            quantity = to_string(newStock);
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
    cout << "\nStock Updated Successfully.\n";
}
void Employee::generatebill()
{
int customerId;
cout << "\n===== GENERATE BILL =====\n";
cout << "Customer ID : ";
cin >> customerId;
if(!customerExists(customerId))
{
    cout << "\nInvalid Customer ID.\n";
    return;
}
vector<BillItem> items;
char choice = 'Y';
while(choice == 'Y' || choice == 'y')
{
    int productId;
    int quantity;
    cout << "\nProduct ID : ";
    cin >> productId;
    if(!productExists(productId))
    {
        cout << "\nInvalid Product ID.\n";
        continue;
    }
    cout << "Quantity : ";
    cin >> quantity;
    if(quantity <= 0)
    {
        cout << "\nInvalid Quantity.\n";
        continue;
    }
    ifstream file("products.txt");
    string line;
    bool added = false;
    while(getline(file, line))
    {
        if(line.empty())
        {
            continue;
        }
        stringstream ss(line);
        string id;
        string name;
        string category;
        string brand;
        string buyingprice;
        string sellingprice;
        string stock;
        string vendorid;
        getline(ss, id, '|');
        getline(ss, name, '|');
        getline(ss, category, '|');
        getline(ss, brand, '|');
        getline(ss, buyingprice, '|');
        getline(ss, sellingprice, '|');
        getline(ss, stock, '|');
        getline(ss, vendorid, '|');
        if(stoi(id) == productId)
        {
            int currentStock = stoi(stock);
            int alreadyInBill = 0;
            for(auto &item : items)
            {
                if(item.productId == productId)
                {
                    alreadyInBill = item.quantity;
                    break;
                }
            }
            if(alreadyInBill + quantity > currentStock)
            {
                cout << "\nInsufficient Stock.\n";
                break;
            }
            bool alreadyExists = false;
            for(auto &item : items)
            {
                if(item.productId == productId)
                {
                    item.quantity += quantity;
                    item.lineTotal =
                        item.quantity * item.unitPrice;

                    alreadyExists = true;
                    break;
                }
            }
            if(!alreadyExists)
            {
                BillItem item;
                item.productId = productId;
                item.productName = name;
                item.quantity = quantity;
                item.unitPrice = stoi(sellingprice);
                item.lineTotal =
                    quantity * item.unitPrice;
                items.push_back(item);
            }
            added = true;
            break;
        }
    }
    file.close();
    if(added)
    {
        cout << "Product Added To Bill.\n";
    }
    cout << "\nAdd More Products? (Y/N) : ";
    cin >> choice;
}
if(items.empty())
{
    cout << "\nNo Items In Bill.\n";
    return;
}
int grandTotal = 0;
for(auto &item : items)
{
    grandTotal += item.lineTotal;
}
int billId = getNextBillId();
ofstream billFile("bills.txt", ios::app);
if(billFile.tellp() > 0)
{
    billFile << '\n';
}
billFile << billId
         << "|"
         << customerId
         << "|"
         << grandTotal;
billFile.close();
ofstream itemFile("billitems.txt", ios::app);
for(auto &item : items)
{
    if(itemFile.tellp() > 0)
    {
        itemFile << '\n';
    }
    itemFile << billId << "|"
             << item.productId << "|"
             << item.quantity << "|"
             << item.unitPrice << "|"
             << item.lineTotal;
}
itemFile.close();
ifstream productFile("products.txt");
ofstream temp("temp.txt");
string line;
while(getline(productFile, line))
{
    if(line.empty())
    {
        continue;
    }
    stringstream ss(line);
    string id;
    string name;
    string category;
    string brand;
    string buyingprice;
    string sellingprice;
    string stock;
    string vendorid;
    getline(ss, id, '|');
    getline(ss, name, '|');
    getline(ss, category, '|');
    getline(ss, brand, '|');
    getline(ss, buyingprice, '|');
    getline(ss, sellingprice, '|');
    getline(ss, stock, '|');
    getline(ss, vendorid, '|');
    int currentProductId = stoi(id);
    for(auto &item : items)
    {
        if(item.productId == currentProductId)
        {
            int currentStock = stoi(stock);
            currentStock -= item.quantity;
            stock = to_string(currentStock);
            break;
        }
    }
    temp << id << "|"
         << name << "|"
         << category << "|"
         << brand << "|"
         << buyingprice << "|"
         << sellingprice << "|"
         << stock << "|"
         << vendorid << '\n';
}
productFile.close();
temp.close();
remove("products.txt");
rename("temp.txt", "products.txt");
cout << "\n=========================================\n";
cout << "              BILL RECEIPT\n";
cout << "=========================================\n";
for(auto &item : items)
{
    cout << item.productName
         << "    "
         << item.quantity
         << " x "
         << item.unitPrice
         << " = "
         << item.lineTotal
         << endl;
}
cout << "-----------------------------------------\n";
cout << "TOTAL : " << grandTotal << endl;
cout << "Bill ID : " << billId << endl;
cout << "=========================================\n";
cout << "\nBill Generated Successfully.\n";
}
