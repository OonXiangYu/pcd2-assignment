#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#pragma warning (disable:4996)

#define MAX_STAFF 100

struct Staff {
    char id[7];
    char name[50];
    char password[20];
    char recovery[20];
    char position[20];
    char role[20];
};

void addStaff(struct Staff staffList[], int* numStaff);
void displayStaff(struct Staff staffList[], int numStaff);
void generateReport(struct Staff staffList[], int numStaff);
void editStaff(struct Staff staffList[], int numStaff);
void checkPassword(struct Staff staffList[], int numStaff);
void searchStaff(struct Staff staffList[], int numStaff);



int main() {
    struct Staff staffList[MAX_STAFF];
    int numStaff = 0;
    int choice;

    printf("=== YY Company Staff Information System ===\n");

    while (1) {
        printf("\nMenu:\n");
        printf("1. Add Staff\n");
        printf("2. Display Staff\n");
        printf("3. Generate Report\n");
        printf("4. Edit Staff Information\n");
        printf("5. Check Password Account\n");
        printf("6. Search Staff\n");
        printf("7. Exit\n");
        printf("Enter your choice (1-7): ");

        // Input validation
        while (scanf("%d", &choice) != 1 || choice < 1 || choice > 7) {
            printf("Invalid choice, please enter a number between 1 and 7: ");
            fflush(stdin);
        }

        fflush(stdin);

        switch (choice) {
        case 1:
            addStaff(staffList, &numStaff);
            break;
        case 2:
            displayStaff(staffList, numStaff);
            break;
        case 3:
            generateReport(staffList, numStaff);
            break;
        case 4:
            editStaff(staffList, numStaff);
            break;
        case 5:
            checkPassword(staffList, numStaff);
            break;
        case 6:
            searchStaff(staffList, numStaff);
            break;
        case 7:
            printf("Exiting program.\n");
            exit(0);
            break;
        default:
            printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}




void addStaff(struct Staff staffList[], int* numStaff) {
    struct Staff newStaff;

    FILE* fp = fopen("stafftxt.txt", "a");
    printf("Enter id : ");
    scanf("%s", newStaff.id);

    // Check if ID already exists
    for (int i = 0; i < *numStaff; i++) {
        if (strcmp(staffList[i].id, newStaff.id) == 0) {
            printf("Error: Staff ID already exists.\n");
            return;
        }
    }
    fflush(stdin);

    printf("Enter Staff Name: ");
    scanf(" %[^\n]", newStaff.name);

    if (strcmp(newStaff.name, "xx") == 0) {
        return;
    }
    fflush(stdin);

    printf("Enter Password: ");
    scanf("%s", newStaff.password);
    fflush(stdin);
    

    printf("Enter Recovery Email: ");
    scanf("%s", newStaff.recovery);
    fflush(stdin);
    
    printf("Enter Position: ");
    scanf("%s", newStaff.position);
    fflush(stdin);
    

    printf("Enter Role: ");
    scanf("%s", newStaff.role);
    fflush(stdin);
    
    printf("%-10s %-20s %-20s %-20s %-20s %-20s\n", "ID", "Name", "Position", "Role", "Recovery Email","Password");

    staffList[*numStaff] = newStaff;
    (*numStaff)++;
    
    
    for (int i = 0; i < *numStaff; i++) {
        fprintf(fp, "%s %s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].position, staffList[i].role, staffList[i].recovery, staffList[i].password);
    }
    fclose(fp);
}

void displayStaff(struct Staff staffList[], int numStaff) {
        FILE* fp = fopen("stafftxt.txt", "r");
        printf("=== Staff List ===\n");

        if (fp == NULL) {
            printf("Error: Unable to open file.\n");
            return;
        }

        printf("%-10s %-20s %-20s %-20s %-20s\n", "ID", "Name", "Position", "Role", "Recovery Email");

        char line[100];
        while (fgets(line, sizeof(line), fp) != NULL) {
            char id[7], name[50], password[20], recovery[20], position[20], role[20];
            sscanf(line, "%s %s %s %s %s\n", id, name, position, role, recovery);
            printf("%-10s %-20s %-20s %-20s %-20s\n", id, name, position, role, recovery);
        }

        fclose(fp);
    }

void generateReport(struct Staff staffList[], int numStaff) {
    FILE* fp = fopen("stafftxt.txt", "r");
    printf("==================================== Staff Report ====================================\n");

    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    printf("+------+----------------------+----------------------+----------------------+----------------------+\n");
    printf("| %-4s | %-20s | %-20s | %-20s | %-20s |\n", "ID", "Name", "Position", "Role", "Recovery Email");
    printf("+------+----------------------+----------------------+----------------------+----------------------+\n");

    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char id[7], name[50], password[20], recovery[20], position[20], role[20];
        sscanf(line, "%s %s %s %s %s\n", id, name, position, role, recovery);
        printf("| %-4s | %-20s | %-20s | %-20s | %-20s |\n", id, name, position, role, recovery);
        printf("+------+----------------------+----------------------+----------------------+----------------------+\n");
    }

    fclose(fp);
    return;
}



void editStaff(struct Staff staffList[], int numStaff) {
    char id[7], name[21];
    int index = -1, choice, i = 0;

    printf("=== Edit Staff Information ===\n");

    printf("Enter Staff ID to edit: ");
    scanf("%s", id);

    FILE* fp = fopen("stafftxt.txt", "r");
    FILE* temp_fp = fopen("temp.txt", "w");

    if (fp == NULL || temp_fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    while (fscanf(fp, "%s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].position, staffList[i].role, staffList[i].recovery) != EOF) {
        if (strcmp(staffList[i].id, id) == 0) {
            index = i;
            printf("\nWhat do you want to change?");
            printf("\n1. Name");
            printf("\n2. Password");
            printf("\n3. Recovery Email");
            printf("\n4. Position");
            printf("\n5. Role");
            printf("\n6. Exit");
            printf("\nEnter your choice: ");
            scanf("%d", &choice);
            if (choice == 1) {
                printf("Enter new Staff Name: ");
                scanf(" %[^\n]", name);
                strcpy(staffList[index].name, name);
            }
            else if (choice == 2) {
                printf("Enter new Password (current password is hidden): ");
                scanf("%s", staffList[index].password);
            }
            else if (choice == 3) {
                printf("Enter new Recovery Email (current recovery email is %s): ", staffList[index].recovery);
                scanf("%s", staffList[index].recovery);
            }
            else if (choice == 4) {
                printf("Enter new Position (current position is %s): ", staffList[index].position);
                scanf("%s", staffList[index].position);
            }
            else if (choice == 5) {
                printf("Enter new Role (current role is %s): ", staffList[index].role);
                scanf("%s", staffList[index].role);
            }
            else {
                fclose(fp);
                fclose(temp_fp);
                return;
            }
        }
        fprintf(temp_fp, "%s %s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].password, staffList[i].position, staffList[i].role, staffList[i].recovery);
        i++;
    }

    fclose(fp);
    fclose(temp_fp);

    if (index == -1) {
        remove("temp.txt");
        printf("Error: Staff ID not found.\n");
    }
    else {
        remove("stafftxt.txt");
        rename("temp.txt", "stafftxt.txt");
        printf("Staff information updated successfully!\n");
    }
    return;
}

void checkPassword(struct Staff staffList[], int numStaff) {
    char id[7], recovery[20];

    printf("Enter ID: ");
    scanf("%s", id);
    printf("Enter recovery email: ");
    scanf("%s", recovery);

    FILE* fp = fopen("stafftxt.txt", "r");
    if (fp == NULL) {
        printf("Error: Unable to open file.\n");
        return;
    }

    char line[100];
    while (fgets(line, sizeof(line), fp) != NULL) {
        char file_id[7], name[50], password[20], file_recovery[20], position[20], role[20];
        sscanf(line, "%s %s %s %s %s %s\n", file_id, name, position, role, file_recovery, password);
        if (strcmp(file_id, id) == 0 && strcmp(file_recovery, recovery) == 0) {
            printf("Password: %s\n", password);
            fclose(fp);
            return;
        }
    }

    fclose(fp);
    printf("No staff member found with the given ID and recovery email.\n");
}

void searchStaff(struct Staff staffList[], int numStaff) {
    
        char searchId[7];
        int found = 0;

        printf("Enter staff ID to search: ");
        scanf("%s", searchId);

        FILE* fp = fopen("stafftxt.txt", "r");
        if (fp == NULL) {
            printf("Error: Unable to open file.\n");
            return;
        }

        printf("=== Search Results ===\n");
        printf("%-10s %-20s %-20s %-20s %-20s\n", "ID", "Name", "Position", "Role", "Recovery Email");

        char line[100];
        while (fgets(line, sizeof(line), fp) != NULL) {
            char id[7], name[50], password[20], recovery[20], position[20], role[20];
            sscanf(line, "%s %s %s %s %s\n", id, name, position, role, recovery);
            if (strcmp(id, searchId) == 0) {
                printf("%-10s %-20s %-20s %-20s %-20s\n", id, name, position, role, recovery);
                found = 1;
                break;
            }
        }

        if (!found) {
            printf("Staff ID '%s' not found.\n", searchId);
        }

        fclose(fp);
   
}