#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "function.h"

void start(){
	loadUserData();  // Load du lieu nguoi dung tu file

    int role, choice;
    while (1) {
        // M�n h�nh login
		printf("\n=================================\n");
		printf("      BANK MANAGEMENT SYSTEM     \n");
		printf("=================================\n");
		printf("  [1] Admin Panel\n");
		printf("  [2] User Services\n");
		printf("  [0] Exit\n");
		printf("=================================\n");
		printf("  Enter your choice: ");
		scanf("%d", &role);
		
        // Kiem tra quyen truy cap
        if (role == 1) {
            char email[50], password[20];
            printf("\nEmail: ");
            scanf("%s", email);  // De tranh loi khoang trong, c� the thay bang fgets
            printf("Password: ");
            scanf("%s", password);  // Cung co the thay bang fgets

            // Kiem tra thong tin dang nhap cua Admin
            if (strcmp(email, "thinh@gmail.com") != 0 || strcmp(password, "thinhdaden") != 0) {
                printf("Login failed! Please try again.\n");
                continue;  // Quay lai vong lap login
            }
            system("cls");

            // Menu Admin
            do {
			    printf("\n=====================================\n");
			    printf("          ADMIN MENU                 \n");
			    printf("=====================================\n");
			    printf("|  [1] Add A New User               |\n");
			    printf("|  [2] Show All Users               |\n");
			    printf("|  [3] Lock/Unlock A User           |\n");
			    printf("|  [4] Search User By Name          |\n");
			    printf("|  [5] View User Details By ID      |\n");
			    printf("|  [6] Sort User List               |\n");
			    printf("|  [7] Exit                         |\n");
			    printf("=====================================\n");
			    printf(" Enter Your Choice: ");

                
                // Xu ly nhap lieu v� kiem tra
                if (scanf("%d", &choice) != 1) {
                    while (getchar() != '\n');  // Xu ly ky tu kh�ng hop le trong bo dem
                    printf("Invalid input! Please enter a valid number.\n");
                    continue;  // Quay lai vong lap menu
                }

                switch (choice) {
                    case 1:
                        system("cls");
                        addUser();
                        saveUserData(); // Them nguoi dung
                        break;
                    case 2:
                        system("cls");
                        displayUserList();  // Hien thi danh sach nguoi dung
                        break;
                    case 3:
                        system("cls");
                        toggleUserStatus();  // Khoa/Mo khoa nguoi dung
                        break;
                    case 4: {
                        char searchName[50];
                        printf("Enter name to search: ");
                        scanf("%s", searchName);
                        system("cls");
                        searchUserByName(searchName);  // T�m ki?m ngu?i d�ng theo t�n
                        break;
                    }
                    case 5: {
                        char userId[10];
                        printf("Enter User ID: ");
                        scanf("%s", userId);
                        system("cls");
                        displayUserDetails(userId);  // Hien thi chi tiet nguoi dung theo ID
                        break;
                    }
                    case 6:
                        system("cls");
                        sortUserList();  // Sap xep danh sach nguoi d�ng theo ID
                        break;
                    case 7:
                        system("cls");
                        saveUserData();  // Luu du lieu nguoi dung
                        printf("Exiting Admin Menu...\n");
                        return;  // Thoat chuong trinh
                    default:
                        printf("Invalid choice! Please try again.\n");
                }

                // Quay lai menu chinh hoac thoat chuong trinh
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
                    system("cls");  // Clear m�n hinh va quay lai menu Admin
                }

            } while (choice != 7); // Lap lai menu cho den khi chon tho�t
        }
        
        // Phan cho User (Neu c� y�u cau sau)
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
