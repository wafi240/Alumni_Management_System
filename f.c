#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>

#define admin_PASS "admin123"
#define max_string_len 100
#define max_Jobs 100
#define max_Events 100
#define max_Alumni 100

// Structure for Alumni
typedef struct
{
    char name[max_string_len];
    char kuet_email[max_string_len];
    char department[max_string_len];
    int batch;
    char current_post[max_string_len];
    char institution[max_string_len];
    char residence[max_string_len];
    char experience[max_string_len];
    int PhD;
    char marital_status[max_string_len];
    char contact_number[max_string_len];
    int strikes;
    char password[max_string_len];
} Alumni;

// Structure for Job Post
typedef struct
{
    char title[max_string_len];       // Job title with multiple words
    char institution[max_string_len]; // Institution name with multiple words
    int salary;
    char required_cgpa[max_string_len]; // Required CGPA as a string
    char deadline[max_string_len];      // Application deadline as a string
    char skills[max_string_len];        // Skills required with multiple words
} JobPost;

// Structure for Event
typedef struct
{
    char name[max_string_len];
    int day;
    char month[max_string_len]; // To store the month name
    int year;
} Event;

// Global arrays for job posts and events
JobPost job_posts[max_Jobs];
Event events[max_Events];
int job_count = 0;
int event_count = 0;

// Load alumni data from file
void load_data(Alumni alumni[], int *count)
{
    FILE *file = fopen("alumnii.txt", "r");
    if (!file)
    {

        printf("------------------------------------------------\n");
        printf("|      No data file found. Starting fresh.     |\n");
        printf("------------------------------------------------\n");

        *count = 0;
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^,],%[^,],%[^,],%d,%[^,],%[^,],%[^,],%[^,],%d,%[^,],%[^,],%d,%[^\n]\n",
                  alumni[*count].name, alumni[*count].kuet_email, alumni[*count].department,
                  &alumni[*count].batch, alumni[*count].current_post, alumni[*count].institution,
                  alumni[*count].residence, alumni[*count].experience, &alumni[*count].PhD,
                  alumni[*count].marital_status, alumni[*count].contact_number, &alumni[*count].strikes,
                  alumni[*count].password) != EOF)
    {
        (*count)++;
    }

    fclose(file);
}

// Save alumni data to file
void save_data(Alumni alumni[], int count)
{
    FILE *file = fopen("alumnii.txt", "w");
    if (!file)
    {
        printf("------------------------------------------------\n");
        printf("|            Error saving data.                |\n");
        printf("------------------------------------------------\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        fprintf(file, "%s,%s,%s,%d,%s,%s,%s,%s,%d,%s,%s,%d,%s\n",
                alumni[i].name, alumni[i].kuet_email, alumni[i].department, alumni[i].batch,
                alumni[i].current_post, alumni[i].institution, alumni[i].residence, alumni[i].experience,
                alumni[i].PhD, alumni[i].marital_status, alumni[i].contact_number, alumni[i].strikes,
                alumni[i].password);
    }

    fclose(file);
}

// View all alumni
void view_alumni(Alumni alumni[], int count)
{
    printf("------------------------------------------------\n");
    printf("|                 Alumni list                  |\n");
    printf("------------------------------------------------\n");
    for (int i = 0; i < count; i++)
    {
        printf("\n%d. %s     (%s , 2k%d) %s\n", i + 1, alumni[i].name, alumni[i].department,
               alumni[i].batch % 100, alumni[i].contact_number);
    }
}

// Sort and view alumni
void view_alumni_sorted(Alumni alumni[], int count)
{
    int choice;
    printf("Sort alumni by:\n");
    printf("1. Passing Year\n2. Department\n3. Name Alphabetically\n4. Age\n");
    printf("\nEnter your choice: ");
    scanf("%d", &choice);

    // Sort logic
    if (choice == 1)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (alumni[i].batch > alumni[j].batch)
                {
                    Alumni temp = alumni[i];
                    alumni[i] = alumni[j];
                    alumni[j] = temp;
                }
            }
        }
    }
    else if (choice == 2)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (strcmp(alumni[i].department, alumni[j].department) > 0)
                {
                    Alumni temp = alumni[i];
                    alumni[i] = alumni[j];
                    alumni[j] = temp;
                }
            }
        }
    }
    else if (choice == 3)
    {
        for (int i = 0; i < count - 1; i++)
        {
            for (int j = i + 1; j < count; j++)
            {
                if (strcmp(alumni[i].name, alumni[j].name) > 0)
                {
                    Alumni temp = alumni[i];
                    alumni[i] = alumni[j];
                    alumni[j] = temp;
                }
            }
        }
    }

    view_alumni(alumni, count);
}

