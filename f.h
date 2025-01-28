// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdbool.h>

#define MAX_ALUMNI 100
#define MAX_STR_LEN 100

typedef struct
{
    char name[MAX_STR_LEN];
    char kuet_email[MAX_STR_LEN];
    char department[MAX_STR_LEN];
    int passing_year;
    char current_post[MAX_STR_LEN];
    char institution[MAX_STR_LEN];
    char residence[MAX_STR_LEN];
    char experience[MAX_STR_LEN];
    bool PhD;
    char marital_status[MAX_STR_LEN];
    char contact_number[MAX_STR_LEN];
    int strikes;
    char password[MAX_STR_LEN];
} Alumni;

// Modify the JobPost structure to ensure required_cgpa is float
typedef struct
{
    char title[MAX_STR_LEN];       // Job title with multiple words
    char institution[MAX_STR_LEN]; // Institution name with multiple words
    int salary;
    char required_cgpa[MAX_STR_LEN]; // Required CGPA as a string
    char deadline[MAX_STR_LEN];      // Application deadline as a string
    char skills[MAX_STR_LEN];        // Skills required with multiple words
} JobPost;

typedef struct
{
    char name[MAX_STR_LEN];
    int day;
    char month[MAX_STR_LEN]; // To store the month name
    int year;
} Event;

extern JobPost job_posts[MAX_ALUMNI];
extern int job_count;

extern Event events[MAX_ALUMNI];
extern int event_count;

// Function Prototypes
void load_data(Alumni alumni[], int *count);
void save_data(Alumni alumni[], int count);
void view_alumni(Alumni alumni[], int count);
void view_alumni_sorted(Alumni alumni[], int count);
void add_strike(Alumni alumni[], int *count);
void sign_up();
void admin_menu(Alumni alumni[], int *count); // Add this declaration
void admin_login();
void alumni_login();
void alumni_menu(Alumni *alumni);
void post_job();
void edit_profile(Alumni *alumni);
void create_event();
void view_available_job_posts();
void view_events_created_by_admin();
void student_menu();

#endif // FUNCTIONS_H
