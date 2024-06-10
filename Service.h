/*
*
* Pet Vet Health Proyect - Service Class
* A01645576
* This class represents the different services that can
* be done. The class service has 4 childs classes:
* MedicalCheck, Surgery, Grooming and hotel.  
*
*/
#ifndef SERVICE_H
#define SERVICE_H

#include "Person.h"

//Declaration of Service class
class Service{
    //Declaration of the protected attributes
    protected:
        Vet *medic;
        Owner *customer;
        Pet *patient;
        int dateDay;
        int dateMonth;
        int dateYear;
        string description;

    //Declaration of the public methods
    public:
        Service(Vet&, Owner&, Pet&);
        Service(Vet&, Owner&, Pet&, int[], string);
        virtual void print() = 0; //Abstract method that will be overwritten
        Vet& getVet();
        Pet& getPet();
        Owner& getOwner();
        void startingPrint(string);
        void endingPrint();
        virtual void printForDB(vector<int>) = 0; //Abstract method that will be overwritten
        void startingPrintForDB(vector<int>, char);
        virtual void printHTML() = 0; //Abstract method that will be overwritten
        void startingHTML(ofstream&, string);
        void endingHTML(ofstream&, string);
};

/**
 * It is the constructor of this object.
 *
 * It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * 
 * @return Service object.
 */
Service::Service(Vet& newMedic, Owner& newOwner, Pet& newPet){
    vector<int> dates=ops.currentDate();
    dateDay=dates[0];
    dateMonth=dates[1];
    dateYear=dates[2];
    medic=&newMedic;
    customer=&newOwner;
    patient=&newPet;
}

/**
 * It is the constructor of this object.
 *
 * It overloads Service(Vet& newMedic, Owner& newOwner, Pet& newPet). It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * @param Int dates[]: The array that stores the date in which the service
 * was done. The array has the day, month and year in that order.
 * @param string newDescription: The description of the service.
 * 
 * @return Service object.
 */
Service::Service(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription){
    dateDay=dates[0];
    dateMonth=dates[1];
    dateYear=dates[2];
    medic=&newMedic;
    customer=&newOwner;
    patient=&newPet;
    description=newDescription;
}

/**
 * Returns the veterinary that did the service.
 *
 * @param
 * 
 * @return Vet& - The reference of the veterinary.
 */
Vet& Service::getVet(){
    return *medic;
}

/**
 * Returns the owner of the pet.
 *
 * @param
 * 
 * @return Owner& - The reference of the pet.
 */
Owner& Service::getOwner(){
    return *customer;
}

/**
 * Returns the pet that was in the service.
 *
 * @param
 * 
 * @return Pet& - The reference of the pet.
 */
Pet& Service::getPet(){
    return *patient;
}

/**
 * Prints the initial data of a service.
 * 
 * @param string title: The title of the service.
 * 
 * @return
 */
void Service::startingPrint(string title){
    cout<<"Owner: ";
    customer->showData();
    cout<<"\n";
    cout<<gfc<<title<<dateDay<<"/"<<dateMonth<<"/"<<dateYear-100<<nfc<<"\n\n";
    cout<<cfc<<"Pet: "<<nfc;
    patient->showData();
    cout<<"\n";
}

/**
 * Prints the ending data of a service.
 * 
 * @param
 * 
 * @return
 */
void Service::endingPrint(){
    cout<<"Veterinary in charge: ";
    medic->showData();
    cout<<"\n";
}

/**
 * Prints the initial data of a service.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param vector<int> index: The index containing the indexes of the
 * veterinary, owner and pet(in the vector that has the pets in an owner).
 * @param char c: The type of service it is(M for Medical check, S for
 * surgery, G for grooming and H for hotel).
 * 
 * @return
 */
void Service::startingPrintForDB(vector<int> index, char c){
    cout<<c<<"\n"<<index[0]<<"\n"<<index[1]<<"\n"<<index[2]<<"\n";
    cout<<dateDay<<"\n"<<dateMonth<<"\n"<<dateYear<<"\n"<<description<<"\n";
}

