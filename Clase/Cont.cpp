//
//
//

#include "Cont.h"


Cont::Cont(string email, string parola, string tip_cont) {
    this->email = email;
    this->parola = parola;
    this->tip_cont = tip_cont;
}

Cont::Cont(int _ignore_, string linieFisier) {
    vector<string> dateFisier = split(linieFisier, SEPARATOR_FISIER);
    if (dateFisier.size() < NR_CARACTERISTICI) {
        throw runtime_error("Date lipsa! linieFisier: " + linieFisier );
    }

    email = dateFisier[EMAIL];
    parola = dateFisier[PAROLA];
    tip_cont = dateFisier[TIP_CONT];
}

Cont::~Cont() {

}

string Cont::ConversieLaSir_PentruFisier() const {
    string output = email + SEPARATOR_FISIER +
                    parola + SEPARATOR_FISIER +
                    tip_cont + SEPARATOR_FISIER;

    return output;
}

istream& operator>>(istream& is, Cont& cont) {
    string input;
    cout << "Introdu email-ul: ";
    cin >> input;
    while(!Validari::validareEmail(input)) {
        cout << "Email invalid, reintrodu email-ul...";
        cin >> input;
    }
    cont.email = input;

    cout << "Introdu parola: ";
    system("stty -echo");
    cin >> cont.parola;
    system("stty echo");

    return is;
}

void Cont::citireContExistent() {
    string input;

    cout << "Introdu email-ul (default: " << email << "): ";
    cin.ignore();
    getline(cin, input);
    while(!Validari::validareEmail(input) && !input.empty()) {
        cout << "Email invalid, reintrodu email-ul...";
        getline(cin, input);
    }
    if (!input.empty()) {
        email = input;
    }

    cout << "Introdu parola ('ENTER' pentru a nu o modifica): ";
    system("stty -echo");
    getline(cin, input);
    if (!input.empty()) {
        parola = input;
    }
    system("stty echo");

    cout << endl << "(Tip cont actual: " << tip_cont << ")\n";
    tip_cont = Cont::selecteazaTipCont();

}

string Cont::selecteazaTipCont() {
    int optiune = -1;
    string tip_cont;

    cout << "Selectati tipul contului: " << endl;
    cout << "1. Client" << endl;
    cout << "2. Administrator" << endl;
    cout << "Introduceti o optiune... ";
    while (optiune < 1 || optiune > 3) {
        cin >> optiune;

        switch (optiune) {
            case 1:
                tip_cont = "Client";
            break;
            case 2:
                tip_cont = "Administrator";
            break;

            default:
                cout << "Optiune invalida. Selecteaza o optiune valida... ";
            break;
        }
    }

    return tip_cont;
}