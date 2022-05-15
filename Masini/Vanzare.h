#ifndef PROIECTFINALPOO_VANZARE_H
#define PROIECTFINALPOO_VANZARE_H

#include <iostream>
#include <set>
#include <utility>
#include "Masini.h"

using namespace std;

template <typename T> class Vanzare{
    int nrTotalMasini;
    static int nrTotalMasiniVandute;
    set<pair<T,bool>> *automobileStoc;
    set<pair<T,bool>> *automobileVandute;

public:
    // Constuctors & destructors
    Vanzare();
    Vanzare(int, set<pair<T,bool>>*);
    Vanzare(const Vanzare &);

    // Setters & getters
    int getNrTotalMasini() const{ return nrTotalMasini;}
    int getNrTotalMasiniVandute() const{ return nrTotalMasiniVandute;}
    set<pair<T,bool>> *getAutomobileStoc() const { return automobileStoc;}
    set<pair<T,bool>> *getAutomobileVandute() const { return automobileVandute;}

    // Functii
    template <typename U>
    friend ostream& operator<<(ostream &, const Vanzare<U>&);

    template <typename U>
    friend istream& operator>>(istream &, Vanzare<U>&);

    template <typename U>
    Vanzare<T>&operator=(const Vanzare<U>&);

    Vanzare<T>&operator-=(T &masina);

    // Functii care calculeaza pretul masinilor din stoc / vandute
    static double valoareMasini(int,set<pair<T,bool>>*);
    double valoareMasiniStoc() { return valoareMasini(nrTotalMasini,automobileStoc); };
    double valoareMasiniVandute() { return valoareMasini(nrTotalMasiniVandute, automobileVandute); };
};

template <typename T>
int Vanzare<T> :: nrTotalMasiniVandute = 0;

///////////////////////////////////////////////
/////// Constructors & Destructors ////////////
//////////////////////////////////////////////

template <typename T>
Vanzare<T>::Vanzare(){
    nrTotalMasini = 0;
    automobileStoc = new set<pair<T,bool>> [0];
    automobileVandute = new set<pair<T,bool>> [0];
}

template <typename T>
Vanzare<T>::Vanzare(int lungime, set<pair<T,bool>> *masini){
    nrTotalMasini = lungime;
    automobileStoc = new set<pair<T,bool>> [nrTotalMasini];
    automobileVandute = new set<pair<T,bool>> [0];

    // Pentru fiecare element al vectorului
    for(int i = 0; i < nrTotalMasini; i++){
        // Copiem fiecare set din masini -> this
        for( auto itr = masini[i].begin(); itr != masini[i].end(); itr++) {
            pair <T,bool> pereche(itr->first, itr->second);
            automobileStoc[i].insert(pereche);
        }
    }

}

template<typename T>
Vanzare<T>::Vanzare(const Vanzare <T> &automobile){
    nrTotalMasini = automobile.nrTotalMasini;
    automobileStoc = new set<pair<T,bool>> [nrTotalMasini];
    automobileVandute = new set<pair<T,bool>> [0];

    // Pentru fiecare element al vectorului
    for(int i = 0; i < nrTotalMasini; i++){
        // Copiem fiecare set din masini -> this
        for( auto itr = automobile.automobileStoc[i].begin(); itr != automobile.automobileStoc[i].end(); itr++) {
            pair <T,bool> pereche(itr->first, itr->second);
            automobileStoc[i].insert(pereche);
        }
    }
}

///////////////////////////////////////////////
//////////////// Functii /////////////////////
//////////////////////////////////////////////

template <typename T>
istream &operator>>(istream &in, Vanzare <T> &masini){
    cout << "Numarul de masini din stoc: ";
    in >> masini.nrTotalMasini;

    // Stergem datele initiale din variabila masini,
    // urmand ca utilizatorul sa reintroduca altele noi

    delete [] masini.automobileStoc;
    masini.automobileStoc = new set<pair<T,bool>> [masini.nrTotalMasini];
    for( int i = 0 ; i < masini.nrTotalMasini; i++){
        cout << "Masina " << i+1 << ":" << endl;
        T masina;
        cin >> masina;
        masini.automobileStoc[i].insert(pair <T,bool> (masina,true) );
    }
    return in;
}

template <typename T>
ostream &operator<<(ostream &out, const Vanzare <T> &masini) {
    out << "Numarul de masini din stoc: " << masini.nrTotalMasini << endl;
    out << endl;
    for(int i = 0; i < masini.nrTotalMasini; i++){
        out << "Masina " << i+1 << ":" << endl;
        for( auto itr = masini.automobileStoc[i].begin(); itr != masini.automobileStoc[i].end(); itr++){
            // Itr->first va fi un tip de masina
            T masina(itr->first);
            // Afisam fiecare masina valida din stoc
            out << masina << endl;
        }
    }

    out << "Numarul de masini vandute: " << masini.nrTotalMasiniVandute << endl;
    out << endl;
    for(int i = 0; i < masini.nrTotalMasiniVandute; i++) {
        cout << "Masina " << i+1 << ":" << endl;
        for( auto itr = masini.automobileVandute[i].begin(); itr != masini.automobileVandute[i].end(); itr++){
            T masina(itr->first);
            // Afisam fiecare masina vanduta
            out << masina << endl;
        }
    }
    return out;
}

template<typename T>
template<typename U>
Vanzare<T> &Vanzare<T>::operator=(const Vanzare<U> &masina) {
    nrTotalMasini = masina.nrTotalMasini;
    delete[] automobileStoc;
    automobileStoc = new set<pair<T, bool>>[nrTotalMasini];

    // Pentru fiecare element al vectorului
    for (int i = 0; i < nrTotalMasini; i++) {
        // Copiem fiecare set din masini -> this
        for (auto itr = masina[i].begin(); itr != masina[i].end(); itr++) {
            pair<T, bool> pereche(itr->first, itr->second);
            automobileStoc[i].insert(pereche);
        }
    }
    return *this;
}

