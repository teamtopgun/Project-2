//============================================================================
// Name        : Course Selection
// Author      : Kyle Gilbert
// Version     : 1.0
// Description : Course Selection tool.  With this you will be able to load a CSV file filled with courses
// and see information and prerequisites.
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold course information
struct CourseInfo {
    string CourseNum; // unique identifier
    string CourseTitle;
    string PreReq1;
    string PreReq2;

    // Define a comparison function for CourseInfos
    bool operator<=(const CourseInfo& other) const {
        return CourseNum <= other.CourseNum; // You may need to adjust this based on your CourseInfo class fields
    }
};


void displayCourseInfo(CourseInfo course) {
    cout << course.CourseNum << ": " << course.CourseTitle << " Prerequisites: " << course.PreReq1 << "  "
        << course.PreReq2 << endl;
    return;
}



/**
 * Load a CSV file containing courses into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the courses read
 */
vector<CourseInfo> loadCourseInfos(string csvPath) {
    cout << "Loading CSV file " << csvPath << endl;

    // Define a vector data structure to hold a collection of courses.
    vector<CourseInfo> courses;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    try {
        // loop to read rows of a CSV file
        for (int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of courses
            CourseInfo course;
            course.CourseNum = file[i][0];
            course.CourseTitle = file[i][1];
            course.PreReq1 = file[i][2];
            course.PreReq1 = file[i][3];
            cout << course.CourseNum;

            // push this course to the end
            courses.push_back(course);
        }
    }
    catch (csv::Error& e) {
        std::cerr << e.what() << std::endl;
    }
    return courses;
}

/**
 * Partition the vector of courses into two parts, low and high
 *
 * @param courses Address of the vector<CourseInfo> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition
 */
int partition(vector<CourseInfo>& courses, int begin, int end) {
    CourseInfo pivot = courses[end]; // Choose the last element as the pivot
    int i = (begin - 1); // Index of the smaller element

    for (int j = begin; j < end; j++) {
        // If the current element is smaller than or equal to the pivot
        if (courses[j] <= pivot) {
            i++; // Increment the index of the smaller element
            std::swap(courses[i], courses[j]);
        }
    }

    std::swap(courses[i + 1], courses[end]);
    return (i + 1);
}

void courseSearch(const vector<CourseInfo>& courses, const string& courseSelection) {
    //when course is selcted this will quickly find the course you are interested in.
    bool found = false;

    for (const CourseInfo& course : courses) {
        if (course.CourseNum == courseSelection) {
            displayCourseInfo(course);
            found = true;
            break;  // Assuming course numbers are unique; no need to continue searching
        }
    }

    if (!found) {
        cout << "Course " << courseSelection << " not found." << endl;
    }
}


void selectionSort(vector<CourseInfo>& courses) {
    //after loaded being loaded into a vector, selection sort it used for 
    int i = 0;
    int j = 0;
    int indexSmallest = 0;
    int numberSize = courses.size();
    CourseInfo temp;  //temp value for swap
    for (i = 0; i < numberSize - 1; ++i) {
        indexSmallest = i; //find index of smallest remaining
        for (j = i + 1; j < numberSize; ++j) {

            if (courses[j] <= courses[indexSmallest]) {
                indexSmallest = j;
            }
        }
        temp = courses[i]; //this swaps the numbers
        courses[i] = courses[indexSmallest];
        courses[indexSmallest] = temp;
    }

}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath;
    string courseSelection;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        break;
    default:
        csvPath = "Course_list.csv";
    }

    // Define a vector to hold all the courses
    vector<CourseInfo> courses;

    // Define a timer variable
    clock_t ticks;

    int choice = 0;
    while (choice != 4) {
        cout << "Menu:" << endl;
        cout << "  1. Load Course Data" << endl;
        cout << "  2. Print Course List" << endl;
        cout << "  3. Search Course and Print Course Prerequisites" << endl;
        cout << "  4. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            // Initialize a timer variable before loading courses


            // Complete the method call to load the courses
            courses = loadCourseInfos(csvPath);


            cout << "Courses Loaded: " << endl;

            break;

        case 2:
            selectionSort(courses);
            // Loop and display the courses read
            for (int i = 0; i < courses.size(); ++i) {
                displayCourseInfo(courses[i]);
            }
            cout << endl;

            break;

        case 3:
            cout << "Enter course number you would like information on: ";
            cin >> courseSelection;
            courseSearch(courses, courseSelection);
            break;
        default:
            cout << "Enter a valid Number" << endl;


        }
    }

    cout << "Good bye." << endl;

    return 0;
}
