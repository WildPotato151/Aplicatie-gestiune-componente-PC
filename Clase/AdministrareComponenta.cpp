//
// 
//

#include "AdministrareComponenta.h"

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>
using namespace std;

AdministrareComponenta::AdministrareComponenta(string numeFisier)
{
    this->numeFisier = numeFisier;
}

AdministrareComponenta::~AdministrareComponenta() {}

void AdministrareComponenta::AdaugaComponenta(Componenta componenta) {
    ofstream fisierCSV(numeFisier, ios::app);
    if (fisierCSV.is_open())
    {
        fisierCSV << componenta.ConversieToString_FisierCSV() << endl;
        fisierCSV.close();
    }
}

vector<Componenta> AdministrareComponenta::GetComponente(int& nrComponente) {
    vector<Componenta> componente(NR_MAX_COMPONENTE);
    ifstream fisier(numeFisier);
    string linieFisier;
    nrComponente = 0;

    while (getline(fisier, linieFisier)) {
        stringstream ss(linieFisier);
        string idStr, tip, brand, model, specs, pretStr, stockStr;

        getline(ss, idStr, ',');
        getline(ss, tip, ',');
        getline(ss, brand, ',');
        getline(ss, model, ',');
        getline(ss, specs, ',');
        getline(ss, pretStr, ',');
        getline(ss, stockStr, ',');

        int id = stoi(idStr);
        float pret = stof(pretStr);
        bool stock = (stockStr == "1");

        componente[nrComponente++] = Componenta(id, tip, brand, model, specs, pret, stock);
    }

    fisier.close();
    return componente;
}

bool AdministrareComponenta::StergeComponentaDupaID(int idComponenta)
{
    int nrComponente = 0;
    vector<Componenta> componente = GetComponente(nrComponente);

    for (auto it = componente.begin(); it != componente.end(); ++it) {
        if (it->getID() == idComponenta) {
            componente.erase(it);

            ofstream fisier(numeFisier);
            if (fisier.is_open()) {
                for (int i = 0; i < nrComponente - 1; i++) {
                    fisier << componente[i].ConversieToString_FisierCSV() << endl;
                }
                fisier.close();
            } else {
                cout << "Eroare la deschiderea fisierului!" << endl;
            }

            return true;
        }
    }

    return false;
}

bool AdministrareComponenta::ModificaComponentaDinFisier(int idComponenta, Componenta componentaModificata) {
    int nrComponente = 0;
    vector<Componenta> componente = GetComponente(nrComponente);

    for (int i = 0; i < nrComponente; i++) {
        if (componente[i].getID() == idComponenta) {
            componente[i] = componentaModificata;

            ofstream fisier(numeFisier);
            if (fisier.is_open()) {
                for (int j = 0; j < nrComponente; j++) {
                    fisier << componente[j].ConversieToString_FisierCSV() << endl;
                }
                fisier.close();
                return true;
            } else {
                cout << "Eroare la deschiderea fisierului!" << endl;
                return false;
            }
        }
    }

    return false;
}

vector<Componenta> AdministrareComponenta::CautaComponenta(string tip, string brand, string model, float pretMin, float pretMax, int idComponenta, bool stock) {
    vector<Componenta> results;

    int nrComponente = 0, index = 1;
    vector<Componenta> componente = GetComponente(nrComponente);

    for (Componenta componenta : componente) {
        if (index > nrComponente) break;

        if ((!tip.empty() && componenta.getTip() != tip) ||
            (!brand.empty() && componenta.getBrand() != brand) ||
            (!model.empty() && componenta.getModel() != model) ||
            (pretMin > 0 && stof(componenta.getPret()) < pretMin) ||
            (pretMax > 0 && stof(componenta.getPret()) > pretMax) ||
            (stock && !componenta.esteStock()) ||
            (idComponenta != -1 && componenta.getID() != idComponenta)) {
            continue;
        }

        results.push_back(componenta);
        index++;
    }

    return results;
}

Componenta AdministrareComponenta::CautaComponentaDupaID(int idComponenta) {
    int nrComponente = 0;
    vector<Componenta> componente = GetComponente(nrComponente);

    for (const auto& componenta : componente) {
        if (componenta.getID() == idComponenta) {
            return componenta;
        }
    }
    return Componenta();
}
