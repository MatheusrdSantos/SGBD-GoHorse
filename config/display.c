void info(){
	yellow();
	printf("GoHorse entreprise.\n");
	printf("System Version: 1.0\n");
	resetColor();
}
void bye(){
	yellow();
	printf("Bye, see you later!\n");
	resetColor();
}
void printHelp(){
	cyan();
	printf("Comandos para os bancos de dados:  \n");
	printf("(80%%) Create \"nome_do_banco\": cria um banco de dados. \n");
	printf("(0%%)  Delete \"nome_do_banco\": exclui determinado banco de dados. \n");
	printf("(90%%) List databases: mostra todos os bancos criados. \n");
	printf("(0%%)  Set database: determina banco para relizar ações (select, insert, etc.) nele. \n\n");
	printf("Comandos para as tabelas:  \n");
	printf("(0%%)  Create table \"nome_da_tabela\" columns (int *\"chave_primária\", varchar[255] \"coluna\", float \"coluna\", date \"coluna\"): Cria tabela no banco \"setado\". \n");
	printf("(0%%)  Delete table \"nome_da_tabela\": exclui determinada tabela. \n");
	printf("(80%%) List tables: mostra todas as tabelas criadas. \n");
	printf("(0%%)  Select table \"nome_da_tabela\": mostra todos dados da tabela determinada. \n");
	printf("(0%%)  Insert into \"nome_da_tabela\" values (\"value1\", \"value2\", ..., \"valueX\"): insere valores, pela ordem, na tabela determinada. \n");
	printf("(0%%)  Delete from \"nome_da_tabela\" where cláusula: exclui determinadas tuplas da tabela baseando-se na cláusula. \n");
	printf("(0%%)  Select \"coluna1\", \"coluna2\", ..., \"colunaX\" from \"nome_da_tabela\" where cláusula: seleciona determinadas tuplas da tabela baseando-se na cláusula. \n");
	resetColor();
}
void throwError(char* error_message){
	red();
	printf("%s\n", error_message);
	resetColor();
}
void displayMessage(char* message){
	yellow();
	printf("%s\n", message);
	resetColor();
}
void displayConfirmMessage(char* message){
	green();
	printf("%s\n", message);
	resetColor();
}