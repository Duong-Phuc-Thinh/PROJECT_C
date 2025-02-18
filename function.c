#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "datatype.h"
#include <ctype.h>  // Them thu vien nay de su dung isdigit

struct User users[100];
int userCount = 0;



int isValidUserId(const char *userId) {
    for (int i = 0; i < strlen(userId); i++) {
        if (isalpha(userId[i])) {  // Neu co ky tu la chu, tra ve false
            return 0;
        }
    }
    return 1;  // Neu tat ca dau khong phai chu, tra ve true
}

// Ham kiem tra ten co hop le khong (khong chua so)
int isValidName(const char *name) {
    for (int i = 0; i < strlen(name); i++) {
        if (isdigit(name[i])) {
            return 0;  // Neu co ky tu so, tra ve false
        }
    }
    return 1;  // Neu tat ca cac ky tu deu la chu, tra ve true
}

// Ham kiem tra so dien thoai có hop le khong (chi chua so va khong dai qua 12 ky tu)
int isValidPhone(const char *phone) {
    if (strlen(phone) > 12) return 0;  // Kiem tra chieu dai
    for (int i = 0; i < strlen(phone); i++) {
        if (!isdigit(phone[i])) {
            return 0;  // Neu co ky tu khong phai so, tra ve false
        }
    }
    return 1;  // Neu tat ca cac ky tu deu la so, tra ve true
}
// Ðinh nghia mang users và bien userCount

void cleanString(char *str) {
    for (int i = 0; str[i]; i++) {
        if (str[i] == '|') {
            str[i] = '_';  // Thay the ky tu '|' bang '_'
        }
    }
}

void saveUserData() {
    FILE *file = fopen("C:/prjcopy/user.txt", "w");  // Mo file de ghi
    if (!file) {
        printf("Error: Could not open file for writing.\n");
        return;
    }

    // Duyet qua tung nguoi dung trong mang users
    for (int i = 0; i < userCount; i++) {
        // Ghi thông tin nguoi dung vao file
        fprintf(file, "USER|%s|%s|%02d-%02d-%04d|%d|%s|%s|%d|%s|%.2f|%s\n",
                users[i].userId, users[i].name,
                users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year,
                users[i].gender, users[i].phone, users[i].email,
                users[i].status, users[i].password,
                users[i].balance, users[i].username);

        // Duyet qua lich su giao dich caa nguoi dung
        for (int j = 0; j < 100; j++) {
            if (users[i].transactionHistory[j].amount > 0) {
                // Ghi thong tin giao dich vao file
                fprintf(file, "TRANSACTION|%s|%s|%.2f|%s|%s|%02d-%02d-%04d\n",
                        users[i].transactionHistory[j].transferId,
                        users[i].transactionHistory[j].receivingId,
                        users[i].transactionHistory[j].amount,
                        users[i].transactionHistory[j].type,
                        users[i].transactionHistory[j].message,
                        users[i].transactionHistory[j].transactionDate.day,
                        users[i].transactionHistory[j].transactionDate.month,
                        users[i].transactionHistory[j].transactionDate.year);
            }
        }
    }
    fclose(file);  // Ðong file
    printf("User data saved successfully!\n");
}
void loadUserData() {
    FILE *file = fopen("C:/prjcopy/user.txt", "r");
    if (!file) {
        printf("Error: Could not open file for reading.\n");
        return;
    }

    char line[256];
    userCount = 0;
    struct User tempUser;
    int transactionIndex = 0;

    while (fgets(line, sizeof(line), file)) {  // Ðam bao co dau ngoac don dung
        char type[20];
        sscanf(line, "%[^|]", type);

        if (strcmp(type, "USER") == 0) {
            sscanf(line, "USER|%[^|]|%[^|]|%d-%d-%d|%d|%[^|]|%[^|]|%d|%[^|]|%f|%[^|]",
                   tempUser.userId, tempUser.name,
                   &tempUser.dateOfBirth.day, &tempUser.dateOfBirth.month, &tempUser.dateOfBirth.year,
                   &tempUser.gender, tempUser.phone, tempUser.email,
                   &tempUser.status, tempUser.password,
                   &tempUser.balance, tempUser.username);

            // Kiem tra tinh hop le caa du lieu
            if (!isValidUserId(tempUser.userId) || !isValidName(tempUser.name) || !isValidPhone(tempUser.phone)) {
                printf("Invalid data found in file for user ID: %s. Skipping this user.\n", tempUser.userId);
                continue;
            }

            users[userCount] = tempUser;
            transactionIndex = 0;
            userCount++;
        } else if (strcmp(type, "TRANSACTION") == 0) {
            struct Transaction transaction;
            sscanf(line, "TRANSACTION|%[^|]|%[^|]|%lf|%[^|]|%[^|]|%d-%d-%d",
                   transaction.transferId, transaction.receivingId,
                   &transaction.amount, transaction.type, transaction.message,
                   &transaction.transactionDate.day, &transaction.transactionDate.month, &transaction.transactionDate.year);

            if (transactionIndex < 100) {
                users[userCount - 1].transactionHistory[transactionIndex] = transaction;
                transactionIndex++;
            }
        }
    }

    fclose(file);
    printf("User data loaded successfully! Found %d users.\n", userCount);
}

