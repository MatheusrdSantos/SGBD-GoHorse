typedef struct{
	char** data;
	int n_data;
}Row;

typedef struct{
	char* name;
	char** columns;
	Row* rows;
	int n_rows;
	int n_columns;
	int pk_index;
}Table;

typedef struct{
	char* day;
	char* month;
	char* year;
	int i_day;
	int i_month;
	int i_year;
}Date;