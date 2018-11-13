/*
* Retorna a palavra no index especificado
* EX: getWordFromIndex("matheus ricardo dos santos", ' ', 2) = "ricardo"
* Se não exeistir o index retorna o comando
*/
char* getWordFromIndex(char* command, char separator, int index){
	int cont = 1;
	int size = strlen(command);
	char* word = (char*) malloc(sizeof(char));
	for (int i = 0; i < size; ++i)
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

int valueIsInVector(char* word, char** array, int size){
	for (int i = 0; i < size; ++i)
	{
		if (strcmp(word, array[i])==0)
		{
			return i+1;
		}
	}
	return 0;
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
			tables[i] = malloc((strlen(ent->d_name)+1) * sizeof(char));
			//printf("strlen d_name: %i\n", strlen(ent->d_name));
			tables[i] = ent->d_name;
			i++;
			tables = (char**) realloc(tables, sizeof(char*)*(i+1));
			//printf("sizeof(char*)*(i+1): %i\n", sizeof(char*)*(i+1));
		}

		tables[i] = NULL;

		closedir (dir);
		return tables;
	} else {
	  	printf("Banco não encontrado ou não há tabelas.\n");
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

		closedir (dir);
		return databases;
	} else {
	  	perror ("Não há bancos criados.");
	  	return 0;
	}
}

