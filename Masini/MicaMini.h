#ifndef PROIECTFINALPOO_MICAMINI_H
#define PROIECTFINALPOO_MICAMINI_H

#include "Masini.h"

// MICA
class Mica : public Masini{

public:
    // Constructors & destructors
    Mica();
    Mica(int lungime, int anFabricatie, int valoare);
    Mica(const Mica &masina_mica);

    // Functii
    Mica &operator=(Mica masina_mica);
    friend istream &operator>>(istream &in, Mica &masina_mica);
    friend ostream &operator<<(ostream &out, Mica &masina_mica);
    double calculeazaPret();
};

// Constructors & destructors
Mica:: Mica():Masini(){}
Mica:: Mica(int lungime, int anFabricatie, int valoare):Masini(lungime,anFabricatie,valoare){}
Mica:: Mica(const Mica &masina_mica) : Masini(masina_mica.getLungime(),masina_mica.getAnFabricatie(),masina_mica.getValoare()){ }

// Functii
// - sunt identice cu cele de la clasa Masini
Mica &Mica::operator=(Mica masina_mica){
    dynamic_cast<Masini&>(*this) = dynamic_cast<Masini&>(masina_mica);
    return *this;
}
istream &operator>>(istream &in, Mica &masina_mica){
    in >> dynamic_cast<Masini&>(masina_mica);
    return in;
}
ostream &operator<<(ostream &out, Mica &masina_mica){
    out << dynamic_cast<Masini&>(masina_mica);
    return out;
}

double Mica ::calculeazaPret() {
    // valoarea masinii scade cu 8% pentru cele mici
    int aniExistenta = 2022 - this->getAnFabricatie();
    double pret = this->getValoare();
    for( int i = 1; i <= aniExistenta; i++)
        pret = pret - pret * 0.08;
    return pret;
}

// MINI
class Mini : public Masini{

public:
    // Constructors & destructors
    Mini();
    Mini(int lungime, int anFabricatie, int valoare);
    Mini(const Mini &masina_mica);
    // Setters & getters
    // Functii
    Mini &operator=(Mini masina_mini);
    friend istream &operator>>(istream &in, Mini &masina_mini);
    friend ostream &operator<<(ostream &out, Mini &masina_mini);
    double calculeazaPret();
};

// Constructors & destructors
Mini::Mini():Masini(){}
Mini:: Mini(int lungime, int anFabricatie, int valoare) : Masini(lungime, anFabricatie, valoare){}
Mini:: Mini(const Mini &masina_mica) : Masini(masina_mica.getLungime(), masina_mica.getAnFabricatie(), masina_mica.getValoare()){}

// Functii
// - sunt identice cu cele de la clasa Masini
Mini &Mini::operator=(Mini masina_mini){
    dynamic_cast <Masini&>(*this) = dynamic_cast <Masini&>(masina_mini);
    return *this;
}

istream &operator>>(istream &in, Mini &masina_mini){
    in >> dynamic_cast<Masini&>(masina_mini);
    return in;
}
ostream &operator<<(ostream &out, Mini &masina_mini){
    out << dynamic_cast<Masini&>(masina_mini);
    return out;
}


double Mini ::calculeazaPret() {
    // in primii doi ani masinile mini se deterioreaza mai rapid ( 15% )
    int aniExistenta = 2022 - this->getAnFabricatie();
    double pret = this->getValoare();
    if ( aniExistenta >= 2){
        pret = pret - pret * 0.15;
        pret = pret - pret * 0.15;
        aniExistenta -= 2;
        for( int i = 1; i <= aniExistenta; i++)
            pret = pret - pret * 0.10;
    } else {
        for(int i = 1; i < aniExistenta; i++)
            pret = pret - pret * 0.15;
    }
    return pret;
}

#endif //PROIECTFINALPOO_MICAMINI_H
