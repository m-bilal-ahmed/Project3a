// Bismillah
/*
Code by Bilal,Zain and Ahmed
*/
#include <iostream>
#include "adjacencyList.h"
#include <set>
#include <stack>
#include "Student.h"
#include <map>
#include <vector>
#include <chrono>
using namespace std::chrono;
using namespace std;

void printOverallMap_BFS(map<int, map<string, adjacencyList>> overallMap)
{
    auto start = high_resolution_clock::now();
    //
    
    for (auto it = overallMap.begin(); it != overallMap.end(); ++it)
    {
        cout << "For the Year: " << it->first << endl << endl;
        // year
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            // each class and semster
            cout << "The students in the class " << it2->first << " are..." << endl;
            // students in the class
            it2->second.printStudents_BFS();
        }
        cout << endl << endl;
    }

    //
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << endl;
    cout << "The total time taken by BFS is: " << duration.count() << " microseconds."<< endl;


}

void printOverallMap_DFS(map<int, map<string, adjacencyList>> overallMap)
{
    auto start = high_resolution_clock::now();
    //

    for (auto it = overallMap.begin(); it != overallMap.end(); ++it)
    {
        cout << "For the Year: " << it->first << endl
             << endl;
        // year
        for (auto it2 = it->second.begin(); it2 != it->second.end(); ++it2)
        {
            // each class and semster
            cout << "The students in the class " << it2->first << " are..." << endl;
            // students in the class
            it2->second.printStudents_DFS();
        }
        cout << endl
             << endl;
    }

    //
    auto stop = high_resolution_clock::now();

    auto duration = duration_cast<microseconds>(stop - start);
    cout << endl;
    cout << "The total time taken by DFS is: " << duration.count() << " microseconds" << endl;
}

void insertIntoOverallMap(map<int, map<string, adjacencyList>> &overallMap, Student &student, int yearNumber, string semester_Class)
{

    if (overallMap.count(yearNumber) == 0) // if the year doesn't exist yet.... make a new year in the overallMap
    {

        // But also, since the year doesnt exist yet, the class wouldn't either, so add that

        adjacencyList newList;

        newList.insertEdge(student);

        map<string, adjacencyList> newMap;
        newMap.emplace(semester_Class, newList);

        overallMap.emplace(yearNumber, newMap);
    }
    else
    {
        // First, check if the semester and class exists
        if (overallMap[yearNumber].count(semester_Class) == 1)
        {
            overallMap[yearNumber][semester_Class].insertEdge(student);
        }
        else
        {
            // If the semester and class does not exist
            adjacencyList newList2;

            newList2.insertEdge(student);

            overallMap[yearNumber].emplace(semester_Class, newList2);
        }
    }
}

adjacencyList returnAdjacencyList(map<int, map<string, adjacencyList>> &overallMap, int yearNumber, string semester_Class)
{

    map<string, adjacencyList> current_map = overallMap[yearNumber];

    for (auto it = current_map.begin(); it != current_map.end(); ++it)
    {
        if (it->first == semester_Class)
        {
            adjacencyList list = it->second;
            return list;
        }
    }
}

void removeFromOverallMap(map<int, map<string, adjacencyList>> &overallMap, int yearNumber, string semester_Class, Student student)
{

    map<string, adjacencyList> &current_map = overallMap[yearNumber];

    for (auto it = current_map.begin(); it != current_map.end(); ++it)
    {
        if (it->first == semester_Class)
        {
            it->second.removeEdge(student);
        }
    }
}

