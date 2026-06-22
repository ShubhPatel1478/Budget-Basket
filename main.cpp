#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <cctype>
#include "Admin.h"
#include "Employee.h"
using namespace std;
const string ADMIN="ADMIN";
const string EMPLOYEE="EMPLOYEE";
int login(const string& role);
bool customerLogin();
bool customerExists(const string& username);
int getNextCustomerId();
bool isValidMobile(const string& mobile);
void registerCustomer();
int main()
{
    int choice;
    do
    {
        cout<<"\n====================================\n";
        cout<<"      BUDGET BASKET SYSTEM\n";
        cout<<"====================================\n";
        cout<<"1. Admin Login\n";
        cout<<"2. Employee Login\n";
        cout<<"3. Customer Registration\n";
        cout<<"4. Customer Login\n";
        cout<<"5. Exit\n";
        cout<<"\nEnter Choice : ";
        cin>>choice;
        switch(choice)
        {
            case 1:
            {
                if(login(ADMIN))
                {
                     cout<<"\nAdmin Login Successful\n";
                     Admin::menu();
                }
                else
                {
                    cout<<"\nInvalid Credentials\n";
                }
                break;
            }
            case 2:
            {
                if(login(EMPLOYEE))
                {
                    cout<<"\nEmployee Login Successful\n";
                    Employee::menu();
                }
                else
                {
                    cout<<"\nInvalid Credentials\n";
                }
                break;
            }
            case 3:
            {
                registerCustomer();
                break;
            }
            case 4:
            {
                if(customerLogin())
                {
                    cout<<"\nCustomer Login Successful\n";
                }
                else
                {
                    cout<<"\nInvalid Credentials\n";
                }
                break;
            }
            case 5:
            {
                cout<<"\nThank You For Using Budget Basket\n";
                break;
            }
            default:
            {
                cout<<"\nInvalid Choice\n";
            }
        }

    } while(choice != 5);
    return 0;
}
int login(const string& role)
{
    string username;
    string password;
    cout<<"\nUsername : ";
    cin>>username;
    cout<<"Password : ";
    cin >> password;
    ifstream file("users.txt");
    if(!file)
    {
        cout<<"\nusers.txt not found.\n";
        return false;
    }
    int id;
    string fileRole;
    string fileUsername;
    string filePassword;
    string name;
    while(file >>
      id >>
      fileRole >>
      fileUsername >>
      filePassword)
    {
    getline(file >> ws, name);
    if(fileRole == role &&
       fileUsername == username &&
       filePassword == password)
    {
        return true;
    }
    }
    return false;
}
bool customerLogin()
{
    string username;
    string password;
    cout<<"\nUsername : ";
    cin>>username;
    cout<<"Password : ";
    cin>>password;
    ifstream file("customers.txt");
    if(!file)
    {
        cout<<"\nNo customers registered yet.\n";
        return false;
    }
    int customerId;
    string fileUsername;
    string filePassword;
    string mobile;
    string name;
    while(file>>
          customerId>>
          fileUsername>>
          filePassword>>
          mobile)
    {
        getline(file>> ws, name);
        if(fileUsername==username &&
           filePassword==password)
        {
            return true;
        }
    }
    return false;
}
bool customerExists(const string& username)
{
    ifstream file("customers.txt");
    if(!file)
    {
        return false;
    }
    int customerId;
    string user;
    string password;
    string mobile;
    string name;
    while(file>>
          customerId>>
          user>>
          password>>
          mobile)
    {
        getline(file >> ws, name);
        if(user==username)
        {
            return true;
        }
    }
    return false;
}
int getNextCustomerId()
{
    ifstream file("customers.txt");
    if(!file)
    {
        return 1;
    }
    int customerId;
    int lastId=0;
    string user;
    string password;
    string mobile;
    string name;
    while(file>>
          customerId>>
          user>>
          password>>
          mobile)
    {
        getline(file >> ws, name);
        lastId=max(lastId, customerId);
    }
    return lastId+1;
}
bool isValidMobile(const string& mobile)
{
    if(mobile.length()!=10)
    {
        return false;
    }
    for(char ch : mobile)
    {
        if(!isdigit(ch))
        {
            return false;
        }
    }
    return true;
}
void registerCustomer()
{
    string username;
    string password;
    string mobile;
    string name;
    cout<<"\n===== Customer Registration =====\n";
    cout<<"Username : ";
    cin>>username;
    if(customerExists(username))
    {
        cout << "\nUsername already exists.\n";
        return;
    }
    cout<<"Password : ";
    cin>>password;
    do
    {
        cout<<"Mobile Number : ";
        cin>>mobile;
        if(!isValidMobile(mobile))
        {
            cout<<"Invalid Mobile Number.\n";
        }
    } while(!isValidMobile(mobile));
    cin.ignore();
    cout<<"Full Name : ";
    getline(cin, name);
    int customerId = getNextCustomerId();
    ofstream file(
        "customers.txt",
        ios::app
    );
    if(!file)
    {
    cout<<"\nError opening customers.txt\n";
    return;
   }
    file
        <<customerId<<" "
        <<username<<" "
        <<password<<" "
        <<mobile<<" "
        <<name<<"\n";
    cout<<"\nCustomer Registered Successfully.\n";
    cout<<"Customer ID : " << customerId << "\n";
}