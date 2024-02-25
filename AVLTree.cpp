//========================================================================================
//                          CS-300: Project Two
// 
// Name        : AVLTree.cpp
// Author      : Ivette Cerpa
// Version     : 1.0
// Description : This file contains the implementation of an AVL Tree, a self-balancing
//               binary search tree. The AVL Tree maintains its balance by keeping track
//               of a balance factor for each node and performing rotations when a node's
//               balance factor indicates that the tree is unbalanced. The file includes
//               functions for inserting a node, rotating subtrees to the left and right,
//               getting the height of a node, getting the balance factor of a node, and
//               destroying the tree. Additionally, it includes functions to search for a
//               course in the tree, print all courses in alphanumeric order, validate
//               that all prerequisites of all courses exist in the tree, and print the
//               information of a specific course.
//========================================================================================

#include "AVLTree.hpp"
#include <iostream>
#include <algorithm>  // for transform

using namespace std;

//============================================================================
// Private functions of the AVLTree Class
//============================================================================

/**
 * Function to destroy the AVL tree
 *
 * @param node the root of the tree to destroy
 */
void AVLTree::destroy(Node* node) {
    if (node != nullptr) {
        destroy(node->leftChild);
        destroy(node->rightChild);
        delete node;
    }
}

/**
 * Function to right rotate subtree rooted with oldRoot
 *
 * @param oldRoot the root of the subtree to rotate
 * @return a pointer to the new root after rotation
 */
AVLTree::Node* AVLTree::rotateRight(Node* oldRoot) {
    Node* newRoot = oldRoot->leftChild;
    Node* transferredSubtree = newRoot->rightChild;

    // Perform rotation
    newRoot->rightChild = oldRoot;
    oldRoot->leftChild = transferredSubtree;

    // Update heights
    oldRoot->height = max(height(oldRoot->leftChild), height(oldRoot->rightChild)) + 1;
    newRoot->height = max(height(newRoot->leftChild), height(newRoot->rightChild)) + 1;

    // Return new root
    return newRoot;
}

/**
 * Function to left rotate subtree rooted with oldRoot
 *
 * @param oldRoot the root of the subtree to rotate
 * @return a pointer to the new root after rotation
 */
AVLTree::Node* AVLTree::rotateLeft(Node* oldRoot) {
    Node* newRoot = oldRoot->rightChild;
    Node* transferredSubtree = newRoot->leftChild;

    // Perform rotation
    newRoot->leftChild = oldRoot;
    oldRoot->rightChild = transferredSubtree;

    // Update heights
    oldRoot->height = max(height(oldRoot->leftChild), height(oldRoot->rightChild)) + 1;
    newRoot->height = max(height(newRoot->leftChild), height(newRoot->rightChild)) + 1;

    // Return new root
    return newRoot;
}


/**
 * Function to get the height of the node
 *
 * @param node the node whose height is to be determined
 * @return the height of the node
 */
int AVLTree::height(Node* node) {
    if (node == nullptr)
        return 0;
    return node->height;
}

/**
 * Function to get balance factor of the node
 *
 * @param node the node whose balance factor is to be determined
 * @return the balance factor of the node
 */
int AVLTree::getBalance(Node* node) {
    if (node == nullptr)
        return 0;
    return height(node->leftChild) - height(node->rightChild);
}

/**
 * Function to insert a new node with given key and value in the AVL tree
 *
 * @param node the root of the tree
 * @param key the key of the new node
 * @param value the value of the new node
 * @return a pointer to the root of the tree after insertion
 */
