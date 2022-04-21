#include <string>
#include <iostream>
#include <map>
#include <vector>

using namespace std;

#pragma once

class Student {

//Private variables
 string name;
 int UFID;
 string major; // we can map integers to different majors
 string uf_email;

 map<int, vector<string>> classesEnrolledIn;

public:

//Constructors
Student();
Student(string name, int UFID, string major, string uf_email);

//Accessors or Getters
string getName() const;
int getUFID() const;
string getMajor() const;
string getEmail() const;
map<int, vector<string>> getEnrolledClasses() const;

//Modifers or Setters
void AddCourse(int year, string sem_Course);   
void DropCourse(int year, string sem_Course); 

};



Student::Student() {
    this->name = "Default name";
    this->UFID = 0;
    this->major = "Default Major";
    this->uf_email = "default_email";
}

Student::Student(string name, int UFID, string major, string uf_email) {
    this->name = name;
    this->UFID = UFID;
    this->major = major;
    this->uf_email = uf_email;
}

string Student::getName() const {
    return this->name;
}

int Student::getUFID() const {
    return this->UFID;
}

string Student::getMajor() const {
    return this->major;
}

string Student::getEmail() const {
    return this->uf_email;
}

map<int, vector<string>> Student::getEnrolledClasses() const {
    return this->classesEnrolledIn;
}



//====================
struct comp
{
    bool operator()(const Student &s1, const Student &s2) const
    {
        // Compare the 2 UFID's, return true if UFID is less than UFID

        if (s1.getName() < s2.getName()) {
            return true;
        }
        return false;
    }
};

//======================


void Student::AddCourse(int year, string sem_Course) {

if (classesEnrolledIn.count(year) == 0)
{ // the year and semester don't exist yet
    vector<string> vec;
    vec.push_back(sem_Course);

    classesEnrolledIn.emplace(year, vec);
    }
    else
    {                                                  // the year exists alread
        vector<string> &vec = classesEnrolledIn[year]; // make sure to have it as a REFERENCE

        bool alreadyEnrolledInClass = false;

        for (int i = 0; i < vec.size(); i++)
        {
            if (vec.at(i) == sem_Course)
            {
                alreadyEnrolledInClass = true;
            }
        }

        if (alreadyEnrolledInClass == true)
        {
            cout << "Error: You've already registered for this class!" << endl;
        }
        else
        {
            vec.push_back(sem_Course);
        }
    }
}


void Student::DropCourse(int year, string sem_Course) {

    if (classesEnrolledIn.count(year) == 0) {
        cout << "You aren't enrolled in this year" << endl;
    }
    else {
        vector<string>& vec = classesEnrolledIn[year];

        
        int i = 0;
        bool classFound = false;

        for (; i < vec.size(); i++) {
            if (vec.at(i) == sem_Course) {
                classFound = true;
                break;
            }
        }


        if (classFound == false) {
            cout << "The year you entered was found, but the class you wanted to drop was not." << endl;
        }
        else {
            
            auto it = vec.begin() + i;

            cout << "The class " << vec.at(i) << ", " << year << " has been successfully dropped." << endl;

            vec.erase(it);

        }

    }


}