/*
*
* Pet Vet Health Proyect - Person Class
* A01645576
* 07/06/2024
* This class contains the data of a person. It has the child
* classes Vet and Owner.
*
*/
#ifndef PERSON_H
#define PERSON_H

#include "Pet.h"

//Declaration of person class
class Person{
    //Declaration of protected attributes
    protected:
        string name;
        string lastName;
        string phoneNumber;

    //Declaration of public methods
    public:
        Person();
        Person(string, string, string);
        string getName();
        string getLastName();
        string getPhone();
        virtual void showData()=0; //Abstract methot that will be overwritten
        virtual void printForDB()=0; //Abstract methot that will be overwritten
};


/**
 * It is the constructor of this object.
 *
 * It constructs the object.
 *
 * @param
 * 
 * @return Person object.
 */
Person::Person(){
    cout<<yfc<<"[[ Person CREATION ]]"<<nfc<<"\n";
    cout<<"Last name(s): ";
    lastName=ops.getString();
    cout<<"Name(s): ";
    name=ops.getString();
    cout<<"Phone number: ";
    phoneNumber=ops.getString();
}

/**
 * It is the constructor of this object.
 *
 * Overloads the Person() method. It constructs the object.
 *
 * @param string newName: The name of the person.
 * @param string newLastName: The last name of the person.
 * @param string newPhoneNumber: The phone number the person.
 * 
 * @return Person object.
 */
Person::Person(string newName, string newLastName, string newPhoneNumber){
    name=newName;
    lastName=newLastName;
    phoneNumber=newPhoneNumber;
}

/**
 * Returns the name of the person.
 *
 * @param
 * 
 * @return string - The name of the person.
 */
string Person::getName(){
    return name;
}

/**
 * Returns the last name of the person.
 *
 * @param
 * 
 * @return string - The last name of the person.
 */
string Person::getLastName(){
    return lastName;
}

/**
 * Returns the phone number of the person.
 *
 * @param
 * 
 * @return string - The phone number of the person.
 */
string Person::getPhone(){
    return phoneNumber;
}




//Declaration of Owner class that inherits from Person class
class Owner : public Person{
    //Declaration of private attributes
    private:
        vector<Pet*> pets; //Pointer to pet

    //Declaration of public methods
    public:
        Owner();
        Owner(string, string, string);
        void showPets();
        void addPet(Pet&);
        int petSize();
        Pet& getPet(int);
        vector<Pet*>& getPets();
        void showData();
        void printForDB();
};

/**
 * It is the constructor of this object.
 *
 * Uses the Person() method. It constructs the object.
 *
 * @param
 * 
 * @return Owner object.
 */
Owner::Owner():Person(){}

/**
 * It is the constructor of this object.
 *
 * Overloads the Owner() method. It constructs the object.
 *
 * @param string newName: The name of the owner.
 * @param string newLastName: The last name of the owner.
 * @param string newPhoneNumber: The phone number the owner.
 * 
 * @return Owner object.
 */
Owner::Owner(string newName, string newLastName, string newPhoneNumber):Person(newName, newLastName, newPhoneNumber){}

/**
 * Show the list of the pets an owner has.
 * 
 * Iterates in a loop showing the data of all the pets
 * that owner has.
 * 
 * @param 
 * 
 * @return
 */
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

/**
 * Adds a pet to the owner.
 * 
 * Pushes back to the vector of pointers to Pets another one
 * 
 * @param Pet& newPet: The reference to the pet that will
 * be added to the owner.
 * 
 * @return
 */
void Owner::addPet(Pet& newPet){
    pets.push_back(&newPet);
}

/**
 * Gets the size of the pets the owner has.
 * 
 * It does this by checking the value using pets.size() .
 * 
 * @param 
 * 
 * @return int - The number of pets the owner has.
 */
int Owner::petSize(){
    return pets.size();
}

/**
 * Gets a certain pet.
 * 
 * By giving the index of the pet. The reference of that
 * pet is returned.
 * 
 * @param int index: The index of the wanted pet.
 * 
 * @return Pet& - The reference to that pet.
 */
Pet& Owner::getPet(int index){
    return *pets[index];
}

/**
 * Gets all of the pets of an owner.
 * 
 * @param 
 * 
 * @return vector<Pet*>& - The reference of the vector that
 * contains the pointers to the pets of an owner.
 */
vector<Pet*>& Owner::getPets(){
    return pets;
}

/**
 * Prints the data of an owner.
 * 
 * @param 
 * 
 * @return
 */
void Owner::showData(){
    cout<<gfc<<lastName<<" "<<name<<nfc<<":\n";
    cout<<"Phone: "<<phoneNumber<<"\n";
}

/**
 * Prints the data of an owner.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param 
 * 
 * @return
 */
void Owner::printForDB(){
    cout<<lastName<<"\n"<<name<<"\n"<<phoneNumber<<"\n";
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
    cout<<gfc<<lastName<<" "<<name<<nfc<<":\n";
    cout<<"Phone: "<<phoneNumber<<"\n";
    cout<<college<<": "<<professionalLicense<<"\n";
}

void Vet::printForDB(){
    cout<<lastName<<"\n"<<name<<"\n"<<phoneNumber<<"\n"<<professionalLicense<<"\n"<<college<<"\n";
}

#endif