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
        void showOwners();
        void goToOwner(int);
        void showPets(int);
        void goToPet(int, int);
        int showVets();
        void showRecords(Pet&);
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
    clear();
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
    ifstream inputFile("database.txt"); 
    string s;
    while(getline(inputFile, s)){
        if(s=="X"){
            break;
        }
        else if(s=="V"){
            string lastName, name, phoneNumber, professionalLicense, college;
            getline(inputFile, lastName);
            getline(inputFile, name);
            getline(inputFile, phoneNumber);
            getline(inputFile, professionalLicense);
            getline(inputFile, college);
            vets.push_back(new Vet(name, lastName, phoneNumber, professionalLicense, college));
        }else if(s=="O"){
            string lastName, name, phoneNumber;
            getline(inputFile, lastName);
            getline(inputFile, name);
            getline(inputFile, phoneNumber);
            owners.push_back(new Owner(name, lastName, phoneNumber));
        }else if(s=="P"){
            string name, aux;
            char sex;
            int day, month, year;
            string breed, annotations;
            int cage;
            getline(inputFile, name);
            getline(inputFile, aux);
            sex=aux[0];
            getline(inputFile, aux);
            day=ops.getInt(aux);
            getline(inputFile, aux);
            month=ops.getInt(aux);
            getline(inputFile, aux);
            year=ops.getInt(aux);
            getline(inputFile, breed);
            getline(inputFile, annotations);
            getline(inputFile, aux);
            cage=ops.getInt(aux);
            owners[owners.size()-1]->addPet(*(new Pet(name, sex, day, month, year, breed, annotations, cage)));
        }else if(s=="M"){
            int iV, iO, iP, day, month, year;
            string description, aux;
            getline(inputFile, aux);
            iV=ops.getInt(aux);
            getline(inputFile, aux);
            iO=ops.getInt(aux);
            getline(inputFile, aux);
            iP=ops.getInt(aux);
            getline(inputFile, aux);
            day=ops.getInt(aux);
            getline(inputFile, aux);
            month=ops.getInt(aux);
            getline(inputFile, aux);
            year=ops.getInt(aux);
            int dates[3]={day, month, year};
            getline(inputFile, description);
            string diagnosis, treatment;
            getline(inputFile, diagnosis);
            getline(inputFile, treatment);
            services.push_back(new MedicalCheck(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, diagnosis, treatment));
        }else if(s=="S"){
            int iV, iO, iP, day, month, year;
            string description, aux;
            getline(inputFile, aux);
            iV=ops.getInt(aux);
            getline(inputFile, aux);
            iO=ops.getInt(aux);
            getline(inputFile, aux);
            iP=ops.getInt(aux);
            getline(inputFile, aux);
            day=ops.getInt(aux);
            getline(inputFile, aux);
            month=ops.getInt(aux);
            getline(inputFile, aux);
            year=ops.getInt(aux);
            int dates[3]={day, month, year};
            getline(inputFile, description);
            string treatment;
            getline(inputFile, treatment);
            services.push_back(new Surgery(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, treatment));
        }else if(s=="G"){
            int iV, iO, iP, day, month, year;
            string description, aux;
            getline(inputFile, aux);
            iV=ops.getInt(aux);
            getline(inputFile, aux);
            iO=ops.getInt(aux);
            getline(inputFile, aux);
            iP=ops.getInt(aux);
            getline(inputFile, aux);
            day=ops.getInt(aux);
            getline(inputFile, aux);
            month=ops.getInt(aux);
            getline(inputFile, aux);
            year=ops.getInt(aux);
            int dates[3]={day, month, year};
            getline(inputFile, description);
            string materials, initialState, finalState;
            getline(inputFile, materials);
            getline(inputFile, initialState);
            getline(inputFile, finalState);
            services.push_back(new Grooming(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, materials, initialState, finalState));
        }else if(s=="H"){
            int iV, iO, iP, day, month, year;
            string description, aux;
            getline(inputFile, aux);
            iV=ops.getInt(aux);
            getline(inputFile, aux);
            iO=ops.getInt(aux);
            getline(inputFile, aux);
            iP=ops.getInt(aux);
            getline(inputFile, aux);
            day=ops.getInt(aux);
            getline(inputFile, aux);
            month=ops.getInt(aux);
            getline(inputFile, aux);
            year=ops.getInt(aux);
            int dates[3]={day, month, year};
            getline(inputFile, description);
            int sDay, sMonth, sYear, eDay, eMonth, eYear;
            getline(inputFile, aux);
            sDay=ops.getInt(aux);
            getline(inputFile, aux);
            sMonth=ops.getInt(aux);
            getline(inputFile, aux);
            sYear=ops.getInt(aux);
            getline(inputFile, aux);
            eDay=ops.getInt(aux);
            getline(inputFile, aux);
            eMonth=ops.getInt(aux);
            getline(inputFile, aux);
            eYear=ops.getInt(aux);
            int sDates[3]={sDay, sMonth, sYear};
            int eDates[3]={eDay, eMonth, eYear};
            services.push_back(new Hotel(*vets[iV], *owners[iO], owners[iO]->getPet(iP), dates, description, sDates, eDates));
        }
    }
    inputFile.close(); 
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
    system("cls");