void displayUserList() {
    printf("\n*** User List ***\n");
    printf("===============================================================================================================\n");
    printf("| %-10s | %-20s | %-25s | %-12s | %-14s | %-6s |\n", "ID", "Name", "Email", "Phone", "Date of Birth", "Status");
    printf("---------------------------------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-10s | %-20s | %-25s | %-12s | %02d-%02d-%04d | %-10s |\n",
               users[i].userId,
               users[i].name,
               users[i].email,
               users[i].phone,
               users[i].dateOfBirth.day, users[i].dateOfBirth.month, users[i].dateOfBirth.year,
               users[i].status ? "Locked" : "Open");
    }
    printf("===============================================================================================================\n");

    int choice;
    printf("\n[1] Return to Admin Menu\n");
    printf("[0] Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 0) {
        saveUserData();
        exit(0);
    } else {
        system("cls");
    }
}

void displayUserDetails(char *userId) {
    int found = 0;

    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            printf("\n================ User Details ================\n");
            printf("User ID      : %s\n", users[i].userId);
            printf("Name         : %s\n", users[i].name);
            printf("Email        : %s\n", users[i].email);
            printf("Phone        : %s\n", users[i].phone);
            printf("Status       : %s\n", users[i].status ? "Locked" : "Open");
            printf("Date of Birth: %02d-%02d-%04d\n",
                   users[i].dateOfBirth.day,
                   users[i].dateOfBirth.month,
                   users[i].dateOfBirth.year);

            printf("\n--- Account Information ---\n");
            printf("Balance      : %.2f\n", users[i].balance);
            printf("Username     : %s\n", users[i].username);

            printf("\n--- Transaction History ---\n");
            printf("| %-10s | %-10s | %-8s | %-15s | %-10s |\n",
                   "Sender", "Receiver", "Amount", "Type", "Date");
            printf("---------------------------------------------------------\n");

            for (int j = 0; j < 100; j++) {
                if (users[i].transactionHistory[j].amount > 0) {
                    printf("| %-10s | %-10s | %-8.2f | %-15s | %02d-%02d-%04d |\n",
                           users[i].transactionHistory[j].transferId,
                           users[i].transactionHistory[j].receivingId,
                           users[i].transactionHistory[j].amount,
                           users[i].transactionHistory[j].type,
                           users[i].transactionHistory[j].transactionDate.day,
                           users[i].transactionHistory[j].transactionDate.month,
                           users[i].transactionHistory[j].transactionDate.year);
                }
            }
            printf("---------------------------------------------------------\n");

            found = 1;
            break;
        }
    }

    if (!found) {
        printf("No user found with ID: %s\n", userId);
    }
}


bool isValidLength(const char *input, int maxLength) {
    return strlen(input) > 0 && strlen(input) <= maxLength;
}

void searchUserByName(char *name) {
    printf("Searching for '%s'...\n", name);
    int found = 0;
    printf("========================================================================================\n");
    printf("| %-10s | %-20s | %-25s | %-12s | %-6s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("----------------------------------------------------------------------------------------\n");

    for (int i = 0; i < userCount; i++) {
        if (strstr(users[i].name, name) != NULL) {
            printf("| %-10s | %-20s | %-25s | %-12s | %-6s |\n",
                   users[i].userId,
                   users[i].name,
                   users[i].email,
                   users[i].phone,
                   users[i].status ? "Locked" : "Open");
            found = 1;
        }
    }
    if (!found) {
        printf("No users found matching '%s'.\n", name);
    }
    printf("========================================================================================\n");
}

bool isDuplicateUser(struct User user) {
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, user.userId) == 0 || 
            strcmp(users[i].phone, user.phone) == 0 || 
            strcmp(users[i].email, user.email) == 0 || 
            strcmp(users[i].name, user.name) == 0) {
            return true;
        }
    }
    return false;
}

