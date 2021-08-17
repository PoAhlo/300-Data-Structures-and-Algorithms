#include <iostream>
#include <fstream>
#include <vector>
#include <limits>

#include "binary_search_tree.h"


// struct to hold course information
struct Course {
	std::string course_num;
	std::string name;
	std::vector<std::string> prerequisites;
};


int main() {
	int user_choice = 0;
	std::string course_num;
	std::string file_name;
	BinarySearchTree bst;
	Course course;

	std::cout << "Welcome to ABCU Advising Assistance Program" << std::endl;

	while (user_choice != 4) {

		// print the menu
		std::cout << std::endl;
		std::cout << "Choose from the following options:" << std::endl;
		std::cout << "1. Load Courses Into Program" << std::endl;
		std::cout << "2. Print Full Course List" << std::endl;
		std::cout << "3. Search for a Course" << std::endl;
		std::cout << "4. Exit" << std::endl;

		try {
			// Propt for user input
			std::cout << std::endl;
			std::cout << "Enter your selection.  Type only the number: " << std::endl;
			std::cin >> user_choice;
			std::cout << std::endl;

			//makes sure the input is a number
			if (std::cin.fail()) {
				std::cin.clear();
				std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
				throw std::runtime_error("Not a number");
			}
			// makes sure the input is within range
			if (user_choice < 1 || user_choice > 4) {
				throw std::runtime_error("Invalid number");
			}
		}
		catch (std::runtime_error& excpt) {
			std::cout << excpt.what() << std::endl;
			std::cout << "Please try again." << std::endl;
		}

		switch (user_choice) {

		// Load courses
		case 1:
			std::cout << "Enter file name: " << std::endl;
			std::cin >> file_name;
			bst.ParseFile(file_name);
			break;

		// Print course list
		case 2: 
			bst.PrintInOrder();
			break;

		// search for a course
		case 3: 
			std::cout << "Enter Course Number (case sensitive): " << std::endl;
			std::cin >> course_num;
			std::cout << std::endl;

			//search for the course
			course = bst.Search(course_num);

			// if the course is found, print the information
			if (!course.course_num.empty()) {
				// Prints the course information
				std::cout << course.course_num << ", ";
				std::cout << course.name << std::endl;
				std::cout << "         Prerequisites: ";
				// Prints the prerequisites, if any.
				if (course.prerequisites.size() == 0) {
					std::cout << "None" << std::endl;
					std::cout << std::endl;
				}
				else {
					// prints all but the last prerequisite
					for (int i = 0; i < course.prerequisites.size() - 1; i++) {
						std::cout << course.prerequisites.at(i) << ", ";
					}
					//prints the last prerequisite without the commma
					std::cout << course.prerequisites.back() << std::endl;
					std::cout << std::endl;
				}
			}
			// if the course is not found, print message
			else {
				std::cout << "Course not found." << std::endl;
			}
			break;
		}
	}
	return 0;
}

