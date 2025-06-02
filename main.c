#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <ctype.h>

#define MAX_CATEG 20
#define MAX_SUBCATG 5
#define MAX_PRODUTOS 20
#define MAX_VENDAS 20
#define MAX_CLIENTES 20

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

typedef struct {
	char nome[50];
	int qntEstoque;
	int codigoProduto;
	int idxCategoria;
	int qntCategorias;
	int idxSubcategoria;
	float precoUnidade;
	float precoCusto;
} Produtos;

struct Venda {
	char nomeProduto[30];
	int quantidade;
	float precoUnidade;
	char formaPagamento[20];
	char tipoOperacao[15];
	
	int idClienteFiado;
	float valorDevido;
};

struct Cliente {
    char nome[50];
    char cpf[12];
    char email[50];
    int idade[20];
    
    char nomeClienteFiado[30];
};

Produtos produtos[MAX_PRODUTOS];
Categoria categorias[MAX_CATEG];
struct Venda venda[MAX_VENDAS];
struct Cliente clientes[MAX_CLIENTES];
int qntCategorias = 0;
int qntProdutos = 0;
int qntVendas = 0;
int totalClientes = 0;

void limparEnter(char atrr[]) {
	atrr[strcspn(atrr, "\n")] = '\0';
}

void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void limparTela() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }
    return 1;
}

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    printf("---- Cadastro de Cliente ----\n\n");

		fflush(stdin);
    printf("Informe seu nome: ");
    fgets(clientes[totalClientes].nome, sizeof(clientes[totalClientes].nome), stdin);
    clientes[totalClientes].nome[strcspn(clientes[totalClientes].nome, "\n")] = '\0';

    // CPF
do {
    printf("Informe seu CPF: ");
    fgets(clientes[totalClientes].cpf, sizeof(clientes[totalClientes].cpf), stdin);
    clientes[totalClientes].cpf[strcspn(clientes[totalClientes].cpf, "\n")] = '\0';

    if (!validarCPF(clientes[totalClientes].cpf)) {
        printf("\nCPF inválido! Deve conter 11 dígitos numericos.\n");
    } else {
        break;
    }
} while (1);


fflush(stdin);
   // Email
   printf("Informe seu e-mail: ");
   fgets(clientes[totalClientes].email, sizeof(clientes[totalClientes].email), stdin);
   clientes[totalClientes].email[strcspn(clientes[totalClientes].email, "\n")] = '\0';

   // Garante que não há lixo no buffer antes de scanf
   printf("Informe sua idade: ");
  while (1) {
    char entrada[10];
    fgets(entrada, sizeof(entrada), stdin);
    if (sscanf(entrada, "%d", &clientes[totalClientes].idade) == 1 && clientes[totalClientes].idade > 0) {
        break;
    } else {
        printf("Idade inválida. Tente novamente: ");
    }
}

    totalClientes++;
    //salvarClientesEmArquivo();
    printf("\nCliente cadastrado com sucesso!\n\n");
}

void listarClientes() {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    printf("------- Lista de Clientes: -------\n\n");
    for (int i = 0; i < totalClientes; i++) {
        printf("Cliente %d:\n", i + 1);
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Email: %s\n", clientes[i].email);
        printf("Idade: %d\n", clientes[i].idade);
        printf("----------------------------\n");
    }
}

int somenteReais(char str[]) {
    int temPonto = 0;
    
    if(str[0] == '\0') return 0;
    
    for(int i = 0; str[i] != '\0'; i++) {
        if(str[i] == '.') {
            if(temPonto) return 0;
                
            temPonto = 1;
        } else if (str[i] < '0' || str[i] > '9') return 0;
    }
    
    return 1;
}

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
				printf("\nEsta categoria já foi cadastrada! Por favor, informe outro nome!\n");
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
						printf("\nEsta subcategoria já foi cadastrada! Por favor, informe outro nome!\n");
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

