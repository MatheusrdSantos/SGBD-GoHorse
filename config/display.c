/*
* função: imprime informações do sistema
* retorno: void
*/
void info(){
	yellow();
	printf("GoHorse entreprise.\n");
	printf("System Version: 1.0\n");
	resetColor();
}


/*
* função: imprime mensagem de despedida
* retorno: void
*/
void bye(){
	yellow();
	printf("Bye, see you later!\n");
	resetColor();
}

/*
* função: imprime um menu de ajuda
* retorno: void
*/
void printHelp(){
	cyan();
	printf("Comandos para os bancos de dados:  \n");
	printf("	create \"nome_do_banco\": cria um banco de dados. \n");
	printf("	list databases: mostra todos os bancos criados. \n");
	printf("	set database: determina banco para relizar ações (select, insert, etc.) nele. \n\n");
	printf("Comandos para as tabelas:  \n");
	printf("	create table \"nome_da_tabela\" columns (int* \"chave_primária\", char[255] \"coluna\", float \"coluna\", date \"coluna\"): Cria tabela no banco \"setado\". \n");
	printf("	delete table \"nome_da_tabela\": exclui determinada tabela. \n");
	printf(" 	list tables: mostra todas as tabelas criadas. \n");
	printf("	select table \"nome_da_tabela\": mostra todos dados da tabela determinada. \n");
	printf("	insert into \"nome_da_tabela\" values (\"value1\", \"value2\", ..., \"valueX\"): insere valores, pela ordem, na tabela determinada. \n");
	printf("	delete table \"nome_da_tabela\" where cláusula: exclui determinadas tuplas da tabela baseando-se na cláusula. \n");
	printf("	select table professores columns (id, salaro, nome) - ou \"*\" para todas colunas - where (salario>2000.0): seleciona determinadas tuplas da tabela baseando-se na cláusula. \n");
	resetColor();
}

/*
* função: imprime um um erro
* retorno: void
*/
void throwError(char* error_message){
	red();
	printf("%s\n", error_message);
	resetColor();
}

/*
* função: imprime uma mensagem
* retorno: void
*/
void displayMessage(char* message){
	yellow();
	printf("%s\n", message);
	resetColor();
}


/*
* função: imprime um alerta
* retorno: void
*/
void displayAlertMessage(char* message){
	b_yellow();
	printf("%s\n", message);
	resetColor();
}


/*
* função: imprime uma mensagem de confirmação
* retorno: void
*/
void displayConfirmMessage(char* message){
	b_green();
	printf("%s\n", message);
	resetColor();
}