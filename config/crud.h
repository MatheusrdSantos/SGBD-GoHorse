char* exec_list(char* command);
char* exec_create(char* command);
int exec_select(char* command);
int exec_set(char* command);
int createTable(char* table_name, char* columns_name);
int createTableFromHeader(char* table_header, char* table_name);
#include "crud.c"