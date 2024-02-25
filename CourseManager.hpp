#ifndef COURSEMANAGER_HPP
#define COURSEMANAGER_HPP

#include "AVLTree.hpp"

//CourseManager.hpp
//Ivette Cerpa

// The CourseManager class serves as the interface for the program.
// It contains a private member of AVLTree to manage the courses.

class CourseManager {
private:
    AVLTree courseTree;

public:
    

    // Constructor
    CourseManager() : courseTree() {}

    // Public methods
    
    bool isValidCourseID(const std::string& str);
    void parseLine(std::string line);
    void readAndParse(std::string fileName);
    void validatePrerequisites();
    void printCourseInfo(std::string courseID);
    void printAlphanumeric();
};

#endif // COURSEMANAGER_HPP
