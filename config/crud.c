/*
* função:  executa comandos para criação de bancos de dados ou tabelas
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
*/
int exec_create(char* command){
	// se o comando tem apenas duas palavras
	// executa a criação de um novo banco
	if (countWords(command, ' ')==2){
		char* db_name = getWordFromIndex(command, ' ', 2);
		
		//checa se banco já existe
		if(databaseExist(db_name)!=-1){
			displayAlertMessage("O banco de dados já existe!");
			return 0;
		}else{
			// verifica se o sistema operacional é windows ou linux
			// isso ocorre porque o caractere de diretório é diferente para os dois sistemas
			if (strcmp(PLATFORM_NAME, "windows")==0) {
				
				char* dash = (char*) malloc(sizeof(char));
				dash[0] = 92; // caractere '\'
				char* storage_path = concat("storage", dash);
				char* command_line = concat("mkdir ", concat(storage_path, db_name)); 
				system(command_line);
			}else if (strcmp(PLATFORM_NAME, "linux")==0) {
				char* command_line = concat("mkdir ", concat("storage/", db_name)); 
				system(command_line);
				
			}
			
		}
		return 1;
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
				return 0;
			}else{
				createTable(table_name, columns_name);
				return 1;
			}
		}else{
			//modularizar!
			red();
			printf("Comando inesperado: \"%s\"\n",  getWordFromIndex(command, ' ', 4));
			resetColor();
			return 0;
		}
	}else{
		throwError("Não foi encontrada declaração de colunas!");
		return 0;
	}
	return 1;
}


/*
* função:  cria a tabela a partir do cabeçalho, do nome e do banco de dados padrão
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
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
* função:  cria uma tabela utilizando a função "createTableFromHeader" auxiliar
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
*/
int createTable(char* table_name, char* columns_name_command){
	
	char* tableHeader = getTableHeader(columns_name_command);
	if (strcmp(tableHeader, "error")==0)
	{
		throwError("Erro durante a criação da tabela!");
		return 0;
	}else{
		displayConfirmMessage("Criando tabela...");
		return createTableFromHeader(tableHeader, table_name);
	}
}

/*
* função:  faz a listagem tanto das tabelas quanto dos bancos de dados
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
*/
int exec_list(char* command){
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
		return 1;
	}else if(strcmp(command, "list databases") == 0){
		displayMessage("Você solicitou listar os bancos.\n");

		char* default_databese_name = getDefaultDatabaseName();
		char** databases = getDatabasesName();
		
		int i = 0;

		while(databases[i] != NULL){
			if(strcmp(databases[i], default_databese_name)==0){
				b_green();
				printf("%s*\n", databases[i]);
				resetColor();
				i++;
			}else{
				printf("%s\n", databases[i]);
				i++;
			}
		}
		return 1;
	}else{
		throwError("Esse comando não existe, tente 'list tables' ou 'list databases'.\n");
		return 0;
	}
}

/*
* função: seleciona o banco de dados padrão, ou seja, onde serão aplicados os comandos
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
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
* função: recupera todos os dados da tabela
* retorno: struct Table preenchida com seus dados
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
* função: realiza os comandos de busca
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
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

				// verifica se tem a palavra reservada where
				if (strcmp(getWordFromIndex(command, ' ', 5), reserved_words[13])==0) {

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
				}else{
					printf("falta o where\n");
				}
			// verifica se tem a palavra reservada 'columns'
			}else if (strcmp(getWordFromIndex(command, ' ', 4), reserved_words[11])==0) {
				//tem especificação de colunas	
				// recpera o nome das colunas
				int left_delimiter = getFirstOcurrencyIndex(command, '(');
				int right_delimiter = getFirstOcurrencyIndex(command, ')');
				
				// recupera os filtros
				char* columns_filter = getStringBetweenIndexes(command, left_delimiter, right_delimiter);
				int left_delimiter_filter = getNOcurrencyIndex(command, '(', 2);
				int right_delimiter_filter = getLastOcurrencyIndex(command, ')');
				char* filter = getStringBetweenIndexes(command, left_delimiter_filter, right_delimiter_filter);
				
				char* table_name = getWordFromIndex(command, ' ', 3);
				
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
				

				// verifica se a tabela existe no banco
				char* full_name = concat(table_name, ".csv");
				if (!valueIsInVector(full_name, tables_name, n)) {
					throwError("Tabela não encontrada!");
					return 1;
				}
				

				Table table = getTableWithData(table_name);
				int n_pks_to_print = 0;
				
				int* pks_to_print = applyFilter(&table, filter, &n_pks_to_print);

				printTableWithFilterColumns(table, pks_to_print, n_pks_to_print, columns_filter);
				
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

/*
* função: escreve registro na tabela
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
*/

int insertRow(Row row, char* table_name){
	displayMessage("Escrevendo dados no arquivo...");
	FILE* table = getTableFileAppend(getDefaultDatabaseName(), table_name);

	if(table == NULL){
		throwError("Problema na leitura do arquivo");
		return 0;
	}

	char* literal_data = concatVectorWithSeparator(row.data, ',', row.n_data);
	fprintf(table, "%s\n", literal_data);
	fclose(table);
	return 1;
}


/*
* função: executa os comandos de inserção (insert)
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
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
* função: deleta registros na tabela apartir de um vetor de primery keys
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
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
	
	fclose(f_table);

	int table_content_splited_size;
	char** table_content_splited = splitData(table_content_string, '\n', &table_content_splited_size);
	
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
* função: executa os comandos de exclusão tanto de linhas quanto de tabelas
* retorno: status do processo (1 = sem erros, 0 = ocorreram erros)
*/
int exec_delete(char* command){

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
		// executa delete de registro
		char* filter = getStringBetweenSymbols(command, '(', ')');
		
		if (strcmp(filter, "error")==0) {
			throwError("Erro na sintaxe. Não foi encontrado '(' ou ')' no comando.");
			return 0;
		}
		
		char* table_name = getWordFromIndex(command, ' ', 3);
		Table table = getTableWithData(table_name);
		int n_pks_to_delete = 0;
		int* pks_to_delete = applyFilter(&table, filter, &n_pks_to_delete);
		deleteRegisters(table_name, pks_to_delete, n_pks_to_delete, table);
		exec_select(concat("select table ", table_name));
	}
}


