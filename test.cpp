#include "PetVetHealth.h"
using namespace std;

int main(){

    //Primera parte - Funcionamiento básico de clases
    vector<Vet*> Medicos;
    Medicos.push_back(new Vet("Juan", "Perez Perez", "442 111 1111", "1111111111", "ITESM"));
    Medicos.push_back(new Vet("Maria Elena", "Martinez Martinez", "442 222 2222", "22222222222", "UAQ"));
    cout<<rfc<<"Veterinarios:\n"<<nfc;
    fore(i,0,Medicos.size()){
        Medicos[i]->showData();
        cout<<"\n";
    }

    vector<Owner*> Duenos;
    Duenos.push_back(new Owner("Edmundo", "Canedo Cervantes", "443 423 7305"));
    Duenos.push_back(new Owner("Jose", "Garcia Garcia", "442 333 3333"));
    cout<<rfc<<"Duenos:\n"<<nfc;
    fore(i,0,Duenos.size()){
        Duenos[i]->showData();
        cout<<"\n";
    }

    Duenos[0]->addPet(*(new Pet("Mike", 'M', 1, 1, 110, "Siamese Cat"))); //El año 110 corresponde a 2010
    Duenos[0]->addPet(*(new Pet("Firulais", 'F', 2, 2, 105, "Street Dog", "Misses a leg"))); //El año 105 corresponde a 2005
    Duenos[0]->addPet(*(new Pet("Mipo", 'M', 12, 24, 122, "Hamster"))); //El año 123 corresponde a 2022

    cout<<rfc<<"\nMascotas del primer dueno:\n"<<nfc;
    fore(i,0,Duenos[0]->petSize()){
        Duenos[0]->getPet(i).showData();
    }

    Duenos[0]->getPet(2).setAnnotations("If it cannot be found search in the sawdust, he likes to hide in there");
    cout<<rfc<<"\n\nMascotas del primer dueno despues de modificacion:\n"<<nfc;
    fore(i,0,Duenos[0]->petSize()){
        Duenos[0]->getPet(i).showData();
    }

    Duenos[1]->addPet(*(new Pet("Michis", 'F', 6, 6, 116, "Street Cat"))); //El año 116 corresponde a 2016.
    cout<<rfc<<"\n\nMascotas del segundo dueno:\n"<<nfc;
    fore(i,0,Duenos[1]->petSize()){
        Duenos[1]->getPet(i).showData();
    }

    vector<Service*> Servicios;
    int a[3]={12, 12, 112};
    Servicios.push_back(new MedicalCheck(*Medicos[0], *Duenos[0], Duenos[0]->getPet(0), a, "Presented itchyness", "Has lice", "Bath once a day for a week"));
    Servicios.push_back(new Surgery(*Medicos[1], *Duenos[1], Duenos[1]->getPet(0), a, "Sterilization", "Cannot use the litter box"));

    cout<<rfc<<"\n\nImpresion de servicios:\n"<<nfc;
    fore(i,0,Servicios.size()){
        cout<<bfc<<"Servicio no: "<<i+1<<"\n"<<nfc;
        Servicios[i]->print();
        cout<<"\n";
    }

    //Liberar memoria
    for(Service* i:Servicios){
        delete i;
    }
    for(Owner* i:Duenos){
        for(Pet* j:i->getPets()){
            delete j;
        }
        delete i;
    }
    for(Vet* i:Medicos){
        delete i;
    }

}