#else
    system ("clear");
#endif
}

void PetVetHealth::loop(){
    int q=-1;
    while(q!=0){
        clear();
        cout<<bfc<<"[[ Main menu ]]"<<nfc<<"\n";
        cout<<"What you want to do?\n";
        cout<<"\t1.- Create a veterinary profile\n";
        cout<<"\t2.- Create an owner profile\n";
        cout<<"\t3.- Access an owner profile(Access to Pets)";
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
        case 2:
            clear();
            owners.push_back(new Owner);
            break;
        case 3:
            clear();
            showOwners();
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

void PetVetHealth::showOwners(){
    cout<<bfc<<"[[ List of owners ]]"<<nfc<<"\n";
    if(owners.size() == 0){
        cout<<rfc<<"There are no owners.\n"<<nfc<<"Going back...";
        waitUser();
        return;
    }
    fore(i,0,owners.size()){
        cout<<"\t"<<i<<".- "<<owners[i]->getLastName()<<" "<<owners[i]->getName()<<": "<<owners[i]->getPhone()<<"\n";
    }
    cout<<"\t Type \"-1\" to go back\n";
    cout<<"\t Type \"0 - "<<owners.size()-1<<"\" to access that owner's index\n";
    cout<<"\nWhat you want to do? \n";
    int q=ops.getInt(-1, owners.size()-1);
    if(q==-1) return;
    goToOwner(q);
}

void PetVetHealth::goToOwner(int index){
    cout<<"\n";
    int q=-1;
    while(q!=0){
        clear();
        cout<<bfc<<"[[ Owner profile ]]"<<nfc<<"\n";
        owners[index]->showData();
        cout<<"What you want to do?\n";
        cout<<"\t1.- Add a pet to this owner\n";
        cout<<"\t2.- Access to a pet\n";
        cout<<"\t0.- Go back\n";
        cout<<"Type the corresponding number: ";
        q=ops.getInt(0,2);
        switch(q){
        case 0:
            break;
        case 1:
            clear();
            owners[index]->addPet(*(new Pet));
            break;
        case 2:
            clear();
            showPets(index);
            break;
        }
    }
}

void PetVetHealth::showPets(int index){
    cout<<bfc<<"[[ List of pets ]]"<<nfc<<"\n";
    if(owners[index]->petSize() == 0){
        cout<<rfc<<"There are no pet's linked to this user.\n"<<nfc<<"Going back...";
        waitUser();
        return;
    }
    fore(i,0,owners[index]->petSize()){
        cout<<"\t"<<i<<".- "<<owners[index]->getPet(i).getName()<<"\n";
    }
    cout<<"\t Type \"-1\" to go back\n";
    cout<<"\t Type \"0 - "<<owners[index]->petSize()-1<<"\" to access that pet's index\n";
    cout<<"\nWhat you want to do? \n";
    int q=ops.getInt(-1, owners[index]->petSize()-1);
    if(q==-1) return;
    goToPet(index, q);
}

void PetVetHealth::goToPet(int ownerIndex, int petIndex){
    cout<<"\n";
    int q=-1;
    while(q!=0){
        clear();
        bool cage = owners[ownerIndex]->getPet(petIndex).getCage() != 0;
        cout<<bfc<<"[[ Pet profile ]]"<<nfc<<"\n";
        owners[ownerIndex]->getPet(petIndex).showData();
        cout<<"What you want to do?\n";
        cout<<"\t1.- Add a medical check to this pet\n";
        cout<<"\t2.- Add a surgery to this pet\n";
        cout<<"\t3.- Add a grooming session to this pet\n";
        cout<<"\t4.- Add a hotel entry linked to this pet\n";
        cout<<"\t5.- View this pet's records\n";
        if(cage) cout<<"\t6.- Give the pet to it's owner\n";
        cout<<"\t0.- Go back\n";
        cout<<"Type the corresponding number: ";
        int vetIndex;
        q=ops.getInt(0, cage ? 6 : 5);
        switch(q){
        case 0:
            break;
        case 1:
            clear();
            vetIndex=showVets();
            services.push_back(new MedicalCheck(*vets[vetIndex], *owners[ownerIndex], owners[ownerIndex]->getPet(petIndex)));
            break;
        case 2:
            clear();
            vetIndex=showVets();
            services.push_back(new Surgery(*vets[vetIndex], *owners[ownerIndex], owners[ownerIndex]->getPet(petIndex)));
            break;
        case 3:
            clear();
            vetIndex=showVets();
            services.push_back(new Grooming(*vets[vetIndex], *owners[ownerIndex], owners[ownerIndex]->getPet(petIndex)));
            break;
        case 4:
            clear();
            vetIndex=showVets();
            services.push_back(new Hotel(*vets[vetIndex], *owners[ownerIndex], owners[ownerIndex]->getPet(petIndex)));
            break;
        case 5:
            clear();
            showRecords(owners[ownerIndex]->getPet(petIndex));
            break;
        case 6:
            clear();
            owners[ownerIndex]->getPet(petIndex).setCage(0);
            break;
        }
    }
}

int PetVetHealth::showVets(){
    cout<<bfc<<"[[ List of vets ]]"<<nfc<<"\n";
    fore(i,0,vets.size()){
        cout<<"\t"<<i<<".- "<<vets[i]->getLastName()<<" "<<vets[i]->getName()<<": "<<vets[i]->getCollege()<<"\n";
    }
    cout<<"\t Type \"0 - "<<vets.size()-1<<"\" to access that vets's index\n";
    cout<<"\nWhat vet is doing this service? \n";
    int q=ops.getInt(0, vets.size()-1);
    return q;
}

void PetVetHealth::showRecords(Pet& patient){
    vector<Service*> filteredServices;
    fore(i,0,services.size()){
        if(&services[i]->getPet() == &patient){
            filteredServices.push_back(services[i]);
        }
    }
    cout<<bfc<<"[[ Records ]]"<<nfc<<"\n";
    if(filteredServices.size() == 0){
        cout<<rfc<<"There are no records linked to this pet.\n"<<nfc<<"Going back...";
        waitUser();
        return;
    }
    fore(i,0,filteredServices.size()){
        filteredServices[i]->print();
        cout<<"\n";
        if((i+1)<filteredServices.size()) cout<<rfc<<" - - - - - - - \n\n\n"<<nfc;
    }
    waitUser();
}

#endif