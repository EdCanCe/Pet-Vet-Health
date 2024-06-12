/*
*
* Pet Vet Health Proyect - PetVetHealth Class
* A01645576
* This class is the main system. It has loops that are used
* to do different things depending on the user input.
*
*/
#ifndef PETVETHEALTH_H
#define PETVETHEALTH_H

#include <fstream>
#include <cstdio>
#include <algorithm>
#include "Service.h"

//Declaration of PetVetHealth class
class PetVetHealth{
    //Declaration of private attributes
    private:
        vector<Vet*> vets;
        vector<Owner*> owners;
        vector<Service*> services;

    //Declaration of public methods.
    public:
        void start();
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
};

/**
 * Starts the system.
 * 
 * Clears the screen, loads the data, prints a message, starts
 * the loop of all the actions, and then, when the loop ends it
 * exits the system.
 * 
 * @param 
 * 
 * @return
 */
void PetVetHealth::start(){
    clear();
    loadData();
    cout<<pfc<<"[[ PET VET HEALTH SYSTEM ]]\n\n"<<nfc;
    waitUser();
    loop();
    exit();
}

/**
 * Exits the system
 * 
 * Stores all the data in a file, clears the screen, and frees the
 * memory
 * 
 * @param 
 * 
 * @return
 */
void PetVetHealth::exit(){
    writeData();
    clear();
    freeMemory();
}

/**
 * Frees the memory.
 * 
 * Loops through the data (services, vets, owners and pets)
 * and deletes each of the elements to free the memory.
 * 
 * @param 
 * 
 * @return
 */
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

/**
 * Loads the data.
 * 
 * By having "database.txt" as the input, uses the stored data
 * and starts to fill each of the vectors representing the
 * different data. It does this by looping until the file ends.
 * Depending on the first char that it reads it means if it is a
 * service, a vet, an owner or a pet. Finally, it sorts the vets
 * and the owners depending on their last name, and if it's the
 * same, then on their name.
 * 
 * @param 
 * 
 * @return
 */
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
    sort(vets.begin(), vets.end(), [](Vet* a, Vet* b){
        if(a->getLastName() == b->getLastName()){
            return a->getName() < b->getName();
        }
        return a->getLastName() < b->getLastName();
    });
    sort(owners.begin(), owners.end(), [](Owner* a, Owner* b){
        if(a->getLastName() == b->getLastName()){
            return a->getName() < b->getName();
        }
        return a->getLastName() < b->getLastName();
    });
}

/**
 * Stores the data.
 * 
 * By using the methods of the different classes to store
 * the data for the database it writes it in the "database.txt"
 * file. To print the services uses polymorphism. At the end it 
 * closes the file.
 * 
 * @param 
 * 
 * @return
 */
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
    delete fp;
    #ifdef _WIN32
    freopen("CON", "w", stdout);
    #else
    freopen("/dev/tty", "w", stdout);
    #endif
}

/**
 * Clears the screen.
 * 
 * It does this by checking the OS and using their respective
 * command to clear the console.
 * 
 * @param 
 * 
 * @return
 */
void PetVetHealth::clear(){
#ifdef _WIN32
    system("cls");
#else
    system ("clear");
#endif
}

/**
 * The main loop of the program.
 * 
 * Prints the different options that can be accesed and
 * depending on the user input does something different.
 * 
 * @param 
 * 
 * @return
 */
void PetVetHealth::loop(){
    int q=-1;
    while(q!=0){
        clear();
        cout<<bfc<<"[[ Main menu ]]"<<nfc<<"\n";
        cout<<"What you want to do?\n";
        cout<<"\t1.- Create a veterinary profile\n";
        cout<<"\t2.- Create an owner profile\n";
        cout<<"\t3.- Access an owner profile(Access to Pets)\n";
        cout<<"\t0.- Exit\n";
        cout<<"Type the corresponding number: ";
        q=ops.getInt(0,3);
        switch(q){
        case 0:
            break;
        case 1:
            clear();
            vets.push_back(new Vet);
            sort(vets.begin(), vets.end(), [](Vet* a, Vet* b){
                if(a->getLastName() == b->getLastName()){
                    return a->getName() < b->getName();
                }
                return a->getLastName() < b->getLastName();
            });
            break;
        case 2:
            clear();
            owners.push_back(new Owner);
            sort(owners.begin(), owners.end(), [](Owner* a, Owner* b){
                if(a->getLastName() == b->getLastName()){
                    return a->getName() < b->getName();
                }
                return a->getLastName() < b->getLastName();
            });
            break;
        case 3:
            clear();
            showOwners();
            break;
        }
    }
}

