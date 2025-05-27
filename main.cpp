#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_CATEG 20
#define MAX_SUBCATG 5

struct Usuarios {
	char usuario[50]; 
	char genero[50]; 
	char email[50]; 
	char senha[50]; 
	int idade;
};

struct Empresa {
	char nomeEmpresa[50]; 
	char responsavel[50]; 
	int porteEmpresa;
	int tempoAtuacao;
	float rendaMensal;
	float metaLucro;
};

typedef struct {
	char nome[50];
} Subcategoria;

typedef struct {
	char nome[50];
	Subcategoria subcategorias[MAX_SUBCATG];
	int qntSubcategorias;
} Categoria;

Categoria categorias[MAX_CATEG];
int qntCategorias = 0;

void limparEnter(char atrr[100]) {
	atrr[strcspn(atrr, "\n")] = '\0';
}

//Inclus�o - fun��o de cadastrar categorias 
void cadastrarCategoria() {	
	int existe;
	char op, entradaChar[20], entrada[50];
	
	Categoria *novaCategoria = &categorias[qntCategorias];
	novaCategoria->qntSubcategorias = 0;
	
	getchar();
	
	do {
		existe = 0;
		
		printf("Informe o nome da categoria: ");
		fgets(novaCategoria->nome, sizeof(novaCategoria->nome), stdin);
		limparEnter(novaCategoria->nome);
		
		for(int i = 0; i < qntCategorias; i++) {
			if(strcmp(novaCategoria->nome, categorias[i].nome) == 0) {
				printf("\nEsta categoria j� foi cadastrada! Por favor, informe outro nome!\n");
				existe = 1;
				break;
			}
		}
	} while(existe);
	
	system("cls");
	
	do {		
		do {
			printf("| Categoria criada: %s", novaCategoria->nome);			
			printf("\n---------------------------");			
			printf("\nDeseja criar uma subcategoria para %s? (s/n): ", novaCategoria->nome);
			fgets(entradaChar, sizeof(entradaChar), stdin);
			limparEnter(entradaChar);
			
			op = tolower(entradaChar[0]);
			
			if(op != 's' && op != 'n' || strlen(entradaChar) > 1) system("cls");				
		} while(op != 's' && op != 'n' || strlen(entradaChar) > 1);
		
		if(op == 's') {			
			do {
				existe = 0;
				
				printf("\n-> Informe o nome da subcategoria: ");
				fgets(entrada, sizeof(entrada), stdin);
				limparEnter(entrada);		
				
				for(int i = 0; i < novaCategoria->qntSubcategorias; i++) {
					if(strcmp(entrada, novaCategoria->subcategorias[i].nome) == 0) {
						printf("\nEsta subcategoria j� foi cadastrada! Por favor, informe outro nome!\n");
						existe = 1;
						break;
					} 
				}
			} while(existe);
					
			if(!existe) {
				strcpy(novaCategoria->subcategorias[novaCategoria->qntSubcategorias].nome, entrada);				
				printf("\n| Subcategoria: %s criada com sucesso!\n\n", novaCategoria->subcategorias[novaCategoria->qntSubcategorias].nome);
				novaCategoria->qntSubcategorias++;					
				system("pause");
			}			
		}		
		system("cls");
	} while (op != 'n');		
	
	printf("Categoria %s criada com sucesso!\n\n", novaCategoria->nome);		
	qntCategorias++;
}

void listarCategorias() {	
	if(qntCategorias == 0) printf("Nenhuma categoria cadastrada no sistema!\n\n");		
	else {
		printf("------- Categorias Cadastradas: -------\n\n");
		
		for(int i = 0; i < qntCategorias; i++) {		
			printf("Categoria %d: %s\n", i + 1, categorias[i].nome);	
				
			for(int j = 0; j < categorias[i].qntSubcategorias; j++) {
				if(categorias[i].qntSubcategorias > 0)
					printf("\tSubcategoria %d: %s\n", j + 1, categorias[i].subcategorias[j].nome);
			}		
			printf("\n---------------------\n");
		}
	}
}

//Inclus�o - fun��o de cadastrar subcategorias 
void cadastrarSubcategoria() {
	int idCategoria, existe;
	char nomeNovaSubcat[50];
	
	if(qntCategorias == 0) 
		printf("Nenhuma categoria cadastrada no sistema! Por favor, cadastre uma categoria para poder adicionar subcategorias.\n\n");
	else {		
		for(int i = 0; i < qntCategorias; i++)
			printf("Categoria %d: %s\n", i + 1, categorias[i].nome);	
			
		do {				
			printf("\n---------------------\n\n");
			printf("Escolha uma categoria entre 1 a %d (informe apenas n�meros): ", qntCategorias);
			scanf("%d", &idCategoria);			
			
			if(idCategoria < 1 || idCategoria > qntCategorias) 
				printf("\nSelecione uma op��o v�lida!\n");
		} while(idCategoria < 1 || idCategoria > qntCategorias);		
		
		getchar();
		Categoria *novaSubcategoria = &categorias[idCategoria - 1];	
		
		do {
			existe = 0;
			
			system("cls");		
			printf("| Categoria selecionada: %s\n", novaSubcategoria->nome);			
			printf("---------------------\n");
			
			printf("Informe o nome da nova subcategoria: ");
			fgets(nomeNovaSubcat, sizeof(nomeNovaSubcat), stdin);
			limparEnter(nomeNovaSubcat);
			
			for(int i = 0; i < novaSubcategoria->qntSubcategorias; i++) {
				if(strcmp(nomeNovaSubcat, categorias[idCategoria].subcategorias[i].nome) == 0) {
					printf("\nEsta subcategoria j� foi cadastrada! Por favor, pressione enter e informe outra!\n\n");
					existe = 1;
					getchar();
					break;
				}
			}
			
			if(!existe) {
				strcpy(novaSubcategoria->subcategorias[novaSubcategoria->qntSubcategorias].nome, nomeNovaSubcat);
				novaSubcategoria->qntSubcategorias++;
				printf("\nSubcategoria criada com sucesso!\n\n");
			}
		} while(existe);		
	}
}

