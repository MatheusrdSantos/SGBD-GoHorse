# SGBD-GoHorse
Projeto final para a  disciplina de ITP (Introdução às Técnicas de Programação) e PTP (Práticas de Técnicas de Progamação)

## Funcionalidades básica
- Criar tabela
- Listar tabelas 
- Inserir registro
- Listar todos os registros de uma tabela
- Pesquisar registro em uma tabela
- Apagar registro de uma tabela
- Apagar uma tabela

## Funcionalidades complementares

- Gerenciamento de mais de um banco de dados;
- Uso de uma sintaxe própria baseada nos comandos SQL;
   - Inclui o uso de palavras e símbolos reservados à sintaxe;
- Escolha de banco de dados padrão para que os comandos se apliquem a ele sem a necessidade de repetição do nome do mesmo;
- Comandos de seleção com filtro de colunas a serem mostradas no resultado;
- Utilização de operadores lógicos na consulta de dados (‘or’ e ‘and’);
- Utilização de datas e filtragem de registros por meio de datas;
- Exclusão por meio de filtros similares aos de seleção;
- Execução de comandos por meio de um arquivo de texto.

Para compilar digite o comando abaixo:
```
gcc main.c -o exec
```
Em determinadas versões do gcc é necessário adicionar '-std=c99':
```
gcc main.c -o exec -std=c99
```
Para executar:
```
./exec
```
Os tipos de dados suportados são: int, float, var[] e Date.
## Comandos
Abaixo estão listados os comandos necessários para utilizar o sistema.
Utilizaremos um exemplo da criação de um banco de dados para uma loja.
### Gerenciamento de bancos
Criar banco:
```
create loja
```
Listar bancos:
```
list databases
```
Escolher o banco da dados padrão:
```
set loja
```
### Gerenciamento de tabelas
Criar tabela:
```
create table produtos columns (int* id, char[255] descricao, float preco, date validade)
```
Deletar tabela:
```
delete table produtos
```
Listar tabelas:
```
list tables
```
Listar dados de uma tabela:
```
select table produtos
```

### Operações de CRUD
Inserir registro:
 ```
insert into produtos values (1, "arroz", 1.0, 10/10/2018)
```
Excluir registro:
```
delete table produtos where (descricao%h and descricao%f)
```
Recuperar registros:
```
select table produtos * where (id=1 or preco>10)
select table produtos columns (id, validade) where (id=1 or preco>10)
select table produtos columns (descricao, preco, validade) where (descricao%arroz)
```

### Comandos em arquivo externo
Para executar comandos por arquivo é necessário colocá-los no arquivo input_commands.txt. Após salvar o aquivo, basta digitar o seguinte comando no terminal:
```
input
```
Para comentar linhas no arquivo de comandos basta adicionar '/' no início da linha.
