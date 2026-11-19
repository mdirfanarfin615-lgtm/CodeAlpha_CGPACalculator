# CodeAlpha_CGPACalculator

A console-based **CGPA Calculator** written in C++ as part of the **CodeAlpha C++ Programming Internship (Task 1)**.

## Features
- Takes the number of courses taken by the student
- Takes the grade and credit hours for each course (letter grade like `A+`, or a number like `3.5`)
- Calculates total credits and total grade points (grade point x credit hours)
- Computes the **semester GPA** and the **overall CGPA** (including previous semesters)
- Displays a formatted table of every course and the final CGPA
- Input validation for all fields

## Grading Scale (4.00)
| Grade | Point | Grade | Point |
|-------|-------|-------|-------|
| A+ | 4.00 | C+ | 2.50 |
| A | 3.75 | C | 2.25 |
| A- | 3.50 | D | 2.00 |
| B+ | 3.25 | F | 0.00 |
| B | 3.00 | | |
| B- | 2.75 | | |

(Change the `GRADE_SCALE` map in `main.cpp` to match your university.)

## Build & Run
```bash
g++ -std=c++17 -o cgpa main.cpp
./cgpa          # Windows: cgpa.exe
```

## Sample Output
```
Course                Grade   GP      Credits   Points
CSE101                A       3.75    3.00      11.25
Math                  B+      3.25    3.00      9.75
Semester GPA           : 3.50
Final CGPA             : 3.50
```

## Concepts Used
`struct`, `vector`, `map`, string handling, input validation, formatted output (`iomanip`).
