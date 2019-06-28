#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

//estrutura para representar cada livro do acervo.
typedef struct{
	char titulo[100];
	char editora[30];
	char autor[60];
	char genero[30];
	char encadernacao[30];
	short ano;
	short edicao;
	int paginas;
	int regnum;
	float preco;
} Livro;

// ponteiro que lidará com a escrita e a leitura do arquivo de backup do acervo. (global)
FILE * arquivo;
// matriz que representará o acervo. (global)
Livro * acervo;
int indice = 0; // indice é um inteiro que representa qual é o próximo índice a ser inserido na matriz. (global)
int ultimo_regnum = 0; //inteiro que guardará o último número registro dos livros. Para não ter livros com o mesmo ID. (global)

//funcão que limpa a tela.
void limpar_tela(){
	system("clear||cls");
}
//funcão que tranforma uma string para a sua equivalente em UPPERCASE.
char * strtoupper(char * string ,int n){
	char * retorno = (char *)malloc(sizeof(char) * (n + 1));
	for(int i = 0; i <= n; i++){
		retorno[i] = toupper(string[i]);
	}

	retorno[n+1] = '\0';
	return retorno;
}
//função que imprime o menu principal e captura a entrada do usuário.
char menu_principal(){
	printf("*******************\n");
	printf("SISTEMA - LIVRARIA\n");
	printf("*******************\n");
	printf("\n'A' para adicionar um livro.\n");
	printf("\n'R' para remover um livro.\n");
	printf("\n'I' para imprimir todos os livros.\n");
	printf("\n'T' para busca por título.\n");
	printf("\n'C' para busca por código.\n");
	printf("\n'S' para sair.\n");

	printf(">> ");
	char escolha;
	scanf(" %c", &escolha);

	return toupper(escolha);
}
//função que percorre a matriz de acervo e salva a sua equivalente no arquivo. 
void salvar_arquivo(){
	arquivo = fopen("acervo.dat", "w");
	for(int i = 0; i < indice; i++){
		fprintf(arquivo, "%s||%s||%s||%s||%s||%hd||%d||%d||%d||%f\n", acervo[i].titulo, 
				acervo[i].editora, 
				acervo[i].autor, 
				acervo[i].genero, 
				acervo[i].encadernacao,
				acervo[i].ano,
				acervo[i].edicao,
				acervo[i].paginas,
				acervo[i].regnum,
				acervo[i].preco);
	}
	fclose(arquivo);
}
//função chamada no início da execução para recuperar a matriz através do arquivo. 
void carregar_livros(){
	arquivo = fopen("acervo.dat", "r"); 

	if (arquivo == NULL){
		fclose(arquivo);
		arquivo = fopen("acervo.dat", "w"); //caso o arquivo não exista (r), ele será criado (w).
		fclose(arquivo);
		return;
	}

	char * linha = NULL;
	size_t tamanho = 0;
	ssize_t check;

	acervo = (Livro *)malloc(sizeof(Livro));
	if (acervo == NULL){
		printf("Erro ao alocar memoria.\n");
		exit(1);
	}

	char titulo[100];
	char editora[30];
	char autor[60];
	char genero[30];
	char encadernacao[30];
	short ano;
	short edicao;
	short paginas;
	int regnum;
	float preco;

	while ((check = getline(&linha, &tamanho, arquivo)) != -1) { // enquanto o check for diferente de -1, continua lendo linha a linha do arquivo.
		sscanf(linha, "%[^||]||%[^||]||%[^||]||%[^||]||%[^||]||%hd||%hd||%hd||%d||%f", titulo, editora, autor, genero, encadernacao, &ano, &edicao, &paginas, &regnum, &preco); // %[^||]|| <- (expressão regular) ler até o separador, depois ignorá-lo.
		//printf("%s\n%s\n%s\n%s\n%s\n%hd\n%hd\n%hd\n%d\n%f\n", titulo, editora, autor, genero, encadernacao, ano, edicao, paginas, regnum, preco);
		strcpy(acervo[indice].titulo, titulo);
		strcpy(acervo[indice].editora, editora);
		strcpy(acervo[indice].autor, autor);
		strcpy(acervo[indice].genero, genero);
		strcpy(acervo[indice].encadernacao, encadernacao);
		acervo[indice].ano = ano;
		acervo[indice].edicao = edicao;
		acervo[indice].paginas = paginas;
		acervo[indice].regnum = regnum;
		acervo[indice].preco = preco;
		indice++;
		ultimo_regnum = regnum;
		acervo = (Livro *)realloc(acervo, sizeof(Livro) * (indice + 1));
		if (acervo == NULL){
			printf("Erro ao alocar memoria.\n");
			exit(1);
		}
	}

	fclose(arquivo);
}
//função que adiciona um livro.
void adicionar_livro(){
	char titulo[100];
	char editora[30];
	char autor[60];
	char genero[30];
	char encadernacao[30];
	short ano;
	short edicao;
	short paginas;
	int regnum;
	float preco;

	printf("Titulo: ");
	fgets(titulo, 100, stdin);
	strtok(titulo, "\n"); //remove o \n da string.

	printf("Editora: ");
	fgets(editora, 30, stdin);
	strtok(editora, "\n");

	printf("Autor(a): ");
	fgets(autor, 60, stdin);
	strtok(autor, "\n");

	printf("Gênero: ");
	fgets(genero, 30, stdin);
	strtok(genero, "\n");

	printf("Encadernação: ");
	fgets(encadernacao, 30, stdin);
	strtok(encadernacao, "\n");

	printf("Ano: ");
	scanf("%hu", &ano);
	printf("Edição: ");
	scanf("%hu", &edicao);
	printf("Páginas: ");
	scanf("%hu", &paginas);
	ultimo_regnum++;
	regnum = ultimo_regnum;
	printf("Preço: ");
	scanf("%f", &preco);	

	strcpy(acervo[indice].titulo, titulo);
	strcpy(acervo[indice].editora, editora);
	strcpy(acervo[indice].autor, autor);
	strcpy(acervo[indice].genero, genero);
	strcpy(acervo[indice].encadernacao, encadernacao);
	acervo[indice].ano = ano;
	acervo[indice].edicao = edicao;
	acervo[indice].paginas = paginas;
	acervo[indice].regnum = regnum;
	acervo[indice].preco = preco;
	indice++;
	acervo = (Livro *)realloc(acervo, sizeof(Livro) * (indice + 1));
	if (acervo == NULL){
		printf("Erro ao alocar memoria.\n");
		exit(1);
	}
	//chama função para sobrescrever o arquivo com a matriz atualizada com o novo livro
	salvar_arquivo();
}
//função que remove livros.
void remover_livro(){
	int codigo, i, j;
	char escolha;
	printf("Código: ");
	scanf("%d", &codigo);
	getchar();
	for(i = 0; i < indice; i++){
		if(acervo[i].regnum == codigo){
			break;
		}
		if(i == indice - 1){
			printf("Código não encontrado.\n");
			return;
		}
	}

	printf("Deseja realmente remover '%s' [s/N]: ", acervo[i].titulo);
	escolha = getchar();
	getchar();

	if(escolha == 's'){
		for(j = i; j < indice - 1; j++){ //caso o livro seja removido, todos os seus sucessores são movidos uma casa para trás.
			acervo[j] = acervo[j + 1];
		}

		indice--;
		acervo = (Livro *)realloc(acervo, sizeof(Livro) * (indice));
		salvar_arquivo();
		printf("Removido.\n");
	}else{
		printf("Saindo.\n");
		return;
	}	
}
void imprimir_livros(){
	for(int i = 0; i < indice; i++){
		printf("*******************************************************************************\n");
		printf("Titulo: %s\n", acervo[i].titulo);
		printf("Editora: %s\n", acervo[i].editora);
		printf("Autor: %s\n", acervo[i].autor);
		printf("Gênero: %s\n", acervo[i].genero);
		printf("Encadernação: %s\n", acervo[i].encadernacao);
		printf("Ano: %hd\n", acervo[i].ano);
		printf("Edição: %hd\n", acervo[i].edicao);
		printf("Nro de Páginas: %hd\n", acervo[i].paginas);
		printf("Código: %d\n", acervo[i].regnum);
		printf("Preço: %.2f\n", acervo[i].preco);
		printf("*******************************************************************************\n");
	}
}
void buscar_titulo(){
	int i;
	char titulo[100];
	printf("Insire o título ou parte dele: ");
	fgets(titulo, 100, stdin);
	strtok(titulo, "\n");
	int encontrado = 0;
	printf("Livros encontrados para sua busca: \n");
	for(i = 0; i < indice; i++){
		//strstr ver se o título é uma substring de um titulo dentro do acervo.
		if(strstr(strtoupper(acervo[i].titulo, strlen(acervo[i].titulo)), strtoupper(titulo, strlen(titulo))) != NULL){
			printf("*******************************************************************************\n");
			printf("Titulo: %s\n", acervo[i].titulo);
			printf("Editora: %s\n", acervo[i].editora);
			printf("Autor: %s\n", acervo[i].autor);
			printf("Gênero: %s\n", acervo[i].genero);
			printf("Encadernação: %s\n", acervo[i].encadernacao);
			printf("Ano: %hd\n", acervo[i].ano);
			printf("Edição: %hd\n", acervo[i].edicao);
			printf("Nro de Páginas: %hd\n", acervo[i].paginas);
			printf("Código: %d\n", acervo[i].regnum);
			printf("Preço: %.2f\n", acervo[i].preco);
			printf("*******************************************************************************\n");
			encontrado = 1;
		}
		if(i == indice - 1 && encontrado == 0){
			printf("Livro não encontrado.\n");
			return;
		}
	}
}
//fução de busca por código
void buscar_codigo(){
	int i, codigo;
	printf("Insira o código do livro: ");
	scanf("%d", &codigo);
	getchar();
	for(i = 0; i < indice; i++){
		if(acervo[i].regnum == codigo){
			printf("Titulo: %s\n", acervo[i].titulo);
			printf("Editora: %s\n", acervo[i].editora);
			printf("Autor: %s\n", acervo[i].autor);
			printf("Gênero: %s\n", acervo[i].genero);
			printf("Encadernação: %s\n", acervo[i].encadernacao);
			printf("Ano: %hd\n", acervo[i].ano);
			printf("Edição: %hd\n", acervo[i].edicao);
			printf("Nro de Páginas: %hd\n", acervo[i].paginas);
			printf("Código: %d\n", acervo[i].regnum);
			printf("Preço: %.2f\n", acervo[i].preco);
			break;
		}
		if(i == indice - 1){
			printf("Livro não encontrado.\n");
			return;
		}
	}
}
//função que libera a memória utilizada pelo acervo e fecha o programa.
void sair(){
	free(acervo);
	printf("Adeus.\n");
	exit(0); // fechar programa sem nenhum aviso de erro.
}

//função principal que chama as funções declaradas acima.
int main(){
	char escolha;
	carregar_livros(); // primeira função a ser chamada, lê o arquivo e alimenta a matriz, salva na momória durante o tempo de execução do programa.

	while (1){
		escolha = menu_principal();
		getchar();
		switch(escolha){
			case 'A': adicionar_livro(); break;
			case 'R': remover_livro(); break;
			case 'I': imprimir_livros(); break;
			case 'T': buscar_titulo(); break;
			case 'C': buscar_codigo(); break;
			case 'S': sair(); break;
			default: printf("Comando não encontrado.\n");			
		}
		printf("..");
		getchar();
		limpar_tela();
	}
}
