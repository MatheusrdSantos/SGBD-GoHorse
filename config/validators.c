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
int isReserverWord(char* word){

}
int validate(char* command){
	char* first_word = getFirstWord(command);
	return 1;
}
void execute(char* command){
	validate(command);
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