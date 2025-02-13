#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Menu chính
void displayMainMenu();

// Hi?n th? danh sách user
void displayUserList();

// Thêm user
void addUser();

// Khóa/M? khóa user
void toggleUserStatus();

// Hi?n th? user theo ID
void displayUserDetails(char *userId);

// S?p x?p danh sách user
 void sortUserList();

// Tìm ki?m user theo tên
void searchUserByName(char *name);

// Ki?m tra d? li?u user
bool validateUserInput(struct User user);


// Luu d? li?u user
void saveUserData();

// Ð?c d? li?u user
void loadUserData();

void displayUserDetails(char *userId);


#endif // FUNCTION_H
