/*
* Executa comandos para criação de bancos de dados ou tabelas
*/
char* exec_create(char* command){
	// se o comando tem apenas duas palavras
	// executa a criação de um novo banco
	//checa se banco já existe
	if (countWords(command, ' ')==2){
		char* db_name = getWordFromIndex(command, ' ', 2);
		if(databaseExist(db_name)!=-1){
			displayAlertMessage("O banco de dados já existe!");
		}else{
			int result = mkdir(concat("storage/", db_name), 0777);
			//int result = mkdir(concat("storage/", db_name));
		}
	}else if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[9]) == 0){
		// create table
		char* default_db = getDefaultDatabaseName();
		char* table_name = getWordFromIndex(command, ' ', 3);
		if (getWordIndex(getWordFromIndex(command, ' ', 4), reserved_words)==11)
		{
			char* columns_name = getWordFromIndex(command, '(', 2);
			// se elas tem tamanho igual significa que a função acima não encontrou o char
			// '(', ou seja, exixte um erro de sintaxe
			if (strlen(columns_name) == strlen(command))
			{
				red();
				printf("Está faltando um \"(\" após o comando \"columns\"!\n");
				resetColor();
			}else{
				createTable(table_name, columns_name);
			}
		}else{
			//modularizar!
			red();
			printf("Comando inesperado: \"%s\"\n",  getWordFromIndex(command, ' ', 4));
			resetColor();
		}
	}
	// existe a possibilidade de não entrar em nenhum dos ifs acima
	// TODO: criar uma terceira condição para erro
	return "ok";
}
/*
* Auxiliar para criar uma tabela e colocar as colunas
*/
int createTableFromHeader(char* table_header, char* table_name){
	FILE *table;
	char* table_path = concat("storage/", getDefaultDatabaseName());
	table_path = concat(table_path, "/");
	char* table_full_path = concat(table_path, table_name);
	table_full_path = concat(table_full_path, ".csv"); 
	if (table == NULL)
	{
		red();
	    printf("Error opening file!\n");
	    resetColor();
	    return 0;
	}
	table = fopen(table_full_path, "w+");
	fprintf(table, "%s\n", table_header);
	fclose(table);
	return 1;
	
}
/*
* Cria uma tabela utilizando a função "createTableFromHeader" auxiliar
*/
int createTable(char* table_name, char* columns_name_command){
	
	char* tableHeader = getTableHeader(columns_name_command);
	if (strcmp(tableHeader, "error")==0)
	{
		throwError("Erro durante a criação da tabela!");
	}else{
		displayConfirmMessage("Criando tabela...");
		return createTableFromHeader(tableHeader, table_name);
	}
}

/*
* Faz a listagem tanto das tabelas quanto dos bancos de dados
*/
char* exec_list(char* command){
	if(strcmp(command, "list tables") == 0){
		green();
		printf("Você solicitou listar as tabelas.\n");
		resetColor();

		char** tables = getTablesName(getDefaultDatabaseName());

		int i = 0;

		// printa de forma bonita os nomes das tabelas
		// dispayTablesName(tables);

		// isso aqui vai para a função acima
		while(tables[i] != NULL){
			for (int j = 0; j < strlen(tables[i])-4; j++)
			{
				printf("%c", tables[i][j]);
			}
			printf("\n");
			i++;
		}

	}else if(strcmp(command, "list databases") == 0){
		green();
		printf("Você solicitou listar os bancos.\n");
		resetColor();

		char* default_databese_name = getDefaultDatabaseName();
		char** databases = getDatabasesName();
		//não listar se for == default_bd.csv
		int i = 0;

		// printa de forma bonita os nomes dos bancos
		// dispayDatabasesName(databases);
		//printf("fora: %s\n", databases[1]);
		// isso aqui vai para a função acima
		//printf("default_db: %s\n", default_databese_name);
		while(databases[i] != NULL){
			//printf("i: %i\n", i);
			if(strcmp(databases[i], default_databese_name)==0){
				b_green();
				printf("%s*\n", databases[i]);
				//printf("----\n");
				resetColor();
				i++;
			}else{
				printf("%s\n", databases[i]);
				i++;
			}
		}

	}else{
		throwError("Esse comando não existe, tente 'list tables' ou 'list databases'.\n");
	}
}//insert into turmas values (1, 10)

/*
* Seta o banco de dados default, ou seja, onde serão aplicados os comandos
*/
int exec_set(char* command){
	FILE *default_db;
	char* db_name = getWordFromIndex(command, ' ', 2);
	int exist = databaseExist(db_name);
	default_db = fopen("storage/default_db.csv", "w+");
	if (default_db == NULL)
	{
		red();
	    printf("Error opening file!\n");
	    resetColor();
	    return 0;
	}
	fprintf(default_db, "%s", db_name);
	green();
	printf("Banco \"%s\" escolhido com sucesso!\n", db_name);
	resetColor();
	fclose(default_db);
	return 1;

}