char* getDefaultDatabaseName(){
	FILE *default_db;
	char* db_name = malloc(sizeof(char)*100);
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
//create table cursos columns (int* id,char[10] nome, float media)
/*
* remove todos os caracteres encontrado na string
*/
char* removeChar(char* old_string, char symbol){
	char* new_string = malloc(sizeof(char));
	int size = strlen(old_string), k=0;
	for (int i = 0; i < size; ++i, ++k)
	{
		if (old_string[i]==symbol)
		{
			k--;
			continue;  		
	 	}
	 	new_string = realloc(new_string, sizeof(char)*(k+1));
	 	new_string[k] = old_string[i];
	}
	new_string = realloc(new_string, sizeof(char)*(k+1));
	new_string[k] = '\0';
	return new_string;
}
/*
* remove o char de uma posição
*/
char* removeCharFromPosition(char* old_string, int position){
	char* new_string = malloc(sizeof(char));
	int size = strlen(old_string), k=0;
	for (int i = 0; i < size; ++i, ++k)
	{
		if (i==position)
		{
			k--;
			continue;  		
	 	}
	 	new_string = realloc(new_string, sizeof(char)*(k+1));
	 	new_string[k] = old_string[i];
	}
	new_string = realloc(new_string, sizeof(char)*(k+1));
	new_string[k] = '\0';
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
			int k = 0;
			for (int j = last_step; j < i; ++j, ++k)
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
			strings[cont][k+1] = '\0';
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
	return size;
}
/*
* Corta a string até o index
*/
char* cropString(char* old_string, int index){
	char* new_string = malloc(sizeof(char));
	for (int i = 0; i <index; ++i)
	{
		new_string = realloc(new_string, sizeof(char)*(i+2));
		new_string[i] = old_string[i];
	}
	new_string[index]= '\0';
	return new_string;
}

// essa função existe na lib math.h
// mas ocorreu um problema de dependência no meu gcc
int myPow(int base, int expoent){
	if (expoent==0)
	{
		return 1;
	}
	int result = base;
	for (int i = 1; i < expoent; ++i)
	{
		result = result*base;
	}
	return result;
}
int intVectorToInt(int* numbers, int size){
	int number = 0;
	for (int i = 0, j=size-1; i < size; ++i, --j)
	{
		// utiliza a representação binária
		// ex: 255 = 2*10^2 + 5*10^1 + 5*10^0
		number += numbers[i] * myPow(10, j);
	}
	return number;
}
int isInt(char* declaration_type){
	if (strlen(declaration_type)==4)
	{
		if (declaration_type[3]==reserved_symbols[3])
		{
			return strcmp(removeCharFromPosition(declaration_type, 3), primitive_types[0])==0?1:0;
		}else{
			return 0;
		}
	}else if(strlen(declaration_type)==3){
		return strcmp(declaration_type, primitive_types[0])==0?1:0;
	}
	return 0;
}

int isChar(char* declaration_type){
	if(strcmp(cropString(declaration_type, 4), primitive_types[2])==0){
		if (declaration_type[4]=='[')
		{
			int* numbers = malloc(sizeof(int));
			int j=0, number;
			for (int i = 5; declaration_type[i]!=']'; ++i, ++j)
			{
				numbers = realloc(numbers, sizeof(int)*(j+1));
				if (isdigit(declaration_type[i]))
				{
					numbers[j] = (int)declaration_type[i] - '0'; 
				}else{
					red();
					printf("Sintaxe inválida no tamanho do char\n");
					resetColor();
					return 0;
				}
			}
			number = intVectorToInt(numbers, j);
			return 1;
		}else{
			return 0;
		}
	}
	return 0;
}

int isFloat(char* declaration_type){
	if (strlen(declaration_type)==6)
	{
		if (declaration_type[5]==reserved_symbols[3])
		{
			return strcmp(removeCharFromPosition(declaration_type, 5), primitive_types[1])==0?1:0;
		}else{
			return 0;
		}

	}else if(strlen(declaration_type)==5){
		return strcmp(declaration_type, primitive_types[1])==0?1:0;
	}
	return 0;
}
int isDate(char* declaration_type){
	if (strlen(declaration_type)==5)
	{
		if (declaration_type[4]==reserved_symbols[3])
		{
			return strcmp(removeCharFromPosition(declaration_type, 4), primitive_types[3])==0?1:0;
		}else{
			return 0;
		}
	}else if(strlen(declaration_type)==4){
		return strcmp(declaration_type, primitive_types[3])==0?1:0;
	}
	return 0;
}
int validateColumnDeclaration(char* column_declaration){
	char* column_declaration_type = getWordFromIndex(column_declaration, ' ', 1);
	if(isInt(column_declaration_type) || isChar(column_declaration_type) || isFloat(column_declaration_type) || isDate(column_declaration_type)){
		return 1;
	}
	return 0;
}
int countCharInString(char* string_1, char symbol){
	int cont = 0;
	for (int i = 0; i < strlen(string_1); ++i)
	{
		if (string_1[i] == symbol)
		{
			cont++;
		}
	}
	return cont;
}
char* putCharAfterSymbol(char* old_string, char new_char, char symbol){

	int j = 0, n_occurrency = countCharInString(old_string, symbol);
	char* new_string = malloc(sizeof(char)*(strlen(old_string)+n_occurrency+1));
	for (int i = 0; i < strlen(old_string); ++i, ++j)
	{
		if (old_string[i]==symbol && old_string[i+1]!=new_char)
		{
			new_string[j] = old_string[i];
			new_string[j+1] = new_char;
			j++;
		}else{
			new_string[j] = old_string[i];
		}
	}
	new_string[j] = '\0';
	return new_string;

}

int hasPrimaryKey(char* columns_name_command){
	int n_columns = 0, found_primary_key = 0, n_key = 0;
	n_columns = countColumns(columns_name_command);
	for (int i = 1; i <= n_columns; ++i)
	{
		// falta remover os espaços e validar a sintaxe
		char* column_declaration = getWordFromIndex(columns_name_command, ',', i);
		if (column_declaration[0] == ' ')
		{
			column_declaration = removeCharFromPosition(column_declaration, 0);
		}
		char* column_declaration_type = getWordFromIndex(column_declaration, ' ', 1);
		if (isInt(column_declaration_type))
		{
			if (column_declaration_type[3]==reserved_symbols[3])
			{
				found_primary_key = 1;
				n_key++;
			}
		} 
	}
	if (found_primary_key && n_key==1)
	{
		return 1;
	}
	return 0;
}
// create table professores columns (int* id, char[60] nome, float salario)
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
		columns_name_command = removeChar(columns_name_command, ')');
		
		int n_columns = 0;
		n_columns = countColumns(columns_name_command);
		for (int i = 1; i <= n_columns; ++i)
		{
			// falta remover os espaços e validar a sintaxe
			char* column_declaration = getWordFromIndex(columns_name_command, ',', i);
			if (column_declaration[0] == ' ')
			{
				column_declaration = removeCharFromPosition(column_declaration, 0);
			}
			// valida a declaração da coluna
			// ex: int* id -> correto
			// ex: sharr[10] nome -> errado pois sharr não é tipo primitivo 
			if(!validateColumnDeclaration(column_declaration)){
				red();
				printf("Comando não reconhecido: \"%s\"\n", column_declaration);
				resetColor();
				return "error";
			}
			// depois concatena com column_name 
		}
		//create table sala columns (int* id,char[10] nome)
		columns_name_command = removeChar(columns_name_command, '(');
		columns_name_command = putCharAfterSymbol(columns_name_command, ' ', ',');
		if (hasPrimaryKey(columns_name_command))
		{
			printf("%s\n", columns_name_command);
			return columns_name_command;
		}
		throwError("Foreign Key não encontrada");
		return "error";
	
	}
}