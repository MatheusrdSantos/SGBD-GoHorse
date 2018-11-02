char* getCommand(){
	// liberar espaço na memória após executar o comando free(command)
	char* command = (char*) malloc(sizeof(char));

		int i = 0;
		while(command[i-1]!='\n'){
			command=realloc(command, (sizeof(char)*i+sizeof(char)));
			command[i]=getchar();
			i++;
		}
		command[i-1]='\0';
		return command;
}
int isReserverdWord(char* word, char** reserved){
	return getWordIndex(word, reserved);
}
int validate(char* command){
	char* first_word = getFirstWord(command);
	if (isReserverdWord(first_word, reserved)!=-1)
	{
		return 1;
	}
	return 0;
}
void execute(char* command){
	printf("%i\n", validate(command)); 
}
void run(){
	while(1){
		char*command=getCommand();
		if(strcmp("exit",command)==0){
			bye();
			break;
		}
		execute(command);
	}
}