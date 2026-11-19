// CodeAlpha C++ Internship - Task 1: CGPA Calculator
#include <algorithm>
#include <cctype>
#include <iomanip>
#include <iostream>
#include <map>
#include <string>
#include <vector>
using namespace std;

struct Course {
    string name;
    string gradeLabel;
    double gradePoint;
    double credits;
    double points() const { return gradePoint * credits; }
};

// Grade -> grade point (4.00 scale). Edit this to match your university.
const map<string, double> GRADE_SCALE = {
    {"A+", 4.00}, {"A", 3.75}, {"A-", 3.50}, {"B+", 3.25}, {"B", 3.00},
    {"B-", 2.75}, {"C+", 2.50}, {"C", 2.25}, {"D", 2.00},  {"F", 0.00}};

string toUpper(string s) {
    transform(s.begin(), s.end(), s.begin(),
              [](unsigned char c) { return toupper(c); });
    return s;
}

string trim(const string& s) {
    size_t a = s.find_first_not_of(" \t\r\n");
    size_t b = s.find_last_not_of(" \t\r\n");
    return a == string::npos ? "" : s.substr(a, b - a + 1);
}

bool tryParseDouble(const string& s, double& out) {
    try {
        size_t pos = 0;
        out = stod(s, &pos);
        return pos == s.size();
    } catch (...) {
        return false;
    }
}

int readInt(const string& prompt, int minValue) {
    string line;
    int value;
    while (true) {
        cout << prompt;
        getline(cin, line);
        double d;
        if (tryParseDouble(trim(line), d) && d == (int)d && (int)d >= minValue) {
            value = (int)d;
            return value;
        }
        cout << "  Invalid input. Enter a whole number >= " << minValue << ".\n";
    }
}

double readDouble(const string& prompt, double minValue, double maxValue) {
    string line;
    double value;
    while (true) {
        cout << prompt;
        getline(cin, line);
        if (tryParseDouble(trim(line), value) && value >= minValue &&
            value <= maxValue)
            return value;
        cout << "  Invalid input. Enter a number between " << minValue << " and "
             << maxValue << ".\n";
    }
}

// Accepts a letter grade (A+, B, ...) or a numeric grade point (0 - 4).
void readGrade(const string& prompt, string& label, double& point) {
    string line;
    while (true) {
        cout << prompt;
        getline(cin, line);
        string g = toUpper(trim(line));
        auto it = GRADE_SCALE.find(g);
        if (it != GRADE_SCALE.end()) {
            label = g;
            point = it->second;
            return;
        }
        double d;
        if (tryParseDouble(g, d) && d >= 0 && d <= 4) {
            label = g;
            point = d;
            return;
        }
        cout << "  Invalid grade. Use A+, A, A-, B+, B, B-, C+, C, D, F or 0-4.\n";
    }
}

void printLine(char c, int n) { cout << string(n, c) << "\n"; }

int main() {
    cout << "\n==============================\n";
    cout << "        CGPA CALCULATOR       \n";
    cout << "==============================\n\n";

    int n = readInt("Number of courses this semester: ", 1);
    vector<Course> courses;
    double totalCredits = 0, totalPoints = 0;

    for (int i = 1; i <= n; i++) {
        cout << "\n--- Course " << i << " ---\n";
        Course c;
        cout << "  Course name/code (optional): ";
        getline(cin, c.name);
        c.name = trim(c.name);
        if (c.name.empty()) c.name = "Course " + to_string(i);
        readGrade("  Grade (e.g. A+, B, 3.5): ", c.gradeLabel, c.gradePoint);
        c.credits = readDouble("  Credit hours: ", 0.5, 30);

        totalCredits += c.credits;
        totalPoints += c.points();
        courses.push_back(c);
    }

    double semesterGPA = totalPoints / totalCredits;

    cout << "\n--- Previous record (enter 0 if this is your first semester) ---\n";
    double prevCredits = readDouble("Credits completed before this semester: ", 0, 1000);
    double prevCGPA = 0;
    if (prevCredits > 0) prevCGPA = readDouble("CGPA before this semester: ", 0, 4);

    double overallCredits = prevCredits + totalCredits;
    double cgpa = (prevCGPA * prevCredits + totalPoints) / overallCredits;

    // ---- Results ----
    cout << fixed << setprecision(2);
    cout << "\n";
    printLine('=', 64);
    cout << left << setw(22) << "Course" << setw(8) << "Grade" << setw(8) << "GP"
         << setw(10) << "Credits" << setw(10) << "Points" << "\n";
    printLine('-', 64);
    for (const auto& c : courses) {
        cout << left << setw(22) << c.name.substr(0, 20) << setw(8) << c.gradeLabel
             << setw(8) << c.gradePoint << setw(10) << c.credits << setw(10)
             << c.points() << "\n";
    }
    printLine('-', 64);
    cout << "Semester total credits : " << totalCredits << "\n";
    cout << "Semester total points  : " << totalPoints << "\n";
    cout << "Semester GPA           : " << semesterGPA << "\n";
    cout << "Total credits so far   : " << overallCredits << "\n";
    cout << "Final CGPA             : " << cgpa << "\n";
    printLine('=', 64);
    return 0;
}
