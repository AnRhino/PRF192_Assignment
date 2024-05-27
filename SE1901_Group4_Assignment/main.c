#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pFile;

struct Student
{
    char sClassName[10];
    char sStudentID[8];
    char sStudentName[30];
    double dWorkshop;
    double dProgressTest;
    double dAssignment;
    double dPracticalExam;
    double dFinalExam;
};

typedef struct Student student;

void LoadFile(student *pStudentInfo, int nNumberStudent); //incomplete
void SaveFile(student *pStudentInfo, int nNumberStudent); //incomplete
void PrintMenu(); //incomplete
int nMakeChoice(int nMin, int nMax); //incomplete
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
        nChoice = nMakeChoice(0, 3);
        switch(nChoice)
        {
        case 0:
            break;
        case 1:
            AddStudent();
            break;
        case 2:
            UpdateInfo();
            break;
        case 3:
            DeleteStudent();
            break;
        }

        if(nChoice)
        {
            printf("\nPress any key to return to the menu.");
            getchar();
        }
    }
    while(nChoice);

    pFile = fopen("Group4Data.txt", "w");
    fprintf(pFile, "%d", nNumberStudent);
    SaveFile(pStudentInfo, nNumberStudent);
    fclose(pFile);
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
    printf("5. Find student grades by student ID\n");
    printf("6. List students' grades by class ID\n");
    printf("7. Save\n");
    printf("0. Exit\n");
}

void LoadFile(student *pStudentInfo, int nNumberStudent)
{
    for(int i = 0; i < nNumberStudent; i++)
    {
        fscanf(pFile, "\n");
        fscanf(pFile, "%[\t]", pStudentInfo[i].sClassName);
    }
}

void SaveFile(student *pStudentInfo, int nNumberStudent)
{

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
