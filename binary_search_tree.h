#ifndef BINARY_SEARCH_TREE_H
#define BINARY_SEARCH_TREE_H

struct Course;
struct Node;

class BinarySearchTree {
private:
	Node* root_;

	void AddNodeHelper(Node* node, Course course);
	void PrintInOrderHelper(Node* node);
	bool IsValid(std::string course_num);
	void CopyTree(Node*& this_root, Node*& source_root);
	void Clear();
	void AssignmentOperator(Node* node);

public:
	BinarySearchTree();

	BinarySearchTree(BinarySearchTree& source);
	~BinarySearchTree();
	BinarySearchTree& operator= (const BinarySearchTree& source);

	void Insert(Course course);
	void PrintInOrder();
	Course Search(std::string course_num);
	void ParseFile(std::string filename);

};

#endif 
