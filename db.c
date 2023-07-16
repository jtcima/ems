#include "Ems.h"

void close_db()
{
    sqlite3_close(db);
    printf("\033[1;33m");
    printf("关闭数据库(Database connection closed)\n");
    printf("\033[0m");
    return;
}

void connect_db()
{    
    rc = sqlite3_open("ems.db", &db);
    printf("\033[1;33m");
    printf("正在连接数据库(Connecting to database)...\n");
    printf("\033[0m");
    //sleep(2);

    if (rc != SQLITE_OK)
    {
        printf("\033[1;31m");
        fprintf(stderr, "连接数据库错误(Error connecting to Database: %s)\n", sqlite3_errmsg(db));
        printf("\033[0m");
    }
    if (rc == SQLITE_OK)
    {
        printf("\033[1;32m");
        printf("数据库连接成功(Database Connection Successful)\n");
        printf("\033[0m");
    }
    return;
}

void create_table()
{
    printf("\033[1;33m");
    printf("创建数据表(Creating Table)...\n");
    printf("\033[0m");
    //sleep(2);
    const char* createTableSQL1 = "CREATE TABLE IF NOT EXISTS Users (id INTEGER PRIMARY KEY, name TEXT , password TEXT);";
    const char* createTableSQL2 = "CREATE TABLE IF NOT EXISTS Employee (id INTEGER PRIMARY KEY, emp_no TEXT,name TEXT ,dob TEXT,address TEXT, contact_num TEXT, position TEXT,department TEXT,salary TEXT);";
    rc = sqlite3_exec(db, createTableSQL1, 0, 0, NULL);
    if(rc != SQLITE_OK)
    {
        printf("\033[1;31m");
        fprintf(stderr, "数据库错误(SQL error: %s)\n", sqlite3_errmsg(db));
        printf("\033[0m");
    }

    rc = sqlite3_exec(db, createTableSQL2, 0, 0, NULL);
    if(rc != SQLITE_OK)
    {
        printf("\033[1;31m");
        fprintf(stderr, "数据库错误(SQL error: %s)\n", sqlite3_errmsg(db));
        printf("\033[0m");
    }
    if(rc == SQLITE_OK)
    {
        printf("\033[1;32m");
        printf("数据表创建成功(Table created successfully)\n");
        printf("\033[0m");
    } 
    return;   
}

void add_user(char* name, char* pass)
{
    const char* insertDataSQL = "INSERT INTO Users (name, password) VALUES (?, ?);";
    rc = sqlite3_prepare_v2(db, insertDataSQL, -1, &stmt, NULL);
    if(rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Prepare statement failed: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
    }
    rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if(rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Binding name parameter failed: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
    }
    rc = sqlite3_bind_text(stmt, 2, pass, -1, SQLITE_STATIC);
    if(rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Binding password parameter failed: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
    }
    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Execution failed: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
    } 
    if(rc == SQLITE_DONE)
    {
        printf("\033[1;32m");
        printf("\n用户创建成功,转至用户登录界面,按回车键继续(User created successfully,re-direct to user log in interface,press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
    }
    sqlite3_finalize(stmt);
    return;
}

int delete_user(char* username)
{
    char* sql = "DELETE FROM Users WHERE name = ?;";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    sqlite3_bind_text(stmt, 1, username, -1, SQLITE_STATIC);
    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    sqlite3_finalize(stmt);

    return 0;
}


