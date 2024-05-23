#include <bits/stdc++.h>
#define fore(i, l, r) for (long long i = (l); i < (r); i++)
#define nl cout<<"\n"
#define cnl "\n"
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
        cout<<"Special annotations:\n"<<annotations<<cnl;
    }
    if(cage!=0){
        cout<<"Cage: "<<cage<<cnl;
    }
}



class Person{
    protected:
        string name;
        string phoneNumber;
    public:
        Person(string, string);
        void setNumber(string);
        string getName();
        string getPhone();
};
Person::Person(string newName, string newPhoneNumber){
    name=newName;
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




class Owner : public Person{
    private:
        vector<Pet> pets;
    public:
        Owner(string, string);
        Owner(string, string, vector<Pet>);
        void showPets();
        void addPet();
        int petSize();
        Pet& getPet(int);
};
Owner::Owner(string newName, string newPhoneNumber):Person(newName, newPhoneNumber){}
Owner::Owner(string newName, string newPhoneNumber, vector<Pet> newPets):Person(newName, newPhoneNumber){
    pets=newPets;
}
void Owner::showPets(){
    if(pets.size()>0){
        fore(i,0,pets.size()){
            cout<<i<<".- ";
            pets[i].showData();
            nl;
        }
    }else{
        cout<<rfc<<"There are no pets\n\n"<<nfc;
    }
}
void Owner::addPet(){
    cout<<yfc<<"[[ PET CREATION ]]"<<nfc<<cnl;
    string newName, newBreed, newAnnotations;
    cout<<"Name of the pet: ";
    cin.ignore();
    getline(cin, newName);
    int bday, bmonth, byear;
    cout<<"Date of birth:\n\tDay(0-31): ";
    cin>>bday;
    cout<<"\tMonth(1-12): ";
    cin>>bmonth;
    cout<<"\tYear(19XX-20XX): ";
    cin>>byear;
    byear-=1900;
    cout<<"Type of breed: ";
    cin.ignore();
    getline(cin, newBreed);
    cout<<"Any special annotations like allergies? Y/N ";
    char c; cin>>c;
    if(c=='Y'){
        cout<<"Annotations: ";
        cin.ignore();
        getline(cin, newAnnotations);
    }
    pets.push_back(Pet(newName, bday, bmonth, byear, newBreed, newAnnotations));
    nl;
}
int Owner::petSize(){
    return pets.size();
}
Pet& Owner::getPet(int index){
    return pets[index];
}




class Vet : public Person{
    private:
        string professionalLicense;
        string college;
    public:
        Vet(string, string, string, string);
        string getProfessionalLicense();
        string getCollege();
};
Vet::Vet(string newName, string newPhoneNumber, string newProfessionalLicense, string newCollege):Person(newName, newPhoneNumber){
    professionalLicense=newProfessionalLicense;
    college=newCollege;
}
string Vet::getProfessionalLicense(){
    return professionalLicense;
}
string Vet::getCollege(){
    return college;
}




class Service{
    protected:
        Vet *medic;
        Pet *customer;
        int dateDay;
        int dateMonth;
        int dateYear;
        string description;
    public:
        Service(Vet&, Pet&);
        virtual void print();
        Vet& getVet();
        Pet& getPet();
        void startingPrint(string);
        void endingPrint();
};
Service::Service(Vet& newMedic, Pet& newPet){
    Operations op=Operations();
    vector<int> dates=op.currentDate();
    dateDay=dates[0];
    dateMonth=dates[1];
    dateYear=dates[2];
    medic=&newMedic;
    customer=&newPet;
}
Vet& Service::getVet(){
    return *medic;
}
Pet& Service::getPet(){
    return *customer;
}
void Service::startingPrint(string title){
    cout<<gfc<<title<<dateDay<<"/"<<dateMonth<<"/"<<dateYear-100<<nfc<<cnl<<cnl;
    cout<<cfc<<"Pet: "<<nfc;
    customer->showData();
    nl;
}
void Service::endingPrint(){
    cout<<"Veterinary in charge: "<<medic->getName()<<" - "<<medic->getPhone()<<" | "<<medic->getCollege()<<": "<<medic->getProfessionalLicense()<<"\n\n";
}
void Service::print(){
    cout<<"It's empty\n\n";
}




class MedicalCheck : public Service{
    private:
        string diagnosis;
        string treatment;
    public:
        MedicalCheck(Vet& newMedic, Pet& newPet);
        void print();
};
MedicalCheck::MedicalCheck(Vet& newMedic, Pet& newPet):Service(newMedic, newPet){
    cout<<yfc<<"[[ MEDICAL CHECK CREATION ]]"<<nfc<<cnl;
    cout<<"Description of the case: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Diagnosis of the case: ";
    getline(cin, diagnosis);
    cout<<"Given treatment: ";
    getline(cin, treatment);
    nl;
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
        Surgery(Vet& newMedic, Pet& newPet);
        void print();
};
Surgery::Surgery(Vet& newMedic, Pet& newPet):Service(newMedic, newPet){
    cout<<yfc<<"[[ SURGERY ENTRY CREATION ]]"<<nfc<<cnl;
    cout<<"Brief description of the surgery: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Post surgery treatment: ";
    getline(cin, postSurgeryTreatment);
    nl;
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
        Grooming(Vet& newMedic, Pet& newPet);
        void print();
};
Grooming::Grooming(Vet& newMedic, Pet& newPet):Service(newMedic, newPet){
    cout<<yfc<<"[[  GROOMING SESSION ENTRY ]]"<<nfc<<cnl;
    cout<<"Description of the grooming order: ";
    cin.ignore();
    getline(cin, description);
    cout<<"Material used in the session: ";
    getline(cin, materialUsed);
    cout<<"Description on pet's appearance before session: ";
    getline(cin, initialState);
    cout<<"Description on pet's appearance after session: ";
    getline(cin, finalState);
    nl;
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
        Hotel(Vet& newMedic, Pet& newPet);
        void print();
};
Hotel::Hotel(Vet& newMedic, Pet& newPet):Service(newMedic, newPet){
    cout<<yfc<<"[[ HOTEL ENTRY CREATION ]]"<<nfc<<cnl;
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
        customer->setCage(index);
    }
    nl;
}
void Hotel::print(){
    startingPrint("Hotel entry registered ");
    cout<<"Starting date: "<<startDateDay<<"/"<<startDateMonth<<"/"<<startDateYear<<"\n\nEnding date: "<<endDateDay<<"/"<<endDateMonth<<"/"<<endDateYear<<"\n\n";
}




