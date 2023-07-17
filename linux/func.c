#include "Ems.h"

void waitForEscapeKey() 
{
    int key;
    
    while (1) {
        key = getchar(); // or getchar() for Linux/Mac
        
        if (key == 27) { // ASCII value of escape key
            printf("Escape key pressed. Exiting...\n");
            return; // Exit out of the function
        }
    }
}

void free_mem(int count, ...)
{
    va_list args;
    
    va_start(args, count);

    for(int i=0; i < count; i++)
    {
        free(va_arg(args, char*));
    }

    va_end(args);
}

void mem_set(int count, ...)
{
    va_list args;
    
    va_start(args, count);

    for(int i=0; i < count; i++)
    {
        char* ptr = va_arg(args, char*);
        size_t length = strlen(ptr);
        memset(ptr, '0', length);
    }

    va_end(args);
}

void clear_stdin()
{
    int c;
    while((c = getchar()) != '\n' && c != EOF){}
}

int check_stdin()
{
    int c = getchar();
    if( c!= EOF )
    {
        return STDIN_ERR;
    }
    
    return 0;
}

int input_length_check(char* input)
{
    size_t len = strlen(input);
    if(len > 0)
    {
        if (input[len-1] != '\n')
        {
            return INPUT_EXCEED_LIMIT_ERR;
        }
    }
    if(len == 1)
    {
        return INPUT_EMPTY_ERR;
    }
    
    return 0;
}

int check_input_length(char* input, char* name_or_pass, char* func)
{
    int check_result = input_length_check(input);
    if (check_result == INPUT_EXCEED_LIMIT_ERR)
    {
        if(strcmp(name_or_pass, "username") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n用户名超过长度限制,用户创建失败,按回车键继续(Input length exceeds limit,user creation failed,press enter to continue)\n");
                printf("\033[0m");
            }
            if(strcmp(func, "check_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n用户名超过长度限制,用户登录失败,按回车键继续(Input length exceeds limit,user log in failed,press enter to continue)\n");
                printf("\033[0m");
            }
            
        }
        if(strcmp(name_or_pass, "password") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n密码超过长度限制,用户创建失败,按回车键继续(Input length exceeds limit,user creation failed,press enter to continue)\n");
                printf("\033[0m");
            }
            if(strcmp(func, "check_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n密码超过长度限制,用户登录失败,按回车键继续(Input length exceeds limit,user log in failed,press enter to continue)\n");
                printf("\033[0m");
            }
            
        }
        if(strcmp(name_or_pass, "temp_pass") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n密码超过长度限制,用户创建失败,按回车键继续(Input length exceeds limit,user creation failed,press enter to continue)\n");
                printf("\033[0m");
            }
            if(strcmp(func, "check_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n密码超过长度限制,用户登录失败,按回车键继续(Input length exceeds limit,user log in failed,press enter to continue)\n");
                printf("\033[0m");            
            }
            
        }
        clear_stdin();
        clear_stdin();
        return INPUT_EXCEED_LIMIT_ERR;
    }
    if (check_result == INPUT_EMPTY_ERR)
    {
        if(strcmp(name_or_pass, "username") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n用户名不能空白,用户创建失败,按回车键继续(Username cannot be left blank,user creation failed,press enter to continue)\n");
                printf("\033[0m");
            }
            if(strcmp(func, "check_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n用户名不能空白,用户登录失败,按回车键继续(Username cannot be left blank,user login failed,press enter to continue)\n");
                printf("\033[0m");
            }   
        }
        if(strcmp(name_or_pass, "password") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n密码不能空白,用户创建失败,按回车键继续(Password cannot be left blank,user creation failed,press enter to continue)\n");
                printf("\033[0m");
            }
            if(strcmp(func, "check_login") == 0)
            {
                printf("\33[1;5;31m");
                printf("\n密码不能空白,用户登录失败,按回车键继续(Password cannot be left blank,user login failed,press enter to continue)\n");
                printf("\033[0m");
            }
        }
        if(strcmp(name_or_pass, "temp_pass") == 0)        
        {
            printf("\33[1;5;31m");
            printf("\n密码不能空白,用户创建失败,按回车键继续(Password cannot be left blank,user creation failed,press enter to continue)\n"); 
            printf("\033[0m");
        }   
        clear_stdin();
        return INPUT_EMPTY_ERR;                
    }
    return 0;
}

