#include <stdio.h>
#include <string.h>

#define MAX_STUDENTS 50
#define SUBJECTS 5

struct Student
{
    int roll;
    char name[50];
    float marks[SUBJECTS];
    float total;
    float percentage;
    char grade;
    int pass;
};

char gradeCalculate(float percentage)
{
    if (percentage >= 90)
        return 'A';
    else if (percentage >= 80)
        return 'B';
    else if (percentage >= 70)
        return 'C';
    else if (percentage >= 60)
        return 'D';
    else if (percentage >= 50)
        return 'E';
    else if (percentage >= 40)
        return 'P';
    else
        return 'F';
}

void calculateResult(struct Student *s)
{
    s->total = 0;
    s->pass = 1;

    for (int i = 0; i < SUBJECTS; i++)
    {
        s->total += s->marks[i];

        if (s->marks[i] < 40)
            s->pass = 0;
    }

    s->percentage = s->total / SUBJECTS;
    s->grade = gradeCalculate(s->percentage);

    if (s->pass == 0)
        s->grade = 'F';
}

void addStudents(struct Student s[], int *n)
{
    int count;

    printf("\nHow many students do you want to add? ");
    scanf("%d", &count);

    if (count <= 0 || *n + count > MAX_STUDENTS)
    {
        printf("Invalid number or student limit exceeded!\n");
        return;
    }

    for (int i = 0; i < count; i++)
    {
        printf("\n--- Student %d ---\n", *n + 1);

        printf("Enter roll number: ");
        scanf("%d", &s[*n].roll);

        printf("Enter name: ");
        scanf(" %49[^\n]", s[*n].name);

        s[*n].total = 0;

        for (int j = 0; j < SUBJECTS; j++)
        {
            do
            {
                printf("Enter marks in Subject %d (0-100): ", j + 1);
                scanf("%f", &s[*n].marks[j]);

                if (s[*n].marks[j] < 0 || s[*n].marks[j] > 100)
                    printf("Invalid marks! Enter between 0 and 100.\n");

            } while (s[*n].marks[j] < 0 || s[*n].marks[j] > 100);
        }

        calculateResult(&s[*n]);
        (*n)++;
    }

    printf("\nStudent records added successfully!\n");
}

void displayStudent(struct Student s)
{
    printf("\n========== REPORT CARD ==========\n");
    printf("Roll Number : %d\n", s.roll);
    printf("Name        : %s\n", s.name);

    for (int i = 0; i < SUBJECTS; i++)
    {
        printf("Subject %d   : %.2f\n", i + 1, s.marks[i]);
    }

    printf("Total       : %.2f / 500\n", s.total);
    printf("Percentage  : %.2f%%\n", s.percentage);
    printf("Grade       : %c\n", s.grade);

    if (s.pass)
        printf("Result      : PASS\n");
    else
        printf("Result      : FAIL\n");

    printf("==============================\n");
}

void displayAll(struct Student s[], int n)
{
    if (n == 0)
    {
        printf("\nNo student records available!\n");
        return;
    }

    printf("\n========== ALL STUDENTS ==========\n");

    for (int i = 0; i < n; i++)
    {
        printf("\nStudent %d\n", i + 1);
        displayStudent(s[i]);
    }
}

void searchStudent(struct Student s[], int n)
{
    int roll, found = 0;

    printf("\nEnter roll number to search: ");
    scanf("%d", &roll);

    for (int i = 0; i < n; i++)
    {
        if (s[i].roll == roll)
        {
            displayStudent(s[i]);
            found = 1;
            break;
        }
    }

    if (!found)
        printf("\nStudent not found!\n");
}

void classAnalysis(struct Student s[], int n)
{
    if (n == 0)
    {
        printf("\nNo student records available!\n");
        return;
    }

    float sum = 0;
    int passed = 0, failed = 0;
    int topper = 0;

    for (int i = 0; i < n; i++)
    {
        sum += s[i].percentage;

        if (s[i].pass)
            passed++;
        else
            failed++;

        if (s[i].percentage > s[topper].percentage)
            topper = i;
    }

    printf("\n========== CLASS ANALYSIS ==========\n");
    printf("Total students : %d\n", n);
    printf("Class average  : %.2f%%\n", sum / n);
    printf("Passed         : %d\n", passed);
    printf("Failed         : %d\n", failed);

    printf("\nClass Topper:\n");
    printf("Name       : %s\n", s[topper].name);
    printf("Roll Number: %d\n", s[topper].roll);
    printf("Percentage : %.2f%%\n", s[topper].percentage);
    printf("Grade      : %c\n", s[topper].grade);

    printf("=================================\n");
}

int main()
{
    struct Student students[MAX_STUDENTS];
    int n = 0;
    int choice;

    do
    {
        printf("\n\n===== STUDENT GRADE ANALYZER =====\n");
        printf("1. Add Students\n");
        printf("2. Display All Students\n");
        printf("3. Search Student\n");
        printf("4. Class Performance Analysis\n");
        printf("5. Exit\n");

        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                addStudents(students, &n);
                break;

            case 2:
                displayAll(students, n);
                break;

            case 3:
                searchStudent(students, n);
                break;

            case 4:
                classAnalysis(students, n);
                break;

            case 5:
                printf("\nThank you for using Student Grade Analyzer!\n");
                break;

            default:
                printf("\nInvalid choice! Please try again.\n");
        }

    } while (choice != 5);

    return 0;
}
