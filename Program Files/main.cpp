#include <iostream>
#include "head1.h"
using namespace std;

vector<Business> a;
Driver *d[40];
int D_no = 0;
void bussinessMenu();
void customerMenu();
void driverMenu();
void mainMenu();


int main()
{
    DLoad(d, D_no);
    BLoad(a);
    // for(int i=0;i<a.size();i++){
    //     std::cout<<a[i].printItems()<<endl;
    // }
    mainMenu();
    BSave(a);
    DSave(d, D_no);
}

void mainMenu()
{
    while (true)
    {
        int input;
        cout << "Please select option:\n";
        cout << "1. Bussiness\n";
        cout << "2. Customer\n";
        cout << "3. Driver\n";
        cout << "4. Exit\n";
        cin >> input;
        cin.ignore();
        switch (input)
        {
        case 1:
            bussinessMenu();
            break;
        case 2:
            customerMenu();
            break;
        case 3:
            driverMenu();
            break;
        case 4:
        return;
        }

        char ch;
        cout<<"Do you want to go back to menu press y for yes\n";
        cin>>ch;
        if(ch=='y'|| ch=='Y'){
            cin.clear();
            continue;
        }
        else{
            return;
        }
    }
}

void bussinessMenu()
{

    char in;
    bool exitFlag = false;

    {
        cout << "Would you like to register a new business? (y/n): ";
        cin >> in;

        string name;
        cout << "Please enter the name of the business: ";
        cin.ignore();
        getline(cin, name);
        if (in == 'y' || in == 'Y')
        {
            NewBusiness(name, a);
        }

        int index;
        index = FindBusiness(name, a);

        if (index == -1)
        {
            cout << "No business found!\n";
            return;
        }
        else
        {
            while (!exitFlag)
            {
                int input;
                cout << "1. Add Item to Catalog\n";
                cout << "2. Remove Item from Catalog\n";
                cout << "3. Change Price of an Item\n";
                cout << "4. Exit\n";
                cout << "Enter your choice: ";
                cin >> input;

                switch (input)
                {
                case 1:
                {
                    string catalogName;
                    int value;
                    cout << "Enter the name of the catalog: ";
                    cin.ignore();
                    getline(cin, catalogName);
                    cout << "Enter the value of the catalog: ";
                    cin >> value;
                    a[index].AddItem(catalogName, value);
                    break;
                }
                case 2:
                {
                    string catalogName;
                    cout << "Enter the name of the catalog: ";
                    cin.ignore();
                    getline(cin, catalogName);
                    a[index].RemoveItem(catalogName);
                    break;
                }
                case 3:
                {
                    string catalogName;
                    int value;
                    cout << "Enter the name of the catalog: ";
                    cin.ignore();
                    getline(cin, catalogName);
                    cout << "Enter the new value of the catalog: ";
                    cin >> value;
                    a[index].ChangePrice(catalogName, value);

                    break;
                }
                case 4:
                    exitFlag = true;
                    break;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    break;
                }
            }
        }
    }
}

void customerMenu()
{

    char in;
    bool exitFlag = false;

    string name;
    cout << "Choose bussiness name of the business: ";
    getline(cin, name);


    int index;
    index = FindBusiness(name, a);
    if (index == -1)
    {
        cout << "No business found!\n";
        return;
    }
    else
    {
        
        vector<string> orders;
        while (!exitFlag)
        {
            int input;
            vector<string> v_names = a[index].giveItemsNames();
            vector<float> v_prices = a[index].giveItemsPrice();
            while (true)
            {
                for (int i = 0; i < v_names.size(); i++)
                {
                    cout << i + 1 << ": " << v_names[i] << '\t' << v_prices[i] << endl;
                }
                int itm;
                cout << "Please enter the item you want 1,2,3..!\n";
                cin >> itm;
                string order = v_names[itm - 1] + ',' + to_string(v_prices[itm - 1]);
                orders.push_back(order);

                char choice;
                cout << "Do you want to continue order? y/n: " << endl;
                cin >> choice;
                if (choice=='n' || choice=='N')
                {
                    break;
                }
            }

            for (int i = 0; i < orders.size(); i++)
            {
                cout << orders[i] << endl;
            }

            createOrder(a[index], orders);
            return;
        }
    }
}

void driverMenu()
{

    char in;
    bool exitFlag = false;

    cout << "Would you like to register a new driver? (y/n): ";
    cin >> in;

    string name, nplate;
    cout << "Please enter the name of the driver: ";
    cin.ignore();
    getline(cin, name);
    if (in == 'y' || in == 'Y')
    {
        int type;
        cout << "Please enter the number plate:\n";
        getline(cin, nplate);
        cout << "Please enter vechicle type \n1.Bike\n2.Car\n3.Van\n";
        cin >> type;
        switch (type)
        {
            vehicle v;
        case 1:
            v = BIKE;
            NewDriver(name, nplate, d, D_no, v);

            break;
        case 2:
            v = CAR;
            NewDriver(name, nplate, d, D_no, v);
            break;
        case 3:
            v = VAN;
            NewDriver(name, nplate, d, D_no, v);
            break;
        }
    }
    int index = DFind(d, D_no, name);

    if (index == -1)
    {
        cout << "No Driver found!\n";
        return;
    }
    else
    {
        vector<string> ord;
        LoadOrders(ord, d[index]);
        for (int i = 0; i < ord.size(); i++)
        {
            cout << ord[i] << endl;
        }
    }
    return;
}
