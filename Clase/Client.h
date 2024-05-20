//
//
//

#ifndef CLIENT_H
#define CLIENT_H

#include <iostream>
#include <string>

using namespace std;

class Client{
    protected:
        string nume;
        string prenume;
        string email;
        string nr_telefon;
        string adresa;

    public:
    Client(string nume = "", string prenume = "", string email = "",string nr_telefon = "",
            string adresa = "");
    ~Client();

    string getNume() const {return nume;}
    string getPrenume() const {return prenume;}
    string getEmail() const {return email;}
    string getNrTelefon() const { return nr_telefon; }
    string getAdresa() const { return adresa; }

    void setNume(string newNume) {nume = newNume;}
    void setPrenume(string newPrenume) {prenume = newPrenume;}
    void setEmail(string newEmail) {email = newEmail;}
    void setTelefon(string newNrTelefon) { nr_telefon = newNrTelefon; }
    void setAdresa(string newAdresa) { adresa = newAdresa; }


};

#endif //CLIENT_H
