#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Menu ch�nh
void displayMainMenu();

// Hien thi danh s�ch nguoi d�ng
void displayUserList();

// Th�m nguoi d�ng
void addUser();

// Kh�a/Mo kh�a ngu?i d�ng
void toggleUserStatus();

// Hien thi th�ng tin nguoi d�ng theo ID
void displayUserDetails(char *userId);

// Sap xep danh s�ch nguoi d�ng
void sortUserList();

// T�m kiem nguoi d�ng theo t�n
void searchUserByName(char *name);

// Kiem tra du lieu nguoi d�ng
bool validateUserInput(struct User user);

// Luu du lieu nguoi d�ng
void saveUserData();

// doc du lieu nguoi d�ng
void loadUserData();

#endif // FUNCTION_H
