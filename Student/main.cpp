#include <bits/stdc++.h>

using namespace std;

class student{
    string nume;
    int anNastere, nrCredite;
    bool dateValide = false;
    double medieGenerala;
    public:
        //Functii pentru validare
        int validAn(int); // anul nasterii trebuie sa fie <= 2012
        int validMedie(double); // media generala trebuie sa fie >=1 si <=10
        int validNume(string); // numele trebuie sa contina doar spatii si litere

        //Constructor fara parametrii
        student(){
            nume.assign("");
            anNastere = 0;
            nrCredite = 0;
            medieGenerala = 0.0;
        }
        //Constructor cu parametrii
        student(string nume, int anNastere, int nrCredite, double medieGenerala){
            if(validAn(anNastere)==1 && validMedie(medieGenerala)==1 && validNume(nume)==1){
                //Daca datele sunt valide, le atribuim clasei
                this->nume.assign(nume);
                this->anNastere = anNastere;
                this->nrCredite = nrCredite;
                this->medieGenerala = medieGenerala;
            } else{
                //Altfel atentionam utilizatorul ca nu sunt valide
                cout<<"Datele introduse nu sunt valide."<<endl;
                this->nume.assign("");
                this->anNastere = 0;
                this->nrCredite = 0;
                this->medieGenerala = 0;
            }
        }
        //Constructor de copiere
        student( student& x){
            // Nu trebuie sa verificam validitatea datelor deoarece
            // x este initializat <=> contine date valide
            nume.assign(x.nume);
            anNastere = x.anNastere;
            nrCredite = x.nrCredite;
            medieGenerala = x.medieGenerala;
        }
        //Destructor
        ~student(){
            nume.assign("");
            anNastere = 0;
            nrCredite = 0;
            medieGenerala = 0.0;
        }

        // Setters

        // Nu se va crea setter pentru 'dateValide' deoarece valoarea variabilei
        // va fi modificata doar in functia de citire

        // Setter pentru nume
        void setNume(string nume){
            if(validNume(nume)==1)
                this->nume.assign(nume);
            else cout<<"Numele trebuie sa contina doar litere si spatii."<<endl;
        }
        // Setter pentru anul nasterii
        void setAnNastere(int anNastere){
            if(validAn(anNastere)==1) this->anNastere = anNastere;
            else cout<<"Anul nasterii trebuie sa fie mai mic decat 2012.";
        }
        // Setter pentru numarul de credite
        void setCredite(int nrCredite){
            this->nrCredite = nrCredite;
        }
        // Setter pentru media generala
        void setMedie(double medie){
            if(validMedie(medieGenerala)==1) this->medieGenerala = medieGenerala;
            else cout<<"Media generala trebuie sa fie intre 1 si 10.";
        }

        //Getters
        string getNume()     { return nume;}
        int getAnNastere()   { return anNastere;}
        int getCredite()     { return nrCredite;}
        double getMedie()    { return medieGenerala;}
        bool getDateValide() { return dateValide;}

        //Citire si scrierere cu supraincarcarea operatorilor
        friend operator >>(istream &in, student &c){
            string nume; int anNastere=-1, nrCredite=-1; double medieGenerala=-1; bool valid=true;

            cout<<"Numele studentului: ";
            in.ignore();
            getline(in, nume);
            if(c.validNume(nume)==1){
                cout<<"Anul nasterii: ";
                in>>anNastere;
                // Daca anul de nastere nu este valid, anuntam utilizatorul
                if(c.validAn(anNastere)==0){
                    cout<<endl;
                    cout<<"Anul nasterii trebuie sa fie mai mic decat 2022."<<endl;
                    valid=false;
                } else{
                    // Daca anul de nastere este valid, continuam citirea
                    cout<<"Media generala a studentului: ";
                    in>>medieGenerala;
                    // Daca media generala nu este valida, anuntam utilizatorul
                    if(c.validMedie(medieGenerala)==0){
                        cout<<endl;
                        cout<<"Media generala trebuie sa fie intre 1 si 10."<<endl;
                        valid=false;
                    } else{
                        //Daca media generala este valida, continuam citirea
                        cout<<"Numarul de credite acumulat: ";
                            in>>nrCredite;
                    }
                }
            } else{
                cout<<"Numele trebuie sa contina doar litere si spatii."<<endl;
                valid=false;
            }

            if(valid==false){
                // Daca datele nu sunt valide, anuntam utilizatorul si nu atribuim nimic clasei
                cout<<"Ati introdus un input invalid. Incercati din nou."<<endl;
                cout<<endl;
                c.nume.assign("");
                c.anNastere = 0;
                c.nrCredite = 0;
                c.medieGenerala = 0.0;
            }
            else{
                //Altfel, atribui normal si setam 'dateValide' -> true
                c.dateValide = true;
                c.nume = nume;
                c.anNastere = anNastere;
                c.nrCredite = nrCredite;
                c.medieGenerala = medieGenerala;
            }
        }