/**
 * Prints the initial data of a service.
 * 
 * It prints it in a way that can be interpreted as HTML.
 * 
 * @param ofstream& output: The reference to the object that references
 * the output file.
 * @param string serviceName: The name of the service(Medical check,
 * Surgery, Grooming or Hotel).
 * 
 * @return
 */
void Service::startingHTML(ofstream& output, string serviceName){
    output<<"<head>\n";
    output<<"<title>"<<serviceName<<"</title>\n";
    output<<"<link rel=\"stylesheet\" type=\"text/css\" href=\"style.css\">\n";
    output<<"</head>\n";
    output<<"<body><div class=\"MainBody\">\n";
    output<<"<p class=\"date\">"<<dateDay<<"/"<<dateMonth<<"/"<<dateYear+1900<<"</p>\n";
    output<<"<h1>"<<serviceName<<"</h1>\n";
    output<<"<div class=\"MainData\">\n";
    output<<"<div class=\"PetData\">\n";
    output<<"<h2>Pet data:</h2>\n";
    output<<"<p>Name: "<<patient->getName()<<"</p>\n";
    output<<"<p>Breed: "<<patient->getBreed()<<"</p>\n";
    output<<"<p>Age: "<<ops.getAgeDifference(patient->getBirth())<<"</p>\n";
    output<<"</div>\n";
    output<<"<div class=\"OwnerData\">\n";
    output<<"<h2>Owner data:</h2>\n";
    output<<"<p>Name: "<<customer->getName()<<"</p>\n";
    output<<"<p>Last name: "<<customer->getLastName()<<"</p>\n";
    output<<"<p>Phone number: "<<customer->getPhone()<<"</p>\n";
    output<<"</div></div>";
    output<<"<p>Annotations: "<<patient->getAnnotations()<<"</p>\n";
}

/**
 * Prints the ending data of a service.
 * 
 * It prints it in a way that can be interpreted as HTML.
 * 
 * @param ofstream& output: The reference to the object that references
 * the output file.
 * @param string nameFile: The name of the file in which it's going to
 * be written.
 * 
 * @return
 */
void Service::endingHTML(ofstream& output, string nameFile){
    output<<"<p class=\"line\"></p>";
    output<<"<p class=\"foot\">"<<medic->getProfessionalLicense()<<" - "<<medic->getLastName()<<"  "<<medic->getName()<<"'s sign<br>Phone number: "<<medic->getPhone()<<"<br>College: "<<medic->getCollege()<<"</p>\n";
    output<<"<script src=\"script.js\"></script>";
    output<<"</div></body>";
    output.close();

    string command;
    #ifdef _WIN32
    command = "start "+nameFile; //for  Windows
    #elif __APPLE__
    command = "open "+nameFile;  //for  macOS
    #elif __linux__
    command = "xdg-open "+nameFile; //for  Linux
    #endif
    system(command.c_str());
}




//Declaration of MedicalCheck class that inherits from Service class
class MedicalCheck : public Service{
    //Declaration of private attributes
    private:
        string diagnosis;
        string treatment;

    //Declaration of public methods
    public:
        MedicalCheck(Vet&, Owner&, Pet&);
        MedicalCheck(Vet&, Owner&, Pet&, int[], string, string, string);
        void print();
        void printForDB(vector<int>);
        void printHTML();
};

/**
 * It is the constructor of this object.
 *
 * Uses Service() method. It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * 
 * @return MedicalCheck object.
 */
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

/**
 * It is the constructor of this object.
 *
 * It overloads MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet). It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * @param Int dates[]: The array that stores the date in which the service
 * was done. The array has the day, month and year in that order.
 * @param string newDescription: The description of the pets status.
 * @param string newDiagnosis: The diagnosis thought.
 * @param string newTreatment: The treatment given.
 * 
 * @return MedicalCheck object.
 */
MedicalCheck::MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription, string newDiagnosis, string newTreatment):Service(newMedic, newOwner, newPet, dates,newDescription){
    diagnosis=newDiagnosis;
    treatment=newTreatment;
}

/**
 * Prints the data of the medical check.
 * 
 * @param 
 * 
 * @return
 */
