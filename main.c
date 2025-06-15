#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define TOP 10
#define MAX_FUNC 100
#define MAX_USERS 20
#define MAX_CATEG 20
#define MAX_VENDAS 20
#define MAX_SUBCATG 5
#define MAX_CLIENTES 20
#define MAX_EMPRESAS 5
#define MAX_PRODUTOS 20

//add typedef
typedef struct {
	char usuario[50]; 
	char genero[50]; 
	char email[50]; 
	char senha[50]; 
	char cpf[50]; 
	int idade;
} Usuario;

typedef struct {
    char tel[50];
    char cnpj[50];
	char nomeEmpresa[50]; 
	char responsavel[50]; 
	int porteEmpresa;
	int tempoAtuacao;
	float rendaMensal;
	float metaLucro;
} Empresa;  

typedef struct {
	char nome[50];
	int qntVendas; //novo
	float totalVendas; //novo
} Subcategoria;

typedef struct {
	char nome[50];
	Subcategoria subcategorias[MAX_SUBCATG];
	int qntSubcategorias;
	int qntVendas; //novo
	float totalVendas; //novo
} Categoria;

typedef struct {
	char nome[50];
	int qntEstoque;
	int codigoProduto;
	int idxCategoria;
	int qntCategorias;
	int idxSubcategoria;
	int qntVendas; //novo
	float precoUnidade;
	float precoCusto;
	float totalVendas; //novo
} Produto;

typedef struct {
    char nomeFuncionario[50];
    char cpf[50];
    char numeroFolha[50];
    char numeroPis[50];
    char empregador[50];
    char departamento[50];
    char funcao[50];
    char admissao[50];
    int idFuncionario; //novo
    int qntVendas; 
    float totalVendas;
} Funcionario;

typedef struct {
	char formaPagamento[20];
	char tipoOperacao[15];
	char dataVenda[11];
	int idProduto;
	int idFuncionario;
	int idCliente;
	int quantidade;
	float totalVenda;
} Venda;

typedef struct {
    char nome[50];
    char cpf[20];
    char email[50];
    char tel[20]; //novo
    int idade;
    int qntCompras; 
    float totalComprado;
} Cliente;

Produto produtos[MAX_PRODUTOS];
Categoria categorias[MAX_CATEG];
Cliente clientes[MAX_CLIENTES];
Empresa empresa[MAX_EMPRESAS];
Usuario usuario[MAX_USERS];
Venda venda[MAX_VENDAS];
Funcionario funcionario[MAX_FUNC];

int qntFuncionarios = 0;
int qntCategorias = 0;
int qntProdutos = 0;
int totalClientes = 0;
int qntVendas = 0;

void start() {
	for(int i = 0; i < MAX_PRODUTOS; i++) {
		produtos[i].qntVendas = 0;
		produtos[i].totalVendas = 0.0;
		produtos[i].qntCategorias = 0;
		produtos[i].idxCategoria = -1;
		produtos[i].idxSubcategoria = -1;
	}
	
	for(int i = 0; i < MAX_FUNC; i++) {
		funcionario[i].qntVendas = 0;
		funcionario[i].totalVendas = 0.0;
	}
	
	for(int i = 0; i < MAX_CLIENTES; i++) {
		clientes[i].qntCompras = 0;
		clientes[i].totalComprado = 0.0;
	}
	
	for(int i = 0; i < MAX_VENDAS; i++)
		venda[i].totalVenda = 0.0;
	
	for(int i = 0; i < MAX_CATEG; i++) {
		categorias[i].qntVendas = 0;
		categorias[i].totalVendas = 0.0;
		
		for(int j = 0; j < MAX_SUBCATG; j++) {
			categorias[i].subcategorias[j].qntVendas = 0;
			categorias[i].subcategorias[j].totalVendas = 0.0;
		}
	}	
}

int verificacao(int entrada, int tamanhoEsperado, char *nome) {
    if (entrada != tamanhoEsperado) {
        printf("\n%s Inválido!!\n\n", nome);
        return 0;
    }
    return 1;
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

int validarEmail(char atrr[]) {	
	int valido = 0;
	
	for(int i = 0; atrr[i] != '\0'; i++) {
		if(atrr[i] == '@')
			valido++;
	}
	
	return (valido == 1) ? 1 : 0;
}

int validarData(char atrr[]) {
	if(atrr[0] == '\0') return 0;
	
	int dia, mes, ano;
	
	if(sscanf(atrr, "%d/%d/%d", &dia, &mes, &ano) == 3) {
		if(ano < 1999 ||
		   ano > 2050 ||
		   mes < 1 ||
		   mes > 12 ||
		   dia < 1 ||
		   dia > 31
		) return 0;
		
		if(mes == 2 ||
		   mes == 4 ||
		   mes == 6 ||
		   mes == 8 ||
		   mes == 10 ||
		   mes == 12) {
		   if(dia > 30) return 0;
		}
	} else return 0;
}

void limparEnter(char atrr[]) {
	atrr[strcspn(atrr, "\n")] = '\0';
}

void exibirHeader(char mensagem[]) {
	printf("------- %s: -------\n\n", mensagem);
}

// Categorias / Subcategorias 
void cadastrarCategoria() {	
	int existe;
	char op, entrada[50];
	
	Categoria *novaCategoria = &categorias[qntCategorias];
	novaCategoria->qntSubcategorias = 0;
	
	exibirHeader("Cadastro nova categoria");
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
			exibirHeader("Cadastro nova categoria");
			printf("| Categoria criada: %s", novaCategoria->nome);			
			printf("\n---------------------------");			
			printf("\nDeseja criar uma subcategoria para %s? (s/n): ", novaCategoria->nome);
			fgets(entrada, sizeof(entrada), stdin);
			limparEnter(entrada);
			
			op = tolower(entrada[0]);
			
			if(op != 's' && op != 'n' || strlen(entrada) > 1) system("cls");				
		} while(op != 's' && op != 'n' || strlen(entrada) > 1);
		
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
	
	printf("| Categoria %s criada com sucesso!\n\n", novaCategoria->nome);		
	qntCategorias++;
}