void cadastrarSubcategoria() {
	int idCategoria, existe;
	char nomeNovaSubcat[50];
	
	if(qntCategorias == 0) 
		printf("Nenhuma categoria cadastrada no sistema! Por favor, cadastre uma categoria para poder adicionar subcategorias.\n\n");
	else {		
		for(int i = 0; i < qntCategorias; i++)
			printf("Categoria %d: %s\n", i + 1, categorias[i].nome);	
			
		do {				
			printf("---------------------\n\n");
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
				if(strcmp(nomeNovaSubcat, categorias[idCategoria - 1].subcategorias[i].nome) == 0) {
					printf("\nEsta subcategoria já foi cadastrada! Por favor, pressione enter e informe outro nome!\n\n");
					existe = 1;
					getchar();
					break;
				}
			}
			
			if(!existe) {
				strcpy(novaSubcategoria->subcategorias[novaSubcategoria->qntSubcategorias].nome, nomeNovaSubcat);
				novaSubcategoria->qntSubcategorias++;
				printf("\nSubcategoria %s criada com sucesso!\n\n", nomeNovaSubcat);
			}
		} while(existe);		
	}
}

void cadastrarProduto() {
	if(qntProdutos == MAX_PRODUTOS) {
		printf("Limite de cadastro de produtos atingido!\n\n");
		return;
	}
	
	Produtos *novoProd = &produtos[qntProdutos];
	char entrada[20];
	
	getchar();
	printf("Informe o nome do produto: ");
	fgets(novoProd->nome, sizeof(novoProd->nome), stdin);
	limparEnter(novoProd->nome);
	
	//listar categorias	
	
	if(qntCategorias > 0) {
		int idxCategoria, idxSubcategoria;
		novoProd->qntCategorias = 0;

		printf("\n| Categorias cadastradas:\n");
		
		for(int i = 0; i < qntCategorias; i++)
			printf("\tCategoria %d: %s\n", i + 1, categorias[i].nome);
		
		do {
			printf("\nSelecione a categoria do produto (de 1 a %d): ", qntCategorias);
			scanf("%d", &idxCategoria);				
		} while(idxCategoria < 1 || idxCategoria > qntCategorias);
		
		novoProd->idxCategoria = idxCategoria - 1;
		Categoria *categoriaSelecionada = &categorias[novoProd->idxCategoria];
		
		if(categoriaSelecionada->qntSubcategorias > 0) {
			printf("\n| Subcategorias cadastradas:\n");
			
			for(int i = 0; i < categoriaSelecionada->qntSubcategorias; i++)
				printf("\tSubcategoria %d: %s\n", i + 1, categoriaSelecionada->subcategorias[i].nome);
			
			do {
				printf("\nSelecione a subcategoria: ");
				scanf("%d", &idxSubcategoria);	
			} while(idxSubcategoria < 1 || idxSubcategoria > categoriaSelecionada->qntSubcategorias);
			
			novoProd->idxSubcategoria = idxSubcategoria - 1;
		}
		
		novoProd->qntCategorias++;
		printf("---------------------\n");
		getchar();
	}	
	
	do {
		printf("\nInforme o preço de custo do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));
	
	novoProd->precoCusto = atof(entrada);
	
	do {
		printf("Informe o preço de venda do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));
	
	novoProd->precoUnidade = atof(entrada);	
	
	do {
		printf("\nInforme a quantidade em estoque: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));
	
	novoProd->qntEstoque = atof(entrada);	
	
	do {
		printf("Informe o código do produto (ex: 1234): ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));	
	
	novoProd->codigoProduto = atof(entrada);
	
	printf("\n| Produto cadastrado com sucesso!!\n\n");
	qntProdutos++;
}

void listarProdutos() {
	if(qntProdutos == 0) {
		printf("Não há produtos cadastrados no estoque!\n\n");
		return;
	}
	
	printf("--------- Produtos cadastrados: ---------\n\n");
	for(int i = 0; i < qntProdutos; i++) {
		printf("| Produto %d:\n\n", i + 1);
		
		printf("\tCódigo do produto: %d\n", produtos[i].codigoProduto);
		printf("\tNome do produto: %s\n", produtos[i].nome);
		printf("\tPreço de custo: R$%.2f\n", produtos[i].precoCusto);
		printf("\tPreço de venda: R$%.2f\n", produtos[i].precoUnidade);		
		printf("\tQuantidade em estoque: %d\n", produtos[i].qntEstoque);
		
		if(produtos[i].qntCategorias > 0)
			printf("\tCategorias do produto: %s\n", categorias[produtos[i].idxCategoria]);
		else
			printf("\tCategorias do produto: não informado\n");
			
		if(categorias[produtos[i].idxCategoria].qntSubcategorias > 0)
			printf("\tSubcategorias do produto: %s\n", categorias[produtos[i].idxCategoria].subcategorias[produtos[i].idxSubcategoria].nome);
		else 
			printf("\tSubcategorias do produto: não informado\n");
			
		printf("\n------------------------\n");
	}
}

void listarVendas() {
	if(qntVendas == 0) {
		printf("Não há nenhuma venda cadastrada!\n\n");
		return;
	}
	
	printf("--------- Listagem de vendas: ---------\n\n");
	for(int i = 0 ; i < qntVendas ; i++) {
		printf("| Venda %d: \n", i + 1);
		printf("\tQuantidade: %d\n", venda[i].quantidade);
		printf("\tForma de pagamento: %s\n", venda[i].formaPagamento);
		
		if (strcmp(venda[i].formaPagamento, "Cartão") == 0) {
      printf("\tTipo de operação: %s\n", venda[i].tipoOperacao);
    }
    
    if (strcmp(venda[i].formaPagamento, "Fiado") == 0) {
    	int idCliente = venda[i].idClienteFiado;
			if (idCliente >= 0) {
	    	printf("\tQuem deve: %s\n", clientes[idCliente].nome);
			}
	      printf("\tQuanto deve: R$%.2f\n", venda[i].valorDevido);
	  }
		printf("---------------------------------\n\n");
	}
}

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

void formaPagamento(int vendaIndex, int idProdutos) {
	int op, op2, qntUnidade, opCliente;
	Produtos *novoProd = &produtos[qntProdutos];
	
	system("cls");
	
	printf("1- Cartão.\n");
	printf("2- Boleto.\n");
	printf("3- Pix.\n");
	printf("4- Dinheiro.\n");
	printf("5- Fiado.\n\n");
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
		case 5:
			system("pause");
			system("cls");
			printf("------- Lista de Clientes: -------\n\n");
	    for (int i = 0; i < totalClientes; i++) {
	      printf("%d: %s\n\n", i + 1, clientes[i].nome);
	    }
	    
	    do {
				printf("Informe qual cliente comprou fiado de 1 à %d: ", totalClientes);
				scanf("%d", &opCliente);
			} while(opCliente < 1 || opCliente > totalClientes);
			
			for(int i = 0 ; i < totalClientes ; i++) {
				strcpy(clientes[opCliente - 1].nomeClienteFiado, clientes[opCliente - 1].nome);
			}
			
			venda[vendaIndex].idClienteFiado = opCliente - 1;
	
			venda[vendaIndex].valorDevido = venda[vendaIndex].quantidade * produtos[idProdutos - 1].precoUnidade;
			
			printf("\nVenda cadastrada com sucesso!\n");
			strcpy(venda[vendaIndex].formaPagamento, "Fiado");
			strcpy(venda[vendaIndex].tipoOperacao, "N/A");
			break;
		default:
			printf("\nErro! Escolha uma opção válida!\n\n");
	}
}

void cadastrarVenda() {
	char op;
	int idProduto;
	
	Produtos *novoProd = &produtos[qntProdutos];
	
	if(qntProdutos == 0) {
		printf("Não há produtos cadastrados no estoque!\n\n");
		return;
	}
	
	if(qntVendas >= MAX_VENDAS) {
		printf("O estoque está cheio!\n\n");
		return;
	}
	
	do {
		printf("----- Produtos cadastrados: -----\n\n");
		for(int i = 0 ; i < qntProdutos ; i++) {
			printf("Produto %d: %s\n", i + 1, produtos[i].nome);
		}
	
		printf("\n");
	
		do {
			printf("Escolha um produto de 1 a %d: ", qntProdutos);
			scanf("%d", &idProduto);
		} while(idProduto < 1 || idProduto > qntProdutos);
		
		printf("\n");
		
		system("pause");
		system("cls");
		
		printf("Informe a quantidade de produtos vendidos: ");
		scanf("%d", &venda[qntVendas].quantidade);
		
		system("cls");
		
		formaPagamento(qntVendas, idProduto);
		qntVendas++;
		
		fflush(stdin);
		printf("Deseja cadastrar mais alguma venda? (S/N)\n");
		scanf("%c", &op);
		
		system("cls");
	} while (op == 'S' || op == 's');
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
				cadastrarCliente();
				break;
			case 3:
				cadastrarProduto();
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
				listarClientes();
				break;
			case 3:
				//listarFuncionario();
				break;
			case 4:
				listarVendas();
				break;
			case 5:
				listarCategorias();
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
	setlocale(LC_ALL, "");
	
	menuInicial();
}