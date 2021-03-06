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
FILE* getTableFileReadBinary(char* db_name, char* table_name);
char* concatVectorWithSeparator(char** vector, char separator, int size);
int isPrimary(char* declaration_type);
int validateIntPrimary(char* data, char* table_name);
char* readLineFromFile(FILE* table, int index);
int findPrimaryKeyIndex(char* header);
char** splitData(char* row_data, char separator, int* size);
int valueIsInIntVector(int* vecto, int size, int value);
int* applyFilter(Table* table, char* filters, int* n_pks_to_print);
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
int* execOperations(int* operations_code, int n_operations, Table* table, char** columnsName, char** filter_values, int isAnd, int* n_pks_to_print);
char* getValueFromFilter(char* filter_declaration,char* c_name);
int* orientateFilterAnd(int operation_code, Table* table, char* column_name, char* filter_value, int* n_pks);
int getColumnIndex(char** columns, char* column_name, int n_columns);
int* applyGreaterThan(Table table, int filter_value, int column_index, int* n_pks);
int* getIntersectionFromIntVector(int** pks, int* n_pks, int* n_result_pks);
int getLargestStringInArray(char** received_array, int size);
void printTableWithFilter(Table table, int* pks_to_print, int n_pks_to_print);
int* applyLessThan(Table table, int filter_value, int column_index, int* n_pks);
int* applyEqualTo(Table table, char* filter_value, int column_index, int* n_pks);
int* applyGreaterEqualTo(Table table, int filter_value, int column_index, int* n_pks);
int* applyLessEqualTo(Table table, int filter_value, int column_index, int* n_pks);
int* applyStringSimilarity(Table table, char* filter_value, int column_index, int* n_pks);
int* getComplementFromIntVector(int** pks, int* n_pks, int* n_result_pks);
int* applyGreaterThanIntFloat(Table table, int filter_value, int column_index, int* n_pks);
int* applyGreaterThanFloatFloat(Table table, float filter_value, int column_index, int* n_pks);
int* applyGreaterThanFloatInt(Table table, float filter_value, int column_index, int* n_pks);
int* applyLessThanIntFloat(Table table, int filter_value, int column_index, int* n_pks);
int* applyLessThanFloatFloat(Table table, float filter_value, int column_index, int* n_pks);
int* applyLessThanFloatInt(Table table, float filter_value, int column_index, int* n_pks);
int* applyGreaterEqualToIntFloat(Table table, int filter_value, int column_index, int* n_pks);
int* applyGreaterEqualToFloatFloat(Table table, float filter_value, int column_index, int* n_pks);
int* applyGreaterEqualToFloatInt(Table table, float filter_value, int column_index, int* n_pks);
int* applyLessEqualToIntFloat(Table table, int filter_value, int column_index, int* n_pks);
int* applyLessEqualToFloatFloat(Table table, float filter_value, int column_index, int* n_pks);
int* applyLessEqualToFloatInt(Table table, float filter_value, int column_index, int* n_pks);
int* applyGreaterThanDate(Table table, Date filter_value, int column_index, int* n_pks);
Date stringToDate(char* text_date);
int compareDateGreater(Date date_1, Date date_2);
int* applyLessThanDate(Table table, Date filter_value, int column_index, int* n_pks);
int* applyEqualToDate(Table table, Date filter_value, int column_index, int* n_pks);
int compareDateEqual(Date date_1, Date date_2);
int* applyLessEqualToDate(Table table, Date filter_value, int column_index, int* n_pks);
int* applyGreaterEqualToDate(Table table, Date filter_value, int column_index, int* n_pks);
char* getStringBetweenIndexes(char* text, int index_1, int index_2);
int getNOcurrencyIndex(char* string_1, char symbol, int n);
void printTableWithFilterColumns(Table table, int* pks_to_print, int n_pks_to_print, char* filter_columns);
int stringIsInVector(char** vector, char* string_1, int v_size);
int exec_delete(char* command);
int removeTable(char* db_name, char* table_name);
void printTable(Table table);
#include "utils.c"