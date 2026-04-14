#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Student {
    int roll;
    char name[50];
    float marks;
};

// Function Prototypes
void addRecord();
void displayRecords();
void searchRecord();
void updateRecord();
void deleteRecord();

int main() {
    int choice;

    while (1) {
        printf("\n--- STUDENT MANAGEMENT SYSTEM ---");
        printf("\n1. Add Student");
        printf("\n2. Display All Students");
        printf("\n3. Search Student");
        printf("\n4. Update Student");
        printf("\n5. Delete Student");
        printf("\n6. Exit");
        printf("\nSelect an option: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: addRecord(); break;
            case 2: displayRecords(); break;
            case 3: searchRecord(); break;
            case 4: updateRecord(); break;
            case 5: deleteRecord(); break;
            case 6: exit(0);
            default: printf("\nInvalid choice! Try again.");
        }
    }
    return 0;
}

void addRecord() {
    FILE *fp = fopen("students.dat", "ab"); // Append binary mode
    struct Student s;

    if (fp == NULL) {
        printf("Error opening file!");
        return;
    }

    printf("\nEnter Roll No: ");
    scanf("%d", &s.roll);
    printf("Enter Name: ");
    scanf(" %[^\n]", s.name); // Reads string with spaces
    printf("Enter Marks: ");
    scanf("%f", &s.marks);

    fwrite(&s, sizeof(struct Student), 1, fp);
    fclose(fp);
    printf("\nRecord added successfully!");
}

void displayRecords() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;

    if (fp == NULL) {
        printf("\nNo records found.");
        return;
    }

    printf("\n%-10s %-20s %-10s", "Roll No", "Name", "Marks");
    printf("\n-------------------------------------------");
    while (fread(&s, sizeof(struct Student), 1, fp)) {
        printf("\n%-10d %-20s %-10.2f", s.roll, s.name, s.marks);
    }
    fclose(fp);
}

void searchRecord() {
    FILE *fp = fopen("students.dat", "rb");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL) return;

    printf("\nEnter Roll No to search: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            printf("\nRecord Found: %d, %s, %.2f", s.roll, s.name, s.marks);
            found = 1;
            break;
        }
    }
    if (!found) printf("\nRecord not found.");
    fclose(fp);
}

void updateRecord() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *ft = fopen("temp.dat", "wb");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL || ft == NULL) return;

    printf("\nEnter Roll No to update: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
            printf("Enter New Name: ");
            scanf(" %[^\n]", s.name);
            printf("Enter New Marks: ");
            scanf("%f", &s.marks);
        }
        fwrite(&s, sizeof(struct Student), 1, ft);
    }

    fclose(fp);
    fclose(ft);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) printf("\nRecord updated successfully!");
    else printf("\nRecord not found.");
}

void deleteRecord() {
    FILE *fp = fopen("students.dat", "rb");
    FILE *ft = fopen("temp.dat", "wb");
    struct Student s;
    int roll, found = 0;

    if (fp == NULL || ft == NULL) return;

    printf("\nEnter Roll No to delete: ");
    scanf("%d", &roll);

    while (fread(&s, sizeof(struct Student), 1, fp)) {
        if (s.roll == roll) {
            found = 1;
        } else {
            fwrite(&s, sizeof(struct Student), 1, ft);
        }
    }

    fclose(fp);
    fclose(ft);

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found) printf("\nRecord deleted.");
    else printf("\nRecord not found.");
}
