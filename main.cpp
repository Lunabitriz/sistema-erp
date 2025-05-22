#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_VENDAS 5

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

struct Venda {
	char categoriaProduto[30];
	int quantidade;
	float precoUnidade;
};

struct Venda venda[MAX_VENDAS];
int qtdVendas = 0;

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
void tipoOperacao(int op) {
	system("cls");
	
	printf("1. Crédito.\n");
	printf("2. Débito.\n\n");
	printf("Informe o tipo de operação desejado: ");
	scanf("%d", &op);
	
	printf("\nVenda cadastrada com sucesso!!!\n\n");
}

void formaPagamento(int op) {
	int op2;
	
	system("cls");
	
	printf("1- Cartão.\n");
	printf("2- Boleto.\n");
	printf("3- Pix.\n");
	printf("4- Dinheiro.\n\n");
	printf("Informe a forma de pagamento: ");
	scanf("%d", &op);
	
	switch(op) {
		case 1:
			tipoOperacao(op2);
			break;
		case 2:
			printf("\nVenda cadastrada com sucesso!!!\n\n");
			break;
		case 3:
			printf("\nVenda cadastrada com sucesso!!!\n");
			break;
		case 4:
			printf("\nVenda cadastrada com sucesso!!!\n");
			break;
		default:
			printf("\nEscolha uma opção válida!\n\n");
	}
}

void cadastrarVenda() {
	char op2;
	
	do {
	int op;
	char novaCategoria[30];
	
	if(qtdVendas >= MAX_VENDAS) {
		printf("Limite de cadastro de vendas atingido!!!\n\n");
		return;
	}
	
	while(1) {
		fflush(stdin);
		printf("Informe a categoria do produto: ");
		fgets(novaCategoria, 30, stdin);
		novaCategoria[strcspn(novaCategoria, "\n")] = '\0';
	
		int categoriaExistente = 0;
		for (int i = 0 ; i < qtdVendas ; i++) {
			if (strcmp(venda[i].categoriaProduto, novaCategoria) == 0) {
				categoriaExistente = 1;
				break;
			}
		}
	
		if(categoriaExistente) {
			printf("Esta categoria já existe! Tente novamente.\n\n");
		} else {
			strcpy(venda[qtdVendas].categoriaProduto, novaCategoria);
			break;
		}
	}
	
	printf("Informe a quantidade do produto: ");
	scanf("%d", &venda[qtdVendas].quantidade);
	
	printf("Informe o preço p/unidade do produto: ");
	scanf("%f", &venda[qtdVendas].precoUnidade);
	
	system("cls");
	
	qtdVendas++;
	
	formaPagamento(op);
	
	fflush(stdin);
	printf("Deseja cadastrar mais alguma venda? (S/N)\n");
	scanf("%c", &op2);
	
	system("cls");
	} while (op2 == 'S' || op2 == 's');
}

void menuPainel() {
	int op;
	
	while(1) {
		printf("1- Cadastrar nova venda.\n");
		printf("2- Cadastrar categoria de produtos.\n");
		printf("3- Cadastrar sub-categoria de produtos.\n");
		printf("4- Cadastrar funcionário.\n");
		printf("5- Listar funcionários.\n");
		printf("6- Listar vendas.\n");
		printf("7- Listar categorias e sub-categorias.\n");
		printf("8- Editar venda.\n");
		printf("9- Remover venda.\n");
		printf("10- Acessar métricas.\n");		
		printf("11- Voltar ao menu.\n\n");		
		printf("Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				cadastrarVenda();
				break;
			case 2:
				//cadastrarCategoria();
				break;				
			case 3:
				//cadastrarSubCategoria();
				break;				
			case 4:
				//cadastrarFuncionario();
				break;				
			case 5:
				//listarFuncionarios();
				break;				
			case 6:
				//listarVendas();
				break;				
			case 7:
				//listarCategorias();
				break;								
			case 8:
				//editarVenda();
				break;				
			case 9:
				//removerVenda();
				break;				
			case 10:
				//acessarMetricas();
				break;				
			case 11:
				//voltarMenu();
				break;				
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}


int main() {
	setlocale(LC_ALL, "portuguese");
	
	//menuInicial();
	menuPainel();
}