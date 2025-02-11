#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

User users[MAX_USERS];
int userCount = 0;

void MainMENU() {
    int choice;
    do {
        printf("*** %s ***\n\n", "Bank management system using C");
        printf("%25s\n", "CHOOSE YOUR ROLE");
        printf("%30s\n", "========================");
        printf("%16s\n", "[1] Admin.");
        printf("%15s\n", "[2] User.");
        printf("%27s\n", "[3] Exit the program.");
        printf("%30s\n", "========================");
        printf("%24s", "Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number!\n");
            while (getchar() != '\n'); // Xóa b? nh? d?m
            continue;
        }

        switch (choice) {
            case 1:
                displayUserMenu();
                break;
            case 2:
                printf("User menu is under development.\n");
                break;
            case 3:
                end();
                break;
            default:
                printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 3);
}

void end() {
    printf("\n%10s %5s %10s\n", "=========", "Thank you", "=========");
    printf("%10s %5s %10s\n", "=========", "See you soon", "=========");
    printf("--------------------------------\n");
}

void displayUserMenu() {
    int choice;
    do {
        printf("\n=== User Management ===\n");
        printf("1. Display user list\n");
        printf("2. Add a user\n");
        printf("5. Sort user list\n");
        printf("6. Search for a user\n");
        printf("0. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number!\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                displayUsers();
                break;
            case 2:
                addUser();
                break;
            case 0:
                printf("Exiting User Management...\n");
                break;
            default:
                printf("Invalid choice. Please try again!\n");
        }
    } while (choice != 0);
}

void displayUsers() {
    if (userCount == 0) {
        printf("No users available.\n");
        return;
    }

    printf("\n");
    printf("=========================================================================================\n");
    printf("| %-12s | %-20s | %-25s | %-12s | %-10s |\n", "ID", "Name", "Email", "Phone", "Status");
    printf("=========================================================================================\n");

    for (int i = 0; i < userCount; i++) {
        printf("| %-12s | %-20s | %-25s | %-12s | %-10s |\n",
               users[i].id, users[i].name, users[i].email, users[i].phone, users[i].status);
    }

    printf("-----------------------------------------------------------------------------------------\n");
}

void addUser() {
    if (userCount >= MAX_USERS) {
        printf("Cannot add more users.\n");
        return;
    }

    User newUser;
    printf("Enter ID: ");
    scanf("%s", newUser.id);
    printf("Enter name: ");
    scanf("%s", newUser.name);
    printf("Enter phone number: ");
    scanf("%s", newUser.phone);
    printf("Enter email: ");
    scanf("%s", newUser.email);
    printf("Enter username: ");
    scanf("%s", newUser.username);
    
    strcpy(newUser.password, newUser.phone); // M?t kh?u m?c d?nh là s? di?n tho?i
    strcpy(newUser.status, "open"); // Tr?ng thái m?c d?nh là m?

    users[userCount++] = newUser;
    printf("User added successfully.\n");
}

