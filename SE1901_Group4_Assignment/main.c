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
void PrintMenu();
int nMakeChoice(int nMin, int nMax);
int nCheckPassed(student StudentInfo); //completed
void f1_PrintAll(student *pStudentInfo, int nNumberStudent); //completed
void f2_AddStudent(); //Bao is cooking
void f3_UpdateInfo(); //Nhut is cooking
void f4_DeleteStudent(); //Bao is cooking
void f5_SortBy(); //Hao is cooking
void f6_FindStudentGrade(); //Phuc is cooking
void f7_ListStudentGradeinClass(); //Phuc is cooking
void f8_SaveFile(student *pStudentInfo, int nNumberStudent); //completed

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
            f1_PrintAll(pStudentInfo, nNumberStudent);
            break;
        case 2:
            f2_AddStudent();
            break;
        case 3:
            f3_UpdateInfo();
            break;
        case 4:
            f4_DeleteStudent();
            break;
        case 5:
            break;
        case 6:
            break;
        case 7:
            break;
        case 8:
            f8_SaveFile(pStudentInfo, nNumberStudent);
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
    printf("3. Update information\n");
    printf("4. Delete a student\n");
    printf("5. Sort by ...\n");
    printf("6. Find student's grades by student ID\n");
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

void f1_PrintAll(student *pStudentInfo, int nNumberStudent)
{
    //print top border of header
    printf("+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");

    //print header
    printf("|Class Name|Student ID|%-30s|Workshop|Progress Test|Assignment|Practical Exam|Final Exam|Status|\n", "Student Name");

    //print bottom border of header
    printf("+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");

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
    printf("+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");
}

void f2_AddStudent()
{
    printf("Write your code here to implement the add_grade() function.\n");
}

void f3_UpdateInfo()
{
    printf("Write your code here to implement the update_grade() function.\n");
}

void f4_DeleteStudent()
{
    printf("Write your code here to implement the delete_grade() function.\n");
}

void f6_FindStudentGrade() //Phuc_unfinished
{
    //Note: Implement a Keystroke to exit in case of not wanting to f6 anymore
    //1.input Class and StudentCode
    //2.Check valid input
    //3.lookup for data in db
    //4.return grades
    char StudentGroup[6];
    char StudentCode[8];

    for(;;)
    {
        printf("Enter Class(Student group, example: SE1901): ");
        scanf("%s", &StudentGroup);

        if(//StudentGroup not found in file)
        {
            printf("Student Group not found, please try again.\n");
        } else {
            break;
        }
    }

    for(;;)
    {
        printf("Enter Student Code(Role number, example: CE19XXXX): ");
        scanf("%s", &StudentCode);

        if(//StudentCode not found in file)
        {
            printf("Student Code not found, please try again.\n");
        } else {
            printf(//Result);
        }
    }
}

void f7_ListStudentGradeinClass() //Phuc_unfinished
{
    //Note: Implement a Keystroke to exit in case of not wanting to f7 anymore
    //1.Input StudentGroup
    //2.Loop through all StudentCode in StudentGroup
    //3.Output Grade of each StudentCode of StudentGroup
    char StudentGroup[6];
    for(;;)
    {
        printf("Enter Class(Student group, example: SE1901): ");
        scanf("%s", &StudentGroup);

        if(//StudentGroup not found in file)
        {
            printf("Student Group not found, please try again.\n");
        } else {
            break;
        }
    }

}

void f8_SaveFile(student *pStudentInfo, int nNumberStudent)
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