/*
* Retorna toda a tabela e seus dados
*/
Table getTableWithData(char* table_name){
	FILE* f_table = NULL;
	f_table = getTableFileRead(getDefaultDatabaseName(), table_name);
	Table table;
	table.name = table_name;
	int n_columns;
	table.columns = split(readLineFromFile(f_table, 0), ',', &n_columns);
	fclose(f_table);
	table.n_columns = n_columns;
	Row* rows = (Row*) malloc(sizeof(Row));
	char* data;
	char* table_header;
	f_table = getTableFileRead(getDefaultDatabaseName(), table_name);
	table_header = readLineFromFile(f_table, 0);
	fclose(f_table);
	int i;
	for(i = 1; data!=NULL; i++)
	{
		int n_columns_row;
		f_table = getTableFileRead(getDefaultDatabaseName(), table_name);
		data = readLineFromFile(f_table, i);
		fclose(f_table);
		if(data!=NULL){
			//printf("%s\n", data);
			Row row;
			row.data = splitData(data, ',', &n_columns_row);
			row.n_data = n_columns_row;
			rows = (Row*) realloc(rows, sizeof(Row)*(i+1));
			rows[i-1] = row;
		}
	}
	table.rows = rows;
	table.n_rows = i-1;
	table.pk_index = findPrimaryKeyIndex(table_header);
	return table; 

}

