#include <bits/stdc++.h>

using namespace std;

class Contract{
    static int nrContractUnic;
    int nrContract;
    int anul;
    string beneficiar;
    string furnizor;
    float valoare;

public:
    //Functii pentru validare
    int validAn(int); // anul semnarii contractului
    // sa fie <= 2022
    int validNume(string); // numele trebuie sa contina doar spatii si litere
    int validBenefFurniz(string,string); // verifica daca numele furnizorului = beneficiar

    // Constructors & destructor
    Contract();
    Contract(int nrContract, int anul, string beneficiar, string furnizor, float valoare);
    Contract(Contract &contract);
    virtual ~Contract() {};

    // Getters
    int getNrContract(){ return nrContract; }
    static int getNrContractUnic() {return nrContractUnic;}
    int getAnul(){ return anul; }
    string getBeneficiar(){ return beneficiar; }
    string getFurnizor(){ return furnizor; }
    float getValoare(){ return valoare; }

    // Setters
    void setNrContract(int);
    void setAnul(int anul);
    void setBeneficiar(string beneficiar);
    void setFurnizor(string furnizor);
    void setValoare(float valoare);

    // Overloading
    Contract &operator=(Contract contract);
    friend istream &operator>>(istream &in, Contract &contract);
    friend ostream &operator<<(ostream &out, Contract &contract);

    // Valoare incasata
    virtual double valoareIncasata();
};

int Contract::nrContractUnic = 0;

// Constructors

Contract::Contract(){
    this->nrContract = nrContractUnic++;
    this->anul = 0;
    this->beneficiar.assign("");
    this->furnizor.assign("");
    this->valoare = 0;
};

Contract::Contract(int nrContract, int anul, string beneficiar, string furnizor, float valoare){
    this->nrContract = nrContractUnic++;
    this->anul = anul;
    this->beneficiar.assign(beneficiar);
    this->furnizor.assign(furnizor);
    this->valoare = valoare;
}

Contract::Contract(Contract &contract){
    this->nrContract = nrContractUnic++;
    this->anul = contract.anul;
    this->beneficiar.assign(contract.beneficiar);
    this->furnizor.assign(contract.furnizor);
    this->valoare = contract.valoare;
};

// Setters
void Contract::setNrContract(int nrContract) {
    this->nrContract = nrContract;
}

void Contract::setAnul(int anul) {
    if(!validAn(anul)){
        cout<<"Anul semnarii nu poate fi mai mare decat 2022"<<endl;
        cout<<"Va rugam introduceti un an valid."<<endl;
    } else{
        this->anul = anul;
    }
}

void Contract::setBeneficiar(string beneficiar) {
    if(!validNume(beneficiar)){
        cout<<"Anul semnarii nu poate fi mai mare decat 2022"<<endl;
        cout<<"Va rugam introduceti un an valid."<<endl;
    } else{
        this->beneficiar = beneficiar;
    }
}

void Contract::setFurnizor(string furnizor) {
    if(!validNume(furnizor) && !validBenefFurniz(getBeneficiar(),furnizor)){
        cout<<"Numele furnizorului trebuie sa contina doar litere si spatii & sa fie diferit de cel al beneficiarului."<<endl;
        cout<<"Va rugam introduceti un an valid."<<endl;
    } else{
        this->furnizor = furnizor;
    }
}

void Contract::setValoare(float valoare) {
    this->valoare = valoare;
}

// Useful functions

int Contract::validAn(int an){
    if(an <= 2022)
        return 1;
    return 0;
}

int Contract::validNume(string nume){
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    for(int i=0;i<nume.length();i++)
        if(alphabet.find(nume[i])==string::npos)
            return 0;
    return 1;
}

int Contract::validBenefFurniz(string beneficiar, string furnizor) {
    if(beneficiar.compare(furnizor) != 0){
        return 1;
    }
    return 0;
}

// Overloading

Contract &Contract::operator = (const Contract copie){
    nrContract = copie.nrContract;
    anul = copie.anul;
    beneficiar = copie.beneficiar;
    furnizor = copie.furnizor;
    valoare = copie.valoare;
    return *this;
}

