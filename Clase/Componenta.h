//
//
//

#ifndef COMPONENTA_H
#define COMPONENTA_H


#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Componenta
{
private:
    const char SEPARATOR_FISIER = ',';

    int id;
    string tip;
    string brand;
    string model;
    string specs;
    float pret;
    bool stock;

    int ID = 0;
    int TIP = 1;
    int BRAND = 2;
    int MODEL = 3;
    int SPECS = 4;
    int PRET = 5;
    int STOCK = 6;

    static const int NR_CARACTERISTICI = 7;



public:
    Componenta(int id = -1, string tip = "N/A", string brand = "N/A", string model = "N/A", string specs = "N/A", float pret = -1, bool stock = false );
    ~Componenta();

    Componenta& operator=(const Componenta& other);
    Componenta(const Componenta& other);

    int getID() const {return id;}
    string getTip() const {return tip;}
    string getBrand() const {return brand;}
    string getModel() const {return model;}
    string getSpecs() const {return specs;}
    float getPret() const {return pret;}
    bool esteStock() const {return stock;}

    void setId(int newId) { id = newId; }
    void setTip(const string& newTip) { tip = newTip; }
    void setBrand(const string& newBrand) { brand = newBrand; }
    void setModel(const string& newModel) { model = newModel; }
    void setSpecs(const string& newSpecs) { specs = newSpecs; }
    void setPret(float newPret) { pret = newPret; }
    void setStock(bool newStock) { stock = newStock; }

    string ConversieToString_FisierCSV() const;

    static string selecteazaTipComponenta();
    static bool selecteazaStockComponenta();

    friend istream& operator>>(istream& is, Componenta& componenta);
    friend ostream& operator<<(ostream& os, Componenta& componenta);

    string Info() const;
};



#endif //COMPONENTA_H
