#include "Ems.h"

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
                 
                printf("\nInput length exceeds limit,user creation failed,press enter to continue\n");
                  
            }
            if(strcmp(func, "check_login") == 0)
            {
                 
                printf("\nInput length exceeds limit,user log in failed,press enter to continue\n");
                  
            }
            
        }
        if(strcmp(name_or_pass, "password") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                 
                printf("\nInput length exceeds limit,user creation failed,press enter to continue\n");
                  
            }
            if(strcmp(func, "check_login") == 0)
            {
                 
                printf("\nInput length exceeds limit,user log in failed,press enter to continue\n");
                  
            }
            
        }
        if(strcmp(name_or_pass, "temp_pass") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                 
                printf("\nInput length exceeds limit,user creation failed,press enter to continue\n");
                  
            }
            if(strcmp(func, "check_login") == 0)
            {
                 
                printf("\nInput length exceeds limit,user log in failed,press enter to continue\n");
                              
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
                 
                printf("\nUsername cannot be left blank,user creation failed,press enter to continue\n");
                  
            }
            if(strcmp(func, "check_login") == 0)
            {
                 
                printf("\nUsername cannot be left blank,user login failed,press enter to continue\n");
                  
            }   
        }
        if(strcmp(name_or_pass, "password") == 0)
        {
            if(strcmp(func, "create_login") == 0)
            {
                 
                printf("\nPassword cannot be left blank,user creation failed,press enter to continue\n");
                  
            }
            if(strcmp(func, "check_login") == 0)
            {
                 
                printf("\nPassword cannot be left blank,user login failed,press enter to continue\n");
                  
            }
        }
        if(strcmp(name_or_pass, "temp_pass") == 0)        
        {
             
            printf("\nPassword cannot be left blank,user creation failed,press enter to continue\n"); 
              
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
    interface_logo("|    CREATE USER    |");

    char* username = (char*) calloc(MAX_INPUT, sizeof(char));
    char* password = (char*) calloc(MAX_INPUT, sizeof(char));
    char* temp_pass = (char*) calloc(MAX_INPUT, sizeof(char));
    
    printf("\nPlease note,username and password length should be less than 20 characters\n");
    
    printf("\nPlease create your username: ");
      
    fgets(username, MAX_INPUT, stdin);
    int result = check_username_exist(username);
    
    if(result > 0)
    {
         
        printf("\nusername already exists,user creation failed,press enter to continue\n");
          
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
            
            printf("Please enter your password: ");
              
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
                
                printf("Please re-enter your password: ");
                  
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
                         
                        printf("\nThe password you entered are not the same,user creation failed,press enter to continue\n");
                          
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
                        system("cls");
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
    interface_logo("|    USER LOG IN    |");
    char* username = (char*) calloc(MAX_INPUT, sizeof(char));
    char* password = (char*) calloc(MAX_INPUT, sizeof(char));
    
    
    printf("\n                           Username: ");
      
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
        
        printf("                           Password: ");
          
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
                
                printf("\nUser login successfully, re-direct to user main interface, press enter to continue\n");
                  
                clear_stdin();
                mem_set(2, username, password);
                free_mem(2, username, password);
                user_menu();
            }

            if (check_result == USERNAME_PASS_LOGIN_ERR)
            {
                printf("\nUsername or password incorrect,press enter to continue\n");
                  
                mem_set(2, username, password);
                free_mem(2, username, password);
                clear_stdin();
                login_menu();
            }

            if (check_result == USER_NOT_FOUND_ERR)
            {
                printf("\nUser does not exist,press enter to continue\n");
                  
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
    interface_logo("|    DELETE USER    |");
    char* username = (char*) calloc(MAX_INPUT, sizeof(char));
    
    printf("\nPlease enter the username you wish to delete: ");
      
    fgets(username, MAX_INPUT, stdin);
    int result = input_length_check(username);

    if(result == INPUT_EXCEED_LIMIT_ERR)
    {
         
        printf("\nInput length exceeds limit,delete user failed,press enter to continue\n");
          
        clear_stdin();
    }
    if(result == INPUT_EMPTY_ERR)
    {
         
        printf("\nUsername cannot be empty,delete user failed,press enter to continue\n");
          
    }
    if(result == 0)
    {
        result = check_username_exist(username);
        if(result > 0)
        {
            int result1 = delete_user(username);
            if(result1 != 0)
            {
                 
                printf("\nDatabase error,delete user failed,press enter to continue\n");
                  
            }
            if(result1 == 0)
            {
                
                printf("\nDelete user successfully,press enter to continue\n");
                  
            }
        }
        if(result <= 0)
        {
             
            printf("\nUsername does not exist,delete user failed,press enter to continue\n");
              
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
    system("cls");
    logo();
    char choice[3];
    
    printf("\n");
    printf("                        1.User Login\n");
    printf("                        2.Create User\n");
    printf("                        3.Delete User\n");
    printf("                        4.Exit EMS\n\n");
   
    printf("Please only choose option 1 to 4: ");
      
    
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInvalid choice,please only choose option 1 to 4. Press enter to continue\n");
          
        clear_stdin();
        login_menu(); 
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
        switch(atoi(choice))
        {
            case 1:
                system("cls");
                logo();
                check_login();
                break;
            case 2:
                system("cls"); 
                logo(); 
                create_login();
                break;
            case 3:
                system("cls"); 
                logo(); 
                delete_login();
                break;
            case 4:
                system("cls");
                close_db();
                
                printf("Exit EMS\n");
                  
                exit(0);
                break;
            default:
                 
                printf("\nInvalid choice,please only choose option 1 to 4. Press enter to continue\n");
                  
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
    
    printf("                                                             @jtcima\n");
    for (int i = 0; i < 70; i++)
    {
        printf("*");
    }
    printf("\n");   
       
    return;
}

void interface_logo(char* logo_name)
{
    
    for(int i = 0; i < 23; i++)
    {
        printf(" ");
    }
    for(int n = 0; n<21; n++)
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
    for(int n = 0; n<21; n++)
    {
        printf("-");
    }
    printf("\n");
      
    return;
}

void employee_logo(char* logo_name)
{
    
    for(int i = 0; i < 14; i++)
    {
        printf(" ");
    }
    for(int n = 0; n<35; n++)
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
    for(int n = 0; n<35; n++)
    {
        printf("-");
    }
    printf("\n");
      
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
         
        printf("\n%s exceeds length limit 50 characters. Employee profile creation failed. Press enter to continue\n", var_name);
          
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
        
        printf("%s: ", var_name[i]);
          
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
    employee_logo("|     CREATE EMPLOYEE PROFILE     |");
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

void update(char* title_eng, char* input, char* title, int choice, int (*db_edit)(char*, char*, char*, int))
{
    char* edit = calloc(MAX_INPUT_EMP, sizeof(char));
    
    printf("Please enter new %s: ", title_eng);
      
    fgets(edit, MAX_INPUT_EMP, stdin);
    if(input_length_check(edit) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInput exceeds 50 characters limit,edit employee profile failed,press enter to continue\n");
          
        clear_stdin();
        system("cls");
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
    employee_logo("|      Edit EMPLOYEE PROFILE      |");
    char* input = calloc(MAX_INPUT_EMP, sizeof(char));
    
    printf("\nPlease enter the employee name or employee number you wish to edit: ");
      
    fgets(input, MAX_INPUT_EMP, stdin);
    if(input_length_check(input) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInput exceeds 50 characters limit,delete employee profile failed,press enter to continue\n");
          
        
    }
    if(input_length_check(input) == INPUT_EMPTY_ERR)
    {
         
        printf("\nInput empty,delete employee profile failed,press enter to continue\n");
          
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
                    
                    printf("Please enter 1 to 8 from the above options which you would like to edit: ");
                      
                    fgets(choice, sizeof(choice), stdin);
                    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
                    {
                        clear_stdin();
                         
                        printf("\nInvalid choice, please only choose option from 1 to 8, press enter to continue\n");
                          
                        clear_stdin();
                        system("cls");
                        logo();
                        user_menu();
                    }
                    else
                    {
                        switch(atoi(choice))
                        {
                            case 1:
                                update("employee number",input, "emp_no", 1, edit_emp);
                                break;
                            case 2:
                                update("employee name", input, "name", 2, edit_emp);
                                break;
                            case 3:
                                update("date of birth", input, "dob", 3, edit_emp);
                                break;
                            case 4:
                                update("address", input, "address", 4, edit_emp);
                                break;
                            case 5:
                                update("contact number", input, "contact_num", 5, edit_emp);
                                break;
                            case 6:
                                update("position", input, "position", 6, edit_emp);
                                break;
                            case 7:
                                update("department", input, "department", 7,edit_emp);
                                break;
                            case 8:
                                update("salary", input, "salary", 8, edit_emp);
                                break;
                            default:
                                 
                                printf("\nInvalid choice, please only choose option from 1 to 8, press enter to continue\n");
                                  
                                clear_stdin();
                                system("cls");
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
                         
                        printf("\nInvalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue\n");
                          
                        clear_stdin();
                        system("cls");
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
                    system("cls");
                    logo();
                    employee_logo("|      Edit EMPLOYEE PROFILE      |");
                }
                else
                {
                    
                    printf("\nEdit employee profile complete,return to main user interface,press enter to continue\n");
                      
                    break;
                }
            }
            
        }
        else
        {
             
            printf("\nEmployee doesn't exist, press enter to continue\n");
              
        }
    }
    clear_stdin();
    mem_set(1, input);
    free_mem(1, input);
    system("cls");
    logo();
    user_menu();
    return;
}    

void view_employee()
{
    employee_logo("|       VIEW EMPLOYEE PROFILE     |");
    char choice[3];
    
    printf("\n1.View all employee profiles\n");
    printf("2.View single employee profile\n");
    printf("3.Return to main user interface\n");
    printf("\nPlease only choose option 1 to 3: ");
      
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInvalid choice, please only choose option from 1 to 3, press enter to continue\n");
          
        clear_stdin();
        system("cls");
        logo();
        view_employee();
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
        switch(atoi(choice))
        {
            case 1:
                system("cls");
                logo();
                view_all_employee();
                break;
            case 2:
                system("cls");
                logo();
                view_single_employee();
                break;
            case 3:
                user_menu();
                break;
            default:
                 
                printf("\nInvalid choice, please only choose option from 1 to 3, press enter to continue\n");
                  
                clear_stdin();
                system("cls");
                logo();
                view_employee();
                break;
        }
    } 
    return;
}

void view_all_employee()
{   
    employee_logo("|       VIEW EMPLOYEE PROFILE     |");
    char choice[3];
    
    printf("\nDo you wish to view all profiles in CSV file? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no: ");
      
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInvalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue\n");
          
        clear_stdin();
        system("cls");
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
                    
                    printf("\nAll profiles export to CSV successfully,press enter to continue\n");
                      
                }
                if(view_all_emp(var_name, 2) != 0)
                {
                     
                    printf("\nAll profiles export to CSV failed,press enter to continue\n");
                      
                }
                clear_stdin();
                system("cls");
                logo();
                view_employee();
                break;
            case 'N':
            case 'n':
                system("cls");
                logo();
                printf("\n");
                view_all_emp(var_name, 1);
                
                printf("\nPress enter to continue\n");
                  
                clear_stdin();
                system("cls");
                logo();
                view_employee();
                break;
            default:
                 
                printf("\nInvalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue\n");
                  
                clear_stdin();
                system("cls");
                logo();
                view_employee(); 
                break;
       }
    }
    return;
}


void view_single_employee()
{
    employee_logo("|       VIEW EMPLOYEE PROFILE     |");
    char* input = calloc(MAX_INPUT_EMP, sizeof(char));
    
    printf("\nPlease enter the employee name or employee number you wish to view: ");
      
    fgets(input, MAX_INPUT_EMP, stdin);
    if(input_length_check(input) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInput exceeds 50 characters limit,delete employee profile failed,press enter to continue\n");
          
        
    }
    if(input_length_check(input) == INPUT_EMPTY_ERR)
    {
         
        printf("\nInput empty,delete employee profile failed,press enter to continue\n");
          
    }
    if(input_length_check(input) == 0)
    {
        if(check_employee_exist(input) > 0)
        {
            char choice[3];
            
            printf("\nDo you wish to view all profiles in CSV file? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no: ");
              
            fgets(choice, sizeof(choice), stdin);
            if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
            {
                clear_stdin();
                 
                printf("\nInvalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue\n");
                  
            }
            if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
            {
               switch(choice[0])
               {
                    case 'Y':
                    case 'y':
                        if(view_single_emp(var_name, input, 2) == 0)
                        {
                            
                            printf("\nAll profiles export to CSV successfully,press enter to continue\n");
                              
                        }
                        if(view_single_emp(var_name, input, 2) != 0)
                        {
                             
                            printf("\nAll profiles export to CSV failed,press enter to continue\n");
                              
                        }
                        break;
                    case 'N':
                    case 'n':
                        system("cls");
                        logo();
                        printf("\n");
                        view_single_emp(var_name, input, 1);
                        
                        printf("\nPress enter to continue\n");
                          
                        break;
                    default:
                         
                        printf("\nInvalid choice, please answer only 'Y' or 'y' for yes and 'N' or 'n' for no, press enter to continue\n");
                           
                        break;
               }
            }
        }
        else
        {
             
            printf("\nEmployee doesn't exist, press enter to continue\n");
              
        }
    }
    clear_stdin();
    mem_set(1, input);
    free_mem(1, input);
    system("cls");
    logo();
    view_employee();
    return;
}


void delete_employee()
{
    employee_logo("|      DELETE EMPLOYEE PROFILE    |");
    char* input = calloc(MAX_INPUT_EMP, sizeof(char));
    
    printf("\nPlease enter the employee name or employee number you wish to delete: ");
      
    fgets(input, MAX_INPUT_EMP, stdin);
    if(input_length_check(input) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInput exceeds 50 characters limit,delete employee profile failed,press enter to continue\n");
          
        
    }
    if(input_length_check(input) == INPUT_EMPTY_ERR)
    {
         
        printf("\nInput empty,delete employee profile failed,press enter to continue\n");
          
    }
    if(input_length_check(input) == 0)
    {
        if(check_employee_exist(input) > 0)
        {
            int result = delete_emp(input);
            if(result == 0)
            {
                
                printf("\nEmployee deleted successfully,re-direct to main user interface,press enter to continue\n");
                  
            }
        }
        else
        {
             
            printf("\nEmployee doesn't exist, press enter to continue\n");
              
        }
    }

    clear_stdin();
    mem_set(1, input);
    free_mem(1, input);
    user_menu();
}

void user_menu()
{   
    system("cls");
    logo();
    char choice[3];
    
    printf("\nHello, what would you like to do today?\n\nPlease select from the following options:\n\n");
    printf("1.Create new employee profile\n");
    printf("2.Edit employee profile\n");
    printf("3.View employee profile\n");
    printf("4.Delete employee profile\n");
    printf("5.Return to system login interface\n\n");
    printf("Please only choose option 1 to 5: ");
      
    fgets(choice, sizeof(choice), stdin);
    if(input_length_check(choice) == INPUT_EXCEED_LIMIT_ERR)
    {
        clear_stdin();
         
        printf("\nInvalid choice, please only choose option from 1 to 5, press enter to continue\n");
          
        clear_stdin();
        user_menu();
    }
    if(input_length_check(choice) != INPUT_EXCEED_LIMIT_ERR)
    {
        switch(atoi(choice))
        {
            case 1:
                system("cls");
                logo();
                create_employee();
                break;
            case 2:
                system("cls");
                logo();
                edit_employee();
                break;
            case 3:
                system("cls");
                logo();
                view_employee();
                break;
            case 4:
                system("cls");
                logo();
                delete_employee();
                break;
            case 5:
                 
                printf("\nExit login...\n");
                  
                sleep(1);
                system("cls");
                logo();
                login_menu();
                break;
            default:
                 
                printf("\nInvalid choice, please only choose option from 1 to 5, press enter to continue\n");
                  
                clear_stdin();
                user_menu();
                break;
        }
    } 
    return;
}
