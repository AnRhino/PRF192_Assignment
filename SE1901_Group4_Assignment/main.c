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
int nCheckPassed(student StudentInfo); //completed
int nGradeValidation(double dGrade, int nScanfRet); //Used to check input

void f1_PrintAll(student *pStudentInfo, int nNumberStudent); //completed
void f2_AddStudent(student *pStudentInfo, int *nNumberStudent); //completed
void f3_UpdateInfo(); //Nhut is cooking
void f4_DeleteStudent(student *pStudentInfo, int *nNumberStudent); //completed
void f5_SortBy(); //Hao is cooking
void f6_FindStudentGrade(student *pStudentInfo, int nNumberStudent); //Completed
void f7_ListStudentGradeinClass(student *pStudentInfo, int nNumberStudent); //Completed
void f8_SaveFile(student *pStudentInfo, int nNumberStudent); //completed
void f0_Exit(student *pStudentInfo, int nNumberStudent); //completed

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
            f0_Exit(pStudentInfo, nNumberStudent);
            break;
        case 1:
            f1_PrintAll(pStudentInfo, nNumberStudent);
            break;
        case 2:
            f2_AddStudent(pStudentInfo, &nNumberStudent);
            break;
        case 3:
            f3_UpdateInfo();
            break;
        case 4:
            f4_DeleteStudent(pStudentInfo, &nNumberStudent);
            break;
        case 5:
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

void f1_PrintAll(student *pStudentInfo, int nNumberStudent)
{
    //print top border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");

    //print header
    printf("|No.|Class Name|Student ID|%-30s|Workshop|Progress Test|Assignment|Practical Exam|Final Exam|Status|\n", "Student Name");

    //print bottom border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");

    //print data
    for(int i = 0; i < nNumberStudent; i++)
    {
        printf("|%3d|%-10s|%-10s|%-30s|%8.1lf|%13.1lf|%10.1lf|%14.1lf|%10.1lf|%s|\n",
               i + 1,
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
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");
}

void f2_AddStudent(student *pStudentInfo, int *nNumberStudent)
{
    int nCheckClassName = 1;
    int nCheckStudentID = 1;
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
        for(int i = 0; i < strlen(pStudentInfo[(*nNumberStudent)-1].sClassName); i++)
        {
            if(pStudentInfo[(*nNumberStudent)-1].sClassName[i] == ' ')
            {
                memmove(pStudentInfo[(*nNumberStudent)-1].sClassName + i,
                        pStudentInfo[(*nNumberStudent)-1].sClassName + i+1,
                        strlen(pStudentInfo[(*nNumberStudent)-1].sClassName + i));
            }

            if(pStudentInfo[(*nNumberStudent)-1].sClassName[i] >= 'a' &&
               pStudentInfo[(*nNumberStudent)-1].sClassName[i] <= 'z')
            {
                pStudentInfo[(*nNumberStudent)-1].sClassName[i] -= ('a' - 'A');
            }
        }
        if(strlen(pStudentInfo[(*nNumberStudent)-1].sClassName) != 6)
        {
            printf("\t\tClass Name is not in the correct format, please try again.\n");
            continue;
        }
        char sMajor[12][3] = {"AI", "BA", "EL", "GD", "HM", "IA", "IB", "JL", "KR", "MC", "SE", "TM"};
        char sMajorName[3];
        strcpy(sMajorName, pStudentInfo[(*nNumberStudent)-1].sClassName);
        sMajorName[2] = '\0';

        nCheckClassName = 0;
        for(int i = 0; i < 12; i++)
        {
            nCheckClassName = strcmp(sMajorName, sMajor[i]);
            if(nCheckClassName == 0)
            {
                break;
            }
        }
        if(nCheckClassName)
        {
            printf("\t\tClass Name is not in the correct format, please try again.\n");
            continue;
        }

        if(atoi(pStudentInfo[(*nNumberStudent)-1].sClassName + 2) == 0)
        {
            printf("\t\tClass Name is not in the correct format, please try again.\n");
            nCheckClassName = 1;
            continue;
        }
    } while(nCheckClassName);

    do //Student ID
    {
        printf("\tStudent ID: ");
        scanf("%[^\n]%*c", &pStudentInfo[(*nNumberStudent)-1].sStudentID);

        for(int i = 0; i < strlen(pStudentInfo[(*nNumberStudent)-1].sStudentID); i++)
        {
            if(pStudentInfo[(*nNumberStudent)-1].sStudentID[i] == ' ')
            {
                memmove(pStudentInfo[(*nNumberStudent)-1].sStudentID + i,
                        pStudentInfo[(*nNumberStudent)-1].sStudentID + i+1,
                        strlen(pStudentInfo[(*nNumberStudent)-1].sStudentID + i));
            }

            if(pStudentInfo[(*nNumberStudent)-1].sStudentID[i] >= 'a' &&
               pStudentInfo[(*nNumberStudent)-1].sStudentID[i] <= 'z')
            {
                pStudentInfo[(*nNumberStudent)-1].sStudentID[i] -= ('a' - 'A');
            }
        }

        if(strlen(pStudentInfo[(*nNumberStudent)-1].sStudentID) != 8)
        {
            printf("\t\tStudent ID is not in the correct format, please try again.\n");
            continue;
        }

        if(pStudentInfo[(*nNumberStudent)-1].sStudentID[0] != 'C' &&
           pStudentInfo[(*nNumberStudent)-1].sStudentID[0] != 'H' &&
           pStudentInfo[(*nNumberStudent)-1].sStudentID[0] != 'S' &&
           pStudentInfo[(*nNumberStudent)-1].sStudentID[0] != 'Q' &&
           pStudentInfo[(*nNumberStudent)-1].sStudentID[0] != 'D')
        {
            printf("\t\tStudent ID is not in the correct format, please try again.\n");
            continue;
        }

        if(pStudentInfo[(*nNumberStudent)-1].sStudentID[1] != 'S' &&
           pStudentInfo[(*nNumberStudent)-1].sStudentID[1] != 'E' &&
           pStudentInfo[(*nNumberStudent)-1].sStudentID[1] != 'A')
        {
            printf("\t\tStudent ID is not in the correct format, please try again.\n");
            continue;
        }

        if(atoi(pStudentInfo[(*nNumberStudent)-1].sStudentID + 2) == 0)
        {
            printf("\t\tStudent ID is not in the correct format, please try again.\n");
            continue;
        }

        nCheckStudentID = 0;
        for(int i = 0; i < (*nNumberStudent)-1; i++)
        {
            if(strcmp(pStudentInfo[(*nNumberStudent)-1].sStudentID, pStudentInfo[i].sStudentID) == 0)
            {
                nCheckStudentID = 1;
                break;
            }
        }
        if(nCheckStudentID)
        {
            printf("\t\tStudent ID already exists, please try again.\n");
            continue;
        }

    } while (nCheckStudentID);
    printf("\tStudent Name: ");
    scanf("%30[^\n]%*[^\n]%*c", &pStudentInfo[(*nNumberStudent)-1].sStudentName);

    printf("Please enter grades for the new student:\n");
    int nScanfRet;
    do //Workshop
    {
        printf("\tWorkshop: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dWorkshop);
    } while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dWorkshop, nScanfRet));
    do //Progress Test
    {
        printf("\tProgress Test: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dProgressTest);
    } while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dProgressTest, nScanfRet));
    do //Assignment
    {
        printf("\tAssignment: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dAssignment);
    } while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dAssignment, nScanfRet));
    do //Practical Exam
    {
        printf("\tPractical Exam: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dPracticalExam);
    } while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dPracticalExam, nScanfRet));
    do //Final Exam
    {
        printf("\tFinal Exam: ");
        nScanfRet = scanf("%lf", &pStudentInfo[(*nNumberStudent)-1].dFinalExam);
    } while(nGradeValidation(pStudentInfo[(*nNumberStudent)-1].dFinalExam, nScanfRet));
    int nChoice;
    do
    {
        nChoice = nMakeChoice_f(0, 1);
        if(nChoice)
            goto do_f2;
    } while(nChoice);
}

