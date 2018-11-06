void run();
char* getCommand();
int validate(char* command);
void execute(char* command);
int isReserverdWord(char* word, char** reserved);
// reserved words
char* reserved_words[RESERVED_WORDS_SIZE] = {"help","create", "delete", "select", "set", "list", "insert", "into", "add", "table", "tables", "from", "where", "by"};
char* reserved_symbols[RESERVED_SYMBOLS_SIZE] = {"=", ">", "<"};
#include "validators.c"