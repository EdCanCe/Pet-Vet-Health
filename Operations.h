#ifndef OPERATIONS_H
#define OPERATIONS_H

#include<iostream>
#include<vector>
#include<string>
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
        int getInt();
        int getInt(int, int);
        int getInt(string);
        string getString();
        char getChar();
        bool getYesOrNo();
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

int Operations::getInt(){
    string s;
    getline(cin, s);
    int li = s[0]=='-' ? 1 : 0;
    fore(i,li,s.size()){
        if(s[i]<'0' || s[i]>'9'){
            cout<<"It must be a number\nTry again: ";
            cin.ignore();
            getline(cin, s);
            i=0;
        }
    }
    int x=0;
    fore(i,li,s.size()){
        x*=10;
        x+=(s[i]-'0');
    }
    return s[0]=='-' ? x*-1 : x;
}

int Operations::getInt(int a, int b){
    if(a>b) swap(a,b);
    int x;
    x=getInt();
    while(x<a || x>b){
        cout<<"The number must be between "<<a<<" and "<<b<<"\nTry again: ";
        x=getInt();
    }
    return x;
}

int Operations::getInt(string s){
    int x=0;
    fore(i,0,s.size()){
        x*=10;
        x+=(s[i]-'0');
    }
    return x;
}

string Operations::getString(){
    string s;
    getline(cin, s);
    return s;
}

char Operations::getChar(){
    string s;
    s=getString();
    while(s.size()>1){
        cout<<"Only enter one character: ";
        s=getString();
    }
    return s[0];
}

bool Operations::getYesOrNo(){
    char q=getChar();
    while(!(q=='Y' || q=='N')){
        cout<<"It's not a 'Y' nor an 'N', type again: ";
        q=getChar();
    }
    return q=='Y';
}

Operations ops;

#endif