istream &operator >> (istream &in, Contract &c){
    cout<<"Numarul contractului: ";
    in>>c.nrContract;
    cout<<"Anul semnarii contractului: ";
    in>>c.anul;
    if(!c.validAn(c.anul)){
        while(!c.validAn(c.anul)){
            cout<<"Anul semnarii nu poate fi mai mare decat 2022"<<endl;
            cout<<"Va rugam introduceti un an valid: ";
            in>>c.anul;
        }
    }

    cout<<"Beneficiarul: ";
    in>>c.beneficiar;
    if(!c.validNume(c.beneficiar)){
        while(!c.validNume(c.beneficiar)){
            cout<<"Numele beneficiarului trebuie sa contina doar litere si spatii."<<endl;
            cout<<"Introduceti un nume valid: ";
            in>>c.beneficiar;
        }
    }

    cout<<"Furnizorul: ";
    in>>c.furnizor;
    if(!c.validNume(c.furnizor) || !c.validBenefFurniz(c.beneficiar,c.furnizor)){
        while(c.validNume(c.furnizor) == 0 || c.validBenefFurniz(c.beneficiar,c.furnizor) == 0){
            cout<<"Numele furnizorului trebuie sa contina doar litere si spatii & sa fie diferit de cel al beneficiarului."<<endl;
            cout<<"Introduceti un nume valid: ";
            in>>c.furnizor;
        }
    }

    cout<<"Valoarea: ";
    in>>c.valoare;
    return in;
}

ostream &operator << (ostream &out, Contract &c){
    out<<"Numarul contractului: "<<c.nrContract<<endl;
    out<<"Anul semnarii contractului: "<<c.anul<<endl;
    out<<"Beneficiarul: "<<c.beneficiar<<endl;
    out<<"Furnizorul: "<<c.furnizor<<endl;
    out<<"Valoarea: "<<c.valoare<<endl;
    return out;
}

// Valoare incasata
double Contract::valoareIncasata() {
    return valoare;
}

class ContractInchiriere: public Contract{
    int perioada;

public:
    // Constructors and destructor
    ContractInchiriere();
    ContractInchiriere(int, int, string, string, float, int);
    ContractInchiriere(ContractInchiriere &contract);
    virtual ~ContractInchiriere();

    // Getters & setters
    int getPerioada(){ return this->perioada; }
    void setPerioada(int perioada);

    // Overloading
    ContractInchiriere &operator=(ContractInchiriere contract);
    friend istream &operator>>(istream &in, ContractInchiriere &contract);
    friend ostream &operator<<(ostream &out, ContractInchiriere &contract);

    // Calcul valoare incasasta
    double valoareIncasata();
};

// Constructors

ContractInchiriere ::ContractInchiriere( ContractInchiriere &contract) : Contract(contract.getNrContract(), contract.getAnul(), contract.getBeneficiar(), contract.getFurnizor(), contract.getValoare()){
    this->perioada = contract.perioada;
}

ContractInchiriere :: ContractInchiriere(int nrContract, int anul, string beneficiar,
                                         string furnizor, float valoare, int perioada) : Contract(nrContract,anul,beneficiar,furnizor,valoare){
    if(perioada < 1){
        cout<<"Perioada de inchiere trebuie sa fie de cel putin o luna."<<endl;
        cout<<"Introduceti o perioada valida."<<endl;
    } else{
        this->perioada = perioada;
    }
}

ContractInchiriere :: ContractInchiriere() : Contract() {
    this->perioada = 0;
}

ContractInchiriere :: ~ContractInchiriere(){
    this->perioada = 0;
}

// Setters

void ContractInchiriere::setPerioada(int perioada) {
    if(perioada < 1){
        cout<<"Perioada de inchiere trebuie sa fie de cel putin o luna."<<endl;
        cout<<"Introduceti o perioada valida."<<endl;
    } else{
        this->perioada = perioada;
    }
}

// Overloading
ContractInchiriere &ContractInchiriere::operator=(ContractInchiriere contract){
    this->perioada = contract.perioada;
    this->setAnul(contract.getAnul());
    this->setBeneficiar(contract.getBeneficiar());
    this->setFurnizor(contract.getFurnizor());
    this->setValoare(contract.getValoare());
    return *this;
}

