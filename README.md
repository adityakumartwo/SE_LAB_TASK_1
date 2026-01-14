SE LAB TASK -1
Student Result Processing System

This program follows a standard INPUT->PROCESS->OUTPUT(IPO) cycle, it breakdown into 3 modules.

    1)Input Module
    2)Computatuin Module
    3)Output Module

Work flow of the program:

1.Initialize (create a main function in the main.c)

    A. The program start with main().
    B. It create an array of student structure to hold data of 100 students.
    C. It also call the Input Module (read_input)

2.Input and validation phase

    A.Opening the file: open input.txt file. If the file is missing it stop the program.
    B.Reading: read line by line using the fscanf.

    C.Ensure validity:
        a)ID check: must be alphanumeric and unique
        b)Name Check: only alphabets
        c)Marks Check: minor (0-40), major(0-60)

    D.Decision: 
        a)If valid: data is copied into the Student array, then student counter is increased.
        b)If invalid: An error message is shown on the screen, also the that student record is not stored.

3.Processing Phase: I.e inside the calcu_Ressult()

    a)Loop: iterate through all valid students
    b)Subject Total: Adds Minor + Major marks of each subject.
    c)FailCheck: <50 marks students is fail.
    d)Grand Total: Grand Total/5 (because there are 5 subjects)

    e)Grading Logic:
        i.If failflag is TRUE, grade is F
        ii.Other wise follow the grading structure
        iii.Calculates CGPA on the basis of grades.


4.Output Phase: I.e show_Output() 

    a)File: Opens results.txt 
    b)Printing Headers: print the table header in both console and the File.
    
    c)Data loop shows:
        i.Class Total (for average)
        ii.High Perc and Low Perc.
        iii.Grade Count
    
    d)Print the summary

    e)Cleaning: close the file and ensure data is saved.
