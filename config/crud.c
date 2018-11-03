char* exec_list(char* command){
	if(strcmp(command, "list tables") == 0){
		green();
		printf("Você solicitou listar as tabelas.\n");
		resetColor();

		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir ("storage/db1/")) != NULL) {
		//printa todos os arquivos e pastas dentro do diretório
			while ((ent = readdir (dir)) != NULL) {
				printf ("%s\n", ent->d_name);
			}
			closedir (dir);
		} else {
		  	perror ("Não há tabelas criadas.");
		  	return 0;
		}

	}else if(strcmp(command, "list databases") == 0){
		green();
		printf("Você solicitou listar os bancos.\n");
		resetColor();

		DIR *dir;
		struct dirent *ent;
		if ((dir = opendir ("storage/")) != NULL) {
		//printa todos os arquivos e pastas dentro do diretório
			while ((ent = readdir (dir)) != NULL) {
				printf ("%s\n", ent->d_name);
			}
			closedir (dir);
		} else {
	  		perror ("Não há databases criados.");
	  		return 0;
		}

	}else{
		red();
		printf("Esse comando não existe, tente 'list tables' ou 'list databases'.\n");
		resetColor();

	}
}