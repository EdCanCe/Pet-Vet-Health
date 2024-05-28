#ifndef PERSON_H
#define PERSON_H

#include "Pet.h"

class Person{
    protected:
        string name;
        string lastName;
        string phoneNumber;
    public:
        Person();
        Person(string, string, string);
        void setNumber(string);
        string getName();
        string getPhone();
        void showData();
        void printForDB();
};

Person::Person(){
    cout<<yfc<<"[[ Person CREATION ]]"<<nfc<<"\n";
    cout<<"Last name(s): ";
    lastName=ops.getString();
    cout<<"Name(s): ";
    name=ops.getString();
    cout<<"Phone number: ";
    phoneNumber=ops.getString();
}

Person::Person(string newName, string newLastName, string newPhoneNumber){
    name=newName;
    lastName=newLastName;
    phoneNumber=newPhoneNumber;
}

void Person::setNumber(string newPhoneNumber){
    phoneNumber=newPhoneNumber;
}

string Person::getName(){
    return name;
}

string Person::getPhone(){
    return phoneNumber;
}

void Person::showData(){
    cout<<gfc<<lastName<<" "<<name<<nfc<<":\n";
    cout<<"Phone: "<<phoneNumber<<"\n";
}

void Person::printForDB(){
    cout<<lastName<<"\n"<<name<<"\n"<<phoneNumber<<"\n";
}




class Owner : public Person{
    private:
        vector<Pet*> pets;
    public:
        Owner();
        Owner(string, string, string);
        void showPets();
        void addPet(Pet&);
        int petSize();
        Pet& getPet(int);
        vector<Pet*>& getPets();
};

Owner::Owner():Person(){
    cout<<"\n";
}

Owner::Owner(string newName, string newLastName, string newPhoneNumber):Person(newName, newLastName, newPhoneNumber){}

void Owner::showPets(){
    if(pets.size()>0){
        fore(i,0,pets.size()){
            cout<<i<<".- ";
            pets[i]->showData();
            cout<<"\n";
        }
    }else{
        cout<<rfc<<"There are no pets\n\n"<<nfc;
    }
}

void Owner::addPet(Pet& newPet){
    pets.push_back(&newPet);
}

int Owner::petSize(){
    return pets.size();
}

Pet& Owner::getPet(int index){
    return *pets[index];
}

vector<Pet*>& Owner::getPets(){
    return pets;
}




class Vet : public Person{
    private:
        string professionalLicense;
        string college;
    public:
        Vet();
        Vet(string, string, string, string, string);
        string getProfessionalLicense();
        string getCollege();
        void showData();
        void printForDB();
};

Vet::Vet():Person(){
    cout<<"Professional license: ";
    professionalLicense=ops.getString();
    cout<<"College: ";
    college=ops.getString();
    cout<<"\n";
}

Vet::Vet(string newName, string newLastName, string newPhoneNumber, string newProfessionalLicense, string newCollege):Person(newName, newLastName, newPhoneNumber){
    professionalLicense=newProfessionalLicense;
    college=newCollege;
}

string Vet::getProfessionalLicense(){
    return professionalLicense;
}

string Vet::getCollege(){
    return college;
}

void Vet::showData(){
    cout<<lastName<<" "<<name<<" - "<<college<<": "<<professionalLicense<<"\n";
    cout<<"Phone: "<<phoneNumber<<"\n";
}

void Vet::printForDB(){
    cout<<lastName<<"\n"<<name<<"\n"<<phoneNumber<<"\n"<<professionalLicense<<"\n"<<college<<"\n";
}

#endif