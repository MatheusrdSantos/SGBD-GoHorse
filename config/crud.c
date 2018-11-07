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

		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir ("storage/db1/")) != NULL) {
		//printa todos os arquivos e pastas dentro do diretório
			while ((ent = readdir (dir)) != NULL) {
				printf ("%s\n", ent->d_name);
			}
			closedir (dir);
		} else {
		  	perror ("Não há tabelas criadas.");
		  	return 0;
		}

	}else if(strcmp(command, "list databases") == 0){
		green();
		printf("Você solicitou listar os bancos.\n");
		resetColor();

		// colocar dentro de uma função no utils.h: getDatabasesName()
		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir ("storage/")) != NULL) {
		//printa todos os arquivos e pastas dentro do diretório
			while ((ent = readdir (dir)) != NULL) {
				printf ("%s\n", ent->d_name);
			}
			closedir (dir);
		} else {
	  		perror ("Não há databases criados.");
	  		return 0;
		}
		// fim

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