int password_check(char* password, char* temp_pass)
{
    int len = strlen(password);
    int len2 = strlen(temp_pass);

    if(len != len2)
    {
        return INPUT_PASS_NOT_MATCH_ERR;
    }

    if(len == len2)
    {
        for(int i = 0; i<len ; i++ )
        {
            if(password[i] != temp_pass[i])
            {
                return INPUT_PASS_NOT_MATCH_ERR;
            }
        }
    }
    return 0; 
}


void create_login()
{
    interface_logo("| 创建用户(CREATE USER) |");

    char* username = (char*) calloc(MAX_INPUT, sizeof(char));
    char* password = (char*) calloc(MAX_INPUT, sizeof(char));
    char* temp_pass = (char*) calloc(MAX_INPUT, sizeof(char));
    
    printf("\n");
    printf("\33[1;33m");
    printf("请注意,用户名和密码长度不得超过20个字符(Please note,username and password length should be less than 20 characters)\n");
    printf("\033[0m");
    printf("\n");
    printf("\33[1;33m");
    printf("请创建用户名(Please create your username): ");
    printf("\033[0m");
    fgets(username, MAX_INPUT, stdin);
    int result = check_username_exist(username);
    
    if(result > 0)
    {
        printf("\33[1;5;31m");
        printf("\n用户名已存在,创建用户失败,按回车键继续(username already exists,user creation failed,press enter to continue)\n");
        printf("\033[0m");
        mem_set(1, username);
        free_mem(1, username);
        clear_stdin();
        login_menu();
    }
    if(result <= 0)
    {
        result = check_input_length(username, "username", "create_login");
        if(result != 0)
        {
            mem_set(1, username);
            free_mem(1, username);
            login_menu();
        }
        if(result == 0)
        {
            printf("\33[1;33m");
            printf("请输入密码(Please enter your password): ");
            printf("\033[0m");
            fgets(password, MAX_INPUT, stdin);
            result = check_input_length(password, "password", "create_login");
            if(result != 0)
            {
                mem_set(2, username, password);
                free_mem(2, username, password);
                login_menu();
            }
            if(result == 0)
            {
                printf("\33[1;33m");
                printf("请再输入一遍密码(Please re-enter your password): ");
                printf("\033[0m");
                fgets(temp_pass, MAX_INPUT, stdin);
                result = check_input_length(temp_pass, "temp_pass", "create_login");
                if(result != 0)
                {
                    mem_set(3, username, password, temp_pass);
                    free_mem(3, username, password, temp_pass);
                    login_menu();
                }
                if(result == 0)
                {
                    int check_result = password_check(password, temp_pass);
                    if(check_result == INPUT_PASS_NOT_MATCH_ERR)
                    {
                        printf("\33[1;5;31m");
                        printf("\n两次输入的密码不同,用户创建失败,按回车键继续(The password you entered are not the same,user creation failed,press enter to continue)\n");
                        printf("\033[0m");
                        mem_set(3, username, password, temp_pass);
                        free_mem(3, username, password, temp_pass);
                        clear_stdin();
                        login_menu();
                    }
                    if(check_result == 0)
                    {
                        add_user(username, password);
                        // Clear sensitive data from memory
                        mem_set(3, username, password, temp_pass);
                        free_mem(3, username, password, temp_pass);
                        system("clear");
                        logo();
                        check_login();
                    }
                }
            }
        }
    }
    return;   
}

