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
        printf("Enter your choice (1-6): ");
        scanf("%d", &choice);
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


//void updateStaff(struct Staff staffList[], int numStaff) {
//    char id[7], confirmation[5];
//    int found = 0;
//
//    printf("Enter staff ID: ");
//    scanf("%s", id);
//    fflush(stdin);
//
//    for (int i = 0; i < numStaff; i++) {
//        if (strcmp(staffList[i].id, id) == 0) {
//            found = 1;
//            printf("Are you sure you want to update staff %s? (yes/no)\n", id);
//            scanf("%s", confirmation);
//            fflush(stdin);
//
//            if (strcmp(confirmation, "yes") == 0) {
//                strcpy(staffList[i].name, "XXX");
//                strcpy(staffList[i].position, "XXX");
//                strcpy(staffList[i].role, "XXX");
//                strcpy(staffList[i].recovery, "XXX");
//                printf("Staff %s has been updated.\n", id);
//
//                // Update staff information in the file
//                FILE* fp = fopen("stafftxt.txt", "w");
//                FILE* temp_fp = fopen("temp.txt", "w");
//
//                if (fp == NULL || temp_fp == NULL) {
//                    printf("Error: Unable to open file.\n");
//                    return;
//                }
//
//                for (int j = 0; j < numStaff; j++) {
//                    fprintf(fp, "%s %s %s %s %s %s\n", staffList[j].id, staffList[j].name, staffList[j].password, staffList[j].position, staffList[j].role, staffList[j].recovery);
//                    fprintf(temp_fp, "%s %s %s %s %s %s\n", staffList[j].id, staffList[j].name, staffList[j].password, staffList[j].position, staffList[j].role, staffList[j].recovery);
//                }
//
//                fclose(fp);
//                fclose(temp_fp);
//            }
//            else {
//                printf("Update cancelled.\n");
//            }
//
//            break;
//        }
//    }
//
//    if (!found) {
//        printf("Error: Staff not found.\n");
//    }
//}



//void renewPassword(struct Staff staffList[], int* numStaff) {
//    char id[7], recovery[20], password[20];
//    int found = 0;
//
//    printf("Enter staff ID: ");
//    scanf("%s", id);
//    fflush(stdin);
//
//    printf("Enter staff recovery email: ");
//    scanf("%s", recovery);
//    fflush(stdin);
//
//    for (int i = 0; i < *numStaff; i++) {
//        if (strcmp(staffList[i].id, id) == 0 && strcmp(staffList[i].recovery, recovery) == 0) {
//            found = 1;
//            printf("Enter new password: ");
//            scanf("%s", password);
//            strcpy(staffList[i].password, password);
//            printf("Password has been renewed.\n");
//
//            // Update staff information in the file
//            FILE* fp = fopen("stafftxt.txt", "a+");
//            for (int i = 0; i < *numStaff; i++) {
//                fprintf(fp, "%s %s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].password, staffList[i].position, staffList[i].role, staffList[i].recovery);
//            }
//            fclose(fp);
//
//            break;
//        }
//    }
//
//    if (!found) {
//        printf("Error: Staff not found or recovery email incorrect.\n");
//    }
//}


//void renewPassword(struct Staff staffList[], int numStaff) {
//    char id[7], newPassword[21];
//    int index = -1, i = 0;
//
//    printf("=== Renew Staff Password ===\n");
//
//    printf("Enter Staff ID to renew password: ");
//    scanf("%s", id);
//
//    FILE* fp = fopen("stafftxt.txt", "r");
//    FILE* temp_fp = fopen("temp.txt", "w");
//
//    if (fp == NULL || temp_fp == NULL) {
//        printf("Error: Unable to open file.\n");
//        return;
//    }
//
//    while (fscanf(fp, "%s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].position, staffList[i].role, staffList[i].recovery) != EOF) {
//        if (strcmp(staffList[i].id, id) == 0) {
//            index = i;
//            printf("Enter new Password: ");
//            scanf("%s", newPassword);
//            strcpy(staffList[index].password, newPassword);
//        }
//        fprintf(temp_fp, "%s %s %s %s %s %s\n", staffList[i].id, staffList[i].name, staffList[i].password, staffList[i].position, staffList[i].role, staffList[i].recovery);
//        i++;
//    }
//
//    fclose(fp);
//    fclose(temp_fp);
//
//    if (index == -1) {
//        remove("temp.txt");
//        printf("Error: Staff ID not found.\n");
//    }
//    else {
//        remove("stafftxt.txt");
//        rename("temp.txt", "stafftxt.txt");
//        printf("Staff password updated successfully!\n");
//    }
//}


//void deleteStaff(struct Staff staffList[], int* numStaff) {
//    char id[7];
//    int index = -1;
//    char line[1024];
//
//
//    printf("=== Delete Staff Account ===\n");
//
//    printf("Enter Staff ID to delete: ");
//    scanf("%s", id);
//
//    FILE* fp = fopen("stafftxt.txt", "r");
//    FILE* temp_fp = fopen("themp.txt", "w");
//    if (fp == NULL || temp_fp == NULL) {
//        printf("Error: Unable to open file.\n");
//        return;
//    }
//
//    // Find the index of the staff with the given ID
//    for (int i = 0; i < *numStaff; i++) {
//        if (strcmp(staffList[i].id, id) == 0) {
//            index = i;
//            break;
//        }
//    }
//
//    if (index == -1) {
//        printf("Error: Staff ID not found.\n");
//        return;
//    }
//
//    // Shift all staff after the index back one position
//    for (int i = index; i < *numStaff - 1; i++) {
//        staffList[i] = staffList[i + 1];
//    }
//
//    (*numStaff)--;
//    printf("Staff account deleted successfully!\n");
//
//    // Update the contents of the text file with the new staffList array
//    fp = fopen("stafftxt.txt", "w");
//    if (fp == NULL) {
//        printf("Error: Unable to open file.\n");
//        return;
//    }
//    for (int i = 0; i < *numStaff; i++) {
//        fprintf(fp, "%s,%s,%s,%s,%s\n", staffList[i].id, staffList[i].name, staffList[i].password, staffList[i].recovery, staffList[i].position, staffList[i].role);
//    }
//    fclose(fp);
//
//    // Rewrite the temporary file to the original file
//    fp = fopen("stafftxt.txt", "w");
//    temp_fp = fopen("themp.txt", "r");
//    while (fgets(line, 1024, temp_fp)) {
//        fprintf(fp, "%s", line);
//    }
//    fclose(fp);
//    fclose(temp_fp);
//
//    remove("themp.txt");
//}

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