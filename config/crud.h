char* exec_list(char* command);
char* exec_create(char* command);
int exec_select(char* command);
int exec_set(char* command);
int exec_insert(char* command);
int createTable(char* table_name, char* columns_name);
int createTableFromHeader(char* table_header, char* table_name);
int insertRow(Row row, char* table_name);
Table getTableWithData(char* table_name);
int exec_delete(char* command);
int deleteRegisters(char* table_name, int* pks_to_delete, int n_pks_to_delete, Table table);
#include "crud.c"