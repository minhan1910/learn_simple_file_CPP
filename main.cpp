#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include "Utils.h"

const char * INPUT_ERROR_STRING = "Input Error! Please Try Again!";
const int MAX_NAME_SIZE = 40;
const char * STUDENTS_FILE_NAME = "Students.bin";

struct Student{

	int studentId;
	
	char firstName[256];
	
	char lastName[256];
	
	int age;
	
	float gpa;

};

struct StudentDB {
	Student * students;
	int numberOfStudents;
	int capacity;
};

char GetOptionFromUser();
void ExecuteOption(const char option, StudentDB& studentDB);
void AddStudent(StudentDB& studentDB);
void DisplayStudents(StudentDB& studentDB);
void ResizeArrayStudents(StudentDB& studentDB, const int newCapacity);
bool LoadStudents(StudentDB& studentDB);
void SaveStudents(StudentDB& studentDB);
void CreateStudentFile();
void InitializeStudentDB(StudentDB& studentDB);
void SaveStudents(StudentDB& studentDB);

int main(int argc, char** argv) {		
		
	char option;	
	
	StudentDB studentDB;
	InitializeStudentDB(studentDB);
	
	CreateStudentFile();
	
	if (!LoadStudents(studentDB)) {
		std::cout << "ERROR Reading File " << STUDENTS_FILE_NAME << std::endl;
		return 0;
	}
		
	do {
		option = GetOptionFromUser();
		
		
		ExecuteOption(option, studentDB);
	} while (option != 'q');
	
	SaveStudents(studentDB);

	return 0;
}

char GetOptionFromUser() {
	char options[] = { 'a', 'd', 'q'};
	
	return GetCharacter("The options:\n(A)dd New Student\n(D)isplay All Student\n(Q)uit\n\nWhat is your choice: ", INPUT_ERROR_STRING, options, 3, CC_LOWER_CASE);	
}

void ExecuteOption(const char option, StudentDB& studentDB) {
	switch (option) {
		case 'a':
			AddStudent(studentDB);
		break;
		
		case 'd':
			DisplayStudents(studentDB);
		break;
		
		default:
		break;
	}
}

void AddStudent(StudentDB& studentDB) {
	
	if (studentDB.numberOfStudents == studentDB.capacity) {
		ResizeArrayStudents(studentDB, studentDB.capacity * 2 + 10);
	}
	
	
	int idxStudent = studentDB.numberOfStudents,
		idStudent = idxStudent + 1;
	
	studentDB.students[idxStudent].studentId = idStudent;
	GetString("Enter first name: ", INPUT_ERROR_STRING, studentDB.students[idxStudent].firstName, MAX_NAME_SIZE);
	GetString("Enter last name: ", INPUT_ERROR_STRING, studentDB.students[idxStudent].lastName, MAX_NAME_SIZE);
	
	std::cout << "Enter your age: ";
	std::cin >> studentDB.students[idxStudent].age;
	
	std::cout << "Enter your gpa: ";
	std::cin >> studentDB.students[idxStudent].gpa;
	
	++studentDB.numberOfStudents;
	
	SaveStudents(studentDB);
	
	std::cout << "Saved!" << std::endl;
}

void DisplayStudents(StudentDB& studentDB) {
	for (int i = 0; i < studentDB.numberOfStudents; ++i) {
		std::cout << "ID: " << studentDB.students[i].studentId << std::endl;
		std::cout << "Fullname: " << studentDB.students[i].firstName << ' ' << studentDB.students[i].lastName << std::endl;
		std::cout << "Age: " << studentDB.students[i].age << std::endl;
		std::cout << "Gpa: " << studentDB.students[i].gpa << std::endl << std::endl;
	}
}

void ResizeArrayStudents(StudentDB& studentDB, const int newCapacity) {
	Student * newStudents = new Student[newCapacity];
	
	for (int i = 0; i < studentDB.numberOfStudents; ++i) {
		if (studentDB.students != nullptr) {
			newStudents[i].studentId = studentDB.students[i].studentId;
			strcpy(newStudents[i].firstName, studentDB.students[i].firstName);
			strcpy(newStudents[i].firstName, studentDB.students[i].lastName);
			newStudents[i].age =  studentDB.students[i].age;
			newStudents[i].gpa =  studentDB.students[i].gpa;
		}
	}
	
	if (studentDB.students != nullptr) {
		delete [] studentDB.students;
		studentDB.students = nullptr;
	}
	
	studentDB.students = newStudents;
	studentDB.capacity = newCapacity;
}

bool LoadStudents(StudentDB& studentDB) {
	std::ifstream inFile;
	
	inFile.open(STUDENTS_FILE_NAME, std::fstream::binary);
	
	if (inFile.is_open()) {
		
		inFile.seekg(0, inFile.end);
		int lengthFileInBytes = inFile.tellg();
		inFile.seekg(0, inFile.beg);
		
		int numberOfStudents = lengthFileInBytes / sizeof(Student);
		int capacity = numberOfStudents * 2 + 10;
		
		studentDB.students = new Student[capacity];
		studentDB.capacity = capacity;
		studentDB.numberOfStudents = numberOfStudents;
		
		inFile.read((char*) studentDB.students, lengthFileInBytes);
		
		inFile.close();
		
		return true;
	}
	
	return false;
}

void SaveStudents(StudentDB& studentDB) {
	std::ofstream outFile;
	
	outFile.open(STUDENTS_FILE_NAME, std::fstream::binary);
	
	if (outFile.is_open()) {
		
		outFile.write((char *) studentDB.students, studentDB.numberOfStudents * sizeof(Student));
		
		outFile.close();
	}
}

void CreateStudentFile() {
		std::ifstream inFile;
		
		inFile.open(STUDENTS_FILE_NAME, std::fstream::binary);
		
		if (!inFile.is_open()) {
			std::ofstream outFile;
			outFile.open(STUDENTS_FILE_NAME, std::fstream::binary);
			outFile << std::flush;
			outFile.close();
		} else {
			inFile.close();
		}		
}

void InitializeStudentDB(StudentDB& studentDB) {
	studentDB.capacity = 0;
	studentDB.numberOfStudents = 0;
	studentDB.students = nullptr;
}