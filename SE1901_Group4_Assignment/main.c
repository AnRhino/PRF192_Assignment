#include <stdio.h>
#include <stdlib.h>
#include <string.h>

FILE *pFile;
int nChangeStatus = 0;

struct Student
{
    char sClassName[7];
    char sStudentID[9];
    char sStudentName[31];
    double dWorkshop;
    double dProgressTest;
    double dAssignment;
    double dPracticalExam;
    double dFinalExam;
};

typedef struct Student student;

void LoadFile(student *pStudentInfo, int nNumberStudent); //completed
void PrintMenu();
void PrintMenu_f(); //Used in function
int nMakeChoice(int nMin, int nMax);
int nMakeChoice_f(int nMin, int nMax); //Used in function
double dAvgGrade(student StudentInfo);
int nCheckPassed(student StudentInfo); //completed
int nGradeValidation(double dGrade, int nScanfRet); //Used to check input
int nCheckClassName(char *sClassName);
int nCheckStudentID(student *pStudentInfo, int nNumberStudent, int nIndex);
void ChangeStudent(student *pStudentInfo, int i, int j, int nSortBy, int nSortFrom); //Used in function 5
int nFindStudentID(char *StudentID, student *pStudentInfo, int nNumberStudent);

void f1_PrintAll(student *pStudentInfo, int nNumberStudent); //completed
void f2_AddStudent(student *pStudentInfo, int *nNumberStudent); //completed
void f3_UpdateInfo(student *pStudentInfo, int nNumberStudent); //Nhut is cooking
void f4_DeleteStudent(student *pStudentInfo, int *nNumberStudent); //completed
void f5_SortBy(student *pStudentInfo, int nNumberStudent); //Completed
void f6_FindStudentGrade(student *pStudentInfo, int nNumberStudent); //Completed
void f7_ListStudentGradeinClass(student *pStudentInfo, int nNumberStudent); //Completed
void f8_SaveFile(student *pStudentInfo, int nNumberStudent); //completed
void f0_Exit(student *pStudentInfo, int nNumberStudent); //completed

