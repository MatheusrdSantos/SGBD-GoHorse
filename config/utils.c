/*
* função: encontra a palavra no index especificado
* EX: getWordFromIndex("matheus ricardo dos santos", ' ', 2) = "ricardo"
* retorno: palavra na posição escolhida, caso não exista retorna o comando inteiro
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
* função:  conta o número de palavras em uma string de acordo com
* um separador.
* retorno: o número de palavra de acordo com o separador
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
* função: recupera a primeira palavra de uma string
* retorno: primeira palavra da string
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
* função: verifica se uma palavra está em um vetor de strings
* retorno: se está no vetor retorna o index+1, se não, retorna 0
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
* função: encontra o index de determinada palavra no vetor de palavras reservadas
* retorno: se está no vetor retorna o index, se não, retorna -1
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
* função: concatena duas strings
* retorno: string composta pelas duas outras strings
*/
char* concat(char *string1, char *string2){
    char *result = (char*) malloc(strlen(string1) + strlen(string2) + sizeof(char)); 
    strcpy(result, string1);
    strcat(result, string2);
    return result;
}

/*
* função: verifica se o banco de dados existe com base em seu nome
* retorno: retorna o index na lista de bancos de dados ou -1 caso o banco não exista
*/
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

/*
* função: recupera o nome de todas as tabelas de um determinado banco
* retorno: vetor com o nome das tabelas
*/
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
			tables[i] = ent->d_name;
			i++;
			tables = (char**) realloc(tables, sizeof(char*)*(i+1));
		}

		tables[i] = NULL;

		closedir (dir);
		return tables;
	} else {
	  	printf("Banco não encontrado ou não há tabelas.\n");
		return NULL;
	}
}