void f3_UpdateInfo()
{
    printf("Write your code here to implement the update_grade() function.\n");
}

void f4_DeleteStudent(student *pStudentInfo, int *nNumberStudent)
{
    char StudentID[9];
    int index = -1;
    int nScanfRet, nInput, nNotValid;
    char cInput;

    do_f4:
    do
    {
        printf("Enter Student ID: ");
        scanf("%[^\n]%*c", StudentID);

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

        for(int i = 0; i < (*nNumberStudent); i++)
        {
            if(strcmp(StudentID, pStudentInfo[i].sStudentID) == 0)
            {
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            system("cls");
            printf("Student ID not found, please try again.\n");
        }
    } while (index == -1);
    printf("Student infomation:\n");
    printf("Class name:     %s\n", pStudentInfo[index].sClassName);
    printf("Student ID:     %s\n", pStudentInfo[index].sStudentID);
    printf("Student name:   %s\n", pStudentInfo[index].sStudentName);
    printf("Workshop:       %.1lf\n", pStudentInfo[index].dWorkshop);
    printf("Progress test:  %.1lf\n", pStudentInfo[index].dProgressTest);
    printf("Assignment:     %.1lf\n", pStudentInfo[index].dAssignment);
    printf("Practical exam: %.1lf\n", pStudentInfo[index].dPracticalExam);
    printf("Final exam:     %.1lf\n", pStudentInfo[index].dFinalExam);
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
    } while(nChoice);
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
                index = i;
                break;
            }
        }
        if(index == -1)
        {
            system("cls");
            printf("Student ID not found, please try again.\n");
        }
    } while (index == -1);

    printf("Student infomation:\n");

    printf("Class name:     %s\n", pStudentInfo[index].sClassName);
    printf("Student ID:     %s\n", pStudentInfo[index].sStudentID);
    printf("Student name:   %s\n", pStudentInfo[index].sStudentName);
    printf("Workshop:       %.1lf\n", pStudentInfo[index].dWorkshop);
    printf("Progress test:  %.1lf\n", pStudentInfo[index].dProgressTest);
    printf("Assignment:     %.1lf\n", pStudentInfo[index].dAssignment);
    printf("Practical exam: %.1lf\n", pStudentInfo[index].dPracticalExam);
    printf("Final exam:     %.1lf\n", pStudentInfo[index].dFinalExam);
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

    do
    {
        printf("Enter Class Name: ");
        scanf("%[^\n]%*c", ClassName);

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
    } while (index == -1);
    //print top border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");

    //print header
    printf("|No.|Class Name|Student ID|%-30s|Workshop|Progress Test|Assignment|Practical Exam|Final Exam|Status|\n", "Student Name");

    //print bottom border of header
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");

    //print data
    for(int i = 0, j = 0; i < nNumberStudent; i++)
    {
        if(strcmp(pStudentInfo[i].sClassName, ClassName) == 0)
        {
            printf("|%3d|%-10s|%-10s|%-30s|%8.1lf|%13.1lf|%10.1lf|%14.1lf|%10.1lf|%s|\n",
               ++j,
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
    }

    //print bottom border of table
    printf("+---+----------+----------+------------------------------+--------+-------------+----------+--------------+----------+------+");
    printf("\n");
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
    int nScanfRet, nInput, nNotValid;
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
            f8_SaveFile(pStudentInfo, nNumberStudent);
    }
}
