#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_VENDAS 50

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

struct Venda {
	char categoriaProduto[30];
	int quantidade;
	float precoUnidade;
	char formaPagamento[20];
	char tipoOperacao[15];
};

struct Venda venda[MAX_VENDAS];
int qtdVendas = 0;

void tipoOperacao(int op, int vendaIndex) {
	system("cls");
	
	printf("1. Crédito.\n");
	printf("2. Débito.\n\n");
	printf("Informe o tipo de operação desejado: ");
	scanf("%d", &op);
	
	switch(op) {
		case 1:
			printf("\nVenda cadastrada com sucesso!!!\n\n");
			strcpy(venda[vendaIndex].tipoOperacao, "Crédito");
			break;
		case 2:
			printf("\nVenda cadastrada com sucesso!!!\n\n");
			strcpy(venda[vendaIndex].tipoOperacao, "Débito");
			break;
		default:
			printf("Erro! Escolha uma opção válida.\n\n");
	}
}

void formaPagamento(int op, int vendaIndex) {
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
			strcpy(venda[vendaIndex].formaPagamento, "Cartão");
			strcpy(venda[vendaIndex].tipoOperacao, "Cartão");
			tipoOperacao(op, vendaIndex);
			break;
		case 2:
			printf("\nVenda cadastrada com sucesso!!!\n\n");
			strcpy(venda[vendaIndex].formaPagamento, "Boleto");
			strcpy(venda[vendaIndex].tipoOperacao, "N/A");
			break;
		case 3:
			printf("\nVenda cadastrada com sucesso!!!\n");
			strcpy(venda[vendaIndex].formaPagamento, "Pix");
			strcpy(venda[vendaIndex].tipoOperacao, "N/A");
			break;
		case 4:
			printf("\nVenda cadastrada com sucesso!!!\n");
			strcpy(venda[vendaIndex].formaPagamento, "Dinheiro");
			strcpy(venda[vendaIndex].tipoOperacao, "N/A");
			break;
		default:
			printf("\nErro! Escolha uma opção válida!\n\n");
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
	
	fflush(stdin);
	printf("Informe a categoria do produto: ");
	fgets(venda[qtdVendas].categoriaProduto, 30, stdin);
	venda[qtdVendas].categoriaProduto[strcspn(venda[qtdVendas].categoriaProduto, "\n")] = '\0';
	
	printf("Informe a quantidade do produto: ");
	scanf("%d", &venda[qtdVendas].quantidade);
	
	printf("Informe o preço p/unidade do produto: ");
	scanf("%f", &venda[qtdVendas].precoUnidade);
	
	system("cls");
	
	formaPagamento(0, qtdVendas);
	qtdVendas++;
	
	fflush(stdin);
	printf("Deseja cadastrar mais alguma venda? (S/N)\n");
	scanf("%c", &op2);
	
	system("cls");
	} while (op2 == 'S' || op2 == 's');
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
				cadastrarVenda();
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

void listarVendas() {
	if(qtdVendas == 0) {
		printf("Não há nenhuma venda cadastrada!\n\n");
		return;
	}
	
	printf("LISTAGEM DE VENDAS\n\n");
	for(int i = 0 ; i < qtdVendas ; i++) {
		printf("Venda #%d: \n", i + 1);
		printf("Categoria: %s.\n", venda[i].categoriaProduto);
		printf("Quantidade: %d.\n", venda[i].quantidade);
		printf("Preço p/unidade: %.2f.\n\n", venda[i].precoUnidade);
		printf("Forma de pagamento: %s.\n", venda[i].formaPagamento);
    printf("Tipo de operação: %s.\n\n", venda[i].tipoOperacao);
		printf("---------------------------------\n\n");
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
				//listarProdutos();
				break;
			case 2:
				//listarClientes();
				break;
			case 3:
				//listarFuncionario();
				break;
			case 4:
				listarVendas();
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