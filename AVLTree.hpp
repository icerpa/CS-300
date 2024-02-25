#ifndef AVLTREE_HPP
#define AVLTREE_HPP

//AVLTree.hpp
//Ivette Cerpa

#include <string>
#include <vector>

class AVLTree {
public:
    struct Course {
        std::string courseID;
        std::string courseName;
        std::vector<std::string> prerequisites;

        // Constructor
        Course(std::string id, std::string name, std::vector<std::string> prereqs)
            : courseID(id), courseName(name), prerequisites(prereqs) {}
    };

    struct Node {
        std::string key;
        Course value;
        Node* leftChild;
        Node* rightChild;
        int height;

        // Constructor
        Node(std::string courseKey, Course courseValue)
            : key(courseKey), value(courseValue), leftChild(nullptr), rightChild(nullptr), height(1) {}
    };

private:
    Node* root;

    // Helper methods
    void destroy(Node* node);
    Node* rotateRight(Node* oldRoot);
    Node* rotateLeft(Node* oldRoot);
    int height(Node* node);
    int getBalance(Node* node);
    Node* insert(Node* node, std::string key, Course value);
    Node* Search(std::string courseID);
    void printAlphanumeric(Node* node);
    bool validatePrerequisites(Node* node);
    

public:
    // Constructor
    AVLTree() {
        root = nullptr;
    }

    // Desctructor
    ~AVLTree();
    

    // Public methods
    void insert(std::string key, Course value);
    void printCourseInfo(std::string courseID);
    void printAlphanumeric() {
        printAlphanumeric(root);
    }
    bool validatePrerequisites() {
        return validatePrerequisites(root);
    }
};

#endif // AVLTREE_HPP