int delete_emp(char* input)
{
    char* sql = "DELETE FROM Employee WHERE (name = ?) or (emp_no = ?);";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to prepare statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    rc = sqlite3_bind_text(stmt, 1, input, -1, SQLITE_STATIC);
    if(rc != SQLITE_OK)
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to bind parameter 1: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    rc = sqlite3_bind_text(stmt, 2, input, -1, SQLITE_STATIC);
    if(rc != SQLITE_OK)
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to bind parameter 2: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    rc = sqlite3_step(stmt);
    if (rc != SQLITE_DONE) {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to execute statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    sqlite3_finalize(stmt);

    return 0;
}


void add_employee(char** employee_arry, char** var_name, int size)
{
    const char* insertDataSQL = "INSERT INTO Employee (emp_no,name,dob,address, contact_num, position,department,salary) VALUES (?,?,?,?,?,?,?,?);";
    rc = sqlite3_prepare_v2(db, insertDataSQL, -1, &stmt, NULL);
    if(rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Prepare statement failed: %s. Press enter to continue.\n", sqlite3_errmsg(db));
        printf("\033[0m");
        clear_stdin();
    }
    
    for(int i = 0; i < size; i++)
    {
        rc = sqlite3_bind_text(stmt, i+1, employee_arry[i], -1, SQLITE_STATIC);
        
        if(rc != SQLITE_OK) 
        {
            printf("\033[1;31m");
            fprintf(stderr, "Binding %s parameter failed: %s. Press enter to continue.\n", var_name[i], sqlite3_errmsg(db));
            printf("\033[0m");
            clear_stdin();
        }
    }

    rc = sqlite3_step(stmt);
    if(rc != SQLITE_DONE) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Execution failed: %s. Press enter to continue.\n", sqlite3_errmsg(db));
        printf("\033[0m");
        clear_stdin();
    } 
    if(rc == SQLITE_DONE)
    {
        printf("\033[1;32m");
        printf("\n员工创建成功,转至用户主界面,按回车键继续(Employee created successfully,re-direct to main user interface,press enter to continue)\n");
        printf("\033[0m");
        clear_stdin();
        user_menu();
    }
    sqlite3_finalize(stmt);
    return;
}

int check_employee_exist(char* input)
{
    const char* sql = "SELECT COUNT(*) FROM Employee WHERE (name = ?) or (emp_no = ?)";
    int result;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot prepare SQL statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }
    rc = sqlite3_bind_text(stmt, 1, input, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot bind parameter: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        sqlite3_finalize(stmt);
        return SQL_ERR;
    }

    rc = sqlite3_bind_text(stmt, 2, input, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot bind parameter: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        sqlite3_finalize(stmt);
        return SQL_ERR;
    }
    
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ROW)
    {
        result = sqlite3_column_int(stmt, 0);
    }
    else if(rc != SQLITE_DONE)
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot execute query: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;  
    }
    
    sqlite3_finalize(stmt);
    return result;
}

int check_username_exist(char* name)
{
    const char* sql = "SELECT COUNT(*) FROM Users WHERE name = ?";
    int result;
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot prepare SQL statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }
    rc = sqlite3_bind_text(stmt, 1, name, -1, SQLITE_STATIC);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot bind parameter: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        sqlite3_finalize(stmt);
        return SQL_ERR;
    }
    rc = sqlite3_step(stmt);
    if(rc == SQLITE_ROW)
    {
        result = sqlite3_column_int(stmt, 0);
    }
    else if(rc != SQLITE_DONE)
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot execute query: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;  
    }
    
    sqlite3_finalize(stmt);
    return result;
}

int check_user_login(char* name, char* pass)
{
    const char* sql = "SELECT name, password FROM Users";
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Cannot prepare SQL statement: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    int foundUser = 0;

    while((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        if((strcmp(name,(char*)sqlite3_column_text(stmt, 0)) == 0))
        {
            foundUser = 1;

            if((strcmp(pass,(char*)sqlite3_column_text(stmt, 1))) == 0)
            {
                sqlite3_finalize(stmt);
                return 0;
            }
            if((strcmp(pass,(char*)sqlite3_column_text(stmt, 1))) != 0)
            {
                sqlite3_finalize(stmt);
                return USERNAME_PASS_LOGIN_ERR;
            }    
        }
    }

    sqlite3_finalize(stmt);

    if(!foundUser)
    {
        return USER_NOT_FOUND_ERR;
    }
    
    return 0;
}

int view_all_emp(char** emp_profile_cat, int choice)
{
    const char* query = "SELECT * FROM Employee";

    rc = sqlite3_prepare_v2(db, query, -1, &stmt, 0);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }

    if(choice == 1)
    {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int numColumns = sqlite3_column_count(stmt);

            for(int i = 1; i < numColumns; i++)
            {
                const unsigned char* data = sqlite3_column_text(stmt, i);

                printf("\033[1;32m");
                printf("%s: %s", emp_profile_cat[i-1], data);
                printf("\033[0m");
            }

            printf("\n");
        }
    }

    if(choice == 2)
    {
        FILE* csvFile = fopen("employee_profiles.csv", "w");
        if(csvFile == NULL)
        {
            return CSV_ERR;
        }
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int numColumns = sqlite3_column_count(stmt);

            for(int i = 1; i < numColumns; i++)
            {
                const unsigned char* data = sqlite3_column_text(stmt, i);

                printf("\033[1;32m");
                fprintf(csvFile, "%s: %s", emp_profile_cat[i-1], data);
                printf("\033[0m");
            }

            fprintf(csvFile, "\n");
        }
        fclose(csvFile);
    }
    
    sqlite3_finalize(stmt);
    return 0;    
}

