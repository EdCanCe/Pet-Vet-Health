#ifndef SERVICE_H
#define SERVICE_H

#include "Person.h"

class Service{
    protected:
        Vet *medic;
        Owner *customer;
        Pet *patient;
        int dateDay;
        int dateMonth;
        int dateYear;
        string description;
    public:
        Service(Vet&, Owner&, Pet&);
        Service(Vet&, Owner&, Pet&, int[], string);
        virtual void print() = 0;
        Vet& getVet();
        Pet& getPet();
        Owner& getOwner();
        void startingPrint(string);
        void endingPrint();
        virtual void printForDB(vector<int>) = 0;
        void startingPrintForDB(vector<int>, char);
};

Service::Service(Vet& newMedic, Owner& newOwner, Pet& newPet){
    vector<int> dates=ops.currentDate();
    dateDay=dates[0];
    dateMonth=dates[1];
    dateYear=dates[2];
    medic=&newMedic;
    customer=&newOwner;
    patient=&newPet;
}

Service::Service(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription){
    dateDay=dates[0];
    dateMonth=dates[1];
    dateYear=dates[2];
    medic=&newMedic;
    customer=&newOwner;
    patient=&newPet;
    description=newDescription;
}

Vet& Service::getVet(){
    return *medic;
}

Owner& Service::getOwner(){
    return *customer;
}

Pet& Service::getPet(){
    return *patient;
}

void Service::startingPrint(string title){
    cout<<"Owner: ";
    customer->showData();
    cout<<"\n";
    cout<<gfc<<title<<dateDay<<"/"<<dateMonth<<"/"<<dateYear-100<<nfc<<"\n\n";
    cout<<cfc<<"Pet: "<<nfc;
    patient->showData();
    cout<<"\n";
}

void Service::endingPrint(){
    cout<<"Veterinary in charge: ";
    medic->showData();
    cout<<"\n";
}
/*
void Service::print(){
    cout<<"It's empty\n\n";
}

void Service::printForDB(vector<int> index){
    cout<<"It's empty\n\n";
}
*/
void Service::startingPrintForDB(vector<int> index, char c){
    cout<<c<<"\n"<<index[0]<<"\n"<<index[1]<<"\n"<<index[2]<<"\n";
    cout<<dateDay<<"\n"<<dateMonth<<"\n"<<dateYear<<"\n"<<description<<"\n";
}




class MedicalCheck : public Service{
    private:
        string diagnosis;
        string treatment;
    public:
        MedicalCheck(Vet&, Owner&, Pet&);
        MedicalCheck(Vet&, Owner&, Pet&, int[], string, string, string);
        void print();
        void printForDB(vector<int>);
};

MedicalCheck::MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ MEDICAL CHECK CREATION ]]"<<nfc<<"\n\n";
    cout<<"Description of the case: ";
    description=ops.getString();
    cout<<"Diagnosis of the case: ";
    diagnosis=ops.getString();
    cout<<"Given treatment: ";
    treatment=ops.getString();
    cout<<"\n";
}

MedicalCheck::MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription, string newDiagnosis, string newTreatment):Service(newMedic, newOwner, newPet, dates,newDescription){
    diagnosis=newDiagnosis;
    treatment=newTreatment;
}

void MedicalCheck::print(){
    startingPrint("Medical check on ");
    cout<<"Description:\n"<<description<<"\n\nDiagnosis:\n"<<diagnosis<<"\n\nTreatment:\n"<<treatment<<"\n\n";
    endingPrint();
}

void MedicalCheck::printForDB(vector<int> index){
    startingPrintForDB(index, 'M');
    cout<<diagnosis<<"\n"<<treatment<<"\n";
}




class Surgery : public Service{
    private:
        string postSurgeryTreatment;
    public:
        Surgery(Vet&, Owner&, Pet&);
        Surgery(Vet&, Owner&, Pet&, int[], string, string);
        void print();
        void printForDB(vector<int>);
};

Surgery::Surgery(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ SURGERY ENTRY CREATION ]]"<<nfc<<"\n";
    cout<<"Brief description of the surgery: ";
    description=ops.getString();
    cout<<"Post surgery treatment: ";
    postSurgeryTreatment=ops.getString();
    cout<<"\n";
}

Surgery::Surgery(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription, string newPostSurgeryTreatment):Service(newMedic, newOwner, newPet, dates, newDescription){
    postSurgeryTreatment=newPostSurgeryTreatment;
}

void Surgery::print(){
    startingPrint(description+" on ");
    cout<<"Post surgery treatment:\n"<<postSurgeryTreatment<<"\n\n";
    endingPrint();
}

void Surgery::printForDB(vector<int> index){
    startingPrintForDB(index, 'S');
    cout<<postSurgeryTreatment<<"\n";
}