istream &operator>>(istream &in, ContractInchiriere &contract){
    in >> dynamic_cast<Contract&>(contract);
    cout << "Perioada: ";
    in >> contract.perioada;
    if(contract.perioada < 1){
        while(contract.perioada < 1){
            cout<<"Perioada de inchiere trebuie sa fie de cel putin o luna."<<endl;
            cout<<"Introduceti o perioada valida."<<endl;
            in >> contract.perioada;
        }
    }
    return in;
}

ostream &operator<<(ostream &out, ContractInchiriere &contract){
    out << dynamic_cast<Contract&>(contract);
    out << "Perioada: " << contract.perioada << endl;
    out << "Valoare incasata: " << contract.valoareIncasata() << endl;
    cout << endl;
    return out;
}

// Calcul valoare incasata
double ContractInchiriere ::valoareIncasata() {
    if(perioada < 12){
        return this->getValoare() * perioada;
    } else if ( perioada >=12 && perioada < 36){
        // Pentru o perioada intre 1 si 3 ani, discount de 3%
        return this->getValoare() * perioada * 0.97;
    } else {
        // Pentru o perioada mai mare de 3 ani, discount 5%
        return this->getValoare() * perioada * 0.95;
    }
}

class Dosar{
    static int idDosar;
    int nrTotalContracte;
    ContractInchiriere *contracte;
    double valoareTotalIncasata;

public:

    // Constructors & destrcutor
    Dosar();
    Dosar(int, ContractInchiriere*);
    Dosar(Dosar&);
    ~Dosar();

    // Setters & getters
    void setContracte(ContractInchiriere*,int);
    static int getIDDosar();
    int getNrContracte();
    float getValoareTotalIncasata();
    ContractInchiriere *getContracte();

    // Overloading
    Dosar &operator=(Dosar dosar);
    friend istream &operator>>(istream &in, Dosar &dosar);
    friend ostream &operator<<(ostream &out, Dosar &dosar);

    // Adaugare & stergere contract
    void adaugaContract(Contract*);
    void stergeContract(int);
};

int Dosar::idDosar = 0;

// Constructors & destructors

Dosar ::Dosar(){
    idDosar++;
    this->nrTotalContracte = 0;
    contracte = nullptr;
}

Dosar ::Dosar(int numarContracte,ContractInchiriere *contracte){
    idDosar++;
    this->nrTotalContracte = numarContracte;
    this->contracte = new ContractInchiriere [numarContracte];
    for(int i=0;i<numarContracte;i++){
        this->contracte[i] = contracte[i];
        valoareTotalIncasata += contracte[i].valoareIncasata();
    }
}

Dosar ::Dosar(Dosar &dosar){
    idDosar++;
    this->nrTotalContracte = dosar.nrTotalContracte;
    this->contracte = new ContractInchiriere [this->nrTotalContracte];
    for(int i=0;i<this->nrTotalContracte;i++){
        this->contracte[i] = dosar.contracte[i];
        valoareTotalIncasata += contracte[i].valoareIncasata();
    }
}

Dosar ::~Dosar(){
    this->nrTotalContracte = 0;
    delete [] this->contracte;
}

// Setters & getters

void Dosar ::setContracte(ContractInchiriere *contracte, int nrTotalContracte) {
    this->nrTotalContracte = nrTotalContracte;
    delete [] this->contracte;
    this->contracte = new ContractInchiriere [this->nrTotalContracte];
    for(int i=0;i<this->nrTotalContracte;i++){
        this->contracte[i] = contracte[i];
        valoareTotalIncasata += contracte[i].valoareIncasata();
    }
}

int Dosar ::getNrContracte() {
    return nrTotalContracte;
}

float Dosar::getValoareTotalIncasata() {
    return valoareTotalIncasata;
}

ContractInchiriere *Dosar::getContracte() {
    return contracte;
}

int Dosar::getIDDosar() {
    return idDosar;
}

// Overloading

