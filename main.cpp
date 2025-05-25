#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_PRODUTOS 20

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
	int qntEstoque;
	int codigoProduto;
	float precoUnidade;
	float precoCusto;
} Produtos;

Produtos listaProdutos[MAX_PRODUTOS];
int qntProdutos = 0;

void limparEnter(char atrr[100]) {
	atrr[strcspn(atrr, "\n")] = '\0';
}

void cadastrarProduto() {
	if(qntProdutos >= MAX_PRODUTOS) {
		printf("Limite de cadastro de produtos atingido!\n\n");
		return;
	}
	
	Produtos *novoProduto = &listaProdutos[qntProdutos];
	
	printf("--------- Cadastro de novo produto ---------\n\n");
	
	getchar();
	printf("Informe o nome do produto: ");
	fgets(novoProduto->nome, sizeof(novoProduto->nome), stdin);
	limparEnter(novoProduto->nome);
	
	//add categoria do produto
	//add subcategoria do produto
	
	printf("Informe a quantidade em estoque: ");
	scanf("%d", &novoProduto->qntEstoque);	
	
	printf("\nInforme o preço de venda por unidade do produto: ");
	scanf("%f", &novoProduto->precoUnidade);
	
	
	printf("Informe o preço de custo por unidade do produto: ");
	scanf("%f", &novoProduto->precoCusto);
	
	printf("\nInforme o código do produto (Ex: 0012): ");
	scanf("%d", &novoProduto->codigoProduto);			
	
	printf("\nProduto adicionado com sucesso!!\n\n");
	qntProdutos++;
}

void listarProdutos() {	
	if(qntProdutos == 0) {
		printf("Nenhum produto cadastrado no sistema!\n\n");
		return;
	}
		
	printf("----------- Produtos cadastrados -----------\n\n");
	
	for(int i = 0; i < qntProdutos; i++) {
		printf("| Produto %d: \n\n", i + 1);
		
	 	printf("Nome do produto: %s\n", listaProdutos[i].nome);
	 	printf("Preço de custo (unidade): R$%.2f\n", listaProdutos[i].precoCusto);
	 	printf("Preço de venda (unidade): R$%.2f\n", listaProdutos[i].precoUnidade);
	 	printf("Quantidade em estoque: %d\n", listaProdutos[i].qntEstoque);
	 	printf("Código do produto: %d\n", listaProdutos[i].codigoProduto);	 	
	 	printf("\n---------------------\n");
	}
}

void menuCadastrar() {
	int op;
	
	while(1) {
		printf("| Menu - Cadastrar informações\n");
		printf("---------------------------\n\n");
		
		printf("1- Cadastrar nova venda\n");
		printf("2- Cadastrar cliente\n");
		printf("3- Cadastrar produto\n");
		printf("4- Cadastrar funcionário\n");
		printf("5- Cadastrar categoria\n");
		printf("6- Cadastrar subcategoria\n");
		printf("7- Voltar ao menu\n\n");	
		printf("-> Escolha uma opção: ");
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
				cadastrarProduto();
				break;
			case 4:
				//cadastrarFuncionario();
				break;
			case 5:
				//cadastrarCategoria();
				break;
			case 6:
				//cadastrarSubcategoria();
				break;
			case 7:
				printf("Voltando para o menu painel!\n\n");
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuListar() {
	int op;
	
	while(1) {
		printf("| Menu - Listar informações\n");
		printf("---------------------------\n\n");
		
		printf("1- Listar produtos\n");
		printf("2- Listar clientes\n");
		printf("3- Listar funcionários\n");
		printf("4- Listar vendas\n");
		printf("5- Listar categorias\n");
		printf("6- Voltar ao menu\n\n");		
		printf("-> Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				listarProdutos();
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
				//listarCategorias();
				break;
			case 6:
				printf("Voltando para o menu painel!\n\n");
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuEditar() {
	int op;
	
	while(1) {
		printf("| Menu - Editar informações\n");
		printf("---------------------------\n\n");
		
		printf("1- Editar venda\n");
		printf("2- Remover venda\n");
		printf("3- Voltar ao menu\n\n");
		printf("-> Escolha uma opção: ");
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
				printf("Escolha uma opção válida!\n\n");
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
		
		printf("1- Cadastrar informações\n");				
		printf("2- Listar informações\n");			
		printf("3- Editar\n");		
		printf("4- Acessar relatório\n");		
		printf("5- Voltar ao menu\n\n");		
		printf("-> Escolha uma opção: ");
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
				printf("Relatório acessado!\n\n");
				//exibirRelatorio();
				break;				
			case 5:
				printf("Voltando para o menu!\n\n");
				return 2;
				break;					
			default:
				printf("Escolha uma opção válida!\n\n");
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
		printf("2- Cadastrar novo usuário\n");
		printf("3- Sair do sistema\n\n");
		printf("-> Escolha uma opção: ");
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
				printf("Opção inválida!!\n\n");
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