void MedicalCheck::print(){
    startingPrint("Medical check on ");
    cout<<"Description:\n"<<description<<"\n\nDiagnosis:\n"<<diagnosis<<"\n\nTreatment:\n"<<treatment<<"\n\n";
    endingPrint();
}

/**
 * Prints the data of the medical check.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param vector<int> index: The index containing the indexes of the
 * veterinary, owner and pet(in the vector that has the pets in an owner).
 * 
 * @return
 */
void MedicalCheck::printForDB(vector<int> index){
    startingPrintForDB(index, 'M');
    cout<<diagnosis<<"\n"<<treatment<<"\n";
}

/**
 * Prints the data of the medical check.
 * 
 * It prints it in a way that can be interpreted as HTML.
 * 
 * @param
 * 
 * @return
 */
void MedicalCheck::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    vector<int> time=ops.currentTime();
    string hour=date+"-"+to_string(time[0])+"-"+to_string(time[1])+"-"+to_string(time[2]);
    string nameFile="Records/"+hour+"-MedicalCheck-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    startingHTML(output, "Medical check");

    output<<"<h2>Description of the patient's case: </h2>\n";
    output<<"<p>"<<description<<"</p>\n";

    output<<"<h2>Diagnosis: </h2>\n";
    output<<"<p>"<<diagnosis<<"</p>\n";

    output<<"<h2>Treatment: </h2>\n";
    output<<"<p>"<<treatment<<"</p>\n";

    endingHTML(output, nameFile);
}



//Declaration of Surgery class that inherits from Service class
class Surgery : public Service{
    //Declaration of private attributes
    private:
        string postSurgeryTreatment;

    //Declaration of public methods
    public:
        Surgery(Vet&, Owner&, Pet&);
        Surgery(Vet&, Owner&, Pet&, int[], string, string);
        void print();
        void printForDB(vector<int>);
        void printHTML();
};

/**
 * It is the constructor of this object.
 *
 * Uses Service() method. It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * 
 * @return Surgery object.
 */
Surgery::Surgery(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ SURGERY ENTRY CREATION ]]"<<nfc<<"\n";
    cout<<"Brief description of the surgery: ";
    description=ops.getString();
    cout<<"Post surgery treatment: ";
    postSurgeryTreatment=ops.getString();
    cout<<"\n";
}

/**
 * It is the constructor of this object.
 *
 * It overloads MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet). It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * @param Int dates[]: The array that stores the date in which the service
 * was done. The array has the day, month and year in that order.
 * @param string newDescription: The description of the surgery.
 * @param string newPostSurgeryTreatment: The treatment given after the surgery.
 * 
 * @return Surgery object.
 */
Surgery::Surgery(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription, string newPostSurgeryTreatment):Service(newMedic, newOwner, newPet, dates, newDescription){
    postSurgeryTreatment=newPostSurgeryTreatment;
}

/**
 * Prints the data of the surgery.
 * 
 * @param 
 * 
 * @return
 */
void Surgery::print(){
    startingPrint(description+" on ");
    cout<<"Post surgery treatment:\n"<<postSurgeryTreatment<<"\n\n";
    endingPrint();
}

/**
 * Prints the data of the surgery.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param vector<int> index: The index containing the indexes of the
 * veterinary, owner and pet(in the vector that has the pets in an owner).
 * 
 * @return
 */
void Surgery::printForDB(vector<int> index){
    startingPrintForDB(index, 'S');
    cout<<postSurgeryTreatment<<"\n";
}

/**
 * Prints the data of the surgery.
 * 
 * It prints it in a way that can be interpreted as HTML.
 * 
 * @param
 * 
 * @return
 */
void Surgery::printHTML(){ 
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    vector<int> time=ops.currentTime();
    string hour=date+"-"+to_string(time[0])+"-"+to_string(time[1])+"-"+to_string(time[2]);
    string nameFile="Records/"+hour+"-Surgery-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    startingHTML(output, "Surgery");

    output<<"<h2>Description of the surgery: </h2>\n";
    output<<"<p>"<<description<<"</p>\n";

    output<<"<h2>Post surgey treatment: </h2>\n";
    output<<"<p>"<<postSurgeryTreatment<<"</p>\n";

    endingHTML(output, nameFile);
}




