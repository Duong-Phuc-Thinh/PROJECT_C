#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Menu chính
void displayMainMenu();

// Hien thi danh sách nguoi dùng
void displayUserList();

// Thêm nguoi dùng
void addUser();

// Khóa/Mo khóa ngu?i dùng
void toggleUserStatus();

// Hien thi thông tin nguoi dùng theo ID
void displayUserDetails(char *userId);

// Sap xep danh sách nguoi dùng
void sortUserList();

// Tìm kiem nguoi dùng theo tên
void searchUserByName(char *name);

// Kiem tra du lieu nguoi dùng
bool validateUserInput(struct User user);

// Luu du lieu nguoi dùng
void saveUserData();

// doc du lieu nguoi dùng
void loadUserData();

#endif // FUNCTION_H
