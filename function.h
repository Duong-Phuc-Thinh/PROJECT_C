#ifndef FUNCTION_H
#define FUNCTION_H

#include "datatype.h"

// Menu ch�nh
void displayMainMenu();

// Hi?n th? danh s�ch user
void displayUserList();

// Th�m user
void addUser();

// Kh�a/M? kh�a user
void toggleUserStatus();

// Hi?n th? user theo ID
void displayUserDetails(char *userId);

// S?p x?p danh s�ch user
 void sortUserList();

// T�m ki?m user theo t�n
void searchUserByName(char *name);

// Ki?m tra d? li?u user
bool validateUserInput(struct User user);


// Luu d? li?u user
void saveUserData();

// �?c d? li?u user
void loadUserData();

void displayUserDetails(char *userId);


#endif // FUNCTION_H