class PetVetHealth{
    private:
        vector<MedicalCheck> rec1;
        vector<Surgery> rec2;
        vector<Grooming> rec3;
        vector<Hotel> rec4;
        vector<Service*> records; // Vector based on https://www.geeksforgeeks.org/cpp-polymorphism/
        vector<Owner> owners;
        vector<Vet> vets; 
        void loadData();
        void saveData();
        void exit();
        void loop();
        void clean();
        void addVet();
        void addOwner();
        void selectOwner();
        void selectedOwner(Owner&);
        void addPet(Owner&);
        void selectPet(Owner&);
        void selectedPet(Pet&);
        Vet& selectVet();
        bool seeRecords(Pet&);
        vector<Service*> filterByPet(Pet&);
    public:
        PetVetHealth();
        void start();
};
PetVetHealth::PetVetHealth(){
    cout<<bfc<<"|| [[ THE SYSTEM HAS BEEN INITIALIZED ]] ||"<<nfc<<"\n";
}
void PetVetHealth::loadData(){
    ifstream input("database.txt");
    while(!input.is_open()){
        cout<<"The data couldn't be loaded\nWould you like to retry? Y/N ";
        char c; cin>>c;
        if(c!='Y'){
            cout<<"Exiting...";
            abort();
        }
    }

    input.close();
}
void PetVetHealth::saveData(){

}
void PetVetHealth::start(){
    cout<<"Press ENTER to continue: ";
    getchar();
    clean();
    loadData();
    loop();
}
void PetVetHealth::exit(){

}
void PetVetHealth::loop(){
    int act=1;
    while(act!=0){
        clean();
        cout<<yfc<<"What would you like to do?\n"<<nfc;
        cout<<"\t0.- Exit\n";
        cout<<"\t1.- Add vet\n";
        cout<<"\t2.- Add owner\n";
        cout<<"\t3.- Select owner(add an entry, see pets, etc)\n";
        cout<<"\nType the correspondent number: ";
        cin>>act;
        switch(act){
        case 1:
            addVet();
            break;
        case 2:
            addOwner();
            break;
        case 3:
            selectOwner();
            break;
        case 0:
            break;
        }
    }
}
void PetVetHealth::clean(){
#ifdef _WIN32
    system("cls");
#else
    system ("clear");
#endif
}
void PetVetHealth::addVet(){
    clean();
    cout<<yfc<<"[[ VET CREATION ]]"<<nfc<<cnl;
    string name, phone, license, college;
    cout<<"Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Phone number: ";
    getline(cin,phone);
    cout<<"Professional license: ";
    getline(cin,license);
    cout<<"College: ";
    getline(cin,college);
    vets.push_back(Vet(name, phone, license, college));
}
void PetVetHealth::addOwner(){
    clean();
    cout<<yfc<<"[[ OWNER CREATION ]]"<<nfc<<cnl;
    string name, phone;
    cout<<"Name: ";
    cin.ignore();
    getline(cin,name);
    cout<<"Phone number: ";
    getline(cin,phone);
    owners.push_back(Owner(name, phone));
}
void PetVetHealth::selectOwner(){
    clean();
    cout<<yfc<<"[[ LIST OF OWNERS ]]"<<nfc<<cnl;
    if(owners.size()==0) cout<<rfc<<"There are no owners\n"<<nfc;
    fore(i,0,owners.size()){
        cout<<"\t"<<i<<".- "<<owners[i].getName()<<" "<<owners[i].getPhone()<<"\n";
    }
    cout<<"Index of owner to select (-1 to go back): ";
    int n=owners.size();
    cin>>n;
    if(n==-1) return;
    while(n>=owners.size() || n<0){
        cout<<"Invalid value, type again: ";
        cin>>n;
        if(n==-1) return;
    }
    selectedOwner(owners[n]);
}
void PetVetHealth::selectedOwner(Owner& customer){
    int act=1;
    while(act!=0){
        clean();
        cout<<yfc<<"What would you like to do?\n"<<nfc;
        cout<<"\t0.- Return\n";
        cout<<"\t1.- Add pet\n";
        cout<<"\t2.- Select pet(add an entry, see data, etc)\n";
        cout<<"\nType the correspondent number: ";
        cin>>act;
        switch(act){
        case 1:
            addPet(customer);
            break;
        case 2:
            selectPet(customer);
            break;
        case 0:
            break;
        }
    }
}
void PetVetHealth::addPet(Owner& customer){
    clean();
    customer.addPet();
}
void PetVetHealth::selectPet(Owner& customer){
    clean();
    cout<<yfc<<"[[ LIST OF PETS ]]"<<nfc<<cnl;
    customer.showPets();
    cout<<"Index of pet to select (-1 to go back): ";
    int n=customer.petSize();
    cin>>n;
    if(n==-1) return;
    while(n>=customer.petSize() || n<0){
        cout<<"Invalid value, type again: ";
        cin>>n;
        if(n==-1) return;
    }
    selectedPet(customer.getPet(n));
}
void PetVetHealth::selectedPet(Pet& customer){
    int act=1;
    while(act!=0){
        clean();
        cout<<yfc<<"What would you like to do?\n"<<nfc;
        cout<<"\t0.- Return\n";
        cout<<"\t1.- Add medical check\n";
        cout<<"\t2.- Add surgery\n";
        cout<<"\t3.- Add grooming\n";
        cout<<"\t4.- Add hotel\n";
        cout<<"\t5.- See records\n";
        cin>>act;
        switch(act){
        case 1:
                rec1.push_back(MedicalCheck(selectVet(), customer));
                records.push_back(&rec1[rec1.size()-1]);
            break;
        case 2:
                rec2.push_back(Surgery(selectVet(), customer));
                records.push_back(&rec2[rec2.size()-1]);
            break;
        case 3:
                rec3.push_back(Grooming(selectVet(), customer));
                records.push_back(&rec3[rec3.size()-1]);
            break;
        case 4:
                rec4.push_back(Hotel(selectVet(), customer));
                records.push_back(&rec4[rec4.size()-1]);
            break;
        case 5:
                seeRecords(customer);
            break;
        case 0:
            break;
        }
    }
}
Vet& PetVetHealth::selectVet(){
    clean();
    cout<<yfc<<"[[ LIST OF VETS ]]"<<nfc<<cnl;
    if(vets.size()==0) cout<<rfc<<"There are no vets\n"<<nfc;
    fore(i,0,vets.size()){
        cout<<"\t"<<i<<".- "<<vets[i].getName()<<" "<<vets[i].getProfessionalLicense()<<"\n";
    }
    cout<<"Index of vet to select: ";
    int n=vets.size();
    cin>>n;
    while(n>=vets.size() || n<0){
        cout<<"Invalid value, type again: ";
        cin>>n;
    }
    return vets[n];
}
bool PetVetHealth::seeRecords(Pet& customer){
    int c=0;
    for(Service* i:records){
        if(&i->getPet()==&customer) i->print();
        c++;
    }
    cout<<"Press ENTER to continue: ";
    string s;
    cin.ignore();
    getline(cin,s);
    return c%2;
}





int main(){

    PetVetHealth* manager = new PetVetHealth();
    manager->start();   
    delete manager;

}