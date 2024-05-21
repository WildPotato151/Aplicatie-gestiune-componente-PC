//
//
//

#ifndef ADMINISTRARECOMPONENTA_H
#define ADMINISTRARECOMPONENTA_H

#include <iostream>
#include <string>
#include "Componenta.h"
#include "Validari.h"

using namespace std;

class AdministrareComponenta {

public:
    AdministrareComponenta(string numeFisier = "Componente.csv");
    ~AdministrareComponenta();


    void AdaugaComponenta(Componenta componenta);
    vector<Componenta> GetComponente(int& nrComponente);
    bool StergeComponentaDupaID(int idComponenta);
    bool ModificaComponentaDinFisier(int idComponenta, Componenta componentaModificata);
    vector<Componenta> CautaComponenta(string tip, string brand, string model, float pretMin, float pretMax, int idComponenta, bool stock);
    Componenta CautaComponentaDupaID(int idComponenta);

private:
    string numeFisier;
    static const int NR_MAX_COMPONENTE = 50;

};



#endif //ADMINISTRARECOMPONENTA_H