void check_login()
{   
    interface_logo("| 用户登录(USER LOG IN) |");
    char* username = (char*) calloc(MAX_INPUT, sizeof(char));
    char* password = (char*) calloc(MAX_INPUT, sizeof(char));
    
    printf("\33[1;33m");
    printf("\n                       用户名(Username): ");
    printf("\033[0m");
    fgets(username, MAX_INPUT, stdin);
    int result = check_input_length(username, "username", "check_login");

    if(result != 0)
    {
        mem_set(1, username);
        free_mem(1, username);
        login_menu();  
    }
    if(result == 0)
    {
        printf("\33[1;33m");
        printf("                       密码(Password): ");
        printf("\033[0m");
        fgets(password, MAX_INPUT, stdin);
        result = check_input_length(password, "password", "check_login");
        if(result != 0)
        {
            mem_set(2,username, password);
            free_mem(2, username, password);
            login_menu();
        }
        if(result == 0)
        {
            int check_result = check_user_login(username, password);

            if (check_result == 0)
            {
                printf("\n");
                printf("\33[1;32m");
                printf("用户登录成功,转至用户主界面,按回车键继续(User login successfully, re-direct to user main interface, press enter to continue)\n");
                printf("\033[0m");
                clear_stdin();
                mem_set(2, username, password);
                free_mem(2, username, password);
                user_menu();
            }

            if (check_result == USERNAME_PASS_LOGIN_ERR)
            {
                printf("\n");
                printf("\33[1;5;31m");
                printf("用户名或密码不正确,按回车键继续(Username or password incorrect,press enter to continue)\n");
                printf("\033[0m");
                mem_set(2, username, password);
                free_mem(2, username, password);
                clear_stdin();
                login_menu();
            }

            if (check_result == USER_NOT_FOUND_ERR)
            {
                printf("\n");
                printf("\33[1;5;31m");
                printf("用户不存在.按回车键继续(User does not exist,press enter to continue)\n");
                printf("\033[0m");
                mem_set(2, username, password);
                free_mem(2, username, password);
                clear_stdin();
                login_menu();
            }
        }
    }
    return;
}

