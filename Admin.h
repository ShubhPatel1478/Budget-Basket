#ifndef ADMIN_H
#define ADMIN_H
class Admin
{
public:
    static void menu();
    static void addproduct();
    static void updateproduct();
    static void deleteproduct();
    static void addvendor();
    static void addemployee();
    static void removeemployee();
    static void viewproducts();
    static void viewvendors();
    static void deactivatevendor();
    static void activatevendor();
};
#endif