/*
* função: recupera o nome de todos os bancos de dados criados
* retorno: vetor de strings dos bancos criados
*/
char** getDatabasesName(){
	char** databases = (char**) malloc(sizeof(char*));
	int i = 0;

	DIR *dir;
	struct dirent *ent;
	if ((dir = opendir ("storage/")) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
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
* função: recupera o banco de dados padrão
* retorno: string com o nome do banco
*/
char* getDefaultDatabaseName(){
	FILE *default_db;
	char* db_name = (char*) malloc(sizeof(char)*100);
	default_db = fopen("storage/default_db.csv", "r");
	if (default_db == NULL)
	{
		throwError("Error opening file!\n");
	    return 0;
	}
	fscanf(default_db, "%s", db_name);
	fclose(default_db);
	return db_name;
}

/*
* função: remove todas as ocorrências de um caractere em uma string
* retorno: nova string sem os caracteres
*/
char* removeChar(char* old_string, char symbol){
	char* new_string = (char*) malloc(sizeof(char));
	
	int size = strlen(old_string), k=0;
	for (int i = 0; i < size; ++i, k++)
	{
		if (old_string[i]==symbol)
		{;
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
* função: remove m caractere de uma posição especificada
* retorno: a string sem o caractere
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
* função: Quebra a string onde existe o sepadator em várias strings e passa o tamanho do novo
* vetor através de um ponteiro
* retorno: vetor de strings com base no separador
*/
char** split(char* text, char separator, int* size){
	
	char** strings = (char**) malloc(sizeof(char*));
	int last_step = 0; 
	int cont = 0, text_size = strlen(text);
	
	// caso o separador não exista, retorna o vetor com a string passada
	// por parâmetro
	if(getFirstOcurrencyIndex(text, separator)==-1){
		strings[0] = text;
		*size = 1;
		return strings;	
	}

	// se a string passada só tiver um caractere 
	// somente ela será retornada
	if (text_size==1)
	{
		strings[0] = text;
		*size = 1;
		return strings;
	}


	for (int i = 0; i < text_size; ++i)
	{
		if ((text[i]==separator && i!=0) || i==text_size-1)
		{
			strings = (char**) realloc(strings, sizeof(char*)*(cont+1));
			int k = 0, final_pos=0;

			for (int j = last_step; j < i; ++j, ++k)
			{
				if (k==0)
				{
					strings[cont] = (char*) malloc(sizeof(char)*(k+2));
					strings[cont][k] = text[j];
				}else{
					strings[cont] = (char*) realloc(strings[cont], sizeof(char)*(k+2));
					strings[cont][k] = text[j];

					if(j+1==i && text[i]!=separator){
						strings[cont] = (char*) realloc(strings[cont], sizeof(char)*(k+3));
						k++;
						strings[cont][k] = text[i];
					}
				}
			}
			strings[cont][k] = '\0';
			last_step = i+1;
			cont++;
		}
	}
	*size = cont;
	return strings;
}

/*
* função: Separa os dados de uma linha.
* A diferença da função split() é que em splitData() ele não quebra string na virgula ou no separador
* "mathes, ricardo" pois ele ignora o que está entre as aspas
* retorno: vetor de strings com base no separador
*/
char** splitData(char* row_data, char separator, int* size){
	char** strings = (char**) malloc(sizeof(char*));
	int last_step = 0; 
	int cont = 0, text_size = strlen(row_data);

	if(getFirstOcurrencyIndex(row_data, separator)==-1){
		strings[0] = row_data;
		*size = 1;
		return strings;	
	}

	if (text_size==1)
	{
		strings[0] = row_data;
		return strings;
	}

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
			last_step = i+1;
			cont++;
		}
	}
	*size = cont;
	return strings;
}

/*
* função: essa funçaõ é utilizada para a validação do comando de criação de tabela.
* Ela basicamente conta quantas colunas foram declaradas utilizando o separador ','.
* retorno: o número de colunas declaradas
*/
int countColumns(char* columns_name_command){
	int size=0;
	split(columns_name_command,',', &size);
	return size;
}

/*
* função: corta a string até o index especificado. Também pode ser interpertada como
* uma funçaõ que retorna a string até o enésimo char.
* retorno: string cortada 
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
* função: corta a string até o index especificado. Também pode ser interpertada como
* uma funçaõ que retorna a string até o enésimo char começando a contar do final.
* retorno: string cortada 
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

/*
* função: realiza uma operação de potência entre dois números
* retorno: resultado da potência
*/
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
* função: converte um vetor de inteiros para um inteiro
* retorno: inteiro resultante
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
* função: verifica se a declaração da coluna está certa e é do tipo int
* retorno: 1 = correta; 0 = incorreta
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

/*
* função: verifica se a declaração do inteiro é primary key, ou seja, se tem forma 'int*'
* retorno: 1 = correta; 0 = incorreta
*/
int isPrimary(char* declaration_type){
	// essa função já espera receber uma declaração de inteiro validada
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
* função: verifica se a declaração da coluna está certa e é do tipo char
* retorno: 1 = correta; 0 = incorreta
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
					throwError("Sintaxe inválida no tamanho do char\n");
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
* função: verifica se a declaração da coluna está certa e é do tipo float
* retorno: 1 = correta; 0 = incorreta
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
* função: verifica se a declaração da coluna está certa e é do tipo date
* retorno: 1 = correta; 0 = incorreta
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
* função: valida uma declaração de tipo de coluna
* retorno: 1 = correta; 0 = incorreta
*/
int validateColumnDeclaration(char* column_declaration){
	char* column_declaration_type = getWordFromIndex(column_declaration, ' ', 1);
	if(isInt(column_declaration_type) || isChar(column_declaration_type) || isFloat(column_declaration_type) || isDate(column_declaration_type)){
		return 1;
	}
	return 0;
}

/*
* função: conta o número de ocorrêcias de um char em uma string
* retorno: número de ocorrências
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
* função: adiciona um char na string após cada ocorrencia de um dado simbolo
* retorno: string com o novo char
* EX: putCharAfterSymbol("1,matheus,19,brasil", ' ', ',') = "1, matheus, 19, brasil"
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
* função: verifica se em uma declaração de colunas existe alguma coluna como primaryKey
* retorno: 1 = tem primary key; 0 = não tem primary key ou tem mais de uma
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
* função: valida e formata uma declaração de colunas para a criação de uma tabela
* retorno: declaração das colunas formatadas ou "erro" em caso de sintaxe inválida
*/
char* getTableHeader(char* columns_name_command){
	// int *id, varchar[255] name, float height, date birthday)
	char* column_name = (char*) malloc(sizeof(char));
	if (columns_name_command[strlen(columns_name_command)-1]!=')')
	{
		throwError("sintaxe error\n");
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
			
			// valida a declaração de colunas
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

/*
* função: recupera a primeira ocorrência de um char em uma string
* retorno: index da ocorrência ou -1 caso ele não ocorra
*/
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

/*
* função: recupera o index da enésima ocorrências de um char em uma string
* retorno: o index ou -1 caso não exista a enésima ocorrência
*/
int getNOcurrencyIndex(char* string_1, char symbol, int n){
	int n_ocurrency = 0;
	for (int i = 0; i < strlen(string_1); ++i)
	{
		if (string_1[i]==symbol)
		{
			n_ocurrency++;
			if(n_ocurrency==n){
				return i;
			}
		}
	}
	return -1;
}

/*
* função: recupera o index da ultima ocorrências de um char em uma string
* retorno: o index ou -1 caso não exista a ocorrência
*/
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
* função: corta a string entre dois caracteres especificados
* retorno: string cortada
* Ex: getStringBetweenSymbols("insert into alunos values (1, “matheus”, 1.70, “09/07/1999”)", '(', ')')
* = "1, “matheus”, 1.70, “09/07/1999”"
*/
char* getStringBetweenSymbols(char* old_string, char symbol_initial, char symbol_final){
	int size = strlen(old_string);
	int firstOcurrency = getFirstOcurrencyIndex(old_string, symbol_initial);
	int lastOcurrency = getLastOcurrencyIndex(old_string, symbol_final);
	if (firstOcurrency == -1 || lastOcurrency== -1)
	{
		throwError("Declaração incorreta!");
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
* função: recupera os dados de uma declaração
* retorno: string referente aos dados
* Ex: getValuesFromDeclaration("insert into alunos values (1, “matheus”, 1.70, “09/07/1999”)", '(', ')')
* = "1, “matheus”, 1.70, “09/07/1999”"
*/
char* getValuesFromDeclaration(char* command){
	if (command[strlen(command)-1]!=')')
	{
		return "error";
	}else{
		char* data = getStringBetweenSymbols(command, '(', ')');
		return data;
	}
}

/*
* função: recupera o arquivo aberto da tabela
* retorno: arquivo aberto em forma de leitura
*/
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

/*
* função: recupera o arquivo aberto da tabela
* retorno: arquivo aberto em forma de leitura binária
*/
FILE* getTableFileReadBinary(char* db_name, char* table_name){
	char* path = concat("storage/", db_name);
	path = concat(path, "/\0");
	path = concat(path, table_name);
	path = concat(path, ".csv\0");
	//printf("path: %s\n", path);
	FILE* table = NULL;
	table = fopen(path, "rb");
	return table;
}

/*
* função: recupera o arquivo aberto da tabela
* retorno: arquivo aberto em forma de escrita
*/
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

/*
* função: recupera o arquivo aberto da tabela
* retorno: arquivo aberto em forma de escrita no final do arquivo
*/
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

/*
* função: lê linha no index especificado a partir de um arquivo
* retorno: string contendo a linha
*/
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
* função: recupera o header da tabela especificada
* retorno: string com o cabeçalho de declaração da tabela
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

/*
* função: valida um dado que vede ser do tipo inteiro
* retorno: 1 = válido; 0 = inválido
*/
int validateInt(char* data){
	
	for(int i = 0; i < strlen(data); i++)
	{
		if(!isdigit(data[i])){
			return 0;
		}
	}

	return 1;
}

/*
* função: verifica se um inteiro ocorre no vetor
* retorno: 1 = ocorre; 0 = não ocorre
*/
int valueIsInIntVector(int* vecto, int size, int value){
	for(int i = 0; i<size; i++){
		if(vecto[i]==value){
			return 1;
		}
	}
	return 0;
}

/*
* função: verifica se a primary key já existe na tabela especificada
* retorno: 1 = válido; 0 = inválido
*/
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

/*
* função: converte string de dígitos para inteiro
* retorno: inteiro equivalente à string
*/
int stringToInt(char* data){
	int* numbers = (int*) malloc(sizeof(int));
	//printf("data: %s\n", data);
	data = removeChar(data, '\n');
	data = removeChar(data, ' ');
	//printf("pos data: %s\n", data);
	for(int i = 0; i < strlen(data); i++)
	{
		numbers = (int*) realloc(numbers, sizeof(int)*(i+1));
		if (isdigit(data[i])) {
			numbers[i] = (int) data[i] - '0';
		}
	}
	return intVectorToInt(numbers, strlen(data));
	
}

/*
* função: valida um dado que vede ser do tipo float
* retorno: 1 = válido; 0 = inválido
*/
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

/*
* função: valida um dado que vede ser do tipo char
* retorno: 1 = válido; 0 = inválido
*/
int validateChar(char* data, char* type){
	if(!(data[0]=='"') || !(data[strlen(data)-1]=='"')){
		return 0;
	}

	// recupera o tamanho do char
	int max_size =stringToInt(getStringBetweenSymbols(type, '[', ']'));

	if(strlen(data)-2<= max_size){
		return 1;
	}
	return 0;
}

/*
* função: verifica se é um dia válido para uma data
* retorno: 1 = válido; 0 = inválido
*/
int isValidDay(int day){
	if(day>0 && day<32){
		return 1;
	}
	return 0;
}

/*
* função: verifica se é um mês válido para uma data
* retorno: 1 = válido; 0 = inválido
*/
int isValidMonth(int month){
	if(month>0 && month<13){
		return 1;
	}
	return 0;
}

/*
* função: verifica se é um ano válido para uma data
* retorno: 1 = válido; 0 = inválido
*/
int isValidYear(int year){
	if(year>-1){
		return 1;
	}
	return 0;
}

/*
* função: valida um dado que vede ser do tipo Date
* retorno: 1 = válido; 0 = inválido
*/
int validateDate(char* data){
	int size = 0;
	//printf("size com barra: %i\n", size);
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

/*
* função: verifica se o valor dado para uma coluna é correto para a sua declaração
* retorno: 1 = válido; 0 = inválido
*/
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

/*
* função: valida os dados que serão inseridos na tabela
* retorno: 1 = válido; 0 = inválido
*/
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

/*
* função: concatena um vetor de string com um separador entre elas
* retorno: string concatenada
*/
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

/*
* função: encontra o index da primary key no header de uma tabela
* retorno: index ou -1 caso não seja encontrado
*/
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

/*
* função: verifica se o char é um símbolo válido com operador
* retorno: 1 = válido; 0 = inválido
*/
int isOperator(char symbol){
	
	for(int i = 0; i < RESERVED_SYMBOLS_SIZE; i++)
	{
		if(symbol == reserved_symbols[i]){
			return 1;
		}
	}
	return 0;
}

/*
* função: verifica se o filtro tem operador
* retorno: 1 = tem; 0 = não tem
*/
int hasOperator(char* filter){
	
	for(int i = 0; i < strlen(filter); i++)
	{
		
		if (isOperator(filter[i])) {
			return 1;
		}
	}
	return 0;
}

/*
* função: faz uma validação únicamente da sintaxe
* retorno: 1 = válido; 0 = inválido
*/
int validateFilterSyntax(char** splited_filters, int n_filters){
	
	for(int i = 0; i < n_filters; i++)
	{
		//printf("splited_f: %s\n", splited_filters[i]);
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

/*
* função: encontra os índices que ocorrem os operadores em um comendo de filtro
* retorno: vetor de índices
*/
int* findOperator(char* filter){
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

/*
* função: recupera o nome de uma coluna a partir de uma declaração de filtro
* retorno: nome da coluna
* ex: 10>=idade retorna apenas "idade"
*/
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
		//
		// DEBUG
		/*printf("left: %s\n", cropped_left);
		printf("right: %s / size: %i\n", cropped_right, (int)strlen(cropped_right));
		printf("n_columns: %i\n", table.n_columns);*/
		for(int i = 0; i < table.n_columns; i++)
		{
			while(table.columns[i][0]==' '){
				table.columns[i] = removeCharFromPosition(table.columns[i], 0);
			}
			//printf("original: %s\n", table.columns[i]);
			char* column_name = getWordFromIndex(table.columns[i], ' ', 2);
			column_name = removeChar(column_name, '\n');
		
			//printf("name->: %s -/- size: %i\n", column_name, (int)strlen(column_name));
			/*if(column_name[strlen(column_name)-1]=='\n'){
				column_name = removeCharFromPosition(column_name, strlen(column_name)-1);
			}*/
			if (strcmp(column_name, cropped_left)==0) {
				return cropped_left;
			}else if(strcmp(column_name, cropped_right)==0){
				return cropped_right;
			}
		}
		throwError("Nome de operador incorreto!");
		return NULL;
	}
	throwError("Nome de operador incorreto!");
	return NULL;
}

/*
* função: recupera o operador de uma coluna a partir de uma declaração de filtro
* retorno: operador
* ex: 10>=idade retorna apenas ">="
*/
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

/*
* função: recupera o tipo da coluna a partir de seu nome
* retorno: tipo da coluna ou NULL caso não encontre a coluna
*/
char* getColumnTypeFromName(Table table, char* column_name){
	char* column_type;
	char* column_declaration_name;

	// percorre a tabela
	for(int i=0; i<table.n_columns; i++){
		while(table.columns[i][0] == ' '){
			table.columns[i] = removeCharFromPosition(table.columns[i], 0);
		}
		// recupera o nome da tabela
		column_declaration_name = getWordFromIndex(table.columns[i], ' ', 2);
		
		if (column_declaration_name[strlen(column_declaration_name)-1] == '\n') {
			column_declaration_name = removeCharFromPosition(column_declaration_name, strlen(column_declaration_name)-1);
		}
		
		// verifica se os nomes são iguais
		if(strcmp(column_declaration_name, column_name) == 0){
			// retorna apenas o tipo
			return getWordFromIndex(table.columns[i], ' ', 1);
		}
	}
	return NULL;
}

/*
* função: verifica se o operador é de operações numéricas
* retorno: 1 = é numérico; 0 = não é
* ex: '>', '<', '>=', '<=', '='
*/
int isMathOperator(char* operator_d){
	//printf("entrou\n");
	for(int i = 0; i < strlen(operator_d); i++)
	{
		if(operator_d[i]!=reserved_symbols[0] && operator_d[i]!=reserved_symbols[1] && operator_d[i]!=reserved_symbols[2]){
			return 0;
		}
	}
	
	//printf("saiu\n");
	return 1;
}

/*
* função: verifica se o operador é do mesmo tipo da coluna declarada
* retorno: 1 = válido; 0 = inválido
*/
int operatorMatchWithColumnType(char* operators, char* column_name, Table table){
	int isMathOp = isMathOperator(operators);
	char* column_type = NULL;
	if(isMathOp){
		//printf("antes\n");
		column_type = getColumnTypeFromName(table, column_name);
		//printf("depois\n");
		//printf("column_type: %s\n", column_type);
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
* função: verifica se uma declaração está filtrando alguma coluna e se o tipo de filtro é
* válido para o tipo da coluna
* retorno: 1 = válido; 0 = inválido
*/
int filterMatchWithColumn(char* filter, Table table){
	char* column_name = getColumnNameFromFilter(filter, table);
	//printf("column name: %s\n", column_name);
	char* operators = getOperatorFromFilter(filter);
	//printf("operator: %s\n", operators);
	if(operatorMatchWithColumnType(operators, column_name, table)){
		//printf("Operador correto!\n");
		return 1;
	}else{
		//printf("Operador incorreto\n");
		return 0;
	}
}

/*
* função: interpretar a operação presente no filtro
* retorno: código que significa alguma operação de:
* >, <, >=, <=, =, %
* {'=', '>', '<', '*', '%'}
* Códigos de retorno de acordo com o filtro
* 1 - >
* 2 - <
* 3 - =
* 4 - %
* 13 - >=
* 23 - <= 
*/
int interpretFilter(char* filter){
	int* codes = (int*) malloc(sizeof(int));
	//printf("complete filter: %s\n", filter);
	int n_symbols = 0;
	for(int i = 0; i < strlen(filter); i++)
	{
		if(filter[i]==reserved_symbols[0]){
			codes = (int*) realloc(codes, sizeof(int)*(n_symbols+1));
			codes[n_symbols] = 3;
			n_symbols++;
		}else if(filter[i]==reserved_symbols[1]){
			codes = (int*) realloc(codes, sizeof(int)*(n_symbols+1));
			codes[n_symbols] = 1;
			n_symbols++;
		}else if(filter[i]==reserved_symbols[2]){
			codes = (int*) realloc(codes, sizeof(int)*(n_symbols+1));
			codes[n_symbols] = 2;
			n_symbols++;
		}else if(filter[i]==reserved_symbols[4]){
			codes = (int*) realloc(codes, sizeof(int)*(n_symbols+1));
			codes[n_symbols] = 4;
			n_symbols++;
		}
	}
	
	return intVectorToInt(codes, n_symbols);
}

/*
* função: recupera o valor de filtro
* retorno: valor do filtro
* ex: 10>=idade retorna apenas "10"
*/
char* getValueFromFilter(char* filter_declaration,char* c_name){
	int* operatorsIndex = findOperator(filter_declaration);
	
	char* cropped_left = NULL;
	char* cropped_right = NULL;
	
	if (operatorsIndex[0]!=-1) {
		if (operatorsIndex[2]==1)
		{
			cropped_left = cropStringLeft(filter_declaration, operatorsIndex[0]);
			cropped_right = cropStringRight(filter_declaration, operatorsIndex[0]);	
		}else if(operatorsIndex[2]==2){
			cropped_left = cropStringLeft(filter_declaration, operatorsIndex[1]);
			cropped_right = cropStringRight(filter_declaration, operatorsIndex[0]);
		}else{
			throwError("Operadores inválidos!");
			return NULL;
		}
		// DEBUG
		/*printf("left: %s\n", cropped_left);
		printf("right: %s\n", cropped_right);*/
		
		
		while(c_name[0]==' '){
			c_name = removeCharFromPosition(c_name, 0);
		}
		//printf("name->: %s\n", c_name);
		if (strcmp(c_name, cropped_left)!=0) {
			return cropped_left;
		}else if(strcmp(c_name, cropped_right)!=0){
			return cropped_right;
		}
		
		return NULL;
	}
	return NULL;
}

/*
* função: busca a coluna em um vetor de strings
* retorno: index da coluna
*/
int getColumnIndex(char** columns, char* column_name, int n_columns){
	//printf("n_columns: ->%i\n", n_columns);
	for(int i = 0; i < n_columns; i++)
	{
		while(columns[i][0]==' '){
			columns[i] = removeCharFromPosition(columns[i], 0);
		}
		if(columns[i][strlen(columns[i])-1] == '\n'){
			columns[i] = removeCharFromPosition(columns[i], strlen(columns[i])-1);
		}
		if(strcmp(getWordFromIndex(columns[i], ' ', 2), column_name)==0){
			return i;
		}
	}
	return -1;
}

/*
* função: verifica qual a maior string em um vetor de string
* retorno: tamanho da maior string
*/
int getLargestStringInArray(char** received_array, int size){
	int pos_largestString, largestLen = 0;
	for(int i = 0; i < size; i++)
	{
		if(strlen(received_array[i]) > largestLen)
			pos_largestString = i;
	}
	return pos_largestString;
}

/*
* função: aplica o filtro de maior que
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterThan(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value>filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: converte uma string para a struct Date
* retorno: struct Date preenchida
*/
Date stringToDate(char* text_date){
	int vector_size;
	char** date = split(text_date, '/', &vector_size);
	Date new_date;
	if(vector_size==3){
		new_date.i_day = stringToInt(date[0]);
		new_date.i_month = stringToInt(date[1]);
		new_date.i_year = stringToInt(date[2]);
	}
	return new_date;
}

/*
* função: aplica o filtro de maior que na data, verifica se a data 1 é após a data 2
* retorno: 1 = data 1 vem após; 0 = data 1 não vem após
*/
int compareDateGreater(Date date_1, Date date_2){
	if(date_1.i_year>date_2.i_year){
		return 1;
	}else if(date_1.i_year==date_2.i_year && date_1.i_month>date_2.i_month){
		return 1;
	}else if(date_1.i_year==date_2.i_year && date_1.i_month==date_2.i_month && date_1.i_day>date_2.i_day){
		return 1;
	}
	return 0;
}

/*
* função: aplica o filtro de igualdade
* retorno: 1 = datas iguais; 0 = datas diferentes
*/
int compareDateEqual(Date date_1, Date date_2){
	if(date_1.i_year == date_2.i_year && date_1.i_month==date_2.i_month && date_1.i_day==date_2.i_day){
		return 1;
	}
	return 0;
}

/*
* função: aplica o filtro de maior que nas datas
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterThanDate(Table table, Date filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		
		char* row_value = table.rows[i].data[column_index];
		Date value_date;
		value_date.i_day = stringToDate(row_value).i_day;
		value_date.i_month = stringToDate(row_value).i_month;
		value_date.i_year = stringToDate(row_value).i_year;
		//printf("row_value: %i\n", row_value);
		if(compareDateGreater(value_date, filter_value)){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior ou igual nas datas
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterEqualToDate(Table table, Date filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		
		char* row_value = table.rows[i].data[column_index];
		Date value_date;
		value_date.i_day = stringToDate(row_value).i_day;
		value_date.i_month = stringToDate(row_value).i_month;
		value_date.i_year = stringToDate(row_value).i_year;
		//printf("row_value: %i\n", row_value);
		if(compareDateGreater(value_date, filter_value) || compareDateEqual(value_date, filter_value)){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor ou igual nas datas
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessEqualToDate(Table table, Date filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		
		char* row_value = table.rows[i].data[column_index];
		Date value_date;
		value_date.i_day = stringToDate(row_value).i_day;
		value_date.i_month = stringToDate(row_value).i_month;
		value_date.i_year = stringToDate(row_value).i_year;
		//printf("row_value: %i\n", row_value);
		if(compareDateGreater(filter_value, value_date) || compareDateEqual(value_date, filter_value)){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor que
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessThanDate(Table table, Date filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		
		char* row_value = table.rows[i].data[column_index];
		Date value_date;
		value_date.i_day = stringToDate(row_value).i_day;
		value_date.i_month = stringToDate(row_value).i_month;
		value_date.i_year = stringToDate(row_value).i_year;
		//printf("row_value: %i\n", row_value);
		if(compareDateGreater(filter_value, value_date)){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;

}

/*
* função: aplica o filtro de igualdade nas datas
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyEqualToDate(Table table, Date filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		
		char* row_value = table.rows[i].data[column_index];
		Date value_date;
		value_date.i_day = stringToDate(row_value).i_day;
		value_date.i_month = stringToDate(row_value).i_month;
		value_date.i_year = stringToDate(row_value).i_year;
		//printf("row_value: %i\n", row_value);
		if(compareDateEqual(filter_value, value_date)){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;

}

/*
* função: aplica o filtro de maior que em com valor inteiros em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterThanIntFloat(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		float row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value>filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior que em com valor float em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterThanFloatFloat(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		float row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value>filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior que em com valor float em uma coluna de int
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterThanFloatInt(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		float row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value>filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor que
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessThan(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value<filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor que com valor inteiro em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessThanIntFloat(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		float row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value<filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor que com valor float em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessThanFloatFloat(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		float row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value<filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor que com valor float em uma coluna de inteiro
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessThanFloatInt(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		float row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value<filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de igualdade com valor inteiro em uma coluna de inteiro
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyEqualTo(Table table, char* filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		char* row_value = table.rows[i].data[column_index];
		row_value = removeChar(row_value, '\n');
		row_value = removeChar(row_value, ' ');
		/*printf("row_value: %s\n", row_value);
		printf("filter: %s\n", filter_value);*/
		if(strcmp(row_value, filter_value)==0){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior ou igualque com valor inteiro em uma coluna de inteiro
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterEqualTo(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value>=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior ou igual com valor inteiro em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterEqualToIntFloat(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value>=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior ou igual com valor float em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterEqualToFloatFloat(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value>=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de maior ou igual em valor float em uma coluna de inteiro
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyGreaterEqualToFloatInt(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value>=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor ou igual com valor inteiro em uma coluna de inteiro
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessEqualTo(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value<=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor ou igual com valor inteiro em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessEqualToIntFloat(Table table, int filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value<=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de menor ou igual com valor float em uma coluna de float
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessEqualToFloatFloat(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = strtof(table.rows[i].data[column_index], NULL);
		//printf("row_value: %i\n", row_value);
		if(row_value<=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}


/*
* função: aplica o filtro de menor ou igual com valor float em uma coluna de inteiro
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyLessEqualToFloatInt(Table table, float filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		int row_value = stringToInt(table.rows[i].data[column_index]);
		//printf("row_value: %i\n", row_value);
		if(row_value<=filter_value){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}


/*
* função: aplica o filtro de proximidade de string (busca por substrings)
* retorno: vetor com as primary keys que satisfazem o filtro
*/
int* applyStringSimilarity(Table table, char* filter_value, int column_index, int* n_pks){
	int* pks = (int*) malloc(sizeof(int));
	int n_pks_local = 0;
	//printf("n_rows: %i\n", table.n_rows);
	for(int i = 0; i < table.n_rows-1; i++)
	{
		// pode não ser inteiro
		/*
		printf("column_i: %i\n", column_index);
		*/
		//printf("valor suspeito: %s - size: %i\n", table.rows[i].data[column_index], (int)strlen(table.rows[i].data[column_index]));
		char* row_value = table.rows[i].data[column_index];
		//printf("row_value: %i\n", row_value);
		//isSubstring()
		if(strstr(row_value, filter_value) != NULL){
			// pega o valor da pk
			
			pks = (int*) realloc(pks, sizeof(int)*(n_pks_local+1));
			pks[n_pks_local] = stringToInt(table.rows[i].data[table.pk_index]);
			//printf("result: %s\n", table.rows[i].data[table.pk_index]);
			n_pks_local++;
		}
	}
	*n_pks = n_pks_local;
	return pks;
	
}

/*
* função: aplica o filtro de acordo com o código da operação e com os tipos de dados e de colunas
* retorno: primary keys restantes após o filtro
* {'=', '>', '<', '*', '%'}
* Códigos de retorno de acordo com o filtro
* 1 - >
* 2 - <
* 3 - =
* 4 - %
* 13 - >=
* 23 - <= 
*/
int* orientateFilterAnd(int operation_code, Table* table, char* column_name, char* filter_value, int* n_pks){
	int column_index = getColumnIndex((*table).columns, column_name, (*table).n_columns);
	//int column_index = 0;
	//comparações de igualdade entre float podem ser feitas como comparação de string
	if(operation_code == 1){
		int* remainders_pk;
		// verificar se filter value é int ou float
		//printf("column index: %i\n", column_index);
		//printf("%s\n", filter_value);
		
		if(validateDate(filter_value) && isDate(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			//printf("entrou no if\n");
			remainders_pk = applyGreaterThanDate((*table), stringToDate(filter_value), column_index, n_pks);
			return remainders_pk;
		}
		//printf("deu merda aqui!\n");
			// applys the same filter logic
		// aplysFilter

		if (validateInt(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))) {
			
			remainders_pk = applyGreaterThan((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;
		}else if(validateInt(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyGreaterThanIntFloat((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;
		}else if(validateFloat(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyGreaterThanFloatFloat((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}else if(validateFloat(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyGreaterThanFloatInt((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;

		}
		
		//printf("column index2: %i\n", column_index);
	}else if(operation_code == 2){
		int* remainders_pk;
		// verificar se filter value é int ou float
		//printf("column index: %i\n", column_index);
		if(validateDate(filter_value) && isDate(getWordFromIndex((*table).columns[column_index], ' ', 1))){

			remainders_pk = applyLessThanDate((*table), stringToDate(filter_value), column_index, n_pks);
			return remainders_pk;
		}
		if (validateInt(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))) {
			remainders_pk = applyLessThan((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;
		}else if(validateInt(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyLessThanIntFloat((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;

		}else if(validateFloat(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyLessThanFloatFloat((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}else if(validateFloat(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyLessThanFloatInt((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}

	}else if(operation_code == 3){
		int* remainders_pk;
		// verificar se filter value é int ou float
		//printf("column index: %i\n", column_index);
		if(validateDate(filter_value) && isDate(getWordFromIndex((*table).columns[column_index], ' ', 1))){

			remainders_pk = applyEqualToDate((*table), stringToDate(filter_value), column_index, n_pks);
			return remainders_pk;
		}
		remainders_pk = applyEqualTo((*table), filter_value, column_index, n_pks);
		return remainders_pk;
		
		//printf("column index2: %i\n", column_index);
		
	}else if(operation_code == 4){
		int* remainders_pk;
		// verificar se filter value é int ou float
		//printf("column index: %i\n", column_index);
		remainders_pk = applyStringSimilarity((*table), filter_value, column_index, n_pks);
		return remainders_pk;
		//printf("column index2: %i\n", column_index);

	}else if(operation_code == 13){

		int* remainders_pk;
		// verificar se filter value é int ou float
		//printf("column index: %i\n", column_index);
		if(validateDate(filter_value) && isDate(getWordFromIndex((*table).columns[column_index], ' ', 1))){

			remainders_pk = applyGreaterEqualToDate((*table), stringToDate(filter_value), column_index, n_pks);
			return remainders_pk;
		}
		if (validateInt(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))) {
			remainders_pk = applyGreaterEqualTo((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;
		}else if(validateInt(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyGreaterEqualToIntFloat((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;

		}else if(validateFloat(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyGreaterEqualToFloatFloat((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}else if(validateFloat(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyGreaterEqualToFloatInt((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}

	}else if(operation_code == 23){
		int* remainders_pk;
		// verificar se filter value é int ou float
		//printf("column index: %i\n", column_index);
		if(validateDate(filter_value) && isDate(getWordFromIndex((*table).columns[column_index], ' ', 1))){

			remainders_pk = applyLessEqualToDate((*table), stringToDate(filter_value), column_index, n_pks);
			return remainders_pk;
		}
		if (validateInt(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))) {
			remainders_pk = applyLessEqualTo((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;
		}else if(validateInt(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyLessEqualToIntFloat((*table), stringToInt(filter_value), column_index, n_pks);
			return remainders_pk;
		}else if(validateFloat(filter_value) && isFloat(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyLessEqualToFloatFloat((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}else if(validateFloat(filter_value) && isInt(getWordFromIndex((*table).columns[column_index], ' ', 1))){
			remainders_pk = applyLessEqualToFloatInt((*table), strtof(filter_value, NULL), column_index, n_pks);
			return remainders_pk;
		}
	}
}

/*
* função: recupera a intersecção de dois vetores de inteiros
* retorno: vetor que representa a intersecção
*/
int* getIntersectionFromIntVector(int** pks, int* n_pks, int* n_result_pks){
	// essa função só pode ser chamada caso exista o oerador lógico 'and'
	int* remainders = (int*) malloc(sizeof(int));
	int n_remainders = 0;
	for(int j = 0; j < n_pks[0]; j++)
	{	
		for(int k = 0; k < n_pks[1]; k++)
		{
			if(pks[0][j] == pks[1][k]){
				remainders = (int*) realloc(remainders, sizeof(int)*(n_remainders+1));
				//printf("-> %i\n", pks[0][j]);
				remainders[n_remainders] = pks[0][j];
				n_remainders++; 
			}
			
		}
	}
	*n_result_pks = n_remainders;
	return remainders;	
}

/*
* função: recupera o complemento de dois vetores de inteiros
* retorno: vetor que representa o complemento
*/
int* getComplementFromIntVector(int** pks, int* n_pks, int* n_result_pks){
	// essa função só pode ser chamada caso exista o operador lógico 'or' 
	int* remainders = (int*) malloc(sizeof(int));
	
	for(int i = 0; i < n_pks[0]; i++)
	{
		remainders = (int*) realloc(remainders, sizeof(int)*(i+1));
		remainders[i] = pks[0][i];
	}
	//printf("entrou aqui\n");
	
	int n_remainders = n_pks[0];
	for(int j = 0; j < n_pks[1]; j++)
	{	
		if(!valueIsInIntVector(remainders, n_remainders, pks[1][j])){
			//printf("entrou--\n");
			remainders = (int*) realloc(remainders, sizeof(int)*(n_remainders+1));
			remainders[n_remainders] = pks[1][j];
			n_remainders++;
		}
	}
	//printf("n_results: %i\n", n_remainders);
	//printf("n_vetor 2: %i\n", n_pks[1]);
	*n_result_pks =n_remainders;
	return remainders;	
}

/*
* função: executa a operação com base nos operadores lógicos presentes no filtro
* retorno: vetor com as primary keys que passaram pelos filtros
*/
int* execOperations(int* operations_code, int n_operations, Table* table, char** columnsName, char** filter_values, int isAnd, int* n_pks_to_print){
	if(isAnd){
		int** pks = (int**) malloc(sizeof(int*));
		int* n_pks = (int*) malloc(sizeof(int));
		int n_pks_aux, i;
		//printf("n_operation: %i\n", n_operations);
		for(i = 0; i < n_operations; i++)
		{
			/*printf("operations_code: %i\n", operations_code[i]);
			printf("columns_name: %s\n", columnsName[i]);
			printf("filter_values: %s\n", filter_values[i]);*/
			n_pks = (int*) realloc(n_pks, sizeof(int)*(i+1));
			pks = (int**) realloc(pks, sizeof(int*)*(i+2));
			pks[i] = orientateFilterAnd(operations_code[i], table, columnsName[i], filter_values[i], &n_pks_aux);
			n_pks[i] = n_pks_aux;

		}
		pks[i] = NULL;
		if(n_operations>1){

			// aplicar função que tranforme os dois vetores em penas um que represente a intersecção entre eles
			int j = 0, n_result_pks;
			int* result_pks = getIntersectionFromIntVector(pks, n_pks, &n_result_pks);
			/*printf("--------\n RESULT\n ------\n");
			printf("n_results: %i\n", n_result_pks);
			for(int j = 0; j < n_result_pks; j++)
			{
				printf("pk: %i\n", result_pks[j]);
			}*/
			*n_pks_to_print = n_result_pks;
			return result_pks;
		}else{
			/*printf("--------\n RESULT\n ------\n");
			printf("n_pks: %i\n", n_pks[0]);
			for(int j = 0; j < n_pks[0]; j++)
			{
				printf("pks: %i\n", pks[0][j]);
			}*/
			*n_pks_to_print = n_pks[0];
			return pks[0];
		}
		
		return NULL;
	}else{
		int** pks = (int**) malloc(sizeof(int*));
		int* n_pks = (int*) malloc(sizeof(int));
		int n_pks_aux, i;
		//printf("n_operation: %i\n", n_operations);
		for(i = 0; i < n_operations; i++)
		{
			/*printf("operations_code: %i\n", operations_code[i]);
			printf("columns_name: %s\n", columnsName[i]);*/
			n_pks = (int*) realloc(n_pks, sizeof(int)*(i+1));
			pks = (int**) realloc(pks, sizeof(int*)*(i+2));
			pks[i] = orientateFilterAnd(operations_code[i], table, columnsName[i], filter_values[i], &n_pks_aux);
			//printf("filter_values: %s\n", filter_values[i]);
			n_pks[i] = n_pks_aux;

		}
		pks[i] = NULL;
		if(n_operations>1){

			// aplicar função que tranforme os dois vetores em penas um que represente a intersecção entre eles
			int j = 0, n_result_pks;
			int* result_pks = getComplementFromIntVector(pks, n_pks, &n_result_pks);
			/*printf("--------\n RESULT\n ------\n");
			printf("n_results: %i\n", n_result_pks);
			for(int j = 0; j < n_result_pks; j++)
			{
				printf("pk: %i\n", result_pks[j]);
			}*/
			*n_pks_to_print = n_result_pks;
			return result_pks;
		}else{
			/*printf("--------\n RESULT\n ------\n");
			printf("n_pks: %i\n", n_pks[0]);
			for(int j = 0; j < n_pks[0]; j++)
			{
				printf("pks: %i\n", pks[0][j]);
			}*/
			*n_pks_to_print = n_pks[0];
			return pks[0];
		}
		
		return NULL;
	}
	
}

/*
* função: imprime a tabela com seus dados no terminal (sem filtro)
* retorno: void
*/
void printTable(Table table){
	//printf("->%s\n", table.rows[0].data[0]);
	int table_content_string_splited_size;
	int size_largestString = 0;
	for (int i = 0; i < table.n_rows-1; i++){
		int pos_largestString = getLargestStringInArray(table.rows[i].data, table.n_columns);
		int size_largestString_line = strlen(table.rows[i].data[pos_largestString]);
		if(size_largestString < size_largestString_line)
			size_largestString = size_largestString_line;
	}
	//printf("inicio\n");
	
	size_largestString++;
	b_blue();
	for(int l = 0; l < table.n_columns; l++)
	{
		int actual_size = strlen(table.columns[l]);
		if(l+1 == table.n_columns){
			table.columns[l] = removeChar(table.columns[l], '\n');
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
		}else{
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}

		}
	}

	for(int l = 0; l < table.n_columns; l++)
	{
		int actual_size = strlen(table.columns[l]);
		if(l+1 == table.n_columns){
			table.columns[l] = removeChar(table.columns[l], '\n');
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf("%s |\n", table.columns[l]);
		}else if(l==0){
			printf("|");
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			printf(" %s", table.columns[l]);
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf(" |");
		}else{
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			printf(" %s", table.columns[l]);
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf(" |");
		}
	}
	resetColor();
	
	for (int i = 0; i < table.n_rows-1; i++){
		int current_pk = stringToInt(table.rows[i].data[table.pk_index]); 
		/*if(!valueIsInIntVector(pks_to_print, n_pks_to_print, current_pk)){
			continue;
		}*/
		green();
		//char** table_splited_twice = splitData(table_content_string_splited[i], ',', &table_splited_twice_size);
		int actual_stringSize;
		for (int j = 0; j < table.n_columns; j++)
		{
			
			if (j==0) {
				printf("|");
			}
			
			actual_stringSize = strlen(table.rows[i].data[j]);
			if(i==table.n_rows-1 && j==table.rows[i].n_data-1){
				for (int k = 0; k < actual_stringSize-1; k++)
				{
					printf("%c", table.rows[i].data[j][k]);
				}
				printf(" ");
			}else{
				table.rows[i].data[j] = removeChar(table.rows[i].data[j], '\n');
				printf(" %s", table.rows[i].data[j]);
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
	//printf("fim\n");
}

/*
* função: imprime a tabela com seus dados no terminal (com filtro)
* retorno: void
*/
void printTableWithFilter(Table table, int* pks_to_print, int n_pks_to_print){
	//printf("->%s\n", table.rows[0].data[0]);
	int table_content_string_splited_size;
	int size_largestString = 0;
	for (int i = 0; i < table.n_rows-1; i++){
		int pos_largestString = getLargestStringInArray(table.rows[i].data, table.n_columns);
		int size_largestString_line = strlen(table.rows[i].data[pos_largestString]);
		if(size_largestString < size_largestString_line)
			size_largestString = size_largestString_line;
	}
	//printf("inicio\n");
	
	size_largestString++;
	b_blue();
	for(int l = 0; l < table.n_columns; l++)
	{
		int actual_size = strlen(table.columns[l]);
		if(l+1 == table.n_columns){
			table.columns[l] = removeChar(table.columns[l], '\n');
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
		}else{
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}

		}
	}

	for(int l = 0; l < table.n_columns; l++)
	{
		int actual_size = strlen(table.columns[l]);
		if(l+1 == table.n_columns){
			table.columns[l] = removeChar(table.columns[l], '\n');
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf("%s |\n", table.columns[l]);
		}else if(l==0){
			printf("|");
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			printf(" %s", table.columns[l]);
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf(" |");
		}else{
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			printf(" %s", table.columns[l]);
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf(" |");
		}
	}
	resetColor();
	
	for (int i = 0; i < table.n_rows-1; i++){
		int current_pk = stringToInt(table.rows[i].data[table.pk_index]); 
		if(!valueIsInIntVector(pks_to_print, n_pks_to_print, current_pk)){
			continue;
		}
		green();
		//char** table_splited_twice = splitData(table_content_string_splited[i], ',', &table_splited_twice_size);
		int actual_stringSize;
		for (int j = 0; j < table.n_columns; j++)
		{
			
			if (j==0) {
				printf("|");
			}
			
			actual_stringSize = strlen(table.rows[i].data[j]);
			if(i==table.n_rows-1 && j==table.rows[i].n_data-1){
				for (int k = 0; k < actual_stringSize-1; k++)
				{
					printf("%c", table.rows[i].data[j][k]);
				}
				printf(" ");
			}else{
				table.rows[i].data[j] = removeChar(table.rows[i].data[j], '\n');
				printf(" %s", table.rows[i].data[j]);
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
	//printf("fim\n");
}

/*
* função: checa se uma string ocorre em determinado vetor de strings
* retorno: 1 = ocorre; 0 = não ocorre
*/
int stringIsInVector(char** vector, char* string_1, int v_size){
	//printf("string_1: %s\n", string_1);
	string_1 = removeChar(string_1, ' ');
	string_1 = removeChar(string_1, '\n');
	for(int i = 0; i < v_size; i++)
	{
		vector[i] = removeChar(vector[i], ' ');
		vector[i] = removeChar(vector[i], '\n');
		
		if (strcmp(vector[i], string_1)==0) {
			return 1;
		}
		
	}
	return 0;
}

/*
* função: imprime a tabela com seus dados no terminal (com filtro de coluna)
* retorno: void
*/
void printTableWithFilterColumns(Table table, int* pks_to_print, int n_pks_to_print, char* filter_columns){
	//printf("->%s\n", table.rows[0].data[0]);
	int n_filter_columns_vector;
	char** filter_columns_vector = split(filter_columns, ',', &n_filter_columns_vector);
	//printf("1pos: %s\n", filter_columns_vector[0]);

	int table_content_string_splited_size;
	int size_largestString = 0;
	for (int i = 0; i < table.n_rows-1; i++){
		int pos_largestString = getLargestStringInArray(table.rows[i].data, table.n_columns);
		int size_largestString_line = strlen(table.rows[i].data[pos_largestString]);
		if(size_largestString < size_largestString_line)
			size_largestString = size_largestString_line;
	}
	//printf("inicio\n");
	
	size_largestString++;
	b_blue();
	for(int l = 0; l < table.n_columns; l++)
	{
		int actual_size = strlen(table.columns[l]);
		if(l+1 == table.n_columns){
			table.columns[l] = removeChar(table.columns[l], '\n');
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
		}else{
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}

		}
	}
	//printf("n_coluns: %i\n", table.n_columns);
	int n_displayed = 0;
	for(int l = 0; l < table.n_columns; l++)
	{
		int actual_size = strlen(table.columns[l]);
		//printf("coluns: %s\n", table.columns[l]);
	
		table.columns[l] = removeChar(table.columns[l], '\n');
		while(table.columns[l][0]==' '){
			table.columns[l] = removeCharFromPosition(table.columns[l], 0);
		}
		if(!stringIsInVector(filter_columns_vector, getWordFromIndex(table.columns[l], ' ', 2), n_filter_columns_vector)){
			if(l==table.n_columns-1){
				printf("\n");
			}
			continue;
		}
		
		if (n_displayed==0 && l>0) {
			printf("|");
			n_displayed++;
		}
		

		if(l+1 == table.n_columns){
			table.columns[l] = removeChar(table.columns[l], '\n');
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf("%s  |\n", table.columns[l]);
		}else if(l==0){
			printf("|");
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			printf(" %s", table.columns[l]);
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf(" |");
		}else{
			if (actual_size>size_largestString) {
				size_largestString = actual_size;
			}
			printf(" %s ", table.columns[l]);
			while(actual_size!=size_largestString){
				printf(" ");
				actual_size++;
			}
			printf(" |");
		}
	}
	resetColor();
	
	for (int i = 0; i < table.n_rows-1; i++){
		n_displayed = 0;
		
		int current_pk = stringToInt(table.rows[i].data[table.pk_index]); 
		if(!valueIsInIntVector(pks_to_print, n_pks_to_print, current_pk)){
			continue;
		}
		green();
		//char** table_splited_twice = splitData(table_content_string_splited[i], ',', &table_splited_twice_size);
		int actual_stringSize;
		for (int j = 0; j < table.n_columns; j++)
		{
			table.columns[j] = removeChar(table.columns[j], '\n');
			if(!stringIsInVector(filter_columns_vector, getWordFromIndex(table.columns[j], ' ', 2), n_filter_columns_vector)){
				continue;
			}
			
			if (n_displayed==0 && j>0) {
				printf("|");
				n_displayed++;
			}

			if (j==0) {
				printf("|");
			}
			
			actual_stringSize = strlen(table.rows[i].data[j]);
			if(i==table.n_rows-1 && j==table.rows[i].n_data-1){
				for (int k = 0; k < actual_stringSize-1; k++)
				{
					printf("%c", table.rows[i].data[j][k]);
				}
				printf(" ");
			}else{
				table.rows[i].data[j] = removeChar(table.rows[i].data[j], '\n');
				printf(" %s", table.rows[i].data[j]);
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
	//printf("fim\n");
}

/*
* função: aplica os filtros
* retorno: vetor com as primary keys que passaram pelo filtro
*/
int* applyFilter(Table* table, char* filters, int* n_pks_to_print){
	// aplicar filtro na tabela

	// DEBUG
	//printf("filter: %s\n", filters);
	
	int n_filters, has_error = 0, n_columns = 0;
	char** splited_filters = split(filters, ' ', &n_filters);
	char** columnsName = (char**) malloc(sizeof(char*));
	char** filter_values = (char**) malloc(sizeof(char*));
	char* v_name;
	char* c_name;
	
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
				columnsName = (char**) realloc(columnsName, sizeof(char*)*(n_columns+1));
				filter_values = (char**) realloc(filter_values, sizeof(char*)*(n_columns+1));
				/*printf("c_name\n");
				printf("solited_f: %s\n", splited_filters[i]);*/
				c_name = getColumnNameFromFilter(splited_filters[i], *table);
				v_name = getValueFromFilter(splited_filters[i], c_name);
				columnsName[n_columns] = c_name;
				filter_values[n_columns] = v_name;
				//printf("v_name: %s\n", v_name);
				n_columns++;
				
				if(!filterMatchWithColumn(splited_filters[i], *table)){
					has_error = 1;
				}
			}
		}
		//printf("quebrou aqui!\n");
		
		if(has_error){
			throwError("Filtros aplicados incorretamente às colunas. Operação não executada!\n");
		}else{
			// se todos forem válidos
			int isAnd = 1, code, n_operations = 0;
			int* operations_code = (int*) malloc(sizeof(int));
			for(int i = 0; i < n_filters; i++)
			{
				if(i%2==0){
					operations_code = (int*) realloc(operations_code, sizeof(int)*(n_operations+1));
					operations_code[n_operations] = interpretFilter(splited_filters[i]);
					//printf("operation code: %i\n", operations_code[n_operations]);
					n_operations++;
				}else{
					if(strcmp(splited_filters[i], reserved_words[16])==0){
						isAnd = 1;
					}else if (strcmp(splited_filters[i], reserved_words[17])==0) {
						isAnd = 0;
					}else{
						throwError("Operador lógico inválido!");
					}
					
				}
			}
			return execOperations(operations_code, n_operations, table, columnsName, filter_values, isAnd, n_pks_to_print);
			//displayConfirmMessage("Aplicando filtros...\n");
		}
	}else{
		throwError("Filtros inválidos. Operação não executada!\n");
	}
	
}

/*
* função: recupera todas as primary keys de uma tabela
* retorno: vetor com as primary keys
*/
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

/*
* função: recupera a string entre dois índices
* retorno: string cortada
*/
char* getStringBetweenIndexes(char* text, int index_1, int index_2){
	char* cropped_string = (char*) malloc(sizeof(char));
	if(index_1<0 || index_2>=strlen(text)){
		return text;
	}

	int str_size = 0;
	for(int i = 0; i < strlen(text); i++)
	{
		if(i>index_1 && i<index_2){
			cropped_string = (char*) realloc(cropped_string, sizeof(char)*(str_size+1));
			cropped_string[str_size] = text[i];
			str_size++;
		}else if(i==index_2){
			cropped_string = (char*) realloc(cropped_string, sizeof(char)*(str_size+1));
			cropped_string[str_size] = '\0';
			return cropped_string;
		}
	}
	return cropped_string;
}

/*
* função: recupera todas as primary keys de uma tabela
* retorno: 1 = sem erros; 0 = com erros
*/
int removeTable(char* db_name, char* table_name){
	int ret_remove;
	char* path = concat("storage/", db_name);
	path = concat(path, "/\0");
	path = concat(path, table_name);
	path = concat(path, ".csv\0");

	ret_remove = remove(path);

	return ret_remove;
}