// Add a strike to an alumni
void add_strike(Alumni alumni[], int *count)
{
    char mail[max_string_len];
    printf("Enter the KUET Email of the alumni to add a strike: ");
    scanf("%s", mail);

    for (int i = 0; i < *count; i++)
    {
        if (strcmp(alumni[i].kuet_email, mail) == 0)
        {
            alumni[i].strikes++;
            if (alumni[i].strikes >= 3)
            {
                printf("%s has been banned due to 3 strikes and is no longer in the alumni list.\n", alumni[i].name);
                for (int j = i; j < *count - 1; j++)
                {
                    alumni[j] = alumni[j + 1];
                }
                (*count)--;
            }
            else
            {
                printf("Strike added to %s. Total strikes: %d\n", alumni[i].name, alumni[i].strikes);
            }
            return;
        }
    }

    printf("Alumni not found.\n");
}

// Sign up a new alumnus
void sign_up()
{
    Alumni alumni[max_Alumni];
    int count;
    load_data(alumni, &count);
    // check if it has reached to its capacity or not
    if (count >= max_Alumni)
    {
        printf("Alumni database is full.\n");
        return;
    }

    Alumni new_alumni;

    printf("Enter your short name: ");
    scanf("%s", new_alumni.name);

    // Email input with validation
    while (true)
    {
        printf("Enter your KUET email : ");
        scanf("%s", new_alumni.kuet_email);

        if (strstr(new_alumni.kuet_email, "@stud.kuet.ac.bd")
            // Check if the email contains @stud.kuet.ac.bd
            &&
            strcmp(new_alumni.kuet_email + strlen(new_alumni.kuet_email) - strlen("@stud.kuet.ac.bd"), "@stud.kuet.ac.bd") == 0)
        // Moves the pointer to the position in the email string where the substring @stud.kuet.ac.bd would start if it were at the end.
        {
            break; // Valid email
        }
        else
        {
            while (1)
            {
                printf("\nInvalid email domain.\n");

                printf("------------------------------------------------\n");
                printf("|           Press 1 to try again               |\n");
                printf("|       Press 0 to return to main menu         |\n");
                printf("------------------------------------------------\n");
                int a;
                scanf("%d", &a);
                if (a == 1)
                {
                    sign_up;
                    break;
                }
                else if (a == 0)
                {
                    return;
                }
                else
                {
                    printf("\n.....Invalid input\n");
                }
                getchar();
            }

            // Exit the function to go back to the main menu
        }
    }

    printf("Enter your department: ");
    scanf("%s", new_alumni.department);
    printf("Enter your HSC passing year(####): ");
    scanf("%d", &new_alumni.batch);
    printf("Enter your current post: ");
    getchar(); // clear newline
    fgets(new_alumni.current_post, max_string_len, stdin);
    new_alumni.current_post[strcspn(new_alumni.current_post, "\n")] = 0; // Remove the newline character

    printf("Enter your institution: ");
    scanf("%s", new_alumni.institution);
    printf("Enter your residence (Foreign/BD):\n");
    printf("If foreign, mention only country. If country mention only district : ");
    scanf("%s", new_alumni.residence);
    printf("Enter years of experience: ");
    scanf("%s", new_alumni.experience); // Change to read years as a string
    printf("Do you have a PhD (1 for yes, 0 for no): ");
    scanf("%d", (int *)&new_alumni.PhD);
    printf("Enter your marital status: ");
    scanf("%s", new_alumni.marital_status);
    printf("Enter your contact number: ");
    scanf("%s", new_alumni.contact_number);
    printf("Set your password: ");
    scanf("%s", new_alumni.password);

    new_alumni.strikes = 0;

    alumni[count++] = new_alumni;
    save_data(alumni, count);
    printf("------------------------------------------------\n");
    printf("|              Sign-up successful.             |\n");
    printf("------------------------------------------------\n");
    printf("\n");
}