template<typename T>
Vanzare<T> &Vanzare<T>::operator-=(T &masina) {
    // Acest operator merge doar daca introducem clasa Masini / clasa derivata din Masini
    try{
        Masini *este_masina = &dynamic_cast<Masini&>(masina);
        // is_same verifica daca sunt de acelasi data type
        if( este_masina == nullptr){
            // in cazul in care nu este de tip Masini, aruncam in exceptie variabila masina
            throw masina;
        } else{
            bool exista_masina = false;
            for(int i = 0; i < nrTotalMasini; i++){
                for( auto itr = automobileStoc[i].begin(); itr != automobileStoc[i].end(); itr++){
                    if(itr->first == masina) {
                        exista_masina = true;
                        // Vom crea 2 copii pentru set-ul de pointeri pentru masini din stoc & vandute
                        auto *copie_stoc = new set<pair<T,bool>> [nrTotalMasini-1];
                        auto *copie_vandute = new set<pair<T,bool>> [nrTotalMasiniVandute+1];
                        int cnt_s = 0;

                        // in copia pentru masinile vandute copiem datele deja existente
                        // ( avand un spatiu in plus, pentru masina care urmeaza sa fie stearsa)
                        for(int j = 0; j < nrTotalMasiniVandute; j++){
                            auto itr2 = automobileVandute[j].begin();
                            copie_vandute[j].insert(pair<T,bool>(itr2->first, itr2->second));
                        }

                        // stergem set-ul de pointeri si cream unul nou, cu un spatiu in plus
                        delete [] automobileVandute;
                        automobileVandute = new set<pair<T,bool>> [nrTotalMasiniVandute+1];

                        // copiem inapoi datele ce existau inainte stergerii in set-ul de pointeri
                        for(int j = 0; j < nrTotalMasiniVandute; j++){
                            auto itr2 = copie_vandute[j].begin();
                            automobileVandute[j].insert(pair<T,bool>(itr2->first, itr2->second));
                        }

                        nrTotalMasiniVandute += 1;

                        for(int j = 0; j < nrTotalMasini; j++){
                            auto itr2 = automobileStoc[j].begin();
                            if(j!=i)
                                // in copia de masini din stoc vor fi toate masinile in afara de cea
                                // care urmeaza sa fie vanduta
                                copie_stoc[cnt_s++].insert(pair<T,bool>(itr2->first,itr2->second));
                            else
                                // masina vanduta intra pe ultima pozitie din set-ul pentru masini vandute
                                automobileVandute[nrTotalMasiniVandute-1].insert(pair<T,bool>(itr2->first,itr2->second));
                        }

                        // scadem din numarul de masini din stoc o masina, si pe urma
                        // copiem datele reinnoite
                        nrTotalMasini--;
                        delete [] automobileStoc;
                        automobileStoc = new set<pair<T, bool>> [nrTotalMasini];
                        for( int j = 0; j < nrTotalMasini; j++) {
                            auto itr3 = copie_stoc[j].begin();
                            automobileStoc[j].insert(pair<T, bool>(itr3->first, itr3->second));
                        }

                        delete [] copie_vandute;
                        delete [] copie_stoc;
                        return *this;
                    }
                }
            }
            if(!exista_masina) cout << "Masina introdusa nu exista, va rugam sa reincercati!" << endl;
        }
    } catch(T mmasina){
        // exceptia este prinsa si este afisat un mesaj corespunzator
        cout << typeid(mmasina).name() << " nu este o variabila de tip Masini!" << endl;
    }
    return *this;
}

// Functii pentru calcularea valorii masinilor din stoc/vandute;
template <typename T>
double Vanzare<T>::valoareMasini(int lungime, set<pair<T,bool>> *masini){
    double pret_masini = 0;
    try{
        T masina;
        Masini *este_masina = &dynamic_cast<Masini&>(masina);
        if( este_masina == nullptr){
            string exceptie = "Nu se poate calcula pretul decat pentru variabile de tip Masini!";
            throw exceptie;
        } else {
            for(int i = 0; i < lungime; i++){
                for(auto itr = masini[i].begin(); itr != masini[i].end(); itr++){
                    T ceva(itr->first);
                    pret_masini += ceva.calculeazaPret();
                }
            }
        }
    } catch(string exceptie){
        cout << exceptie << endl;
    }
    return pret_masini;
}

///////////////////////////////////////////////
/////// Specializare Monovolum ////////////////
//////////////////////////////////////////////

template <>
istream &operator>>(istream &in, Vanzare <Monovolum> &masini){
    // specializare pentru masinile monovolum, in bool se va
    // introduce true daca masina e noua, daca nu se introduce false
    cout << "Numarul de masini din stoc: ";
    in >> masini.nrTotalMasini;

    delete [] masini.automobileStoc;
    masini.automobileStoc = new set<pair<Monovolum,bool>> [masini.nrTotalMasini];
    for( int i = 0 ; i < masini.nrTotalMasini; i++){
        cout << "Masina " << i+1 << ":" << endl;
        bool vechime = true;
        Monovolum masina;
        cin >> masina;
        if(masina.getVechime() == "SH") vechime = false;
        masini.automobileStoc[i].insert(pair <Monovolum,bool> (masina,vechime) );
    }
    return in;
}

#endif //PROIECTFINALPOO_VANZARE_H
