#include "Clase/Client.h"
#include "Clase/Componenta.h"
#include "Clase/Cont.h"
#include "Clase/Validari.h"
#include "Clase/AdministrareComponenta.h"
#include "Clase/AdministrareConturi.h"
#include "Clase/AdministrareCumparare.h"
#include "Clase/CumparaComponenta.h"

#include "Clase/Client.cpp"
#include "Clase/Componenta.cpp"
#include "Clase/Cont.cpp"
#include "Clase/AdministrareComponenta.cpp"
#include "Clase/AdministrareConturi.cpp"
#include "Clase/AdministrareCumparare.cpp"
#include "Clase/CumparaComponenta.cpp"
#include "single_include/tabulate/tabulate.hpp"



#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
using namespace tabulate;

int main()
{

    return 0;
}


void update_nrComenzi_nextIdComanda(int& nrComenzi, int& nextIdComanda, AdministrareCumparare adminComanda)
{
    vector <CumparaComponenta> cumparaComponente = adminComanda.GetComanda(nrComenzi);
    if(nrComenzi !=0)
        nextIdComanda = cumparaComponente[nrComenzi - 1].getIdCumparare() + 1;
}

void update_nrComponente_nextIdComponenta(int& nrComponente, int& nextIdComponenta, AdministrareComponenta adminComponenta )
{
    vector <Componenta> componente = adminComponenta.GetComponente(nrComponente);
    if(nrComponente !=0)
        nextIdComponenta = componente[nrComponente - 1].getID() + 1;
}

void afisareTabelComponente(const vector<Componenta>& componente, int nrComponente)
{
    if(componente.empty()) {
        cout<<"Nu exsita componente de afisat!"<<endl;
        return;
    }

    Table tComponente;
    tComponente.add_row({"ID","Tip;", "Brand", "Model", "Specs", "Pret", "Stock"});

    for (int i = 0; i< nrComponente; i++) {

        tComponente.add_row({componente[i].getID() == -1 ? "N/A" : to_string(componente[i].getID()),
            componente[i].getTip(),
            componente[i].getBrand(),
            componente[i].getModel(),
            componente[i].getSpecs(),
            (componente[i].getPret() == -1.0f ? "N/A" : to_string(componente[i].getPret())) + "RON",
            (componente[i].esteStock() ? "Da" : "Nu")});
    }
    tComponente[0].format()
    .font_style({FontStyle::bold})
    .padding(1)
    .font_align(FontAlign::center);

    cout << tComponente<<endl;

}

void afisareComenzi (const vector<CumparaComponenta>& comenzi, int nrComenzi) {
    if (comenzi.empty()) {
        cout << "Nu exista comenzi de afisat." << endl;
        return;
    }

    Table tComenzi;
    AdministrareComponenta adminComponenta = AdministrareComponenta();

    tComenzi.add_row({"ID", "Componenta", "Nume", "Prenume", "Email", "Numar telefon", "Adresa" });

    for (int i = 0; i < nrComenzi; i++) {

        int idComponenta = comenzi[i].getIdComponenta();
        string componenta = adminComponenta.CautaComponentaDupaID(idComponenta).getBrand() + ' ' + adminComponenta.CautaComponentaDupaID(idComponenta).getModel() + " (#" + to_string(idComponenta) + ")";
        tComenzi.add_row({(comenzi[i].getIdCumparare() == -1 ? "N/A" : to_string(comenzi[i].getIdCumparare())),
            (comenzi[i].getIdComponenta() == -1 ? "N/A" : componenta),
            comenzi[i].getNume(),
            comenzi[i].getPrenume(),
            comenzi[i].getEmail(),
            comenzi[i].getNrTelefon(),
            comenzi[i].getAdresa() });
    }
    tComenzi[0].format()
            .font_style({FontStyle::bold})
            .padding(1)
            .font_align(FontAlign::center);

    cout<<tComenzi<<endl;

}

