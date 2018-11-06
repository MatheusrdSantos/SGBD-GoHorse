typedef struct{
	char** data;
}Row;

typedef struct{
	char* name;
	char**columns
	Row* rows;
}Table;

typedef struct{
	char* day;
	char* month;
	char* year;
}Date;