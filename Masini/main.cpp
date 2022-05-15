#include <iostream>
#include <iterator>
#include <fstream>

#include "MicaMini.h"
#include "Compacta.h"
#include "Monovolum.h"
#include "Vanzare.h"
using namespace std;

Vanzare <Mini> utilizator1; Vanzare <Mica> utilizator2; Vanzare <Compacta> utilizator3; Vanzare <Monovolum> utilizator4;
int nr_obiecte = 0;

void scrieInFisier(string numeFisier, int &tipMasina){
    ofstream output(numeFisier.c_str());
    switch(tipMasina){
        case 1:{
            tipMasina = -1;
            output << utilizator1;
            break;
        } case 2:{
            tipMasina = -1;
            output << utilizator2;
            break;
        } case 3:{
            tipMasina = -1;
            output << utilizator3;
            break;
        } case 4:{
            tipMasina = -1;
            output << utilizator4;
            break;
        } default:{
            cout << "Nu exista niciun obiect. Inainte de a afisa un obiect, trebuie sa creati unul." << endl;
            break;
        }
    }
}

void Testare(){
    Vanzare <Mica> mica1;
    cin >> mica1;
    Vanzare <Mica> mica2(mica1);
    cout << mica2 << endl;

    Compacta compacta1;
    compacta1.Citire(cin);
    cout << compacta1 << endl;

    Monovolum mono1;
    mono1.Afisare(cout);
}

int main(){
    int comanda;
    cout << "Aveti o afecere cu masini si doriti sa va gestionati informatiile mai usor?" << endl;
    cout << "Platformat aceasta face exact acest lucru pentru dumneavoastr." << endl;
    cout << " Comenzile pe care le aveti la dispozitie: " << endl;
    cout << " 0 - parasiti si salvati datele introduse intr-un fisier extern;" << endl;
    cout << " 1 - creati un obiect de gestionare a mai multor masini;" << endl;
    cout << " 2 - vindeti una dintre masinile gestionate;" << endl;
    cout << " 3 - se va afisa pretul total al masinilor din stoc" << endl;
    cout << " 4 - se va afisa pretul total al masinilor vandute" << endl;
    cout << " 5 - salvati datele introduse si creati un nou obiect" << endl;

    int ok = -1; // folosim ok pentru a verifica ce tip de masina a ales utilizatorul si daca exista unul deja
    cout << "Comanda: ";
    cin >> comanda;
    while( comanda != 0){
        switch(comanda){
            case 1: {
                if( ok == -1) {
                    string tipMasina;
                    cout << "Ce fel de masini doriti sa gestionati?" << endl;
                    cout << "/// Mini, Mica, Compacta, Monovolum ///" << endl;
                    cout << "Tip masina: ";
                    cin >> tipMasina;

                    while (tipMasina != "Mini" && tipMasina != "Mica" && tipMasina != "Compacta" &&
                           tipMasina != "Monovolum") {
                        cout << "Masina trebuie sa fie una din tipurile mentionate precedent." << endl;
                        cout << "Tip masina: ";
                        cin >> tipMasina;
                    }

                    if (tipMasina == "Mica") {
                        ok = 1;
                        cin >> utilizator1;
                    } else if (tipMasina == "Mini") {
                        ok = 2;
                        cin >> utilizator2;
                    } else if (tipMasina == "Compacta") {
                        ok = 3;
                        cin >> utilizator3;
                    } else {
                        ok = 4;
                        cin >> utilizator4;
                    }

                } else {
                    cout << "Deja exista un obiect, pentru a il salva pe cel actual si a crea unul nou, apelati comanda 5." << endl;
                }

                cout << "Comanda: ";
                cin >> comanda;

                break;
            } case 2: {
                switch(ok){
                    case 1: {
                        Mini masina_sters;
                        cout << "Ati ales sa stergeti o masina!" << endl;
                        cin >> masina_sters;
                        utilizator1 -= masina_sters;
                        break;
                    } case 2: {
                        Mica masina_sters;
                        cout << "Ati ales sa stergeti o masina!" << endl;
                        cin >> masina_sters;
                        utilizator2 -= masina_sters;

                        break;
                    } case 3: {
                        Compacta masina_sters;
                        cout << "Ati ales sa stergeti o masina!" << endl;
                        cin >> masina_sters;
                        utilizator3 -= masina_sters;

                        break;
                    } case 4: {
                        Monovolum masina_sters;
                        cout << "Ati ales sa stergeti o masina!" << endl;
                        cin >> masina_sters;
                        utilizator4 -= masina_sters;
                        break;
                    } default: {
                        cout << "Nu exista niciun obiect, inainte de a sterge o masina trebuie sa introduceti un obiect." << endl;
                        break;
                    }
                }
                cout << "Comanda: ";
                cin >> comanda;
                break;
            } case 3:{
                switch(ok){
                    case 1:{
                        cout << "Pretul total al masinilor din stoc este: " << utilizator1.valoareMasiniStoc() << endl;
                        break;
                    } case 2:{
                        cout << "Pretul total al masinilor din stoc este: " << utilizator2.valoareMasiniStoc() << endl;
                        break;
                    } case 3:{
                        cout << "Pretul total al masinilor din stoc este: " << utilizator3.valoareMasiniStoc() << endl;
                        break;
                    } case 4:{
                        cout << "Pretul total al masinilor din stoc este: " << utilizator4.valoareMasiniStoc() << endl;
                        break;
                    } default:{
                        cout << "Nu exista niciun obiect. Inainte de a afisa pretul total, trebuie sa creati un obiect." << endl;
                        break;
                    }
                }
                cout << "Comanda: ";
                cin >> comanda;
                break;
            } case 4:{
                switch(ok){
                    case 1:{
                        cout << "Pretul total al masinilor vandute este: " << utilizator1.valoareMasiniVandute() << endl;
                        break;
                    } case 2:{
                        cout << "Pretul total al masinilor vandute este: " << utilizator2.valoareMasiniVandute() << endl;
                        break;
                    } case 3:{
                        cout << "Pretul total al masinilor vandute este: " << utilizator3.valoareMasiniVandute() << endl;
                        break;
                    } case 4:{
                        cout << "Pretul total al masinilor vandute este: " << utilizator4.valoareMasiniVandute() << endl;
                        break;
                    } default:{
                        cout << "Nu exista niciun obiect. Inainte de a afisa pretul total, trebuie sa creati un obiect." << endl;
                        break;
                    }
                }
                cout << "Comanda: ";
                cin >> comanda;
                break;
            } case 5:{
                if(ok!=-1){
                    nr_obiecte ++;
                    scrieInFisier("Garaj"+to_string(nr_obiecte),ok);
                }
                comanda = 1;
                break;
            } case 0:{
                break;
            } default:{
                cout << "Nu ati introdus o valoare valida, va rugam sa reincercati." << endl;
                cout << "Comanda: ";
                cin >> comanda;
                break;
            }
        }
    }
    nr_obiecte ++;
    scrieInFisier("Garaj"+to_string(nr_obiecte),ok);
//    Testare();
    return 0;
}