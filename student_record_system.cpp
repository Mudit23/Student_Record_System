#include <iostream>
#include <fstream>
using namespace std;

class Student {
    string rollNo;
    string name;
    float marks;
public:
    void input() {
        cout << "Enter Roll No: ";
        cin >> rollNo;
        cin.ignore();
        cout << "Enter Name: ";
        getline(cin, name);
        cout << "Enter Marks: ";
        cin >> marks;
    }

    void display() const {
        cout << "Roll No: " << rollNo << endl;
        cout << "Name   : " << name << endl;
        cout << "Marks  : " << marks << endl;
        cout << "------------------------" << endl;
    }

    string getRollNo() const { return rollNo; }
    string getName() const { return name; }
    float getMarks() const { return marks; }
};

void addStudent() {
    Student s;
    s.input();
    string newRoll = s.getRollNo();

    ifstream in("students.txt");
    string line;
    bool exists = false;

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        if (pos1 == string::npos) continue;
        string roll = line.substr(0, pos1);
        if (roll == newRoll) {
            exists = true;
            break;
        }
    }
    in.close();

    if (exists) {
        cout << "Error: Roll number already exists. Cannot add duplicate record.\n";
        return;
    }

    ofstream out("students.txt", ios::app);
    if (!out) {
        cerr << "Error opening file!" << endl;
        return;
    }

    out << s.getRollNo() << "|" << s.getName() << "|" << s.getMarks() << "\n";
    out.close();

    cout << "Student added successfully.\n";
}


void displayStudents() {
    ifstream in("students.txt");
    if (!in) {
        cerr << "Error reading file!" << endl;
        return;
    }

    string line;
    cout << "\n-- Student Records --\n";

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string roll = line.substr(0, pos1);
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        float marks = stof(line.substr(pos2 + 1));

        cout << "Roll No: " << roll << endl;
        cout << "Name   : " << name << endl;
        cout << "Marks  : " << marks << endl;
        cout << "------------------------" << endl;
    }

    in.close();
}

void searchStudent(const string& rollToFind) {
    ifstream in("students.txt");
    string line;
    bool found = false;

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        size_t pos2 = line.find('|', pos1 + 1);

        if (pos1 == string::npos || pos2 == string::npos) continue;

        string roll = line.substr(0, pos1);
        string name = line.substr(pos1 + 1, pos2 - pos1 - 1);
        float marks = stof(line.substr(pos2 + 1));

        if (roll == rollToFind) {
            cout << "\nStudent Found:\n";
            cout << "Roll No: " << roll << endl;
            cout << "Name   : " << name << endl;
            cout << "Marks  : " << marks << endl;
            found = true;
            break;
        }
    }

    in.close();
    if (!found) cout << "Student not found.\n";
}

void deleteStudent(const string& rollToDelete) {
    ifstream in("students.txt");
    ofstream out("temp.txt");
    string line;
    bool deleted = false;

    while (getline(in, line)) {
        size_t pos1 = line.find('|');
        string roll = line.substr(0, pos1);

        if (roll != rollToDelete) {
            out << line << "\n";
        } else {
            deleted = true;
        }
    }

    in.close();
    out.close();
    remove("students.txt");
    rename("temp.txt", "students.txt");

    if (deleted)
        cout << "Record deleted.\n";
    else
        cout << "Roll number not found.\n";
}

int main() {
    int choice;
    string roll;

    do {
        cout << "\n--- Student Record Menu ---\n";
        cout << "1. Add Student\n2. Display All\n3. Search Student\n4. Delete Student\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
            case 1: addStudent(); break;
            case 2: displayStudents(); break;
            case 3:
                cout << "Enter Roll No to search: ";
                getline(cin, roll);
                searchStudent(roll);
                break;
            case 4:
                cout << "Enter Roll No to delete: ";
                getline(cin, roll);
                deleteStudent(roll);
                break;
            case 5:
                cout << "Exiting...\n"; break;
            default:
                cout << "Invalid choice!\n";
        }
    } while (choice != 5);

    return 0;
}