void delete_login()
{
    interface_logo("| 删除用户(DELETE USER) |");
    char* username = (char*) calloc(MAX_INPUT, sizeof(char));
    printf("\33[1;33m");
    printf("\n请输入要删除的用户名(Please enter the username you wish to delete): ");
    printf("\033[0m");
    fgets(username, MAX_INPUT, stdin);
    int result = input_length_check(username);

    if(result == INPUT_EXCEED_LIMIT_ERR)
    {
        printf("\33[1;5;31m");
        printf("\n用户名超过长度限制,用户删除失败,按回车键继续(Input length exceeds limit,delete user failed,press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
    }
    if(result == INPUT_EMPTY_ERR)
    {
        printf("\33[1;5;31m");
        printf("\n用户名不能空白,用户删除失败,按回车键继续(Username cannot be empty,delete user failed,press enter to continue)\n");
        printf("\033[0m");
    }
    if(result == 0)
    {
        result = check_username_exist(username);
        if(result > 0)
        {
            int result1 = delete_user(username);
            if(result1 != 0)
            {
                printf("\33[1;5;31m");
                printf("\n数据库错误,用户删除失败,按回车键继续(Database error,delete user failed,press enter to continue)\n");
                printf("\033[0m");
            }
            if(result1 == 0)
            {
                printf("\33[1;32m");
                printf("\n用户删除成功,按回车键继续(Delete user successfully,press enter to continue)\n");
                printf("\033[0m");
            }
        }
        if(result <= 0)
        {
            printf("\33[1;5;31m");
            printf("\n用户名不存在,用户删除失败,按回车键继续(Username does not exist,delete user failed,press enter to continue)\n");
            printf("\033[0m");
        }

    }

    clear_stdin();
    mem_set(1,username);
    free_mem(1, username);
    login_menu();
    return;    
}

void login_menu()
{
    system("clear");
    logo();
    char choice[3];
    printf("\033[1;33m");
    printf("\n");
    printf("                        1.用户登录(User Login)\n");
    printf("                        2.创建用户(Create User)\n");
    printf("                        3.删除用户(Delete User)\n");
    printf("                        4.退出系统(Exit EMS)\n\n");
    printf("\033[0m");
    printf("\033[1m");
    printf("请选择选项1-4(Please only choose option 1 to 4): ");
    printf("\033[0m");
    
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n无效选项,请选择1-4,按回车键继续(Invalid choice,please only choose option 1 to 4. Press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
        login_menu(); 
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
        switch(atoi(choice))
        {
            case 1:
                system("clear");
                logo();
                check_login();
                break;
            case 2:
                system("clear"); 
                logo(); 
                create_login();
                break;
            case 3:
                system("clear"); 
                logo(); 
                delete_login();
                break;
            case 4:
                system("clear");
                close_db();
                printf("\033[1;33m");
                printf("退出系统(Exit EMS)\n");
                printf("\033[0m");
                exit(0);
                break;
            default:
                printf("\033[1;5;31m");
                printf("\n无效选项,请选择1-4,按回车键继续(Invalid choice,please only choose option 1 to 4. Press enter to continue)\n");
                printf("\033[0m");
                clear_stdin();
                login_menu();      
                break;             
        }
    }
    return;    
}

void logo()
{   
    for (int i = 0; i < 70; i++)
    {
        printf("\033[1;34m");
        printf("*");
    }
    printf("\n");

    printf("          @@@@@@@@@@@       @@@@     @@@@          @@@@@@@\n");
    printf("         @@               @@  @@   @@   @@       @@      @@\n");
    printf("        @@               @@   @@  @@    @@      @@       \n");
    printf("       @@@@@@@@@@@@     @@    @@ @@     @@       @@@@@@@\n");
    printf("      @@               @@     @@        @@             @@\n");
    printf("     @@               @@      @@        @@    @@     @@\n");
    printf("    @@@@@@@@@@@@@    @@       @@        @@     @@@@@@@    \n");
    printf("\033[1;33m");
    printf("                                                             @jtcima\n");
    printf("\033[1;34m");
    for (int i = 0; i < 70; i++)
    {
        printf("*");
    }
    printf("\n");   
    printf("\033[0m"); 
    return;
}

void interface_logo(char* logo_name)
{
    printf("\33[1;33m");
    for(int i = 0; i < 23; i++)
    {
        printf(" ");
    }
    for(int n = 0; n<25; n++)
    {
        printf("-");
    }
    printf("\n");
    for(int i = 0; i < 23; i++)
    {
        printf(" ");  
    }
    printf("%s\n", logo_name);
    
    for(int i = 0; i < 23; i++)
    {
        printf(" ");
    }
    for(int n = 0; n<25; n++)
    {
        printf("-");
    }
    printf("\n");
    printf("\033[0m");
    return;
}

void employee_logo(char* logo_name)
{
    printf("\33[1;33m");
    for(int i = 0; i < 14; i++)
    {
        printf(" ");
    }
    for(int n = 0; n<41; n++)
    {
        printf("-");
    }
    printf("\n");
    for(int i = 0; i < 14; i++)
    {
        printf(" ");  
    }
    printf("%s\n", logo_name);
    
    for(int i = 0; i < 14; i++)
    {
        printf(" ");
    }
    for(int n = 0; n<41; n++)
    {
        printf("-");
    }
    printf("\n");
    printf("\033[0m");
    return;
}
void startup()
{
    logo();
    connect_db();
    sleep(1);
    create_table();
    return;
}


int employee_entry_length_check(char* var, char* var_name)
{
    int result = input_length_check(var);
    if(result == INPUT_EXCEED_LIMIT_ERR)
    {
        printf("\033[1;5;31m");
        printf("\n%s超过50个字符限制.员工档案创建失败.按回车继续(exceeds length limit 50 characters. Employee profile creation failed. Press enter to continue)\n", var_name);
        printf("\033[0m");
        clear_stdin();
        return INPUT_EXCEED_LIMIT_ERR;
    }
    return 0;
}

int employee_entry(char** employee_arry, char** var_name, int size)
{
    printf("\n");
    for(int i = 0; i < size; i++)
    {
        printf("\033[1;32m");
        printf("%s: ", var_name[i]);
        printf("\033[0m");
        fgets(employee_arry[i], MAX_INPUT_EMP, stdin);  
        if(employee_entry_length_check(employee_arry[i], var_name[i]) != 0)
        {
            clear_stdin();
            return EMPLOYEE_CREATION_ERR;
        }
    }

    return 0;
}

void create_employee()
{
    employee_logo("| 创建员工档案(CREATE EMPLOYEE PROFILE) |");
    char* emp_no = calloc(MAX_INPUT_EMP, sizeof(char));
    char* name = calloc(MAX_INPUT_EMP, sizeof(char)); 
    char* dob = calloc(MAX_INPUT_EMP, sizeof(char));   
    char* position = calloc(MAX_INPUT_EMP, sizeof(char));
    char* department = calloc(MAX_INPUT_EMP, sizeof(char));
    char* contact_num = calloc(MAX_INPUT_EMP, sizeof(char));
    char* address = calloc(MAX_INPUT_EMP, sizeof(char));
    char* salary = calloc(MAX_INPUT_EMP, sizeof(char));
    
    char* employee_arry[8] = {emp_no,name,dob,address,contact_num,position,department,salary};

    int result = employee_entry(employee_arry, var_name, 8);
    
    if(result == EMPLOYEE_CREATION_ERR)
    {
        user_menu();
    }
    if(result == 0)
    {
        add_employee(employee_arry, var_name, 8);
    }
    return;
}

void update(char* title_ch, char* title_eng, char* input, char* title, int choice, int (*db_edit)(char*, char*, char*, int))
{
    char* edit = calloc(MAX_INPUT_EMP, sizeof(char));
    printf("\33[1;32m");
    printf("请输入新的%s(Please enter new %s): ", title_ch, title_eng);
    printf("\033[0m");
    fgets(edit, MAX_INPUT_EMP, stdin);
    if(input_length_check(edit) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n输入内容超过50个字符限制,员工档案更改失败,按回车键继续(Input exceeds 50 characters limit,edit employee profile failed,press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
        system("clear");
        logo();
        user_menu();
    }
    if(input_length_check(edit) != INPUT_EXCEED_LIMIT_ERR)
    {
        db_edit(input, edit, title, choice);
    }
    mem_set(1, edit);
    free_mem(1, edit);
}

void edit_employee()
{
    employee_logo("| 编辑员工档案( Edit EMPLOYEE PROFILE ) |");
    char* input = calloc(MAX_INPUT_EMP, sizeof(char));
    printf("\33[1;33m");
    printf("\n请输入要编辑的员工姓名或工号(Please enter the employee name or employee number you wish to edit): ");
    printf("\033[0m");
    fgets(input, MAX_INPUT_EMP, stdin);
    if(input_length_check(input) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n输入内容超过50个字符限制,员工档案更改失败,按回车键继续(Input exceeds 50 characters limit,delete employee profile failed,press enter to continue)\n");
        printf("\033[0m");
        
    }
    if(input_length_check(input) == INPUT_EMPTY_ERR)
    {
        printf("\033[1;5;31m");
        printf("\n输入内容为空,员工档案更改失败,按回车键继续(Input empty,delete employee profile failed,press enter to continue)\n");
        printf("\033[0m");
    }
    if(input_length_check(input) == 0)
    {
        if(check_employee_exist(input) > 0)
        {
            int cont = 1;
            while(1)
            {
                if(cont == 1)
                {
                    printf("\n");
                    edit_emp_option_menu(var_name, input);
                    char choice[3];
                    printf("\33[1;32m");
                    printf("请从以上选项中输入1到8选择您想要编辑的内容(Please enter 1 to 8 from the above options which you would like to edit): ");
                    printf("\033[0m");
                    fgets(choice, sizeof(choice), stdin);
                    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
                    {
                        clear_stdin();
                        printf("\033[1;5;31m");
                        printf("\n无效选项,请选择选项1-8,按回车键继续(Invalid choice, please only choose option from 1 to 8, press enter to continue)\n");
                        printf("\033[0m");
                        clear_stdin();
                        system("clear");
                        logo();
                        user_menu();
                    }
                    else
                    {
                        switch(atoi(choice))
                        {
                            case 1:
                                update("工号", "employee number",input, "emp_no", 1, edit_emp);
                                break;
                            case 2:
                                update("姓名", "employee name", input, "name", 2, edit_emp);
                                break;
                            case 3:
                                update("生日", "date of birth", input, "dob", 3, edit_emp);
                                break;
                            case 4:
                                update("地址", "address", input, "address", 4, edit_emp);
                                break;
                            case 5:
                                update("联系电话", "contact number", input, "contact_num", 5, edit_emp);
                                break;
                            case 6:
                                update("职位", "position", input, "position", 6, edit_emp);
                                break;
                            case 7:
                                update("部门", "department", input, "department", 7,edit_emp);
                                break;
                            case 8:
                                update("薪水", "salary", input, "salary", 8, edit_emp);
                                break;
                            default:
                                printf("\033[1;5;31m");
                                printf("\n无效选项,请选择选项1-8,按回车键继续(Invalid choice, please only choose option from 1 to 8, press enter to continue)\n");
                                printf("\033[0m");
                                clear_stdin();
                                system("clear");
                                logo();
                                user_menu();
                                break;
                        }
                    }
                    char option[3];
                    fgets(option,sizeof(option),stdin);
                    if(input_length_check(option) == INPUT_EXCEED_LIMIT_ERR)
                    {
                        clear_stdin();
                        printf("\033[1;5;31m");
                        printf("\n无效选择,请用'Y'或'y'代表是,'N'或者'n'代表不是,按回车键继续(Invalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue)\n");
                        printf("\033[0m");
                        clear_stdin();
                        system("clear");
                        logo();
                        user_menu();
                    }
                    else
                    {
                        if(option[0] == 'y' || option[0] == 'Y')
                        {
                            cont = 1;
                        }
                        else
                        {
                            cont = 0;
                        }
                    }
                    system("clear");
                    logo();
                    employee_logo("| 编辑员工档案( Edit EMPLOYEE PROFILE ) |");
                }
                else
                {
                    printf("\033[1;32m");
                    printf("\n员工档案编辑完成,返回用户主界面,按回车继续(Edit employee profile complete,return to main user interface,press enter to continue)\n");
                    printf("\033[0m");
                    break;
                }
            }
            
        }
        else
        {
            printf("\033[1;5;31m");
            printf("\n员工不存在,按回车键继续(Employee doesn't exist, press enter to continue)\n");
            printf("\033[0m");
        }
    }
    clear_stdin();
    mem_set(1, input);
    free_mem(1, input);
    system("clear");
    logo();
    user_menu();
    return;
}    

void view_employee()
{
    employee_logo("| 浏览员工档案( VIEW EMPLOYEE PROFILE ) |");
    char choice[3];
    printf("\33[1;32m");
    printf("\n1.浏览所有员工档案(View all employee profiles)\n");
    printf("2.选择单个员工档案(View single employee profile)\n");
    printf("3.返回用户主界面(Return to main user interface)\n");
    printf("\n您的选择是: ");
    printf("\033[0m");
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n无效选项,请选择选项1-3,按回车键继续(Invalid choice, please only choose option from 1 to 3, press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
        system("clear");
        logo();
        view_employee();
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
        switch(atoi(choice))
        {
            case 1:
                system("clear");
                logo();
                view_all_employee();
                break;
            case 2:
                system("clear");
                logo();
                view_single_employee();
                break;
            case 3:
                user_menu();
                break;
            default:
                printf("\033[1;5;31m");
                printf("\n无效选项,请选择选项1-3,按回车键继续(Invalid choice, please only choose option from 1 to 3, press enter to continue)\n");
                printf("\033[0m");
                clear_stdin();
                system("clear");
                logo();
                view_employee();
                break;
        }
    } 
    return;
}

void view_all_employee()
{   
    employee_logo("| 浏览员工档案( VIEW EMPLOYEE PROFILE ) |");
    char choice[3];
    printf("\033[1;33m");
    printf("\n请问您想把档案输出到CSV文档来浏览吗?请用'Y'或'y'代表是,'N'或者'n'代表不是(Do you wish to view all profiles in CSV file? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
    printf("\033[0m");
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n无效选择,请用'Y'或'y'代表是,'N'或者'n'代表不是,按回车键继续(Invalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
        system("clear");
        logo();
        view_employee();
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
       switch(choice[0])
       {
            case 'Y':
            case 'y':
                if(view_all_emp(var_name, 2) == 0)
                {
                    printf("\33[1;33m");
                    printf("\n档案输出到CSV文档成功,按回车键继续(All profiles export to CSV successfully,press enter to continue)\n");
                    printf("\033[0m");
                }
                if(view_all_emp(var_name, 2) != 0)
                {
                    printf("\33[1;5;31m");
                    printf("\n档案输出到CSV文档失败,按回车键继续(All profiles export to CSV failed,press enter to continue)\n");
                    printf("\033[0m");
                }
                clear_stdin();
                system("clear");
                logo();
                view_employee();
                break;
            case 'N':
            case 'n':
                system("clear");
                logo();
                printf("\n");
                view_all_emp(var_name, 1);
                printf("\33[1;33m");
                printf("\n按回车键继续(Press enter to continue)\n");
                printf("\033[0m");
                clear_stdin();
                system("clear");
                logo();
                view_employee();
                break;
            default:
                printf("\033[1;5;31m");
                printf("\n无效选择,请用'Y'或'y'代表是,'N'或者'n'代表不是,按回车键继续(Invalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue)\n");
                printf("\033[0m");
                clear_stdin();
                system("clear");
                logo();
                view_employee(); 
                break;
       }
    }
    return;
}


void view_single_employee()
{
    employee_logo("| 浏览员工档案( VIEW EMPLOYEE PROFILE ) |");
    char* input = calloc(MAX_INPUT_EMP, sizeof(char));
    printf("\33[1;33m");
    printf("\n请输入要浏览的员工姓名或工号(Please enter the employee name or employee number you wish to view): ");
    printf("\033[0m");
    fgets(input, MAX_INPUT_EMP, stdin);
    if(input_length_check(input) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n输入内容超过50个字符限制,员工档案浏览失败,按回车键继续(Input exceeds 50 characters limit,delete employee profile failed,press enter to continue)\n");
        printf("\033[0m");
        
    }
    if(input_length_check(input) == INPUT_EMPTY_ERR)
    {
        printf("\033[1;5;31m");
        printf("\n输入内容为空,员工档案浏览失败,按回车键继续(Input empty,delete employee profile failed,press enter to continue)\n");
        printf("\033[0m");
    }
    if(input_length_check(input) == 0)
    {
        if(check_employee_exist(input) > 0)
        {
            char choice[3];
            printf("\033[1;33m");
            printf("\n请问您想把档案输出到CSV文档来浏览吗?请用'Y'或'y'代表是,'N'或者'n'代表不是(Do you wish to view all profiles in CSV file? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
            printf("\033[0m");
            fgets(choice, sizeof(choice), stdin);
            if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
            {
                clear_stdin();
                printf("\033[1;5;31m");
                printf("\n无效选择,请用'Y'或'y'代表是,'N'或者'n'代表不是,按回车键继续(Invalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue)\n");
                printf("\033[0m");
            }
            if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
            {
               switch(choice[0])
               {
                    case 'Y':
                    case 'y':
                        if(view_single_emp(var_name, input, 2) == 0)
                        {
                            printf("\33[1;33m");
                            printf("\n档案输出到CSV文档成功,按回车键继续(All profiles export to CSV successfully,press enter to continue)\n");
                            printf("\033[0m");
                        }
                        if(view_single_emp(var_name, input, 2) != 0)
                        {
                            printf("\33[1;5;31m");
                            printf("\n档案输出到CSV文档失败,按回车键继续(All profiles export to CSV failed,press enter to continue)\n");
                            printf("\033[0m");
                        }
                        break;
                    case 'N':
                    case 'n':
                        system("clear");
                        logo();
                        printf("\n");
                        view_single_emp(var_name, input, 1);
                        printf("\33[1;33m");
                        printf("\n按回车键继续(Press enter to continue)\n");
                        printf("\033[0m");
                        break;
                    default:
                        printf("\033[1;5;31m");
                        printf("\n无效选择,请用'Y'或'y'代表是,'N'或者'n'代表不是,按回车键继续(Invalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue)\n");
                        printf("\033[0m"); 
                        break;
               }
            }
        }
        else
        {
            printf("\033[1;5;31m");
            printf("\n员工不存在,按回车键继续(Employee doesn't exist, press enter to continue)\n");
            printf("\033[0m");
        }
    }
    clear_stdin();
    mem_set(1, input);
    free_mem(1, input);
    system("clear");
    logo();
    view_employee();
    return;
}


void delete_employee()
{
    employee_logo("| 删除员工档案(DELETE EMPLOYEE PROFILE) |");
    char* input = calloc(MAX_INPUT_EMP, sizeof(char));
    printf("\33[1;33m");
    printf("\n请输入要删除的员工姓名或工号(Please enter the employee name or employee number you wish to delete): ");
    printf("\033[0m");
    fgets(input, MAX_INPUT_EMP, stdin);
    if(input_length_check(input) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n输入内容超过50个字符限制,员工档案删除失败,按回车键继续(Input exceeds 50 characters limit,delete employee profile failed,press enter to continue)\n");
        printf("\033[0m");
        
    }
    if(input_length_check(input) == INPUT_EMPTY_ERR)
    {
        printf("\033[1;5;31m");
        printf("\n输入内容为空,员工档案删除失败,按回车键继续(Input empty,delete employee profile failed,press enter to continue)\n");
        printf("\033[0m");
    }
    if(input_length_check(input) == 0)
    {
        if(check_employee_exist(input) > 0)
        {
            int result = delete_emp(input);
            if(result == 0)
            {
                printf("\033[1;32m");
                printf("\n员工删除成功,转至用户主界面,按回车键继续(Employee deleted successfully,re-direct to main user interface,press enter to continue)\n");
                printf("\033[0m");
            }
        }
        else
        {
            printf("\033[1;5;31m");
            printf("\n员工不存在,按回车键继续(Employee doesn't exist, press enter to continue)\n");
            printf("\033[0m");
        }
    }

    clear_stdin();
    mem_set(1, input);
    free_mem(1, input);
    user_menu();
}

void user_menu()
{   
    system("clear");
    logo();
    char choice[3];
    printf("\33[1;32m");
    printf("\n您好(Hello), 今天您想做什么(what would you like to do today)?\n\n请从以下选项中选择(Please select from the following options):\n\n");
    printf("1.创建新员工档案(Create new employee profile)\n");
    printf("2.编辑员工档案(Edit employee profile)\n");
    printf("3.浏览员工档案(View employee profile)\n");
    printf("4.删除员工档案(Delete employee profile)\n");
    printf("5.返回系统登录界面(Return to system login interface )\n\n");
    printf("您的选择是: ");
    printf("\033[0m");
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
        printf("\033[1;5;31m");
        printf("\n无效选项,请选择选项1-5,按回车键继续(Invalid choice, please only choose option from 1 to 5, press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
        user_menu();
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
        switch(atoi(choice))
        {
            case 1:
                system("clear");
                logo();
                create_employee();
                break;
            case 2:
                system("clear");
                logo();
                edit_employee();
                break;
            case 3:
                system("clear");
                logo();
                view_employee();
                break;
            case 4:
                system("clear");
                logo();
                delete_employee();
                break;
            case 5:
                printf("\033[1;31m");
                printf("\n退出登录(Exit login)...\n");
                printf("\033[0m");
                sleep(1);
                system("clear");
                logo();
                login_menu();
                break;
            default:
                printf("\033[1;5;31m");
                printf("\n无效选项,请选择选项1-5,按回车键继续(Invalid choice, please only choose option from 1 to 5, press enter to continue)\n");
                printf("\033[0m");
                clear_stdin();
                user_menu();
                break;
        }
    } 
    return;
}