        friend operator<<(ostream &out, student c){
            out<<"Numele studentului: "<<c.nume<<endl;
            out<<"Anul nasterii: "<<c.anNastere<<endl;
            out<<"Numarul de credite acumulat: "<<c.nrCredite<<endl;
            out<<"Media generala a studentului: "<<c.medieGenerala<<endl;
        }

};

inline int student::validAn(int an){
    if(an <= 2012)
        return 1;
    return 0;
}

inline int student::validMedie(double medie){
    if(medie>=1 && medie<=10)
        return 1;
    return 0;
}

inline int student::validNume(string nume){
    string alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ ";
    for(int i=0;i<nume.length();i++)
        if(alphabet.find(nume[i])==string::npos)
            return 0;
    return 1;
}

class grupa{
    string numeGrupa;   //Am adaugat aceasta variabila pentru a identifica unic grupa creata
    student *stud;
    int nrStudenti;
    double mediaGrupei;

    public:
        //Constructors
        grupa(){
            numeGrupa.assign("");
            stud = new student[0];
            nrStudenti = 0;
            mediaGrupei = 0;
        }

        grupa(grupa &x){
            numeGrupa.assign(x.numeGrupa);
            nrStudenti = x.nrStudenti;
            mediaGrupei = x.mediaGrupei;
            stud = new student[nrStudenti];
            for(int i=0;i<nrStudenti;i++)
                stud[i] = x.stud[i];
        }

        grupa(string numeGrupa, student x[], int nrStudenti, double mediaGrupei){
            this->numeGrupa.assign(numeGrupa);
            this->nrStudenti = nrStudenti;
            this->mediaGrupei = mediaGrupei;
            stud = new student[nrStudenti];
            for(int i=0;i<nrStudenti;i++)
                    stud[i] = x[i];
        }

        //Destructor
        ~grupa(){
            numeGrupa.assign("");
            delete []stud;
            nrStudenti = 0;
            mediaGrupei = 0;
        }

        //Setters
        //Setter-ul pentru mediaGrupei nu va exista deoarece ea o sa depinda de media elevilor
        void setNumarStudenti(int nrStudenti){
            this->nrStudenti = nrStudenti;
        }
        //Pentru a seta array-ul, vom avea nevoie si de lungimea acestuia
        //Pentru a-l aloca dinamic
        void setListaStudentilor(student lista[], int lenLista){
            delete []stud;
            stud = new student[lenLista];
            for(int i=0;i<lenLista;i++)
                stud[i] = lista[i];
        }

        void setNumeGrupa(string numeGrupa){
            this->numeGrupa.assign(numeGrupa);
        }
        //Getters
        int getNumarStudenti(){
            return nrStudenti;
        }

        double getMediaGrupei(){
            return mediaGrupei;
        }

        student *getListaStudentilor(){
            return stud;
        }

        string getNumeleGrupei(){
            return numeGrupa;
        }

        //Verification
        int Verificare(string);
        //Add
        void Adaugare(student);
        //Delete
        void Eliminare(string);

        friend operator >>(istream &in, grupa &c){
            cout<<"Introduceti numele grupei( nu se pot utiliza spatii): ";
            in>>c.numeGrupa;
            cout<<"Introduceti numarul de studenti: ";
            in>>c.nrStudenti;
            c.stud = new student [c.nrStudenti];
            for(int i=0;i<c.nrStudenti;i++){
                //Aici vom folosi 'dateValide' din clasa student
                //In cazul in care din greseala utilizatorul gresete input-ul si are deja foarte multi studenti
                //Introdusi corect, sa nu piarda progresul
                while(c.stud[i].getDateValide() == false){
                    cout<<"Studentul "<<i+1<<":"<<endl;
                    in>>c.stud[i];
                }
                c.mediaGrupei += c.stud[i].getMedie();
            }
            c.mediaGrupei /= c.nrStudenti;
            //Media grupei nu poate fi citita de catre utilizator
            //Deoarece trebuie sa depinda de date introduse anterior
            cout<<"Media grupei este: "<<c.mediaGrupei<<endl;
            cout<<"Grupa a fost creata cu succes."<<endl;
        }

