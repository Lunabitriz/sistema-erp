#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_SUBCATG 6
#define MAX_CATEG 5

struct Usuarios {
	char nome[50]; 
	char genero[50]; 
	char email[50]; 
	char senha[50]; 
	int idade;
};

struct Empresa {
	char nomeEmpresa[50]; 
	int porteEmpresa; //poupa o cliente de ter que digitar muito!
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

void cadastrarCategoria() {	
	int existe;
	char op, entrada[50];
	
	Categoria *novaCategoria = &categorias[qntCategorias];
	novaCategoria->qntSubcategorias = 0;
	
	getchar();
	
	do {
		existe = 0;
		
		printf("Informe o nome da categoria: ");
		fgets(novaCategoria->nome, 50, stdin);
		limparEnter(novaCategoria->nome);
		
		for(int i = 0; i < qntCategorias; i++) {
			if(strcmp(novaCategoria->nome, categorias[i].nome) == 0) {
				printf("\nEsta categoria já foi cadastrada! Por favor, pressione enter e informe outra!\n");
				existe = 1;
				break;
			}
		}
	} while(existe);
	
	system("cls");
	
	do {
		printf("| Categoria criada: %s", novaCategoria->nome);
		printf("\n---------------------------");
		printf("\nDeseja criar uma subcategoria para %s? (s/n): ", novaCategoria->nome);
		scanf(" %c", &op);
		
		op = tolower(op);
		
		if(op == 's') {			
			existe = 0;
			
			getchar();
			printf("\n-> Informe o nome da subcategoria: ");
			fgets(entrada, 50, stdin);
			limparEnter(entrada);		
			
			for(int i = 0; i < novaCategoria->qntSubcategorias; i++) {
				if(strcmp(entrada, novaCategoria->subcategorias[i].nome) == 0) {
					printf("\nEsta subcategoria já foi cadastrada! Por favor, informe outro nome!\n");
					existe = 1;
					break;
				} 
			}
			
			if(!existe) {
				strcpy(novaCategoria->subcategorias[novaCategoria->qntSubcategorias].nome, entrada);
				printf("\nSubcategoria: %s criada com sucesso!\n", novaCategoria->subcategorias[novaCategoria->qntSubcategorias].nome);
				novaCategoria->qntSubcategorias++;					
			}
		}
		
		system("cls");
	} while (op != 'n');	
	
	printf("Categoria %s criada com sucesso!\n\n", novaCategoria->nome);		
	qntCategorias++;
}

void listarCategorias() {	
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
			printf("Escolha uma categoria entre 1 a %d (informe apenas números): ", qntCategorias);
			scanf("%d", &idCategoria);			
			
			if(idCategoria < 1 || idCategoria > qntCategorias) 
				printf("\nSelecione uma opção válida!\n");
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
					printf("\nEsta subcategoria já foi cadastrada! Por favor, pressione enter e informe outra!\n\n");
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

void menuPainel() {
	int op;
	
	while(1) {
		printf("1- Cadastrar nova venda\n");
		printf("2- Cadastrar nova categoria de produtos\n");
		printf("3- Listar vendas\n");
		printf("4- Listar categorias\n");
		printf("5- Editar venda\n");
		printf("6- Remover venda\n");
		printf("7- Acessar métricas\n");
		printf("8- Voltar ao menu\n\n");		
		printf("Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//cadastrarVenda();
				break;
			case 2:
				cadastrarCategoria();
				break;				
			case 3:
				cadastrarSubcategoria();
				//listarVendas();
				break;				
			case 4:
				listarCategorias();
				break;				
			case 5:
				//editarVenda();
				break;				
			case 6:
				//removerVenda();
				break;				
			case 7:
				//acessarRelatorio();
				break;				
			case 8:
				return;
			default:
				printf("Opção inválida!!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuInicial() {
	int op;
	
	while(1) {
		printf("1- Login\n");
		printf("2- Cadastrar novo usuário\n");
		printf("3- Sair do sistema\n\n");
		printf("Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//login();
				menuPainel();
				break;
			case 2:
				//cadastrar();
				break;
			case 3:
				printf("Encerrando sistema...\n\n");
				abort();				
			default:
				printf("Opção inválida!!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

int main() {
	setlocale(LC_ALL, "portuguese");
	
	menuInicial();
}