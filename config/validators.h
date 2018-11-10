void run();
char* getCommand();
int validate(char* command);
void execute(char* command);
int isReserverdWord(char* word, char** reserved);

#include "validators.c"