//
// Created by EON on 5/20/2024.
//

#ifndef COMPONENTA_H
#define COMPONENTA_H

#include "Componenta.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Componenta
{
private:
    char SEPARATOR_FISIER = ',';

    int id;
    string tip;
    string brand;
    string model;
    string specs;
    float pret;
    bool stock;

public:
    Componenta(int id = -1, string tip = "N/A", string brand = "N/A", string model = "N/A", string specs = "N/A", float pret = -1, bool stock = false );
    ~Componenta();

    int getID() const {return id;}
    string getTip() const {return tip;}
    string getBrand() const {return brand;}
    string getModel() const {return model;}
    string getSpecs() const {return specs;}
    string getPret() const {return to_string(pret);}
    bool esteStock() const {return stock;}

    void setId(int newId) { id = newId; }
    void setTip(const string newTip) { tip = newTip; }
    void setBrand(const string newBrand) { brand = newBrand; }
    void setModel(const string newModel) { model = newModel; }
    void setSpecs(const string newSpecs) { specs = newSpecs; }
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