int main(void)
{
    pFile = fopen("Group4Data.txt", "r");
    if(pFile == NULL)
    {
        int nStart = 0;
        printf("Data not found!\n");
        printf("Enter ONLY '1' to create new data, or else to exit.\n");
        printf("\tEnter: ");
        scanf("%d", &nStart);
        if(nStart != 1)
            return 0;
    }
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
            f0_Exit(pStudentInfo, nNumberStudent);
            break;
        case 1:
            f1_PrintAll(pStudentInfo, nNumberStudent);
            break;
        case 2:
            f2_AddStudent(pStudentInfo, &nNumberStudent);
            break;
        case 3:
            f3_UpdateInfo(pStudentInfo, nNumberStudent);
            break;
        case 4:
            f4_DeleteStudent(pStudentInfo, &nNumberStudent);
            break;
        case 5:
            f5_SortBy(pStudentInfo, nNumberStudent);
            break;
        case 6:
            f6_FindStudentGrade(pStudentInfo, nNumberStudent);
            break;
        case 7:
            f7_ListStudentGradeinClass(pStudentInfo, nNumberStudent);
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

void PrintMenu_f()
{
    //system("clear"); // for macos, linux
    system("cls"); // for windows
    printf("Updated successfully!\n");
    printf("Do you want to continue?\n");
    printf("1. Yes\n");
    printf("0. No\n");
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

int nMakeChoice_f(int nMin, int nMax)
{
    int nNotValid = 1, nInput, nScanfRet;
    char cInput;

    PrintMenu_f();
    fflush(stdin);
    do
    {
        printf("\nEnter your choice: ");
        nScanfRet = scanf("%d%c", &nInput, &cInput);
        if(nScanfRet < 2 || cInput != '\n')
        {
            PrintMenu_f();
            printf("\nYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(nInput < nMin || nInput > nMax)
        {
            PrintMenu_f();
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

double dAvgGrade(student StudentInfo)
{
    return 0.1*(StudentInfo.dWorkshop + StudentInfo.dProgressTest + StudentInfo.dAssignment)
           + 0.4*StudentInfo.dPracticalExam + 0.3*StudentInfo.dFinalExam;
}

int nCheckPassed(student StudentInfo)
{
    if(StudentInfo.dAssignment == 0 ||
            StudentInfo.dProgressTest == 0 ||
            StudentInfo.dWorkshop == 0 ||
            StudentInfo.dPracticalExam == 0 ||
            StudentInfo.dFinalExam < 4)
        return 0;
    if(dAvgGrade(StudentInfo) < 5)
        return 0;
    return 1;
}

int nGradeValidation(double dGrade, int nScanfRet)
{
    scanf("%*[^\n]%*c");
    if(nScanfRet == 0)
    {
        printf("\t\tThe grade must be a number.\n");
        return 1;
    }
    if(dGrade < 0 || dGrade > 10)
    {
        printf("\t\tThe grade must be between 0 and 10, please try again.\n");
        return 1;
    }
    return 0;
}

int nCheckClassName(char *sClassName)
{

    for(int i = 0; i < strlen(sClassName); i++)
    {
        if(sClassName[i] == ' ')
        {
            memmove(sClassName + i, sClassName + i+1, strlen(sClassName + i));
        } //Delete SPACE characters

        if(sClassName[i] >= 'a' && sClassName[i] <= 'z')
        {
            sClassName[i] -= ('a' - 'A');
        } //Upper letter characters
    }

    if(strlen(sClassName) != 6)
    {
        printf("\t\tClass Name is not in the correct format, please try again.\n");
        return 1;
    } //Check the length of Class Name (must be 6)

    if(atoi(sClassName + 2) == 0)
    {
        printf("\t\tClass Name is not in the correct format, please try again.\n");
        return 1;
    } //Check number characters

    char sMajor[12][3] = {"AI", "BA", "EL", "GD", "HM", "IA", "IB", "JL", "KR", "MC", "SE", "TM"};
    char sMajorName[3];
    memmove(sMajorName, sClassName, 2);
    sMajorName[2] = '\0';

    for(int i = 0; i < 12; i++)
    {
        if(strcmp(sMajorName, sMajor[i]) == 0)
        {
            return 0;
        }
    } //Check major code
    printf("\t\tClass Name is not in the correct format, please try again.\n");
    return 1;
}

int nCheckStudentID(student *pStudentInfo, int nNumberStudent, int nIndex)
{
    for(int i = 0; i < strlen(pStudentInfo[nIndex].sStudentID); i++)
    {
        if(pStudentInfo[nIndex].sStudentID[i] == ' ')
        {
            memmove(pStudentInfo[nIndex].sStudentID + i,
                    pStudentInfo[nIndex].sStudentID + i+1,
                    strlen(pStudentInfo[nIndex].sStudentID + i));
        } //Delete SPACE characters

        if(pStudentInfo[nIndex].sStudentID[i] >= 'a' &&
                pStudentInfo[nIndex].sStudentID[i] <= 'z')
        {
            pStudentInfo[nIndex].sStudentID[i] -= ('a' - 'A');
        } //Upper letter characters
    }

    if(strlen(pStudentInfo[nIndex].sStudentID) != 8)
    {
        printf("\t\tStudent ID is not in the correct format, please try again.\n");
        return 1;
    } //Check the length of Class Name (must be 6)

    if(pStudentInfo[nIndex].sStudentID[0] != 'C' &&
            pStudentInfo[nIndex].sStudentID[0] != 'H' &&
            pStudentInfo[nIndex].sStudentID[0] != 'S' &&
            pStudentInfo[nIndex].sStudentID[0] != 'Q' &&
            pStudentInfo[nIndex].sStudentID[0] != 'D')
    {
        printf("\t\tStudent ID is not in the correct format, please try again.\n");
        return 1;
    } //Check campus code

    if(pStudentInfo[nIndex].sStudentID[1] != 'S' &&
            pStudentInfo[nIndex].sStudentID[1] != 'E' &&
            pStudentInfo[nIndex].sStudentID[1] != 'A')
    {
        printf("\t\tStudent ID is not in the correct format, please try again.\n");
        return 1;
    } //Check major code

    if(atoi(pStudentInfo[nIndex].sStudentID + 2) == 0)
    {
        printf("\t\tStudent ID is not in the correct format, please try again.\n");
        return 1;
    } //Check number characters

    for(int i = 0; i < nNumberStudent; i++)
    {
        if(i == nIndex) continue;
        if(strcmp(pStudentInfo[nIndex].sStudentID, pStudentInfo[i].sStudentID) == 0)
        {
            printf("\t\tStudent ID already exists, please try again.\n");
            return 1;
        }
    } //Check for uniqueness of Student ID
    return 0;
}

void ChangeStudent(student *pStudentInfo, int i, int j, int nSortBy, int nSortFrom)
{
    switch(nSortBy)
    {
    case 1:
        if(strcmp(pStudentInfo[i].sClassName, pStudentInfo[j].sClassName) == 0) return;
        if((nSortFrom == 1) ^ (strcmp(pStudentInfo[i].sClassName, pStudentInfo[j].sClassName) < 0))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 2:
        if((nSortFrom == 1) ^ (strcmp(pStudentInfo[i].sStudentID, pStudentInfo[j].sStudentID) < 0))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 3:
        if(strcmp(pStudentInfo[i].sStudentName, pStudentInfo[j].sStudentName) == 0) return;
        if((nSortFrom == 1) ^ (strcmp(pStudentInfo[i].sStudentName, pStudentInfo[j].sStudentName) < 0))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 4:
        if(pStudentInfo[i].dWorkshop == pStudentInfo[j].dWorkshop) return;
        if((nSortFrom == 1) ^ (pStudentInfo[i].dWorkshop < pStudentInfo[j].dWorkshop))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 5:
        if(pStudentInfo[i].dProgressTest == pStudentInfo[j].dProgressTest) return;
        if((nSortFrom == 1) ^ (pStudentInfo[i].dProgressTest < pStudentInfo[j].dProgressTest))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 6:
        if(pStudentInfo[i].dAssignment == pStudentInfo[j].dAssignment) return;
        if((nSortFrom == 1) ^ (pStudentInfo[i].dAssignment < pStudentInfo[j].dAssignment))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 7:
        if(pStudentInfo[i].dPracticalExam == pStudentInfo[j].dPracticalExam) return;
        if((nSortFrom == 1) ^ (pStudentInfo[i].dPracticalExam < pStudentInfo[j].dPracticalExam))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 8:
        if(pStudentInfo[i].dFinalExam == pStudentInfo[j].dFinalExam) return;
        if((nSortFrom == 1) ^ (pStudentInfo[i].dFinalExam < pStudentInfo[j].dFinalExam))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    case 9:
        if(dAvgGrade(pStudentInfo[i]) == dAvgGrade(pStudentInfo[j])) return;
        if((nSortFrom == 1) ^ (dAvgGrade(pStudentInfo[i]) < dAvgGrade(pStudentInfo[j])))
        {
            student tmp = pStudentInfo[i];
            pStudentInfo[i] = pStudentInfo[j];
            pStudentInfo[j] = tmp;
        }
        return;
    }
}

int nFindStudentID(char *StudentID, student *pStudentInfo, int nNumberStudent)
{
    for(int i = 0; i < strlen(StudentID); i++)
    {
        if(StudentID[i] == ' ')
        {
            memmove(StudentID + i, StudentID + i+1, strlen(StudentID + i));
        }

        if(StudentID[i] >= 'a' && StudentID[i] <= 'z')
        {
            StudentID[i] -= ('a' - 'A');
        }
    }

    for(int i = 0; i < nNumberStudent; i++)
    {
        if(strcmp(StudentID, pStudentInfo[i].sStudentID) == 0)
        {
            return i;
        }
    }
    system("cls");
    printf("Student ID not found, please try again.\n");
    return -1;
}

void f1_PrintAll(student *pStudentInfo, int nNumberStudent)
{
    //print top border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+---------+------+");
    printf("\n");

    //print header
    printf("|No.|Class Name|Student ID|%-30s|Workshop|Progress Test|Assignment|Practical Exam|Final Exam|Avg Grade|Status|\n", "Student Name");

    //print bottom border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+---------+------+");
    printf("\n");

    //print data
    for(int i = 0; i < nNumberStudent; i++)
    {
        printf("|%3d|%-10s|%-10s|%-30s|%8.1lf|%13.1lf|%10.1lf|%14.1lf|%10.1lf|%9.1lf|%s|\n",
               i + 1,
               pStudentInfo[i].sClassName,
               pStudentInfo[i].sStudentID,
               pStudentInfo[i].sStudentName,
               pStudentInfo[i].dWorkshop,
               pStudentInfo[i].dProgressTest,
               pStudentInfo[i].dAssignment,
               pStudentInfo[i].dPracticalExam,
               pStudentInfo[i].dFinalExam,
               dAvgGrade(pStudentInfo[i]),
               (nCheckPassed(pStudentInfo[i]) == 1)?"Passes":"Failed");
    }

    //print bottom border of table
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+---------+------+");
    printf("\n");
}

void f2_AddStudent(student *pStudentInfo, int *nNumberStudent)
{
    nChangeStatus = 1;
do_f2:
    (*nNumberStudent)++;
    pStudentInfo = (student*)realloc(pStudentInfo, (*nNumberStudent) * sizeof(student));

    system("cls");
    printf("Please enter information for the new student:\n");
    do //Class Name
    {
        printf("\tClass Name: ");
        scanf("%[^\n]%*c", &pStudentInfo[(*nNumberStudent)-1].sClassName);
        fflush(stdin);
    }
    while(nCheckClassName(pStudentInfo[(*nNumberStudent)-1].sClassName));

    do //Student ID
    {
        printf("\tStudent ID: ");
        scanf("%[^\n]%*c", &pStudentInfo[(*nNumberStudent)-1].sStudentID);
        fflush(stdin);
    }
    while(nCheckStudentID(pStudentInfo, *nNumberStudent, (*nNumberStudent) - 1));
    printf("\tStudent Name: ");
    scanf("%30[^\n]", &pStudentInfo[(*nNumberStudent)-1].sStudentName);
    fflush(stdin);

    printf("Please enter grades for the new student:\n");
    int nScanfRet;
    do //Workshop
    {
        printf("\tWorkshop: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dWorkshop);
    }
    while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dWorkshop, nScanfRet));
    do //Progress Test
    {
        printf("\tProgress Test: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dProgressTest);
    }
    while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dProgressTest, nScanfRet));
    do //Assignment
    {
        printf("\tAssignment: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dAssignment);
    }
    while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dAssignment, nScanfRet));
    do //Practical Exam
    {
        printf("\tPractical Exam: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dPracticalExam);
    }
    while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dPracticalExam, nScanfRet));
    do //Final Exam
    {
        printf("\tFinal Exam: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dFinalExam);
    }
    while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dFinalExam, nScanfRet));

    int nChoice;
    do
    {
        nChoice = nMakeChoice_f(0, 1);
        if(nChoice)
            goto do_f2;
    }
    while(nChoice);
}

void f3_UpdateInfo(student *pStudentInfo, int nNumberStudent)
{
    int index;
    char StudentID[9];
    int nNotValid = 1, nInput, nScanfRet;
    char cInput;
do_f3:
    do
    {
        printf("Enter Student ID: ");
        scanf("%[^\n]%*c", StudentID);
        fflush(stdin);
        index = nFindStudentID(StudentID, pStudentInfo, nNumberStudent);
        if(index != -1) break;
        system("cls");
        printf("Student ID not found. Do you want to continue?\n");
        printf("\t1. Yes\n");
        printf("\t0. No\n");
        do
        {
            printf("\nEnter your choice: ");
            nScanfRet = scanf("%d%c", &nInput, &cInput);
            if(nScanfRet < 2 || cInput != '\n')
            {
                system("cls");
                printf("Student ID not found. Do you want to continue?\n");
                printf("\t1. Yes\n");
                printf("\t0. No\n");
                printf("\n\tYour choice is not valid. Please try again!\n");
                fflush(stdin);
            }
            else if(nInput < 0 || nInput > 1)
            {
                system("cls");
                printf("Student ID not found. Do you want to continue?\n");
                printf("\t1. Yes\n");
                printf("\t0. No\n");
                printf("\n\tYour choice is not valid. Please try again!\n");
            }
            else
                nNotValid = 0;
        }
        while(nNotValid);
        if(nInput == 0) return;
        system("cls");
    }
    while(1);
    printf("\nStudent information:\n");

    printf("\t1. Class Name:     %s\n", pStudentInfo[index].sClassName);
    printf("\t2. Student ID:     %s\n", pStudentInfo[index].sStudentID);
    printf("\t3. Student Name:   %s\n", pStudentInfo[index].sStudentName);
    printf("\t4. Workshop:       %.1lf\n", pStudentInfo[index].dWorkshop);
    printf("\t5. Progress Test:  %.1lf\n", pStudentInfo[index].dProgressTest);
    printf("\t6. Assignment:     %.1lf\n", pStudentInfo[index].dAssignment);
    printf("\t7. Practical Exam: %.1lf\n", pStudentInfo[index].dPracticalExam);
    printf("\t8. Final Exam:     %.1lf\n", pStudentInfo[index].dFinalExam);
    printf("\nWhich information do you want to update?\n");
    printf("\t(Enter '0' if you do not want to change anything)\n");
    do
    {
        printf("\nEnter your choice: ");
        nScanfRet = scanf("%d%c", &nInput, &cInput);
        if(nScanfRet < 2 || cInput != '\n')
        {
            printf("\nYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(nInput < 0 || nInput > 8)
        {
            printf("\nYour choice is not valid. Please try again!\n");
        }
        else
            nNotValid = 0;
    }
    while(nNotValid);
    switch(nInput)
    {
    case 0:
        return;
    case 1:
        do //Class Name
        {
            printf("Enter new Class Name: ");
            scanf("%[^\n]%*c", &pStudentInfo[index].sClassName);
            fflush(stdin);
        }
        while(nCheckClassName(pStudentInfo[index].sClassName));
        break;
    case 2:
        do //Student ID
        {
            printf("Enter new Student ID: ");
            scanf("%[^\n]%*c", &pStudentInfo[index].sStudentID);
            fflush(stdin);
        }
        while(nCheckStudentID(pStudentInfo, nNumberStudent, index));
        break;
    case 3:
        printf("Enter new Student Name: ");
        scanf("%30[^\n]", &pStudentInfo[index].sStudentName);
        fflush(stdin);
        break;
    case 4:
        do //Workshop
        {
            printf("Enter new Workshop grade: ");
            nScanfRet = scanf("%lf", &pStudentInfo[index].dWorkshop);
        }
        while(nGradeValidation(pStudentInfo[index].dWorkshop, nScanfRet));
        break;
    case 5:
        do //Progress Test
        {
            printf("Enter new Progress Test grade: ");
            nScanfRet = scanf("%lf", &pStudentInfo[index].dProgressTest);
        }
        while(nGradeValidation(pStudentInfo[index].dProgressTest, nScanfRet));
        break;
    case 6:
        do //Assignment
        {
            printf("Enter new Assignment grade: ");
            nScanfRet = scanf("%lf", &pStudentInfo[index].dAssignment);
        }
        while(nGradeValidation(pStudentInfo[index].dAssignment, nScanfRet));
        break;
    case 7:
        do //Practical Exam
        {
            printf("Enter new Practical Exam grade: ");
            nScanfRet = scanf("%lf", &pStudentInfo[index].dPracticalExam);
        }
        while(nGradeValidation(pStudentInfo[index].dPracticalExam, nScanfRet));
        break;
    case 8:
        do //Final Exam
        {
            printf("Enter new Final Exam grade: ");
            nScanfRet = scanf("%lf", &pStudentInfo[index].dFinalExam);
        }
        while(nGradeValidation(pStudentInfo[index].dFinalExam, nScanfRet));
        break;
    }
    nChangeStatus = 1;
    int nChoice;
    do
    {
        nChoice = nMakeChoice_f(0, 1);
        if(nChoice)
            goto do_f3;
    }
    while(nChoice);
}

void f4_DeleteStudent(student *pStudentInfo, int *nNumberStudent)
{
    char StudentID[9];
    int index = -1;
    int nScanfRet, nInput, nNotValid = 1;
    char cInput;

do_f4:
    do
    {
        printf("Enter Student ID: ");
        scanf("%[^\n]%*c", StudentID);

        index = nFindStudentID(StudentID, pStudentInfo, *nNumberStudent);
    }
    while (index == -1);
    printf("Student information:\n");
    printf("Class name:     %s\n", pStudentInfo[index].sClassName);
    printf("Student ID:     %s\n", pStudentInfo[index].sStudentID);
    printf("Student name:   %s\n", pStudentInfo[index].sStudentName);
    printf("Workshop:       %.1lf\n", pStudentInfo[index].dWorkshop);
    printf("Progress test:  %.1lf\n", pStudentInfo[index].dProgressTest);
    printf("Assignment:     %.1lf\n", pStudentInfo[index].dAssignment);
    printf("Practical exam: %.1lf\n", pStudentInfo[index].dPracticalExam);
    printf("Final exam:     %.1lf\n", pStudentInfo[index].dFinalExam);
    printf("Avg Grade:      %.1lf\n", dAvgGrade(pStudentInfo[index]));
    printf("Status:         %s\n", (nCheckPassed(pStudentInfo[index]) == 1)?"Passes":"Failed");

    printf("\nDo you want to delete this student's information?\n");
    printf("\t1. Yes\n");
    printf("\t0. No\n");
    do
    {
        printf("\nEnter your choice: ");
        nScanfRet = scanf("%d%c", &nInput, &cInput);
        if(nScanfRet < 2 || cInput != '\n')
        {
            printf("\nYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(nInput < 0 || nInput > 1)
        {
            printf("\nYour choice is not valid. Please try again!\n");
        }
        else
            nNotValid = 0;
    }
    while(nNotValid);
    if(nInput)
    {
        nChangeStatus = 1;
        (*nNumberStudent)--;
        for(int i = index; i < (*nNumberStudent); i++)
            pStudentInfo[i] = pStudentInfo[i+1];
    }
    int nChoice;
    do
    {
        nChoice = nMakeChoice_f(0, 1);
        if(nChoice)
            goto do_f4;
    }
    while(nChoice);
}

void f5_SortBy(student *pStudentInfo, int nNumberStudent)
{
    int nNotValid = 1, nInput1, nInput2, nScanfRet;
    char cInput;
do_f5:
    printf("You want to sort by:\n");
    printf("\t1. Class Name\n");
    printf("\t2. Student ID\n");
    printf("\t3. Student Name\n");
    printf("\t4. Workshop\n");
    printf("\t5. Progress Test\n");
    printf("\t6. Assignment\n");
    printf("\t7. Practical Exam\n");
    printf("\t8. Final Exam\n");
    printf("\t9. Avg Grade\n");
    printf("\t0. Cancel\n");
    do
    {
        printf("\nEnter your choice: ");
        nScanfRet = scanf("%d%c", &nInput1, &cInput);
        if(nScanfRet < 2 || cInput != '\n')
        {
            printf("\tYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(nInput1 < 0 || nInput1 > 9)
        {
            printf("\tYour choice is not valid. Please try again!\n");
        }
        else
            nNotValid = 0;
    }
    while(nNotValid);
    if(nInput1 == 0) return;

    printf("You want to sort from:\n");
    printf("\t1. Smallest to Largest (A to Z)\n");
    printf("\t2. Largest to Smallest (Z to A)\n");
    printf("\t0. Cancel\n");
    nNotValid = 1;
    do
    {
        printf("\nEnter your choice: ");
        nScanfRet = scanf("%d%c", &nInput2, &cInput);
        if(nScanfRet < 2 || cInput != '\n')
        {
            printf("\tYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(nInput2 < 0 || nInput2 > 2)
        {
            printf("\tYour choice is not valid. Please try again!\n");
        }
        else
            nNotValid = 0;
    }
    while(nNotValid);
    if(nInput2 == 0) return;

    nChangeStatus = 1;
    for(int i = 0; i < nNumberStudent - 1; i++)
    {
        for(int j = i+1; j <nNumberStudent; j++)
            ChangeStudent(pStudentInfo, i, j, nInput1, nInput2);
    }

    int nChoice;
    do
    {
        nChoice = nMakeChoice_f(0, 1);
        if(nChoice)
            goto do_f5;
    }
    while(nChoice);
}

void f6_FindStudentGrade(student *pStudentInfo, int nNumberStudent)
{
    //Note: Implement a Keystroke to exit in case of not wanting to f6 anymore
    //1.input StudentCode
    //2.Check valid input
    //3.lookup for data in db
    //4.return grades
    char StudentID[9];
    int index = -1;

    do
    {
        printf("Enter Student ID: ");
        scanf("%[^\n]%*c", StudentID);
        fflush(stdin);

        index = nFindStudentID(StudentID, pStudentInfo, nNumberStudent);
    }
    while (index == -1);

    printf("\nStudent information:\n");

    printf("Class name:     %s\n", pStudentInfo[index].sClassName);
    printf("Student ID:     %s\n", pStudentInfo[index].sStudentID);
    printf("Student name:   %s\n", pStudentInfo[index].sStudentName);
    printf("Workshop:       %.1lf\n", pStudentInfo[index].dWorkshop);
    printf("Progress test:  %.1lf\n", pStudentInfo[index].dProgressTest);
    printf("Assignment:     %.1lf\n", pStudentInfo[index].dAssignment);
    printf("Practical exam: %.1lf\n", pStudentInfo[index].dPracticalExam);
    printf("Final exam:     %.1lf\n", pStudentInfo[index].dFinalExam);
    printf("Avg Grade:      %.1lf\n", dAvgGrade(pStudentInfo[index]));
    printf("Status:         %s\n", (nCheckPassed(pStudentInfo[index]) == 1)?"Passes":"Failed");
}

void f7_ListStudentGradeinClass(student *pStudentInfo, int nNumberStudent)
{
    //Note: Implement a Keystroke to exit in case of not wanting to f7 anymore
    //1.Input StudentGroup
    //2.Loop through all StudentCode in StudentGroup
    //3.Output Grade of each StudentCode of StudentGroup

    char ClassName[7];
    int index = -1;
    double dAvgOfClass = 0;

    do
    {
        printf("Enter Class Name: ");
        scanf("%[^\n]%*c", ClassName);
        fflush(stdin);

        for(int i = 0; i < strlen(ClassName); i++)
        {
            if(ClassName[i] == ' ')
            {
                memmove(ClassName + i, ClassName + i+1, strlen(ClassName + i));
            }

            if(ClassName[i] >= 'a' && ClassName[i] <= 'z')
            {
                ClassName[i] -= ('a' - 'A');
            }
        }

        for(int i = 0; i < nNumberStudent; i++)
        {
            if(strcmp(ClassName, pStudentInfo[i].sClassName) == 0)
            {
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            system("cls");
            printf("Class Name not found, please try again.\n");
        }
    }
    while (index == -1);
    //print top border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+---------+------+");
    printf("\n");

    //print header
    printf("|No.|Class Name|Student ID|%-30s|Workshop|Progress Test|Assignment|Practical Exam|Final Exam|Avg Grade|Status|\n", "Student Name");

    //print bottom border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+---------+------+");
    printf("\n");

    //print data
    for(int i = 0, j = 0; i < nNumberStudent; i++)
    {
        if(strcmp(pStudentInfo[i].sClassName, ClassName) == 0)
        {
            printf("|%3d|%-10s|%-10s|%-30s|%8.1lf|%13.1lf|%10.1lf|%14.1lf|%10.1lf|%9.1lf|%s|\n",
                   ++j,
                   pStudentInfo[i].sClassName,
                   pStudentInfo[i].sStudentID,
                   pStudentInfo[i].sStudentName,
                   pStudentInfo[i].dWorkshop,
                   pStudentInfo[i].dProgressTest,
                   pStudentInfo[i].dAssignment,
                   pStudentInfo[i].dPracticalExam,
                   pStudentInfo[i].dFinalExam,
                   dAvgGrade(pStudentInfo[i]),
                   (nCheckPassed(pStudentInfo[i]) == 1)?"Passes":"Failed");
            dAvgOfClass += dAvgGrade(pStudentInfo[i]);
        }
        if(i == nNumberStudent - 1)
            dAvgOfClass /= j;
    }

    //print bottom border of table
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+---------+------+");
    printf("\n");
    printf("AVERAGE of class %s: %.1lf\n", ClassName, dAvgOfClass);
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
    nChangeStatus = 0;
}

void f0_Exit(student *pStudentInfo, int nNumberStudent)
{
    int nScanfRet, nInput, nNotValid = 1;
    char cInput;
    if(nChangeStatus == 1)
    {
        printf("Do you want to save your changes to text file?\n");
        printf("\t1. Save\n");
        printf("\t0. Don't save\n");
        do
        {
            printf("\nEnter your choice: ");
            nScanfRet = scanf("%d%c", &nInput, &cInput);
            if(nScanfRet < 2 || cInput != '\n')
            {
                printf("\nYour choice is not valid. Please try again!");
                fflush(stdin);
            }
            else if(nInput < 0 || nInput > 1)
            {
                printf("\nYour choice is not valid. Please try again!");
            }
            else
                nNotValid = 0;
        }
        while(nNotValid);
        if(nInput)
            f8_SaveFile(pStudentInfo, nNumberStudent);
    }
}
