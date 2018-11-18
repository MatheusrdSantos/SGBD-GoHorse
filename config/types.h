typedef struct{
	char** data;
	int n_data;
}Row;

typedef struct{
	char* name;
	char**columns;
	Row* rows;
	int n_rows;
	int n_columns;
}Table;

typedef struct{
	char* day;
	char* month;
	char* year;
}Date;