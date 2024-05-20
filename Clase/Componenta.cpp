//
// Created by EON on 5/20/2024.
//

#include "Componenta.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

Componenta::Componenta(int id, string tip, string brand, string model, string specs, float pret, bool stock ) {

    this->id = id;
    this->tip = tip;
    this->brand = brand;
    this->model = model;
    this->specs = specs;
    this->pret = pret;
    this->stock = stock;


}
Componenta::~Componenta() {}
