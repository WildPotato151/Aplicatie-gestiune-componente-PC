#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#include <algorithm>

#undef byte

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





using namespace std;
using namespace tabulate;

void update_nrComenzi_nextIdComanda(int& nrComenzi, int& nextIdComanda, AdministrareCumparare& adminComanda);
void update_nrComponente_nextIdComponenta(int& nrComponente, int& nextIdComponenta, AdministrareComponenta adminComponenta);
void afisareTabelComponente(const vector<Componenta>& componente, int nrComponente);
void afisareTabelComenzi (const vector<CumparaComponenta>& comenzi, int nrComenzi);
void afisareTabelConturi( const vector<Cont>& conturi, int nrConturi);
int meniuCautareComponenta(vector<Componenta> componente);
int meniuCautareComanda(vector<CumparaComponenta> comenzi);
string meniuCautareCont(vector<Cont> conturi);

int main()
{

    int optiune;
    int nrComenzi=0, nextIdComanda=0, nrComponente=0, nextIdComponenta=0, nrConturi=0;
    int mod = 1;

    AdministrareCumparare adminComanda = AdministrareCumparare();
     update_nrComenzi_nextIdComanda(nrComenzi, nextIdComanda, adminComanda);



    AdministrareComponenta adminComponente = AdministrareComponenta();
    update_nrComponente_nextIdComponenta(nrComponente, nextIdComponenta, adminComponente);

    AdministrareConturi adminConturi = AdministrareConturi();

    vector<CumparaComponenta> comenzi = adminComanda.GetComanda(nrComenzi);
    CumparaComponenta comanda;

    vector<Componenta> componente = adminComponente.GetComponente(nrComponente);
    Componenta componenta_meniu1;
    Componenta componenta_meniu2;

    vector<Cont> conturi = adminConturi.GetConturi(nrConturi);
    Cont cont;
    Cont cont_autentificare;
    Cont cont_verificare, cont_verificare_exista;

    int idComponentaSelectata_meniu1 = -1;
    bool infoComanda = false;
    int idComandaSelectat_meniu2 = -1, idComponentaSelectata_meniu2 = -1;
    bool infoComponenta = false;
    string comandaSelectata, componentalSelectat, componentaSelectata_client, contSelectat, ContAuthString, emailSelectat;
    bool autentificat = false;

    do
    {
        //system("clear");
        system("cls"); // pentru windows

        if(mod == 1) {
            ContAuthString = cont_verificare.getEmail() + " (" + cont_verificare.getTipCont() + ") ";
            componentaSelectata_client = adminComponente.CautaComponentaDupaID(idComponentaSelectata_meniu1).getTip() + ' '
                                         + adminComponente.CautaComponentaDupaID(idComponentaSelectata_meniu1).getModel()
                                         + " (#" + to_string(idComponentaSelectata_meniu1) + ")";
            cout << " -= Cumpara componente pc =-\n";
            cout << "1. " << (!autentificat ? "Autentificare" : "Log out") << "\n";
            cout << "2. Inregistrare\n";
            cout << "3. Comenzile mele\n";
            cout << '\n';
            cout << "Cont curent: " << (!autentificat ? "N/A (te poti autentifica accesand optiunea \"1. Autentificare\")" : ContAuthString) << "\n";
            cout << '\n';
            cout << "-=Comanda o componenta=-\n";
            cout << "4. Cauta/Selecteaza componenta\n";
            cout << "5. " << (!infoComanda ? "Introduce" : "Modifica") << " informatii comanda\n";
            cout << "6. Afisare informatii comanda\n";
            cout << "7. Salveaza informatii comanda\n";
            cout << '\n';
            cout << "Componenta selectata: " << (idComponentaSelectata_meniu1 == -1 ? "N/A (poti selecta o componenta accesand optiunea \"4. Cauta/Selecteaza componenta\")" : componentaSelectata_client) << "\n";
            cout << '\n';
            cout << "8. Meniu admin\n";
            cout << "0. Inchidere program\n";
            cout << "\nIntroduceti o optiune... ";
            cin >> optiune;
            cout << endl;
            switch (toupper(optiune)) {
                case 1: {
                    if(!autentificat) {
                        cin >> cont_autentificare;
                        cout << endl << endl;
                        cont_verificare = adminConturi.CautaContDupaEmail(cont_autentificare.getEmail());
                        if(cont_verificare.getEmail() != cont_autentificare.getEmail()) {
                            cout << "Eroare! Nu s-a gasit niciun cont cu email-ul introdus.";
                        }
                        else if(cont_verificare.getParola() != cont_autentificare.getParola()) {
                            cout << "Eroare! Parola gresita.";
                        }
                        else {
                            autentificat = true;
                            cout << "Autentificare cu succes.";
                        }
                    }
                    else {
                        autentificat = false;
                        cout << "Log out cu succes.";
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }
                case 2: {
                    cin >> cont;
                    cout << endl << endl;
                    cont.setTipCont("Client");
                    cont_verificare_exista = adminConturi.CautaContDupaEmail(cont.getEmail());
                    if(cont_verificare_exista.getEmail() == cont.getEmail()) {
                        cout << "Eroare! Contul deja exista!";
                    }
                    else {
                        adminConturi.AdaugaCont(cont);
                        cout << "Inregistrare cu succes.";
                        cont = Cont();
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }
                case 3: {
                    if(!autentificat) {
                        cout << "Eroare! Aceasta optiune necesita autentificare.";
                    }
                    else {
                        vector<CumparaComponenta> searchResults = adminComanda.CautaComanda("", "", cont_autentificare.getEmail(), "", -1, -1);

                        if (searchResults.empty()) {
                            cout << "Nicio comanda gasita.";
                        } else {
                            cout << "Comanda gasita:" << endl;
                            afisareTabelComenzi(searchResults, searchResults.size());
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }
                case 4: {
                    idComponentaSelectata_meniu1 = meniuCautareComponenta(componente);
                    comanda.setIdCumparare(idComponentaSelectata_meniu1);

                    break;
                }

                case 5: {
                    if(idComponentaSelectata_meniu1 != -1) {
                        if(!infoComanda) {
                            cin >> comanda;
                            comanda.setEmail(cont_autentificare.getEmail());
                            infoComanda = true;
                        }
                        else {
                            comanda.citireCumparareExistenta();
                        }
                    }
                    else
                        cout << "Eroare! Nu a fost selectata o componenta!";

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 6: {
                    if(!infoComanda)
                        cout << "Eroare! Nu au fost introduse informatiile!";
                    else
                        cout << comanda;

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 7: {
                    if(!infoComanda)
                        cout << "Eroare! Nu au fost introduse informatiile!";
                    else if(!autentificat) {
                        cout << "Eroare! Aceasta optiune necesita autentificare.";
                    }
                    else {
                        update_nrComenzi_nextIdComanda(nrComenzi, nextIdComanda, adminComanda);
                        comanda.setIdCumparare(nextIdComanda);
                        adminComanda.AdaugaComanda(comanda);

                        componenta_meniu1 = Componenta(adminComponente.CautaComponentaDupaID(idComponentaSelectata_meniu1));
                        componenta_meniu1.setStock(false);
                        adminComponente.ModificaComponentaDinFisier(idComponentaSelectata_meniu1, componenta_meniu1);

                        idComponentaSelectata_meniu1 = -1;
                        cout << "Salvat";
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }


                case 8: {
                    if(!autentificat) {
                        cout << "Eroare! Aceasta optiune necesita autentificare.";
                        cin.ignore();
                        cin.get();
                    }
                    else {
                        if ("Administrator" != cont_verificare.getTipCont()) {
                            cout << "Eroare! Permisiune insuficienta.";
                            cin.ignore();
                            cin.get();
                        } else {
                            mod = 3;
                            cout << "Succes.";
                        }
                    }

                    break;
                }

                case 0:
                    exit(0);

                default:
                    cout << "Optiune invalida. Va rugam selectati o optiune valida.\n";

                    cin.ignore();
                    cin.get();
            }
        }
        else if(mod == 2) {
            comandaSelectata = adminComanda.CautaCommandaDupaID(idComandaSelectat_meniu2).getNume() + ' '
                                  + adminComanda.CautaCommandaDupaID(idComandaSelectat_meniu2).getPrenume()
                                  + " (#" + to_string(idComandaSelectat_meniu2) + ")";
            componentalSelectat =
                    adminComponente.CautaComponentaDupaID(idComponentaSelectata_meniu2).getTip() + ' '
                    + adminComponente.CautaComponentaDupaID(idComponentaSelectata_meniu2).getModel()
                    + " (#" + to_string(idComponentaSelectata_meniu2) + ")";

            cout << " COMENZI\n";
            cout << "1. Afisare comenzi\n";
            cout << "2. Cauta/Selecteaza comanda\n";
            cout << "3. Modifica comanda\n";
            cout << "4. Sterge comanda\n";
            cout << '\n';
            cout << "Comanda selectata: " << (idComandaSelectat_meniu2 == -1
                                                 ? "N/A (poti selecta o comanda accesand optiunea \"2. Cauta/Selecteaza comanda\")"
                                                 : comandaSelectata) << "\n";
            cout << '\n';
            cout << " COMPONENTE\n";
            cout << "5. " << (!infoComponenta ? "Introduce" : "Modifica")
                 << " informatii componenta\n"; // validare date
            cout << "6. Afisare informatii componenta\n";
            cout << "7. Salvare informatii componenta\n";
            cout << "8. Afisare componente\n";
            cout << "9. Cauta/Selecteaza componenta\n";
            cout << "10. Modifica informatii componenta\n";
            cout << "11. Sterge componenta\n";
            cout << '\n';
            cout << "Componenta selectat: " << (idComponentaSelectata_meniu2 == -1
                                                 ? "N/A (poti selecta o componenta accesand optiunea \"10. Cauta/Selecteaza componenta\")"
                                                 : componentalSelectat) << "\n";
            cout << '\n';
            cout << "12. Meniu clienti\n";
            cout << "13. Meniu admin\n";
            cout << "0. Inchidere program\n";
            cout << "\nIntroduceti o optiune... ";
            cin >> optiune;
            cout << endl;
            switch (toupper(optiune)) {
                case 1: {
                    comenzi = adminComanda.GetComanda(nrComenzi);
                    afisareTabelComenzi(comenzi, nrComenzi);

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 2: {
                    idComandaSelectat_meniu2 = meniuCautareComanda(comenzi);
                    break;
                }

                case 3: {
                    string raspuns;

                    if (idComandaSelectat_meniu2 == -1) {
                        cout
                                << "Nu ati selectat nicio comanda. Va rugam selectati o comanda valida accesand optiunea \"2. Cauta/Selecteaza comanda\"."
                                << endl;
                    } else {
                        bool confirmare = false;
                        while (!confirmare) {
                            cout << "Comanda selectata: " << comandaSelectata << "\n";
                            cout << "Doriti sa modificati aceasta comanda? (Da/Nu): ";
                            cin >> raspuns;
                            cout << "\n";

                            if (raspuns == "Da" || raspuns == "da" || raspuns == "DA" || raspuns == "dA" ||
                                raspuns == "d" || raspuns == "D") {
                                CumparaComponenta comandaModificata = CumparaComponenta(
                                        adminComanda.CautaCommandaDupaID(idComandaSelectat_meniu2));
                                comandaModificata.citireCumparareExistenta();

                                bool rezultat = adminComanda.ModificaComandaDinFisier(idComandaSelectat_meniu2,
                                                                                            comandaModificata);
                                if (rezultat) {
                                    cout << "Comanda a fost modificata cu succes." << endl;
                                } else {
                                    cout << "Nu s-a putut gasi comanda pentru modificare." << endl;
                                }
                                confirmare = true;
                            } else if (raspuns == "Nu" || raspuns == "nu" || raspuns == "NU" || raspuns == "nU" ||
                                       raspuns == "n" || raspuns == "N") {
                                cout << "Modificarea comanzii a fost anulata." << endl;
                                confirmare = true;
                            } else {
                                cout << "Raspuns invalid. Va rugam introduceti 'Da' sau 'Nu'." << endl;
                                cin.ignore();
                                cin.get();
                                for (int i = 1; i <= 5; i++)
                                    cout << "\33[2K\r\033[A\r";
                            }
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 4: {
                    string raspuns;

                    if (idComandaSelectat_meniu2 == -1) {
                        cout
                                << "Nu ati selectat nicio comanda. Va rugam selectati o comanda valida accesand optiunea \"2. Cauta/Selecteaza comanda\"."
                                << endl;
                    } else {
                        bool confirmare = false;
                        while (!confirmare) {
                            cout << "Comanda selectata: " << comandaSelectata << "\n";
                            cout << "Doriti sa stergeti aceasta comanda? (Da/Nu): ";
                            cin >> raspuns;
                            cout << "\n";

                            if (raspuns == "Da" || raspuns == "da" || raspuns == "DA" || raspuns == "dA" ||
                                raspuns == "d" || raspuns == "D") {
                                bool rezultat = adminComanda.stergereComandaDupaID(idComandaSelectat_meniu2);
                                if (rezultat) {
                                    idComandaSelectat_meniu2 = -1;
                                    cout << "Comanda a fost stearsa cu succes." << endl;
                                } else {
                                    cout << "Nu s-a putut gasi comanda pentru stergere." << endl;
                                }
                                confirmare = true;
                            } else if (raspuns == "Nu" || raspuns == "nu" || raspuns == "NU" || raspuns == "nU" ||
                                       raspuns == "n" || raspuns == "N") {
                                cout << "Stergerea comenzii a fost anulata." << endl;
                                confirmare = true;
                            } else {
                                cout << "Raspuns invalid. Va rugam introduceti 'Da' sau 'Nu'." << endl;
                                cin.ignore();
                                cin.get();
                                for (int i = 1; i <= 5; i++)
                                    cout << "\33[2K\r\033[A\r";
                            }
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 5: {
                    if (!infoComponenta) {
                        cin >> componenta_meniu2;
                        infoComponenta = true;
                    } else {
                        componenta_meniu2.citireComponentaExistenta();
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 6: {
                    if (infoComponenta)
                        cout << componenta_meniu2;
                    else
                        cout << "Eroare! Nu au fost introduse informatiile!";


                    cin.ignore();
                    cin.get();
                    break;
                }

                case 7: {
                    if (infoComponenta) {
                        update_nrComponente_nextIdComponenta(nrComponente, nextIdComponenta, adminComponente);
                        componenta_meniu2.setId(nextIdComponenta);
                        adminComponente.AdaugaComponenta(componenta_meniu2);
                        cout << "Componenta salvata";

                        infoComponenta = false;
                        componenta_meniu2 = Componenta();
                    } else
                        cout << "Eroare! Nu au fost introduse informatiile!";

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 8: {
                    componente = adminComponente.GetComponente(nrComponente);
                    afisareTabelComponente(componente, nrComponente);

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 9: {
                    idComponentaSelectata_meniu2 = meniuCautareComponenta(componente);
                    break;
                }

                case 10: {
                    string raspuns;

                    if (idComponentaSelectata_meniu2 == -1) {
                        cout << "Nu ati selectat nicio componenta. Va rugam selectati o componenta valid accesand optiunea \"10. Cauta/Selecteaza componenta\"...";
                    } else {
                        bool confirmare = false;
                        while (!confirmare) {
                            cout << "Componenta selectata: " << componentalSelectat << "\n";
                            cout << "Doriti sa modificati aceasta componenta? (Da/Nu): ";
                            cin >> raspuns;
                            cout << "\n";

                            if (raspuns == "Da" || raspuns == "da" || raspuns == "DA" || raspuns == "dA" ||
                                raspuns == "d" || raspuns == "D") {
                                Componenta componentaModificata = Componenta(
                                        adminComponente.CautaComponentaDupaID(idComponentaSelectata_meniu2));
                                componentaModificata.citireComponentaExistenta();

                                bool rezultat = adminComponente.ModificaComponentaDinFisier(
                                        idComponentaSelectata_meniu2, componentaModificata);
                                if (rezultat) {
                                    cout << "Componenta a fost modificata cu succes." << endl;
                                } else {
                                    cout << "Nu s-a putut gasi componenta pentru modificare." << endl;
                                }
                                confirmare = true;
                            } else if (raspuns == "Nu" || raspuns == "nu" || raspuns == "NU" || raspuns == "nU" ||
                                       raspuns == "n" || raspuns == "N") {
                                cout << "Modificarea componentei a fost anulata." << endl;
                                confirmare = true;
                            } else {
                                cout << "Raspuns invalid. Va rugam introduceti 'Da' sau 'Nu'." << endl;
                                cin.ignore();
                                cin.get();
                                for (int i = 1; i <= 5; i++)
                                    cout << "\33[2K\r\033[A\r";
                            }
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 11: {
                    string raspuns;

                    if (idComponentaSelectata_meniu2 == -1) {
                        cout << "Nu ati selectat nicio componenta. Va rugam selectati o componenta valida accesand optiunea \"10. Cauta/Selecteaza componenta\"...";
                    } else {
                        bool confirmare = false;
                        while (!confirmare) {
                            cout << "Componenta selectat: " << componentalSelectat << "\n";
                            cout << "Doriti sa stergeti aceasta componenta? (Da/Nu): ";
                            cin >> raspuns;
                            cout << "\n";

                            if (raspuns == "Da" || raspuns == "da" || raspuns == "DA" || raspuns == "dA" ||
                                raspuns == "d" || raspuns == "D") {
                                bool rezultat = adminComponente.StergeComponentaDupaID(idComponentaSelectata_meniu2);
                                if (rezultat) {
                                    idComponentaSelectata_meniu2 = -1;
                                    cout << "Componenta a fost stearsa cu succes." << endl;
                                } else {
                                    cout << "Nu s-a putut gasi componenta pentru stergere." << endl;
                                }
                                confirmare = true;
                            } else if (raspuns == "Nu" || raspuns == "nu" || raspuns == "NU" || raspuns == "nU" ||
                                       raspuns == "n" || raspuns == "N") {
                                cout << "Stergerea componentei a fost anulata." << endl;
                                confirmare = true;
                            } else {
                                cout << "Raspuns invalid. Va rugam introduceti 'Da' sau 'Nu'." << endl;
                                cin.ignore();
                                cin.get();
                                for (int i = 1; i <= 5; i++)
                                    cout << "\33[2K\r\033[A\r";
                            }
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }


                case 12: {
                    mod = 1;

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 13: {
                    if (!autentificat) {
                        cout << "Eroare! Aceasta optiune necesita autentificare.";
                        cin.ignore();
                        cin.get();
                    } else {
                        if ("Administrator" != cont_verificare.getTipCont()) {
                            cout << "Eroare! Permisiune insuficienta.";
                            cin.ignore();
                            cin.get();
                        }
                        else {
                            mod = 3;
                        }
                    }

                    break;
                }

                case 0:
                    exit(0);

                default:
                    cout << "Optiune invalida. Va rugam selectati o optiune valida.\n";

                    cin.ignore();
                    cin.get();
            }
        }
        else if(mod == 3) {
            contSelectat = emailSelectat + " (" + adminConturi.CautaContDupaEmail(emailSelectat).getTipCont() + ") ";
            cout << " CONTURI\n";
            cout << "1. Creare cont\n";
            cout << "2. Afisare conturi\n";
            cout << "3. Cauta/Selecteaza cont\n";
            cout << "4. Modifica date cont\n";
            cout << "5. Sterge cont\n";
            cout << '\n';
            cout << "Cont selectat: " << (emailSelectat.empty() ? "N/A (poti selecta un cont accesand optiunea \"3. Cauta/Selecteaza cont\")" : contSelectat) << endl;
            cout << '\n';
            cout << "6. Meniu clienti\n";
            cout << "7. Meniu admin\n";
            cout << "0. Inchidere program\n";
            cout << "\nIntroduceti o optiune... ";
            cin >> optiune;
            cout << endl;
            switch (toupper(optiune)) {
                case 1: {
                    cin >> cont;
                    cout << endl << endl;
                    cont.setTipCont(cont.selecteazaTipCont());
                    cont_verificare_exista = adminConturi.CautaContDupaEmail(cont.getEmail());
                    if(cont_verificare_exista.getEmail() == cont.getEmail()) {
                        cout << endl << "Eroare! Contul deja exista!";
                    }
                    else {
                        adminConturi.AdaugaCont(cont);
                        cout << endl << "Cont salvat";
                        cont = Cont();
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 2: {
                    conturi = adminConturi.GetConturi(nrConturi);
                    afisareTabelConturi(conturi, nrConturi);

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 3: {
                    emailSelectat = meniuCautareCont(conturi);
                    break;
                }

                case 4: {
                    string raspuns;

                    if (emailSelectat.empty()) {
                        cout << "Nu ati selectat niciun cont. Va rugam selectati un cont valid accesand optiunea \"3. Cauta/Selecteaza cont\"...";
                    } else {
                        bool confirmare = false;
                        while (!confirmare) {
                            cout << "Cont selectat: " << contSelectat << endl;
                            cout << "Doriti sa modificati acest cont? (Da/Nu): ";
                            cin >> raspuns;
                            cout << "\n";

                            if (raspuns == "Da" || raspuns == "da" || raspuns == "DA" || raspuns == "dA" || raspuns == "d" || raspuns == "D") {
                                Cont contModificat = Cont(adminConturi.CautaContDupaEmail(emailSelectat));
                                contModificat.citireContExistent();

                                bool rezultat = adminConturi.ModificaContDinFisier(emailSelectat, contModificat);
                                if (rezultat) {
                                    cout << endl << "Contul a fost modificat cu succes.";
                                } else {
                                    cout << endl << "Nu s-a putut gasi contul pentru modificare.";
                                }
                                confirmare = true;
                            } else if (raspuns == "Nu" || raspuns == "nu" || raspuns == "NU" || raspuns == "nU" || raspuns == "n" || raspuns == "N") {
                                cout << endl << "Modificarea contului a fost anulata.";
                                confirmare = true;
                            } else {
                                cout << endl << "Raspuns invalid. Va rugam introduceti 'Da' sau 'Nu'.";
                                cin.ignore();
                                cin.get();
                                for(int i = 1; i <= 5; i++)
                                    cout << "\33[2K\r\033[A\r";
                            }
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 5: {
                    string raspuns;

                    if (emailSelectat.empty()) {
                        cout << "Nu ati selectat niciun cont. Va rugam selectati un cont valid accesand optiunea \"3. Cauta/Selecteaza cont\"...";
                    } else {
                        bool confirmare = false;
                        while (!confirmare) {
                            cout << "Cont selectat: " << componentalSelectat << "\n";
                            cout << "Doriti sa stergeti aceast cont? (Da/Nu): ";
                            cin >> raspuns;
                            cout << "\n";

                            if (raspuns == "Da" || raspuns == "da" || raspuns == "DA" || raspuns == "dA" || raspuns == "d" || raspuns == "D") {
                                bool rezultat = adminConturi.StergeContDupaEmail(emailSelectat);
                                if (rezultat) {
                                    emailSelectat = "";
                                    cout << endl << "Contul a fost sters cu succes.";
                                } else {
                                    cout << endl << "Nu s-a putut gasi contul pentru stergere.";
                                }
                                confirmare = true;
                            } else if (raspuns == "Nu" || raspuns == "nu" || raspuns == "NU" || raspuns == "nU" || raspuns == "n" || raspuns == "N") {
                                cout << endl << "Stergerea contului a fost anulata.";
                                confirmare = true;
                            } else {
                                cout << endl << "Raspuns invalid. Va rugam introduceti 'Da' sau 'Nu'.";
                                cin.ignore();
                                cin.get();
                                for(int i = 1; i <= 5; i++)
                                    cout << "\33[2K\r\033[A\r";
                            }
                        }
                    }

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 6: {
                    mod = 1;

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 7: {
                    mod = 2;

                    cin.ignore();
                    cin.get();
                    break;
                }

                case 0:
                    exit(0);

                default:
                    cout << "Optiune invalida. Va rugam selectati o optiune valida.\n";

                    cin.ignore();
                    cin.get();
            }
        }
    }while(true);

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

void afisareTabelComenzi (const vector<CumparaComponenta>& comenzi, int nrComenzi)
{
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

void afisareTabelConturi( const vector<Cont> conturi, int nrConturi)
{
    if (conturi.empty()) {
        cout << "Nu exista conturi de afisat." << endl;
        return;
    }

    Table tConturi;
    AdministrareConturi adminConturi = AdministrareConturi();

    tConturi.add_row({"Index", "Email", "Parola", "Tip Cont"});
    for (int i = 0; i < nrConturi; i++) {
        tConturi.add_row({to_string(i + 1),
                          conturi[i].getEmail(),
                          conturi[i].getParola(),
                          conturi[i].getTipCont()});
    }

    tConturi[0].format()
            .font_style({FontStyle::bold})
            .padding(1)
            .font_align(FontAlign::center);

    cout << tConturi << endl;

}

int meniuCautareComponenta(vector<Componenta> componente) {

    string tip, brand, model;
    float costMin = 0, costMax = 0;
    int optiune, idSelectat = -1, idComponenta = -1;

    AdministrareComponenta adminComponenta = AdministrareComponenta();

    Componenta componenta;

    bool exitMenu = false;

    while(!exitMenu) {
        bool exitMenuSelectare = false;
        system("clear");

        cout << "Filtreza componente: \n";
        cout << "1. Filtreaza dupa tip" << (tip.empty() ? "" : " (Filtru: " + tip + ")") << '\n';
        cout << "2. Filtreaza dupa brand" << (brand.empty() ? "" : " (Filtru: " + brand+ ")") << '\n';
        cout << "3. Filtreaza dupa model" << (model.empty() ? "" : " (Filtru: " + model + ")") << '\n';
        cout << "4. Filtru dupa pret minim" << (costMin > 0 ? " (Filtru: " + to_string(costMin) + ")" : "") << '\n';
        cout << "5. Filtru dupa pret maxim pe zi" << (costMax > 0 ? " (Filtru: " + to_string(costMax) + ")" : "") << '\n';
        cout << "6. Filtru dupa ID" << (idComponenta != -1 ? " (Filtru: " + to_string(idComponenta) + ")" : "") << '\n';
        cout << "7. Reseteaza filtre\n";
        cout << '\n';
        cout << "9. Afiseaza rezultate\n";
        cout << "0. Inapoi la meniul principal\n";

        string componentaSelectata = adminComponenta.CautaComponentaDupaID(idSelectat).getBrand() + ' ' + adminComponenta.CautaComponentaDupaID(idSelectat).getModel() +  "(#" + to_string(idSelectat) + ") ";
        cout << "\nComponenta selectata: " + (idSelectat == -1 ? "N/A" : componentaSelectata) + "\n";

        cout << "\nIntrodu o optiune... ";
        cin >> optiune;
        cout << endl;

        switch (optiune) {

            case 1:
                tip = componenta.selecteazaTipComponenta();
            break;
            case 2:
                cout << "Introdu brand-ul: ";
            cin.ignore();
            getline(cin, brand);
            break;
            case 3:
                cout << "Introdu modelul: ";
            cin.ignore();
            getline(cin, model);
            break;
            case 4:
                cout << "Introdu pretul minim: ";
            cin >> costMin;
            break;
            case 5:
                cout << "Introdu pretul maxim: ";
            cin >> costMax;
            break;
            case 6:
                cout << "Introdu ID-ul componentei: ";
            cin >> idComponenta;
            break;
            case 7:
                model = "";
                brand = "";
                tip = "";
                costMin = 0;
                costMax = 0;
                idComponenta = -1;
                cout << "Filtre resetate." << endl;

                cin.ignore();
                cin.get();
                break;
            case 8: {
                vector<Componenta> searchResults = adminComponenta.CautaComponenta(tip, brand, model, costMin, costMax,idComponenta, true);
                if(searchResults.empty()) {
                    cout << "Nicio componenta gasita conform filtrelor specificate." << endl;
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Componente gasite conform filtrelor specificate:" << endl;
                    afisareTabelComponente(searchResults, searchResults.size());

                    while (!exitMenuSelectare) {
                        cout << "1. Selecteaza componenta\n";
                        cout << "0. Inapoi la cautare\n";
                        cout << "\nIntroduceti o optiune... ";
                        cin >> optiune;
                        cout << endl;

                        switch (optiune) {
                            case 1:
                                cout << "Introduceti ID-ul componentei: ";
                            cin >> idSelectat;
                            if (adminComponenta.CautaComponentaDupaID(idSelectat).getID() == -1) {
                                idSelectat = -1;
                                cout << "Componenta cu ID-ul specificat nu a fost gasit." << endl;
                                cin.ignore();
                                cin.get();
                                for (int i = 1; i <= 8; i++)
                                    cout << "\33[2K\r\033[A\r";
                            } else exitMenuSelectare = true;
                            break;
                            case 0:
                                exitMenuSelectare = true;
                            break;
                            default:
                                cout << "Optiune invalida. Selecteaza o optiune valida." << endl;

                            cin.ignore();
                            cin.get();
                            for (int i = 1; i <= 7; i++)
                                cout << "\33[2K\r\033[A\r";
                            break;
                        }
                    }
                }
                break;
            }
            case 0:
                exitMenu = true;
                break;
            default:
                cout << "Optiune invalida. Selecteaza o optiune valida." << endl;

            cin.ignore();
            cin.get();
            break;

        }
    }
    return idSelectat;
}


int meniuCautareComanda(vector<CumparaComponenta> comenzi) {
    string nume, prenume, email, nr_telefon;
    int idComanda = -1, idComponenta = -1, optiune, idSelectat = -1;
    AdministrareCumparare adminComanda = AdministrareCumparare();

    bool exitMenu = false;

    while (!exitMenu) {
        bool exitMenuSelectare = false;
        system("cls");
        cout << " FILTRE DISPONIBILE:\n";
        cout << "1. Filtru dupa nume" << (nume.empty() ? "" : " (Filtru: " + nume + ")") << '\n';
        cout << "2. Filtru dupa prenume" << (prenume.empty() ? "" : " (Filtru: " + prenume + ")") << '\n';
        cout << "3. Filtru dupa email" << (email.empty() ? "" : " (Filtru: " + email + ")") << '\n';
        cout << "4. Filtru dupa numar telefon" << (nr_telefon.empty() ? "" : " (Filtru: " + nr_telefon + ")") << '\n';
        cout << "5. Filtru dupa ID comanda" << (idComanda != -1 ? " (Filtru: " + to_string(idComanda) + ")" : "")
             << '\n';
        cout << "6. Filtru dupa ID componenta"
             << (idComponenta != -1 ? " (Filtru: " + to_string(idComponenta) + ")" : "") << '\n';
        cout << "7. Reseteaza filtre\n";
        cout << '\n';
        cout << "8. Afiseaza rezultate\n";
        cout << "0. Inapoi la meniul principal\n";

        string comandaSelectata = adminComanda.CautaCommandaDupaID(idSelectat).getNume() + ' '
                                  + adminComanda.CautaCommandaDupaID(idSelectat).getPrenume()
                                  + " (#" + to_string(idSelectat) + ") ";
        cout << "\nComanda selectata: " + (idSelectat == -1 ? "N/A" : comandaSelectata) + "\n";
        cout << "\nIntrodu o optiune... ";
        cin >> optiune;
        cout << endl;

        switch (optiune) {
            case 1:
                cout << "Introdu numele: ";
                cin.ignore();
                getline(cin, nume);
                break;
            case 2:
                cout << "Introdu prenumele: ";
                cin.ignore();
                getline(cin, prenume);
                break;
            case 3:
                cout << "Introdu email-ul: ";
                cin.ignore();
                getline(cin, email);
                break;
            case 4:
                cout << "Introduceti numar telefon: ";
                cin.ignore();
                getline(cin, nr_telefon);
                break;
            case 5:
                cout << "IntroduID-ul comenzii: ";
                cin >> idComanda;
                break;
            case 6:
                cout << "Introdu ID-ul componentei: ";
                cin >> idComponenta;
                break;
            case 7:
                nume = "";
                prenume = "";
                email = "";
                nr_telefon = "";
                idComanda = -1;
                idComponenta = -1;
                cout << "Filtre resetate." << endl;
                cin.ignore();
                cin.get();
                break;
            case 8: {
                vector<CumparaComponenta> searchResults = adminComanda.CautaComanda(nume, prenume, email, nr_telefon,
                                                                                    idComanda, idComponenta);

                if (searchResults.empty()) {
                    cout << "Nicio comanda gasita conform filtrelor specificate." << endl;
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Comenzile gasite conform filtrelor specificate:" << endl;
                    afisareTabelComenzi(searchResults, searchResults.size());

                    while (!exitMenuSelectare) {
                        cout << "1. Selecteaza comanda\n";
                        cout << "0. Inapoi la cautare\n";
                        cout << "\nIntroduceti o optiune... ";
                        cin >> optiune;
                        cout << endl;

                        switch (optiune) {
                            case 1:
                                cout << "Introduceti ID-ul comenzii: ";
                                cin >> idSelectat;
                                if (adminComanda.CautaCommandaDupaID(idSelectat).getIdCumparare() == -1) {
                                    idSelectat = -1;
                                    cout << "Comanda cu ID-ul specificat nu a fost gasita." << endl;
                                    cin.ignore();
                                    cin.get();
                                    for (int i = 1; i <= 8; i++)
                                        cout << "\33[2K\r\033[A\r";
                                } else exitMenuSelectare = true;
                                break;
                            case 0:
                                exitMenuSelectare = true;
                                break;
                            default:
                                cout << "Optiune invalida. Selecteaza o optiune valida." << endl;

                                cin.ignore();
                                cin.get();
                                for (int i = 1; i <= 7; i++)
                                    cout << "\33[2K\r\033[A\r";
                                break;
                        }
                    }
                }

                break;
            }
            case 0:
                exitMenu = true;
                break;
            default:
                cout << "Optiune invalida. Va rugam sa selectati o optiune valida." << endl;

                cin.ignore();
                cin.get();
                break;
        }
    }
    return idSelectat;
}

string meniuCautareCont(vector<Cont> conturi)
{
    string email, tip, emailSelectat;
    int optiune, indexSelectat = -1;
    AdministrareConturi adminConturi = AdministrareConturi();
    Cont cont;

    bool exitMenu = false;

    while (!exitMenu) {
        bool exitMenuSelectare = false;
        system("cls");
        cout << " FILTRE DISPONIBILE:\n";
        cout << "1. Filtru dupa email" << (email.empty() ? "" : " (Filtru: " + email + ")") << '\n';
        cout << "2. Filtru dupa tip cont" << (tip.empty() ? "" : " (Filtru: " + tip + ")") << '\n';
        cout << "3. Reseteaza filtre\n";
        cout << '\n';
        cout << "9. Afiseaza rezultate\n";
        cout << "0. Inapoi la meniul principal\n";

        string contSelectat = emailSelectat + " (" + adminConturi.CautaContDupaEmail(emailSelectat).getTipCont() + ") ";
        cout << "\nCont selectat: " + (emailSelectat == "" ? "N/A" : contSelectat) + "\n";

        cout << "\nIntroduceti o optiune... ";
        cin >> optiune;
        cout << endl;

        switch (optiune) {
            case 1:
                cout << "Introduceti email-ul: ";
                cin.ignore();
                getline(cin, email);
                break;
            case 2:
                tip = cont.selecteazaTipCont();
                break;
            case 3:
                email = "";
                tip = "";
                cout << "Filtre resetate." << endl;
                cin.ignore();
                cin.get();
                break;
            case 9:
            {
                vector<Cont> searchResults = adminConturi.CautaCont(email, tip);

                if (searchResults.empty()) {
                    cout << "Niciun cont gasit conform filtrelor specificate." << endl;
                    cin.ignore();
                    cin.get();
                } else {
                    cout << "Conturile gasite conform filtrelor specificate:" << endl;
                    afisareTabelConturi(searchResults, searchResults.size());

                    while (!exitMenuSelectare) {
                        cout << "1. Selecteaza cont\n";
                        cout << "0. Inapoi la cautare\n";
                        cout << "\nIntroduceti o optiune... ";
                        cin >> optiune;
                        cout << endl;

                        switch (optiune) {
                            case 1:
                                cout << "Introduceti index-ul contului: ";
                                cin >> indexSelectat;
                                if(searchResults[indexSelectat-1].getEmail() == "")
                                {
                                    indexSelectat = -1;
                                    cout << "Contul specificat nu a fost gasit." << endl;
                                    cin.ignore();
                                    cin.get();
                                    for(int i = 1; i <= 8; i++)
                                        cout << "\33[2K\r\033[A\r";
                                }
                                else {
                                    emailSelectat = searchResults[indexSelectat-1].getEmail();
                                    exitMenuSelectare = true;
                                }
                                break;
                            case 0:
                                exitMenuSelectare = true;
                                break;
                            default:
                                cout << "Optiune invalida. Va rugam sa selectati o optiune valida." << endl;

                                cin.ignore();
                                cin.get();
                                for(int i = 1; i <= 7; i++)
                                    cout << "\33[2K\r\033[A\r";
                                break;
                        }
                    }
                }

                break;
            }
            case 0:
                exitMenu = true;
                break;
            default:
                cout << "Optiune invalida. Va rugam sa selectati o optiune valida." << endl;

                cin.ignore();
                cin.get();
                break;
        }
    }
    return emailSelectat;
}