/*
* Realiza os comandos de busca (select)
*/
int exec_select(char* command){
	//Select table “table_name”
	if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[9])==0){
		// executa um select simples, sem filtros
		if(countWords(command, ' ')==3){
			FILE *selected_table;

			char* default_db = getDefaultDatabaseName();
			char* table_content = (char*) malloc(sizeof(char)*100);

			char* url_1 = concat("storage/", default_db);
			char* url_2 = concat(url_1, "/");

			char* table_name = getWordFromIndex(command, ' ', 3);
			char* url_3 = concat(url_2, table_name);
			char* url_final = concat(url_3, ".csv");
			
			selected_table = fopen(url_final, "rb");

			if (selected_table == NULL)
			{
				throwError("Erro na abertura do arquivo!\n");
				return 0;
			}

			fseek(selected_table, 0, SEEK_END);
			int table_content_string_size = ftell(selected_table);
			fseek(selected_table, 0, SEEK_SET);  //mesmo que rewind(f);
			
			char* table_content_string = (char*) malloc(table_content_string_size + 1);
			fread(table_content_string, table_content_string_size, 1, selected_table);

			table_content_string[table_content_string_size] = '\0';

			int table_content_string_splited_size;
			char** table_content_string_splited = splitData(table_content_string, '\n', &table_content_string_splited_size);
			int table_splited_twice_size, size_largestString = 0;
			for (int i = 0; i < table_content_string_splited_size; i++){
				char** table_splited_twice = splitData(table_content_string_splited[i], ',', &table_splited_twice_size);

				int pos_largestString = getLargestStringInArray(table_splited_twice, table_splited_twice_size);
				int size_largestString_line = strlen(table_splited_twice[pos_largestString]);
				if(size_largestString < size_largestString_line)
					size_largestString = size_largestString_line;
			}
			size_largestString++;
			for (int i = 0; i < table_content_string_splited_size; i++){
				if (i==0){b_blue();}
				else{green();}
				char** table_splited_twice = splitData(table_content_string_splited[i], ',', &table_splited_twice_size);
				int actual_stringSize;
				for (int j = 0; j < table_splited_twice_size; j++)
				{
					actual_stringSize = strlen(table_splited_twice[j]);
					if(i==table_content_string_splited_size-1 && j==table_splited_twice_size-1){
						for (int k = 0; k < actual_stringSize-1; k++)
						{
							printf("%c", table_splited_twice[j][k]);
						}
						printf(" ");
					}else{
						printf("%s", table_splited_twice[j]);
					}
					while(actual_stringSize <= size_largestString){
						printf(" ");
						actual_stringSize++;
					}
					printf("|");	
				}
				printf("\n");
			}
			resetColor();
			fclose(selected_table);
		}else{

			// verifica se tem * após o nome da tabela
			if(strlen(getWordFromIndex(command, ' ', 4)) == 1 && getWordFromIndex(command, ' ', 4)[0] == reserved_symbols[3]){
				//printf("tem o *\n");
				if (strcmp(getWordFromIndex(command, ' ', 5), reserved_words[13])==0) {
					// select table alunos * where (media>5)
					// select table alunos * where (nome%math)
					char* filter = getStringBetweenSymbols(command, '(', ')');
					char* table_name = getWordFromIndex(command, ' ', 3);
					Table table = getTableWithData(table_name);
					int n_pks_to_print = 0;
					//printf("aqui\n");
					int* pks_to_print = applyFilter(&table, filter, &n_pks_to_print);
					printTableWithFilter(table, pks_to_print, n_pks_to_print);
					/*printf("tablename: %s\n", table.name);
					printf("n_columns: %i\n", table.n_columns);
					printf("n_rows: %i\n", table.n_rows);*/

					// getClonsure
					//printf("tem where\n");
				}else{
					printf("falta o where\n");
				}
				
			}else if (strcmp(getWordFromIndex(command, ' ', 4), reserved_words[11])==0) {
				// Select table alunos columns (id, nome) where (media > 5)
				// select table professores columns (id, salaro, nome) where (salario>2000.0)
				//tem especificação de colunas
				// getColumsName
				int left_delimiter = getFirstOcurrencyIndex(command, '(');
				int right_delimiter = getFirstOcurrencyIndex(command, ')');
				char* columns_filter = getStringBetweenIndexes(command, left_delimiter, right_delimiter);
				int left_delimiter_filter = getNOcurrencyIndex(command, '(', 2);
				int right_delimiter_filter = getLastOcurrencyIndex(command, ')');
				char* filter = getStringBetweenIndexes(command, left_delimiter_filter, right_delimiter_filter);
				
				char* table_name = getWordFromIndex(command, ' ', 3);
				printf("%s\n", table_name);
				char** tables_name = getTablesName(getDefaultDatabaseName());
				if(tables_name==NULL){
					throwError("Não existem tabelas no banco!");
					return 1;
				}
				int n = 0;
				while(tables_name[n]!=NULL){
					n++;
				}
				
				if (!valueIsInVector(table_name, tables_name, n-1)) {
					throwError("Tabela não encontrada!");
					return 1;
				}
				

				Table table = getTableWithData(table_name);
				int n_pks_to_print = 0;
				//printf("aqui\n");
				int* pks_to_print = applyFilter(&table, filter, &n_pks_to_print);

				printTableWithFilterColumns(table, pks_to_print, n_pks_to_print, columns_filter);
				
				/*printf("column filter: %s\n", columns_filter);
				printf("filter: %s\n", filter);
				printf("tem declaração de colunas\n");*/
				
			}else{
				// filtro de colunas está faltando
				printf("falta a declaração de colunas\n");
			}

		}
		
		
	}else{
		//modularizar!
		red();
		printf("Comando inesperado: \"%s\"\n",  getWordFromIndex(command, ' ', 2));
		resetColor();
	}
	

	return 1;
}
//insere os dados na tabela
// insert into alunos values (4, "matheus", 9.0, 09/07/1999)
// insert into professores values (1, "jose joao", 2000.0)
// int* id, char[50] nome, float media, date nasc
// int* id, char[60] nome, float salario
// insert into itens values (6, "teste", 9.9, 09/10/2018)
// insert into itens values (3, "teste", 9.9, 09/10/2018)
/*
* Insere tupla na tabela
*/
int insertRow(Row row, char* table_name){
	displayMessage("Escrevendo dados em disco");
	FILE* table = getTableFileAppend(getDefaultDatabaseName(), table_name);
	if(table == NULL){
		throwError("Problema na leitura do arquivo");
		return 0;
	}
	/*printf("data 1: %s\n", row.data[0]);
	printf("data 2: %s\n", row.data[1]);*/

	char* literal_data = concatVectorWithSeparator(row.data, ',', row.n_data);
	fprintf(table, "%s\n", literal_data);
	fclose(table);
	return 1;
}

/*
* Executa os comandos de inserção (insert)
*/
int exec_insert(char* command){
	if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[7])==0){
		char* table_name = getWordFromIndex(command, ' ', 3);
		if (strcmp(getWordFromIndex(command, ' ', 4), reserved_words[15])==0)
		{
			char* values = getValuesFromDeclaration(command);
			int size = 0, result;
			char** data = splitData(values, ',', &size);
			int is_valid = validateValues(table_name, data);
			if(is_valid == 1){	
				Row row;
				row.data = data;
				row.n_data = size;
				result = insertRow(row, table_name);
				exec_select(concat("select table ", table_name));
				return result;
			}else if(is_valid==0){
				throwError("Erro durante a inserção: dados inválidos!");
				return 0;
			}else if (is_valid == -1) {
				throwError("Erro durante a inserção: tabela desconhecida!");
				return 0;
			}
			
			
		}
	}else{
		// melhorar a função para receber strings por parametro
		throwError("Comando into não encontrado");
		return 0;
	}
}