void AddAllStudentsToSet_DFS(set<Student, comp> &initialSet, adjacencyList& adj_list)
{

    set<Student, comp> visited;
    stack<Student> s; // stack is for DFS

    Student src;

    for (int i = 0; i < adj_list.getList().size(); i++)
    { // because our graphs deal with disconnected graphs, wrap the algorithm in a for loop that makes sure to touch every single node

        bool cond = true;
        
        for (auto it = adj_list.getList().begin(); it != adj_list.getList().end(); ++it)
        {
            if (visited.count(it->first) == 0 && cond == true)
            { // if we haven't seen this vertex before, then break
                src = it->first;
                cond = false; // for some reason, the break statement wouldn't work, leading the an exception bad access when trying to get it->first
                break;
            }
        }

        if (visited.count(src) == 1)
        { // or, we're starting to repeat values, then break out of this method
            break;
        }

        visited.insert(src);
        s.push(src);

        // Start of algorithm

        while (!s.empty())
        {
            Student u = s.top();
            initialSet.insert(u);
            // cout << u.getName() << "   " << u.getEmail() << endl;
            s.pop();

            for (auto v : adj_list.getList()[u])
            { // this returns the vector of pairs     // map<Student, vector<pair<Student, string>>, comp> adjacencyList;
                // if (v == dest)
                //     return true;
                if ((visited.find(v.first) == visited.end()))
                { // if we DONT find student v.first in the set, then go ahead and insert in stack and the set
                    visited.insert(v.first);
                    s.push(v.first);
                }
            }
        }
    }
}

void findInterSectionOFSets_DFS(set<Student, comp> &initialSet, set<Student, comp> &finalSet, adjacencyList adj_list)
{

    set<Student, comp> visited;
    stack<Student> s; // stack is for DFS

    Student src;

    for (int i = 0; i < adj_list.getList().size(); i++)
    { // because our graphs deal with disconnected graphs, wrap the algorithm in a for loop that makes sure to touch every single node

        for (auto it = adj_list.getList().begin(); it != adj_list.getList().end(); ++it)
        {
            if (visited.count(it->first) == 0)
            { // if we haven't seen this vertex before, then break
                src = it->first;
                break;
            }
        }

        if (visited.count(src) == 1)
        { // or, we're starting to repeat values, then break out of this method
            break;
        }

        visited.insert(src);
        s.push(src);

        // Start of algorithm

        while (!s.empty())
        {
            Student u = s.top();

            if (initialSet.count(u) == 1)
            {
                finalSet.insert(u);
            }
            // initialSet.insert(u);
            // cout << u.getName() << "   " << u.getEmail() << endl;
            s.pop();

            for (auto v : adj_list.getList()[u])
            { // this returns the vector of pairs     // map<Student, vector<pair<Student, string>>, comp> adjacencyList;
                // if (v == dest)
                //     return true;
                if ((visited.find(v.first) == visited.end()))
                { // if we DONT find student v.first in the set, then go ahead and insert in stack and the set
                    visited.insert(v.first);
                    s.push(v.first);
                }
            }
        }
    }
}