//Declaration of Grooming class that inherits from Service class
class Grooming : public Service{
    //Declaration of private attributes
    private:
        string materialUsed;
        string initialState;
        string finalState;

    //Declaration of public methods
    public:
        Grooming(Vet&, Owner&, Pet&);
        Grooming(Vet&, Owner&, Pet&, int[], string, string, string, string);
        void print();
        void printForDB(vector<int> index);
        void printHTML();
};

/**
 * It is the constructor of this object.
 *
 * Uses Service() method. It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * 
 * @return Grooming object.
 */
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

/**
 * It is the constructor of this object.
 *
 * It overloads MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet). It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * @param Int dates[]: The array that stores the date in which the service
 * was done. The array has the day, month and year in that order.
 * @param string newDescription: The description of what the customer
 * asked for.
 * @param string newMaterialUsed: The materials used during the session.
 * @param string newInitialState: The description of the initial
 * status.
 * @param string newFinalState: The description of the final status.
 * 
 * @return Grooming object.
 */
Grooming::Grooming(Vet& newMedic, Owner& newOwner, Pet& newPet, int dates[], string newDescription, string newMaterialUsed, string newInitialState, string newFinalState):Service(newMedic, newOwner, newPet, dates, newDescription){
    materialUsed=newMaterialUsed;
    initialState=newInitialState;
    finalState=newFinalState;
}

/**
 * Prints the data of the grooming service.
 * 
 * @param 
 * 
 * @return
 */
void Grooming::print(){
    startingPrint("Grooming on ");
    cout<<"Description of grooming order:\n"<<description<<"\n\nMaterials used during the session:\n"<<materialUsed<<"\n\n"<<"Appearance before session:\n"<<initialState<<"\n\nAppearance after session:\n"<<finalState<<"\n\n";
    endingPrint();
}

/**
 * Prints the data of the groomig service.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param vector<int> index: The index containing the indexes of the
 * veterinary, owner and pet(in the vector that has the pets in an owner).
 * 
 * @return
 */
void Grooming::printForDB(vector<int> index){
    startingPrintForDB(index, 'G');
    cout<<materialUsed<<"\n"<<initialState<<"\n"<<finalState<<"\n";
}


/**
 * Prints the data of grooming service.
 * 
 * It prints it in a way that can be interpreted as HTML.
 * 
 * @param
 * 
 * @return
 */
void Grooming::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    vector<int> time=ops.currentTime();
    string hour=date+"-"+to_string(time[0])+"-"+to_string(time[1])+"-"+to_string(time[2]);
    string nameFile="Records/"+hour+"-Grooming-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    startingHTML(output, "Grooming");

    output<<"<h2>Description of customer's order: </h2>\n";
    output<<"<p>"<<description<<"</p>\n";

    output<<"<h2>Meterial used during the grooming session: </h2>\n";
    output<<"<p>"<<materialUsed<<"</p>\n";

    output<<"<h2>Initial appearance: </h2>\n";
    output<<"<p>"<<initialState<<"</p>\n";

    output<<"<h2>Final appearance:</h2>\n";
    output<<"<p>"<<finalState<<"</p>\n";

    endingHTML(output, nameFile);
}




//Declaration of Hotel class that inherits from Service class
class Hotel : public Service{
    //Declaration of private attributes
    private:
        int startDateDay;
        int startDateMonth;
        int startDateYear;
        int endDateDay;
        int endDateMonth;
        int endDateYear;

    //Declaration of public methods
    public:
        Hotel(Vet&, Owner&, Pet&);
        Hotel(Vet&, Owner&, Pet&, int[], string, int[], int[]);
        Hotel(Vet&, Owner&, Pet&, int[], string, int[], int[], int);
        void print();
        void printForDB(vector<int>);
        void printHTML();
};


/**
 * It is the constructor of this object.
 *
 * Uses Service() method. It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * 
 * @return Hotel object.
 */
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


/**
 * It is the constructor of this object.
 *
 * It overloads MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet). It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * @param Int dates[]: The array that stores the date in which the service
 * was done. The array has the day, month and year in that order.
 * @param string newDescription: The description of the pets status.
 * @param int startDate[]: Start of the period of staying. It is
 * stored in this order: day, month, year.
 * @param int endDate[]: End of the period of staying. It is
 * stored in this order: day, month, year.
 * 
 * @return Hotel object.
 */
