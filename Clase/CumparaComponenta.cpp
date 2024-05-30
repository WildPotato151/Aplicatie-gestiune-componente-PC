//
//
//

#include "CumparaComponenta.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

CumparaComponenta::CumparaComponenta(int idCumparare, int idComponenta, string nume, string prenume, string email, string nr_telefon, string adresa) {
    this-> idCumparare = idCumparare;
    this->idComponenta = idComponenta;
}

CumparaComponenta::CumparaComponenta(string linieFisier) {

    vector<string> dateFisier = split(linieFisier, SEPARATOR_FISIER);

    if(dateFisier.size() < NR_CARACTERISTICI) {
        throw runtime_error("Date lipsa! linieFisier: " + linieFisier );
    }

    idCumparare = stoi(dateFisier[ID_CUMPARARE] );
    idComponenta = stoi(dateFisier[ID_COMPONENTA]);
    nume = dateFisier[NUME];
    prenume = dateFisier[PRENUME];
    email = dateFisier[EMAIL];
    nr_telefon = dateFisier[NRTELEFON];
    adresa = dateFisier[ADRESA];
}

CumparaComponenta::~CumparaComponenta() {}

string CumparaComponenta::Info() const {
    string info = "ID cos cumparaturi: " + (idCumparare ==-1 ? "N/A" : to_string(idCumparare)) + "\n";
    info += "ID componenta: " + to_string(idComponenta) + "\n";
    info += "Nume: " + nume + "\n";
    info += "Prenume: " + prenume  + "\n";
    info += "Email: " + email + "\n";
    info += "Numar de telefon: " + nr_telefon  + "\n";
    info += "Adresa: " + adresa + "\n";


    return info;
}

string CumparaComponenta::ConversieLaSir_PentruFisier() {
    string output = to_string(idCumparare) +SEPARATOR_FISIER +
                    to_string(idCumparare) + SEPARATOR_FISIER +
                    nume + SEPARATOR_FISIER + prenume + SEPARATOR_FISIER +
                    email + SEPARATOR_FISIER + nr_telefon + SEPARATOR_FISIER +
                    adresa + SEPARATOR_FISIER;

    return output;

}

istream &operator>>(istream &is, CumparaComponenta &cumparareComponenta) {
    string input;

    cout<< "Introdu numele clientului: ";
    is.ignore();
    getline(is, cumparareComponenta.nume);

    cout<< "Introdu prenumele clientului: ";
    getline(is, cumparareComponenta.prenume);

    cout<<"Introdu adresa de email a clientului: ";
    getline(is, cumparareComponenta.email);

    cout<<"Introdu numarul de telefon al clientului: ";
    getline(is,input);
    while(!Validari::validareDoarCifre(input)) {
        cout<< "Numarul de telefon trebuie sa contina doar cifre!!!";
        getline(is, input);
    }
    cumparareComponenta.nr_telefon = input;

    cout<< "Introdu adresa clientului: ";
    getline(is, cumparareComponenta.adresa);

    return is;
}

ostream& operator<<(ostream& os, const CumparaComponenta& cumparareComponenta) {
    os << cumparareComponenta.Info();
    return os;
}

void CumparaComponenta::citireCumparareExistenta() {
    string input;

    cout<<"Introdu numele clientului (default: " << nume << "): ";
    cin.ignore();
    getline(cin, input);
    if(!input.empty()) {
        nume = input;
    }

    cout << "Introdu prenumele clientului (default: " << prenume << "): ";
    getline(cin, input);
    if (!input.empty()) {
        prenume = input;
    }

    cout << "Introdu adresa de email a clientului (default: " << email << "): ";
    getline(cin, input);
    while(!Validari::validareEmail(input) && !input.empty()) {
        cout << "Email invalid, reintroduceti email-ul...";
        getline(cin, input);
    }
    if (!input.empty()) {
        email = input;
    }

    cout << "Introdu numarul de telefon al clientului (default: " << nr_telefon << "): ";
    getline(cin, input);
    while(!Validari::validareDoarCifre(input) && !input.empty()) {
        cout << "Numarul de telefon trebuie sa contina doar cifre!!!";
        getline(cin, input);
    }
    if (!input.empty()) {
        nr_telefon = input;
    }

    cout << "Introdu adresa clientului (default: " << adresa << "): ";
    getline(cin, input);
    if (!input.empty()) {
        adresa = input;
    }
}


