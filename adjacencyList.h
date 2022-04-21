#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <iterator>
#include <algorithm>
#include <set>
#include "Student.h"
#include <set>
#include <stack>
#include <queue>
#pragma once
using namespace std;




class adjacencyList
{
    private:
            // TODO: Graph structure that supports parallel edges and self-loops

        map<Student, vector<pair<Student, string>>, comp> adjacencyList; // implement as an adjacency list
        map<string, vector<Student>> helperMap;

    public:
        void insertEdge(Student insertedStudent);
        void printAdjList();
        void printStudents_DFS();
        void printStudents_BFS();

        void removeEdge(Student studentToBeRemoved);

        map<Student, vector<pair<Student, string>>, comp>& getList(); // this MUST RETURN BY REFERENCE- IF IT DOESNT, IT RETURNS A WHOLE BUNCH OF BUGS

        //bool isEdge(int from, int to);
        //int sumEdge(int from, int to);
        //std::vector<int> getWeight(int from, int to);
        //std::vector<int> getAdjacent(int vertex);
};





void adjacencyList::insertEdge(Student insertedStudent) // Insert students, and in the graph for each class, doubly connect students with the same major to each other
{
    /*
         TODO: insertEdge() adds a new edge between the from
         and to vertex.
    */
    // if(Node.){

    //Step 1) Initial insertion
    vector<pair<Student, string>> newVector;
    // adjacencyList.emplace(insertedStudent, newVector);
    //adjacencyList.insert(pair < Student, vector<pair<Student, string>>>(insertedStudent, newVector)); // For some reason, emplace doesn't work- if 2 Zain's, with different UFIDs are being tried to be inserted into the map, emplace will just do it so one of the Zain's is kept, even though we do NOT want this
    adjacencyList[insertedStudent] = newVector;

    //Step 2) for loop #1:
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
    {
        if (it->first.getUFID() == insertedStudent.getUFID()) {
            continue;
        }
        else {
            if (it->first.getMajor() == insertedStudent.getMajor()) {
                it->second.push_back(make_pair(insertedStudent, insertedStudent.getMajor()));
            }
        }
    }

    //Step 3) For loop #2

    vector<Student> currentVector;

    for (auto it1 = adjacencyList.begin(); it1 != adjacencyList.end(); ++it1)
    {
        if (it1->first.getUFID() == insertedStudent.getUFID()) {
            //Then copy the contets of the helperMap, for the specific key of the major
            if (helperMap.count(insertedStudent.getMajor()) == 1) {

                currentVector = helperMap[insertedStudent.getMajor()];

                for (int i = 0; i < currentVector.size(); i++) {
                    it1->second.push_back(make_pair(currentVector.at(i), currentVector.at(i).getMajor()));
                }
                break;
            }
            else {
                vector<Student> vec;
                helperMap.emplace(insertedStudent.getMajor(), vec);
            }
        }
    }

    //Step 4: add the insertedStudent to the helper map
    for (auto it3 = helperMap.begin(); it3 != helperMap.end(); ++it3)
    {
        if (insertedStudent.getMajor() == it3->first)
        {
            it3->second.push_back(insertedStudent);
        }
    }

    //Iterate throughout the entire adjacency List
    // for (map<string, vector<pair<Student, string>>>::iterator it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
    // {
    //     for (int i = 0; i < it->second.size(); i++)
    //     {
    //         if (it->first.UFID == insertedStudent.UFID)
    //         {
    //             continue;
    //         }
    //         else {
    //             //Check to see if the major is the same
    //             if (it->second.at(i).second.major == insertedStudent.major) {
    //                 it->second.push_back(make_pair(insertedStudent, major)); // Make a new pair of that student and that student's major
    //              // it->second.push_back(make_pair(insertedStudent, major));
    //              cout << "Student " << insertedStudent.name << "was inserted to the key of " << it->first << ", and this key has a major of " << it->first.name << endl;
    //             }
    //         }
    //     }
    // }






}