void menuCadastrar() {
	int op;
	
	while(1) {
		printf("| Menu - Cadastrar informa��es\n");
		printf("---------------------------\n\n");
		
		printf("1- Cadastrar nova venda\n");
		printf("2- Cadastrar cliente\n");
		printf("3- Cadastrar produto\n");
		printf("4- Cadastrar funcion�rio\n");
		printf("5- Cadastrar categoria\n");
		printf("6- Cadastrar subcategoria\n");
		printf("7- Voltar ao menu\n\n");	
		printf("-> Escolha uma op��o: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//cadastrarVenda();
				break;
			case 2:
				//cadastrarCliente();
				break;
			case 3:
				//cadastrarProduto();
				break;
			case 4:
				//cadastrarFuncionario();
				break;
			case 5:
				cadastrarCategoria();
				break;
			case 6:
				cadastrarSubcategoria();
				break;
			case 7:
				printf("Voltando para o menu painel!\n\n");
				return;
			default:
				printf("Escolha uma op��o v�lida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuListar() {
	int op;
	
	while(1) {
		printf("| Menu - Listar informa��es\n");
		printf("---------------------------\n\n");
		
		printf("1- Listar produtos\n");
		printf("2- Listar clientes\n");
		printf("3- Listar funcion�rios\n");
		printf("4- Listar vendas\n");
		printf("5- Listar categorias\n");
		printf("6- Voltar ao menu\n\n");		
		printf("-> Escolha uma op��o: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//listarProdutos();
				break;
			case 2:
				//listarClientes();
				break;
			case 3:
				//listarFuncionario();
				break;
			case 4:
				//listarVendas();
				break;
			case 5:
				listarCategorias();
				break;
			case 6:
				printf("Voltando para o menu painel!\n\n");
				return;
			default:
				printf("Escolha uma op��o v�lida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuEditar() {
	int op;
	
	while(1) {
		printf("| Menu - Editar informa��es\n");
		printf("---------------------------\n\n");
		
		printf("1- Editar venda\n");
		printf("2- Remover venda\n");
		printf("3- Voltar ao menu\n\n");
		printf("-> Escolha uma op��o: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//editarVenda();
				break;
			case 2:
				//removerVenda();
				break;
			case 3:
				printf("Voltando para o menu painel!\n\n");
				return;
			default:
				printf("Escolha uma op��o v�lida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void exibirRelatorio() {
	//para desenvolver
}

int menuPainel() {
	int op;
	
	while(1) {
		printf("| Menu Painel\n");
		printf("---------------------------\n\n");				
		
		printf("1- Cadastrar informa��es\n");				
		printf("2- Listar informa��es\n");			
		printf("3- Editar\n");		
		printf("4- Acessar relat�rio\n");		
		printf("5- Voltar ao menu\n\n");		
		printf("-> Escolha uma op��o: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				menuCadastrar();
				break;
			case 2:
				menuListar();
				break;				
			case 3:
				menuEditar();
				break;				
			case 4:
				printf("Relat�rio acessado!\n\n");
				//exibirRelatorio();
				break;				
			case 5:
				printf("Voltando para o menu!\n\n");
				return 2;
				break;					
			default:
				printf("Escolha uma op��o v�lida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void login() {
	printf("Login acessado! Redirecionando para o Menu Painel.\n\n");
	
	system("pause");	
	system("cls");	
	
	menuPainel();
}

void menuInicial() {
	int op;	
	
	while(1) {
		printf("------ Menu login/cadastro ------\n\n");
		printf("1- Login\n");
		printf("2- Cadastrar novo usu�rio\n");
		printf("3- Sair do sistema\n\n");
		printf("-> Escolha uma op��o: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				login();
				break;
			case 2:
				//cadastrar();
				break;
			case 3:
				printf("Encerrando sistema...\n\n");
				abort();				
			default:
				printf("Op��o inv�lida!!\n\n");
		}
		
		system("pause");
		system("cls");
	}
	
	if(menuPainel() == 2) menuInicial(); 
}

int main() {
	setlocale(LC_ALL, "portuguese");
	
	menuInicial();
}