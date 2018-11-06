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