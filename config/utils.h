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
char* removeChar(char* old_string, char symbol);
int countColumns(char* columns_name_command);
char* getTableHeader(char* columns_name_command);
int valueIsInVector(char* word, char** array, int size);
char* cropString(char* old_string, int index);
int intVectorToInt(int* numbers, int size);
#include "utils.c"