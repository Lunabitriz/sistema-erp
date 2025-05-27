#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

#define TAM 5
#define USU 20
#define FUN 100
#define MAX_VENDAS 100

struct Empresa {
    char nome[50];
    char responsavel[50];
    char cnpj[50];
    char tel[50];
};

struct Usuario {
    char usuario[50];
    char senha[50];
    char email[50];
    char cpf[50];
};

struct Funcionario {
    char funcionarioNome[50];
    char funcionarioCpf[50];
    char numeroFolha[50];
    char numeroPis[50];
    char empregador[50];
    char departamento[50];
    char funcao[50];
    char admissao[50];
};

struct Venda {
	char categoriaProduto[30];
	int quantidade;
	float precoUnidade;
	char formaPagamento[20];
	char tipoOperacao[15];
};

struct Empresa empresa[TAM];
struct Usuario usuario[USU];
struct Funcionario funcionario[FUN];
struct Venda venda[MAX_VENDAS];
int qtdVendas = 0;

int verificacao(int entrada, int tamanhoEsperado, char *nome) {
    if (entrada != tamanhoEsperado) {
        printf("%s Inválido!!!\n", nome);
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

void cadastroUsuario(struct Usuario usuario[], int *cadastro) {
    int tamanhoSenha, tamanhoCpf;
    int index = *cadastro;

    system("cls");
    getchar();

    printf("\nBem-Vindo!!!\n");

    printf("\nEmail: ");
    fgets(usuario[index].email, 50, stdin);
    usuario[index].email[strcspn(usuario[index].email, "\n")] = '\0';

    do {
        printf("\nInforme CPF: ");
        fgets(usuario[index].cpf, 50, stdin);
        usuario[index].cpf[strcspn(usuario[index].cpf, "\n")] = '\0';
        tamanhoCpf = strlen(usuario[index].cpf);
    } while (!verificacao(tamanhoCpf, 11, "CPF") || !somenteNumeros(usuario[index].cpf));

    printf("\nInforme Nome de usuário: ");
    fgets(usuario[index].usuario, 50, stdin);
    usuario[index].usuario[strcspn(usuario[index].usuario, "\n")] = '\0';

    do {
        printf("\nInforme uma senha com no mínimo 8 caractéres: ");
        fgets(usuario[index].senha, 50, stdin);
        usuario[index].senha[strcspn(usuario[index].senha, "\n")] = '\0';
        tamanhoSenha = strlen(usuario[index].senha);
    } while (!verificacao(tamanhoSenha, 8, "Senha"));

    printf("\n\nUsuário cadastrado!!!\n");
    (*cadastro)++;
    system("pause");
}

void cadastroEmpresa(struct Empresa empresa[], int *cadastroEM) {
    if (*cadastroEM >= TAM) {
        system("cls");
        printf("\nLimite de cadastros Atingido!!");
        printf("\nSeu limite de CNPJ atual é %i \n", TAM);
        system("pause");
        return;
    }

    int tamanhoCnpj, tamanhoTel;
    int index = *cadastroEM;

    system("cls");
    getchar();

    printf("\nInforme o nome da sua empresa: ");
    fgets(empresa[index].nome, 50, stdin);
    empresa[index].nome[strcspn(empresa[index].nome, "\n")] = '\0';

    printf("\nInforme Nome do Responsavel: ");
    fgets(empresa[index].responsavel, 50, stdin);
    empresa[index].responsavel[strcspn(empresa[index].responsavel, "\n")] = '\0';

    do {
        printf("\nInforme o CNPJ: ");
        fgets(empresa[index].cnpj, 50, stdin);
        empresa[index].cnpj[strcspn(empresa[index].cnpj, "\n")] = '\0';
        tamanhoCnpj = strlen(empresa[index].cnpj);
    } while (!verificacao(tamanhoCnpj, 14, "CNPJ") || !somenteNumeros(empresa[index].cnpj));

    do {
        printf("\nInforme Numero de Telefone/Celular: ");
        fgets(empresa[index].tel, 50, stdin);
        empresa[index].tel[strcspn(empresa[index].tel, "\n")] = '\0';
        tamanhoTel = strlen(empresa[index].tel);
    } while (!verificacao(tamanhoTel, 11, "Telefone") || !somenteNumeros(empresa[index].tel));

    printf("Cadastro Feito com sucesso!!!\n\n");
    (*cadastroEM)++;
}

void cadastroFuncionario(struct Funcionario funcionario[], int *cadastro) {
	
	
    if (*cadastro >= FUN) {
        system("cls");
        printf("Numero de funcionarios atingido!!!\n");
        printf("O seu limite atual de Funcionários é de %i", USU);
        system("pause");
        return;
    }

    int numeroCpf;
    int index = *cadastro;

    system("cls");
    getchar();

    printf("\nNome: ");
    fgets(funcionario[index].funcionarioNome, 50, stdin);
    funcionario[index].funcionarioNome[strcspn(funcionario[index].funcionarioNome, "\n")] = '\0';

    do {
        printf("\nCPF: ");
        fgets(funcionario[index].funcionarioCpf, 50, stdin);
        funcionario[index].funcionarioCpf[strcspn(funcionario[index].funcionarioCpf, "\n")] = '\0';
        numeroCpf = strlen(funcionario[index].funcionarioCpf);
    } while (!verificacao(numeroCpf, 11, "CPF") || !somenteNumeros(funcionario[index].funcionarioCpf));

    printf("\nNumero da folha: ");
    fgets(funcionario[index].numeroFolha, 50, stdin);
    funcionario[index].numeroFolha[strcspn(funcionario[index].numeroFolha, "\n")] = '\0';

    printf("\nNumero PIS: ");
    fgets(funcionario[index].numeroPis, 50, stdin);
    funcionario[index].numeroPis[strcspn(funcionario[index].numeroPis, "\n")] = '\0';

    printf("\nNome do empregador: ");
    fgets(funcionario[index].empregador, 50, stdin);
    funcionario[index].empregador[strcspn(funcionario[index].empregador, "\n")] = '\0';

    printf("\nDepartamento: ");
    fgets(funcionario[index].departamento, 50, stdin);
    funcionario[index].departamento[strcspn(funcionario[index].departamento, "\n")] = '\0';

    printf("\nFunção: ");
    fgets(funcionario[index].funcao, 50, stdin);
    funcionario[index].funcao[strcspn(funcionario[index].funcao, "\n")] = '\0';

    printf("\nDia da admissão: ");
    fgets(funcionario[index].admissao, 50, stdin);
    funcionario[index].admissao[strcspn(funcionario[index].admissao, "\n")] = '\0';

    printf("Funcionario cadastrado!!!!\n");
    (*cadastro)++;
}

void menuPainel() {
    int op;
    int cadastroEm = 0;
    int cadastrofun = 0;

    while (1) {
        printf("0- Cadastrar empresa \n");
        printf("1- Cadastrar nova venda\n");
        printf("2- Cadastrar novo funcionario\n");
        printf("3- Voltar ao menu\n");
        printf("4- Listar vendas\n\n");
        printf("Escolha uma opção: ");
        scanf("%d", &op);

        system("cls");

        switch (op) {
            case 0:
                cadastroEmpresa(empresa, &cadastroEm);
                break;
            case 1:
                //cadastrarVenda();
                break;
            case 2:
                cadastroFuncionario(funcionario, &cadastrofun);
                break;
            case 3:
            		
                return;         
            case 4:
            		//listarVendas();
                return;
            default:
                printf("Opção inválida!!\n\n");
        }

        system("pause");
        system("cls");
    }
}

void login(struct Usuario usuario[], int totalUsuarios) {
    char nomeUsuario[50];
    char senhaUsuario[50];
    int encontrado = 0;

    system("cls");
    getchar();

    printf("\n----- LOGIN -----\n");
    printf("Usuário: ");
    fgets(nomeUsuario, 50, stdin);
    nomeUsuario[strcspn(nomeUsuario, "\n")] = '\0';

    printf("Senha: ");
    fgets(senhaUsuario, 50, stdin);
    senhaUsuario[strcspn(senhaUsuario, "\n")] = '\0';

    for (int i = 0; i < totalUsuarios; i++) {
        if (strcmp(usuario[i].usuario, nomeUsuario) == 0 && strcmp(usuario[i].senha, senhaUsuario) == 0) {
            encontrado = 1;
            break;
        }
    }

    if (encontrado) {
        printf("\nLogin bem-sucedido!\n");
        system("pause");
        system("cls");
        printf("Bem-vindo(a) %s!!! \n\n", nomeUsuario);
        menuPainel();
    } else {
        printf("\nUsuário ou senha incorretos!\n");
    }
    system("pause");
}

void menu() {
    system("cls");
    printf(" Bem-Vindo ao Menu!!! \n\n\n");

    printf(" ------------------ \n");
    printf("| 1- Cadastrar-se  |\n");
    printf("| 2- Login         |\n");
    printf("| 3- Sair          |\n");
    printf(" ------------------ \n");
    printf("\nSua escolha: ");
}

int main() {
    setlocale(LC_ALL, "portuguese");
    int escolha;
    int cadastrosUsuario = 0;

    while (1) {
        menu();
        scanf("%i", &escolha);

        switch (escolha) {
            case 1:
                cadastroUsuario(usuario, &cadastrosUsuario);
                break;
            case 2:
                login(usuario, cadastrosUsuario);
                break;
            case 3:
                system("cls");
                printf("\nSaindo....bip...bip...bop..\n");
                exit(0);
                break;
            default:
                system("cls");
                printf("Número inválido, Tente novamente!!  \n\n");
                system("pause");
                break;
        }
    }
}