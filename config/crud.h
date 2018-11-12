char* exec_list(char* command, char* default_db);
char* exec_create(char* command);
int exec_set(char* command);
int createTable(char* table_name, char* columns_name);
#include "crud.c"