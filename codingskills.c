#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define STUD_FILE "students.txt"
#define CRE_FILE  "credentials.txt"
char currentUser[50];
char currentRole[20];
int login() {
    char u[50], p[50], r[20];
    char inUser[50], inPass[50];
    printf("USERNAME: ");
    if (scanf("%49s", inUser) != 1) return 0;
    printf("PASSWORD: ");
    if (scanf("%49s", inPass) != 1) return 0;
    FILE *fp = fopen(CRE_FILE, "r");
    if (!fp) {
        printf("Credential file missing!\n");
        return 0;
    }
    while (fscanf(fp, "%49s %49s %19s", u, p, r) == 3) {
        if (strcmp(inUser, u) == 0 && strcmp(inPass, p) == 0) {
            strcpy(currentUser, u);
            strcpy(currentRole, r);
            /* Remove any trailing whitespace/newline from role */
            int len = strlen(currentRole);
            while (len > 0 && (currentRole[len-1] == '\n' || currentRole[len-1] == '\r' || currentRole[len-1] == ' ')) {
                currentRole[len-1] = '\0';
                len--;
            }
            fclose(fp);
            return 1;
        }
    }
    fclose(fp);
    return 0;
}
void addStudent() {
    int roll;
    char name[50];
    float mark;
    printf("Roll: ");
    if (scanf("%d", &roll) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }
    printf("Name: ");
    getchar(); /* consume newline left by scanf */
    if (!fgets(name, sizeof(name), stdin)) name[0] = '\0';
    name[strcspn(name, "\n")] = '\0';
    printf("Mark: ");
    if (scanf("%f", &mark) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }
    if (mark < 0.0f || mark > 100.0f) {
        printf("Invalid mark. Must be between 0 and 100. Student not added.\n");
        return;
    }
    FILE *fp = fopen(STUD_FILE, "a");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    fprintf(fp, "%d %s %.2f\n", roll, name, mark);
    fclose(fp);
    printf("Student added!\n");
}
void displayStudents() {
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    printf("Roll\tName\tMark\n");
    printf("----\t----\t----\n");
    while (fscanf(fp, "%d %49s %f", &roll, name, &mark) == 3) {
        printf("%d\t%s\t%.2f\n", roll, name, mark);
    }
    fclose(fp);
}
void str_to_lower(char *s) {
    while (*s) { *s = (char) tolower((unsigned char)*s); s++; }
}

void trim_whitespace(char *s) {
    int len = strlen(s);
    while (len > 0 && (s[len-1] == '\n' || s[len-1] == '\r' || s[len-1] == ' ')) {
        s[len-1] = '\0';
        len--;
    }
}
void searchStudentByName() {
    char q[50];
    printf("Enter name (or part of name) to search: ");
    getchar(); 
    if (!fgets(q, sizeof(q), stdin)) q[0] = '\0';
    q[strcspn(q, "\n")] = '\0';
    if (q[0] == '\0') {
        printf("Empty query. Aborting search.\n");
        return;
    }
    char qlow[50];
    strncpy(qlow, q, sizeof(qlow));
    qlow[sizeof(qlow)-1] = '\0';
    str_to_lower(qlow);

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    int found = 0;
    while (fscanf(fp, "%d %49s %f", &roll, name, &mark) == 3) {
        char name_low[50];
        strncpy(name_low, name, sizeof(name_low));
        name_low[sizeof(name_low)-1] = '\0';
        str_to_lower(name_low);
        if (strstr(name_low, qlow) != NULL) {
            if (!found) {
                printf("Matches:\n");
                printf("Roll\tName\tMark\n");
                printf("----\t----\t----\n");
            }
            printf("%d\t%s\t%.2f\n", roll, name, mark);
            found = 1;
        }
    }
    fclose(fp);
    if (!found) printf("No students matched '%s'\n", q);
}
void searchStudentByMarkRange() {
    float low, high;
    printf("Enter lower mark: ");
    if (scanf("%f", &low) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        printf("Invalid input.\n");
        return;
    }
    printf("Enter upper mark: ");
    if (scanf("%f", &high) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        printf("Invalid input.\n");
        return;
    }
    if (low < 0.0f || high > 100.0f || low > high) {
        printf("Invalid range! Must be 0–100 and low = high.\n");
        return;
    }

    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }

    int roll;
    char name[50];
    float mark;
    int found = 0;

    printf("Results for marks between %.2f and %.2f:\n", low, high);
    printf("Roll\tName\tMark\n");
    printf("----\t----\t----\n");

    while (fscanf(fp, "%d %49s %f", &roll, name, &mark) == 3) {
        if (mark >= low && mark <= high) {
            printf("%d\t%s\t%.2f\n", roll, name, mark);
            found = 1;
        }
    }

    fclose(fp);

    if (!found) {
        printf("No students found in this mark range.\n");
    }
}

