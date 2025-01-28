// main.c
#include <stdio.h>
#include "f.h"

int main()
{
    int choice;

    printf("+----------------------------------------------+\n");
    printf("|                                              |\n");
    printf("|     Welcome to Alumni Management System      |\n");
    printf("|                                              |\n");
    printf("+----------------------------------------------+\n");

    while (1)
    {
        printf("------------------------------------------------\n");
        printf("|                                              |\n");
        printf("|                  Main Menu                   |\n");
        printf("|                                              |\n");
        printf("------------------------------------------------\n");
        printf("\n1. Admin Segment\n2. Alumni Segment\n3. Student Segment\n4. Exit\n");
        printf("Press 1/2/3/4: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            admin_login(); // Admin functionalities
            break;
        case 2:
        {
            int alumni_choice;
            printf("------------------------------------------------\n");
            printf("|                 Alumni Segment                |\n");
            printf("------------------------------------------------\n");
            printf("1. Alumni Login\n2. Alumni Sign Up\n");
            printf("Enter your choice: ");
            scanf("%d", &alumni_choice);

            switch (alumni_choice)
            {
            case 1:
                alumni_login(); // Alumni login functionalities
                break;
            case 2:
                sign_up(); // Alumni sign-up functionalities
                break;
            default:
                printf("Invalid choice. Please try again.\n");
            }
        }
        break;
        case 3:
            student_menu(); // Student functionalities
            break;
        case 4:
            printf("Exiting program.\n");
            return 0; // Exit from the program
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }

    return 0; // Redundant as the loop will exit on option 4
}
