#ifndef DATATYPE_H
#define DATATYPE_H

#define MAX_USERS 100
#include <stdbool.h>

typedef struct {
    char id[20];
    char name[50];
    bool gender;
    char phone[15];
    char email[50];
    char username[30];
    char password[10];
    char status[10];
} User;

typedef struct {
    char userid[20];
    float balance;
    bool status;
} AccountInfo;

typedef struct {
    char adminname[20];
    char adminpassword[20];
} AdminAccountInfo;

typedef struct {
    int day, month, year;
} Date;

#endif

