#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void start(){
	loadUserData();  // Load d? li?u ngu?i dùng t? file

    int role, choice;
    while (1) {
        // Màn hình login
        printf("\n*** BANK MANAGEMENT SYSTEM ***\n");
        printf("============================\n");
        printf("[1] Admin\n");
        printf("[2] User\n");
        printf("[0] Exit\n");
        printf("============================\n");
        printf("Enter Your Choice: ");
        scanf("%d", &role);

        // Ki?m tra quy?n truy c?p
        if (role == 1) {
            char email[50], password[20];
            printf("\nEmail: ");
            scanf("%s", email);  // Ð? tránh l?i kho?ng tr?ng, có th? thay b?ng fgets
            printf("Password: ");
            scanf("%s", password);  // Cung có th? thay b?ng fgets

            // Ki?m tra thông tin dang nh?p c?a Admin
            if (strcmp(email, "thinh@gmail.com") != 0 || strcmp(password, "thinhdaden") != 0) {
                printf("Login failed! Please try again.\n");
                continue;  // Quay l?i vòng l?p login
            }
            system("cls");

            // Menu Admin
            do {
                printf("\n*** ADMIN MENU ***\n");
                printf("============================\n");
                printf("[1] Add A New User\n");
                printf("[2] Show All Users\n");
                printf("[3] Lock (Unlock) A User\n");
                printf("[4] Search User By Name\n");
                printf("[5] View User Details By ID\n");
                printf("[6] Sort User List\n");  
                printf("[7] Exit\n");
                printf("============================\n");
                printf("Enter Your Choice: ");
                
                // X? lý nh?p li?u và ki?m tra
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n');  // X? lý ký t? không h?p l? trong b? d?m
                    printf("Invalid input! Please enter a valid number.\n");
                    continue;  // Quay l?i vòng l?p menu
                }

                switch (choice) {
                    case 1:
                        system("cls");
                        addUser();
                        saveUserData(); // Thêm ngu?i dùng
                        break;
                    case 2:
                        system("cls");
                        displayUserList();  // Hi?n th? danh sách ngu?i dùng
                        break;
                    case 3:
                        system("cls");
                        toggleUserStatus();  // Khóa/M? khóa ngu?i dùng
                        break;
                    case 4: {
                        char searchName[50];
                        printf("Enter name to search: ");
                        scanf("%s", searchName);
                        system("cls");
                        searchUserByName(searchName);  // Tìm ki?m ngu?i dùng theo tên
                        break;
                    }
                    case 5: {
                        char userId[10];
                        printf("Enter User ID: ");
                        scanf("%s", userId);
                        system("cls");
                        displayUserDetails(userId);  // Hi?n th? chi ti?t ngu?i dùng theo ID
                        break;
                    }
                    case 6:
                        system("cls");
                        sortUserList();  // S?p x?p danh sách ngu?i dùng theo ID
                        break;
                    case 7:
                        system("cls");
                        saveUserData();  // Luu d? li?u ngu?i dùng
                        printf("Exiting Admin Menu...\n");
                        return;  // Thoát chuong trình
                    default:
                        printf("Invalid choice! Please try again.\n");
                }

                // Quay l?i menu chính ho?c thoát chuong trình
                printf("\n[1] Return to Admin Menu\n");
                printf("[0] Exit\n");
                int exitChoice;
                printf("Enter choice: ");
                if (scanf("%d", &exitChoice) != 1) {
                    while (getchar() != '\n');
                    printf("Invalid input! Please enter a valid number.\n");
                    continue;
                }

                if (exitChoice == 0) {
                    saveUserData();
                    return ;  // Exit the program
                } else {
                    system("cls");  // Clear màn hình và quay l?i menu Admin
                }

            } while (choice != 7); // L?p l?i menu cho d?n khi ch?n thoát
        }
        
        // Ph?n cho User (N?u có yêu c?u sau)
        else if (role == 2) {  // User login
    char email[50], phone[12];
    printf("\nEnter Email: ");
    scanf("%s", email);  // To avoid whitespace issues, use fgets or scanf
    printf("Enter Pass: ");
    scanf("%s", phone);  // Use phone as the password

    // Check if the user exists and if the email and phone number match
    int found = 0;
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].email, email) == 0 && strcmp(users[i].phone, phone) == 0) {
            found = 1;
            printf("\nLogin Successful!\n");
            // Check if the user is locked
            if (users[i].status) {
                printf("Your account is locked.\n");
            } else {
                printf("Your account is open.\n");
            }
            break;
        }
    }

    if (!found) {
        printf("Invalid login. Please check your email and phone number.\n");
    }
    continue;  // Go back to the main menu
}

    }
}
int main() {
	start();
    return 0;
}
