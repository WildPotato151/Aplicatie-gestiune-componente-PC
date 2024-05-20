//
//
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

string Componenta::Info() const {

    string stock_string = (stock ? "Da" : "Nu");

    string info = "ID: " + (id == -1 ? "N/A" : to_string(id)) + "\n";
    info += "Tip: " + tip + "\n";
    info += "Brand: " + brand + "\n";
    info += "Model: " + model + "\n";
    info += "Specificatii: " + specs + "\n";
    info += "Pret: " + to_string(pret) + "\n";
    info += "In stock: " + stock_string + "\n";

}

string Componenta::ConversieToString_FisierCSV() const {

    string output = to_string(id) + SEPARATOR_FISIER + tip + SEPARATOR_FISIER + brand + SEPARATOR_FISIER +
        model + SEPARATOR_FISIER + specs + SEPARATOR_FISIER + to_string(pret) + SEPARATOR_FISIER +
        (stock ? "1" : "0") + SEPARATOR_FISIER;

    return output;
}

string Componenta::selecteazaTipComponenta() {

    int optiune = -1;
    string tip;

    cout<<"Selecteaza tipul de componenta: "<<endl;
    cout<<"1. CPU "<<endl;
    cout<<"2. GPU "<<endl;
    cout<<"3. Placa de baza"<<endl;
    cout<<"4. Memorie "<<endl;
    cout<<"5. SSD"<<endl;
    cout<<"6. Sursa"<<endl;
    cout<<"7. Carcasa"<<endl;

    while (optiune < 1 || optiune > 6) {
        cin >> optiune;

        switch (optiune) {
            case 1:
                tip = "CPU";
            break;
            case 2:
                tip = "GPU";
            break;
            case 3:
                tip = "Placa de baza";
            break;
            case 4:
                tip = "Memorie";
            break;
            case 5:
                tip = "SSD";
            break;
            case 6:
                tip = "Sursa";
            break;
            case 7:
                tip = "Carcasa";
            break;
            default:
                cout << "Optiune invalida!!! Selecteazsa o optiune valida... ";
            break;
        }
    }
    return tip;
}

bool Componenta::selecteazaStockComponenta() {

    int optiune = -1;
    bool stock;

    cout << "Selecteaza daca componenta se afla sau nu in stock:  " << endl;
    cout << "1. In stock" << endl;
    cout << "2. Nu se afla in stock" << endl;
    cout << "Introduceti o optiune... ";
    while (optiune < 1 || optiune > 2) {
        cin >> optiune;

        switch (optiune) {
            case 1:
                stock = true;
            break;
            case 2:
                stock = false;
            break;
            default:
                cout << "Optiune invalida!!! Selecteazsa o optiune valida... ";
            break;
        }
    }
    return optiune;
}

istream& operator>>(istream& is, Componenta& componenta) {

    string input;
    float input_float;

    cout << endl;
    componenta.getTip() = Componenta::selecteazaTipComponenta();

    cout<<"Introdu brand-ul componentei: ";
    is.ignore();
    getline(is, componenta.brand);

    cout<< "Introdu modelul componentei: ";
    getline(is, componenta.model);

    cout<< "Introdu specificatiile componentei: ";
    getline(is, componenta.specs);

    cout<< endl<<"Introdu pretul componentei(RON): ";
    is>> input;
    input_float = stof(input);
    componenta.pret = input_float;

    cout<< endl;
    componenta.stock = Componenta::selecteazaStockComponenta();

    return is;
}

ostream& operator<<(ostream& os, Componenta& componenta) {

    os << componenta.Info();
    return os;
}