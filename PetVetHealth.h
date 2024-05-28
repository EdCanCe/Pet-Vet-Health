#ifndef PETVETHEALTH_H
#define PETVETHEALTH_H

#include <fstream>
#include <cstdio>
#include "Service.h"

class PetVetHealth{
    private:
        vector<Vet*> vets;
        vector<Owner*> owners;
        vector<Service*> services;
        void exit();
        void freeMemory();
        void loadData();
        void writeData();
        void clear();
        void loop();
        void waitUser();
        vector<int> getIndex(Vet&, Owner&, Pet&);

    public:
        void start();
};

void PetVetHealth::start(){
    clear();
    loadData();
    cout<<pfc<<"[[ PET VET HEALTH SYSTEM ]]\n\n"<<nfc;
    waitUser();
    loop();
    exit();
}

void PetVetHealth::exit(){
    writeData();
    cout<<"Did it end up on writing?\n";
    clear();
    cout<<"Did it did clear?";
    freeMemory();
    cout<<"Exiting...";
}

void PetVetHealth::freeMemory(){
    for(Service* i:services){
        delete i;
    }
    for(Owner* i:owners){
        for(Pet* j:i->getPets()){
            delete j;
        }
        delete i;
    }
    for(Vet* i:vets){
        delete i;
    }
}

void PetVetHealth::loadData(){
    FILE *fp=freopen("database.txt", "r", stdin);
    string s;
    while(getline(cin, s)){
        if(s=="X"){
            break;
        }
        else if(s=="V"){
            string lastName, name, phoneNumber, professionalLicense, college;
            lastName=ops.getString();
            name=ops.getString();
            phoneNumber=ops.getString();
            professionalLicense=ops.getString();
            college=ops.getString();
            vets.push_back(new Vet(name, lastName, phoneNumber, professionalLicense, college));
        }else if(s=="O"){
            string lastName, name, phoneNumber;
            lastName=ops.getString();
            name=ops.getString();
            phoneNumber=ops.getString();
            owners.push_back(new Owner(name, lastName, phoneNumber));
        }else if(s=="P"){
            string name;
            char sex;
            int day, month, year;
            string breed, annotations;
            int cage;
            name=ops.getString();
            sex=ops.getChar();
            day=ops.getInt();
            month=ops.getInt();
            year=ops.getInt();
            breed=ops.getString();
            annotations=ops.getString();
            cage=ops.getInt();
            owners[owners.size()-1]->addPet(*(new Pet(name, sex, day, month, year, breed, annotations, cage)));
        }else if(s=="M"){
            int iV, iO, iP, day, month, year;
            string description;
            iV=ops.getInt();
            iO=ops.getInt();
            iP=ops.getInt();
            day=ops.getInt();
            month=ops.getInt();
            year=ops.getInt();
            int dates[3]={day, month, year};
            description=ops.getString();
            string diagnosis, treatment;
            diagnosis=ops.getString();
            treatment=ops.getString();
            services.push_back(new MedicalCheck(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, diagnosis, treatment));
        }else if(s=="S"){
            int iV, iO, iP, day, month, year;
            string description;
            iV=ops.getInt();
            iO=ops.getInt();
            iP=ops.getInt();
            day=ops.getInt();
            month=ops.getInt();
            year=ops.getInt();
            int dates[3]={day, month, year};
            description=ops.getString();
            string treatment;
            treatment=ops.getString();
            services.push_back(new Surgery(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, treatment));
        }else if(s=="G"){
            int iV, iO, iP, day, month, year;
            string description;
            iV=ops.getInt();
            iO=ops.getInt();
            iP=ops.getInt();
            day=ops.getInt();
            month=ops.getInt();
            year=ops.getInt();
            int dates[3]={day, month, year};
            description=ops.getString();
            string materials, initialState, finalState;
            materials=ops.getString();
            initialState=ops.getString();
            finalState=ops.getString();
            services.push_back(new Grooming(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, materials, initialState, finalState));
        }else if(s=="H"){
            int iV, iO, iP, day, month, year;
            string description;
            iV=ops.getInt();
            iO=ops.getInt();
            iP=ops.getInt();
            day=ops.getInt();
            month=ops.getInt();
            year=ops.getInt();
            int dates[3]={day, month, year};
            description=ops.getString();
            int sDay, sMonth, sYear, eDay, eMonth, eYear;
            sDay=ops.getInt();
            sMonth=ops.getInt();
            sYear=ops.getInt();
            eDay=ops.getInt();
            eMonth=ops.getInt();
            eYear=ops.getInt();
            int sDates[3]={sDay, sMonth, sYear};
            int eDates[3]={eDay, eMonth, eYear};
            services.push_back(new Hotel(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, sDates, eDates));
        }
    }
    fclose(fp);
    #ifdef _WIN32
    freopen("CON", "r", stdin);
    #else
    freopen("/dev/tty", "r", stdin);
    #endif
}

void PetVetHealth::writeData(){
    FILE *fp=freopen("database.txt", "w", stdout);
    fore(i,0,vets.size()){
        cout<<"V\n";
        vets[i]->printForDB();
    }
    fore(i,0,owners.size()){
        cout<<"O\n";
        owners[i]->printForDB();
        fore(j,0,owners[i]->petSize()){
            cout<<"P\n";
            owners[i]->getPet(j).printForDB();
        }
    }
    fore(i,0,services.size()){
        services[i]->printForDB(getIndex(services[i]->getVet(), services[i]->getOwner(), services[i]->getPet()));
    }
    cout<<"X";
    fclose(fp);
    #ifdef _WIN32
    freopen("CON", "w", stdout);
    #else
    freopen("/dev/tty", "w", stdout);
    #endif
}

void PetVetHealth::clear(){
#ifdef _WIN32
    //system("cls");
#else
    //system ("clear");
#endif
}

void PetVetHealth::loop(){
    int q=-1;
    while(q!=0){
        clear();
        cout<<"What you want to do?\n";
        cout<<"\t1.- Create a veterinary profile\n";
        cout<<"\t2.- Create an owner profile\n";
        cout<<"\t3.- Access an owner profile(Acces to Pets)";
        cout<<"\t0.- Exit\n";
        cout<<"Type the corresponding number: ";
        q=ops.getInt(0,3);
        switch(q){
        case 0:
            break;
        case 1:
            clear();
            vets.push_back(new Vet);
            break;
        }
    }
}

void PetVetHealth::waitUser(){
    cout<<"Press enter to continue: ";
    string s=ops.getString();
}

vector<int> PetVetHealth::getIndex(Vet& newVet, Owner& newOwner, Pet& newPet){
    int a, b, c;
    fore(i,0,vets.size()){
        if(vets[i]==&newVet){
            a=i;
            break;
        }
    }
    fore(i,0,owners.size()){
        if(owners[i]==&newOwner){
            b=i;
            break;
        }
    }
    fore(i,0,owners[b]->petSize()){
        if(&owners[b]->getPet(i)==&newPet){
            c=i;
        }
    }
    vector<int> v={a, b, c};
    return v;
}

#endif