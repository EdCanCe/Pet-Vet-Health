/*
*
* Pet Vet Health Proyect - Operations Class
* A01645576
* 07/06/2024
* This class is used by other classes to do certain
* operations, just as the name says.
* Mainly the operations are to control user input and
* prevent they enter something that they weren't asked for
*
*/

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

//Declaration of Operations class
class Operations{
    //Since it only has methods, there is no reason to have private attributes.

    //Declaration of the methods Operations will have
    public:
        Operations();
        vector<int> currentDate();
        vector<int> currentTime();
        int getAgeDifference(vector<int>);
        int getInt();
        int getInt(int, int);
        int getInt(string);
        string getString();
        char getChar();
        bool getYesOrNo();
};

/**
 * It is the constructor of this object.
 *
 * It constructs the object
 *
 * @param
 * 
 * @return Operations object
 */
Operations::Operations(){}

/**
 * Returns the current date.
 * 
 * Get's the current values of the day, month and
 * year. It returns it in the form of a vector. The
 * year starts at 0 meaning 1900.
 * 
 * @param 
 * 
 * @return vector<int> - having day, month and year in that order
 */
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

/**
 * Returns the current time.
 * 
 * Get's the current values of the hour, minute and
 * second. It returns it in the form of a vector.
 * 
 * @param
 * 
 * @return vector<int> - Having hour, minute and second in that order
 */
vector<int> Operations::currentTime(){
    //Portion of code based on https://cplusplus.com/reference/ctime/localtime/
    time_t rawtime;
    struct tm * timeinfo;
    time (&rawtime);
    timeinfo=localtime(&rawtime);
    int hour=timeinfo->tm_hour;
    int min=timeinfo->tm_min;
    int seg=timeinfo->tm_sec;
    return {hour, min, seg};
}

/**
 * Returns the age difference between two dates.
 * 
 * By substrating the years and checking if the month and/or already
 * passed, it calculates the age difference between two different
 * dates.
 * 
 * @param vector<int> past: Having the day, month and year in that order.
 * 
 * @return int - The age difference in years.
 */
int Operations::getAgeDifference(vector<int> past){
    vector<int> current=currentDate();
    int age=current[2]-past[2];
    if(current[1]<past[1] || (current[1]==past[1] && current[0]<past[0])){
        age--;
    }
    return age;
}

/**
 * Gets an integer with user input.
 * 
 * By reading and validating strings given as an input by the user it
 * checks if it can be used as an integer to be able to return it. It
 * does this by looping the string and validating each character. In
 * case it's not validated it asks for another input. When it's 
 * confirmed it's a number is passed on to another loop to make it
 * an integer. Then checks if it's a negative number to make it one.
 * 
 * @param 
 * 
 * @return int - The integer the user gave as input.
 */
int Operations::getInt(){
    string s;
    getline(cin, s);
    int li = s[0]=='-' ? 1 : 0;
    int x=s.size();
    for(int i=li; i<x; i++){
        if(s[i]<'0' || s[i]>'9'){
            cout<<"It must be a number\nTry again: ";
            getline(cin, s);
            li = s[0]=='-' ? 1 : 0;
            i=li-1;
            x=s.size();
        }
    }
    x=0;
    fore(i,li,s.size()){
        x*=10;
        x+=(s[i]-'0');
    }
    return s[0]=='-' ? x*-1 : x;
}

/**
 * Gets an integer between two different numbers.
 * 
 * This method overloads getInt(). Using that method it gets an
 * integer, then checks if it's between the given range. In case
 * it's not it asks again for another number.
 * 
 * @param int a: The lower number of the range.
 * @param int b: The higher number of the range.
 * 
 * @return int - The integer the user gave as input.
 */
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

/**
 * Gets an integer with a string.
 * 
 * This method overloads getInt(). Given a string it loops through
 * it to make an integer out of it.
 * 
 * @param string s: The number as a string.
 * 
 * @return int - The integer the user gave as input.
 */
int Operations::getInt(string s){
    int x=0;
    fore(i,0,s.size()){
        x*=10;
        x+=(s[i]-'0');
    }
    return x;
}

/**
 * Gets a string with user input.
 * 
 * Using getline() gets a string.
 * 
 * @param 
 * 
 * @return string - The string the user gave as input
 */
string Operations::getString(){
    string s;
    getline(cin, s);
    return s;
}

/**
 * Gets a character with user input
 * 
 * By using getString() gets a string with user input. Then it
 * loops if it's not a single character until only one character
 * is given as the input. Then it returns that character.
 * 
 * @param 
 * 
 * @return char - The character the user gave as input.
 */
char Operations::getChar(){
    string s;
    s=getString();
    while(s.size()>1){
        cout<<"Only enter one character: ";
        s=getString();
    }
    return s[0];
}

/**
 * Gets a bool meaning a yes or a no.
 * 
 * It uses getChar() to get a character, then checks if its a 'Y'
 * or a 'N'. In case not it asks again in a loop until it is given
 * one character with those restrictions. If the character is a 'Y' it
 * returns true, if it's 'N' it returns false.
 * 
 * @param 
 * 
 * @return bool - A true if is a yes and a false if is a no.
 */
bool Operations::getYesOrNo(){
    char q=getChar();
    while(!(q=='Y' || q=='N')){
        cout<<"It's not a 'Y' nor an 'N', type again: ";
        q=getChar();
    }
    return q=='Y';
}

//Creates an operations object that will be used throughout the classes.
Operations ops;

#endif