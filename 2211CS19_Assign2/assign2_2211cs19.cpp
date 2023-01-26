/*
Name: Krishna Kant Verma
Roll No: 2211CS19
Computer System Lab - 2
Assignment No: 2
Indian Institute of Technology Patna

*/

// all important header file required
//  input output header file
#include <iostream>
// header file to use map
#include <map>
// header file to use vectors
#include <vector>
// header file to use file related operations
#include <fstream>
// header file to use file utility class of file
#include <utility>
// header file to use unordered_set
#include <unordered_set>
// header file to use regex pattern matching operations
#include <regex>
// header file to use algorithms of stl
#include <algorithm>

// defining namespace as standard library (std;)
using namespace std;

// creating class StudentInfo for Storing required Student Information
class StudentInfo
{
public:
    // taking roll no of student
    string rollNo;
    // stores subjects grades
    int s1, s2, s3, s4, s5;
};

// set of valid grades of students(to verfiy whether grades are valid or invalid)
unordered_set<int> validGrades = {0, 4, 5, 6, 7, 8, 9, 10};

// regular expression to match roll no of students
regex rollNoPattern("^\\d{4}[A-Z]{2}\\d{3}$");
// regular expression to match subject code (S1->S5)
regex subjectCodePattern("^\\S[1-5]{1}$");

// taking input from user and appending grades of subject into database
void appendStudentGrades(int &grade)
{
    while (true)
    {
        // if grades provided in input belongs to valid Grade category
        if (validGrades.find(grade) == validGrades.end())
        {
            cout << "Grades Provided by You Seems Wrong (0,4,5,6,7,8,9,10) are valid Grades Enter Again\n";
            cin >> grade;
        }
        // otherwise break
        else
        {
            break;
        }
    }
}

// comparator function to compare the final results and sort them in desired format
static bool cmp(pair<int, string> pair1, pair<int, string> pair2)
{

    // returns true if first grade is lesser than second grade
    if (pair1.first < pair2.first)
    {
        return true;
    }
    // if grade of two student is equal than return true first roll no is lexico lesser than second roll no
    else if (pair1.first == pair2.first && pair1.second < pair1.second)
    {
        return true;
    }
    // otherwise return false
    else
    {
        return false;
    }
}

// function that write the student grades detail into Database
void writeStudentsGradesToDatabase()
{
    ofstream stud;
    stud.open("student_database.txt", std::ios_base::app);

    cout << "Enter Details of students\n";
    int choice = 1;

    map<string, bool> mp;

    while (choice)
    {

        StudentInfo student;

        // taking input roll no of student
        cout << "Enter Roll Number of Student: ";
        cin >> student.rollNo;
        if (!regex_match(student.rollNo, rollNoPattern))
        {
            cout << "Roll Number Provided By You is Wrong\n";
            continue;
        }

        /*****Entering the Grades of Students*****/

        cout << "\nEnter Grades of Student\n\n";

        // subject1
        cout << "Enter Subject 1(S1) Grade: ";
        cin >> student.s1;
        appendStudentGrades(student.s1);

        // subject2
        cout << "Enter Subject 2(S2) Grade: ";
        cin >> student.s2;
        appendStudentGrades(student.s2);

        // subject3
        cout << "Enter Subject 3(S3) Grade: ";
        cin >> student.s3;
        appendStudentGrades(student.s3);

        // subject4
        cout << "Enter Subject 4(S4) Grade: ";
        cin >> student.s4;
        appendStudentGrades(student.s4);

        // subject5
        cout << "Enter Subject 5(S5) Grade: ";
        cin >> student.s5;
        appendStudentGrades(student.s5);

        cout << "\n";
        cout << "Adding Details into Database\n";
        stud << student.rollNo << " " << student.s1 << " " << student.s2 << " " << student.s3 << " " << student.s4 << " " << student.s5 << endl;
        cout << "Record Added Successfully" << endl;

        cout << "Want to Add More Records Press 1 otherwise Press 0\n";
        cin >> choice;
    }

    // closing file
    stud.close();
}