void adjacencyList::printAdjList(){                     
    cout<< "The students in this class are: " << endl;
    for (auto it = adjacencyList.begin(); it != adjacencyList.end(); it++) {
            cout << it->first.getName() << " and the students of his same major are: ";
        for (int i = 0; i < it->second.size(); i++) {
            if (i == it->second.size()-1) {
                cout << it->second.at(i).first.getName() << " (" << it->second.at(i).second << ", " << it->second.at(i).first.getEmail() << ")";
            }
            else {
                cout << it->second.at(i).first.getName() << " (" << it->second.at(i).second << ", " << it->second.at(i).first.getEmail() << ") and ";
            }
        }
        cout << endl;
    }
}




void adjacencyList::printStudents_DFS() { //This will implement DFS 

    set<Student, comp> visited;
    stack<Student> s; // stack is for DFS

    Student src;

    for (int i = 0; i < adjacencyList.size(); i++) {  // because our graphs deal with disconnected graphs, wrap the algorithm in a for loop that makes sure to touch every single node


        for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it) {
            if (visited.count(it->first) == 0) { //if we haven't seen this vertex before, then break
                src = it->first;
                break;
            }
        }

        if (visited.count(src) == 1) { // or, we're starting to repeat values, then break out of this method
            break;
        }

        visited.insert(src);
        s.push(src);


    //Start of algorithm

        while (!s.empty()){
            Student u = s.top();
            cout << u.getName() << "  (" << u.getEmail() << ")" << endl;
            s.pop();

            for (auto v : adjacencyList[u]){   //this returns the vector of pairs     // map<Student, vector<pair<Student, string>>, comp> adjacencyList;
                // if (v == dest) 
                //     return true;
                if ((visited.find(v.first) == visited.end())){ //if we DONT find student v.first in the set, then go ahead and insert in stack and the set
                    visited.insert(v.first);
                    s.push(v.first);
                }
            }
            
        }    
    }

//End of algorithm

}





//============================= BFS =======================//


void adjacencyList::printStudents_BFS()
{ // This will implement BFS
    set<Student, comp> visited;
    queue<Student> q; // queues are for BFS

    Student src;

    for (int i = 0; i < adjacencyList.size(); i++)
    {

        for (auto it = adjacencyList.begin(); it != adjacencyList.end(); ++it)
        {
            if (visited.count(it->first) == 0)
            { // if we haven't seen this vertex before, then break
                src = it->first;
                break;
            }
        }

        if (visited.count(src) == 1)
        { // or, we're starting to repeat values, then break out of this method, because this means we've touched every single vertice in our graph
            break;
        }

        visited.insert(src);
        q.push(src);

        // Start of algorithm

        while (!q.empty())
        {
            Student u = q.front();
            cout << u.getName() << "  (" << u.getEmail() << ")" << endl;
            q.pop();

            for (auto v : adjacencyList[u])
            { // this returns the vector of pairs     // map<Student, vector<pair<Student, string>>, comp> adjacencyList;
                // if (v == dest)
                //     return true;
                if ((visited.find(v.first) == visited.end()))
                { // if we DONT find student v.first in the set, then go ahead and insert in stack and the set
                    visited.insert(v.first);
                    q.push(v.first);
                }
            }
        }
    }

    // End of algorithm

}

//----------------------------------------------------------
void adjacencyList::removeEdge(Student studentToBeRemoved) {

    for (auto it = adjacencyList.begin(); it != adjacencyList.end();) {  // map<Student, vector<pair<Student, string>>, comp> adjacencyList;

        if (it->first.getUFID() == studentToBeRemoved.getUFID()) { //remove the actual key from the map
            adjacencyList.erase(it++); //or, after we destroy it, THEN increment the iterator
            continue;
        }

        //also, iterate through every vector and erase that student from there
        vector < pair<Student, string>>& vec = it->second; // MAKE SURE IN ALL REMOVAL SITUATIONS, YOU PASS BY REFERENCE

        for (int i = 0; i < vec.size(); i++) {
            if (vec.at(i).first.getUFID() == studentToBeRemoved.getUFID()) {
                vec.erase(vec.begin() + i);
            }
        }

        ++it; // increment the iterator here
    }


    

}


map<Student, vector<pair<Student, string>>, comp>& adjacencyList::getList() { //THIS MUST RETURN BY REFERECE- IF IT DOESNT, IT LEADS TO A BUNCH OF BUGS LIKE EXCEPTION BAD ACCESS


    return this->adjacencyList;

}