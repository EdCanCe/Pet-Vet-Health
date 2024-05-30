#ifndef PET_H
#define PET_H

#include "Operations.h"

class Pet{
    private:
        string name;
        char sex;
        int birthDay;
        int birthMonth;
        int birthYear;
        string breed;
        string annotations="-"; // Any allergies, etc.
        vector<int> getBirth();
        int cage=0; // In case the pet stays in the veterinary, cage assigns the cage where the pet was put in.
    public:
        Pet();
        Pet(string, char, int, int, int, string, string, int);
        Pet(string, char, int, int, int, string, string);
        Pet(string, char, int, int, int, string);
        void setAnnotations(string);
        void setCage(int);
        string getName(); //Used when owner selects which pet is being treated
        string getAnnotations();
        int getCage();
        void showData();
        void printForDB();
};

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
    cout<<"Birth of the pet:\n\tDay(0-31): ";
    birthDay=ops.getInt(0, 31);
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

Pet::Pet(string newName, char newSex, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed, string newAnnotations){
    name=newName;
    sex=newSex;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
    annotations=newAnnotations;
}

Pet::Pet(string newName, char newSex, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed){
    name=newName;
    sex=newSex;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
}

void Pet::setAnnotations(string newAnnotations){
    annotations=newAnnotations;
}

void Pet::setCage(int index){
    cage=index;
}

string Pet::getName(){
    return name;
}

vector<int> Pet::getBirth(){
    return {birthDay, birthMonth, birthYear};
}

string Pet::getAnnotations(){
    return annotations;
}

int Pet::getCage(){
    return cage;
}

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

void Pet::printForDB(){
    cout<<name<<"\n"<<sex<<"\n"<<birthDay<<"\n"<<birthMonth<<"\n"<<birthYear<<"\n"<<breed<<"\n"<<annotations<<"\n"<<cage<<"\n";
}

#endif