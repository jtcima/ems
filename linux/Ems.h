#ifndef Ems_H
#define Ems_H

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <sqlite3.h>
#include <string.h>
#include <stdarg.h>
#include <unistd.h>


#define MAX_INPUT 22
#define MAX_INPUT_EMP 50
#define INPUT_EXCEED_LIMIT_ERR -2
#define INPUT_PASS_NOT_MATCH_ERR -1
#define USERNAME_PASS_LOGIN_ERR 1
#define INPUT_EMPTY_ERR -3
#define USER_NOT_FOUND_ERR -4
#define STDIN_ERR 2
#define USER_ALREADY_EXIST_ERR 3
#define SQL_ERR 4
#define EMPLOYEE_CREATION_ERR 5
#define CSV_ERR -5

sqlite3 *db;
sqlite3_stmt *stmt;
int rc;

char* var_name[8] = {"工号(Employee Number)", "员工姓名(Employee Name)", "生日(Date of Birth)", "地址(Address)", "联系电话(Contact Number)", 
                    "职位(Position Title)", "部门(Department)", "薪水(Salary)"};

//database functions
void connect_db();
void close_db();
void create_table();
void add_user(char* name, char* pass);
int check_user_login(char* name, char* pass);

//ems functions
void waitForEscapeKey();
void create_login();
void free_mem(int count, ...);
void mem_set(int count, ...);
void clear_stdin();
int password_check(char* password, char* temp_pass);
int input_length_check(char* input);
int check_input_length(char* input,char* name_or_pass,char* func);
int check_username_exist(char*name);
void check_login();
void delete_login();
int delete_user(char* name);
void logo();
void interface_logo(char* logo_name);
void employee_logo(char* logo_name);
void login_menu();
void startup();
void user_menu();
void create_employee();
int employee_entry_length_check(char* var, char* var_name);
int employee_entry(char** employee_arry, char** var_name, int size);
void add_employee(char** employee_arry, char** var_name, int size);
void edit_employee();
int edit_emp_option_menu(char** emp_profile_cat, char* input);
int edit_emp(char* input, char* input2, char* title, int choice);
void update(char* title_ch, char* title_eng, char* input, char* title, int choice, int (*db_edit)(char*, char*, char*, int));
void view_employee();
int check_employee_exist(char* input);
void delete_employee();
int delete_emp(char* input);
void view_all_employee();
int view_all_emp(char** emp_profile_cat, int choice);
void view_single_employee();
int view_single_emp(char** emp_profile_cat, char* input, int choice);



#endif