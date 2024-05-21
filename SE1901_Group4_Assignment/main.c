#include <stdio.h>
#include <stdlib.h>

void print_menu();
int make_choice(int min, int max);
void add_grade();
void update_grade();
void delete_grade();

int main(void)
{
    int choice;

    do
    {
        choice = make_choice(0, 3);
        switch(choice)
        {
        case 0:
            break;
        case 1:
            add_grade();
            break;
        case 2:
            update_grade();
            break;
        case 3:
            delete_grade();
            break;
        }

        if(choice)
        {
            printf("\nPress any key to return to the menu.");
            getchar();
        }
    }
    while(choice);

    return 0;
}

void print_menu()
{
    system("clear"); // for macos, linux
    // system("cls"); // for windows
    printf("GRADING MANAGEMENT SYSTEM\n");
    printf("-------------------------\n");
    printf("1. Display list of students\n");
    printf("2. Add a new student\n");
    printf("3. Delete a student\n");
    printf("4. Update infomation\n");
    printf("5. Check for missing grades\n");
    printf("6. Find student grades by student ID\n");
    printf("7. List students' grades by class ID\n");
    printf("8. Save\n");
    printf("0. Exit\n");
}

int make_choice(int min, int max)
{
    int not_valid = 1, num, scanf_ret;
    char c;

    print_menu();
    fflush(stdin);
    do
    {
        printf("\nEnter your choice: ");
        scanf_ret = scanf("%d%c", &num, &c);
        if(scanf_ret < 2 || c != '\n')
        {
            print_menu();
            printf("\nYour choice is not valid. Please try again!\n");
            fflush(stdin);
        }
        else if(num < min || num > max)
        {
            print_menu();
            printf("\nYour choice is not valid. Please try again!\n");
        }
        else
            not_valid = 0;
    }
    while(not_valid);

    system("clear");

    return num;
}

void add_grade()
{
    printf("Write your code here to implement the add_grade() function.\n");
}

void update_grade()
{
    printf("Write your code here to implement the update_grade() function.\n");
}

void delete_grade()
{
    printf("Write your code here to implement the delete_grade() function.\n");
}