Dosar &Dosar::operator=(Dosar dosar) {
    this->nrTotalContracte = dosar.nrTotalContracte;
    delete [] this->contracte;
    valoareTotalIncasata = 0;

    this->contracte = new ContractInchiriere [this->nrTotalContracte];
    for(int i=0;i<this->nrTotalContracte;i++){
        this->contracte[i] = dosar.contracte[i];
        valoareTotalIncasata += contracte[i].valoareIncasata();
    }
    return *this;
}

ostream &operator << (ostream &out, Dosar &dosar){
    if(dosar.nrTotalContracte != 0)
        Dosar::idDosar ++;
    out << endl;
    out << "Numarul total de contracte este de: ";
    out << dosar.nrTotalContracte << endl << endl;
    if(dosar.nrTotalContracte > 0){
        out << "Contractele sunt:" << endl;
        for(int i=0;i<dosar.nrTotalContracte;i++){
            out << dosar.contracte[i];
        }
        out << endl;
        out << "Valoare totala a dosarului este de: ";
        out << dosar.valoareTotalIncasata << endl;
    } else{
        cout << "Nu este niciun contract de afisat.";
    }
    return out;
}

istream &operator >> (istream &in, Dosar &dosar){
    cout << "Introduceti numarul de contracte: ";
    in >> dosar.nrTotalContracte;
    dosar.contracte = new ContractInchiriere [dosar.nrTotalContracte];
    for(int i=0; i<dosar.nrTotalContracte; i++){
        cout << "Contractul " << i+1 <<endl;
        in >> dosar.contracte[i];
        dosar.valoareTotalIncasata += dosar.contracte[i].valoareIncasata();
    }
    return in;
}

// Stergese & adaugare

void Dosar::adaugaContract(Contract *contractNou) {
    ContractInchiriere *test = dynamic_cast<ContractInchiriere*>(contractNou);
    if( test != NULL){
        this->nrTotalContracte += 1;
        ContractInchiriere *contracteCopie = new ContractInchiriere [nrTotalContracte];

        for(int i=0;i<this->nrTotalContracte-1;i++){
            contracteCopie[i] = this->contracte[i];
        }

        contracteCopie[nrTotalContracte-1] = *test;
        this->valoareTotalIncasata += contracteCopie[nrTotalContracte-1].valoareIncasata();
        delete [] contracte;

        this->contracte = new ContractInchiriere [nrTotalContracte];
        for( int i=0;i<this->nrTotalContracte;i++){
            contracte[i] = contracteCopie[i];
        }
        delete [] contracteCopie;
    } else{
        cout << "Contractul trebuie sa fie de tip inchiriere pentru a fi adaugat!" << endl;
    }
}

void Dosar::stergeContract(int id) {
    int aux=-1;
    for(int i=0;i<this->nrTotalContracte;i++){
        if(contracte[i].getNrContract() == id)
            aux = i;
    }

    if(aux == -1){
        cout << "Contractul nu poate fi sters deoarece nu exista in dosar." << endl;
    } else{
        ContractInchiriere *copie = new ContractInchiriere [this->nrTotalContracte-1];
        for(int i=aux;i<this->nrTotalContracte-1;i++){
            copie[i] = this->contracte[i+1];
        }

        delete [] this->contracte;
        this->contracte = new ContractInchiriere [this->nrTotalContracte-1];
        this->nrTotalContracte --;

        for(int i=0;i<this->nrTotalContracte;i++){
            this->contracte[i] = copie[i];
        }

        delete [] copie;
        cout << "Contractul a fost sters cu succes." << endl;
    }

}

void testare(){
    ContractInchiriere contract_inchiriere_test(2002,20,"Villy","Wero",300,12);
    cout << contract_inchiriere_test;

    Contract contract_test(2002,21,"Vlad","Mihai",300);
    cout << contract_test;
}