void addUser() {
    struct User newUser;
    int valid = 0;

    while (!valid) {
        printf("Enter Name: ");
        getchar();
        fgets(newUser.name, sizeof(newUser.name), stdin);
        newUser.name[strcspn(newUser.name, "\n")] = 0;

        if (strlen(newUser.name) == 0 || !isValidName(newUser.name)) {
            printf("Name cannot be empty or contain numbers!\n");
            continue;
        }

        printf("Enter User ID: ");
        fgets(newUser.userId, sizeof(newUser.userId), stdin);
        newUser.userId[strcspn(newUser.userId, "\n")] = 0;

        if (strlen(newUser.userId) == 0 || !isValidUserId(newUser.userId)) {
            printf("User ID cannot be empty or contain letters!\n");
            continue;
        }

        printf("Enter Phone: ");
        fgets(newUser.phone, sizeof(newUser.phone), stdin);
        newUser.phone[strcspn(newUser.phone, "\n")] = 0;

        if (strlen(newUser.phone) == 0 || !isValidPhone(newUser.phone)) {
            printf("Phone number must be a valid number and less than or equal to 12 digits!\n");
            continue;
        }

        printf("Enter Email: ");
        fgets(newUser.email, sizeof(newUser.email), stdin);
        newUser.email[strcspn(newUser.email, "\n")] = 0;

        if (strlen(newUser.email) == 0) {
            printf("Email cannot be empty!\n");
            continue;
        }

        printf("Enter Date of Birth (DD MM YYYY): ");
        scanf("%d %d %d", &newUser.dateOfBirth.day, &newUser.dateOfBirth.month, &newUser.dateOfBirth.year);

        if (newUser.dateOfBirth.year < 1900 || newUser.dateOfBirth.year > 2025 ||
            newUser.dateOfBirth.month < 1 || newUser.dateOfBirth.month > 12 ||
            newUser.dateOfBirth.day < 1 || newUser.dateOfBirth.day > 31) {
            printf("Invalid date of birth!\n");
            continue;
        }

        valid = 1;
    }

    newUser.status = 0;
    strcpy(newUser.password, newUser.phone);

    if (isDuplicateUser(newUser)) {
        printf("User ID, phone number, or email is already taken!\n");
        return;
    }

    users[userCount++] = newUser;
    saveUserData();
    printf("User added successfully!\n");
}


void toggleUserStatus() {
    char userId[10];
    printf("\n*** Lock (Unlock) a User ***\n");
    printf("Enter User ID: ");
    scanf("%s", userId);

    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].userId, userId) == 0) {
            found = 1;
            printf("User found: %s\n", userId);
            printf("Current Status: %s. Do you want to change the status? (y/n): ", users[i].status ? "Locked" : "Open");

            char confirm;
            scanf(" %c", &confirm);  
            if (confirm == 'y' || confirm == 'Y') {
                users[i].status = !users[i].status;
                saveUserData();
                printf("User status changed successfully!\n");
            } else {
                printf("Status change canceled.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("No user found with ID: %s\n", userId);
    }

    int choice;
    printf("\n[1] Return to Admin Menu\n");
    printf("[0] Exit\n");
    printf("Enter choice: ");
    scanf("%d", &choice);
    
    if (choice == 0) {
        saveUserData();
        exit(0); 
    } else {
        system("cls"); 
    }
}

void sortUserList() {
    int choice;
    printf("\n*** Sort User List ***\n");
    printf("============================\n");
    printf("[1] Sort by ID Ascending\n");
    printf("[2] Sort by ID Descending\n");
    printf("============================\n");
    printf("Enter your choice: ");
    scanf("%d", &choice);

    if (choice == 1) {
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].userId, users[j].userId) > 0) {
                    struct User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("User list sorted by ID in ascending order.\n");
    } else if (choice == 2) {
        for (int i = 0; i < userCount - 1; i++) {
            for (int j = i + 1; j < userCount; j++) {
                if (strcmp(users[i].userId, users[j].userId) < 0) {
                    struct User temp = users[i];
                    users[i] = users[j];
                    users[j] = temp;
                }
            }
        }
        printf("User list sorted by ID in descending order.\n");
    } else {
        printf("Invalid choice.\n");
        return;
    }

    displayUserList();
}