// function that reads  student information from the database and added them into map to make the data operable
void readFileFromDatabase(map<string, vector<int>> &studentDetails)
{
    ifstream studInput("student_database.txt");

    // untill end of file not found
    while (!studInput.eof())
    {
        // putting each line from database to map
        string student_data;
        getline(studInput, student_data);

        string str = "";
        string rollno;
        vector<int> grades;

        bool flagRollNumber = false;

        /****Storing Details into Map****/
        for (int i = 0; i < student_data.size(); i++)
        {
            if (student_data[i] != ' ' && student_data[i] != '\n')
            {
                str += student_data[i];
            }
            else
            {
                if (!flagRollNumber)
                {
                    rollno = str;
                    flagRollNumber = true;
                }
                else
                {
                    int grade = stoi(str);
                    grades.push_back(grade);
                }
                str = "";
            }
        }

        // handling the grade value of student in subject S5 and adding it to map
        if (str.size())
        {
            int grade = stoi(str);
            grades.push_back(grade);
            studentDetails[rollno] = grades;
            str = "";
            flagRollNumber = false;
        }
    }
    // closing the file
    studInput.close();
}

// finding the student records in the range of rMin and rMax and store it into some final result array
void findStudentInRangeQuery(map<string, vector<int>> &studentDetails, vector<pair<int, string>> &queryResult, int subjectCode, int rMin, int rMax)
{
    // iterating in student details and if condn matches put it into final result
    for (auto roll : studentDetails)
    {
        vector<int> grade = roll.second;
        int score = grade[subjectCode - 1];
        if (score >= rMin && score <= rMax)
        {
            queryResult.push_back({score, roll.first});
        }
    }
    // this function returs nothing
}

// Function that print the details of student present in the data base
void printStudentDataBase(map<string, vector<int>> studentDetails)
{
    for (auto it : studentDetails)
    {
        cout << it.first << " ";
        for (auto x : it.second)
        {
            cout << x << " ";
        }
        cout << endl;
    }
}

// Function that prints the final Results
void printQueryResult(vector<pair<int, string>> &queryResult)
{
    // iterating all over results found
    cout << "Roll No\t\tGrade" << endl;
    for (auto it : queryResult)
    {
        cout << it.second << "\t" << it.first;

        cout << endl;
    }
}

int main()
{

    /*Code For Writing it to Database*/

    // creating map to store the student details
    map<string, vector<int>> studentDetails;

    // function that take input and write back to to student database
    cout << "**** Press 1 if You Want to add Records into Student Database OtherWise Press 0 ****" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        writeStudentsGradesToDatabase();
    }
    else
    {
        // execute nothing if choice is 0
        choice = 0;
    }

    // read details from database and append it to operable format
    readFileFromDatabase(studentDetails);

    // printing student database
    cout << "\n";
    cout << "All Student Data Present in Database" << endl;
    printStudentDataBase(studentDetails);

    /****************Writing and Reading Part Done Now Querying Part*******************22****/

    // taking input from user
    string subject;
    int rMin, rMax;

    cout << "\n";
    cout << "Enter Your Query in Format (Subject(S1) , MinGrade(integer), MaxGrade(integer)): ";
    cin >> subject >> rMin >> rMax;

    // if either of the query part is not in the format throwing error to user
    if (validGrades.find(rMin) == validGrades.end() || validGrades.find(rMax) == validGrades.end() || !regex_match(subject, subjectCodePattern))
    {
        cout << "\nInput Provided is either Wrong or not in Format (Restart Program) \n";
        return 0;
    }

    vector<pair<int, string>> queryResult;

    // finding code of subject from the input subject(for ex S1 finding 1 from S1)
    string code = "";
    code += subject[1];
    int subjectCode = stoi(code);

    // finding student details according to the given query
    findStudentInRangeQuery(studentDetails, queryResult, subjectCode, rMin, rMax);

    if (!queryResult.size())
    {
        cout << "Students Record not Found in Database(Restart Program)\n";
        return 0;
    }

    // sorting the query in appropriate format
    sort(queryResult.begin(), queryResult.end(), cmp);

    // printing the results of the query given by user
    cout << "\nStudents Matches with Your Search" << endl;
    cout << "Printing (Lexicographically Sorted Format)\n\n";

    printQueryResult(queryResult);

    cout << "\nQuerying Done" << endl;

    return 0;
}
// thank you so much