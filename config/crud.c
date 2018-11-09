char* exec_create(char* command){
	// se o comando tem apenas duas palavras
	// executa a criação de um novo banco
	if (countWords(command, ' ')==2){
		char* db_name = getWordFromIndex(command, ' ', 2);
		int result = mkdir(concat("storage/", db_name), 0777);
	}

	//checar se banco já existe
}
char* exec_list(char* command){
	if(strcmp(command, "list tables") == 0){
		green();
		printf("Você solicitou listar as tabelas.\n");
		resetColor();

		char** tables = getTablesName("db1");

		//printf("%s\n", tables[0]);
		//printf("%s\n", tables[1]);
		printf("%s\n", tables[2]);


	}else if(strcmp(command, "list databases") == 0){
		green();
		printf("Você solicitou listar os bancos.\n");
		resetColor();

		char** databases = getDatabasesName();

		//printf("%s\n", databases[0]);
		//printf("%s\n", databases[1]);
		//printf("%s\n", databases[2]);
		printf("%s\n", databases[3]);

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