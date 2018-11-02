void run();
char* getCommand();
int validate(char* command);
void execute(char* command);
// reserved words
char* reserved[17] = {"help","create", "delete", "select", "set", "list", "insert", "into", "add", "table", "tables", "from", "where", "by", "=", ">", "<"};
#include "validators.c"