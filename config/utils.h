char* getFirstWord(char* command);
int getWordIndex(char* word, char** array);
int countWords(char* command, char separator);
char* getWordFromIndex(char* command, char separator, int index);
char* concat(char *string1, char *string2);
int databaseExist(char* db_name);
char** getTablesName(char* db_name);
char** getDatabasesName();
char* getDefaultDatabaseName();
int validateColumnDeclaration(char* column_declaration);
char** split(char* text, char separator, int* size);
int myPow(int base, int expoent);
char* removeChar(char* old_string, char symbol);
int countColumns(char* columns_name_command);
char* getTableHeader(char* columns_name_command);
int valueIsInVector(char* word, char** array, int size);
char* cropStringRight(char* old_string, int index);
char* cropStringLeft(char* old_string, int index);
int intVectorToInt(int* numbers, int size);
int isInt(char* declaration_type);
int isChar(char* declaration_type);
int isFloat(char* declaration_type);
int isDate(char* declaration_type);
char* putCharAfterSymbol(char* old_string, char new_char, char symbol);
int countCharInString(char* string_1, char symbol);
int hasPrimaryKey(char* columns_name_command);
char* removeCharFromPosition(char* old_string, int position);
char* getValuesFromDeclaration(char* command);
int getLastOcurrencyIndex(char* string_1, char symbol);
int getFirstOcurrencyIndex(char* string_1, char symbol);
int validateValues(char* table_name, char** data);
char* getStringBetweenSymbols(char* old_string, char symbol_initial, char symbol_final);
char* getTableHeaderFromDatabase(char* db_name, char* table_name);
int valueMatchWithType(char* data, char* type_declaration, char* table_name);
int validateInt(char* data);
int validateChar(char* data, char* type);
int stringToInt(char* data);
int validateDate(char* data);
int isValidYear(int year);
int isValidMonth(int month);
int isValidDay(int day);
FILE* getTableFileRead(char* db_name, char* table_name);
FILE* getTableFileWrite(char* db_name, char* table_name);
char* concatVectorWithSeparator(char** vector, char separator, int size);
int isPrimary(char* declaration_type);
int validateIntPrimary(char* data, char* table_name);
char* readLineFromFile(FILE* table, int index);
int findPrimaryKeyIndex(char* header);
char** splitData(char* row_data, char separator, int* size);
int valueIsInIntVector(int* vecto, int size, int value);
void applyFilter(Table* table, char* filter);
int* getAllIdsFromTable(char* table_name, int* n_numbers);
int validateFilterSyntax(char** splited_filters, int n_filters);
int hasOperator(char* filter);
int isOperator(char symbol);
int filterMatchWithColumn(char* filter, Table table);
char* getColumnNameFromFilter(char* filter, Table table);
int* findOperator(char* filter);
char* getOperatorFromFilter(char* filter);
int operatorMatchWithColumnType(char* operators, char* column_name, Table table);
char* getColumnTypeFromName(Table table, char* column_name);
int isMathOperator(char* operator_d);
int interpretFilter(char* filter);
int execOperations(int* operations_code, int n_operations, Table* table, char** columnsName, int isAnd);
#include "utils.c"