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
				word = (char*) realloc(word, sizeof(char)*(cont_word+2));
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

/*
* Retorna a primeira palavra de uma string separada por espaço
*/
char* getFirstWord(char* command){
	char* firstWord =(char*) malloc(sizeof(char));
	int i = 0;
	while(command[i]!=' ' && command[i]!='\0'){
		firstWord[i] = command[i];
		i++;
		firstWord = (char*) realloc(firstWord, sizeof(char)*(i+1));
	}
	firstWord[i] = '\0';
	return firstWord;
}

/*
* Retorna o index de ocorrencia de uma string em um vetor de strings
* caso a string não exista no vetor retorna 0
*/

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

/*
* Retorna o index de ocorrencia de uma string no vetor de palavras reservadas
* caso a string não exista no vetor retorna -1.
* Na prática essa função informa se uma palavra é reservada ou não
*/

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
/*
* Recebe duas strings e retorna uma terceira concatenada
*/
char* concat(char *string1, char *string2){
    char *result = (char*) malloc(strlen(string1) + strlen(string2) + sizeof(char)); 
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

int databaseExist(char* db_name){
	char** dbs_name = getDatabasesName();
	int i = 0;
	while(dbs_name[i]!=NULL){
		if (strcmp(dbs_name[i], db_name)==0)
		{
			return i;
		}
		i++;
	}
	return -1;
}

//create table itens columns (int id, char[100] nome, float preco)
char** getTablesName(char* db_name){
	char** tables = (char**) malloc(sizeof(char*));
	int i = 0;

	char* firstparturl = concat("storage/", db_name);
	char* finalurl = concat(firstparturl, "/");

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir(finalurl)) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if (strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0)
			{
				continue;
			}
			tables[i] = (char*) malloc((strlen(ent->d_name)+1) * sizeof(char));
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
	}
}

char** getDatabasesName(){
	char** databases = (char**) malloc(sizeof(char*));
	int i = 0;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("storage/")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			//printf("d_name: %s\n", ent->d_name);
			if (strcmp(ent->d_name, reserved_files_name[0])==0 || strcmp(ent->d_name, ".")==0 || strcmp(ent->d_name, "..")==0)
			{
				continue;
			}
			databases[i] = (char*) malloc(strlen(ent->d_name) * sizeof(char)); 
			databases[i] = ent->d_name;
			i++;
			databases = (char**) realloc(databases, sizeof(char*)*(i+1));
		}

		databases[i] = NULL;

		closedir (dir);
		return databases;
	} else {
	  	perror ("Não há bancos criados.");
	  	return 0;
	}
}

/*
* Retorna o nome do dabase padrão
*/

char* getDefaultDatabaseName(){
	FILE *default_db;
	char* db_name = (char*) malloc(sizeof(char)*100);
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
	char* new_string = (char*) malloc(sizeof(char));
	int size = strlen(old_string), k=0;
	for (int i = 0; i < size; ++i, ++k)
	{
		if (old_string[i]==symbol)
		{
			k--;
			continue;  		
	 	}
	 	new_string = (char*) realloc(new_string, sizeof(char)*(k+1));
	 	new_string[k] = old_string[i];
	}
	new_string = (char*) realloc(new_string, sizeof(char)*(k+1));
	new_string[k] = '\0';
	return new_string;
}

/*
* remove o char de uma posição
*/

char* removeCharFromPosition(char* old_string, int position){
	char* new_string = (char*) malloc(sizeof(char));
	int size = strlen(old_string), k=0;
	for (int i = 0; i < size; ++i, ++k)
	{
		if (i==position)
		{
			k--;
			continue;  		
	 	}
	 	new_string = (char*) realloc(new_string, sizeof(char)*(k+1));
	 	new_string[k] = old_string[i];
	}
	new_string = (char*) realloc(new_string, sizeof(char)*(k+1));
	new_string[k] = '\0';
	return new_string;
}