void searchStudent() {
    int choice = 1;
    printf("Search by:\n");
    printf("1. Roll\n");
    printf("2. Name\n");
    printf("3. Mark Range\n");
    printf("Enter choice: ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }

    if (choice == 1) {
        int find, roll;
        char name[50];
        float mark;
        printf("Enter roll to search: ");
        if (scanf("%d", &find) != 1) {
            while (getchar() != '\n' && getchar() != EOF);
            return;
        }
        FILE *fp = fopen(STUD_FILE, "r");
        if (!fp) {
            printf("No student file!\n");
            return;
        }
        while (fscanf(fp, "%d %49s %f", &roll, name, &mark) == 3) {
            if (roll == find) {
                printf("Found: %d %s %.2f\n", roll, name, mark);
                fclose(fp);
                return;
            }
        }
        fclose(fp);
        printf("Student not found!\n");
    } else if (choice == 2) {
        searchStudentByName();
    } else if (choice == 3) {
        searchStudentByMarkRange();
    } else {
        printf("Invalid choice.\n");
    }
}

void deleteStudent() {
    int delRoll;
    printf("Enter roll to delete: ");
    if (scanf("%d", &delRoll) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(fp);
        printf("Unable to create temp file!\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    int found = 0;
    while (fscanf(fp, "%d %49s %f", &roll, name, &mark) == 3) {
        if (roll != delRoll) {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        } else {
            found = 1;
        }
    }
    fclose(fp);
    fclose(temp);
    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);
    if (found) printf("Student deleted!\n");
    else printf("Roll not found!\n");
}

void updateStudent() {
    int updateRoll;
    printf("Enter roll to update: ");
    if (scanf("%d", &updateRoll) != 1) {
        while (getchar() != '\n' && getchar() != EOF);
        return;
    }
    FILE *fp = fopen(STUD_FILE, "r");
    if (!fp) {
        printf("No student file!\n");
        return;
    }
    FILE *temp = fopen("temp.txt", "w");
    if (!temp) {
        fclose(fp);
        printf("Unable to create temp file!\n");
        return;
    }
    int roll;
    char name[50];
    float mark;
    int found = 0;
    while (fscanf(fp, "%d %49s %f", &roll, name, &mark) == 3) {
        if (roll == updateRoll) {
            found = 1;
            char newName[50];
            float newMark;
            printf("New Name: ");
            getchar();
            if (!fgets(newName, sizeof(newName), stdin)) newName[0] = '\0';
            newName[strcspn(newName, "\n")] = '\0';
            printf("New Mark: ");
            if (scanf("%f", &newMark) != 1) {
                while (getchar() != '\n' && getchar() != EOF);
                newMark = mark;
            }
            if (newMark < 0.0f || newMark > 100.0f) {
                printf("Invalid mark. Must be between 0 and 100. Keeping previous mark (%.2f).\n", mark);
                newMark = mark;
            }
            fprintf(temp, "%d %s %.2f\n", roll, newName, newMark);
        } else {
            fprintf(temp, "%d %s %.2f\n", roll, name, mark);
        }
    }
    fclose(fp);
    fclose(temp);
    remove(STUD_FILE);
    rename("temp.txt", STUD_FILE);
    if (found) printf("Student updated!\n");
    else printf("Roll not found!\n");
}
void adminMenu() {
    int c;
    while (1) {
        printf("\nADMIN MENU\n");
        printf("1.Add\n2.Display\n3.Search\n4.Update\n5.Delete\n6.Logout\n");
        if (scanf("%d",&c) != 1) {
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }
        if(c==1) addStudent();
        else if(c==2) displayStudents();
        else if(c==3) searchStudent();
        else if(c==4) updateStudent();
        else if(c==5) deleteStudent();
        else return;
    }
}
void staffMenu() {
    int c;
    while (1) {
        printf("\nSTAFF MENU\n");
        printf("1.Add\n2.Display\n3.Search\n4.Update\n5.Logout\n");
        if (scanf("%d",&c) != 1) {
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }
        if(c==1) addStudent();
        else if(c==2) displayStudents();
        else if(c==3) searchStudent();
        else if(c==4) updateStudent();
        else return;
    }
}
void guestMenu() {
    int c;
    while (1) {
        printf("\nGUEST MENU\n");
        printf("1.Display\n2.Search\n3.Logout\n");
        if (scanf("%d",&c) != 1) {
            while (getchar() != '\n' && getchar() != EOF);
            continue;
        }
        if(c==1) displayStudents();
        else if(c==2) searchStudent();
        else return;
    }
}
int main() {
    if (!login()) {
        printf("Invalid login!\n");
        return 0;
    }
    
    /* Clean up role string */
    trim_whitespace(currentRole);
    
    printf("Logged in as: %s\n", currentRole);
    
    /* Convert role to lowercase for comparison */
    char roleCheck[20];
    strcpy(roleCheck, currentRole);
    str_to_lower(roleCheck);
    
    if (strcmp(roleCheck, "admin") == 0) {
        adminMenu();
    } else if (strcmp(roleCheck, "staff") == 0) {
        staffMenu();
    } else {
        guestMenu();
    }
    
    return 0;
}