int main(){
    int comanda, id_stergere;
    Dosar utilizator;
    ContractInchiriere contract_inchiriere_nou;
    Contract *contract_nou = &contract_inchiriere_nou;

    cout << "Doriti sa aveti o agenda a contractelor dumneavoastra imobiliara?";
    cout << "Platforma aceasta face exact acest lucru automat pentru dumneavoastra.";
    cout << endl;
    cout << "/////////////////////";
    cout << endl;
    cout << "Comenzile pe care le aveti la dispozitie:" <<endl;
    cout << "1 - Creati un dosar" << endl;
    cout << "2 - Afisati dosarul( daca acesta este creat)" << endl;
    cout << "3 - Stergeti un contract din dosarul creat" << endl;
    cout << "4 - Adaugati un nou contract la dosarul creat" << endl;
    cout << "0 - Parisiti & salvati datele introduse" << endl;

    cout << "Comanda: ";
    cin >> comanda;
    if(comanda < 0 || comanda > 4){
        while(comanda < 0 || comanda > 4){
            cout << "Va rugam sa introduceti o comanda valida( intre 0 si 4)." << endl;
            cout << "Comanda: ";
            cin >> comanda;
        }
    }
    while (comanda != 0){
        switch(comanda){
            case 1:
                if ( utilizator.getNrContracte() > 0) {
                    int comandaLocala;
                    cout << "Deja ati creat un dosar." << endl;
                    cout << "Apasati tasta daca doriti: " << endl;
                    cout << "1 - Sa salvati intr-un fisier dosarul deja creat si sa creati unul nou." << endl;
                    cout << "2 - Sa stergeti dosarul anterior si sa creati unul nou." << endl;
                    cout << "3 - Sa va intoarceti la meniul principal." << endl;
                    cout << "Comanda: ";
                    cin >> comandaLocala;
                    while (comandaLocala != 1 && comandaLocala != 2 && comandaLocala!=3) {
                        switch (comandaLocala) {
                            case 1:
                                cout << "Dosarul anterior a fost salvat si il gasiti in fisierul Dosar"
                                     << utilizator.getIDDosar() << ".txt." << endl;
                                cout << "Ati ales sa creati un dosar. Va rugam sa introduceti datele corespunzatoare."
                                     << endl;
                                cin >> utilizator;
                                break;
                            case 2:
                                cout << "Dosarul anterior a fost sters." << endl;
                                cout << "Ati ales sa creati un dosar. Va rugam sa introduceti datele corespunzatoare."
                                     << endl;
                                cin >> utilizator;
                                break;
                            case 3:
                                break;
                            default:
                                cout << "Trebuie sa alegeti intre comanda 1 si 3." << endl;
                                break;
                        }
                        cout << "Comanda: ";
                        cin >> comandaLocala;
                    }
                } else{
                    cout << "Ati ales sa creati un dosar. Va rugam sa introduceti datele corespunzatoare." << endl;
                    cin >> utilizator;
                    cout << "Ati creat dosarul cu succes!" << endl;
                }
                break;
            case 2:
                if( utilizator.getNrContracte() == 0){
                    cout << "Inca nu ati creat un dosar. Va rugam creati un dosar pentru a-l putea vizualiza." << endl;
                } else{
                    cout << utilizator;
                }
                break;

            case 3:
                if( utilizator.getNrContracte() == 0){
                    cout << "Inca nu ati creat un dosar. Va rugam creati un dosar pentru a putea sterge un contract." << endl;
                } else{
                    cout << "Ati ales sa stergeti un contract." << endl;
                    cout << "Introduceti id-ul contractului pe care doriti sa il stergeti:" << endl;
                    cin >> id_stergere;
                    utilizator.stergeContract(id_stergere);
                }
                break;

            case 4:
                if( utilizator.getNrContracte() == 0){
                    cout << "Inca nu ati creat un dosar. Va rugam creati un dosar pentru a adauga un nou contract." << endl;
                } else{
                    cout << "Ati ales sa introduceti un nou contract in dosarul dvs." << endl;
                    cout << "Va rugam sa introduceti contractul." << endl;
                    cin >> *dynamic_cast<ContractInchiriere *>(contract_nou);
                    utilizator.adaugaContract(contract_nou);
                }
                break;

            default:
                cout << "Va rugam sa introduceti o comanda valida( intre 0 si 4)." << endl;
                break;
        }
        cout << "Comanda: ";
        cin >> comanda;
    }

    if(utilizator.getNrContracte() != 0){
        string outputFile = "Dosarul" + to_string(utilizator.getIDDosar());
        ofstream output(outputFile.c_str());
        output<<utilizator;
    }

    return 0;
}
