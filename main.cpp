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
    int idade[20];
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
    int idade[20];
};

struct Cliente clientes[MAX_CLIENTES];
int totalClientes = 0;

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

void exibirTelaInicial() {
    limparTela();
    printf("====================================\n");
    printf("         BEM-VINDO AO SISTEMA       \n");
    printf("              SENAI ERP             \n");
    printf("====================================\n\n");

    int opcao;
    do {
        printf("1 - Deseja Entrar no Sistema? \n");
        printf("2 - Deseja Sair do Sistema?  \n");
        printf("-> Escolha: ");
        if (scanf("%d", &opcao) != 1) {
            limparBuffer();
            opcao = 0;
        } else {
            limparBuffer();
        }

        if (opcao == 2) {
            printf("Saindo do sistema...\n");
            exit(0);
        } else if (opcao != 1) {
            printf("Opção invalida! Tente novamente.\n");
        }

    } while (opcao != 1);

    limparTela();
}

int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return 0;
    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') return 0;
    }
    return 1;
}

void salvarClientesEmArquivo() {
    FILE *arquivo = fopen("clientes.txt", "w");
    if (!arquivo) {
        printf("Erro ao abrir o arquivo para salvar os clientes.\n");
        return;
    }
    for (int i = 0; i < totalClientes; i++) {
        fprintf(arquivo, "%s;%s;%s;%d\n",
                clientes[i].nome,
                clientes[i].cpf,
                clientes[i].email,
                clientes[i].idade);
    }
    fclose(arquivo);
}

void carregarClientesDoArquivo() {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (!arquivo) return;

    char linha[200];
    while (totalClientes < MAX_CLIENTES && fgets(linha, sizeof(linha), arquivo)) {
        if (strlen(linha) > 1) {
            sscanf(linha, "%49[^;];%11[^;];%49[^;];%d",
                   clientes[totalClientes].nome,
                   clientes[totalClientes].cpf,
                   clientes[totalClientes].email,
                   &clientes[totalClientes].idade);
            totalClientes++;
        }
    }

    fclose(arquivo);
}

void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    printf("---- Cadastro de Cliente ----\n\n");

    printf("Informe seu nome: ");
    fgets(clientes[totalClientes].nome, sizeof(clientes[totalClientes].nome), stdin);
    clientes[totalClientes].nome[strcspn(clientes[totalClientes].nome, "\n")] = '\0';

    // CPF
do {
    printf("Informe seu CPF: ");
    fgets(clientes[totalClientes].cpf, sizeof(clientes[totalClientes].cpf), stdin);
    clientes[totalClientes].cpf[strcspn(clientes[totalClientes].cpf, "\n")] = '\0';

    if (!validarCPF(clientes[totalClientes].cpf)) {
        printf("CPF inválido! Deve conter 11 dígitos numéricos.\n");
    } else {
        break;
    }
} while (1);

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
    salvarClientesEmArquivo();
    printf("Cliente cadastrado com sucesso!\n");
}

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

void menuCadastrar() {
    int op;
    while (1) {
        printf("| Menu - Cadastrar informações\n");
        printf("------------------------------\n\n");

        printf("1- Cadastrar nova venda\n");
        printf("2- Cadastrar cliente\n");
        printf("3- Cadastrar produto\n");
        printf("4- Cadastrar funcionario\n");
        printf("5- Cadastrar categoria\n");
        printf("6- Cadastrar subcategoria\n");
        printf("7- Voltar ao menu\n\n");
        printf("-> Escolha uma opcao: ");
        scanf("%d", &op);
        limparBuffer();

        limparTela();

        switch (op) {
            case 1:
            case 3:
            case 4:
            case 5:
            case 6:
                printf("Funcionalidade não implementada ainda.\n");
                break;
            case 2:
                cadastrarCliente();
                break;
            case 7:
                return;
            default:
                printf("Escolha uma opção valida!\n");
        }

        printf("Pressione Enter para continuar...");
        getchar();
        limparTela();
    }
}

void menuListar() {
    int op;

    while (1) {
        printf("| Menu - Listar informações\n");
        printf("----------------------------\n\n");

        printf("1- Listar produtos\n");
        printf("2- Listar clientes\n");
        printf("3- Listar funcionários\n");
        printf("4- Listar vendas\n");
        printf("5- Listar categorias\n");
        printf("6- Voltar ao menu\n\n");
        printf("-> Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        limparTela();

        switch (op) {
            case 2:
                listarClientes();
                break;
            case 1:
            case 3:
            case 4:
            case 5:
                printf("Funcionalidade não implementada ainda.\n");
                break;
            case 6:
                return;
            default:
                printf("Escolha uma opção válida!\n");
        }

        printf("Pressione Enter para continuar...");
        getchar();
        limparTela();
    }
}

void menuEditar() {
    int op;

    while (1) {
        printf("| Menu - Editar informações\n");
        printf("-----------------------------\n\n");

        printf("1- Editar venda\n");
        printf("2- Remover venda\n");
        printf("3- Voltar ao menu\n\n");
        printf("-> Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        limparTela();

        switch (op) {
            case 1:
            case 2:
                printf("Funcionalidade não implementada ainda.\n");
                break;
            case 3:
                return;
            default:
                printf("Escolha uma opção válida!\n");
        }

        printf("Pressione Enter para continuar...");
        getchar();
        limparTela();
    }
}

void exibirRelatorio() {
    printf("Funcionalidade de relatório não implementada ainda.\n");
}

int menuPainel() {
    int op;

    while (1) {
        printf("| Menu Painel\n");
        printf("---------------------------\n\n");

        printf("1- Cadastrar informações\n");
        printf("2- Listar informações\n");
        printf("3- Editar\n");
        printf("4- Acessar relatório\n");
        printf("5- Voltar ao menu\n\n");
        printf("-> Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        limparTela();

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
                exibirRelatorio();
                break;
            case 5:
                return 0;
            default:
                printf("Escolha uma opção válida!\n");
        }

        printf("Pressione Enter para continuar...");
        getchar();
        limparTela();
    }
}

void login() {
    printf("Login acessado! Redirecionando para o Menu Painel.\n");
    printf("Pressione Enter para continuar...");
    getchar();
    limparTela();
    menuPainel();
}

void menuInicial() {
    int op;

    while (1) {
        printf("------ Menu login/cadastro ------\n\n");
        printf("1- Login\n");
        printf("2- Cadastrar novo usuário\n");
        printf("3- Sair do sistema\n\n");
        printf("-> Escolha uma opção: ");
        scanf("%d", &op);
        limparBuffer();

        limparTela();

        switch (op) {
            case 1:
                login();
                break;
            case 2:
                printf("Funcionalidade de cadastro ainda não implementada.\n");
                break;
            case 3:
                printf("Encerrando sistema...\n");
                exit(0);
            default:
                printf("Opção inválida!\n");
        }

        printf("Pressione Enter para continuar...");
        getchar();
        limparTela();
    }
}

int main() {
    setlocale(LC_ALL, "Portuguese");
    exibirTelaInicial();
    carregarClientesDoArquivo();
    menuInicial();
    return 0;
}