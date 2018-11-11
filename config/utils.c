/*
* Retorna a palavra no index especificado
* EX: getWordFromIndex("matheus ricardo dos santos", ' ', 2) = "ricardo"
* Se não exeistir o index retorna o comando
*/
char* getWordFromIndex(char* command, char separator, int index){
	int cont = 1;
	int size = strlen(command);
	char* word = (char*) malloc(sizeof(char));
	for (int i = 1; i < size; ++i)
	{
		if (cont == index)
		{
			int cont_word = 0;
			while(command[i]!=separator && command[i]!='\0'){
				word[cont_word] = command[i];
				i++;
				word = realloc(word, sizeof(char)*(cont_word+2));
				cont_word++;
			}
			word[cont_word] = '\0';
			return word;

		}
		// se o char na posicao i for igual ao separador
		// e o separador não está na ultima posição
		if (command[i]==separator && i!=size-1)
		{
			cont++;
		}
	}

	return command;
}

/*
* Conta o número de palavras em uma string de acordo com
* um separador.
*/
int countWords(char* command, char separator){
	int cont = 1;
	int size = strlen(command);
	for (int i = 1; i < size; ++i)
	{
		// se o char na posicao i for igual ao separador
		// e o separador não está na ultima posição
		if (command[i]==separator && i!=size-1)
		{
			cont++;
		}
	}

	return cont;
}
char* getFirstWord(char* command){
	char* firstWord =(char*) malloc(sizeof(char));
	int i = 0;
	while(command[i]!=' ' && command[i]!='\0'){
		firstWord[i] = command[i];
		i++;
		firstWord = realloc(firstWord, sizeof(char)*(i+1));
	}
	firstWord[i] = '\0';
	return firstWord;
}

int getWordIndex(char* word, char** array){
	for (int i = 0; i < RESERVED_WORDS_SIZE; ++i)
	{
		if (strcmp(word, array[i])==0)
		{
			return i;
		}
	}
	return -1;
}

char* concat(char *string1, char *string2){
    char *result = malloc(strlen(string1) + strlen(string2) + sizeof(char)); 
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

// verifica se o db_name é o nome de um banco existente
int databaseExist(char* db_name){
	//getDatabasesName()
	// verifica se db_name está dentro do vetor de string
	// retorna 1 em caso positivo e 0 em caso negativo
}

char** getTablesName(char* db_name){
	char** tables = malloc(sizeof(char*));
	int i = 0;

	char* firstparturl = concat("storage/", db_name);
	char* finalurl = concat(firstparturl, "/");

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(finalurl)) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			tables[i] = malloc(strlen(ent->d_name) * sizeof(char)); 
			tables[i] = ent->d_name;
			i++;
			tables = realloc(tables, sizeof(char*)*(i+1));
		}

		tables[i] = NULL;

		return tables;

		for (int j = 0; j <= i; j++)
		{
			free(tables[j]);
		}
		free(tables);

		closedir (dir);
	} else {
	  	perror ("Não há tabelas criadas.");
	  	return 0;
	}
}

char** getDatabasesName(){
	char** databases = malloc(sizeof(char*));
	int i = 0;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("storage/")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			databases[i] = malloc(strlen(ent->d_name) * sizeof(char)); 
			databases[i] = ent->d_name;
			i++;
			databases = realloc(databases, sizeof(char*)*(i+1));
		}

		databases[i] = NULL;

		return databases;

		for (int j = 0; j <= i; j++)
		{
			free(databases[j]);
		}
		free(databases);

		closedir (dir);
	} else {
	  	perror ("Não há bancos criados.");
	  	return 0;
	}
}

char* getDefaultDatabaseName(){
	FILE *default_db;
	char* db_name;
	default_db = fopen("storage/default_db.csv", "r");
	if (default_db == NULL)
	{
		red();
	    printf("Error opening file!\n");
	    resetColor();
	    return 0;
	}
	fscanf(default_db, "%s", db_name);
	fclose(default_db);
	return db_name;
}

/*
* remove todos os caracteres encontrado na string
*/
char* removeChar(char* old_string, char symbol){
	char* new_string = malloc(sizeof(char));
	int size = strlen(old_string);
	for (int i = 0; i < size; ++i)
	{
		if (old_string[i]==symbol)
		{
			continue;  		
	 	}
	 	new_string = realloc(new_string, sizeof(char)*(i+1));
	 	new_string[i] = old_string[i];
		if (i==size-1)
		{
			new_string = realloc(new_string, sizeof(char)*(i+2));
			new_string[i+1] = '\0';
		}
	}
	return new_string;
}
char** split(char* text, char separator, int* size){
	char** strings;
	int last_step = 0; 
	int cont = 0;
	for (int i = 0; i < strlen(text); ++i)
	{
		if ((text[i]==separator && i!=0) || text[i] == '\0')
		{
			strings = malloc(sizeof(char*)*(cont+1));
			for (int j = last_step, k = 0; j < i; ++j, ++k)
			{
				if (k==0)
				{
					strings[cont] = malloc(sizeof(char)*(k+2));
					strings[cont][k] = text[j];
				}else{
					strings[cont] = realloc(strings[cont], sizeof(char)*(k+2));
					strings[cont][k] = text[j];
				}
			}
			strings[cont] = '\0';
			last_step = i+1;
			cont++;
		}
	}
	*size = cont+1;
	return strings;
}
int countColumns(char* columns_name_command){
	// validar a sintaxe
	// e formatar a srting para um formato divisivel por ','
	int size=0;
	split(columns_name_command,',', &size);
	printf("%i\n", size);
	return 1;
}
char* getTableHeader(char* columns_name_command){
	// int *id, varchar[255] name, float height, date birthday)
	char* column_name = malloc(sizeof(char));
	if (columns_name_command[strlen(columns_name_command)-1]!=')')
	{
		printf("sintaxe error\n");
		return "error";
	}else{

		/*
		* TODO: termina esse fluxo.
		*/
		// remover o último ')'
		removeChar(columns_name_command, ')');
		
		int n_columns = 0;
		n_columns = countColumns(columns_name_command);
		for (int i = 1; i <= n_columns; ++i)
		{
			char* column_declaration = getWordFromIndex(columns_name_command, ',', i);
			// valida a declaração da coluna
			// ex: int* id -> correto
			// ex: sharr[10] nome -> errado pois sharr não é tipo primitivo 
			// validateColumnDeclaration(column_declaration)
			// depois concatena com column_name 
		}
	
	}
}