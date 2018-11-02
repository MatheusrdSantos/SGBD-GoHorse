char* getCommand(){
	char*command = malloc(sizeof(char));

		int i=0;
		while(command[i-1]!='\n'){
			command=realloc(command, (sizeof(char)*i+sizeof(char)));
			command[i]=getchar();
			i++;
		}
		command[i-1]='\0';
		return command;
}
void run(){
	while(1){
		char*command=getCommand();
		if(strcmp("exit",command)==0){
			bye();
			break;
		}
		printf("%s\n", command);
		//validate(v);
	}
}