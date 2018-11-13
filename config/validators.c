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
	return isReserverdWord(first_word, reserved_words);
	
}
void execute(char* command){
	int command_index = validate(command);
	if (command_index == -1)
	{
	 	printf("Comando \"%s\" não reconhecido!\n", getFirstWord(command));
	}else{
		// após identificação do comando executa-o
		if (command_index==0)
		{
			printHelp();
		}else if(command_index == 1){
			exec_create(command);
		}else if(command_index == 2){
			//exec_delete(command);
		}else if(command_index == 3){
			//exec_select(command);
		}else if(command_index == 4){
			exec_set(command);
		}else if(command_index == 5){
			exec_list(command);
		}else if(command_index == 6){
			//exec_insert(command);
		}else if(command_index == 7){
			//exec_add(command);
		}
		printf("Executando operação \"%s\"\n", reserved_words[command_index]);
	}
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