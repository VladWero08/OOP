#ifndef PROIECTFINALPOO_MASINI_H
#define PROIECTFINALPOO_MASINI_H

#include <iostream>

using namespace std;

class Masini{
    int lungime;
    int anFabricatie;
    int valoare;

public:

    // Constructors & Destructor
    virtual ~Masini() = default;
    Masini();
    Masini(int lungime, int anFabricatie, int valoare);
    Masini(const Masini &masina);

    // Setters && getters
    void setLungime( int lungime ) { this->lungime = lungime; }
    void setAnFabricatie( int anFabricatie ) { this->anFabricatie = anFabricatie; }
    void setValoare( int valoare ) { this->valoare = valoare; }

    int getLungime() const{ return lungime; }
    int getAnFabricatie() const{ return anFabricatie; }
    int getValoare() const{ return valoare; }

    // Functii

    // Pentru fiecare tip de masina, vechime & anul fabricatiei
    // vom recalcula pretul acesteia
    virtual double calculeazaPret(){ return valoare; }
    Masini &operator=(const Masini& masina);
    friend bool operator==(const Masini &masina1, const Masini &masina2);
    friend istream &operator>>(istream &in, Masini &masina);
    friend ostream &operator<<(ostream &out, const Masini &masina);
    virtual istream &Citire(istream &in);
    virtual ostream &Afisare(ostream &out);
};

// Constructors
Masini::Masini(){
    lungime = 0;
    anFabricatie = 0;
    valoare = 0;
}

Masini::Masini(int lungime, int anFabricatie, int valoare){
    this->lungime = lungime;
    this->anFabricatie = anFabricatie;
    this->valoare = valoare;
}

Masini::Masini(const Masini &masina){
    lungime = masina.lungime;
    anFabricatie = masina.lungime;
    valoare = masina.valoare;
}

// Functii
Masini &Masini::operator=(const Masini &masina) {
    lungime = masina.lungime;
    anFabricatie = masina.anFabricatie;
    valoare = masina.valoare;
    return *this;
}

istream &operator>>(istream &in, Masini &masina){
    cout << "Introduceti date corespunzatoare." << endl;
    cout << "Lungimea masinii( metri): ";
    in >> masina.lungime;
    cout << "Anul fabricatiei: ";
    in >> masina.anFabricatie;
    cout << "Valoarea masinii: ";
    in >> masina.valoare;
    return in;
}

ostream &operator<<(ostream &out, const Masini &masina){
    out << "Lungimea masinii: " << masina.lungime << endl;
    out << "Anul fabricatiei: " << masina.anFabricatie << endl;
    out << "Valoarea masinii: " << masina.valoare << endl;
    return out;
}

bool operator==(const Masini &masina1, const Masini &masina2) {
    return masina1.getLungime() == masina2.getLungime() && masina1.getAnFabricatie() == masina2.getAnFabricatie() &&  masina1.getValoare() == masina2.getValoare();
}

// Redefinim operatorul < pentru a putea clasa Masini in set-ul STL-ului
bool operator<(const Masini &masina1, const Masini &masina2) {
    return masina1.getValoare() < masina2.getValoare();
}

// Functii de citire si afisare, virtuale
istream &Masini::Citire(istream &in){
    in >> *this;
    return in;
}

ostream &Masini::Afisare(ostream &out){
    out << *this;
    return out;
}

#endif