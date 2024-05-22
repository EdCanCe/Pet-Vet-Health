#include <bits/stdc++.h>
#define fore(i, l, r) for (long long i = (l); i < (r); i++)
#define nl cout<<"\n"
#define cnl "\n"
using namespace std;




class Pet{
    private:
        string name;
        int birthDay;
        int birthMonth;
        int birthYear;
        string breed;
        string annotations; // Any allergies, etc.
        bool status; // {Alive, With the owner} / {Deceased, In the wild}
    public:
        Pet(string, int, int, int, string, string);
        void setAnnotations(string);
        void setStatus(bool);

};




class Person{
    protected:
        string name;
        string phoneNumber;

    public:
        Person(string, string);
        void showData();
        void setNumber(string);
        string getName();
        string getPhone();
};
Person::Person(string newName, string newPhoneNumber){
    name=newName;
    phoneNumber=newPhoneNumber;
}



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