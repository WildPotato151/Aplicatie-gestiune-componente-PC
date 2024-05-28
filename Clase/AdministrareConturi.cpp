//
//
//

#include "AdministrareConturi.h"
#include "Cont.h"
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

AdministrareConturi::AdministrareConturi(string numeFisier) {
    this->numeFisier = numeFisier;
}

AdministrareConturi::~AdministrareConturi() {}

void AdministrareConturi::AdaugaCont(Cont cont)
{
    ofstream fisierCSV(numeFisier, ios::app);
    if (fisierCSV.is_open())
    {
        fisierCSV << cont.ConversieLaSir_PentruFisier() << endl;
        fisierCSV.close();
    }
    else {
        cout << "Eroare la deschiderea fișierului!" << endl;
    }
}

vector<Cont> AdministrareConturi::GetConturi(int& nrConturi)
{
    vector<Cont> conturi;
    ifstream fisier(numeFisier);
    string linieFisier;
    nrConturi = 0;

    while (getline(fisier, linieFisier)) {
        stringstream ss(linieFisier);
        string email, parola, tipCont;

        getline(ss, email, ',');
        getline(ss, parola, ',');
        getline(ss, tipCont, ',');

        conturi.push_back(Cont(email, parola, tipCont));
        nrConturi++;
    }

    fisier.close();
    return conturi;
}

bool AdministrareConturi::StergeContDupaEmail(string email)
{
    int nrConturi = 0;
    vector<Cont> conturi = GetConturi(nrConturi);
    bool contGasit = false;

    auto it = remove_if(conturi.begin(), conturi.end(), [&](Cont& cont) {
        return cont.getEmail() == email;
    });

    if (it != conturi.end()) {
        conturi.erase(it, conturi.end());
        contGasit = true;
    }

    ofstream fisier(numeFisier);
    if (fisier.is_open()) {
        for (const auto& cont : conturi) {
            fisier << cont.ConversieLaSir_PentruFisier() << endl;
        }
        fisier.close();
    } else {
        cout << "Eroare la deschiderea fișierului!" << endl;
    }

    return contGasit;
}

bool AdministrareConturi::ModificaContDinFisier(string email, Cont contModificat)
{
    int nrConturi = 0;
    vector<Cont> conturi = GetConturi(nrConturi);
    bool contGasit = false;

    for (auto& cont : conturi) {
        if (cont.getEmail() == email) {
            cont = contModificat;
            contGasit = true;
            break;
        }
    }

    ofstream fisier(numeFisier);
    if (fisier.is_open()) {
        for (const auto& cont : conturi) {
            fisier << cont.ConversieLaSir_PentruFisier() << endl;
        }
        fisier.close();
        return contGasit;
    } else {
        cout << "Eroare la deschiderea fișierului!" << endl;
        return false;
    }
}

vector<Cont> AdministrareConturi::CautaCont(string email, string tip) {
    vector<Cont> results;
    int nrConturi = 0;

    vector<Cont> conturi = GetConturi(nrConturi);
    string emailCautat = Validari::toLowercase(email);

    for (const auto& cont : conturi) {
        string emailGasit = Validari::toLowercase(cont.getEmail());

        if ((!email.empty() && (emailGasit.find(emailCautat) == string::npos)) ||
            (!tip.empty() && cont.getTipCont() != tip)) {
            continue;
            }

        results.push_back(cont);
    }

    return results;
}

Cont AdministrareConturi::CautaContDupaEmail(string email) {
    int nrConturi = 0;
    vector<Cont> conturi = GetConturi(nrConturi);

    for (const auto& cont : conturi) {
        if (cont.getEmail() == email) {
            return cont;
        }
    }
    return Cont();
}