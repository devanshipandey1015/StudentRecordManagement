#include <iostream>
#include <unordered_map>
#include <list>
#include <string>

using namespace std;

// this is a linkedlist. here we are storing course data.


struct Course {
    string courseName;
    string grade;
    Course* next;
    Course(string cName, string g) : courseName(cName), grade(g), next(nullptr) {}
};

// binary search tree to sort students based on cgpa

struct Student {
    int id;
    string name;
    float gpa;
    Course* courseHistory; // Linked list of courses
    Student* left;
    Student* right;
    
    Student(int i, string n, float g) : id(i), name(n), gpa(g), courseHistory(nullptr), left(nullptr), right(nullptr) {}
};


// hash table is used for storing our student id

unordered_map<int, Student*> studentHashTable;

//  function for inserting student data into BST

Student* insertStudentBST(Student* root, Student* newStudent) {
    if (!root) return newStudent;
    if (newStudent->gpa < root->gpa) root->left = insertStudentBST(root->left, newStudent);
    else root->right = insertStudentBST(root->right, newStudent);
    return root;
}

// FUNCTION FOR DISPLAYING COURSE HISTORY 

void displayCourseHistory(Course* courseHead) {
    Course* temp = courseHead;
    while (temp) {
        cout << "Course: " << temp->courseName << ", Grade: " << temp->grade << endl;
        temp = temp->next;
    }
}

// Func for student data


void displayStudentData(Student* student) {
    if (!student) return;
    cout << "ID: " << student->id << ", Name: " << student->name << ", GPA: " << student->gpa << endl;
    cout << "Course History: " << endl;
    displayCourseHistory(student->courseHistory);
    cout << "-----------------------------" << endl;
}

// traversal to show student data - inorder

void displayAllStudents(Student* root) {
    if (!root) return;
    displayAllStudents(root->left);
    displayStudentData(root);
    displayAllStudents(root->right);
}

// to add new course

void addCourse(Student* student, string courseName, string grade) {
    Course* newCourse = new Course(courseName, grade);
    newCourse->next = student->courseHistory;
    student->courseHistory = newCourse;
}

// to add new student

Student* addStudent(Student* bstRoot) {
    int id;
    string name;
    float gpa;
    
    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Student Name: ";
    cin >> name;
    cout << "Enter GPA: ";
    cin >> gpa;

    //  new student
    Student* newStudent = new Student(id, name, gpa);

    // inserting in hash table

    studentHashTable[id] = newStudent;

    // inserting in binary tree

    bstRoot = insertStudentBST(bstRoot, newStudent);

    // adding courses
    int numCourses;
    cout << "Enter number of courses: ";
    cin >> numCourses;
    for (int i = 0; i < numCourses; ++i) {
        string courseName, grade;
        cout << "Enter course name and grade: ";
        cin >> courseName >> grade;
        addCourse(newStudent, courseName, grade);
    }

    return bstRoot;
}

// to search for student by ID

void searchStudentById(int id) {
    if (studentHashTable.find(id) != studentHashTable.end()) {
        displayStudentData(studentHashTable[id]);
    } else {
        cout << "Student with ID " << id << " not found." << endl;
    }
}

// main

int main() {
    Student* bstRoot = nullptr;
    int choice, id;

    do {
        cout << "Student Record Management System" << endl;
        cout << "1. Add Student" << endl;
        cout << "2. Display All Students (sorted by GPA)" << endl;
        cout << "3. Search Student by ID" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                bstRoot = addStudent(bstRoot);
                break;
            case 2:
                displayAllStudents(bstRoot);
                break;
            case 3:
                cout << "Enter Student ID to search: ";
                cin >> id;
                searchStudentById(id);
                break;
            case 4:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
