#ifndef PROIECTFINALPOO_COMPACTA_H
#define PROIECTFINALPOO_COMPACTA_H

#include "Masini.h"

class Compacta : public Masini{
    string model;
public:
    // Constructors & destructors
    Compacta();
    Compacta(int lungime, int anFabricatie, int valoare, string model);
    Compacta(const Compacta &masina_compacta);
    ~Compacta();

    // Setters & getters
    void setModel( string modelul) { model.assign(modelul); }
    string getModel() const{ return model; }

    // Functii
    Compacta &operator=(Compacta masina_compacta);
    friend bool operator==(const Compacta &masina1, const Compacta &masina2);
    friend istream &operator>>(istream &in, Compacta &masina_compacta);
    friend ostream &operator<<(ostream &out, Compacta &masina_compacta);
    istream &Citire(istream &in);
    ostream &Afisare(ostream &out);
    double calculeazaPret();
};

// Constructors & destructors
Compacta::Compacta():Masini(){
    this->model.assign("");
}
Compacta:: Compacta(int lungime, int anFabricatie, int valoare, string model):Masini(lungime,anFabricatie,valoare){
    this->model.assign(model);
}
Compacta:: Compacta(const Compacta &masina_compacta) : Masini(masina_compacta.getLungime(), masina_compacta.getAnFabricatie(), masina_compacta.getValoare()){
    this->model.assign(masina_compacta.model);
}
Compacta::~Compacta(){
    this->model.assign("");
}

// Functii
Compacta &Compacta::operator=(Compacta masina_compacta){
    dynamic_cast <Masini&>(*this) = dynamic_cast <Masini&>(masina_compacta);
    this->model = masina_compacta.model;
    return *this;
}
istream &operator>>(istream &in, Compacta &masina_compacta){
    in >> dynamic_cast <Masini&>(masina_compacta);
    cout << "Introduceti modelul masinii( Hatchback, Combi sau Sedan): ";
    in >> masina_compacta.model;

    // Daca string-ul introdus de utilizator nu este unul dintre cele 3 modele precedente
    // va fi nevoit sa reintroduca un alt string

    while(masina_compacta.model != "Hatchback" && masina_compacta.model  != "Combi" && masina_compacta.model != "Sedan"){
        cout << "Ati introdus un input invalid. Incercati din nou: ";
        in >> masina_compacta.model;
    }
    return in;
}
ostream &operator<<(ostream &out, Compacta &masina_compacta){
    out << dynamic_cast <Masini&>(masina_compacta);
    out << "Modelul masinii: " << masina_compacta.model << endl;
    return out;
}

// Functii de citire si afisare
istream &Compacta::Citire(istream &in){
    in >> *this;
    return in;
}

ostream &Compacta::Afisare(ostream &out) {
    out << *this;
    return out;
}

double Compacta ::calculeazaPret() {
    // vom presupune ca ordina calitatii este sedan > combi > hatchback
    // deci vom avea procente diferite de scadere in pret 9%, 10%, 11%
    double percent;
    if( this->getModel() == "Hatchback")
        percent = 0.11;
    else if ( this->getModel() == "Combi")
        percent = 0.10;
    else if ( this->getModel() == "Sedan")
        percent = 0.09;

    int aniExistenta = 2022 - this->getAnFabricatie();
    double pret = this->getValoare();
    for( int i = 1; i <= aniExistenta; i++)
        pret = pret - pret * percent;

    return pret;
}

bool operator==(const Compacta &masina1, const Compacta &masina2){
    return masina1.getLungime() == masina2.getLungime() && masina1.getAnFabricatie() == masina2.getAnFabricatie()
           &&  masina1.getValoare() == masina2.getValoare() && masina1.getModel() == masina2.getModel();
}

#endif //PROIECTFINALPOO_COMPACTA_H