// Admin menu function
void create_event()
{
    if (event_count >= max_Events)
    {
        printf("Event list is full. Cannot add more events.\n");
        return;
    }

    // Clear the input buffer before reading the event name
    while (getchar() != '\n')
        ; // This will flush the input buffer

    printf("Enter event name: ");
    fgets(events[event_count].name, max_string_len, stdin);
    events[event_count].name[strcspn(events[event_count].name, "\n")] = 0; // Remove the newline character

    // Read the date input as a string
    char date_input[max_string_len];
    printf("Enter event date\nformat: DD MMM YYYY\n(25 JAN 2023): ");
    fgets(date_input, max_string_len, stdin);

    // Parse the date
    if (sscanf(date_input, "%d %s %d", &events[event_count].day, events[event_count].month, &events[event_count].year) != 3)
    // !3 checks how many output sscanf has succesfully taken
    {
        printf("Invalid date format.\n");
        return;
    }

    event_count++;
    printf("------------------------------------------------\n");
    printf("|            Event created successfully.       |\n");
    printf("------------------------------------------------\n");
}

void admin_menu(Alumni alumni[], int *count);
// Admin login function
void admin_login()
{
    char password[max_string_len];
    int i = 0;
    char ch;

    printf("Enter admin password: ");

    // Loop to get password character by character
    while (1)
    {
        ch = getch(); // Get a character without displaying it in console
        if (ch == '\r' || ch == '\n')
        { // Enter key pressed
            break;
        }
        else if (ch == 8)
        { // Backspace key pressed
            if (i > 0)
            {
                i--;             // Decrement index
                printf("\b \b"); // Move back, print space, move back again
            } // |_|
        }
        else if (i < max_string_len - 1)//to store null char , it is empty
        {
            password[i++] = ch; // Store character
            printf("*");        // Print asterisk
        }
    }
    password[i] = '\0'; // Null-terminate the string

    printf("\n");

    // Check the password
    if (strcmp(password, admin_PASS) == 0)
    {
        Alumni alumni[max_Alumni];
        int count;
        load_data(alumni, &count);
        admin_menu(alumni, &count);
    }
    else
    {
        printf("Incorrect password.\n");
    }
}
void alumni_menu(Alumni *alumni);
// Alumni login function
void alumni_login()
{
    Alumni alumni[max_Alumni];
    int count;
    load_data(alumni, &count);

    char mail[max_string_len];
    char password[max_string_len];
    int i = 0;
    char ch;

    printf("Enter your KUET mail: ");
    scanf("%s", mail);

    printf("Enter your password: ");

    // Loop to get password character by character
    while (1)
    {
        ch = getch(); // Get a character without echoing it
        if (ch == '\r')
        { // Enter key pressed
            break;
        }
        else if (ch == 8)
        { // Backspace key pressed
            if (i > 0)
            {
                i--;             // Decrement index
                printf("\b \b"); // Move back, print space, move back again
            }
        }
        else if (i < max_string_len - 1)
        {
            password[i++] = ch; // Store character
            printf("*");        // Print asterisk
        }
    }
    password[i] = '\0'; // Null-terminate the string

    printf("\n");

    // Validate credentials
    for (int j = 0; j < count; j++)
    {
        if (strcmp(alumni[j].kuet_email, mail) == 0 && strcmp(alumni[j].password, password) == 0)
        {
            alumni_menu(&alumni[j]);
            return;
        }
    }

    printf("\n.......Login failed. Please check your credentials.......\n");
}

