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
	
}