        friend operator <<(ostream &out, grupa c){
            out<<"Numele grupei: "<<c.numeGrupa<<endl;
            out<<"Numarul de studenti: "<<c.nrStudenti<<endl;
            out<<"Media generala a grupei: "<<c.mediaGrupei<<endl;
            out<<"Studentii sunt: "<<endl;
            out<<endl;
            for(int i=0;i<c.nrStudenti;i++){
                out<<"Studentul "<<i+1<<":"<<endl;
                out<<c.stud[i];
                out<<endl;
            }
        }

};

int grupa::Verificare(string numeStudent){
    //Returneaza pozitia studentului in grupa
    //Daca exista, altfel -1
    for(int i=0;i<nrStudenti;i++)
        if(stud[i].getNume().compare(numeStudent)==0)
            return i;
    return -1;
}

void grupa::Adaugare(student studentNou)
{
    double sumaMediilorGenerale = nrStudenti * mediaGrupei;

    //Copiez grupa actuala intr-o grupa cu un spatiu in plus
    student *grupaNoua = new student[nrStudenti+1];
    for(int i=0;i<nrStudenti;i++)
        grupaNoua[i]=stud[i];
    //Noul student este introdus pe pozitia suplimentara
    grupaNoua[nrStudenti]=studentNou;

    //Grupa anterioara este dezalocata
    delete []stud;
    //Vom pointa lista privata de studenti catre cea locala
    stud = new student[++nrStudenti];
    for(int i=0;i<nrStudenti;i++)
        stud[i]=grupaNoua[i];

    delete []grupaNoua;
    sumaMediilorGenerale += studentNou.getMedie();
    mediaGrupei = sumaMediilorGenerale/nrStudenti;
}

void grupa::Eliminare(string numeStudent)
{
    {
        //Verificam daca studentul se afla in grupa
        if(Verificare(numeStudent) > -1){
            int pozitie = Verificare(numeStudent);
                //Copiem cu o pozitie spre stanga, incepand cu pozitia
                //Pe care se afla studentul cautat
                for(int i=pozitie;i<nrStudenti-1;i++)
                    stud[i]=stud[i+1];

                //Cream o lista cu un student mai putin
                //Ii atribuim valori pana la nrStudenti-1 dupa o copiem inapoi
                student *aux = new student[nrStudenti-1];
                for(int i=0;i<nrStudenti-1;i++)
                    aux[i]=stud[i];
                delete []stud;
                stud = new student[nrStudenti-1];
                stud = aux;
                //trebuie sters ultimul element din student

                // Aflam suma mediilor din formula: sumaMediilor / nrStudenti = mediaGenerala
                double sumaMediilorGenerale = nrStudenti * mediaGrupei;
                // Recalculam sumaMediilor, scazandu-l pe studentul eliminat
                sumaMediilorGenerale -= stud[pozitie].getMedie();
                nrStudenti--;
                mediaGrupei = sumaMediilorGenerale/nrStudenti;
        } else{
            //Altfel, informam utilizatorul ca nu exista
            cout<<"Studentul nu se afla in aceasta grupa. Incercati din nou.";
        }
    }
}

void testConstructors(){

    student Villy("olaeriu vlad",2002,300,9.54);
    student Nou(Villy);
    // La initiliaziare, daca exist vreo eroare aceasta se afiseaza
    student List[]={Villy,Nou};

    grupa grupa141("141",List,2,9.54);
    grupa grupa141nou(grupa141);

    //Afisez grupa initializata cu parametrii, si cea cu constructorul de copiere
    //Iar daca sunt la fel, inseamna ca sunt buni constructorii

    cout<<grupa141nou;
    cout<<grupa141;
}

void testEliminare(){
    student Stud1("olaeriu vlad",2002,300,9.54);
    student Stud2("vlad mihai",2002,300,9.54);
    student GrupaLista[]={Stud1,Stud2};
    grupa grupa141("Grupa141",GrupaLista,2,9.54);
    grupa141.Eliminare("olaeriu vlad");
    if(grupa141.getNumarStudenti()==1)
        cout<<"S-a eliminat studentul 'olaeriu vlad' cu succes.";
    else
        cout<<"Functia de eliminare nu functioneaza.";
}

