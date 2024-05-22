#include <bits/stdc++.h>
#define fore(i, l, r) for (long long i = (l); i < (r); i++)
#define nl cout<<"\n"
#define cnl "\n"
using namespace std;




class Operations{
    public:
        string getAgeDifference(vector<int>);
};
string Operations::getAgeDifference(vector<int> pastDate){

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
    public:
        Pet(string, int, int, int, string, string);
        void setAnnotations(string);
        string getName(); //Used when owner selects which pet is being treated
        string getAnnotations();
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
string Pet::getName(){
    return name;
}
vector<int> Pet::getBirth(){
    vector<int> aux={birthDay, birthMonth, birthYear};
    return aux;
}
string Pet::getAnnotations(){
    return annotations;
}
void Pet::showData(){
    Operations oper;
    cout<<name<<": "<<breed<<cnl;
    cout<<oper.getAgeDifference(getBirth())<<" years old\n";
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
        string id;
        vector<Pet> pets;
    public:
        Owner(string, string);
        Owner(string, string, vector<Pet>);
        void showPets();
        void addPet();
};
Owner::Owner(string newName, string newPhoneNumber):Person(newName, newPhoneNumber){}
Owner::Owner(string newName, string newPhoneNumber, vector<Pet> newPets):Person(newName, newPhoneNumber){
    pets=newPets;
}
void Owner::showPets(){
    if(pets.size()>0){
        fore(i,0,pets.size()){
            pets[i].showData();
            nl;
        }
    }else{
        cout<<"There are no pets\n";
    }
}



class Vet : public Person{
    private:

    public:
};




int main(){

    //Portion of code based on https://cplusplus.com/reference/ctime/localtime/
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo = localtime (&rawtime);
    int year = timeinfo->tm_year;
    int month = timeinfo->tm_mon+1;
    int day = timeinfo->tm_mday;
    cout<<day<<" "<<month<<" "<<year;
}