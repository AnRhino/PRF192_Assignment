#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pFile;

struct Student
{
    char sClassName[10];
    char sStudentID[10];
    char sStudentName[30];
    double dWorkshop;
    double dProgressTest;
    double dAssignment;
    double dPracticalExam;
    double dFinalExam;
};

typedef struct Student student;

void LoadFile(student *pStudentInfo, int nNumberStudent); //completed
void SaveFile(student *pStudentInfo, int nNumberStudent); //completed
void PrintMenu();
int nMakeChoice(int nMin, int nMax);
int nCheckPassed(student StudentInfo); //completed
void PrintAll(student *pStudent, int nNumberStudent); //completed
void AddStudent(); //incomplete
void UpdateInfo(); //incomplete
void DeleteStudent(); //incomplete

int main(void)
{
    pFile = fopen("Group4Data.txt", "r");

    int nNumberStudent = 0;
    fscanf(pFile, "%d", &nNumberStudent);

    student *pStudentInfo;
    pStudentInfo = (student*) malloc(nNumberStudent * sizeof(student));
    //Dynamic memory allocation

    LoadFile(pStudentInfo, nNumberStudent);
    fclose(pFile);

    int nChoice;
    do
    {
        nChoice = nMakeChoice(0, 8);
        switch(nChoice)
        {
        case 0:
            break;
        case 1:
            PrintAll(pStudentInfo, nNumberStudent);
            break;
        case 2:
            AddStudent();
            break;
        case 3:
            UpdateInfo();
            break;
        case 4:
            DeleteStudent();
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            SaveFile(pStudentInfo, nNumberStudent);
            break;
        }

        if(nChoice)
        {
            printf("\nPress any key to return to the menu.");
            getchar();
        }
    }
    while(nChoice);

    /*pFile = fopen("alo.txt", "w");
    fprintf(pFile, "%d", nNumberStudent);
    SaveFile(pStudentInfo, nNumberStudent);
    fclose(pFile);*/
    free(pStudentInfo);
    return 0;
}

void PrintMenu()
{
    //system("clear"); // for macos, linux
    system("cls"); // for windows
    printf("GRADING MANAGEMENT SYSTEM\n");
    printf("-------------------------\n");
    printf("1. Display list of students\n");
    printf("2. Add a new student\n");
    printf("3. Delete a student\n");
    printf("4. Update information\n");
    printf("5. Sort by ...\n");
    printf("6. Find student grades by student ID\n");
    printf("7. List students' grades by class ID\n");
    printf("8. Save\n");
    printf("0. Exit\n");
}

void LoadFile(student *pStudentInfo, int nNumberStudent)
{
    for(int i = 0; i < nNumberStudent; i++)
    {
        fscanf(pFile, "\n");
        fscanf(pFile, "%[^;]%*c", &pStudentInfo[i].sClassName);
        fscanf(pFile, "%[^;]%*c", &pStudentInfo[i].sStudentID);
        fscanf(pFile, "%[^;]%*c", &pStudentInfo[i].sStudentName);
        fscanf(pFile, "%lf%*c", &pStudentInfo[i].dWorkshop);
        fscanf(pFile, "%lf%*c", &pStudentInfo[i].dProgressTest);
        fscanf(pFile, "%lf%*c", &pStudentInfo[i].dAssignment);
        fscanf(pFile, "%lf%*c", &pStudentInfo[i].dPracticalExam);
        fscanf(pFile, "%lf%*c", &pStudentInfo[i].dFinalExam);
    }
}

void SaveFile(student *pStudentInfo, int nNumberStudent)
{
    pFile = fopen("Group4Data.txt", "w");
    fprintf(pFile, "%d", nNumberStudent);
    for(int i = 0; i < nNumberStudent; i++)
    {
        fprintf(pFile, "\n");
        fprintf(pFile, "%s;", pStudentInfo[i].sClassName);
        fprintf(pFile, "%s;", pStudentInfo[i].sStudentID);
        fprintf(pFile, "%s;", pStudentInfo[i].sStudentName);
        fprintf(pFile, "%.1lf;", pStudentInfo[i].dWorkshop);
        fprintf(pFile, "%.1lf;", pStudentInfo[i].dProgressTest);
        fprintf(pFile, "%.1lf;", pStudentInfo[i].dAssignment);
        fprintf(pFile, "%.1lf;", pStudentInfo[i].dPracticalExam);
        fprintf(pFile, "%.1lf", pStudentInfo[i].dFinalExam);
    }
    fclose(pFile);
    printf("All data and edits have been saved!\n");
}

int nMakeChoice(int nMin, int nMax)
{
    int nNotValid = 1, nInput, nScanfRet;
    char cInput;

    PrintMenu();
    fflush(stdin);
    do
    {
        printf("\nEnter your choice: ");
        nScanfRet = scanf("%d%c", &nInput, &cInput);
        if(nScanfRet < 2 || cInput != '\n')
        {
            PrintMenu();
            printf("\nYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(nInput < nMin || nInput > nMax)
        {
            PrintMenu();
            printf("\nYour choice is not valid. Please try again!\n");
        }
        else
            nNotValid = 0;
    }
    while(nNotValid);

    //system("clear"); // for macos, linux
    system("cls"); // for windows

    return nInput;
}

int nCheckPassed(student StudentInfo)
{
    if(StudentInfo.dAssignment == 0 ||
       StudentInfo.dProgressTest == 0 ||
       StudentInfo.dWorkshop == 0 ||
       StudentInfo.dPracticalExam == 0 ||
       StudentInfo.dFinalExam < 4)
        return 0;
    double dAverage = 0.1*(StudentInfo.dWorkshop + StudentInfo.dProgressTest + StudentInfo.dAssignment)
                    + 0.4*StudentInfo.dPracticalExam + 0.3*StudentInfo.dFinalExam;
    if(dAverage < 5)
        return 0;
    return 1;
}

void PrintAll(student *pStudentInfo, int nNumberStudent)
{
    //print top border of header
    {
        printf("+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
        printf("\n");
    }
    //print header
    {
        printf("|Class Name|Student ID|%-30s|Workshop|Progress Test|Assignment|Practical Exam|Final Exam|Status|\n", "Student Name");
    }
    //print bottom border of header
    {
        printf("+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
        printf("\n");
    }
    //print data
    for(int i = 0; i < nNumberStudent; i++)
    {
        printf("|%-10s|%-10s|%-30s|%8.1lf|%13.1lf|%10.1lf|%14.1lf|%10.1lf|%s|\n",
               pStudentInfo[i].sClassName,
               pStudentInfo[i].sStudentID,
               pStudentInfo[i].sStudentName,
               pStudentInfo[i].dWorkshop,
               pStudentInfo[i].dProgressTest,
               pStudentInfo[i].dAssignment,
               pStudentInfo[i].dPracticalExam,
               pStudentInfo[i].dFinalExam,
               (nCheckPassed(pStudentInfo[i]) == 1)?"Passes":"Failed");
    }
    //print bottom border of table
    {
        printf("+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
        printf("\n");
    }
}

void AddStudent()
{
    printf("Write your code here to implement the add_grade() function.\n");
}

void UpdateInfo()
{
    printf("Write your code here to implement the update_grade() function.\n");
}

void DeleteStudent()
{
    printf("Write your code here to implement the delete_grade() function.\n");
}