AVLTree::Node* AVLTree::insert(Node* node, string key, Course value) {
    // Perform normal BST insertion
    if (node == nullptr)
        return new Node(key, value);

    if (key < node->key)
        node->leftChild = insert(node->leftChild, key, value);
    else if (key > node->key)
        node->rightChild = insert(node->rightChild, key, value);
    else // Equal keys are not allowed in BST
        return node;

    // Update height of this ancestor node
    node->height = 1 + max(height(node->leftChild), height(node->rightChild));

    // Get the balance factor
    int balance = getBalance(node);

    // If this node becomes unbalanced, then there are 4 cases

    // Left Left Case
    if (balance > 1 && key < node->leftChild->key)
        return rotateRight(node);

    // Right Right Case
    if (balance < -1 && key > node->rightChild->key)
        return rotateLeft(node);

    // Left Right Case
    if (balance > 1 && key > node->leftChild->key) {
        node->leftChild = rotateLeft(node->leftChild);
        return rotateRight(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->rightChild->key) {
        node->rightChild = rotateRight(node->rightChild);
        return rotateLeft(node);
    }

    // Return the (unchanged) node pointer
    return node;
}

/**
 * Function to search for a course in the AVL tree
 *
 * @param courseID the ID of the course to search for
 * @return a pointer to the Node containing the course, or nullptr if the course is not found
 */
AVLTree::Node* AVLTree::Search(string courseID) {
    // Convert courseID to upper case
    transform(courseID.begin(), courseID.end(), courseID.begin(), ::toupper);

    Node* current = root;
    while (current != nullptr) {
        string currentKey = current->key;
        // Convert currentKey to upper case
        transform(currentKey.begin(), currentKey.end(), currentKey.begin(), ::toupper);

        if (courseID < current->key)
            current = current->leftChild;
        else if (courseID > current->key)
            current = current->rightChild;
        else
            return current;  // Found the course
    }
    return nullptr;  // Course not found
}

/**
 * Function to print all courses in the AVL tree in alphanumeric order
 *
 * @param node is a pointer to the Node to start printing from 
 */
void AVLTree::printAlphanumeric(Node* node) {
    if (node != nullptr) {
        printAlphanumeric(node->leftChild);
        cout << "Course ID: " << node->value.courseID << ", Course Name: " << node->value.courseName << endl;
        printAlphanumeric(node->rightChild);
    }
}

/**
 * Function to validate that all prerequisites of all courses exist in the AVL tree
 *
 * @param node is a pointer to the Node to start validating from
 * @return true if all prerequisites are valid, false otherwise
 */
bool AVLTree::validatePrerequisites(Node* node) {
    if (node != nullptr) {
        for (const auto& prereq : node->value.prerequisites) {
            if (Search(prereq) == nullptr) {
                //cout << "Prerequisite course for " << node->value.courseID << " is missing an entry" << endl;
                return false;
            }
        }
        // Recursively validate prerequisites in the left and right subtrees
        if (!validatePrerequisites(node->leftChild) || !validatePrerequisites(node->rightChild)) {
            return false;
        }
    }
    return true;
}


//============================================================================
// Public functions of the AVLTree Class
//============================================================================

/**
 * Destructor for the AVLTree class
 */
AVLTree::~AVLTree() {
    destroy(root);
}

/**
 * Function to insert a new course into the AVL tree
 *
 * @param key the ID of the course to insert
 * @param value the Course object to insert
 */
void AVLTree::insert(string key, Course value) {
    root = insert(root, key, value);
}

/**
 * Function to print the information of a specific course
 *
 * @param courseID the ID of the course to print
 */
void AVLTree::printCourseInfo(std::string courseID) {
    Node* courseNode = Search(courseID);
    if (courseNode != nullptr) {
        cout << "Course ID: " << courseNode->value.courseID << ", Course Name: " << courseNode->value.courseName << endl;
        if (!courseNode->value.prerequisites.empty()) {
            cout << "Prerequisites: ";
            for (const auto& prereq : courseNode->value.prerequisites) {
                cout << prereq << " ";
            }
            cout << endl;
        }
        else {
            cout << "Prerequisites: None" << endl;
        }
    }
    else {
        cout << "Course not found." << endl;
    }
}
