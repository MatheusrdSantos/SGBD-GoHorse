#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#define RESERVED_WORDS_SIZE 15
#define RESERVED_SYMBOLS_SIZE 3
// reserved words
char* reserved_words[RESERVED_WORDS_SIZE] = {"help","create", "delete", "select", "set", "list", "insert", "into", "add", "table", "tables", "columns","from", "where", "by"};
char* reserved_symbols[RESERVED_SYMBOLS_SIZE] = {"=", ">", "<"};
#include "colors.h"
#include "display.h"
#include "utils.h"
#include "crud.h"
#include "validators.h"