int main()
{

    /*
    1. First make a graph and insert student objects by courses.
    2. have some test cases to see if insertion is working fine ?
    3. make the 'condtions' to keep the insertion in such a way that the graph is dense
    */

    // First, initialize the graph
    adjacencyList graphList;
    map<int, map<string, adjacencyList>> overallMap;
    // Variables to enter in by the user
    string Name, major, uf_email;
    string semester, class_Name;
    int UFID, yearNumber;

    // Pre-inserted test cases into our overallMap
    //--------------------------------------

    //-----------------------------Insertions into 2020 -----------------------------//
    // Fall
    Student s1("Zain", 1, "CpE", "z1.edu");
    insertIntoOverallMap(overallMap, s1, 2020, "FA_DSA");

    Student s2("Haroon", 2, "CpE", "h.edu");
    insertIntoOverallMap(overallMap, s2, 2020, "FA_DSA");

    Student s3("Haris", 3, "CS", "h.edu");
    insertIntoOverallMap(overallMap, s3, 2020, "FA_DSA");

    // Spring
    Student s4("Bilal", 4, "CS", "b.edu");
    insertIntoOverallMap(overallMap, s4, 2020, "SP_DSA");

    Student s5("s4", 5, "CS", "4.edu");
    insertIntoOverallMap(overallMap, s5, 2020, "SP_DSA");

    // Repeated Insertions
    insertIntoOverallMap(overallMap, s2, 2020, "SP_DSA");
    insertIntoOverallMap(overallMap, s3, 2020, "SP_DSA");

    // Summer

    //-----------------------------  Insertions into 2021  -----------------------------//
    // // Fall
    // Student s6("s6", 4, "CS", "6.edu");
    // insertIntoOverallMap(overallMap, s6, 2021, "FA_DSA");

    // // Spring
    // Student s7("s7", 5, "CpE", "7.edu");
    // insertIntoOverallMap(overallMap, s7, 2021, "SP_DSA");

    // Student s8("s8", 3, "CpE", "8.edu");
    // insertIntoOverallMap(overallMap, s8, 2021, "SP_DSA");

    // // Repeated Insertions
    // insertIntoOverallMap(overallMap, s2, 2021, "SP_DSA");
    // insertIntoOverallMap(overallMap, s3, 2021, "SP_DSA");

    // // Summer
    // Student student5("Jaabir", 6, "Business", "j.edu");
    // insertIntoOverallMap(overallMap, student5, 2021, "SU_DSA");

    // //----------------------------- Insertions into 2022 -----------------------------//
    // // Fall
    // Student student6("Rayyan", 7, "Bio", "r.edu");
    // insertIntoOverallMap(overallMap, student6, 2022, "FA_DSA");

    // // Spring
    // Student student7("Daniyal", 8, "Bio", "d.edu");
    // insertIntoOverallMap(overallMap, student7, 2022, "SP_CDA");

    // // Summer
    // Student student8("Imran", 8, "CpE", "i.edu");
    // insertIntoOverallMap(overallMap, student8, 2022, "SU_CDA");

    // Student student9("Shahid", 9, "Law", "s.edu");
    // insertIntoOverallMap(overallMap, student9, 2022, "SU_DSA");

    // Student student10("Arhum", 10, "APK", "ar.edu");
    // insertIntoOverallMap(overallMap, student10, 2022, "SU_CDA");

    string arrayMajor[5] = {"CS", "CpE", "Bio", "Math","Chem"};
    int arrayYear[5] = {1999,2001,2025,2024,2025};
    string arraySemClass[8] = {"FA_DSA", "SP_DSA", "FA_CDA", "SP_CDA", "FA_Bio1", "SP_Bio2", "SP_Chem1", "SU_MicroP"};
    int k = 0;

    string test_name, test_major, test_email, test_year, test_sem_Class;
    int test_UFID;


//Testing i tupes

    for (int i = 0; i < 10000; i++) {

        //Name
        test_name = "stu_" + to_string(i);
        //UFID
        test_UFID = i;
        //Major
        int RanMajor = rand() % 5;
        //Email
        test_email = test_name + ".edu";

        //Year and Sem_Class will be inserted directly into the Student constructor
    

        Student test_student(test_name, i, arrayMajor[RanMajor], test_email);
        int RanYear = rand() % 5;
        int RanSemClass = rand() % 8;
        insertIntoOverallMap(overallMap, test_student, arrayYear[RanYear], arraySemClass[RanSemClass]);

    }


    // Now, the for loop for the user

    cout << endl;

    cout << "Welcome to classMatch!" << endl;
    cout << "To start, please register your information." << endl;
    cout << "Enter the following details..." << endl
         << endl;

    cout << "Name: ";
    cin >> Name;
    cout << "Student Number: ";
    cin >> UFID;

    cout << "Major: ";
    cin >> major;

    cout << "Student Email: ";
    cin >> uf_email;

    cout << endl
         << "Thank you for registering. Here is the Main Menu: " << endl;

    // Initialize the user as a student object:
    Student user_student(Name, UFID, major, uf_email);

    bool loopCondition = true;

    int z = 0;

    while (loopCondition)
    {
        cout << "Menu Options: ";
        cout << endl;

        cout << "1. Enroll in a Class" << endl;
        cout << "2. Drop a Class" << endl;
        cout << "3. Find students who share the same classes as you " << endl;
        cout << "4. Print all student who are taking a class this year" << endl;
        cout << "5. Print a list of all classes the user is enrolled in" << endl;
        cout << "-1. End Application" << endl
             << endl;

        int menuOption;

        cout << "Please choose one of the above options: ";
        cin >> menuOption;

        cout << endl;

        if (menuOption == 1)
        {

            cout << "To add a course, enter in the following details: " << endl;

            bool enterMoreClasses = true;

            while (enterMoreClasses)
            {
                cout << "Year: ";
                cin >> yearNumber;

                //=========================================================================================//

                bool isSem = true;
                int k = 0;

                while (isSem)
                {

                    cout << "Semester: Enter in \"FA\" for fall,\"SP\" for spring and \"SU\" for summer: ";
                    cin >> semester;
                    if (semester == "FA" || semester == "SP" || semester == "SU")
                    {
                        isSem = false;
                    }
                    else
                    {
                        cout << "Invalid Semester Name: Enter again" << endl;
                        //--- semster=fa
                        semester = "";
                    }
                    k++;

                    if (k == 15)
                    {
                        cout << "infinite loop entered";
                        break;
                    }
                }

                //======================================================================================//
                cout << "Enter class name: ";
                cin >> class_Name;

                string semester_Class = "";
                semester_Class = semester + "_" + class_Name;

                // Add this course into the student object
                user_student.AddCourse(yearNumber, semester_Class);

                // And also Insert into the database, or theoverallMap
                insertIntoOverallMap(overallMap, user_student, yearNumber, semester_Class);

                cout << "Does the user want to enroll in more classes? (Y/N): ";
                char check;
                cin >> check;
                if (check == 'n' || check == 'N')
                {
                    enterMoreClasses = false;
                    break;
                }
                else
                {
                    continue;
                }
            }
        }

        else if (menuOption == 2)
        {
            // Drop a course
            cout << "Which of the following courses would you like to drop? " << endl;

            map<int, vector<string>> enrolledClasses = user_student.getEnrolledClasses();

            int k = 1;

            for (auto it = enrolledClasses.begin(); it != enrolledClasses.end(); ++it)
            {
                vector<string> vec = it->second;
                int i = 0;
                for (; i < vec.size(); i++)
                {
                    cout << k << ". " << it->first << ", " << vec.at(i) << endl;
                    k++;
                }
            }
            // ------------------------------------------------------------ //
            int numberOfCourseToDrop;

            cout << "Enter one of the above numbers: ";

            cin >> numberOfCourseToDrop;

            int j = 0;

            for (auto it = enrolledClasses.begin(); it != enrolledClasses.end(); ++it)
            {
                vector<string> vec = it->second;
                int i = 0;
                for (; i < vec.size(); i++)
                {
                    if (j == numberOfCourseToDrop - 1)
                    {
                        // First, remove from the student object.
                        user_student.DropCourse(it->first, vec.at(i));
                        // Finally, remove this same course from the data-base
                        removeFromOverallMap(overallMap, it->first, vec.at(i), user_student);
                    }
                    j++;
                }
            }
        }

        else if (menuOption == 3)
        {

            int option = 0;

            cout << "Option 1: Find students in the classes that you specify: " << endl;
            cout << "Option 2: Find any students who share all the same classes as you: " << endl;

            cout << "Enter in which option you want to take: ";

            cin >> option;

            if (option == 1)
            {
                int year1;
                string semester1;
                string class1;

                cout << "Enter in the year you want to look for: ";
                cin >> year1;

                cout << "Enter in the semester you're looking for: ";
                cin >> semester1;

                cout << "Enter in the classes you want to see mutual students in: ";
                cin >> class1;

                string total_sem_class = "";
                total_sem_class = semester1 + "_" + class1;

                adjacencyList list = returnAdjacencyList(overallMap, year1, total_sem_class);

                char optionOther;
                cout << "a. Print using DFS " << endl;
                cout << "b. Print using BFS " << endl;
                cout << "Select option 'a' or 'b': ";
                cin >> optionOther;
                if (optionOther == 'a' || optionOther == 'A')
                {
                    cout << "The students in the class that you are looking for are: " << endl;
                    list.printStudents_DFS();
                    cout << endl;
                }
                else if (optionOther == 'b' || optionOther == 'B')
                {
                    list.printStudents_BFS();
                    cout << endl;
                    // Do BFS
                }

                // search in the map for year1 and total_sem_class
            }
            else if (option == 2)
            {
                cout << "Here are all the classes you are enrolled in right now: " << endl;

                map<int, vector<string>> enrolledClasses = user_student.getEnrolledClasses();

                int k = 1;

                for (auto it = enrolledClasses.begin(); it != enrolledClasses.end(); ++it)
                {
                    vector<string> vec = it->second;
                    int i = 0;
                    for (; i < vec.size(); i++)
                    {
                        cout << k << ". " << it->first << ", " << vec.at(i) << endl;
                        k++;
                    }
                }

                //-----------------------------------------------------//
                cout << "Here's a list of students who share all of these classes with you: " << endl;
                set<Student, comp> initialSet;
                set<Student, comp> finalSet;

                int j = 0;
                for (auto it = enrolledClasses.begin(); it != enrolledClasses.end(); ++it)
                {
                    vector<string> vec = it->second;
                    for (int i = 0; i < vec.size(); i++)
                    {
                        adjacencyList list = returnAdjacencyList(overallMap, it->first, vec.at(i));
                        if (j == 0)
                        {
                            // Add all students in class to set:
                            AddAllStudentsToSet_DFS(initialSet, list);
                        }
                        else
                        {
                            if (j % 2 == 1)
                            {
                                findInterSectionOFSets_DFS(initialSet, finalSet, list);
                                // Now that things are added to the finalSet, clear the initial Set
                                initialSet.clear();
                            }
                            else
                            {
                                findInterSectionOFSets_DFS(finalSet, initialSet, list);
                                // Now initialSet has the intersection, so clear finalSet
                                finalSet.clear();
                            }
                        }
                        j++;
                    }
                }
                // Now, either initialSet of finalSet has the intersections- the other one is empty
                int z = 0;
                if (initialSet.size() > 0)
                {

                    //First, the user_student exists in all these classes, cuz he's enrolled in them, so take him out, cuz he doesn't really count
                    auto it1 = initialSet.find(user_student);
                    initialSet.erase(it1);

                    for (auto it = initialSet.begin(); it != initialSet.end(); ++it)
                    {
                        if (initialSet.size() == 1) {
                            cout << it->getName() << "(" << it->getEmail() << ")" << endl;
                        }
                        else if (z == initialSet.size() - 1 && initialSet.size() > 1)
                        {
                            cout << "and "<< it->getName() << "(" << it->getEmail() << ")" << endl;
                        }
                        else
                        {
                            cout << it->getName() << "(" << it->getEmail() << ")" << ", ";
                        }
                        z++;
                    }
                }
                else
                {

                    // First, the user_student exists in all these classes, cuz he's enrolled in them, so take him out, cuz he doesn't really count
                    auto it1 = finalSet.find(user_student);
                    finalSet.erase(it1);

                    for (auto it = finalSet.begin(); it != finalSet.end(); ++it)
                    {
                        if (initialSet.size() == 1)
                        {
                            cout << it->getName() << "(" << it->getEmail() << ")" << endl;
                        }
                        else if (z == finalSet.size() - 1)
                        {
                            cout << "and " << it->getName() << "(" << it->getEmail() << ")" << endl;
                        }
                        else
                        {
                            cout << it->getName() << "(" << it->getEmail() << ")" << ", ";
                        }
                        z++;
                    }
                }
            }
        }
        else if (menuOption == 4)
        {
            // Now print the overall map
            int option;
            cout << "1. Print using BFS: " << endl;
            cout << "2. Print using DFS: " << endl;

            cout << "Enter one of the above options: ";
            cin >> option;

            if (option == 1) {
                printOverallMap_BFS(overallMap);
            }
            else if (option == 2) {
                printOverallMap_DFS(overallMap);
            }
        }
        else if (menuOption == 5)
        {

            cout << "Here are the courses you are enrolled in right now: " << endl;

            map<int, vector<string>> enrolledClasses = user_student.getEnrolledClasses();

            int k = 1;

            for (auto it = enrolledClasses.begin(); it != enrolledClasses.end(); ++it)
            {
                vector<string> vec = it->second;
                int i = 0;
                for (; i < vec.size(); i++)
                {
                    cout << k << ". " << it->first << ", " << vec.at(i) << endl;
                    k++;
                }
            }
        }
        else if (menuOption == -1)
        {
            break;
        }

        // graphList.insertEdge(student);

        // Now print the overall map

        //    printOverallMap(overallMap);

        z++;

        if (z > 20)
        {
            cout << "loop entered. Ending program " << endl;
            break;
        }

        cout << endl;
    }

    cout << "Program ended." << endl;

    return 0;
}
