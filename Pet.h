/*
*
* Pet Vet Health Proyect - Pet Class
* A01645576
* 07/06/2024
* This class stores the data of a pet. It's used
* in the services and person class.
*
*/
#ifndef PET_H
#define PET_H

#include "Operations.h"

//Declaration of person class
class Pet{
    //Declaration of private attributes
    private:
        string name;
        char sex;
        int birthDay;
        int birthMonth;
        int birthYear;
        string breed;
        string annotations="-"; // Any allergies, etc.
        int cage=0; // In case the pet stays in the veterinary, cage assigns the cage where the pet was put in.
    
    //Declaration of public methods
    public:
        Pet();
        Pet(string, char, int, int, int, string, string, int);
        Pet(string, char, int, int, int, string, string);
        Pet(string, char, int, int, int, string);
        vector<int> getBirth();
        void setCage(int);
        string getName();
        string getBreed();
        string getAnnotations();
        int getCage();
        void showData();
        void printForDB();
};

/**
 * It is the constructor of this object.
 *
 * It constructs the object.
 *
 * @param
 * 
 * @return Pet object.
 */
Pet::Pet(){
    cout<<yfc<<"[[ PET CREATION ]]"<<nfc<<"\n";
    cout<<"Name of the pet: ";
    name=ops.getString();
    cout<<"Sex of the pet(M=Male, F=Female): ";
    sex=ops.getChar();
    while(!(sex=='M' || sex=='F')){
        cout<<"The given sex doesn't exist, type again: ";
        sex=ops.getChar();
    }
    cout<<"Birth of the pet:\n\tDay(1-31): ";
    birthDay=ops.getInt(1, 31);
    cout<<"\tMonth(1-12): ";
    birthMonth=ops.getInt(1,12);
    cout<<"\tYear(19XX-20XX): ";
    birthYear=ops.getInt(1900, 2099);
    birthYear-=1900;
    cout<<"Breed of the pet: ";
    breed=ops.getString();
    cout<<"Are there any special annotations?\nex(Allergies, Misses an extremity, etc.) (Y=Yes, N=No): ";
    if(ops.getYesOrNo()){
        cout<<"Enter the annotations: ";
        annotations=ops.getString();
    }
    cout<<"\n";
}

/**
 * It is the constructor of this object.
 *
 * Overloads the Pet() method. It constructs the object.
 *
 * @param string newName: The name of the pet.
 * @param char newSex: The sex of the pet (M for male, F for female)
 * @param int newBirthDay: The day of birth of the pet.
 * @param int newBirthMonth: The day of birth of the pet.
 * @param int newBirthYear: The month of birth of the pet. It's stored
 * in a way 0 means 1900. Ex(5 = 1995, 15 = 2005, etc.) Goes from 0 - *
 * @param string newBreed: The breed of the pet.
 * @param string newAnnotations: Special annotations the pet could
 * have. Ex(Allergies, special conditions, unique features)
 * @param string newCage: The cage the pet is in. It's 0 if it's in
 * none, otherwise is in that number. Used only if the pet is staying
 * in a hotel service.
 * 
 * @return Pet object.
 */
Pet::Pet(string newName, char newSex, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed, string newAnnotations, int newCage){
    name=newName;
    sex=newSex;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
    annotations=newAnnotations;
    cage=newCage;
}

/**
 * It is the constructor of this object.
 *
 * Overloads the Pet() method. It constructs the object.
 *
 * @param string newName: The name of the pet.
 * @param char newSex: The sex of the pet (M for male, F for female)
 * @param int newBirthDay: The day of birth of the pet.
 * @param int newBirthMonth: The day of birth of the pet.
 * @param int newBirthYear: The month of birth of the pet. It's stored
 * in a way 0 means 1900. Ex(5 = 1995, 15 = 2005, etc.) Goes from 0 - *
 * @param string newBreed: The breed of the pet.
 * @param string newAnnotations: Special annotations the pet could
 * have. Ex(Allergies, special conditions, unique features)
 * 
 * @return Pet object.
 */
Pet::Pet(string newName, char newSex, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed, string newAnnotations){
    name=newName;
    sex=newSex;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
    annotations=newAnnotations;
}

/**
 * It is the constructor of this object.
 *
 * Overloads the Pet() method. It constructs the object.
 *
 * @param string newName: The name of the pet.
 * @param char newSex: The sex of the pet (M for male, F for female)
 * @param int newBirthDay: The day of birth of the pet.
 * @param int newBirthMonth: The day of birth of the pet.
 * @param int newBirthYear: The month of birth of the pet. It's stored
 * in a way 0 means 1900. Ex(5 = 1995, 15 = 2005, etc.) Goes from 0 - *
 * @param string newBreed: The breed of the pet.
 * 
 * @return Pet object.
 */
Pet::Pet(string newName, char newSex, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed){
    name=newName;
    sex=newSex;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
}

/**
 * Sets the cage in which the pet is in.
 * 
 * When the pet is in a hotel service it's placed on a cage.
 * 
 * @param int index: The number of cage it's going to be put in.
 * 
 * @return
 */
void Pet::setCage(int index){
    cage=index;
}

/**
 * Gets the name of the pet.
 * 
 * @param 
 * 
 * @return string - The name of the pet.
 */
string Pet::getName(){
    return name;
}

/**
 * Gets the breed of the pet.
 * 
 * @param 
 * 
 * @return string - The breed of the pet.
 */
string Pet::getBreed(){
    return breed;
}

/**
 * Gets the birth of the pet.
 * 
 * @param 
 * 
 * @return vector<int> - The birth of the pet in a vector. The vector
 * stores the data in this order: day, month, year.
 */
vector<int> Pet::getBirth(){
    return {birthDay, birthMonth, birthYear};
}

/**
 * Gets the annotations of the pet.
 * 
 * @param 
 * 
 * @return string - The annotations of the pet.
 */
string Pet::getAnnotations(){
    return annotations;
}

/**
 * Gets the cage the pet is in.
 * 
 * @param 
 * 
 * @return string - The cage the pet is in.
 */
int Pet::getCage(){
    return cage;
}

/**
 * Prints the data of a pet.
 * 
 * @param 
 * 
 * @return
 */
void Pet::showData(){
    cout<<gfc<<name<<nfc<<": "<<breed<<" - ";
    cout<<ops.getAgeDifference(getBirth())<<" years old\n";
    cout<<"Sex: "<<(sex == 'M' ? "Male" : "Female")<<"\n";
    if(annotations!="-"){
        cout<<"Special annotations:\n"<<annotations<<"\n";
    }
    if(cage!=0){
        cout<<"Cage: "<<cage<<"\n";
    }
}

/**
 * Prints the data of a pet.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param 
 * 
 * @return
 */
void Pet::printForDB(){
    cout<<name<<"\n"<<sex<<"\n"<<birthDay<<"\n"<<birthMonth<<"\n"<<birthYear<<"\n"<<breed<<"\n"<<annotations<<"\n"<<cage<<"\n";
}

#endif