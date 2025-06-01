#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_FUNC 100
#define MAX_USERS 20
#define MAX_CATEG 20
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

typedef struct {
    char nomeFuncionario[50];
    char cpf[50];
    char numeroFolha[50];
    char numeroPis[50];
    char empregador[50];
    char departamento[50];
    char funcao[50];
    char admissao[50];
} Funcionario;

typedef struct {
    char nome[50];
    char cpf[20];
    char email[50];
    int idade[20];
    int qntCompras; //novo
    float valorPendente; //novo
    float totalComprado; //novo
} Cliente;

Produtos produtos[MAX_PRODUTOS];
Categoria categorias[MAX_CATEG];
Cliente clientes[MAX_CLIENTES];
Empresa empresa[MAX_EMPRESAS];
Usuario usuario[MAX_USERS];
Funcionario funcionario[MAX_FUNC];

int qntCategorias = 0;
int qntProdutos = 0;
int totalClientes = 0;

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

void limparEnter(char atrr[]) {
	atrr[strcspn(atrr, "\n")] = '\0';
}

void exibirHeader(char mensagem[]) {
	printf("------- %s: -------\n\n", mensagem);
}

void cadastrarCategoria() {	
	int existe;
	char op, entradaChar[20], entrada[50];
	
	Categoria *novaCategoria = &categorias[qntCategorias];
	novaCategoria->qntSubcategorias = 0;
	
	getchar();
	
	do {
		existe = 0;
		exibirHeader("Cadastro nova categoria");
				
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

void cadastrarSubcategoria() {
	char nomeNovaSubcat[50];
	int idCategoria, existe;
	
	if(qntCategorias == 0) 
		printf("Nenhuma categoria cadastrada no sistema!\nPor favor, cadastre uma categoria primeiro.\n\n");
	else {		
		printf("Categorias cadastradas: \n\n");
		
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
	
	exibirHeader("Cadastro Novo Produto");
	
	getchar();
	printf("Informe o nome do produto: ");
	fgets(novoProd->nome, sizeof(novoProd->nome), stdin);
	limparEnter(novoProd->nome);
	
	if(qntCategorias > 0) {
		int idxCategoria, idxSubcategoria;
		novoProd->qntCategorias = 0;

		system("cls");
		exibirHeader("Cadastro Novo Produto");		
		printf("| Categorias cadastradas:\n");
		
		for(int i = 0; i < qntCategorias; i++)
			printf("\tCategoria %d: %s\n", i + 1, categorias[i].nome);
		
		do {			
			printf("\nSelecione a categoria do produto (de 1 a %d): ", qntCategorias);
			scanf("%d", &idxCategoria);				
		} while(idxCategoria < 1 || idxCategoria > qntCategorias);
		
		novoProd->idxCategoria = idxCategoria - 1;
		Categoria *categoriaSelecionada = &categorias[novoProd->idxCategoria];
		
		if(categoriaSelecionada->qntSubcategorias > 0) {	
			system("cls");
			exibirHeader("Cadastro Novo Produto");						
			printf("| Subcategorias cadastradas de '%s':\n", categorias[novoProd->idxCategoria]);
			
			for(int i = 0; i < categoriaSelecionada->qntSubcategorias; i++)
				printf("\tSubcategoria %d: %s\n", i + 1, categoriaSelecionada->subcategorias[i].nome);
			
			do {
				printf("\nSelecione a subcategoria: ");
				scanf("%d", &idxSubcategoria);	
			} while(idxSubcategoria < 1 || idxSubcategoria > categoriaSelecionada->qntSubcategorias);
			
			novoProd->idxSubcategoria = idxSubcategoria - 1;
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
	
	exibirHeader("Produtos cadastrados");
	
	for(int i = 0; i < qntProdutos; i++) {
		printf("| Produto %d:\n\n", i + 1);
		
		printf("Código do produto: %d\n", produtos[i].codigoProduto);
		printf("Nome do produto: %s\n", produtos[i].nome);
		printf("Preço de custo: R$%.2f\n", produtos[i].precoCusto);
		printf("Preço de venda: R$%.2f\n", produtos[i].precoUnidade);		
		printf("Quantidade em estoque: %d\n", produtos[i].qntEstoque);
		
		if(produtos[i].qntCategorias > 0)
			printf("Categorias do produto: %s\n", categorias[produtos[i].idxCategoria]);
		else
			printf("Categorias do produto: não informado\n");
			
		if(categorias[produtos[i].idxCategoria].qntSubcategorias > 0)
			printf("Subcategorias do produto: %s\n", categorias[produtos[i].idxCategoria].subcategorias[produtos[i].idxSubcategoria].nome);
		else 
			printf("Subcategorias do produto: não informado\n");
			
		printf("\n------------------------\n");
	}
}

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

	int sizeCpf;
	Cliente *novoCliente = &clientes[totalClientes];

    exibirHeader("Cadastro de Cliente");

	getchar();
    printf("Informe seu nome: ");
    fgets(novoCliente->nome, sizeof(novoCliente->nome), stdin);
    limparEnter(novoCliente->nome);

	do {
	    printf("Informe seu CPF: ");
	    fgets(novoCliente->cpf, sizeof(novoCliente->cpf), stdin);
	    limparEnter(novoCliente->cpf);
			    
	    sizeCpf = strlen(novoCliente->cpf);
	} while (!verificacao(sizeCpf, 11, "CPF"));

	//getchar();
	printf("Informe seu e-mail: ");
	fgets(novoCliente->email, sizeof(novoCliente->email), stdin);
	limparEnter(novoCliente->email);	
	
	printf("Informe sua idade: ");
	
	while (1) { // Garante que não há lixo no buffer antes de scanf
		char entrada[10];		
		fgets(entrada, sizeof(entrada), stdin);		
		
		if(sscanf(entrada, "%d", &novoCliente->idade) == 1 && novoCliente->idade > 0)
		    break;
		else 
		    printf("Idade inválida. Tente novamente: ");
	}
	
	totalClientes++;
	printf("\nCliente cadastrado com sucesso!\n");
}

void listarClientes() {
    if (totalClientes == 0) {
        printf("Nenhum cliente cadastrado.\n");
        return;
    }

    exibirHeader("Clientes cadastrados");
	    
    for (int i = 0; i < totalClientes; i++) {
        printf("| Cliente %d: \n\n", i + 1);
        
        printf("Nome: %s\n", clientes[i].nome);
        printf("CPF: %s\n", clientes[i].cpf);
        printf("Email: %s\n", clientes[i].email);
        printf("Idade: %d\n", clientes[i].idade);
        //exibir -> qnt de compras feitas
        //exibir -> Valor total comprado na empresa
        //exibir -> valor pendente (caso fiado)        
        printf("----------------------------\n");
    }
}

void cadastrarFuncionario(Funcionario funcionario[], int *cadastro) {	
    if (*cadastro >= MAX_FUNC) {
        system("cls");
        printf("Numero de funcionarios atingido!!!\n");
        printf("O seu limite atual de Funcionários é de %i", MAX_USERS);
        system("pause");
        return;
    }

    int numeroCpf;
    int index = *cadastro;
    
    Funcionario *novoFunc = &funcionario[index];

    getchar();
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

    printf("\nNumero da folha: ");
    fgets(novoFunc->numeroFolha, sizeof(novoFunc->numeroFolha), stdin);
    limparEnter(novoFunc->numeroFolha);

    printf("Numero PIS: ");
    fgets(novoFunc->numeroPis, sizeof(novoFunc->numeroPis), stdin);
    limparEnter(novoFunc->numeroPis);

    printf("\nNome do empregador: ");
    fgets(novoFunc->empregador, sizeof(novoFunc->empregador), stdin);
    limparEnter(novoFunc->empregador);

    printf("Departamento: ");
    fgets(novoFunc->departamento, sizeof(novoFunc->departamento), stdin);
    limparEnter(novoFunc->departamento);

    printf("Função: ");
    fgets(novoFunc->funcao, sizeof(novoFunc->funcao), stdin);
    limparEnter(novoFunc->funcao);

    printf("\nDia da admissão: ");
    fgets(novoFunc->admissao, sizeof(novoFunc->admissao), stdin);
    limparEnter(novoFunc->admissao);

    printf("\nFuncionario cadastrado!!!!\n");
    (*cadastro)++;
}

void menuCadastrar() {
	int op;
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
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//cadastrarVenda();
				break;
			case 2:
				cadastrarCliente();
				break;
			case 3:
				cadastrarProduto();
				break;
			case 4:
				cadastrarFuncionario(funcionario, &cadastrofunc);
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
				//listarVendas();
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

void cadastroUsuario(Usuario usuario[], int *cadastro) {
    int tamanhoSenha, tamanhoCpf;
    int index = *cadastro;
    char entrada[50];
    
    Usuario *novoUsuario = &usuario[index];

    getchar();
	exibirHeader("Bem-Vindo(a)!!");

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
        
        if(tamanhoSenha < 8)
        	printf("\nSenha inválida!!\n\n");
    } while (tamanhoSenha < 8);

    (*cadastro)++;
    printf("\n\nUsuário cadastrado com sucesso!!!\n");
}

void cadastroEmpresa(Empresa empresa[], int *cadastroEM) {
    if(*cadastroEM >= MAX_EMPRESAS) {
        system("cls");
        printf("\nLimite de cadastros Atingido!!");
        printf("\nSeu limite de CNPJ atual é %i \n", MAX_EMPRESAS);
        system("pause");
        return;
    }

    int tamanhoCnpj, tamanhoTel;
    int index = *cadastroEM;
    
    Empresa *novaEmpresa = &empresa[index];

    system("cls");
    getchar();

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
    getchar();

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
	int op;	
	int cadastrosUsuario = 0;
	
	while(1) {
		exibirHeader("Menu login/cadastro");
		printf("1- Login\n");
		printf("2- Cadastrar novo usuário\n");
		printf("3- Sair do sistema\n\n");
		printf("-> Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				login(usuario, cadastrosUsuario);
				break;
			case 2:
				cadastroUsuario(usuario, &cadastrosUsuario);
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