int view_single_emp(char** emp_profile_cat, char* input, int choice)
{
    char sql[100];
    sprintf(sql, "SELECT * FROM Employee WHERE emp_no = '%s' OR name = '%s'", input, input);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }
    if(choice == 1)
    {
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int numColumns = sqlite3_column_count(stmt);

            for(int i = 1; i < numColumns; i++)
            {
                const unsigned char* data = sqlite3_column_text(stmt, i);

                printf("\033[1;32m");
                printf("%s: %s", emp_profile_cat[i-1], data);
                printf("\033[0m");
            }

            printf("\n");
        }
    }

    if(choice == 2)
    {
        FILE* csvFile = fopen("employee_profile.csv", "w");
        if(csvFile == NULL)
        {
            return CSV_ERR;
        }
        while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
        {
            int numColumns = sqlite3_column_count(stmt);

            for(int i = 1; i < numColumns; i++)
            {
                const unsigned char* data = sqlite3_column_text(stmt, i);

                printf("\033[1;32m");
                fprintf(csvFile, "%s: %s", emp_profile_cat[i-1], data);
                printf("\033[0m");
            }

            fprintf(csvFile, "\n");
        }
        fclose(csvFile);
    }
    
    sqlite3_finalize(stmt);
    return 0;    
}

int edit_emp_option_menu(char** emp_profile_cat, char* input)
{
    char sql[100];
    sprintf(sql, "SELECT * FROM Employee WHERE emp_no = '%s' OR name = '%s'", input, input);
    rc = sqlite3_prepare_v2(db, sql, -1, &stmt, NULL);
    if (rc != SQLITE_OK) 
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }
   
    while ((rc = sqlite3_step(stmt)) == SQLITE_ROW)
    {
        int numColumns = sqlite3_column_count(stmt);
        for(int i = 1; i < numColumns; i++)
        {
            const unsigned char* data = sqlite3_column_text(stmt, i);
            printf("\033[1;32m");
            printf("%d.%s: %s", i, emp_profile_cat[i-1], data);
            printf("\033[0m");
        }
        printf("\n");
    }
    sqlite3_finalize(stmt);
    return 0; 
}

int edit_emp(char* input, char* input2, char* title, int choice)
{
    char sql[100];
    char* errMsg = 0;
    sprintf(sql, "UPDATE Employee SET '%s' = '%s' WHERE name = '%s' or emp_no = '%s'",title, input2, input, input);
    rc = sqlite3_exec(db, sql, 0, 0, &errMsg);
    if(rc != SQLITE_OK)
    {
        printf("\033[1;31m");
        fprintf(stderr, "Failed to execute query: %s\n", sqlite3_errmsg(db));
        printf("\033[0m");
        return SQL_ERR;
    }
    else
    {
        switch(choice)
        {
            case 1:
                printf("\033[1;32m");
                printf("\n工号更改成功(Employee number Updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 2:
                printf("\033[1;32m");
                printf("\n姓名更改成功(Name Updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 3:
                printf("\033[1;32m");
                printf("\n生日更改成功(Date of birth Updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 4:
                printf("\033[1;32m");
                printf("\n地址更改成功(Address Updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 5:
                printf("\033[1;32m");
                printf("\n联系电话更改成功(Contact number Updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 6:
                printf("\033[1;32m");
                printf("\n职位更改成功(Position updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 7:
                printf("\033[1;32m");
                printf("\n部门更新成功(Department updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            case 8:
                printf("\033[1;32m");
                printf("\n薪水更改成功(Salary updated Successfully)\n");
                printf("继续编辑当前员工?请输入'Y'或'y'代表是,'N'或者'n'代表不是(Continue editing current profile? Please answer only 'Y' or 'y' for yes and 'N' or 'n' for no): ");
                printf("\033[0m");
                break;
            default:
                printf("\033[1;5;31m");
                printf("\n员工档案更改失败,按回车键继续(Edit employee profile failed,press enter to continue)\n");
                printf("\033[0m");
                break;
        }
    }
    return 0;
}


