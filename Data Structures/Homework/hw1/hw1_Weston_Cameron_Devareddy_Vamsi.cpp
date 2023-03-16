/*
  Cameron Weston
  Vamsi Devareddy
  HW1 - on pointers, dynamic arrays, and structures
  @file hw1_incomplete.cpp
*/

#include <iostream>
#include <string>
#include <sstream> //needed for istringstream
#include <fstream>
#include <cassert> //needed for assert
#include <iomanip>

using namespace std;

struct Student
{
  string name;
  double * exams;
  double * quizzes;
  double * hw;
  double * labs;
};

//function prototypes
Student* readStudentsData(int numStudents, int numExams, int numQuizzes, int numHW, int numLabs); //reads students records from input file
double* getArray(string line, int numValues); //tokenizes a string into an array of doubles; similar to Python's split function
double calculateScore(double* activityArray, int num); //returns the score out of 100 or 10. Function removes lowest grade and scales the score
double findGrade(Student s, int numExams, int numQuizzes, int numHW, int numLabs); //calculates the grade out of 100 for the student s
void displayArray(double* lst, int arraySize); //display an array to the screen

int main()
{
  Student* data; //pointer to store the base address of a dynamic array to contain structs of students
  ifstream inFile;
  //read number of students and number of exams, quizzes, hws, and labs from file
  inFile.open("numbersActivities.txt");
  assert(inFile); //make sure that file was opened successfully; otherwise, terminate program with an error message

  //Read number of students from file
  int numStudents;
  inFile >> numStudents;
  cout << "Number of Students: " << numStudents << endl;

  //Read number of exams, quizzes, hws and labs from file
  int numExams, numQuizzes, numHW, numLabs;
  inFile >> numExams >> numQuizzes >> numHW >> numLabs;
  inFile.close();

  //load students data from file
  data = readStudentsData(numStudents, numExams, numQuizzes, numHW, numLabs);

  //Find the grade for each student
  for (int i = 0; i < numStudents; i++)
  {
    Student s = data[i]; //s takes current student's record
    double grade = findGrade(data[i], numExams, numQuizzes, numHW, numLabs); //calculate the grade for the current student
    cout << fixed << showpoint << setprecision(2); //Format output to show two digits after decimal point
    cout <<"Grade for " << data[i].name << " is " << grade << endl;
  }

  //Release dynamically allocated data
  delete [] data -> exams;
  delete [] data -> quizzes;
  delete [] data -> hw;
  delete [] data -> labs;
  delete [] data;

  return 0;
}//main()

/*
Function readStudentsData reads students records from the input file grades.txt and stores the results in a dynamic array
of Student structs. The function returns that array as its return value.
@param numStudents -- number of students
@param numExams -- number of exams
@param numQuizzes -- number of quizzes
@param numHW -- number of homework assignments
@param numLabs -- number of lab activities
*/
Student* readStudentsData(int numStudents, int numExams, int numQuizzes, int numHW, int numLabs)
{
  Student* studentsData; // pointer to base address of dynamically allocated array to store data read from file
  ifstream inFile;
  string line;

  inFile.open("grades.txt");
  assert(inFile); // if failed to open file, terminate program with an error message

  //fill in missing code
  //allocate memory for the dynamic array studentsData
  studentsData = new Student[numStudents];
  studentsData -> exams = new double[numExams];
  studentsData -> quizzes = new double[numQuizzes];
  studentsData -> hw = new double[numHW];
  studentsData -> labs = new double[numLabs];

  //store student read from file into the array
  for (int i = 0; i < numStudents; i++)
  {
        for (int j = 0; j < 5; j++)
        {
            if (j == 0)
            {
                getline(inFile, line);
                studentsData[i].name = line;
            }
            else if (j == 1)
            {
                getline(inFile, line);
                studentsData[i].exams = getArray(line, numExams);
            }
            else if (j == 2)
            {
                getline(inFile, line);
                studentsData[i].quizzes = getArray(line, numQuizzes);
            }
            else if (j == 3)
            {
                getline(inFile, line);
                studentsData[i].hw = getArray(line, numHW);
            }
            else if (j == 4)
            {
                getline(inFile, line);
                studentsData[i].labs = getArray(line, numLabs);
            }
        }
  }

  inFile.close();
  return studentsData;
}//readStudentsData()

