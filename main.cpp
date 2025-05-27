#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <locale.h>

#define MAX_EMPRESAS 5
#define MAX_USERS 20

struct Usuario {
    char usuario[50];
	//char genero[50]; 
    char email[50];
    char senha[50];
    char cpf[50];
	//int idade;
};

struct Empresa {
    char nomeEmpresa[50];
    char responsavel[50];
    char cnpj[50];
    char tel[50];
//	int porteEmpresa;
//	int tempoAtuacao;
//	float rendaMensal;
//	float metaLucro;
};

struct Empresa empresa[MAX_EMPRESAS];
struct Usuario usuario[MAX_USERS];

int verificacao(int entrada, int tamanhoEsperado, char *nome) {
    if (entrada != tamanhoEsperado) {
        printf("\n%s Inválido!!\n\n", nome);
        return 0;
    }
    return 1;
}

int somenteNumeros(char str[]) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] < '0' || str[i] > '9') {
            return 0;
        }
    }
    return 1;
}

void limparEnter(char atrr[]) {
	atrr[strcspn(atrr, "\n")] = '\0';
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

void cadastroUsuario(struct Usuario usuario[], int *cadastro) {
    int tamanhoSenha, tamanhoCpf;
    int index = *cadastro;
    
    Usuario *novoUsuario = &usuario[index];

    getchar();
//    system("cls");
    printf("------ Bem-Vindo!! ------\n\n");

    printf("Email: ");
    fgets(novoUsuario->email, sizeof(novoUsuario->email), stdin);
    limparEnter(novoUsuario->email);

    do {
        printf("Informe CPF: ");
        fgets(novoUsuario->cpf, sizeof(novoUsuario->cpf), stdin);
        limparEnter(novoUsuario->cpf);        
        tamanhoCpf = strlen(novoUsuario->cpf);
    } while (!verificacao(tamanhoCpf, 11, "CPF") || !somenteNumeros(novoUsuario->cpf));

    printf("Informe Nome de usuário: ");
    fgets(novoUsuario->usuario, sizeof(novoUsuario->usuario), stdin);
    limparEnter(novoUsuario->usuario);
    
	/*
	Antes não permitia senhas acima de 8 dígitos
    do {
        printf("Informe uma senha com no mínimo 8 caractéres: ");
        fgets(novoUsuario->senha, sizeof(novoUsuario->senha), stdin);
        limparEnter(novoUsuario->senha);
        tamanhoSenha = strlen(novoUsuario->senha);
    } while (!verificacao(tamanhoSenha, 8, "Senha"));
    */
    
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

void cadastroEmpresa(struct Empresa empresa[], int *cadastroEM) {
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
    } while (!verificacao(tamanhoCnpj, 14, "CNPJ") || !somenteNumeros(novaEmpresa->cnpj));

    do {
        printf("\nInforme Numero de Telefone/Celular: ");
        fgets(novaEmpresa->tel, sizeof(novaEmpresa->tel), stdin);
        limparEnter(novaEmpresa->tel);
        tamanhoTel = strlen(novaEmpresa->tel);
    } while (!verificacao(tamanhoTel, 11, "Telefone") || !somenteNumeros(novaEmpresa->tel));

    printf("Cadastro Feito com sucesso!!!\n\n");
    (*cadastroEM)++;
}

void login(struct Usuario usuario[], int totalUsuarios) {
    char nomeUsuario[50];
    char senhaUsuario[50];
    int encontrado = 0;

    system("cls");
    getchar();

    printf("------ LOGIN ------\n\n");
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

    if(encontrado) {
        printf("\nLogin bem-sucedido! Bem-vindo(a) de volta, %s!\n\n", nomeUsuario);
        system("pause");
        system("cls");
//        printf("Bem-vindo(a), %s! \n\n", nomeUsuario);
        menuPainel();
    } else
        printf("\nUsuário ou senha incorretos!\n");
}

void menuInicial() {
	int op;	
	int cadastrosUsuario = 0;
	
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