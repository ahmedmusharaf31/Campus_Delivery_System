#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
using namespace std;

enum vehicle{BIKE, CAR, VAN};

class Catalog{
    protected:
    vector<string> iname;
    vector<float> iprice;

    public:
    int findIndex(string item) {
        for (int i = 0; i < iname.size(); ++i)  {
            if (iname[i] == item)
                return i;
        }
        return -1;
    }
    void AddItem(string n, float p){
        iname.push_back(n);
        iprice.push_back(p);
    }
    void RemoveItem(string item){
        int ind = findIndex(item);
        if(ind!=-1){
            iname.erase(iname.begin()+ind);
            iprice.erase(iprice.begin()+ind);
        }
    }
    void ChangePrice(string item, float p){
        int ind = findIndex(item);
        if(ind!=-1){
            iprice[ind]=p;
        }
    }
};


class Business : public Catalog{
    protected:
    string name;
    Business(string x){
        name = x;
    }
    public:
    friend void NewBusiness(string x, vector<Business> &a);
    friend int FindBusiness(string x, vector<Business> &a);
    friend void RemoveBusiness(string x, vector<Business> &a);
    friend void BSave(vector<Business> &a);
    friend void BLoad(vector<Business> &a);
    friend void CSave(Business &a, string name);
    friend void CLoad(Business &a, string name);
    friend string createOrder(Business a, vector<string> ord);
    friend int calcOrder(Business a, vector<string> ord);
    int printItems(){
        cout<<"Name: "<<name<<endl;
        int numberOfItems=0;
        cout<<"Name:    Price:"<<endl;
        for(int i=0;i<iname.size();i++){
             cout<<iname[i]<<'\t'<<iprice[i]<<endl;
             numberOfItems++;
        }
    };
    vector<string> giveItemsNames(){
        return iname;
    }
    vector<float> giveItemsPrice(){
        return iprice;
    }
    
};

class Driver{
    public:
    string numplate;
    string name;
    vehicle v;
    Driver(string n, string p):name(n), numplate(p){}
    virtual int seatno()=0;
};

class bike : public Driver{
    public:
    bike(string n, string p):Driver(n,p){
        v = BIKE;
    }
    int seatno(){
        return 1;
    }
};


class car : public Driver{
    public:
    car(string n, string p) : Driver(n,p){
        v = CAR;
    }
    int seatno(){
        return 2;
    }
};


class van : public Driver{
    public:
    van(string n, string p) : Driver(n,p){
        v = VAN;
    }
    int seatno(){
        return 4;
    }
};

void NewBusiness(string x,vector<Business> &a){
    Business b(x);
    a.push_back(b);
}

int FindBusiness(string x, vector<Business> &a){

    for(int i=0; i<a.size(); i++){
        if(a[i].name==x){
            return i;
        }
    }
    return -1;
}

void RemoveBusiness(string x, vector<Business> &a){
    int i=FindBusiness(x, a);
    a.erase(a.begin()+i);
}


void CSave(Business &a, string name){
    ofstream outputFile((name+".txt"));
    for (size_t i = 0; i < a.iname.size(); i++) {
        outputFile << a.iname[i] << "," << a.iprice[i] << endl;
    }
    outputFile.close();
}

void CLoad(Business &a,string name){
    ifstream inputFile((name+".txt"));
    // if(inputFile.is_open()){
    //     while(geltine(inputFile,))
    // }
    // else{
    //     std::cout<<"file not open!";
    // }


    string line;
    while (getline(inputFile, line)) {
        istringstream iss(line);
        string str;
        float value;

        if (getline(iss, str, ',') && iss >> value) {
            a.iname.push_back(str);
            a.iprice.push_back(value);
        }
    }
    inputFile.close();
}

void BSave(vector<Business> &a){
    ofstream outputFile("businesses.txt");
    for (int i = 0; i <a.size(); ++i) {
        outputFile << a[i].name<<endl;
        CSave(a[i],a[i].name);
    }

    outputFile.close();
}

void BLoad(vector<Business> &a){
    a.clear();
    ifstream inputFile("businesses.txt");
    string line;
    int i=0;
    while(getline(inputFile, line)){
        a.push_back(line);
        CLoad(a[i],a[i].name);
        i++;
    }
    inputFile.close();
}

int calcOrder(Business a, vector<string> ord){
    float sum=0;
    int ind;
    for(int i=0; i<ord.size(); i++){
        ind = a.findIndex(ord[i]);
        sum += a.iprice[i];
    }
    return sum;
}


void SaveOrder(string order){
    ofstream outputFile("orders.txt", ios::app);
    outputFile<<order<<endl;
    outputFile.close();
}

string createOrder(Business a, vector<string> ord){
    float sum = calcOrder(a, ord);
    string x = "Business: " + a.name +", Items: ";
    for(int i=0; i<ord.size(); i++){
        x += ord[i];
        if(i<ord.size()-1)
         x+= "|";
    }
    x += ", Price: "+to_string(sum);
    SaveOrder(x);
    return x;
}

void NewDriver(string name, string nplate,Driver* a[], int &size, vehicle v = BIKE){
    switch(v){
        case BIKE:
        a[size]=new bike(name, nplate);
        break;
        case CAR:
        a[size]=new car(name, nplate);
        break;
        case VAN:
        a[size]=new van(name, nplate);
        break;
    }
    size++;
}

void DSave(Driver* a[], int &size){
    ofstream outputFile("drivers.txt");
    for (int i = 0; i < size; i++) {
        outputFile <<a[i]->name<< "," << a[i]->numplate<<","<<a[i]->v<< endl;
    }
    outputFile.close();
}

void DLoad(Driver* a[], int &size) {
    ifstream inputFile("drivers.txt");
    string line;
    while (getline(inputFile, line)) {
        int pos = line.find(",");

        string name = line.substr(0, pos);

        size_t nextPos = line.find(",", pos + 1);

        string numplate = line.substr(pos + 1, nextPos - pos - 1);

        string vStr = line.substr(nextPos + 1);
        vehicle v = static_cast<vehicle>(stoi(vStr));
        NewDriver(name, numplate, a, size, v);
    }
    inputFile.close();
}

int DFind(Driver* a[], int size, const string &targetName) {
    for (int i = 0; i < size; i++) {
        if (a[i]->name == targetName) {
            return i;  // driver found, return index
        }
    }
    return -1;  // driver not found
}

void removeLines(string filename, int numLinesToRemove) {
    ifstream inFile(filename);
    vector<string> lines;
    string line;
    while (getline(inFile, line)) {
        lines.push_back(line);
    }

    inFile.close();
    if (numLinesToRemove >= lines.size()) {
        lines.clear();
    } else {
        lines.erase(lines.begin(), lines.begin() + numLinesToRemove);
    }
    ofstream outFile(filename);
    for (const string& updatedLine : lines) {
        outFile << updatedLine << "\n";
    }

    outFile.close();
}

void LoadOrders(vector<string> &ord, Driver* a){
    int seats = a->seatno();
    int i=0;
    ord.clear();
    ifstream inputFile("orders.txt");
    string line;
    while(getline(inputFile, line)&&i!=seats){
        ord.push_back(line);
        i++;
    }
    removeLines("orders.txt", i);
}