/*
* Quebra a string onde existe o sepadator em várias strings e passa o tamanho do novo
* vetor através de um ponteiro 
*/

char** split(char* text, char separator, int* size){
	//printf("initial text: %s\n", text);
	char** strings = (char**) malloc(sizeof(char*));
	int last_step = 0; 
	int cont = 0, text_size = strlen(text);
	for (int i = 0; i < text_size; ++i)
	{
		if ((text[i]==separator && i!=0) || i==text_size-1)
		{
			strings = (char**) realloc(strings, sizeof(char*)*(cont+1));
			int k = 0;
			for (int j = last_step; j < i; ++j, ++k)
			{
				if (k==0)
				{
					strings[cont] = (char*) malloc(sizeof(char)*(k+2));
					strings[cont][k] = text[j];
				}else{
					strings[cont] = (char*) realloc(strings[cont], sizeof(char)*(k+2));
					strings[cont][k] = text[j];
					// se ele entrar no if pela condição i==text_size
					// o erro que ocorria é que o ultimo caractere não era recuperado

					if(j+1==i && text[i]!=separator){
						strings[cont] = (char*) realloc(strings[cont], sizeof(char)*(k+3));
						k++;
						strings[cont][k] = text[i];
					}
				}
			}
			strings[cont][k] = '\0';
			//printf("splited: %s - size: %i\n", strings[cont], (int)strlen(strings[cont]));
			last_step = i+1;
			cont++;
		}
	}
	*size = cont;
	//printf("size: %i\n", *size);
	return strings;
}
/*
* Separa os dados de uma linha.
* A diferença da função acima é que em splitData() ele não quebra string na virgula
* "mathes, ricardo" não vai bugar, pois ele ignora o que está entre as aspas
*/
char** splitData(char* row_data, char separator, int* size){
	//printf("aqui: %s\n", row_data);
	char** strings = (char**) malloc(sizeof(char*));
	int last_step = 0; 
	int cont = 0, text_size = strlen(row_data);
	for (int i = 0; i < text_size; ++i)
	{
		if(row_data[i]=='"'){
			i++;
			while(i<text_size && row_data[i]!='"'){
				i++;
			}
		}
		if ((row_data[i]==separator && i!=0) || i==text_size-1)
		{
			if(i==text_size-1){
				i++;
			}
			strings = (char**) realloc(strings, sizeof(char*)*(cont+1));
			int k = 0;
			for (int j = last_step; j < i; ++j, ++k)
			{
				if (k==0)
				{
					strings[cont] = (char*) malloc(sizeof(char)*(k+2));
					strings[cont][k] = row_data[j];
				}else{
					strings[cont] = (char*) realloc(strings[cont], sizeof(char)*(k+2));
					strings[cont][k] = row_data[j];
					// se ele entrar no if pela condição i==text_size
					// o erro que ocorria é que o ultimo caractere não era recuperado

					if(j+1==i && row_data[i]!=separator){
						strings[cont] = (char*) realloc(strings[cont], sizeof(char)*(k+3));
						k++;
						strings[cont][k] = row_data[i];
					}
				}
			}
			strings[cont][k] = '\0';
			//printf("splited: |%s| - size: %i\n", strings[cont], (int)strlen(strings[cont]));
			last_step = i+1;
			cont++;
		}
	}
	*size = cont;
	//printf("size: %i\n", *size);
	return strings;
}

/*
* Essa funçaõ é utilizada para a validação do comando de criação de tabela.
* Ela basicamente conta quantas colunas foram declaradas utilizando o separador ','.
*/

int countColumns(char* columns_name_command){
	int size=0;
	split(columns_name_command,',', &size);
	return size;
}

/*
* Corta a string até o index especificado. Também pode ser interpertada como
* uma funçaõ que retorna a string até o enésimo char.
* Ex: cropStringRight("matheus", 4) = "math"
* right significa que ele vai ignorar o que tem à direita
*/

