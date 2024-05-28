//
//
//

#ifndef ADMINISTRARECONTURI_H
#define ADMINISTRARECONTURI_H
#include <iostream>
#include <string>
#include "Cont.h"

using namespace std;


class AdministrareConturi {

public:
    AdministrareConturi(string numeFisier = "Conturi.csv");
    ~AdministrareConturi();
    void AdaugaCont(Cont cont);
    vector<Cont> GetConturi(int& nrConturi);
    bool StergeContDupaEmail(string email);
    bool ModificaContDinFisier(string email, Cont contModificat);
    vector<Cont> CautaCont(string email, string tip);
    Cont CautaContDupaEmail(string email);

private:
    string numeFisier;
    static const int NR_MAX_CONTURI = 50;

};



#endif //ADMINISTRARECONTURI_H
