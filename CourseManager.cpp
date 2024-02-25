//========================================================================================
//                          CS-300: Project Two
// 
// Name        : CourseManager.cpp
// Author      : Ivette Cerpa
// Version     : 1.0
// Description : This file contains the implementation of the CourseManager class, which
//               serves as the interface for the program. The CourseManager class uses an
//               AVLTree to manage the courses. It includes functions to validate a course
//               ID, parse a line from the input file, read and parse an input file,
//               validate prerequisites of all courses, print information of a specific
//               course, and print all courses in alphanumeric order. The main function
//               is also included in this file, which provides a menu for users to load
//               courses, print all courses, search for a course, or exit the program.
//========================================================================================

#include "CourseManager.hpp"
#include <iostream>
#include <fstream>
#include <sstream>
#include <cctype>
#include <algorithm>

using namespace std;

/**
 * Function to check if a given string is a valid course ID
 *
 * @param str the string to check
 * @return true if the string is a valid course ID, false otherwise
 */
bool CourseManager::isValidCourseID(const string& str) {
    // Check if str has the expected length for a course ID
    if (str.length() != 7) {
        return false;
    }

    // Check if the first 4 characters are letters
    if (!all_of(str.begin(), str.begin() + 4, ::isalpha)) {
        return false;
    }

    // Check if the last 3 characters are digits
    return all_of(str.begin() + 4, str.end(), ::isdigit);
}

/**
 * Function to parse a line from the input file and add the course to the AVL tree
 *
 * @param line is the line from the input file to parse
 */
void CourseManager::parseLine(string line) {
    stringstream ss(line);
    vector<string> courseInfo;
    string info;

    // Split line using commas as delimiter into a vector
    while (getline(ss, info, ',')) {
        courseInfo.push_back(info);
    }

    // Check if line format is correct
    if (courseInfo.size() < 2) {
        cout << "Incorrect line format" << endl;
        cout << "Press enter to exit...";
        cin.ignore();  // Ignore leftover newline
        cin.get();
        exit(1);  // End program
    }

    
    // Validate course ID and course name
    string courseID = courseInfo[0];
    string courseName = courseInfo[1];
    if (!isValidCourseID(courseID)) {
        cout << "Invalid course ID" << endl;
        cout << "Press enter to exit...";
        cin.ignore();  // Ignore leftover newline
        cin.get();
        exit(1);  // End program
    }

    if (isValidCourseID(courseName)) {
        cout << "Course name is missing." << endl;
        cout << "Press enter to exit...";
        cin.ignore();  // Ignore leftover newline
        cin.get();
        exit(1);  // End program
    }
  

    // Create a Course object and insert it into the tree
    vector<string> prerequisites(courseInfo.begin() + 2, courseInfo.end());
    AVLTree::Course course(courseID, courseName, prerequisites);
    courseTree.insert(courseID, course);
}

/**
 * Function to read an input file and parse each line
 *
 * @param fileName the name of the input file to read
 */
void CourseManager::readAndParse(string fileName) {
    // Open the file
    ifstream file(fileName);
    if (!file.is_open()) {
        cout << "Unable to open file" << endl;
        cout << "Press enter to exit...";
        cin.ignore();  // Ignore leftover newline
        cin.get();
        exit(1);  // End program
    }

    // Read and parse each line in the file
    string line;
    while (getline(file, line)) {
        parseLine(line);
    }

    // close the file
    file.close();
}


/**
 * Function to validate that all prerequisites of all courses exist in the AVL tree.
 * If a course is missing a prerequisite, it will print an error message and terminate the program.
 */
void CourseManager::validatePrerequisites() {
    if (!courseTree.validatePrerequisites()) {
        cout << "Some courses have prerequisites that are missing an entry in the file." << endl;
        cout << "Press enter to exit...";
        cin.ignore();  // Ignore leftover newline
        cin.get();
        exit(1);  // End program
    }
}


/**
 * Function to print the information of a specific course
 *
 * @param courseID the ID of the course to print
 */
void CourseManager::printCourseInfo(string courseID) {
    courseTree.printCourseInfo(courseID);
}

/**
 * Function to print all courses in the AVL tree in alphanumeric order
 */
void CourseManager::printAlphanumeric() {
    courseTree.printAlphanumeric();
}



int main() {
	string filePath, course;

    CourseManager manager;

    int choice = 0;
    std::string input;

    while (choice != 4) {
        cout << "Menu: " << endl;
        cout << "1. Load courses" << endl;
        cout << "2. Print all courses alphanumerically" << endl;
        cout << "3. Search for a course" << endl;
        cout << "4. EXIT" << endl;
        cout << "Enter choice: " << endl;

        cin >> input;

        // Check if the input is a digit
        if (!isdigit(input[0]) || stoi(input) < 1 || stoi(input) > 4) {
            cout << "Invalid option. Please enter a number between 1 and 4." << endl;
            continue;  // Skip the rest of the loop and start from the beginning
        }

        choice = stoi(input);  // Convert the valid input to an integer

        switch (choice) {
        case 1:
            // Ask the user for the file name
            cout << "Please enter the name of the file to load: ";
            cin >> filePath;

            cout << "loading courses" << endl;
            manager.readAndParse(filePath);
            manager.validatePrerequisites();
            break;
        case 2:
            manager.printAlphanumeric();
            break;
        case 3:
            cout << "Please enter the course ID that you want to search for: ";
            cin >> course;
            manager.printCourseInfo(course);
            break;
        case 4:
            cout << "Good bye." << endl;
            return 0;
        }
    }
}