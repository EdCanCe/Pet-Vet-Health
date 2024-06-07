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
        virtual void printHTML() = 0;
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
        void printHTML();
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

void MedicalCheck::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    vector<int> time=ops.currentTime();
    string hour=date+"-"+to_string(time[0])+"-"+to_string(time[1])+"-"+to_string(time[2]);
    string nameFile="Records/"+hour+"-MedicalCheck-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    output<<"<head>\n";
    output<<"<title>Medical Check</title>\n";
    output<<"<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n";
    output<<"</head>\n";
    output<<"<body><div class=\"MainBody\">\n";
    output<<"<p class=\"date\">"<<dateDay<<"/"<<dateMonth<<"/"<<dateYear<<"</p>\n";
    output<<"<h1>Medical check</h1>\n";
    output<<"<h2>Pet data:</h2>\n";
    output<<"<p class=\"PetData\">Name: "<<patient->getName()<<"</p>\n";
    output<<"<p class=\"PetData\">Breed: "<<patient->getBreed()<<"</p>\n";
    output<<"<p class=\"PetData\">Age: "<<ops.getAgeDifference(patient->getBirth())<<"</p>\n";
    output<<"<p class=\"PetData\">Annotations: "<<patient->getAnnotations()<<"</p>\n";

    output<<"<h2>Description: </h2>\n";
    output<<"<p>"<<description<<"</p>\n";

    output<<"<h2>Diagnosis: </h2>\n";
    output<<"<p>"<<diagnosis<<"</p>\n";

    output<<"<h2>Treatment: </h2>\n";
    output<<"<p>"<<treatment<<"</p>\n";

    output<<"<p class=\"line\"></p>";
    output<<"<p class=\"foot\">"<<medic->getProfessionalLicense()<<" - "<<medic->getLastName()<<"  "<<medic->getName()<<"'s sign</p>\n";
    output<<"<script src=\"script.js\"></script>";
    output<<"</div></body>";
    output.close();

    string command;
    #ifdef _WIN32
    command = "start "+nameFile; // Para Windows
    #elif __APPLE__
    command = "open "+nameFile;  // Para macOS
    #elif __linux__
    command = "xdg-open "+nameFile; // Para Linux
    #endif
    system(command.c_str());

}




class Surgery : public Service{
    private:
        string postSurgeryTreatment;
    public:
        Surgery(Vet&, Owner&, Pet&);
        Surgery(Vet&, Owner&, Pet&, int[], string, string);
        void print();
        void printForDB(vector<int>);
        void printHTML();
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

void Surgery::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    string nameFile="records/"+date+"-Surgery-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    output<<"<h1>Medical check</h1>";

    output.close();

    string command;
    #ifdef _WIN32
    command = "start "+nameFile; // Para Windows
    #elif __APPLE__
    command = "open "+nameFile;  // Para macOS
    #elif __linux__
    command = "xdg-open "+nameFile; // Para Linux
    #endif
    system(command.c_str());
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
        void printHTML();
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

void Grooming::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    string nameFile="records/"+date+"-Grooming-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    output<<"<h1>Medical check</h1>";

    output.close();

    string command;
    #ifdef _WIN32
    command = "start "+nameFile; // Para Windows
    #elif __APPLE__
    command = "open "+nameFile;  // Para macOS
    #elif __linux__
    command = "xdg-open "+nameFile; // Para Linux
    #endif
    system(command.c_str());
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
        void printHTML();
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

void Hotel::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    string nameFile="records/"+date+"-Hotel-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    output<<"<h1>Medical check</h1>";

    output.close();

    string command;
    #ifdef _WIN32
    command = "start "+nameFile; // Para Windows
    #elif __APPLE__
    command = "open "+nameFile;  // Para macOS
    #elif __linux__
    command = "xdg-open "+nameFile; // Para Linux
    #endif
    system(command.c_str());
}

#endif