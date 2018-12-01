/*
* Executa comandos para criação de bancos de dados ou tabelas
*/
char* exec_create(char* command){
	// se o comando tem apenas duas palavras
	// executa a criação de um novo banco
	if (countWords(command, ' ')==2){
		char* db_name = getWordFromIndex(command, ' ', 2);
		
		//checa se banco já existe
		if(databaseExist(db_name)!=-1){
			displayAlertMessage("O banco de dados já existe!");
		}else{
			// verifica se o sistema operacional é windows ou linux
			// isso ocorre porque o caractere de diretório é diferente para os dois sistemas
			if (strcmp(PLATFORM_NAME, "windows")==0) {
				//int result = _mkdir(concat("storage/", db_name));
				char* dash = (char*) malloc(sizeof(char));
				dash[0] = 92; // caractere '\'
				char* storage_path = concat("storage", dash);
				//printf("db_name: %s\n", db_name);
				//printf("size: %i\n", (int)strlen(db_name));
				char* command_line = concat("mkdir ", concat(storage_path, db_name)); 
				//printf("comando: %s\n", command_line);
				system(command_line);
			}else if (strcmp(PLATFORM_NAME, "linux")==0) {
				char* command_line = concat("mkdir ", concat("storage/", db_name)); 
				//printf("db_name: %s\n", db_name);
				//printf("size: %i\n", (int)strlen(db_name));
				//printf("char: %c\n", db_name[4]);
				//printf("int: %i\n", (int) db_name[4]);
				//printf("comando: %s\n", command_line);
				system(command_line);
				
			}
			
		}
	// verifica sea segunda palavra é 'table'
	}else if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[9]) == 0){
		// create table
		char* default_db = getDefaultDatabaseName();
		char* table_name = getWordFromIndex(command, ' ', 3);

		// verifica se após o nome da tabela tem o nome columns
		if (getWordIndex(getWordFromIndex(command, ' ', 4), reserved_words)==11)
		{
			char* columns_name = getWordFromIndex(command, '(', 2);
			
			// se elas tem tamanho igual significa que a função acima não encontrou o char
			// '(', ou seja, existe um erro de sintaxe
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
	}else{
		throwError("Não foi encontrada declaração de colunas!");
	}
	return "ok";
}

/*
* Cria a tabela a partir do cabeçalho, do nome e do banco de dados padrão
*/

int createTableFromHeader(char* table_header, char* table_name){
	FILE *table;
	char* table_path = concat("storage/", getDefaultDatabaseName());
	table_path = concat(table_path, "/");
	char* table_full_path = concat(table_path, table_name);
	table_full_path = concat(table_full_path, ".csv"); 
	if (table == NULL)
	{
		throwError("Error opening file!\n");
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

		displayMessage("Você solicitou listar as tabelas.\n");

		char** tables = getTablesName(getDefaultDatabaseName());

		int i = 0;

		while(tables[i] != NULL){
			for (int j = 0; j < strlen(tables[i])-4; j++)
			{
				printf("%c", tables[i][j]);
			}
			printf("\n");
			i++;
		}

	}else if(strcmp(command, "list databases") == 0){
		displayMessage("Você solicitou listar os bancos.\n");

		char* default_databese_name = getDefaultDatabaseName();
		char** databases = getDatabasesName();
		
		int i = 0;

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
}

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
		throwError("Error opening file!\n");
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
* Retorna toda a tabela em forma de Table e seus dados
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

	//insere os dados na estrutura de dados Table
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
			
			char* table_name = getWordFromIndex(command, ' ', 3);	
			Table table = getTableWithData(table_name);
			printTable(table);

		}else{

			// verifica se tem * após o nome da tabela
			if(strlen(getWordFromIndex(command, ' ', 4)) == 1 && getWordFromIndex(command, ' ', 4)[0] == reserved_symbols[3]){
				//printf("tem o *\n");

				// verifica se tem a palavra reservada where
				if (strcmp(getWordFromIndex(command, ' ', 5), reserved_words[13])==0) {
					// select table alunos * where (media>5)
					// select table alunos * where (nome%math)
					//printf("comando: %s\n", command);
					// recupera o filtro
					char* filter = getStringBetweenSymbols(command, '(', ')');
					if(strcmp(filter, "error")==0){
						throwError("Erro de sintaxe. Falta '(' ou ')' na declaração do filtro.");
						return 0;
					}
					char* table_name = getWordFromIndex(command, ' ', 3);
					Table table = getTableWithData(table_name);
					int n_pks_to_print = 0;

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
			// verifica se tem a palavra reservada 'columns'
			}else if (strcmp(getWordFromIndex(command, ' ', 4), reserved_words[11])==0) {
				// Select table alunos columns (id, nome) where (media > 5)
				// select table professores columns (id, salaro, nome) where (salario>2000.0)
				//tem especificação de colunas
				// getColumsName
				
				// recpera o nome das colunas
				int left_delimiter = getFirstOcurrencyIndex(command, '(');
				int right_delimiter = getFirstOcurrencyIndex(command, ')');
				
				// recupera os filtros
				char* columns_filter = getStringBetweenIndexes(command, left_delimiter, right_delimiter);
				int left_delimiter_filter = getNOcurrencyIndex(command, '(', 2);
				int right_delimiter_filter = getLastOcurrencyIndex(command, ')');
				char* filter = getStringBetweenIndexes(command, left_delimiter_filter, right_delimiter_filter);
				
				char* table_name = getWordFromIndex(command, ' ', 3);
				//printf("%s\n", table_name);
				char** tables_name = getTablesName(getDefaultDatabaseName());
				if(tables_name==NULL){
					throwError("Não existem tabelas no banco!");
					return 1;
				}

				// conta o número de tabelas no banco
				int n = 0;
				while(tables_name[n]!=NULL){
					n++;
				}
				//printf("n-> %i\n", n);

				// verifica se a tabela existe no banco
				char* full_name = concat(table_name, ".csv");
				if (!valueIsInVector(full_name, tables_name, n)) {
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

	// verifica se possui a palavra reservada 'into' na segunda posição do comando
	if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[7])==0){
		char* table_name = getWordFromIndex(command, ' ', 3);

		// verifica se tem a palavra reservada 'values'
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
* Deleta linhas a partir de um vetor de primary keys
*/
int deleteRegisters(char* table_name, int* pks_to_delete, int n_pks_to_delete, Table table){
	FILE* f_table = getTableFileReadBinary(getDefaultDatabaseName(), table_name);
	if (f_table == NULL)
	{
		throwError("Erro na abertura do arquivo!\n");
		return 0;
	}

	// recupera o contrúdo do arquivo e conta quantos caracteres tem nele
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
	
	// recupera os indexes para serem ignorados com base nas primary keys passadas
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


	// reescreve a linhas remanescentes na tabelas
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
* Executa os comandos de exclusão tanto de linhas quanto de tabelas
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
	//executa delete de linhas
	// verifica se na posição 4 tem a palavra reservada 'where'
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
		
		if (strcmp(filter, "error")==0) {
			throwError("Erro na sintaxe. Não foi encontrado '(' ou ')' no comando.");
			return 0;
		}
		
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
		
	}
}