class Grooming : public Service{
    private:
        string materialUsed;
        string initialState;
        string finalState;
    public:
        Grooming(Vet&, Owner&, Pet&);
        Grooming(Vet&, Owner&, Pet&, int[], string, string, string, string);
        void print();
        void printForDB(vector<int> index);
};

Grooming::Grooming(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[  GROOMING SESSION ENTRY ]]"<<nfc<<"\n";
    cout<<"Description of the grooming order: ";
    description=ops.getString();
    cout<<"Material used in the session: ";
    materialUsed=ops.getString();
    cout<<"Description on pet's appearance before session: ";
    initialState=ops.getString();
    cout<<"Description on pet's appearance after session: ";
    finalState=ops.getString();
    cout<<"\n";
}

Grooming::Grooming(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription, string newMaterialUsed, string newInitialState, string newFinalState):Service(newMedic, newOwner, newPet, dates, newDescription){
    materialUsed=newMaterialUsed;
    initialState=newInitialState;
    finalState=newFinalState;
}

void Grooming::print(){
    startingPrint("Grooming on ");
    cout<<"Description of grooming order:\n"<<description<<"\n\nMaterials used during the session:\n"<<materialUsed<<"\n\n"<<"Appearance before session:\n"<<initialState<<"\n\nAppearance after session:\n"<<finalState<<"\n\n";
    endingPrint();
}

void Grooming::printForDB(vector<int> index){
    startingPrintForDB(index, 'G');
    cout<<materialUsed<<"\n"<<initialState<<"\n"<<finalState<<"\n";
}




class Hotel : public Service{
    private:
        int startDateDay;
        int startDateMonth;
        int startDateYear;
        int endDateDay;
        int endDateMonth;
        int endDateYear;
    public:
        Hotel(Vet&, Owner&, Pet&);
        Hotel(Vet&, Owner&, Pet&, int[], string, int[], int[]);
        Hotel(Vet&, Owner&, Pet&, int[], string, int[], int[], int);
        void print();
        void printForDB(vector<int>);
};

Hotel::Hotel(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ HOTEL ENTRY CREATION ]]"<<nfc<<"\n";
    cout<<"Description of the stay: ";
    description=ops.getString();
    cout<<"Start of the period:\n\tDay(0-31): ";
    startDateDay=ops.getInt(0, 31);
    cout<<"\tMonth(1-12): ";
    startDateMonth=ops.getInt(1,12);
    cout<<"\tYear(19XX-20XX): ";
    startDateYear=ops.getInt(1900, 2099);
    startDateYear-=1900;
    cout<<"End of the period:\n\tDay(0-31): ";
    endDateDay=ops.getInt(0,31);
    cout<<"\tMonth(1-12): ";
    endDateMonth=ops.getInt(1,12);
    cout<<"\tYear(19XX-20XX): ";
    endDateYear=ops.getInt(1900,2099);
    endDateYear-=1900;
    vector<int> currentDate=ops.currentDate();
    if(startDateDay==currentDate[0] && startDateMonth==currentDate[1] && startDateYear==currentDate[2]){
        int index;
        cout<<"Number of cage it's going to be put in: ";
        index=ops.getInt();
        patient->setCage(index);
    }
    cout<<"\n";
}

Hotel::Hotel(Vet& newMedic, Owner& newOwner, Pet& newPet, int orderDate[], string description, int startDate[], int endDate[]):Service(newMedic, newOwner, newPet, orderDate, description){
    startDateDay=startDate[0];
    startDateMonth=startDate[1];
    startDateYear=startDate[2];
    endDateDay=endDate[0];
    endDateMonth=endDate[1];
    endDateYear=endDate[2];
}

Hotel::Hotel(Vet& newMedic, Owner& newOwner, Pet& newPet, int orderDate[], string description, int startDate[], int endDate[], int newCage):Service(newMedic, newOwner, newPet, orderDate, description){
    startDateDay=startDate[0];
    startDateMonth=startDate[1];
    startDateYear=startDate[2];
    endDateDay=endDate[0];
    endDateMonth=endDate[1];
    endDateYear=endDate[2];
    patient->setCage(newCage);
}

void Hotel::print(){
    startingPrint("Hotel entry registered ");
    cout<<"Starting date: "<<startDateDay<<"/"<<startDateMonth<<"/"<<startDateYear+1900<<"\n\nEnding date: "<<endDateDay<<"/"<<endDateMonth<<"/"<<endDateYear+1900<<"\n\n";
}

void Hotel::printForDB(vector<int> index){
    startingPrintForDB(index, 'H');
    cout<<startDateDay<<"\n"<<startDateMonth<<"\n"<<startDateYear<<"\n";
    cout<<endDateDay<<"\n"<<endDateMonth<<"\n"<<endDateYear<<"\n";  
}

#endif