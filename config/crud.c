char* exec_create(char* command){
	// se o comando tem apenas duas palavras
	// executa a criação de um novo banco
	//checar se banco já existe
	if (countWords(command, ' ')==2){
		char* db_name = getWordFromIndex(command, ' ', 2);
		int result = mkdir(concat("storage/", db_name), 0777);
	}else if(strcmp(getWordFromIndex(command, ' ', 2), reserved_words[9]) == 0){
		char* default_db = getDefaultDatabaseName();
		printf("%s\n", default_db);
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
	return "ok";
}

int createTable(char* table_name, char* columns_name_command){
	//getDefaultDatabaseName()
	//deve validar e retornar a string que será escrita como cabeçalho da tabela
	char* tableHeader = getTableHeader(columns_name_command);
	if (strcmp(tableHeader, "error")==0)
	{
		throwError("Erro durante a criação da tabela!");
	}else{
		//createTableFromHeader(tableHeader)
		displayConfirmMessage("Criando tabela...");
	}
}

char* exec_list(char* command, char* default_db){
	if(strcmp(command, "list tables") == 0){
		green();
		printf("Você solicitou listar as tabelas.\n");
		resetColor();

		char** tables = getTablesName(default_db);

		int i = 2;
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
		while(databases[i] != NULL){
			printf("%s\n", databases[i]);
			i++;
		}

	}else{
		red();
		printf("Esse comando não existe, tente 'list tables' ou 'list databases'.\n");
		resetColor();

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