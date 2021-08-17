#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>

#include "binary_search_tree.h"


// struct to hold course information
struct Course {
    std::string course_num;
    std::string name;
    std::vector<std::string> prerequisites;
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course t_course) : Node() {
        course = t_course;
    }
};

/**
 * Default Constructor
 */
BinarySearchTree::BinarySearchTree() {
    root_ = nullptr;
}

/**
 * Copy Constructor
 */
BinarySearchTree::BinarySearchTree(BinarySearchTree& source) {
    if (source.root_ == nullptr) {
        root_ = nullptr;
    }
    else {
        CopyTree(this->root_, source.root_);
    }
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    if (root_ != nullptr) {
        delete root_->right;
        delete root_->left;
        delete root_;
    }
}

/**
 * Copy assignement operator
 */
BinarySearchTree& BinarySearchTree::operator= (const BinarySearchTree& source) {
    if (this != &source) {
        this->Clear();
        Node* node = source.root_;
        AssignmentOperator(node);
    }
    return *this;
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root is null, the course becomes the first node on the tree
    if (root_ == nullptr) {
        root_ = new Node(course);
    }
    // else, use the AddNodeHelper function to appropriately add the course to the tree
    else {
        this->AddNodeHelper(root_, course);
    }
}

/**
 * Traverse the tree in order
 */
void BinarySearchTree::PrintInOrder() {
    this->PrintInOrderHelper(root_);
}

/**
 * Searches for a course
 * 
 * @return matching course, otherwise return empty course
 */
Course BinarySearchTree::Search(std::string course_num) {
    Node* curr = root_;
    Course match;

    // while there are still nodes left to compare
    while (curr != nullptr) {
        // if the course numbers match, return the matching course
        if (course_num == curr->course.course_num) {
            match = curr->course;
            break;
        }
        // if the course num is smaller, follow the left child
        else if (course_num < curr->course.course_num) {
            curr = curr->left;
        }
        // if the course num is larger, follow the right child
        else if (course_num > curr->course.course_num) {
            curr = curr->right;
        }
    }
    return match;
}

/**
 * Parses a file, loading its contents into the tree
 */
void BinarySearchTree::ParseFile(std::string file_name) {
    std::ifstream in_file_stream; // input file stream
    std::string line;
    std::string parameter;
    std::vector<std::string> course_info;
    std::vector<std::string> all_prerequisites;
    size_t found;
    Course blank; // used to reset the course in the while loop


    try {
        // attempt to open file 
        in_file_stream.open(file_name);
        if (!in_file_stream.is_open()) {
            throw std::runtime_error("File could not be opened");
        }
        // continues to read lines until the end of the file
        while (std::getline(in_file_stream, line)) {
            // reads the line and checks to make sure there are enough parameters
            found = line.find(","); // looks for the first comma

            //if there is no comma in the line
            if (found == std::string::npos) {
                throw std::runtime_error("Invalid information: Line has too few arguments");
            }

            //makes sure courseInfo is empty
            course_info.clear();

            // adds the parameter to a vector of course information
            // for each letter
            for (int i = 0; i < line.length(); i++) {
                // if the letter is a comma, adds the parameter to courseInfo
                if (line[i] == ',') {
                    course_info.push_back(parameter);
                    parameter = "";
                }
                // otherwise, appends the letter to parameter
                else {
                    parameter += line[i];
                }
            }
            // leftover information gets added to courseInfo
            course_info.push_back(parameter);
            parameter = "";

            // make sure newCourse is an empty course
            Course new_course = blank; 

            // transfers the courseInfo from vector to the course
            for (int i = 0; i < course_info.size(); i++) {
                // first the courseNum
                if (i == 0) {
                    new_course.course_num = course_info.at(i);
                }
                // then the course name
                else if (i == 1) { 
                    new_course.name = course_info.at(i);
                }
                // finally the prerequisites
                else { 
                    new_course.prerequisites.push_back(course_info.at(i));
                    all_prerequisites.push_back(course_info.at(i));
                }
            }
            // adds the course to the three.
            this->Insert(new_course);
        }
        // after all the courses have been entered, validate the prerequisites
        for (int i = 0; i < all_prerequisites.size(); i++) {
            if (this->IsValid(all_prerequisites.at(i)) == false) {
                throw std::runtime_error("Invalid Prerequisite");
            }
        }
    }
    catch (std::runtime_error& excpt) {
        std::cout << excpt.what() << std::endl;
        std::cout << "Cannot Parse File." << std::endl;
    }
    std::cout << "Courses Successfully loaded" << std::endl;
}

/**
 * Add a course to appropriate node (recursive)
 *
 * @param node - current node in the tree
 * @param course - course to be added
 */
void BinarySearchTree::AddNodeHelper(Node* node, Course course) {
    // if the course is smaller, add to the left
    if (course.course_num < node->course.course_num) {
        // if the left node is empty, course gets added to the left
        if (node->left == nullptr) {
            node->left = new Node(course);
        }
        // if there is a left node, recurse down the left node
        else {
            this->AddNodeHelper(node->left, course);
        }
    }
    // if the course is larger, add to the right
    else {
        // if the right node is empty, course gets added to the right
        if (node->right == nullptr) {
            node->right = new Node(course);
        }
        // if there is a right node, recurse down the right node
        else {
            this->AddNodeHelper(node->right, course);
        }
    }
}

/**
 * Prints all the courses in the tree in order (recursive)
 */
void BinarySearchTree::PrintInOrderHelper(Node* node) {
    // recursively calls inOrder, printing nodes as they're found
    if (node != nullptr) {
        PrintInOrderHelper(node->left);

        // Prints the course information
        std::cout << node->course.course_num << ", ";
        std::cout << node->course.name << std::endl;
        std::cout << "         Prerequisites: ";
        // Prints the prerequisites, if any.
        if (node->course.prerequisites.size() == 0) {
            std::cout << "None" << std::endl;
            std::cout << std::endl;
        }
        else {
            // prints all but the last prerequisite
            for (int i = 0; i < node->course.prerequisites.size() - 1; i++) {
                std::cout << node->course.prerequisites.at(i) << ", ";
            }
            //prints the last prerequisite without the commma
            std::cout << node->course.prerequisites.back() << std::endl;
            std::cout << std::endl;
        }

        PrintInOrderHelper(node->right);
    }
}

/**
 * Checks to see that a course (a prerequisite) is a valid course in the tree
 */
bool BinarySearchTree::IsValid(std::string course_num) {
    // if cannot find the course, return false.
    if (this->Search(course_num).course_num == "") {
        return false;
    }
    return true;
}

/**
 * Copies a tree
 */
void BinarySearchTree::CopyTree(Node*& this_root, Node*& source_root) {
    if (source_root == nullptr) {
        this_root = nullptr;
    }
    else {
        this_root = new Node;
        this_root->course = source_root->course;
        CopyTree(this_root->left, source_root->left);
        CopyTree(this_root->right, source_root->right);
    }
}

/**
 * Clears a tree, but not fully deletes it
 */
void BinarySearchTree::Clear() {
    delete root_->left;
    delete root_->right;
    root_ = nullptr;
}

/**
 * Builds a tree to match the source tree (recursive)
 */
void BinarySearchTree::AssignmentOperator(Node* node) {
    this->Insert(node->course);

    if (node->left != nullptr) {
        AssignmentOperator(node->left);
    }
    if (node->right != nullptr) {
        AssignmentOperator(node->right);
    }
}