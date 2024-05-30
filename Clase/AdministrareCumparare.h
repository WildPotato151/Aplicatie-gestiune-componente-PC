//
//
//

#ifndef ADMINISTRARECUMPARARE_H
#define ADMINISTRARECUMPARARE_H

#include "CumparaComponenta.h"

#include <iostream>
#include <string>
using namespace std;


class AdministrareCumparare {

public:
    AdministrareCumparare(string numeFisier = "Comenzi.csv");
    ~AdministrareCumparare();
    void AdaugaComanda(CumparaComponenta cumparaComponenta);
    vector <CumparaComponenta> GetComanda(int& nrCumparari);
    bool stergereComandaDupaID(int idCumparare);
    bool ModificaComandaDinFisier(int idCumparare, CumparaComponenta cumparaComponentaModificat);
    vector <CumparaComponenta> CautaComanda(string nume, string prenume, string email, string nr_telefon, int idCumparare, int idComponenta);
    CumparaComponenta CautaCommandaDupaID(int idCumparare);

private:
    string numeFisier;
    static const int NR_MAX_COMENZI = 50;


};



#endif //ADMINISTRARECUMPARARE_H