/*
The function getArray() uses an istringstream object to read the different grades from a string as tokens.
Then, builds and returns an array with the grades.
@param line -- string with the different grades
@param numValues -- number of grades, which is the same as size of array
*/
double* getArray(string line, int numValues)
{
  double* lst = new double[numValues];
  istringstream instream(line);
  double grade;
  for (int i = 0; i < numValues; i++){
    instream >> grade; // read grade from instream
    lst[i] = grade;
  }
  return lst;
}//getArray()

/*
Function calculateScore accepts an array representing an activity --such as quizzes, hws, or labs-- containing
  the different scores for that activity.
Function takes care of removing the lowest grade from the calculations.
Function calculates and returns the total grade out of 100 in case of homework (or 10 in case of quizzes and labs) for that activity.
@param activityArray -- activity array
@param num -- number of elements of that kind of activity. For example, number of quizzes.
*/
double calculateScore(double* activityArray, int num)
{
  double sum = 0; //to accumulate sum of grades in
  double minScore = 100; //to store minimum score

  //fill in missing code
    for (int i = 0; i < num; i++)
    {
        if (activityArray[i] < minScore)
        {
            minScore = activityArray[i];
        }
        sum += activityArray[i];
    }

  sum = sum - minScore; // remove lowest exam score
  //scale grade to make it out of 100 (or 10) if activity is graded out of 100 (or 10)
  sum = sum / (num - 1);

  return sum;
}//calculateScore()

/*
The function findGrade calculates the final grade out of 100 for the student s.
The grade is calculated based on the following scale: exams count for 45% of the grade,
quizzes count for 10%, homework assignments count for 30%, and lab activities count for 15%.
One homework assignment, one quiz, and one lab with the lowest grade among that type of activity are removed for each student.
@param s -- a student record that the function needs to find the grade for
@param numExams -- number of exams
@param numQuizzes -- number of quizzes
@param numHW -- number of homework assignments
@param numLabs -- number of lab activities/assignments
*/
double findGrade(Student s, int numExams, int numQuizzes, int numHW, int numLabs)
{
    double exams_score;
    for (int i = 0; i < numExams; i++)
    {
        exams_score += s.exams[i];
    }
    exams_score /= numExams;
    //double exams_score = (s.exams[0] + s.exams[1] + s.exams[2]) / 3.0; //there are 3 exams
    //cout << "exams_score: " << exams_score << endl;
    double quizzes_score = calculateScore(s.quizzes,  numQuizzes);
    quizzes_score = quizzes_score * 10; // since quizzes are graded out of 10, scale the quizzes grade to make it out of 100
    //cout << "quizzes_score: " << quizzes_score << endl;

    //fill in missing code
    double hw_score = calculateScore(s.hw, numHW);
    //cout << "homework_score: " << hw_score << endl;
    double labs_score = calculateScore(s.labs, numLabs);
    labs_score *= 10; // since labs are graded out of 10, scale the labs grade to make it out of 100
    //cout << "labs_score: " << hw_score << endl;


    double score = exams_score * 0.45 + quizzes_score * 0.1 + hw_score * 0.3 + labs_score * 0.15;
    return score;
}//findGrade()

/*
Prints out the values in the array lst on one line where different values are separated by a space
*/
void displayArray(double* lst, int arraySize)
{
    //fill in missing code
    string arrayString;
    for (int i = 0; i < arraySize; i++)
    {
      arrayString += to_string(lst[i]) + " ";
    }
    cout << endl << arrayString << endl;
}//displayArray()
