void run();
char* getCommand();
int validate(char* command);
void execute(char* command);
int isReserverdWord(char* word, char** reserved);
int isInt(char* declaration_type);
int isChar(char* declaration_type);
int exec_input_file();
#include "validators.c"