/*
* Deleta tuplas
*/
int deleteRegisters(char* table_name, int* pks_to_delete, int n_pks_to_delete, Table table){
	FILE* f_table = getTableFileReadBinary(getDefaultDatabaseName(), table_name);
	if (f_table == NULL)
	{
		throwError("Erro na abertura do arquivo!\n");
		return 0;
	}

	fseek(f_table, 0, SEEK_END);
	int table_content_string_size = ftell(f_table);
	fseek(f_table, 0, SEEK_SET);  //mesmo que rewind(f);
	
	char* table_content_string = (char*) malloc(table_content_string_size + 1);
	fread(table_content_string, table_content_string_size, 1, f_table);

	table_content_string[table_content_string_size] = '\0';
	//printf("%s\n", table_content_string);
	fclose(f_table);
	int table_content_splited_size;
	char** table_content_splited = splitData(table_content_string, '\n', &table_content_splited_size);
	//printf("n_lines: %i\n", table_content_splited_size);
	
	int* indexes_to_ignore = (int*) malloc(sizeof(int));
	int n_ignored = 0;
	int n_columns;
	for(int i = 1; i < table_content_splited_size; i++)
	{
		
		char** splited_data = splitData(table_content_splited[i], ',', &n_columns);
		int current_pk = stringToInt(splited_data[table.pk_index]);
		
		if (valueIsInIntVector(pks_to_delete, n_pks_to_delete, current_pk)) {
			indexes_to_ignore = (int*) realloc(indexes_to_ignore, sizeof(int)*(n_ignored+1));
			indexes_to_ignore[n_ignored] = i;
			n_ignored++;
		}

	}

	f_table = getTableFileWrite(getDefaultDatabaseName(), table_name);
	if (f_table == NULL)
	{
		throwError("Erro na abertura do arquivo!\n");
		return 0;
	}


	for(int i = 0; i < table_content_splited_size; i++)
	{
		
		if (!valueIsInIntVector(indexes_to_ignore, n_ignored, i)) {
			if(i+1==table_content_splited_size){
				fprintf(f_table, "%s", table_content_splited[i]);
			}else{
				fprintf(f_table, "%s\n", table_content_splited[i]);
			}
		}
		
	}
	
	fclose(f_table);
	return 1;
}

/*
* Executa os comandos de exclusão tanto de tuplas quanto de tabelas
*/
int exec_delete(char* command){
	// delete table professores where (id=3)
	// create table professores columns (int* id, char[30] nome, float salario)
	// insert into professores values (3, "maria", 4000.0)
	// verifica se tem * após o nome da tabela
	
	if (strcmp(getWordFromIndex(command, ' ', 2), reserved_words[9])!=0) {
		throwError("Comando \"table\" não encontrado!");
		return 0;
	}
	if(countWords(command, ' ')==3){
		char* table_name = getWordFromIndex(command, ' ', 3);
		char* db_name = getDefaultDatabaseName();

		int ret_remove_table = removeTable(db_name, table_name);

		if(ret_remove_table == 0){
			displayConfirmMessage("Tabela deletada com sucesso!");
		}else{
			throwError("Não foi possível deletar a tabela.");
		}

		return 0;
		//executar delete de tabela
	}else if(strcmp(getWordFromIndex(command, ' ', 4), reserved_words[13]) == 0){
		//printf("tem o *\n");
		// executa delete de registro
		// select table alunos * where (media>5)
		// select table alunos * where (nome%math)
		//int* id, char[30] nome, float salario
		/*1, "jose", 2000.0
		2, "mario", 3000.0
		3, "maria", 4000.0*/
		char* filter = getStringBetweenSymbols(command, '(', ')');
		char* table_name = getWordFromIndex(command, ' ', 3);
		Table table = getTableWithData(table_name);
		int n_pks_to_delete = 0;
		int* pks_to_delete = applyFilter(&table, filter, &n_pks_to_delete);
		//printTableWithFilter(table, pks_to_delete, n_pks_to_delete);
		deleteRegisters(table_name, pks_to_delete, n_pks_to_delete, table);
		exec_select(concat("select table ", table_name));
		/*printf("tablename: %s\n", table.name);
		printf("n_columns: %i\n", table.n_columns);
		printf("n_rows: %i\n", table.n_rows);*/

		// getClonsure
		//printf("tem where\n");
		
	}
}


