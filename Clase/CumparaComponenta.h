//
//
//

#ifndef CUMPARACOMPONENTA_H
#define CUMPARACOMPONENTA_H

#include "Client.h"
#include "Validari.h"
#include "AdministrareCumparare.h"

#include <iostream>
#include <string>

using namespace std;

class CumparaComponenta: public Client, public Validari
{

private:
    char SEPARATOR_FISIER = ',';
    int idCumparare;
    int idComponenta;

    int ID_CUMPARARE = 0;
    int ID_COMPONENTA = 1;
    int NUME = 2;
    int PRENUME = 3;
    int EMAIL = 4;
    int NRTELEFON = 5;
    int ADRESA = 6;

    static const int NR_CARACTERISTICI = 7;

public:

    CumparaComponenta(int idCumparare =-1, int idComponenta = -1, string nume = "N/A", string prenume = "N/A", string email = "N/A", string nr_telefon = "N/A", string adresa = "N/A");
    CumparaComponenta(string linieFisier);

    ~CumparaComponenta();

    int getIdCumparare() const {return idCumparare;}
    int getIdComponenta() const {return idComponenta;}
    string getNume() const {return nume;}
    string getPrenume() const {return prenume;}

    void setIdCumparare(int id) {idCumparare = id;}
    void setIdComponenta(int id) {idComponenta = id;}
    void setNume(string n) { nume = n; }
    void setPrenume(string p) { prenume = p; }

    string Info() const;
    string ConversieLaSir_PentruFisier();
    friend istream& operator>>(istream& is, CumparaComponenta& cumparareComponenta);
    friend ostream& operator<<(ostream& os, const CumparaComponenta& cumparareComponenta);

    void citireCumparareExistenta();


};



#endif //CUMPARACOMPONENTA_H
