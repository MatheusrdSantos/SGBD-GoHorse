#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>
#define RESERVED_WORDS_SIZE 16
#define RESERVED_SYMBOLS_SIZE 4
#define RESERVED_PRIMITIVE_TYPES_SIZE 4
// reserved words, symbols and types
char* reserved_words[RESERVED_WORDS_SIZE] = {"help","create", "delete", "select", "set", "list", "insert", "into", "add", "table", "tables", "columns","from", "where", "by", "values"};
char reserved_symbols[RESERVED_SYMBOLS_SIZE] = {'=', '>', '<', '*'};
char* primitive_types[RESERVED_PRIMITIVE_TYPES_SIZE] = {"int", "float", "char", "date"};
#include "colors.h"
#include "display.h"
#include "utils.h"
#include "crud.h"
#include "validators.h"
