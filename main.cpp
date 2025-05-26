#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define MAX_CLIENTES 100

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

struct Cliente {
	char nome[50];
	char cpf[12];
	char email[50];
	int idade;
};

struct Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

// Salva os clientes no arquivo
void salvarClientesEmArquivo() {
	FILE *arquivo = fopen("clientes.txt", "w");

	if (arquivo == NULL) {
		printf("Erro ao abrir o arquivo para salvar os clientes.\n");
		return;
	}

	for (int i = 0; i < totalClientes; i++) {
		fprintf(arquivo, "%s;%s;%s;%d\n",
			clientes[i].nome,
			clientes[i].cpf,
			clientes[i].email,
			clientes[i].idade
		);
	}

	fclose(arquivo);
	arquivo = NULL;
}

// Carrega os clientes do arquivo
void carregarClientesDoArquivo() {
	FILE *arquivo = fopen("clientes.txt", "r");

	if (arquivo == NULL) {
		// Arquivo ainda não existe
		return;
	}

	while (!feof(arquivo) && totalClientes < MAX_CLIENTES) {
		char linha[200];
		if (fgets(linha, sizeof(linha), arquivo)) {
			if (strlen(linha) > 1) {
				sscanf(linha, "%[^;];%[^;];%[^;];%d\n",
					clientes[totalClientes].nome,
					clientes[totalClientes].cpf,
					clientes[totalClientes].email,
					&clientes[totalClientes].idade
				);
				totalClientes++;
			}
		}
	}

	fclose(arquivo);
	arquivo = NULL;
}

// Função para cadastrar cliente
void cadastrarCliente() {
	if (totalClientes >= MAX_CLIENTES) {
		printf("Limite de clientes atingido!\n");
		return;
	}
	
	do {
    printf("CPF: ");
    if (fgets(clientes[totalClientes].cpf, 12, stdin) == NULL) {
        // Trata erro ou fim de arquivo, se desejar
        continue;
    }
    // Remove o '\n' se existir
    clientes[totalClientes].cpf[strcspn(clientes[totalClientes].cpf, "\n")] = '\0';

    size_t tamanho = strlen(clientes[totalClientes].cpf);

    if (tamanho != 11) {
        printf("\nCPF Invalido! Tente novamente: \n\n");
    } else {
        break;  // CPF válido, sai do loop
    }

} while (1);

	
	printf("---- Cadastro de Cliente ----\n");
	printf("Nome: ");
	fflush(stdin);
	fgets(clientes[totalClientes].nome, 50, stdin);
	clientes[totalClientes].nome[strcspn(clientes[totalClientes].nome, "\n")] = 0;

	do {
    printf("CPF: ");
    if (fgets(clientes[totalClientes].cpf, 12, stdin) == NULL) {
        // Trata erro ou fim de arquivo, se desejar
        continue;
    }
    // Remove o '\n' se existir
    clientes[totalClientes].cpf[strcspn(clientes[totalClientes].cpf, "\n")] = '\0';

    size_t tamanho = strlen(clientes[totalClientes].cpf);

    if (tamanho != 11) {
        printf("\nCPF Invalido! Tente novamente: \n\n");
    } else {
        break;  // CPF válido, sai do loop
    }

} while (1);

	printf("Email: ");
	fflush(stdin);
	fgets(clientes[totalClientes].email, 50, stdin);
	clientes[totalClientes].email[strcspn(clientes[totalClientes].email, "\n")] = 0;

	printf("Idade: ");
	scanf("%d", &clientes[totalClientes].idade);

	totalClientes++;
	salvarClientesEmArquivo(); // salvar após cadastro

	printf("Cliente cadastrado com sucesso!\n");
}

// Função para listar clientes
void listarClientes() {
	if (totalClientes == 0) {
		printf("Nenhum cliente cadastrado.\n");
		return;
	}

	printf("---- Lista de Clientes ----\n");
	for (int i = 0; i < totalClientes; i++) {
		printf("Cliente %d:\n", i + 1);
		printf("Nome: %s\n", clientes[i].nome);
		printf("CPF: %s\n", clientes[i].cpf);
		printf("Email: %s\n", clientes[i].email);
		printf("Idade: %d\n", clientes[i].idade);
		printf("----------------------------\n");
	}
}