char* cropStringRight(char* old_string, int index){
	char* new_string = (char*) malloc(sizeof(char));
	for (int i = 0; i <index; ++i)
	{
		new_string = (char*) realloc(new_string, sizeof(char)*(i+2));
		new_string[i] = old_string[i];
	}
	new_string[index]= '\0';
	return new_string;
}

/*
* Corta a string até o index especificado. Também pode ser interpertada como
* uma funçaõ que retorna a string até o enésimo char.
* Ex: cropStringLeft("matheus", 4) = "eus"
* left significa que ele vai ignorar o que tem à esquerda
*/

char* cropStringLeft(char* old_string, int index){
	char* new_string = (char*) malloc(sizeof(char));
	int j = 0;
	for (int i = index+1; i <strlen(old_string); ++i, ++j)
	{
		new_string = (char*) realloc(new_string, sizeof(char)*(j+2));
		new_string[j] = old_string[i];
	}
	new_string[j]= '\0';
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

/*
* Converte um vetor de inteiros para um inteiro
* Ex: [2,5,5] = 255
*/
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

/*
* Verifica se a declaração da coluna está certa e é do tipo int
*/

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
// essa função já espera receber uma declaração de inteiro validada
int isPrimary(char* declaration_type){
	if (strlen(declaration_type)==4)
	{
		if (declaration_type[3]==reserved_symbols[3])
		{
			return 1;
		}else{
			return 0;
		}
	}
	return 0;
}
/*
* Verifica se a declaração da coluna está certa e é do tipo char
*/

int isChar(char* declaration_type){
	if(strcmp(cropStringRight(declaration_type, 4), primitive_types[2])==0){
		if (declaration_type[4]=='[')
		{
			int* numbers = (int*) malloc(sizeof(int));
			int j=0, number;
			for (int i = 5; declaration_type[i]!=']'; ++i, ++j)
			{
				numbers = (int*) realloc(numbers, sizeof(int)*(j+1));
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

/*
* Verifica se a declaração da coluna está certa e é do tipo float
*/

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

/*
* Verifica se a declaração da coluna está certa e é do tipo date
*/

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

/*
* Valida uma declaração de tipo de coluna
*/
int validateColumnDeclaration(char* column_declaration){
	char* column_declaration_type = getWordFromIndex(column_declaration, ' ', 1);
	if(isInt(column_declaration_type) || isChar(column_declaration_type) || isFloat(column_declaration_type) || isDate(column_declaration_type)){
		return 1;
	}
	return 0;
}

/*
* Essa funçaõ retonar o número de vezes que um char ocorre em uma string
*/

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

/*
* Adiciona um char na string após cada ocorrencia de um dado simbolo
* Ex: putCharAfterSymbol("1,matheus,19,brasil", ' ', ',') = "1, matheus, 19, brasil" 
*/
char* putCharAfterSymbol(char* old_string, char new_char, char symbol){

	int j = 0, n_occurrency = countCharInString(old_string, symbol);
	char* new_string = (char*) malloc(sizeof(char)*(strlen(old_string)+n_occurrency+1));
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
/*
* Verifica se em uma declaração de colunas existe alguma coluna como primaryKey
*/
int hasPrimaryKey(char* columns_name_command){
	int n_columns = 0, found_primary_key = 0, n_key = 0;
	n_columns = countColumns(columns_name_command);
	for (int i = 1; i <= n_columns; ++i)
	{
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

/*
* Valida e formata uma declaração de colunas para a criação de uma tabela
*/

char* getTableHeader(char* columns_name_command){
	// int *id, varchar[255] name, float height, date birthday)
	char* column_name = (char*) malloc(sizeof(char));
	if (columns_name_command[strlen(columns_name_command)-1]!=')')
	{
		printf("sintaxe error\n");
		return "error";
	}else{

		columns_name_command = removeChar(columns_name_command, ')');
		
		int n_columns = 0;
		n_columns = countColumns(columns_name_command);
		for (int i = 1; i <= n_columns; ++i)
		{
			
			char* column_declaration = getWordFromIndex(columns_name_command, ',', i);
			if (column_declaration[0] == ' ')
			{
				column_declaration = removeCharFromPosition(column_declaration, 0);
			}
			
			if(!validateColumnDeclaration(column_declaration)){
				red();
				printf("Comando não reconhecido: \"%s\"\n", column_declaration);
				resetColor();
				return "error";
			}
		}
		
		columns_name_command = removeChar(columns_name_command, '(');
		columns_name_command = putCharAfterSymbol(columns_name_command, ' ', ',');
		if (hasPrimaryKey(columns_name_command))
		{
			return columns_name_command;
		}
		throwError("Primary Key não encontrada");
		return "error";
	
	}
}

int getFirstOcurrencyIndex(char* string_1, char symbol){
	for (int i = 0; i < strlen(string_1); ++i)
	{
		if (string_1[i]==symbol)
		{
			return i;
		}
	}
	return -1;
}

int getLastOcurrencyIndex(char* string_1, char symbol){
	for (int i = strlen(string_1)-1; i>=0; --i)
	{
		if (string_1[i]==symbol)
		{
			return i;
		}
	}
	return -1;
}
/*
* Corta a string entre dois caracteres especificados
* Ex: getStringBetweenSymbols("insert into alunos values (1, “matheus”, 1.70, “09/07/1999”)", '(', ')')
* = "1, “matheus”, 1.70, “09/07/1999”"
*/
char* getStringBetweenSymbols(char* old_string, char symbol_initial, char symbol_final){
	int size = strlen(old_string);
	int firstOcurrency = getFirstOcurrencyIndex(old_string, symbol_initial);
	int lastOcurrency = getLastOcurrencyIndex(old_string, symbol_final);
	if (firstOcurrency == -1 || lastOcurrency== -1)
	{
		return "error";
	}
	char* cropped_left = cropStringLeft(old_string, firstOcurrency);
	int chars_removed = size - strlen(cropped_left);
	char* cropped_right = cropStringRight(old_string, lastOcurrency);
	char* result = removeCharFromPosition(cropped_left, lastOcurrency - chars_removed);
	result = (char*) realloc(result, sizeof(char)*(strlen(result)+1));
	result[strlen(result)] = '\0';
	return result;
}
/*
* recupera os dados
*/
char* getValuesFromDeclaration(char* command){
	if (command[strlen(command)-1]!=')')
	{
		//printf("sintaxe error\n");
		return "error";
	}else{
		char* data = getStringBetweenSymbols(command, '(', ')');
		//printf("->>> %s\n", data);
		return data;
	}
}

FILE* getTableFileRead(char* db_name, char* table_name){
	char* path = concat("storage/", db_name);
	path = concat(path, "/\0");
	path = concat(path, table_name);
	path = concat(path, ".csv\0");
	//printf("path: %s\n", path);
	FILE* table = NULL;
	table = fopen(path, "r");
	return table;
}

FILE* getTableFileWrite(char* db_name, char* table_name){
	char* path = concat("storage/", db_name);
	path = concat(path, "/\0");
	path = concat(path, table_name);
	path = concat(path, ".csv\0");
	//printf("path: %s\n", path);
	FILE* table = NULL;
	table = fopen(path, "w");
	return table;
}

FILE* getTableFileAppend(char* db_name, char* table_name){
	char* path = concat("storage/", db_name);
	path = concat(path, "/\0");
	path = concat(path, table_name);
	path = concat(path, ".csv\0");
	//printf("path: %s\n", path);
	FILE* table = NULL;
	table = fopen(path, "a");
	return table;
}

char* readLineFromFile(FILE* table, int index){
	char* line = (char*) malloc(sizeof(char));
	char c = '*';
	int cont = 0, n_linebreaker = 0;
	int d;

	while(n_linebreaker!=index){
		if((d = fgetc(table))!=EOF){
			if(d=='\n'){
				n_linebreaker++;
				if(n_linebreaker == index){
					if((d = fgetc(table))==EOF){
						return NULL;
					}else{
						ungetc(d, table);
					}
				}
			}
		}else{
			//printf("erro\n");
			return NULL;
		}
		//printf("%i\n", cont2);
	}

	while(c!='\n'){
		//printf("%i\n", cont);
		c = fgetc(table);
		line = (char*) realloc(line, sizeof(char)*(cont+1));
		line[cont] = c;
		cont++;
	}
	line[cont] = '\0';
	//printf("line: %s\n", line);
	return line;
}

/*
* Recupera o header da tabela especificada
*/

char* getTableHeaderFromDatabase(char* db_name, char* table_name){
	char* header;
	FILE* table;
	table = getTableFileRead(db_name, table_name);
	if(table == NULL){
		return "";
	}
	header = readLineFromFile(table, 0);
	fclose(table);
	return header;
}

int validateInt(char* data){
	
	for(int i = 0; i < strlen(data); i++)
	{
		if(!isdigit(data[i])){
			return 0;
		}
	}

	return 1;
}
int valueIsInIntVector(int* vecto, int size, int value){
	for(int i = 0; i<size; i++){
		if(vecto[i]==value){
			return 1;
		}
	}
	return 0;
}
int validateIntPrimary(char* data, char* table_name){
	
	if(!validateInt(data)){
		return 0;
	}
	int n_numbers;
	int* pks = getAllIdsFromTable(table_name, &n_numbers);
	if(valueIsInIntVector(pks, n_numbers, stringToInt(data))){
		throwError("Violação de primaryKey! A chave especificada já existe!");
		return 0;
	}
	return 1;
}

int stringToInt(char* data){
	int* numbers = (int*) malloc(sizeof(int));
	//printf("data: %s", data);
	data = removeChar(data, '\n');
	data = removeChar(data, ' ');
	//printf("pos data: %s", data);
	for(int i = 0; i < strlen(data); i++)
	{
		numbers = (int*) realloc(numbers, sizeof(int)*(i+1));
		if (isdigit(data[i])) {
			numbers[i] = (int) data[i] - '0';
		}
	}
	return intVectorToInt(numbers, strlen(data));
	
}

int validateFloat(char* data){
	int size = strlen(data);
	
	if (!isdigit(data[0])) {
		return 0;
	}
	
	for(int i = 0; i < size; i++)
	{
		if(!(isdigit(data[i])) && data[i]!='.'){
			return 0;
		}else if(data[i]=='.' && !(isdigit(data[i+1]))){
			return 0;
		}
	}
	return 1;
}

int validateChar(char* data, char* type){
	if(!(data[0]=='"') || !(data[strlen(data)-1]=='"')){
		return 0;
	}
	int max_size =stringToInt(getStringBetweenSymbols(type, '[', ']'));

	if(strlen(data)-2<= max_size){
		return 1;
	}
	return 0;
}

int isValidDay(int day){
	if(day>0 && day<32){
		return 1;
	}
	return 0;
}

int isValidMonth(int month){
	if(month>0 && month<13){
		return 1;
	}
	return 0;
}

int isValidYear(int year){
	if(year>-1){
		return 1;
	}
	return 0;
}

int validateDate(char* data){
	int size;
	char** date = split(data, '/', &size);
	if(size!=3){
		return 0;	
	}
	int day, month, year;
	day = stringToInt(date[0]);
	month = stringToInt(date[1]);
	year = stringToInt(date[2]);

	if(isValidDay(day) && isValidMonth(month) && isValidYear(year)){
		return 1;
	}

	return 0;
}

// a primayKey será checada nessa função, mas será implementada
// em outro momento
int valueMatchWithType(char* data, char* type_declaration, char* table_name){
	// remove os espaçoes iniciais
	// é um loop porque o comando pode vim com mais de um espaço
	// Ex: int* id,  char[50] nome
	while(type_declaration[0]==' '){
		type_declaration = removeCharFromPosition(type_declaration, 0);
	}
	// faz a mesma coisa que o loop de cima porém com os dados
	while(data[0]==' '){
		data = removeCharFromPosition(data, 0);
	}
	char* type =  getWordFromIndex(type_declaration, ' ', 1);
	if(isInt(type)){
		if(isPrimary(type)){
			if(validateIntPrimary(data, table_name)){
				//displayConfirmMessage("Valor inteiro para primaryKey válido");
			}else{
				throwError("Valor inteiro para primaryKey inválido");
				return 0;
			}
		}else{
			if(validateInt(data)){
				//displayConfirmMessage("Valor inteiro válido");
			}else{
				throwError("Valor inteiro inválido");
				return 0;
			}
		}
		
	}else if(isChar(type)){
		
		if (validateChar(data, type)) {
			//displayConfirmMessage("Valor char válido");
		}else{
			throwError("Valor char inválido");
			return 0;
		}
		
	}else if (isFloat(type)) {
		if(validateFloat(data)){
			//displayConfirmMessage("Valor float válido");
		}else{
			throwError("Valor float inválido");
			return 0;
		}
		
	}else if (isDate(type)){
		if(validateDate(data)){
			//displayConfirmMessage("Valor date válido");
		}else{
			throwError("Valor date inválido");
			return 0;
		}
	}else{
		throwError("Erro não identificado!");
		return 0;
	}
	return 1;
}

int validateValues(char* table_name, char** data){
	char* db_name = getDefaultDatabaseName();
	char* table_header = getTableHeaderFromDatabase(db_name, table_name);
	if(strcmp(table_header, "")==0){
		return -1;
	}
	int size;
	char** columns_declaration = split(table_header, ',', &size);
	
	for(int i = 0; i < size; i++)
	{
		if(!valueMatchWithType(data[i], columns_declaration[i], table_name)){
			return 0;
		}
	}
	return 1;
}

char* concatVectorWithSeparator(char** vector, char separator, int size){
	char* result;
	for(int i = 0; i < size; i++)
	{
		if(i==0){
			result = concat("", concat(vector[i], ","));
		}else if(i+1 == size){
			result = concat(result, vector[i]);
		}else{
			result = concat(result, concat(vector[i], ","));
		}
	}
	return result;
}

int findPrimaryKeyIndex(char* header){
	int size; 
 	char** declarations = split(header, ',', &size);
	for(int i = 0; i<size; ++i){
		while(declarations[i][0]==' '){
			declarations[i] = removeCharFromPosition(declarations[i], 0);
		}
		char* type = getWordFromIndex(declarations[i], ' ', 1);
		//printf("type: %s - i: %i - size: %i\n", type, i, size);
		if(isPrimary(type)){
			return i;
		}
	}
	return -1;
}
int isOperator(char symbol){
	
	for(int i = 0; i < RESERVED_SYMBOLS_SIZE; i++)
	{
		if(symbol == reserved_symbols[i]){
			return 1;
		}
	}
	return 0;
}
int hasOperator(char* filter){
	
	for(int i = 0; i < strlen(filter); i++)
	{
		
		if (isOperator(filter[i])) {
			return 1;
		}
	}
	return 0;
}

// faz uma validação únicamente da sintaxe
int validateFilterSyntax(char** splited_filters, int n_filters){
	
	for(int i = 0; i < n_filters; i++)
	{
		
		if (i%2 == 0) {
			if(!hasOperator(splited_filters[i])){
				red();
				printf("Sintaxe incorreta: \"%s\"\n", splited_filters[i]);
				resetColor();
				return 0;
			}
		}else{
			if((strcmp(splited_filters[i], reserved_words[17])!=0 && strcmp(splited_filters[i], reserved_words[16])!=0) || (i+1)==n_filters){
				red();
				printf("Operador inesperado: \"%s\"\n", splited_filters[i]);
				resetColor();
				return 0;
			}
		}	
	}
	return 1;
	
}

int* findOperator(char* filter){
	//int* operatorsIndex[3] = {-1, -1, 0};
	int* operatorsIndex = (int*) malloc(sizeof(int)*3);
	operatorsIndex[0] = -1;
	operatorsIndex[1] = -1;
	operatorsIndex[2] = 0;

	int n_operators = 0;
	for(int i = 0; i < strlen(filter); i++)
	{
		
		if (isOperator(filter[i])) {
			operatorsIndex[n_operators] = i;
			n_operators++;
		}
	}
	operatorsIndex[2] = n_operators;
	return operatorsIndex;
}

char* getColumnNameFromFilter(char* filter, Table table){
	// filter
	// ex: 10>=idade
	int* operatorsIndex = findOperator(filter);
	
	char* cropped_left = NULL;
	char* cropped_right = NULL;
	
	if (operatorsIndex[0]!=-1) {
		if (operatorsIndex[2]==1)
		{
			cropped_left = cropStringLeft(filter, operatorsIndex[0]);
			cropped_right = cropStringRight(filter, operatorsIndex[0]);	
		}else if(operatorsIndex[2]==2){
			cropped_left = cropStringLeft(filter, operatorsIndex[1]);
			cropped_right = cropStringRight(filter, operatorsIndex[0]);
		}else{
			throwError("Operadores inválidos!");
			return NULL;
		}
		// DEBUG
		/*printf("left: %s\n", cropped_left);
		printf("right: %s\n", cropped_right);*/
		
		for(int i = 0; i < table.n_columns; i++)
		{
			while(table.columns[i][0]==' '){
				table.columns[i] = removeCharFromPosition(table.columns[i], 0);
			}
			char* column_name = getWordFromIndex(table.columns[i], ' ', 2);
			printf("name->: %s\n", column_name);
			if (strcmp(column_name, cropped_left)==0) {
				return cropped_left;
			}else if(strcmp(column_name, cropped_right)==0){
				return cropped_right;
			}
		}
		return NULL;
	}
	return NULL;
}

char* getOperatorFromFilter(char* filter){
	char* operator_c = (char*) malloc(sizeof(char));
	int n_operators = 0;
	for(int i = 0; i < strlen(filter); i++)
	{
		if(isOperator(filter[i])){
			operator_c = (char*) realloc(operator_c, sizeof(char)*(n_operators+2));
			operator_c[n_operators] = filter[i];
			n_operators++;
		}
	}
	operator_c[n_operators] = '\0';
	return operator_c;
}

char* getColumnTypeFromName(Table table, char* column_name){
	char* column_type;
	for(int i=0; i<table.n_columns; i++){
		while(table.columns[i][0] == ' '){
			table.columns[i] = removeCharFromPosition(table.columns[i], 0);
		}
		if(strcmp(getWordFromIndex(table.columns[i], ' ', 2), column_name) == 0){
			
			return getWordFromIndex(table.columns[i], ' ', 1);
		}
	}
	return NULL;
}

int isMathOperator(char* operator_d){
	
	for(int i = 0; i < strlen(operator_d); i++)
	{
		if(operator_d[i]!=reserved_symbols[0] && operator_d[i]!=reserved_symbols[1] && operator_d[i]!=reserved_symbols[2]){
			return 0;
		}
	}
	
	return 1;
}

int operatorMatchWithColumnType(char* operators, char* column_name, Table table){
	int isMathOp = isMathOperator(operators);
	char* column_type = NULL;
	if(isMathOp){
		column_type = getColumnTypeFromName(table, column_name);
		if(isInt(column_type) || isFloat(column_type) || isDate(column_type)){
			//printf("Is interger match\n");
			return 1;
		}else{
			//printf("Not Intege match\n");
			return 0;
		}
	}else{
		column_type = getColumnTypeFromName(table, column_name);
		
		if (isChar(column_type)) {
			//printf("char match\n");
			return 1;
		}else{
			//printf("char not match\n");
			return 0;
		}
		
	}
	//printf("none match\n");
	return 0;
}
/*
* verifica se uma declaração está filtrando alguma coluna
*/

int filterMatchWithColumn(char* filter, Table table){
	char* column_name = getColumnNameFromFilter(filter, table);
	printf("column name: %s\n", column_name);
	char* operators = getOperatorFromFilter(filter);
	printf("operator: %s\n", operators);
	if(operatorMatchWithColumnType(operators, column_name, table)){
		//printf("Operador correto!\n");
		return 1;
	}else{
		//printf("Operador incorreto\n");
		return 0;
	}
}

// retorna um código que significa alguma operação de:
// >, <, >=, <=, =, %
/*int interpretFilter(char* filter){

}*/

// operação controle:
// select table alunos * where (media>5 and id>3)
void applyFilter(Table* table, char* filters){
	// aplicar filtro na tabela

	// DEBUG
	//printf("filter: %s\n", filters);
	
	int n_filters, has_error = 0;
	char** splited_filters = split(filters, ' ', &n_filters);
	
	// DEBUG
	/*for(int i = 0; i < n_filters; i++)
	{
		printf("Splited filter: %s\n", splited_filters[i]);
	}*/

	// se for inválido imprime um erro e deixa table = NULL
	if(validateFilterSyntax(splited_filters, n_filters)){
		
		for(int i = 0; i < n_filters; i++)
		{
			if(i%2==0){
				if(!filterMatchWithColumn(splited_filters[i], *table)){
					has_error = 1;
				}
			}
		}
		
		if(has_error){
			throwError("Filtros aplicados incorretamente às colunas. Operação não executada!\n");
		}else{
			// se todos forem válidos
			//int isAnd = 0
			/*for(int i = 0; i < n_filters; i++)
			{
				if(i%2==0){
					//interpretFilter()
				}else{
					if(splited_filter[i]=="and"){
						isAnd = 1;
					}
				}
			}*/
			displayConfirmMessage("Aplicando filtros...\n");
		}
	}else{
		throwError("Filtros inválidos. Operação não executada!\n");
	}
	
}

int* getAllIdsFromTable(char* table_name, int* n_numbers){
	FILE* table = NULL;
	/* FILE* table = getTableFileRead(getDefaultDatabaseName(), table_name);
	printf("-> %s\n", readLineFromFile(table, 1));
	fclose(table);
	table = getTableFileRead(getDefaultDatabaseName(), table_name);
	printf("-> %s\n", readLineFromFile(table, 2));
	fclose(table);
	table = getTableFileRead(getDefaultDatabaseName(), table_name);
	printf("-> %s\n", readLineFromFile(table, 3));
	fclose(table); */
	char** rows = (char**) malloc(sizeof(char**));
	char* row;
	int i;
	int* numbers = (int*) malloc(sizeof(int*));
	for(i = 0; row!=NULL; i++)
	{
		
		table = getTableFileRead(getDefaultDatabaseName(), table_name);
		row = readLineFromFile(table, i);
		fclose(table);
		if(row != NULL){
			rows = (char**) realloc(rows, sizeof(char*)*(i+1));
			//printf("%s\n", row);
			rows[i] = row;
		}
	}
	i--;
	int pk_index = findPrimaryKeyIndex(rows[0]);
	//printf("rows[0]: %s\n", rows[0]);
	//printf("pk: %i - i: %i\n", pk_index, i);
	int size;
	for(int j = 1; j < i; j++)
	{
		char* pk_data = splitData(rows[j], ',', &size)[pk_index];
		numbers = (int*) realloc(numbers, sizeof(int*)*(j));
		//numbers[j-1] = 1;
		numbers[j-1] = stringToInt(pk_data);
	}
	
	/*for(int k = 0; k < i-1; k++)
	{
		printf("%i\n", numbers[k]);
	}*/
	//printf("PASSOU\n");
	*n_numbers = i-1;
	return numbers;

	/* table = getTableFileRead(getDefaultDatabaseName(), table_name);
	printf("-> %s\n", readLineFromFile(table, 4));
	fclose(table); */
}