Hotel::Hotel(Vet& newMedic, Owner& newOwner, Pet& newPet, int orderDate[], string newDescription, int startDate[], int endDate[]):Service(newMedic, newOwner, newPet, orderDate, newDescription){
    startDateDay=startDate[0];
    startDateMonth=startDate[1];
    startDateYear=startDate[2];
    endDateDay=endDate[0];
    endDateMonth=endDate[1];
    endDateYear=endDate[2];
}

/**
 * It is the constructor of this object.
 *
 * It overloads MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet). It constructs the object.
 *
 * @param Vet& newMedic: The reference of the vet that did the service.
 * @param Owner& newOwner: The reference of the owner of the pet.
 * @param Pet& newPEt: The reference of the pet.
 * @param Int dates[]: The array that stores the date in which the service
 * was done. The array has the day, month and year in that order.
 * @param string newDescription: The description of the pets status.
 * @param int startDate[]: Start of the period of staying. It is
 * stored in this order: day, month, year.
 * @param int endDate[]: End of the period of staying. It is
 * stored in this order: day, month, year.
 * @param int newCage: The cage the pet is going to be put in.
 * 
 * @return Hotel object.
 */
Hotel::Hotel(Vet& newMedic, Owner& newOwner, Pet& newPet, int orderDate[], string newDescription, int startDate[], int endDate[], int newCage):Service(newMedic, newOwner, newPet, orderDate, newDescription){
    startDateDay=startDate[0];
    startDateMonth=startDate[1];
    startDateYear=startDate[2];
    endDateDay=endDate[0];
    endDateMonth=endDate[1];
    endDateYear=endDate[2];
    patient->setCage(newCage);
}

/**
 * Prints the data of the hotel service.
 * 
 * @param 
 * 
 * @return
 */
void Hotel::print(){
    startingPrint("Hotel entry registered ");
    cout<<"Starting date: "<<startDateDay<<"/"<<startDateMonth<<"/"<<startDateYear+1900<<"\n\nEnding date: "<<endDateDay<<"/"<<endDateMonth<<"/"<<endDateYear+1900<<"\n\n";
    endingPrint();
}

/**
 * Prints the data of the hotel service.
 * 
 * It's printed in a way that can be used to store the data
 * in the database.
 * 
 * @param vector<int> index: The index containing the indexes of the
 * veterinary, owner and pet(in the vector that has the pets in an owner).
 * 
 * @return
 */
void Hotel::printForDB(vector<int> index){
    startingPrintForDB(index, 'H');
    cout<<startDateDay<<"\n"<<startDateMonth<<"\n"<<startDateYear<<"\n";
    cout<<endDateDay<<"\n"<<endDateMonth<<"\n"<<endDateYear<<"\n";  
}

/**
 * Prints the data of the hotel service.
 * 
 * It prints it in a way that can be interpreted as HTML.
 * 
 * @param
 * 
 * @return
 */
void Hotel::printHTML(){
    string date=to_string(dateDay)+"-"+to_string(dateMonth)+"-"+to_string(dateMonth);
    vector<int> time=ops.currentTime();
    string hour=date+"-"+to_string(time[0])+"-"+to_string(time[1])+"-"+to_string(time[2]);
    string nameFile="Records/"+hour+"-Hotel-"+patient->getName()+"-"+customer->getLastName()+"-"+customer->getName()+".html";
    ofstream output(nameFile);

    startingHTML(output, "Hotel");

    output<<"<h2>Description of the stay: </h2>\n";
    output<<"<p>"<<description<<"</p>\n";

    output<<"<h2>Start date: </h2>\n";
    output<<"<p>"<<startDateDay<<"/"<<startDateMonth<<"/"<<startDateYear<<"</p>\n";

    output<<"<h2>Final date: </h2>\n";
    output<<"<p>"<<endDateDay<<"/"<<endDateMonth<<"/"<<endDateYear<<"</p>\n";

    endingHTML(output, nameFile);
}

#endif