// Menu de cadastro
void menuCadastrar() {
	int op;

	while (1) {
		printf("| Menu - Cadastrar informacoes\n");
		printf("---------------------------\n\n");

		printf("1- Cadastrar nova venda\n");
		printf("2- Cadastrar cliente\n");
		printf("3- Cadastrar produto\n");
		printf("4- Cadastrar funcionario\n");
		printf("5- Cadastrar categoria\n");
		printf("6- Cadastrar subcategoria\n");
		printf("7- Voltar ao menu\n\n");
		printf("-> Escolha uma opcao: ");
		scanf("%d", &op);

		system("cls");

		switch (op) {
		case 1:
			// cadastrarVenda();
			break;
		case 2:
			cadastrarCliente();
			break;
		case 3:
			// cadastrarProduto();
			break;
		case 4:
			// cadastrarFuncionario();
			break;
		case 5:
			// cadastrarCategoria();
			break;
		case 6:
			// cadastrarSubcategoria();
			break;
		case 7:
			printf("Voltando para o menu painel!\n\n");
			return;
		default:
			printf("Escolha uma opcao valida!\n\n");
		}

		system("pause");
		system("cls");
	}
}

// Menu de listagem
void menuListar() {
	int op;

	while (1) {
		printf("| Menu - Listar informacoes\n");
		printf("---------------------------\n\n");

		printf("1- Listar produtos\n");
		printf("2- Listar clientes\n");
		printf("3- Listar funcionarios\n");
		printf("4- Listar vendas\n");
		printf("5- Listar categorias\n");
		printf("6- Voltar ao menu\n\n");
		printf("-> Escolha uma opcao: ");
		scanf("%d", &op);

		system("cls");

		switch (op) {
		case 1:
			// listarProdutos();
			break;
		case 2:
			listarClientes();
			break;
		case 3:
			// listarFuncionario();
			break;
		case 4:
			// listarVendas();
			break;
		case 5:
			// listarCategorias();
			break;
		case 6:
			printf("Voltando para o menu painel!\n\n");
			return;
		default:
			printf("Escolha uma opcao valida!\n\n");
		}

		system("pause");
		system("cls");
	}
}

// Menu de edição (não implementado aqui)
void menuEditar() {
	int op;

	while (1) {
		printf("| Menu - Editar informacoes\n");
		printf("---------------------------\n\n");

		printf("1- Editar venda\n");
		printf("2- Remover venda\n");
		printf("3- Voltar ao menu\n\n");
		printf("-> Escolha uma opcao: ");
		scanf("%d", &op);

		system("cls");

		switch (op) {
		case 1:
			// editarVenda();
			break;
		case 2:
			// removerVenda();
			break;
		case 3:
			printf("Voltando para o menu painel!\n\n");
			return;
		default:
			printf("Escolha uma opcao valida!\n\n");
		}

		system("pause");
		system("cls");
	}
}

// Relatório (não implementado)
void exibirRelatorio() {
	// para desenvolver
}

// Menu principal
int menuPainel() {
	int op;

	while (1) {
		printf("| Menu Painel\n");
		printf("---------------------------\n\n");

		printf("1- Cadastrar informacoes\n");
		printf("2- Listar informações\n");
		printf("3- Editar\n");
		printf("4- Acessar relatorio\n");
		printf("5- Voltar ao menu\n\n");
		printf("-> Escolha uma opcao: ");
		scanf("%d", &op);

		system("cls");

		switch (op) {
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
			// exibirRelatorio();
			break;
		case 5:
			printf("Voltando para o menu!\n\n");
			return 2;
		default:
			printf("Escolha uma opção valida!\n\n");
		}

		system("pause");
		system("cls");
	}
}

// Simulação de login
void login() {
	printf("Login acessado! Redirecionando para o Menu Painel.\n\n");
	system("pause");
	system("cls");

	menuPainel();
}

// Menu inicial
void menuInicial() {
	int op;

	while (1) {
		printf("------ Menu login/cadastro ------\n\n");
		printf("1- Login\n");
		printf("2- Cadastrar novo usuario\n");
		printf("3- Sair do sistema\n\n");
		printf("-> Escolha uma opcao: ");
		scanf("%d", &op);

		system("cls");

		switch (op) {
		case 1:
			login();
			break;
		case 2:
			// cadastrar();
			break;
		case 3:
			printf("Encerrando sistema...\n\n");
			exit(0);
		default:
			printf("Opcao invalida!!\n\n");
		}

		system("pause");
		system("cls");
	}

	if (menuPainel() == 2) menuInicial();
}

// Função principal
int main() {
	setlocale(LC_ALL, "portuguese");

	carregarClientesDoArquivo(); // carregar clientes salvos
	menuInicial();
}