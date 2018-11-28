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

int exec_input_file(){
	FILE* input;
	input = fopen("input_commands.txt", "rb");

	if (input == NULL)
	{
		throwError("Erro na abertura do arquivo!\n");
		return 0;
	}

	fseek(input, 0, SEEK_END);
	int table_content_string_size = ftell(input);
	fseek(input, 0, SEEK_SET);  //mesmo que rewind(f);
	
	char* table_content_string = (char*) malloc(table_content_string_size + 1);
	fread(table_content_string, table_content_string_size, 1, input);

	table_content_string[table_content_string_size] = '\0';
	//printf("content size: %i\n", table_content_string_size);
	//printf("%s\n", table_content_string);
	fclose(input);


	/*int table_content_splited_size;
	char** table_content_splited = split(table_content_string, '\n', &table_content_splited_size);
	printf("size: %i\n", table_content_splited_size);
	printf("%s-", table_content_splited[0]);*/
	/*for(int i = 0; i < table_content_splited_size; i++)
	{
		printf("%s-", table_content_splited[i]);
		execute(concat(table_content_splited[i], "\n"));
	}*/
	int i = 0;
	while(table_content_string[i]!='\0' && i<table_content_string_size){
		char* command = (char*) malloc(sizeof(char));
		int j = 0, commented_line = 0;
		while(table_content_string[i]!='\n' && table_content_string[i]!='\0'){
			
			if (j==0) {
				
				if (table_content_string[i]=='/') {
					commented_line = 1;
				}
				
			}
			if(!commented_line){
				command = (char*) realloc(command, sizeof(char)*(j+2));
				command[j] = table_content_string[i];
			}
			i++;
			j++;
		}
		if(!commented_line){
			if(command[j] == '\0'){
				//printf("input command: %s limit\n", command);
				execute(command);
			}else{	
				command[j] = '\0';
				//printf("char: %c, i: %i\n", command[j-1], i);
				//command = removeCharFromPosition(command, j-1);
				//printf("input command: %s limit\n", command);
				execute(command);
			}
		}
		i++;
	}
	
	return 1;
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
			exec_delete(command);
		}else if(command_index == 3){
			exec_select(command);
		}else if(command_index == 4){
			exec_set(command);
		}else if(command_index == 5){
			exec_list(command);
		}else if(command_index == 6){
			exec_insert(command);
		}else if(command_index == 7){
			//exec_add(command);
		}else if(command_index == 18){
			exec_input_file();
		}
		printf("Executada a operação \"%s\"\n", reserved_words[command_index]);
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