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
    char SEPARATOR_FISIER = ';';

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
};



#endif //COMPONENTA_H