/**
 * Waits for user input.
 * 
 * Tries to get a string, therefore making the system wait
 * until the user presses enter.
 * 
 * @param 
 * 
 * @return
 */
void PetVetHealth::waitUser(){
    cout<<"Press enter to continue: ";
    string s=ops.getString();
}

/**
 * Gets the indexes of a ver, an owner and a pet.
 * 
 * Given a vet, an owner and a pet it iterates through the vectors
 * that store them to search for their index.
 * 
 * @param Vet& newVet: The reference of the veterinary.
 * @param Owner& newOwner: The reference of the owner.
 * @param Pet& newPet: The reference of the pet.
 * 
 * @return vector<int> - The indexes asked for. Being the vet index, the owner index and the pet index(in the vector of that owner).
 */
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

/**
 * Show the list of the owners.
 * 
 * Prints all of the owners names. Then asks the user to select
 * one or to go back. If the user wants to select one needs to 
 * type the index of that owner.
 * 
 * @param 
 * 
 * @return
 */
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
    cout<<"\t Type from 0 - "<<owners.size()-1<<" to access that owner's index\n";
    cout<<"\nWhat you want to do? \n";
    int q=ops.getInt(-1, owners.size()-1);
    if(q==-1) return;
    goToOwner(q);
}

/**
 * Shows the owner data and displays a menu.
 * 
 * Prints the owner data. Then displays the menu with the different
 * options that can be done and waits for the user input to know
 * what it needs to do.
 * 
 * @param 
 * 
 * @return
 */
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

/**
 * Show the list of the pets an owner has.
 * 
 * Prints all of the pets names. Then asks the user to select
 * one or to go back. If the user wants to select one needs to 
 * type the index of that pet.
 * 
 * @param int index: The index of the owner.
 * 
 * @return
 */
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
    cout<<"\t Type from 0 - "<<owners[index]->petSize()-1<<" to access that pet's index\n";
    cout<<"\nWhat you want to do? \n";
    int q=ops.getInt(-1, owners[index]->petSize()-1);
    if(q==-1) return;
    goToPet(index, q);
}

/**
 * Shows the pet data and displays a menu.
 * 
 * Prints the pet data. Then displays the menu with the different
 * options that can be done and waits for the user input to know
 * what it needs to do.
 * 
 * @param int ownerIndex: The index of the owner.
 * @param int petIndex: The index of the pet.
 * 
 * @return
 */
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
        cout<<"\t5.- View this pet's records(get their HTML)\n";
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
        if(q<=4 && q>=1){
            services[services.size()-1]->print();
            cout<<"Would you like to generate it's HTML right now? (Y=Yes, N=No) ";
            if(ops.getYesOrNo()) services[services.size()-1]->printHTML();
            waitUser();
        }
    }
}

/**
 * Show the list of the vets.
 * 
 * Prints all of the vets names. Then asks the user to select
 * one, the user will need to type the index of that vet.
 * 
 * @param int index: The index of the veterinary.
 * 
 * @return
 */
int PetVetHealth::showVets(){
    cout<<bfc<<"[[ List of vets ]]"<<nfc<<"\n";
    fore(i,0,vets.size()){
        cout<<"\t"<<i<<".- "<<vets[i]->getLastName()<<" "<<vets[i]->getName()<<": "<<vets[i]->getCollege()<<"\n";
    }
    cout<<"\t Type from 0 - "<<vets.size()-1<<" to access that vets's index\n";
    cout<<"\nWhat vet is doing this service? \n";
    int q=ops.getInt(0, vets.size()-1);
    return q;
}

/**
 * Show the services a pet has.
 * 
 * Prints all of the services a pet has been through. At the and
 * asks to the user what to do. If the user wants to get the html
 * version of a service then it'l be needed that the user types
 * it's index. Otherwhise only type -1 to go back.
 * 
 * @param int index: The index of the owner.
 * 
 * @return
 */
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
        cout<<yfc<<"Entry number: "<<i<<"\n"<<nfc;
        filteredServices[i]->print();
        cout<<"\n";
        if((i+1)<filteredServices.size()) cout<<rfc<<" - - - - - - - \n\n\n"<<nfc;
    }

    cout<<"\t Type \"-1\" to go back\n";
    cout<<"\t Type from 0 - "<<filteredServices.size()-1<<" to get the corresponding html for that entry\n";
    cout<<"What do you want to do?\n";
    int q=ops.getInt(-1,filteredServices.size()-1);
    if(q==-1) return;
    filteredServices[q]->printHTML();
    waitUser();
}

#endif