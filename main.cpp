#include <bits/stdc++.h>
#define fore(i, l, r) for (long long i = (l); i < (r); i++)
#define rfc "\033[31;1m"
#define gfc "\033[32;1m"
#define yfc "\033[33;1m"
#define bfc "\033[34;1m"
#define pfc "\033[35;1m"
#define cfc "\033[36;1m"
#define nfc "\033[0m"
using namespace std;




class Operations{
    public:
        Operations();
        vector<int> currentDate();
        int getAgeDifference(vector<int>);
};
Operations::Operations(){}
vector<int> Operations::currentDate(){
    //Portion of code based on https://cplusplus.com/reference/ctime/localtime/
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo=localtime(&rawtime);
    int year=timeinfo->tm_year;
    int month=timeinfo->tm_mon+1;
    int day=timeinfo->tm_mday;
    return {day, month, year};
}
int Operations::getAgeDifference(vector<int> past){
    vector<int> current=currentDate();
    int age=current[2]-past[2];
    if(current[1]<past[1] || (current[1]==past[1] && current[0]<past[0])){
        age--;
    }
    return age;
}




class Pet{
    private:
        string name;
        int birthDay;
        int birthMonth;
        int birthYear;
        string breed;
        string annotations; // Any allergies, etc.
        vector<int> getBirth();
        int cage=0; // In case the pet stays in the veterinary, cage assigns the cage where the pet was put in.
    public:
        Pet(string, int, int, int, string, string);
        Pet(string, int, int, int, string);
        void setAnnotations(string);
        void setCage(int);
        string getName(); //Used when owner selects which pet is being treated
        string getAnnotations();
        int getCage();
        void showData();
};
Pet::Pet(string newName, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed, string newAnnotations){
    name=newName;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
    annotations=newAnnotations;
}
Pet::Pet(string newName, int newBirthDay, int newBirthMonth, int newBirthYear, string newBreed){
    name=newName;
    birthDay=newBirthDay;
    birthMonth=newBirthMonth;
    birthYear=newBirthYear;
    breed=newBreed;
    annotations="";
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
    Operations oper=Operations();
    cout<<gfc<<name<<nfc<<": "<<breed<<" - ";
    cout<<oper.getAgeDifference(getBirth())<<" years old\n";
    if(annotations!=""){
        cout<<"Special annotations:\n"<<annotations<<"\n";
    }
    if(cage!=0){
        cout<<"Cage: "<<cage<<"\n";
    }
}



class Person{
    protected:
        string name;
        string lastName;
        string phoneNumber;
    public:
        Person(string, string, string);
        void setNumber(string);
        string getName();
        string getPhone();
        void showData();
};
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




class Owner : public Person{
    private:
        vector<Pet*> pets;
    public:
        Owner(string, string, string);
        void showPets();
        void addPet(Pet&);
        int petSize();
        Pet& getPet(int);
};
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



class Vet : public Person{
    private:
        string professionalLicense;
        string college;
    public:
        Vet(string, string, string, string, string);
        string getProfessionalLicense();
        string getCollege();
        void showData();
};
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
        virtual void print();
        Vet& getVet();
        Pet& getPet();
        void startingPrint(string);
        void endingPrint();
};
Service::Service(Vet& newMedic, Owner& newOwner, Pet& newPet){
    Operations op=Operations();
    vector<int> dates=op.currentDate();
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
void Service::print(){
    cout<<"It's empty\n\n";
}




class MedicalCheck : public Service{
    private:
        string diagnosis;
        string treatment;
    public:
        MedicalCheck(Vet&, Owner&, Pet&);
        MedicalCheck(Vet&, Owner&, Pet&, int[], string, string, string);
        void print();
};
MedicalCheck::MedicalCheck(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ MEDICAL CHECK CREATION ]]"<<nfc<<"\n";
    cout<<"Description of the case: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Diagnosis of the case: ";
    getline(cin, diagnosis);
    cout<<"Given treatment: ";
    getline(cin, treatment);
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




class Surgery : public Service{
    private:
        string postSurgeryTreatment;
    public:
        Surgery(Vet&, Owner&, Pet&);
        Surgery(Vet&, Owner&, Pet&, int[], string, string);
        void print();
};
Surgery::Surgery(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ SURGERY ENTRY CREATION ]]"<<nfc<<"\n";
    cout<<"Brief description of the surgery: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Post surgery treatment: ";
    getline(cin, postSurgeryTreatment);
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