// edit profile
void edit_profile(Alumni *alumni)
{
    getchar();
    printf("Editing Profile for: %s\n", alumni->name);

    printf("Edit name (current: %s): ", alumni->name);
    fgets(alumni->name, max_string_len, stdin);
    alumni->name[strcspn(alumni->name, "\n")] = 0;

    printf("Edit department (current: %s): ", alumni->department);
    fgets(alumni->department, max_string_len, stdin);
    alumni->department[strcspn(alumni->department, "\n")] = 0;

    printf("Edit passing year (current: %d): ", alumni->batch);
    scanf("%d", &alumni->batch);

    printf("Enter new current post (current: %s): ", alumni->current_post);
    getchar(); // Clear newline
    fgets(alumni->current_post, max_string_len, stdin);
    alumni->current_post[strcspn(alumni->current_post, "\n")] = 0;

    printf("Enter new institution (current: %s): ", alumni->institution);
    fgets(alumni->institution, max_string_len, stdin);
    alumni->institution[strcspn(alumni->institution, "\n")] = 0;

    printf("Enter new residence (current: %s): ", alumni->residence);
    fgets(alumni->residence, max_string_len, stdin);
    alumni->residence[strcspn(alumni->residence, "\n")] = 0;

    printf("Update years of experience (current: %s): ", alumni->experience);
    fgets(alumni->experience, max_string_len, stdin);
    alumni->experience[strcspn(alumni->experience, "\n")] = 0;

    printf("Do you have a PhD? (current: %d): ", alumni->PhD);
    scanf("%d", &alumni->PhD);

    printf("Edit your marital status (current: %s): ", alumni->marital_status);
    getchar(); // Clear newline
    fgets(alumni->marital_status, max_string_len, stdin);
    alumni->marital_status[strcspn(alumni->marital_status, "\n")] = 0;

    printf("Edit contact number (current: %s): ", alumni->contact_number);
    fgets(alumni->contact_number, max_string_len, stdin);
    alumni->contact_number[strcspn(alumni->contact_number, "\n")] = 0;
    printf("*--------------------------------------------- *\n");
    printf("         Profile updated successfully!          \n");
    printf("*----------------------------------------------*\n");
}

void post_job();
// Alumni menu
void alumni_menu(Alumni *alumni)
{
    int choice;

    while (1)
    {

        printf("*--------------------------------------------- *\n");
        printf("|                                              |\n");
        printf("|                  Alumni Menu                 |\n");
        printf("|                                              |\n");
        printf("*----------------------------------------------*\n");

        printf("\n==========  ==========");
        printf("\n1. View Profile\n2. Post Job\n3. Edit Profile\n4. log-out\n\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("------------------------------------------------\n");
            printf("|                    Profile                    |\n");
            printf("------------------------------------------------\n");

            printf("\nName: %s\nEmail: %s\nDepartment: %s\nPassing YeaBatch: %d\nPost: %s\nInstitution: %s\n",
                   alumni->name, alumni->kuet_email, alumni->department, alumni->batch,
                   alumni->current_post, alumni->institution);
            break;
        case 2:
            post_job();
            break;
        case 3:
            edit_profile(alumni); // Call the edit profile function
            break;

        case 4:
            return; // Logout
        default:
            printf("\n .....Invalid choice. Please try again.......\n");
        }
    }
}

// Post a job opportunity

void post_job()
{
    if (job_count >= max_Jobs)
    {
        printf("\n.....Job posts are full. Cannot add more jobs.\n");
        return;
    }

    printf("Enter job title: ");
    getchar(); // Clear any leftover newline
    fgets(job_posts[job_count].title, max_string_len, stdin);
    job_posts[job_count].title[strcspn(job_posts[job_count].title, "\n")] = 0; // Remove newline

    printf("Enter institution: ");
    fgets(job_posts[job_count].institution, max_string_len, stdin);
    job_posts[job_count].institution[strcspn(job_posts[job_count].institution, "\n")] = 0; // Remove newline

    printf("Enter salary: ");
    scanf("%d", &job_posts[job_count].salary);

    printf("Enter required CGPA: ");                                                           // Message updated to reflect string input
    getchar();                                                                                 // Clear newline
    fgets(job_posts[job_count].required_cgpa, max_string_len, stdin);                          // Accept CGPA as string
    job_posts[job_count].required_cgpa[strcspn(job_posts[job_count].required_cgpa, "\n")] = 0; // Remove newline

    printf("Enter application deadline: ");
    fgets(job_posts[job_count].deadline, max_string_len, stdin);                     // Accept deadline as string
    job_posts[job_count].deadline[strcspn(job_posts[job_count].deadline, "\n")] = 0; // Remove newline

    printf("Enter skills requirement\n(Multiple skills are allowed):\n");
    fgets(job_posts[job_count].skills, max_string_len, stdin);                   // Accept skills as multiple words
    job_posts[job_count].skills[strcspn(job_posts[job_count].skills, "\n")] = 0; // Remove newline

    job_count++;

    printf("------------------------------------------------\n");
    printf("|           Job posted successfully            |\n");
    printf("------------------------------------------------\n");
}

