#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <dirent.h>
#include <ctype.h>
#include <sys/stat.h>
#include <sys/types.h>

#if defined(_WIN32)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(_WIN64)
    #define PLATFORM_NAME "windows" // Windows
#elif defined(__linux__)
    #define PLATFORM_NAME "linux" // Debian, Ubuntu, Gentoo, Fedora, openSUSE, RedHat, Centos and other
#else
    #define PLATFORM_NAME NULL
#endif

#define RESERVED_WORDS_SIZE 19
#define RESERVED_SYMBOLS_SIZE 5
#define RESERVED_PRIMITIVE_TYPES_SIZE 4
#define RESERVED_FILES_NAME_SIZE 1
// reserved words, symbols and types
char* reserved_words[RESERVED_WORDS_SIZE] = {"help","create", "delete", "select", "set", "list", "insert", "into", "add", "table", "tables", "columns","from", "where", "by", "values", "and", "or", "input"};
char reserved_symbols[RESERVED_SYMBOLS_SIZE] = {'=', '>', '<', '*', '%'};
char* primitive_types[RESERVED_PRIMITIVE_TYPES_SIZE] = {"int", "float", "char", "date"};
char* reserved_files_name[RESERVED_FILES_NAME_SIZE] = {"default_db.csv"};
#include "types.h"
#include "colors.h"
#include "display.h"
#include "utils.h"
#include "crud.h"
#include "validators.h"