class Grooming : public Service{
    private:
        string materialUsed;
        string initialState;
        string finalState;
    public:
        Grooming(Vet&, Owner&, Pet&);
        Grooming(Vet&, Owner&, Pet&, int[], string, string, string, string);
        void print();
};
Grooming::Grooming(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[  GROOMING SESSION ENTRY ]]"<<nfc<<"\n";
    cout<<"Description of the grooming order: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Material used in the session: ";
    getline(cin, materialUsed);
    cout<<"Description on pet's appearance before session: ";
    getline(cin, initialState);
    cout<<"Description on pet's appearance after session: ";
    getline(cin, finalState);
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
};
Hotel::Hotel(Vet& newMedic, Owner& newOwner, Pet& newPet):Service(newMedic, newOwner, newPet){
    cout<<yfc<<"[[ HOTEL ENTRY CREATION ]]"<<nfc<<"\n";
    cout<<"Description of the stay: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Start of the period:\n\tDay(0-31): ";
    cin>>startDateDay;
    cout<<"\tMonth(1-12): ";
    cin>>startDateMonth;
    cout<<"\tYear(19XX-20XX): ";
    cin>>startDateYear;
    startDateYear-=1900;
    cout<<"End of the period:\n\tDay(0-31): ";
    cin>>endDateDay;
    cout<<"\tMonth(1-12): ";
    cin>>endDateMonth;
    cout<<"\tYear(19XX-20XX): ";
    cin>>endDateYear;
    endDateYear-=1900;
    Operations op;
    vector<int> currentDate=op.currentDate();
    if(startDateDay==currentDate[0] && startDateMonth==currentDate[1] && startDateYear==currentDate[2]){
        int index;
        cout<<"Number of cage it's going to be put in: ";
        cin>>index;
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
    cout<<"Starting date: "<<startDateDay<<"/"<<startDateMonth<<"/"<<startDateYear<<"\n\nEnding date: "<<endDateDay<<"/"<<endDateMonth<<"/"<<endDateYear<<"\n\n";
}









int main(){

    //Primera parte - Funcionamiento básico de clases
    cout<<"Veterinarios:\n";
    Vet Medico1=Vet("Juan", "Perez Perez", "442 111 1111", "1111111111", "ITESM");
    Vet Medico2=Vet("Maria Elena", "Martinez Martinez", "442 222 2222", "22222222222", "UAQ");
    Medico1.showData();
    cout<<"\n";
    Medico2.showData();
    cout<<"\n";

    cout<<"Duenos:\n";
    Owner Dueno1=Owner("Edmundo", "Canedo Cervantes", "443 423 7305");
    Owner Dueno2=Owner("Jose", "Garcia Garcia", "442 333 3333");
    Dueno1.showData();
    cout<<"\n";
    Dueno2.showData();
    cout<<"\n";

    Pet* aux = new Pet(Pet("Mike", 1, 1, 110, "Siamese Cat")); //Eñ año 110 corresponde a 2010.
    Dueno1.addPet(*aux);
    aux = new Pet(Pet("Firulais", 2, 2, 105, "Street Dog", "Misses a leg")); //El año 105 corresponde a 2005
    Dueno1.addPet(*aux);
    aux = new Pet(Pet("Mipo", 12, 24, 122, "Hamster"));
    Dueno1.addPet(*aux); //El año 123 corresponde a 2022

    cout<<"\nMascotas del primer dueno:\n";
    fore(i,0,Dueno1.petSize()){
        Dueno1.getPet(i).showData();
    }

    Dueno1.getPet(2).setAnnotations("If it cannot be found search in the sawdust, he likes to hide in there");
    cout<<"\n\nMascotas del primer dueno después de modificación:\n";
    fore(i,0,Dueno1.petSize()){
        Dueno1.getPet(i).showData();
    }

    aux = new Pet(Pet("Michis", 6, 6, 116, "Street Cat")); //Eñ año 116 corresponde a 2016.
    Dueno2.addPet(*aux);
    cout<<"\n\nMascotas del segundo dueno:\n";
    fore(i,0,Dueno2.petSize()){
        Dueno2.getPet(i).showData();
    }


    //Liberar memoria
    for
}