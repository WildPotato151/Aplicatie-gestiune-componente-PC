//
//
//

#include "AdministrareCumparare.h"


#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

AdministrareCumparare::AdministrareCumparare(string numeFisier) {
    this->numeFisier = numeFisier;
}

AdministrareCumparare::~AdministrareCumparare() {}

void AdministrareCumparare::AdaugaComanda(CumparaComponenta cumparaComponenta) {

    ofstream fisierCSV(numeFisier, ios::app);

    if(fisierCSV.is_open()) {
        fisierCSV <<cumparaComponenta.ConversieLaSir_PentruFisier() << endl;
        fisierCSV.close();
    }
}

vector<CumparaComponenta> AdministrareCumparare::GetComanda(int &nrCumparari) {

    vector<CumparaComponenta> cumparaComponenta;
    ifstream fisier(numeFisier);
    string linieFisier;
    nrCumparari = 0;

    while (getline(fisier, linieFisier)) {
        cumparaComponenta.push_back(CumparaComponenta(linieFisier));
        nrCumparari++;
    }

    fisier.close();
    return cumparaComponenta;
}

bool AdministrareCumparare::stergereComandaDupaID(int idCumparare) {

    int nrCumparari = 0;
    vector<CumparaComponenta> cumparaComponente = GetComanda(nrCumparari);
    bool sters = false;

    ofstream fisier(numeFisier);

    if (fisier.is_open()) {
        for ( auto& cumparaComponenta : cumparaComponente) {
            if (cumparaComponenta.getIdCumparare() != idCumparare) {
                fisier << cumparaComponenta.ConversieLaSir_PentruFisier() << endl;
            } else {
                sters = true;
            }
        }
        fisier.close();
    } else {
        cout << "Eroare la deschiderea fisierului! " << endl;
        return false;
    }
    return sters;

}

bool AdministrareCumparare::ModificaComandaDinFisier(int idCumparare, CumparaComponenta cumparaComponentaModificat) {

    int nrCumparari = 0;
    vector<CumparaComponenta> cumparaComponente = GetComanda(nrCumparari);
    bool modificat = false;

    ofstream fisier(numeFisier);

    if (fisier.is_open()) {
        for ( auto& cumparaComponenta : cumparaComponente) {
            if (cumparaComponenta.getIdCumparare() == idCumparare) {
                fisier << cumparaComponentaModificat.ConversieLaSir_PentruFisier() << endl;
                modificat = true;
            } else {
                fisier << cumparaComponenta.ConversieLaSir_PentruFisier() << endl;
            }
        }
        fisier.close();
    } else {
        cout << "Eroare la deschiderea fisierului!!!" << endl;
        return false;
    }
    return modificat;
}

vector<CumparaComponenta> AdministrareCumparare::CautaComanda(string nume, string prenume, string email, string nr_telefon, int idCumparare, int idComponenta) {

    vector<CumparaComponenta> results;
    int nrCumparari = 0;
    vector<CumparaComponenta> cumparaComponente = GetComanda(nrCumparari);

    string numeCautat = Validari::toLowercase(nume);
    string prenumeCautat = Validari::toLowercase(prenume);
    string emailCautat = Validari::toLowercase(email);
    string nrtelefonCautat = Validari::toLowercase(nr_telefon);

    for (const auto& cumparaComponenta : cumparaComponente) {
        string numeGasit = Validari::toLowercase(cumparaComponenta.getNume());
        string prenumeGasit = Validari::toLowercase(cumparaComponenta.getPrenume());
        string emailGasit = Validari::toLowercase(cumparaComponenta.getEmail());
        string nrtelefonGasit = cumparaComponenta.getNrTelefon();

        if ((!nume.empty() && (numeGasit.find(numeCautat) == string::npos)) ||
            (!prenume.empty() && (prenumeGasit.find(prenumeCautat) == string::npos)) ||
            (!email.empty() && (emailGasit.find(emailCautat) == string::npos)) ||
            (!nr_telefon.empty() && (nrtelefonGasit.find(nrtelefonCautat) == string::npos)) ||
            (idCumparare != -1 && cumparaComponenta.getIdCumparare() != idCumparare) ||
            (idComponenta != -1 && cumparaComponenta.getIdComponenta() != idComponenta)) {
            continue;
            }
        results.push_back(cumparaComponenta);
    }
    return results;

}

CumparaComponenta AdministrareCumparare::CautaCommandaDupaID(int idCumparare) {

    int nrCumparari = 0;
    vector<CumparaComponenta> cumparaComponente = GetComanda(nrCumparari);

    for (const auto& cumparaComponenta : cumparaComponente) {
        if (cumparaComponenta.getIdCumparare() == idCumparare) {
            return cumparaComponenta;
        }
    }
    return CumparaComponenta();

}




