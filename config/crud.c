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
	fprintf(table, "%s", table_header);
	fclose(table);
	return 1;
	
}
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

// mudar o tipo de retorno para inteiro
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

		char** databases = getDatabasesName();
		//não listar se for == default_bd.csv
		int i = 3;

		// printa de forma bonita os nomes dos bancos
		// dispayDatabasesName(databases);

		// isso aqui vai para a função acima
		while(databases[i] != NULL){
			printf("%s\n", databases[i]);
			i++;
		}

	}else{
		throwError("Esse comando não existe, tente 'list tables' ou 'list databases'.\n");
	}
}

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

int exec_select(char* command){
	//Select table “table_name”
	FILE *selected_table;

	char* default_db = getDefaultDatabaseName();
	char* second_word = getWordFromIndex(command, ' ', 2);
	char* table_content = (char*) malloc(sizeof(char)*100);

	char* url_1 = concat("storage/", default_db);
	char* url_2 = concat(url_1, "/");

	if(strcmp(second_word, reserved_words[9]) == 0){
		char* table_name = getWordFromIndex(command, ' ', 3);
		char* url_3 = concat(url_2, table_name);
		char* url_final = concat(url_3, ".csv");
		
		selected_table = fopen(url_final, "rb");

		if (selected_table == NULL)
		{
			red();
		    printf("Error opening file!\n");
		    resetColor();
		    return 0;
		}

		fseek(selected_table, 0, SEEK_END);
		int fsize = ftell(selected_table);
		fseek(selected_table, 0, SEEK_SET);  //same as rewind(f);
		
		char *string = (char*) malloc(fsize + 1);
		fread(string, fsize, 1, selected_table);

		string[fsize] = '\0';

		green();
		printf("%s\n", string);
		resetColor();
		fclose(selected_table);
	}

	return 1;
}
//insere os dados na tabela
int insertRow(Row row){
	
	for(int i = 0; i < row.n_data; i++)
	{
		//printf("%s\n", row.data[i]);
	}
}

int exec_insert(char* command){
	if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[7])==0){
		char* table_name = getWordFromIndex(command, ' ', 3);
		if (strcmp(getWordFromIndex(command, ' ', 4), reserved_words[15])==0)
		{
			char* values = getValuesFromDeclaration(command);
			int size = 0, result;
			char** data = split(values, ',', &size);
			if(validateValues(table_name, data)){	
				Row row;
				row.data = data;
				row.n_data = size;
				result =  insertRow(row);
			}
			
		}
	}else{
		// melhorar a função para receber strings por parametro
		throwError("Comando into não encontrado");
		return 0;
	}
}