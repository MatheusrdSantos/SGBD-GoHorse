char* getFirstWord(char* command);
int getWordIndex(char* word, char** array);
int countWords(char* command, char separator);
char* getWordFromIndex(char* command, char separator, int index);
char* concat(char *string1, char *string2);
int databaseExist(char* db_name);
#include "utils.c"