void listarCategorias() {	
	if(qntCategorias == 0) printf("Nenhuma categoria cadastrada no sistema!\n\n");		
	else {
		exibirHeader("Categorias Cadastradas");
		
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

int listarSelecionarCategoria() {
	int idCategoria;
	
	printf("| Categorias cadastradas: \n\n");
			
	for(int i = 0; i < qntCategorias; i++)
		printf("Categoria %d: %s\n", i + 1, categorias[i].nome);	
		
	do {				
		printf("---------------------\n\n");
		printf("Escolha uma categoria entre 1 a %d (informe apenas números): ", qntCategorias);
		scanf("%d", &idCategoria);			
		
		if(idCategoria < 1 || idCategoria > qntCategorias) 
			printf("\nSelecione uma opção válida!\n");
	} while(idCategoria < 1 || idCategoria > qntCategorias);	
	
	return idCategoria - 1;	
}

int listarSelecionarSubcategoria(int idxCategoria) {
	int idSubcategoria;
	
	printf("| Subcategorias cadastradas de '%s':\n", categorias[idxCategoria]);
			
	for(int i = 0; i < categorias[idxCategoria].qntSubcategorias; i++)
		printf("\tSubcategoria %d: %s\n", i + 1, categorias[idxCategoria].subcategorias[i].nome);
	
	do {
		printf("\nSelecione a subcategoria: ");
		scanf("%d", &idSubcategoria);	
	} while(idSubcategoria < 1 || idSubcategoria > categorias[idxCategoria].qntSubcategorias);	
	
	return idSubcategoria - 1;	
}

void cadastrarSubcategoria() {
	char nomeNovaSubcat[50];
	int idCategoria, existe;
	
	if(qntCategorias == 0) 
		printf("Nenhuma categoria cadastrada no sistema!\nPor favor, cadastre uma categoria primeiro.\n\n");
	else {		
		idCategoria = listarSelecionarCategoria();		
		
		getchar();
		Categoria *novaSubcategoria = &categorias[idCategoria];	
		
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

// Produtos
void cadastrarProduto() {
	if(qntProdutos == MAX_PRODUTOS) {
		printf("Limite de cadastro de produtos atingido!\n\n");
		return;
	}
	
	Produto *novoProd = &produtos[qntProdutos];
	char entrada[20];
	int existeIgual = 0;
	
	exibirHeader("Cadastro Novo Produto");
	
	do {
		existeIgual = 0;
		
		printf("Informe o nome do produto: ");
		fgets(novoProd->nome, sizeof(novoProd->nome), stdin);
		limparEnter(novoProd->nome);
		
		for(int i = 0; i < qntProdutos; i++) {
			if(strcmp(novoProd->nome, produtos[i].nome) == 0) existeIgual = 1;
		}
		
		if(existeIgual) printf("\nEsse nome já foi cadastrado! Tente novamente.\n");
	} while(existeIgual);
	
	// Mostra essa opção apenas se houver categorias
	if(qntCategorias > 0) {
		int idxCategoria, idxSubcategoria;
		
		novoProd->qntCategorias = 0;

		system("cls");
		exibirHeader("Cadastro Novo Produto");		
		idxCategoria = listarSelecionarCategoria();
		
		novoProd->idxCategoria = idxCategoria;
		Categoria *categoriaSelecionada = &categorias[novoProd->idxCategoria];
		
		// Mostra essa opção apenas se houver subcategorias > categorias
		if(categoriaSelecionada->qntSubcategorias > 0) {	
			system("cls");
			exibirHeader("Cadastro Novo Produto");
			novoProd->idxSubcategoria = listarSelecionarSubcategoria(idxCategoria);
		}
		
		novoProd->qntCategorias++;
		
		system("cls");	
		exibirHeader("Cadastro Novo Produto");		
		
		printf("Nome do produto: %s\n", novoProd->nome);
		printf("Categoria do produto: %s\n", categorias[novoProd->idxCategoria].nome);
		printf("Subcategoria do produto: %s\n", categorias[novoProd->idxCategoria].subcategorias[novoProd->idxSubcategoria].nome);
		printf("\n---------------------");
		getchar();
	}		
	
	do {
		printf("\nInforme o preço de venda do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));
	
	novoProd->precoUnidade = atof(entrada);	
	
	do {
		printf("Informe o preço de custo do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));
	
	novoProd->precoCusto = atof(entrada);
	
	do {
		printf("\nInforme a quantidade em estoque: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
	} while(!somenteReais(entrada));
	
	novoProd->qntEstoque = atof(entrada);	
	
	do {	
		existeIgual = 0;
		
		printf("Informe o código do produto (ex: 1234): ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);			
		
		for(int i = 0; i < qntProdutos; i++) {
			if(atoi(entrada) == produtos[i].codigoProduto) existeIgual = 1;
		}
		
		if(existeIgual) printf("\nEsse código já foi cadastrado! Tente novamente.\n");
	} while(!somenteReais(entrada) || existeIgual);	
		
	novoProd->codigoProduto = atoi(entrada);
	
	printf("\n| Produto cadastrado com sucesso!!\n\n");
	qntProdutos++;
}

void exibirProduto(int i, int count) {		
	printf("| Produto %d\n\n", count);	
	printf("\tNome do produto: %s\n", produtos[i].nome);
	printf("\tCódigo do produto: %d\n", produtos[i].codigoProduto);
	printf("\tPreço de venda: R$%.2f\n", produtos[i].precoUnidade);		
	printf("\tPreço de custo: R$%.2f\n", produtos[i].precoCusto);
	printf("\tQuantidade em estoque: %d\n", produtos[i].qntEstoque);
	printf("\tQuantidade de vendas: %d\n", produtos[i].qntVendas);
	
	if(produtos[i].qntCategorias > 0)
		printf("\tCategorias do produto: %s\n", categorias[produtos[i].idxCategoria].nome);
	else
		printf("\tCategorias do produto: não informado\n");
		
	if(categorias[produtos[i].idxCategoria].qntSubcategorias > 0)
		printf("\tSubcategorias do produto: %s\n", categorias[produtos[i].idxCategoria].subcategorias[produtos[i].idxSubcategoria].nome);
	else 
		printf("\tSubcategorias do produto: não informado\n");
		
	printf("\n------------------------\n");
}

// Listagem por filtros
void listarPorCategoria() {
	int idCategoria, count = 0;
	
	if(qntCategorias == 0) 
		printf("Nenhuma categoria cadastrada no sistema!\n\n");
	else {		
		idCategoria = listarSelecionarCategoria();	
		system("cls");
		
		getchar();
		for(int i = 0; i < qntProdutos; i++) {
			if(produtos[i].idxCategoria == idCategoria) {
				count++;
				exibirProduto(i, count);
			}
		}
	}
}

void listarPorSubcategoria() {
	int idCategoria, idSubcategoria, count = 0;
	
	if(qntCategorias == 0) 
		printf("Nenhuma categoria cadastrada no sistema!\n\n");
	else {		
		idCategoria = listarSelecionarCategoria();	
		Categoria *categoriaSelecionada = &categorias[idCategoria];
		system("cls");
		
		if(categorias[idCategoria].qntSubcategorias <= 0) {
			printf("%s não possui subcategorias cadastradas!\n\n", categoriaSelecionada->nome);
		} else {					
			idSubcategoria = listarSelecionarSubcategoria(idCategoria);
			
			for(int i = 0; i < qntProdutos; i++) {
				if(produtos[i].idxSubcategoria == idCategoria && produtos[i].idxSubcategoria == idSubcategoria - 1) {
					count++;
					exibirProduto(i, count);
				}
			}
		}
	}
}

int compararValores(int a, int b, char operador) {
	if(operador == '<') return a < b;
	if(operador == '>') return a > b;
	if(operador == 'e') return a == b;
	if(operador == '!') return a != b;
}

void listarPorFaixa(char operador, char mensagem[20]) {
	int count = 0, existe = 0;
	float valor;
	
	printf("| Opção: Listagem %s x valor\n", mensagem);
	printf("---------------------------\n\n");
	
	printf("Informe um valor: ");
	scanf("%f", &valor);
	
	printf("\n---------------------");	
	
	for(int i = 0; i < qntProdutos; i++) {
		if(compararValores(produtos[i].precoUnidade, valor, operador)) existe = 1;
	}	
	
	if(existe) {
		system("cls");
		printf("------- Produtos %s R$%.2f -------\n\n", mensagem, valor);
		
		for(int i = 0; i < qntProdutos; i++) {
			if(compararValores(produtos[i].precoUnidade, valor, operador)) {
				count++;
				exibirProduto(i, count);
			}
		}
	} else 
		printf("\nNão há produtos cadastrados %s %.2f!\n\n", mensagem, valor);
	
	//if(!existe) 
}

void listarPorPreco() {
	int idCategoria, idSubcategoria, count = 0;
	char op, entrada[20];
	
	while(1) {
		printf("| Menu - Listagem por:\n");
		printf("---------------------------\n\n");
		
		printf("1- Valor específico\n");
		printf("2- Produtos acima de um valor\n");
		printf("3- Produtos abaixo de um valor\n");
		printf("4- Voltar ao menu\n");
		
		printf("\nEscolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		system("cls");
		
		switch(entrada[0]) {
			case '1':
				listarPorFaixa('e', "com valor igual a:");
				break;
			case '2':
				listarPorFaixa('>', "acima de");
				break;
			case '3':
				listarPorFaixa('<', "abaixo de");
				break;
			case '4':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		getchar();
		system("pause");
		system("cls");
	}
}

void listarMaisVendidos() {
	int index, aux;
	int order[TOP];
	
	if(qntVendas <= 0) {
		printf("Ainda não há vendas cadastradas no sistema!!\n\n");
		return;
	}
	
	index = (qntProdutos >= 10) ? TOP : qntProdutos;
	
	for(int i = 0; i < index; i++) 
		order[i] = i;
		
	for(int i = 0; i < index; i++) {
		for(int j = 0; j < index - 1 - i; j++) {
			if(produtos[order[j]].qntVendas < produtos[order[j + 1]].qntVendas) {
				aux = order[j];
				order[j] = order[j + 1];
				order[j + 1] = aux;
			}
		}
	}
	
	printf("------- Top %d mais vendios: -------\n\n", index + 1);
	
	for(int i = 0; i < index; i++) 
		exibirProduto(order[i], i + 1);
}

void listarSemEstoque() {	
	int existe = 0;
	
	for(int i = 0; i < qntProdutos; i++) {
		if(produtos[i].qntEstoque <= 0) existe = 1;		
	}
	
	if(!existe) 
		printf("Não há produtos cadastrados sem estoque!!\n\n");
	else {
		exibirHeader("Produtos sem estoque");	
		
		for(int i = 0; i < qntProdutos; i++) {
			if(produtos[i].qntEstoque <= 0) exibirProduto(i, i + 1);
		}		
	}
}

void listarProdutos() {
	if(qntProdutos == 0) {
		printf("Não há produtos cadastrados no estoque!\n\n");
		return;
	}
	
	char op, entrada[20];
	int idCategoria, idSubcategoria, count = 0;	
	
	while(1) {
		printf("| Menu - Opções de listagem de produtos\n");
		printf("---------------------------\n\n");
		
		printf("1- Top 10 mais vendidos\n");
		printf("2- Listar por preço\n");
		printf("3- Listar por categoria\n");
		printf("4- Listar por subcategoria\n");
		printf("5- Produtos sem estoque\n");
		printf("6- Voltar ao menu\n");
		
		printf("\nEscolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		system("cls");
		
		switch(entrada[0]) {
			case '1':
				listarMaisVendidos();
				break;
			case '2':
				listarPorPreco();
				break;
			case '3':
				listarPorCategoria();
				break;
			case '4':
				listarPorSubcategoria();
				break;
			case '5':
				listarSemEstoque();
				break;
			case '6':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void exibirOpcaoEditar(int idEncontrado) {
	char novoValor[50], entrada[50], op;
	int opEdicao;
	
	system("cls");
	printf("Produto encontrado!\n\n");
	
	exibirProduto(idEncontrado, idEncontrado + 1);
	Produto *prod = &produtos[idEncontrado];
	
	printf("| Opções de edição:\n\n");
	
	printf("1- Nome\n");
	printf("2- Código do produto\n");
	printf("3- Categoria\n");
	printf("4- Subcategoria\n");
	printf("5- Preço de venda\n");
	printf("6- Preço de custo\n");
	printf("7- Quantidade em estoque\n\n");
	
	do {
		printf("Informe o que deseja editar de 1 a 7: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		opEdicao = atoi(entrada);
	} while(opEdicao < 1 || opEdicao > 7);
	
	system("cls");
	
	if(atoi(entrada) == 1) {
		printf("| Nome atual: %s\n", prod->nome);
		printf("---------------------------\n\n");
		
		printf("Informe um novo nome para o produto: ");
		fgets(novoValor, sizeof(novoValor), stdin);
		limparEnter(novoValor);
		
		strcpy(prod->nome, novoValor);		
		printf("\nNome atualizado com sucesso!!\n\n");
	} 			
	else if(atoi(entrada) == 2) {		
		do{
			printf("| Nome atual: %s\n", prod->nome);
			printf("---------------------------\n\n");
			
			printf("Informe um novo código para o produto: ");
			fgets(novoValor, sizeof(novoValor), stdin);
			limparEnter(novoValor);
		} while(!somenteReais(novoValor));			
			
		prod->codigoProduto = atoi(novoValor);		
		printf("\nCódigo do produto atualizado com sucesso!!\n\n");
	}			
	else if(atoi(entrada) == 3) {		
		if(qntCategorias <= 0)
			printf("Cadastre uma categoria primeiro para usar esta opção!\n\n");
		else {			
			printf("| Categoria atual: %s\n", (prod->idxCategoria != -1) ? categorias[prod->idxCategoria].nome : "Nenhuma");
			printf("---------------------------\n\n");
			
			prod->idxCategoria = listarSelecionarCategoria();
			prod->qntCategorias++;
			printf("\n");
			
			if(categorias[prod->idxCategoria].qntSubcategorias > 0){
				system("cls");
				prod->idxSubcategoria = listarSelecionarSubcategoria(prod->idxCategoria);					
				printf("\nCategoria e subcategoria atualizadas com sucesso!!\n\n");				
			} else 
				printf("\nCategoria atualizada com sucesso!!\n\n");					
		}
	}			
	else if(atoi(entrada) == 4) {
		if(prod->idxCategoria != -1) {
			printf("| Subcategoria atual: %s\n", categorias[prod->idxCategoria].subcategorias[prod->idxSubcategoria].nome);
			printf("---------------------------\n\n");
			
			prod->idxSubcategoria = listarSelecionarSubcategoria(prod->idxCategoria);				
			printf("\nSubcategoria atualizada com sucesso!!\n\n");			
		} else
			printf("Informe uma categoria para o produto antes de adicionar/modificar as subcategorias!");
	}			
	else if(atoi(entrada) == 5) {
		do{
			printf("| Preço de venda atual: R$%.2f\n", prod->precoUnidade);
			printf("---------------------------\n\n");
			
			printf("Informe um novo preço de venda: ");
			fgets(novoValor, sizeof(novoValor), stdin);
			limparEnter(novoValor);
		} while(!somenteReais(novoValor));
		
		prod->precoUnidade = atof(novoValor);				
		printf("\nPreço de venda atualizado com sucesso!!\n\n");
	}
	else if(atoi(entrada) == 6) {
		do{
			printf("| Preço de custo atual: R$%.2f\n", prod->precoCusto);
			printf("---------------------------\n\n");
			
			printf("Informe um novo preço de custo: ");
			fgets(novoValor, sizeof(novoValor), stdin);
			limparEnter(novoValor);
		} while(!somenteReais(novoValor));
		
		prod->precoCusto = atof(novoValor);		
		printf("\nPreço de custo atualizado com sucesso!!\n\n");
	}
	else if(atoi(entrada) == 7) {
		do{
			printf("| Quantidade em estoque atual: %d\n", prod->qntEstoque);
			printf("---------------------------\n\n");
			
			printf("Informe a quantidade em estoque atual do produto: ");
			fgets(novoValor, sizeof(novoValor), stdin);
			limparEnter(novoValor);
		} while(!somenteReais(novoValor));
		
		prod->qntEstoque = atoi(novoValor);		
		printf("\nQuantidade em estoque atualizada com sucesso!!\n\n");
	}
}

// Editar/remover informações
void editarProduto() {
	if(qntProdutos == 0) {
		printf("Não há produtos cadastrados no estoque!\n\n");
		return;
	}
	
	char novoValor[50], entrada[50], op;
	int idEncontrado, encontrou = 0; 
	
	do {
		printf("| Opções de busca\n");
		printf("---------------------------\n\n");
		
		printf("1- Por nome.\n");
		printf("2- Por código do produto.\n\n");
		
		printf("Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
	} while(op != '1' && op != '2');

	system("cls");
	printf("| Opção selecionada: %s\n", (op == '1') ? "Nome" : "Código");
	printf("---------------------------\n\n");
	
	if(op == '1') {
		printf("Informe o nome do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		for(int i = 0; i < qntProdutos; i++) {
			if(strcmp(entrada, produtos[i].nome) == 0) {
				encontrou = 1;
				idEncontrado = i;
			}
		}
		
		if(encontrou)
			exibirOpcaoEditar(idEncontrado);
		else 
			printf("\nProduto não encontrado!\n\n");
	}
	
	if(op == '2') {		
		printf("Informe o código do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		for(int i = 0; i < qntProdutos; i++) {
			if(atoi(entrada) == produtos[i].codigoProduto) {
				encontrou = 1;
				idEncontrado = i;
			}
		}
		
		if(encontrou)
			exibirOpcaoEditar(idEncontrado);
		else 
			printf("\nProduto não encontrado!\n\n");
	}
}

void removerProduto() {
	if(qntProdutos == 0) {
		printf("Não há produtos cadastrados no estoque!\n\n");
		return;
	}
	
	char novoValor[50], entrada[50], op;
	int idEncontrado, encontrou = 0; 
	
	do {
		printf("1- Por nome.\n");
		printf("2- Por código do produto.\n\n");
		
		printf("Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
	} while(op != '1' && op != '2');

	system("cls");
	printf("| Opção selecionada: %s\n", (op == '1') ? "Nome" : "Código");
	printf("---------------------------\n\n");
	
	if(op == '1') {
		printf("Informe o nome do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		for(int i = 0; i < qntProdutos; i++) {
			if(strcmp(entrada, produtos[i].nome) == 0) {
				encontrou = 1;
				idEncontrado = i;
				break;
			}
		}
		
		if(encontrou) {
			do {
				printf("\nTem certeza que deseja remover o produto? (s/n): ");
				fgets(entrada, sizeof(entrada), stdin);
				limparEnter(entrada);
				
				op = tolower(entrada[0]);				
			} while(op != 's' && op != 'n');
			
			if(op == 's') {
				char aux[50];
				
				strcpy(aux, produtos[idEncontrado].nome);
				
				for(int i = idEncontrado; i < qntProdutos - 1; i++)
					produtos[i] = produtos[i + 1];
				
				qntProdutos--;
				printf("\nProduto: %s removido com sucesso!\n\n", aux);
			} else
				printf("\nRemoção cancelada com sucesso!\n\n");
		} else
			printf("\nProduto não encontrado!\n\n");
	}
	
	if(op == '2') {		
		printf("Informe o código do produto: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		for(int i = 0; i < qntProdutos; i++) {
			if(atoi(entrada) == produtos[i].codigoProduto) {
				encontrou = 1;
				idEncontrado = i;
				break;
			}
		}
		
		if(encontrou) {
			char aux[50];
			
			strcpy(aux, produtos[idEncontrado].nome);
			
			for(int i = idEncontrado; i < qntProdutos - 1; i++) {
				produtos[i] = produtos[i + 1];
			}
			
			qntProdutos--;
			printf("\nProduto: %s removido com sucesso!\n\n", aux);			
		} else 
			printf("Produto não encontrado!\n\n");
	}
}

void editarCategoria() {
	if(qntCategorias == 0) {
		printf("Cadastre uma categoria primeiro para usar esta função!\n\n");
		return;
	}
	
	char entrada[50];
	int idCategoria, existeIgual = 0;
	
	idCategoria = listarSelecionarCategoria();
		
	system("cls");
	printf("| Categoria selecionada: %s\n", categorias[idCategoria].nome);
	printf("---------------------------\n\n");
	
	getchar();
	
	do {		
		existeIgual = 0;
	
		printf("Informe um novo nome para a categoria: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		for(int i = 0; i < qntCategorias; i++) {
			if(strcmp(entrada, categorias[i].nome) == 0) {
				existeIgual = 1;
				break;
			}
		}
		
		if(existeIgual) printf("\nEssa categoria já foi cadastrada. \nPor favor, informe outro nome!\n\n");	
	} while(existeIgual);
	
	strcpy(categorias[idCategoria].nome, entrada);
	printf("\nCategoria editada com sucesso!!\n\n");
}

void removerCategoria() {
	if(qntCategorias == 0) {
		printf("Não há categorias cadastradas no sistema!\n\n");
		return;
	}
	
	int idCategoria = listarSelecionarCategoria();
	char entrada[50], op;
	
	getchar();
	
	do {
		printf("\nTem certeza que deseja remover %s? (s/n): ", categorias[idCategoria].nome);
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);				
	} while(op != 's' && op != 'n');
	
	if(op == 's') {
		char aux[50];
		
		strcpy(aux, categorias[idCategoria].nome);
		
		for(int i = idCategoria; i < qntCategorias - 1; i++) 
			categorias[i] = categorias[i + 1];
		
		qntCategorias--;
		printf("\nCategoria: %s removida com sucesso!!\n\n", aux);
	} else 
		printf("\nRemoção cancelada com sucesso!\n\n");		
}

void editarSubcategoria() {
	if(qntCategorias == 0) {
		printf("Cadastre uma categoria primeiro para usar esta função!\n\n");
		return;
	}
	
	int idCategoria = listarSelecionarCategoria();
	
	if(categorias[idCategoria].qntSubcategorias == 0) {
		printf("%s não possui subcategorias cadastradas no sistema!!\n\n");
		return;
	}
	
	system("cls");
	int idSubcategoria = listarSelecionarSubcategoria(idCategoria);
		
	char entrada[50];
	int existeIgual = 0;
	
	system("cls");
	printf("| Subcategoria selecionada: %s\n", categorias[idCategoria].subcategorias[idSubcategoria].nome);
	printf("---------------------------\n\n");
	
	getchar();
	
	do {		
		existeIgual = 0;
	
		printf("Informe um novo nome para a subcategoria: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		for(int i = 0; i < qntCategorias; i++) {
			if(strcmp(entrada, categorias[idCategoria].subcategorias[idSubcategoria].nome) == 0) {
				existeIgual = 1;
				break;
			}
		}
		
		if(existeIgual) printf("\nEssa subcategoria já foi cadastrada. \nPor favor, informe outro nome!\n\n");	
	} while(existeIgual);
	
	strcpy(categorias[idCategoria].subcategorias[idSubcategoria].nome, entrada);
	printf("\nSubcategoria editada com sucesso!!\n\n");
}

void removerSubcategoria() {
	if(qntCategorias == 0) {
		printf("Não há categorias cadastradas no sistema!\n\n");
		return;
	}
	
	int idCategoria = listarSelecionarCategoria();
	
	if(categorias[idCategoria].qntSubcategorias == 0) {
		printf("%s não possui subcategorias cadastradas no sistema!!\n\n");
		return;
	}
	
	system("cls");
	int idSubcategorias = listarSelecionarSubcategoria(idCategoria);
	
	char entrada[50], op;
	
	getchar();
	
	do {
		printf("\nTem certeza que deseja remover %s? (s/n): ", categorias[idCategoria].subcategorias[idSubcategorias].nome);
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);				
	} while(op != 's' && op != 'n');
	
	if(op == 's') {
		char aux[50];
		
		strcpy(aux, categorias[idCategoria].subcategorias[idSubcategorias].nome);
		
		for(int i = idSubcategorias; i < categorias[idCategoria].qntSubcategorias - 1; i++)
			categorias[idCategoria].subcategorias[i] = categorias[idCategoria].subcategorias[i + 1];
		
		categorias[idCategoria].qntSubcategorias--;
		printf("\nSubcategoria: %s removida com sucesso!!\n\n", aux);
	} else 
		printf("\nRemoção cancelada com sucesso!\n\n");		
}

// Clientes
void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

	int sizeCpf;
	char entrada[50];
	
	Cliente *novoCliente = &clientes[totalClientes];

    exibirHeader("Cadastro de Cliente");

    printf("Informe seu nome: ");
    fgets(novoCliente->nome, sizeof(novoCliente->nome), stdin);
    limparEnter(novoCliente->nome);

	do {
	    printf("Informe seu CPF: ");
	    fgets(novoCliente->cpf, sizeof(novoCliente->cpf), stdin);
	    limparEnter(novoCliente->cpf);
			    
	    sizeCpf = strlen(novoCliente->cpf);
	} while (!verificacao(sizeCpf, 11, "CPF"));

	do {
		printf("Informe seu e-mail: ");
		fgets(novoCliente->email, sizeof(novoCliente->email), stdin);
		limparEnter(novoCliente->email);		
		
		if(!validarEmail(novoCliente->email) || validarEmail(novoCliente->email) == 2)
			printf("\nInforme um email válido!\n\n");
	} while(!validarEmail(novoCliente->email));
	
	do {
		printf("Informe sua idade: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
	} while(atoi(entrada) < 18);
	
	novoCliente->idade = atoi(entrada);
	
	totalClientes++;
	printf("\nCliente cadastrado com sucesso!\n");
}

void listarClientes() {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n\n");
        return;
    }

    exibirHeader("Clientes cadastrados");
	    
    for (int i = 0; i < totalClientes; i++) {
        printf("| Cliente %d: \n\n", i + 1);
        
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Email: %s\n", clientes[i].email);
        printf("Idade: %d\n", clientes[i].idade);
        printf("Quantidade de compras feitas: %d\n", clientes[i].qntCompras);
        printf("Valor total em compras: R$%.2f\n", clientes[i].totalComprado);
        printf("----------------------------\n");
    }
}

// Funcionários
void cadastrarFuncionario(Funcionario funcionario[]) {	
    if (qntFuncionarios >= MAX_FUNC) {
        system("cls");
        printf("Numero de funcionarios atingido!!!\n");
        printf("O seu limite atual de Funcionários é de %i", MAX_USERS);
        return;
    }

	char entrada[30];
    int numeroCpf;
    int index = qntFuncionarios;
    
    Funcionario *novoFunc = &funcionario[index];

    system("cls");
	exibirHeader("Cadastro novo funcionário");
	
    printf("Nome: ");
    fgets(novoFunc->nomeFuncionario, sizeof(novoFunc->nomeFuncionario), stdin);
    limparEnter(novoFunc->nomeFuncionario);

    do {
        printf("CPF: ");
        fgets(novoFunc->cpf, sizeof(novoFunc->cpf), stdin);
        limparEnter(novoFunc->cpf);
        numeroCpf = strlen(novoFunc->cpf);
    } while (!verificacao(numeroCpf, 11, "CPF") || !somenteReais(novoFunc->cpf));

    printf("Numero da folha: ");
    fgets(novoFunc->numeroFolha, sizeof(novoFunc->numeroFolha), stdin);
    limparEnter(novoFunc->numeroFolha);

    printf("Numero PIS: ");
    fgets(novoFunc->numeroPis, sizeof(novoFunc->numeroPis), stdin);
    limparEnter(novoFunc->numeroPis);

    printf("Nome do empregador: ");
    fgets(novoFunc->empregador, sizeof(novoFunc->empregador), stdin);
    limparEnter(novoFunc->empregador);

    printf("Departamento: ");
    fgets(novoFunc->departamento, sizeof(novoFunc->departamento), stdin);
    limparEnter(novoFunc->departamento);

    printf("Função: ");
    fgets(novoFunc->funcao, sizeof(novoFunc->funcao), stdin);
    limparEnter(novoFunc->funcao);

	do {
	    printf("Dia da admissão (ex.: dd/mm/aaaa): ");
	    fgets(novoFunc->admissao, sizeof(novoFunc->admissao), stdin);
	    limparEnter(novoFunc->admissao);		
	} while(!validarData(novoFunc->admissao));
    
    //+idFuncionario   -> é o identificador do funcionário na empresa. Será usado na função de cadastrarVenda()

    printf("\nFuncionario cadastrado!!!!\n");
    qntFuncionarios++;
}

void listarFuncionarios() {
	if(qntFuncionarios == 0) printf("Nenhum funcionário cadastrado(a) no sistema!\n\n");		
	else {
		exibirHeader("Funcionarios Cadastrados(a)");
	
		for(int i = 0; i < qntFuncionarios; i++) {		
			printf("Funcionario: %s\n", funcionario[i].nomeFuncionario);
			printf("Numero folha: %s\n", funcionario[i].numeroFolha);		
			printf("Numero PIS: %s\n", funcionario[i].numeroPis);
			printf("Departamento: %s\n", funcionario[i].departamento);		
			printf("Função: %s\n",  funcionario[i].funcao);		
			printf("CPF: %s\n",  funcionario[i].cpf);		
			printf("ID: %s\n",  funcionario[i].idFuncionario);		
			printf("Data de admissão: %s\n", funcionario[i].admissao);	
			printf("Quantidade de vendas feitas: %d\n", funcionario[i].qntVendas);	
			printf("Valor total em vendas: R$%.2f\n", funcionario[i].totalVendas);	
			printf("\n---------------------\n");
		}
	}
}

void editarFuncionario() {
	if(qntFuncionarios == 0) {
		printf("Nenhum funcionário cadastrado(a) no sistema!\n\n");
		return;
	}
	
	char entrada[50], op;
	int escolha, opcao;
	
	exibirHeader("Editar funcionário");
	
	for(int i = 0; i < qntFuncionarios; i++) {
		printf("%d - %s\n", i + 1, funcionario[i].nomeFuncionario);
	}
	
	do {
		printf("\nDigite o número do funcionário que deseja editar: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);		
	} while(atoi(entrada) < 1 || atoi(entrada) > qntFuncionarios);
	
	int index = atoi(entrada) - 1;
	Funcionario *f = &funcionario[index];
	
	do {
		system("cls");
		exibirHeader("Edição de dados");
		
		printf("| Editando: %s\n", f->nomeFuncionario);
		
		printf("\nEscolha o campo que deseja editar:\n\n");
		printf("1 - Nome\n");
		printf("2 - CPF\n");
		printf("3 - Número da Folha\n");
		printf("4 - Número PIS\n");
		printf("5 - Empregador\n");
		printf("6 - Departamento\n");
		printf("7 - Função\n");
		printf("8 - Data de Admissão\n");
		printf("0 - Sair da edição\n\n");
		
		printf("Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = entrada[0];
		
		system("cls");
		
		switch(op) {
			case '1':
				printf("| Nome atual: %s\n", f->nomeFuncionario);
				printf("---------------------------\n\n");
				
				printf("Novo nome: ");
				fgets(f->nomeFuncionario, sizeof(f->nomeFuncionario), stdin);
				limparEnter(f->nomeFuncionario);
			break;
			case '2':
				do {
					printf("Novo CPF: ");
					fgets(f->cpf, sizeof(f->cpf), stdin);
					limparEnter(f->cpf);
				} while (!verificacao(strlen(f->cpf), 11, "CPF") || !somenteReais(f->cpf));
			break; 
			case '3':
				printf("Novo número da folha: ");
				fgets(f->numeroFolha, sizeof(f->numeroFolha), stdin);
				limparEnter(f->numeroFolha);
			break;
			case '4':
				printf("Novo número PIS: ");
				fgets(f->numeroPis, sizeof(f->numeroPis), stdin);
				limparEnter(f->numeroPis);
			break;
			case '5':
				printf("Novo empregador: ");
				fgets(f->empregador, sizeof(f->empregador), stdin);
				limparEnter(f->empregador);
			break;
			case '6':
				printf("Novo departamento: ");
				fgets(f->departamento, sizeof(f->departamento), stdin);
				limparEnter(f->departamento);
			break;
			case '7':
				printf("Nova função: ");
				fgets(f->funcao, sizeof(f->funcao), stdin);
				limparEnter(f->funcao);
			break;
			case '8':
				printf("Nova data de admissão: ");
				fgets(f->admissao, sizeof(f->admissao), stdin);
				limparEnter(f->admissao);
			break;
			case '0':
				printf("Saindo da edição...\n");
			break;
			default:
				printf("Opção inválida!\n");
		}
			
		if(op != '0') {
			printf("\nCampo atualizado com sucesso!\n\n");
			system("pause");
		}
	} while(op != '0');
}

void removerFuncionario() {
    if(qntFuncionarios == 0) {
      printf("Nenhum funcionário cadastrado(a) no sistema!\n\n");
      return;
    }

    //int escolha;
    char entrada[50], op;

    exibirHeader("Remover funcionário");

    for(int i = 0; i < qntFuncionarios; i++) {
		printf("%d - %s\n", i + 1, funcionario[i].nomeFuncionario);
    }
	
	do {
	    printf("\nDigite o número do funcionário que deseja remover: ");
	    fgets(entrada, sizeof(entrada), stdin);
	    limparEnter(entrada);		
	} while(atoi(entrada) < 1 || atoi(entrada) > qntFuncionarios);

    int index = atoi(entrada) - 1;

    do {
	    printf("\nTem certeza que deseja remover %s? (s/n): ", funcionario[index].nomeFuncionario);
	    fgets(entrada, sizeof(entrada), stdin);
	    limparEnter(entrada);    	
	    
	    op = tolower(entrada[0]);
	} while(op != 's' && op != 'n');

	if(op == 's') {
		for(int i = index; i < qntFuncionarios - 1; i++) {
			funcionario[i] = funcionario[i + 1];
		}
		
		qntFuncionarios--;
		printf("\nFuncionário removido com sucesso!\n");
	} else {
		printf("\nRemoção cancelada.\n");
	}
}

// Vendas
void listarVendas() {
	if(qntVendas == 0) {
		printf("Não há nenhuma venda cadastrada!\n\n");
		return;
	}
	
	exibirHeader("Vendas cadastradas");
	
	for(int i = 0; i < qntVendas; i++) {
		Produto *prod = &produtos[venda[i].idProduto];
		Categoria *categSelecionada = &categorias[produtos[venda[i].idProduto].idxCategoria];
		
		printf("| Venda %d: \n", i + 1);		
		printf("\tNome do produto: %s\n", prod->nome);
		printf("\tCódigo do produto: %d\n", prod->codigoProduto);
		printf("\tData da venda: %s\n", venda[i].dataVenda);
		
		if(produtos[i].qntCategorias >= 1) 
			printf("\tCategoria: %s\n", categSelecionada->nome);			
		else
			printf("\tCategoria: nenhuma informada\n");
			
		if(produtos[i].qntCategorias >= 1 && categSelecionada->qntSubcategorias >= 1)
			printf("\tSubcategoria: %s\n", categSelecionada->subcategorias[prod->idxSubcategoria].nome);
		else 
			printf("\tSubcategoria: nenhuma informada\n");
			
		printf("\tForma de pagamento: %s\n", venda[i].formaPagamento);
		
		if(strcmp(venda[i].formaPagamento, "Cartão") == 0) 
			printf("\tTipo de operação: %s\n", venda[i].tipoOperacao);
			
		if(qntFuncionarios >= 1 && venda[i].idFuncionario >= 0 && venda[i].idFuncionario < qntFuncionarios)
			printf("\tFuncionário que efetuou a venda: %s\n", funcionario[venda[i].idFuncionario].nomeFuncionario);
		else
			printf("\tFuncionário que efetuou a venda: Nenhum informado\n");

		if (totalClientes >= 1 && venda[i].idCliente >= 0 && venda[i].idCliente < totalClientes)
			printf("\tCliente que efetuou a compra: %s\n", clientes[venda[i].idCliente].nome);
		else 
			printf("\tCliente que efetuou a compra: Nenhum informado\n");
		    
		printf("\tValor total: R$%.2f\n", venda[i].totalVenda);
		printf("\tQuantidade: %d\n", venda[i].quantidade);
		printf("---------------------------------\n\n");
	}
}

void tipoOperacao(int op, int vendaIndex) {
	system("cls");
	
	do {
		printf("1. Crédito.\n");
		printf("2. Débito.\n\n");
		printf("Informe o tipo de operação: ");
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
		
		system("pause");
		system("cls");
		 
	} while(op < 1 || op > 2);
}

void formaPagamento(int vendaIndex, float valorTotal) {
	int op;	

	do {		
		system("cls");				
		printf("Valor total: %.2f", valorTotal);
		printf("\n---------------------\n\n");
		
		printf("1- Cartão.\n");
		printf("2- Boleto.\n");
		printf("3- Pix.\n");
		printf("4- Dinheiro.\n\n");
		printf("Informe a forma de pagamento: ");
		scanf("%d", &op);
		
		system("cls");
		
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
		
		system("pause");
		system("cls");
	} while(op < 1 || op > 4);
}

void cadastrarVenda() {
	char entrada[15], op;
	char confirmacaoFuncionario, confirmacaoCliente;
	int idProduto, idFuncionario, idCliente;
	float valorTotal;	
	
	if(qntProdutos == 0) {
		printf("Não há produtos cadastrados no estoque!\n\n");
		return;
	}
	
	if(qntVendas >= MAX_VENDAS) {
		printf("O estoque está cheio!\n\n");
		return;
	}
	
	do {
		Venda *novaVenda = &venda[qntVendas];
		
		//validar se existe funcionários cadastrados no sistema*
		printf("É funcionário cadastrado? (S/N):\n");
		scanf("%c", &confirmacaoFuncionario);
		
		confirmacaoFuncionario = tolower(confirmacaoFuncionario);

		//mudança lucas 14/06
		if(confirmacaoFuncionario == 's') {
			system("cls");
			printf("| Funcionários cadastrados:\n\n");
				
			for(int i = 0 ; i < qntFuncionarios ; i++) 
				printf("\tFuncionário %d: %s\n", i + 1, funcionario[i].nomeFuncionario);
			
			printf("\n\t0- Funcionário não cadastrado\n");
			printf("\n---------------------\n");
		
			do {
				printf("Informe o funcionário que efetuou a venda: ");
				scanf("%d", &idFuncionario);
			} while(idFuncionario < 0 || idFuncionario > qntFuncionarios);
		}
		
		//validar se existe clientes cadastrados no sistema*
		fflush(stdin);
		printf("\nQuem efetuou a compra é um cliente cadastrado? (S/N):\n");
		scanf("%c", &confirmacaoCliente);
		
		confirmacaoCliente = tolower(confirmacaoCliente);

		if(confirmacaoCliente == 's') {
			system("cls");
			printf("| Clientes cadastrados:\n\n");
				
			for(int i = 0 ; i < totalClientes ; i++) 
				printf("\tCliente %d: %s\n", i + 1, clientes[i].nome);

			printf("\n\t0- Cliente não cadastrado\n");
			printf("\n---------------------\n");

			do {
				printf("Informe o cliente que comprou: ");
				scanf("%d", &idCliente);
			} while(idCliente < 0 || idCliente > totalClientes);
		}
		
		system("cls");			
		printf("| Produtos cadastrados:\n\n");	
		
		for(int i = 0 ; i < qntProdutos ; i++) {
			if(produtos[i].qntEstoque > 0)
				printf("\tProduto %d: %s\n", i + 1, produtos[i].nome);
		}
	
		printf("\n---------------------\n");
	
		do {
			printf("Escolha um produto de 1 a %d: ", qntProdutos);
			scanf("%d", &idProduto);
		} while(idProduto < 1 || idProduto > qntProdutos);
		
		novaVenda->idProduto = idProduto - 1;

		system("cls");		
		printf("| Produto selecionado: %s", produtos[idProduto - 1].nome);	
		printf("\n---------------------\n");
		
		printf("Informe a quantidade de produtos vendidos: ");
		scanf("%d", &novaVenda->quantidade);

		int valido;

		do {
			valido = 1;
			
			for(int i = 0 ; i < qntProdutos ; i++) {
				if(novaVenda->quantidade > produtos[i].qntEstoque) {
					printf("\nNão há essa quantidade deste produto no estoque. Tente novamente!\n");					
					printf("Informe a quantidade de produtos vendidos: ");
					scanf("%d", &novaVenda->quantidade);
										
					valido = 0;
					break;
				}
			}
		} while(!valido) ;
		
		fflush(stdin);
		
		do {
			printf("\nInforme a data da venda (ex.: dd/mm/aaaa): ");
			fgets(novaVenda->dataVenda, sizeof(novaVenda->dataVenda), stdin);
			limparEnter(novaVenda->dataVenda);
			
			fflush(stdin);
		} while(!validarData(novaVenda->dataVenda));
		
		Produto *prodSelecionado = &produtos[idProduto - 1];
		valorTotal = novaVenda->quantidade * prodSelecionado->precoUnidade;
		
		formaPagamento(qntVendas, valorTotal);
		
		novaVenda->totalVenda += valorTotal;		
		prodSelecionado->qntVendas++;				
		prodSelecionado->totalVendas += valorTotal;		
		categorias[prodSelecionado->idxCategoria].qntVendas++;
		categorias[prodSelecionado->idxCategoria].totalVendas += valorTotal;
		categorias[prodSelecionado->idxCategoria].subcategorias[prodSelecionado->idxSubcategoria].qntVendas++;
		categorias[prodSelecionado->idxCategoria].subcategorias[prodSelecionado->idxSubcategoria].totalVendas += valorTotal;
		prodSelecionado->qntEstoque -= venda[qntVendas].quantidade;
		novaVenda->idFuncionario = (confirmacaoFuncionario == 's') ? idFuncionario - 1 : -1;
		novaVenda->idCliente = (confirmacaoCliente == 's') ? idCliente - 1 : -1;
		
		clientes[idCliente - 1].qntCompras++; //novo
		clientes[idCliente - 1].totalComprado += valorTotal; //novo
		funcionario[idFuncionario - 1].qntVendas++; //novo
		funcionario[idFuncionario - 1].totalVendas += valorTotal; //novo
		qntVendas++;
		
		fflush(stdin);
		
		do {
			printf("Deseja cadastrar mais alguma venda (s/n)?: ");
			fgets(entrada, sizeof(entrada), stdin);
			limparEnter(entrada);
			
			op = tolower(entrada[0]);
			
			system("cls");			
		} while(op != 's' && op != 'n');
	} while (op == 's');
}

// Relatório
void relatorioGeral() {
	//Faturamento do mês atual
	//Mês que mais vendeu 
	//Mês com menos vendas
	//Média de venda mensal (quantidade/valor)
	//Produto com mais vendas
	//Funcionário que mais vendeu
	//Cliente cadastrado com mais compras
	//categorias com mais vendas
}
void menuRelatorio() {
	//relatório geral (resumão)
	//relatório de vendas
	//relatório de produtos
	//relatório de funcionários
	//relatório de clientes
	//relatório de categorias
	
	//talvez não seja necessário ter um menu de relatório, mas vou vendo ao decorrer do código
	char op, entrada[15];
	
	while(1) {
		printf("| Menu - Relatório\n");
		printf("---------------------------\n\n");
		
		printf("1- Relatório geral\n");
		printf("2- Relatório de vendas\n");
		printf("3- Relatório de produtos\n");
		printf("4- Relatório de funcionários\n");
		printf("5- Relatório de clientes\n");
		printf("6- Relatório de categorias\n");
		
		printf("Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = entrada[0];
		system("cls");
		
		switch(op) {
			case '1':
				break;
			case '2':
				break;
			case '3':
				break;
			case '4':
				break;
			case '5':
				break;
			case '6':
				break;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

// Menus > Menu Painel
void menuCadastrar() {
	char op, entrada[15];
	int cadastrofunc = 0;
	
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
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				cadastrarVenda();
				break;
			case '2':
				cadastrarCliente();
				break;
			case '3':
				cadastrarProduto();
				break;
			case '4':
				cadastrarFuncionario(funcionario);
				break;
			case '5':
				cadastrarCategoria();
				break;
			case '6':
				cadastrarSubcategoria();
				break;
			case '7':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuListar() {
	char op, entrada[15];
	
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
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				listarProdutos();
				break;
			case '2':
				listarClientes();
				break;
			case '3':
				listarFuncionarios();
				break;
			case '4':
				listarVendas();
				break;
			case '5':
				listarCategorias();
				break;
			case '6':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuEditar() {
	char op, entrada[15];
	
	while(1) {
		printf("| Menu - Editar informações\n");
		printf("---------------------------\n\n");
		
		printf("1- Editar venda\n");
		printf("2- Editar cliente\n");
		printf("3- Editar produto\n");
		printf("4- Editar funcionário\n");
		printf("5- Editar categoria\n");
		printf("6- Editar subcategoria\n");
		printf("7- Voltar ao menu\n\n");
			
		printf("-> Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				//editarVenda();
				break;
			case '2':
				//editarCliente();
				break;
			case '3':
				editarProduto();
				break;
			case '4':
				editarFuncionario();
				break;
			case '5':
				editarCategoria();
				break;
			case '6':
				editarSubcategoria();
				break;
			case '7':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuRemover() {
	char op, entrada[15];
	
	while(1) {
		printf("| Menu - Remover informações\n");
		printf("---------------------------\n\n");
		
		printf("1- Remover venda\n");
		printf("2- Remover cliente\n");
		printf("3- Remover produto\n");
		printf("4- Remover funcionário\n");
		printf("5- Remover categoria\n");
		printf("6- Remover subcategoria\n");
		printf("7- Voltar ao menu\n\n");
			
		printf("-> Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				//removerVenda();
				break;
			case '2':
				//removerCliente();
				break;
			case '3':
				removerProduto();
				break;
			case '4':
				removerFuncionario();
				break;
			case '5':
				removerCategoria();
				break;
			case '6':
				removerSubcategoria();
				break;
			case '7':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void menuEditarRemover() {
	char op, entrada[15];
	
	while(1) {
		printf("| Menu - Editar/remover informações\n");
		printf("---------------------------\n\n");
		
		printf("1- Editar\n");
		printf("2- Remover\n");
		printf("3- Voltar ao menu\n\n");
		
		printf("-> Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				menuEditar();
				break;
			case '2':
				menuRemover();
				break;
			case '3':
				return;
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

int menuPainel() {
	char op, entrada[15];
	
	while(1) {
		printf("| Menu Painel\n");
		printf("---------------------------\n\n");				
		
		printf("1- Cadastrar informações\n");				
		printf("2- Listar informações\n");			
		printf("3- Editar/remover informações\n");		
		printf("4- Acessar relatório\n");		
		printf("5- Voltar ao menu\n\n");
		
		printf("-> Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				menuCadastrar();
				break;
			case '2':
				menuListar();
				break;				
			case '3':
				menuEditarRemover();
				break;				
			case '4':
				printf("Relatório acessado!\n\n");
				//exibirRelatorio();
				break;				
			case '5':
				while(1) {
					printf("Tem certeza que deseja voltar para a tela de login? (s/n): ");
					fgets(entrada, sizeof(entrada), stdin);
					limparEnter(entrada);
					
					op = tolower(entrada[0]);
										
					system("cls");
					
					switch(op) {
						case 's': return 2; break;
						case 'n': menuPainel(); break;
						default: printf("Escolha uma opção válida");
					}
				}
				break;				
			default:
				printf("Escolha uma opção válida!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

void cadastroUsuario(Usuario usuario[], int *cadastro) {
    int tamanhoSenha, tamanhoCpf;
    int index = *cadastro;
    char entrada[50];
    
    Usuario *novoUsuario = &usuario[index];

	exibirHeader("Bem-Vindo(a)!!");

	//validar se o email possui "@"
    printf("Email: ");
    fgets(novoUsuario->email, sizeof(novoUsuario->email), stdin);
    limparEnter(novoUsuario->email);

    do {
        printf("Informe CPF: ");
        fgets(novoUsuario->cpf, sizeof(novoUsuario->cpf), stdin);
        limparEnter(novoUsuario->cpf);        
        tamanhoCpf = strlen(novoUsuario->cpf);
    } while (!verificacao(tamanhoCpf, 11, "CPF") || !somenteReais(novoUsuario->cpf));

    printf("Informe Nome de usuário: ");
    fgets(novoUsuario->usuario, sizeof(novoUsuario->usuario), stdin);
    limparEnter(novoUsuario->usuario);
    
    do {
        printf("Informe uma senha com no mínimo 8 caracteres: ");
        fgets(novoUsuario->senha, sizeof(novoUsuario->senha), stdin);
        limparEnter(novoUsuario->senha);
        tamanhoSenha = strlen(novoUsuario->senha);
        
        if(tamanhoSenha < 8) printf("\nSenha inválida!!\n\n");
    } while (tamanhoSenha < 8);

    (*cadastro)++;
    printf("\n\nUsuário cadastrado com sucesso!!!\n");
}

//Ainda não está sendo usado, pois será criado um menu de empresas por usuário *
void cadastroEmpresa(Empresa empresa[], int *cadastroEM) {
    if(*cadastroEM >= MAX_EMPRESAS) {
        printf("\nLimite de cadastros Atingido!!");
        printf("\nSeu limite de CNPJ atual é %i \n", MAX_EMPRESAS);
        return;
    }

    int tamanhoCnpj, tamanhoTel;
    int index = *cadastroEM;
    
    Empresa *novaEmpresa = &empresa[index];

    printf("\nInforme o nome da sua empresa: ");
    fgets(novaEmpresa->nomeEmpresa, sizeof(novaEmpresa->nomeEmpresa), stdin);
    limparEnter(novaEmpresa->nomeEmpresa);

    printf("\nInforme Nome do Responsavel: ");
    fgets(novaEmpresa->responsavel, sizeof(novaEmpresa->responsavel), stdin);
    limparEnter(novaEmpresa->responsavel);

    do {
        printf("\nInforme o CNPJ: ");
        fgets(novaEmpresa->cnpj, sizeof(novaEmpresa->cnpj), stdin);
        limparEnter(novaEmpresa->cnpj);
        tamanhoCnpj = strlen(novaEmpresa->cnpj);
    } while (!verificacao(tamanhoCnpj, 14, "CNPJ") || !somenteReais(novaEmpresa->cnpj));

    do {
        printf("\nInforme Numero de Telefone/Celular: ");
        fgets(novaEmpresa->tel, sizeof(novaEmpresa->tel), stdin);
        limparEnter(novaEmpresa->tel);
        tamanhoTel = strlen(novaEmpresa->tel);
    } while (!verificacao(tamanhoTel, 11, "Telefone") || !somenteReais(novaEmpresa->tel));

    printf("Cadastro Feito com sucesso!!!\n\n");
    (*cadastroEM)++;
}

void login(Usuario usuario[], int totalUsuarios) {
    char nomeUsuario[50];
    char senhaUsuario[50];
    int encontrado = 0;

    system("cls");
    exibirHeader("Login");
    
    printf("Usuário: ");
    fgets(nomeUsuario, sizeof(nomeUsuario), stdin);
    limparEnter(nomeUsuario);

    printf("Senha: ");
    fgets(senhaUsuario, sizeof(senhaUsuario), stdin);
    limparEnter(senhaUsuario);

    for(int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuario[i].usuario, nomeUsuario) == 0 && strcmp(usuario[i].senha, senhaUsuario) == 0) {
            encontrado = 1;
            break;
        }
    }
    
    nomeUsuario[0] = toupper(nomeUsuario[0]);
	    
    encontrado = 1; // Adicionei para facilitar o acesso/teste de outras funções do sistema

    if(encontrado) {
        printf("\nLogin bem-sucedido! Bem-vindo(a) de volta, %s!\n\n", nomeUsuario);
        system("pause");
        system("cls");
        menuPainel();
    } else
        printf("\nUsuário ou senha incorretos!\n");
}

void menuInicial() {
	char op, entrada[15];
	int cadastrosUsuario = 0;
	
	while(1) {
		exibirHeader("Menu login/cadastro");
		printf("1- Login\n");
		printf("2- Cadastrar novo usuário\n");
		printf("3- Sair do sistema\n\n");
		
		printf("-> Escolha uma opção: ");
		fgets(entrada, sizeof(entrada), stdin);
		limparEnter(entrada);
		
		op = tolower(entrada[0]);
		
		system("cls");
		
		switch(op) {
			case '1':
				login(usuario, cadastrosUsuario);
				break;
			case '2':
				cadastroUsuario(usuario, &cadastrosUsuario);
				break;
			case '3':
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
	
	start();
	menuInicial();
}