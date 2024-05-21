//
//
//

#ifndef CONT_H
#define CONT_H

#include <iostream>
#include <string>

#include "Validari.h"

using namespace std;


class Cont : public Validari{

private:
    const char SEPARATOR_FISIER = ',';
    string email;
    string parola;
    string tip_cont;

    int EMAIL = 0;
    int PAROLA =1;
    int TIP_CONT = 2;

    static const int NR_CARACTERISTICI = 3;

public:
    Cont(string email = "", string parola = "", string tip_cont = "");
    Cont(int _ignore_, string linieFisier);
    ~Cont();

    string getEmail() const { return email; }
    string getParola() const { return parola; }
    string getTipCont() const { return tip_cont; }

    void setEmail(const string& newEmail) { email = newEmail; }
    void setParola(const string& newParola) { parola = newParola; }
    void setTipCont(const string& newTipCont) { tip_cont = newTipCont; }

    string ConversieLaSir_PentruFisier() const;
    friend istream& operator>>(istream& is, Cont& cont);

    void citireContExistent();

    static string selecteazaTipCont();

};



#endif //CONT_H