// Viewing available job posts
void view_available_job_posts()
{
    printf("------------------------------------------------\n");
    printf("|             Available Job Posts               |\n");
    printf("------------------------------------------------\n");

    if (job_count == 0)
    {
        printf("\nNo job posts available.\n");
        return;
    }
    for (int i = 0; i < job_count; i++)
    {
        printf("\n%d. Title: %s\n   Institution: %s\n   Salary: %d\n   Required CGPA: %s\n   Deadline: %s\n   Skills: %s\n",
               i + 1,
               job_posts[i].title,
               job_posts[i].institution,
               job_posts[i].salary,
               job_posts[i].required_cgpa, // Output as string
               job_posts[i].deadline,      // Output as string
               job_posts[i].skills);
    }
}

// Viewing events created by the admin
void view_events_created_by_admin()
{
    printf("------------------------------------------------\n");
    printf("|              View upcoming events            |\n");
    printf("------------------------------------------------\n");
    if (event_count == 0)
    {
        printf("No events available.\n");
        return;
    }
    for (int i = 0; i < event_count; i++)
    {
        printf("\n%d. Event: %s\n   Date: %s %d %d\n",
               i + 1,
               events[i].name,
               events[i].month,
               events[i].day,
               events[i].year);
    }
}

// Student segment functions
void student_menu()
{
    Alumni alumni[max_Alumni];
    int count;
    load_data(alumni, &count);

    int choice;

    while (1)
    {
        printf("------------------------------------------------\n");
        printf("|                                              |\n");
        printf("|                 Student Menu                 |\n");
        printf("|                                              |\n");
        printf("------------------------------------------------\n");
        printf("\n1. View Alumni\n2. View Available Job Posts\n3. View Upcoming Events\n4. Back\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            view_alumni_sorted(alumni, count);
            break;
        case 2:
            view_available_job_posts(); // Call to display job posts
            break;
        case 3:
            view_events_created_by_admin(); // Call to display events
            break;
        case 4:
            return; // Back to main menu
        default:
            printf("\n.....Invalid choice. Please try again.\n");
            getchar();
        }
    }
}
// Admin menu function
void search_alumni_by_email(Alumni alumni[], int count)
{
    char email[max_string_len];
    printf("Enter KUET email: ");
    scanf("%s", email);

    bool found = false;
    for (int i = 0; i < count; i++)
    {
        if (strcmp(alumni[i].kuet_email, email) == 0)
        {
            printf("\nAlumni Found:\n");
            printf("Name: %s\n", alumni[i].name);
            printf("Department: %s\n", alumni[i].department);
            printf("Batch: %d\n", alumni[i].batch);
            printf("Current Post: %s\n", alumni[i].current_post);
            printf("Institution: %s\n", alumni[i].institution);
            printf("KUET mail: %s\n", alumni[i].kuet_email);
            found = true;
            break;
        }
    }

    if (!found)
    {
        printf("\n....Alumni with the given email not found.\n");
    }
}

// Admin menu function
void admin_menu(Alumni alumni[], int *count)
{
    int choice;

    while (1)
    {
        printf("------------------------------------------------\n");
        printf("|                                              |\n");
        printf("|                  Admin Menu                  |\n");
        printf("|                                              |\n");
        printf("------------------------------------------------\n");
        printf("\n1. View Alumni\n2. Add Strike\n3. Create Event\n4. Search Alumni by Email\n5. Logout\n");
        printf("\nEnter your choice: ");
        scanf("%d", &choice);
        printf("\n");
        switch (choice)
        {
        case 1:
            view_alumni_sorted(alumni, *count); // Viewing all alumni with sorting options
            break;
        case 2:
            add_strike(alumni, count); // Adding strike to an alumni
            save_data(alumni, *count); // Save changes after adding a strike
            break;
        case 3:
            create_event(); // Create a new event
            break;
        case 4:
            search_alumni_by_email(alumni, *count); // Search alumni by email
            break;
        case 5:
            printf("Logging out...\n");
            return; // Logout and exit the menu
        default:
            printf("Invalid choice. Please try again.\n");
        }
    }
}
