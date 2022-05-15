#ifndef PROIECTFINALPOO_MONOVOLUM_H
#define PROIECTFINALPOO_MONOVOLUM_H

#include "Masini.h"

// MONOVOLUM
class Monovolum : public Masini{
    string vechime;     // SH sau noua
public:
    // Constructors & destructors
    Monovolum();
    Monovolum(int lungime, int anFabricatie, int valoare, string vechime);
    Monovolum(const Monovolum &masina_monovolum);
    ~Monovolum();
    // Setters & getters
    void setVechime( string vechimea ) { vechime.assign(vechimea); }
    string getVechime() const{ return vechime; }
    // Functii
    Monovolum &operator=(Monovolum masina_monovolum);
    friend bool operator==(const Monovolum &masina1, const Monovolum &masina2);
    friend istream &operator>>(istream &in, Monovolum &masina_monovolum);
    friend ostream &operator<<(ostream &out, Monovolum &masina_monovolum);
    istream &Citire(istream &in);
    ostream &Afisare(ostream &out);
    double calculeazaPret();
};

// Constructors & destructors
Monovolum::Monovolum():Masini(){
    this->vechime.assign("");
}
Monovolum:: Monovolum(int lungime, int anFabricatie, int valoare, string vechime):Masini(lungime,anFabricatie,valoare){
    this->vechime.assign(vechime);
}
Monovolum:: Monovolum(const Monovolum &masina_monovolum) : Masini(masina_monovolum.getLungime(), masina_monovolum.getAnFabricatie(), masina_monovolum.getValoare()){
    this->vechime.assign(masina_monovolum.vechime);
}
Monovolum::~Monovolum(){
    this->vechime.assign("");
}

// Functii
Monovolum &Monovolum::operator=(Monovolum masina_monovolum) {
    dynamic_cast <Masini&> (*this) = dynamic_cast <Masini&> (masina_monovolum);
    this->vechime = masina_monovolum.vechime;
    return *this;
}
istream &operator>>(istream &in, Monovolum &masina_monovolum){
    in >> dynamic_cast <Masini&> (masina_monovolum);
    cout << "Vechime( Noua/SH): ";
    in >> masina_monovolum.vechime;

    // Daca string-ul introdus de utilizator nu este unul dintre cele 2 tipuri precedente
    // va fi nevoit sa reintroduca un alt string

    while(masina_monovolum.vechime != "Noua" && masina_monovolum.vechime != "SH"){
        cout << "Ati introdus un input invalid. Incercati din nou: ";
        in >> masina_monovolum.vechime;
    }
    return in;
}
ostream &operator<<(ostream &out, Monovolum &masina_monovolum){
    out << dynamic_cast <Masini&> (masina_monovolum);
    out << "Vechime: " << masina_monovolum.vechime << endl;
    return out;
}

// Functii de citire si afisare
istream &Monovolum::Citire(istream &in){
    in >> *this;
    return in;
}
ostream &Monovolum::Afisare(ostream &out){
    out << *this;
    return out;
}

double Monovolum ::calculeazaPret() {
    // valoarea masinii scade cu 12% pentru monovolume
    int aniExistenta = 2022 - this->getAnFabricatie();
    double pret = this->getValoare();
    for( int i = 1; i <= aniExistenta; i++)
        pret = pret - pret * 0.12;
    // daca e SH, se mai adauga un discount de 10%
    if(vechime == "SH")
        pret = pret - pret * 0.1;
    return pret;
}

bool operator==(const Monovolum &masina1, const Monovolum &masina2){
    return masina1.getLungime() == masina2.getLungime() && masina1.getAnFabricatie() == masina2.getAnFabricatie()
           &&  masina1.getValoare() == masina2.getValoare() && masina1.getVechime() == masina2.getVechime();
}

#endif //PROIECTFINALPOO_MONOVOLUM_H
