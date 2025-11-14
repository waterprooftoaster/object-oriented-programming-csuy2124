/*
    Andy Wu
cw4483
spring 2025
  rec05-start.cpp

  Remember that the file you are to submit should be named rec05.cpp.
  And YOUR NAME should appear up here in the comment.
 */

#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Section {
    friend ostream &operator<<(ostream &os, const Section &sec);
    class StudentRecord {
        friend ostream &operator<<(ostream &os, const StudentRecord &sec);

    public:
        StudentRecord(const string &theStudentName)
            : studentname(theStudentName), grades(14, -1) {
        }

        const string &getStudentName() const { return studentname; }

        void setStudentGrade(int theGrade, size_t labCount) {
            grades[labCount - 1] = theGrade;
        }

    private:
        string studentname;
        vector<int> grades;
    };

    friend ostream &operator<<(ostream &os, const Section::StudentRecord &sec);

    class TimeSlot {
        friend ostream &operator<<(ostream &os, const TimeSlot &sec);

    public:
        TimeSlot(const string &theDay, int theStartTime)
            : day(theDay), starttime(theStartTime) {
        }

    private:
        string day;
        int starttime;
    };
    friend ostream &operator<<(ostream &os, const Section::TimeSlot &sec);
public:

    Section(const string &theSecName, const string &theDay, int theStartTime)
        : secname(theSecName), slot(theDay, theStartTime) {
    }

    Section(const Section &anotherSection)
        : secname(anotherSection.secname), slot(anotherSection.slot) {
        for (size_t i = 0; i < anotherSection.records.size(); i++) {
            records.push_back(new StudentRecord(*anotherSection.records[i]));
        }
    }

    // vector<StudentRecord*> &getRecord() {
    //     return records;
    // }

    bool addGrade (const string &theStudentName, int theGrade, size_t labCount) {
        for (StudentRecord* recordp: records) {
            if (recordp->getStudentName() == theStudentName) {
                recordp->setStudentGrade(theGrade, labCount);
                return true;
            }
        }
        return false;
    }

    void addStudent(const string &theStudentName) {
        records.push_back(new StudentRecord(theStudentName));
    }

    ~Section() {
        cout << "section " << secname << " is being deleted" << endl;
        for (StudentRecord * recordp: records) {
            cout << "deleting " << recordp->getStudentName() << endl;
            delete recordp;
        }
    }

private:
    string secname;
    TimeSlot slot;
    vector<StudentRecord *> records;
};

class LabWorker {
    friend ostream &operator<<(ostream &os, const LabWorker &worker);

public:
    LabWorker(const string &theName) : name(theName), sec(nullptr) {
    }

    void addSection(Section &theSec) { sec = &theSec; }

    bool addGrade(const string &theStudentName, int theGrade, size_t labCount) {
        if (sec == nullptr) {
            cerr << "labworker does not have a section" << endl;
            return false;
        }
        sec -> addGrade(theStudentName, theGrade, labCount);
        return true;
    }

private:
    string name;
    Section *sec;
};

//labworker operator overload
ostream &operator<<(ostream &os, const LabWorker &worker) {
    if (!worker.sec) {
        os << worker.name << " does not have a section" << endl;
        return os;
    } else {
        os << worker.name << " has " << *worker.sec;
        return os;
    }
}

//section operator overload
ostream &operator<<(ostream &os, const Section &sec) {
    os << "Section " << sec.secname << ", ";
    os << sec.slot << endl;

    for (const Section::StudentRecord* recordp: sec.records) {
        os << *recordp;
    }
    return os;
}

// timeslot output operator
ostream &operator<<(ostream &os, const Section::TimeSlot &sec) {
    os << "Time slot: [Day: " << sec.day
            << ", Start time: ";
    if (sec.starttime > 12) {
        os << sec.starttime - 12 << "pm";
    } else {
        os << sec.starttime << "am";
    }
    os << "], Students:" << endl;
    return os;
}


// student record output operator
ostream &operator<<(ostream &os, const Section::StudentRecord &sec_student_record) {
    os << "Name: " << sec_student_record.studentname << ", Grades:";
    for (int curr_grade: sec_student_record.grades) {
        os << " " << curr_grade;
    }
    os << endl;
    return os;
}

// Test code
void doNothing(const Section &sec) { cout << sec << endl; }

int main() {
    cout << "Test 1: Defining a section\n";
    Section secA2("A2", "Tuesday", 16);
    cout << secA2 << endl;

    cout << "\nTest 2: Adding students to a section\n";
    secA2.addStudent("John");
    secA2.addStudent("George");
    secA2.addStudent("Paul");
    secA2.addStudent("Ringo");
    cout << secA2 << endl;

    cout << "\nTest 3: Defining a lab worker.\n";
    LabWorker moe("Moe");
    cout << moe << endl;

    cout << "\nTest 4: Adding a section to a lab worker.\n";
    moe.addSection(secA2);
    cout << moe << endl;

    cout << "\nTest 5: Adding a second section and lab worker.\n";
    LabWorker jane("Jane");
    Section secB3("B3", "Thursday", 11);
    secB3.addStudent("Thorin");
    secB3.addStudent("Dwalin");
    secB3.addStudent("Balin");
    secB3.addStudent("Kili");
    secB3.addStudent("Fili");
    secB3.addStudent("Dori");
    secB3.addStudent("Nori");
    secB3.addStudent("Ori");
    secB3.addStudent("Oin");
    secB3.addStudent("Gloin");
    secB3.addStudent("Bifur");
    secB3.addStudent("Bofur");
    secB3.addStudent("Bombur");
    jane.addSection(secB3);
    cout << jane << endl;

    cout << "\nTest 6: Adding some grades for week one\n";
    moe.addGrade("John", 17, 1);
    moe.addGrade("Paul", 19, 1);
    moe.addGrade("George", 16, 1);
    moe.addGrade("Ringo", 7, 1);
    cout << moe << endl;

    cout << "\nTest 7: Adding some grades for week three (skipping week 2)\n";
    moe.addGrade("John", 15, 3);
    moe.addGrade("Paul", 20, 3);
    moe.addGrade("Ringo", 0, 3);
    moe.addGrade("George", 16, 3);
    cout << moe << endl;

    cout << "\nTest 8: We're done (almost)! \nWhat should happen to all "
            << "those students (or rather their records?)\n";

    cout << "\nTest 9: Oh, IF you have covered copy constructors in lecture, "
            << "then make sure the following call works properly, i.e. no memory "
            "leaks\n";
    doNothing(secA2);
    cout << "Back from doNothing\n\n";
} // main