int main()
{
    char raspuns[10];
    //Un mic template pentru comenzile disponibile
    cout<<"Acestea sunt comenzile pe care le veti avea la dispozitie: "<<endl
        <<"0 - nu"<<endl
        <<"1 - da"<<endl
        <<"2 - afisarea grupei( daca exista)"<<endl
        <<"3 - parasirea paginii"<<endl;

    grupa utilizator;
    while(strcmp(raspuns,"3")!=0 && strcmp(raspuns,"0")!=0)
    {
        cout<<"Doriti sa creati o grupa? ";
        cin>>raspuns;

        // Daca a apasat 1, se va crea o grupa
        if(strcmp(raspuns,"1")==0){
            //Se face citirea grupei
            cin>>utilizator;

            //Dupa ce s-a citit grupa, daca utilizatorul mai vrea sa o modifice cumva
            //O sa mai aiba posibilitatea, altfel este afisata intr-un fisier creat automat
            //Atat ca sa fie citita de la tastatura, dar si de utilizator insusi

            // Intai va avea posibilitatea de a mai adauga studenti
            while(strcmp(raspuns,"0") && strcmp(raspuns,"3")){
                cout<<"Doriti sa adaugati un alt student in grupa? ";
                cin>>raspuns;

                if(strcmp(raspuns,"1")==0){
                    //Daca raspunsul este da, adauga un student citit de la tastatura
                    student studentulNou;
                    cin>>studentulNou;
                    utilizator.Adaugare(studentulNou);
                } else if(strcmp(raspuns,"3")==0 || strcmp(raspuns,"2")==0){
                    // Daca vrea sa iasa sau sa afiseze pe ecran, va afisa dupa va iesi
                    cout<<utilizator;
                } else if(strcmp(raspuns,"0")==0){
                    // Daca nu vrea sa adauge va iesi
                    break;
                } else{
                    // Daca a introdus o comanda invalida, informam utilizatorul
                    cout<<"Ati introdus un input invalid. Incercati din nou."<<endl;
                }
            }
            if(strcmp(raspuns,"3")!=0)
                strcpy(raspuns,"");// daca utilizatorul nu vrea sa paraseasca pagina, continua progamul
            // A doua posibilitate este de a sterge un student din grupa
            while(strcmp(raspuns,"0") && strcmp(raspuns,"3")){
                cout<<"Doriti sa stergeti vreun student din grupa? ";
                cin>>raspuns;

                if(strcmp(raspuns,"1")==0){
                    //Daca raspunsul este da, sterge studentul al carui nume este citit de la tastatura
                    string studentSters;
                    cout<<"Care este numele studentului pe care doriti sa il stergeti din grupa? ";
                    cin>>studentSters;
                    utilizator.Eliminare(studentSters);
                } else if(strcmp(raspuns,"2")==0){
                    // Daca vrea sa iasa sau sa afiseze pe ecran, va afisa dupa va iesi
                    cout<<utilizator;
                } else if(strcmp(raspuns,"0")==0 || strcmp(raspuns,"3")==0){
                    // Daca nu vrea sa adauge va iesi
                    break;
                } else{
                    // Daca a introdus o comanda invalida, informam utilizatorul
                    cout<<"Ati introdus un input invalid. Incercati din nou."<<endl;
                }
            }
            //Daca a trecut prin toti pasii, utilizatorul va primi fi informat
            //Ca poate vedea/accesa grupa prin intermediul unor fisiere
            cout<<"Ati modificat cu succes grupa. Puteti gasi datele grupei intr-un fisier cu numele grupei initializate. "<<endl;

            string filenameVizualizare=utilizator.getNumeleGrupei();
            ofstream vizualizareFile(filenameVizualizare.c_str());
            vizualizareFile<<utilizator;


        } else if(strcmp(raspuns,"2")==0){
            if(utilizator.getMediaGrupei()==0 && utilizator.getNumarStudenti()==0 && utilizator.getNumeleGrupei()=="")
                cout<<"Nu se poate afisa grupa, deoarece nu exista."<<endl;
            else
                cout<<utilizator;
        } else if(strcmp(raspuns,"3")==0){
                continue;
        } else if(strcmp(raspuns,"0")==0){
                continue;
        } else{
            cout<<"Ati introdus un input invalid. Incercati din nou."<<endl;
        }
    }
    return 0;
}
