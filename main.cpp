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

// Limpa buffer do stdin
void limparBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Valida se CPF tem exatamente 11 dígitos numéricos
int validarCPF(const char *cpf) {
    if (strlen(cpf) != 11) return 0;

    for (int i = 0; i < 11; i++) {
        if (cpf[i] < '0' || cpf[i] > '9') {
            return 0;
        }
    }
    return 1;
}

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
                clientes[i].idade);
    }

    fclose(arquivo);
}

// Carrega os clientes do arquivo
void carregarClientesDoArquivo() {
    FILE *arquivo = fopen("clientes.txt", "r");
    if (arquivo == NULL) {
        // Arquivo não existe ainda, nada a carregar
        return;
    }

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

// Função para cadastrar cliente
void cadastrarCliente() {
    if (totalClientes >= MAX_CLIENTES) {
        printf("Limite de clientes atingido!\n");
        return;
    }

    printf("---- Cadastro de Cliente ----\n");

// Nome
printf("Nome: ");
fgets(clientes[totalClientes].nome, sizeof(clientes[totalClientes].nome), stdin);
clientes[totalClientes].nome[strcspn(clientes[totalClientes].nome, "\n")] = '\0';

// CPF
do {
    printf("CPF (apenas numeros, 11 digitos): ");
    if (fgets(clientes[totalClientes].cpf, sizeof(clientes[totalClientes].cpf), stdin) == NULL) {
        printf("Erro na leitura do CPF. Tente novamente.\n");
        continue;
    }
    clientes[totalClientes].cpf[strcspn(clientes[totalClientes].cpf, "\n")] = '\0';

    if (!validarCPF(clientes[totalClientes].cpf)) {
        printf("CPF inválido! Tente novamente.\n");
    } else {
        break;
    }
} while (1);

// Pergunta Email separadamente
fflush(stdin);
printf("Email (digite seu email): ");
fgets(clientes[totalClientes].email, sizeof(clientes[totalClientes].email), stdin);
clientes[totalClientes].email[strcspn(clientes[totalClientes].email, "\n")] = '\0';

// Pergunta Idade separadamente
printf("Idade (digite sua idade): ");
while (scanf("%d", &clientes[totalClientes].idade) != 1 || clientes[totalClientes].idade <= 0) {
    printf("Entrada inválida para idade. Digite um número válido: ");
    limparBuffer();
}
limparBuffer();  // Limpa o '\n' que fica no buffer após o scanf

limparBuffer();  // Limpa o '\n' remanescente após o scanf

    limparBuffer(); // limpa '\n' após o scanf

    totalClientes++;

    salvarClientesEmArquivo(); // salva os dados após cadastro

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

// Outros menus e funções permanecem os mesmos, com chamadas para funções de cadastro, listagem, etc.

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
        limparBuffer();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        switch (op) {
        case 1:
            // cadastrarVenda();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 2:
            cadastrarCliente();
            break;
        case 3:
            // cadastrarProduto();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 4:
            // cadastrarFuncionario();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 5:
            // cadastrarCategoria();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 6:
            // cadastrarSubcategoria();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 7:
            printf("Voltando para o menu painel!\n\n");
            return;
        default:
            printf("Escolha uma opcao valida!\n\n");
        }

#ifdef _WIN32
        system("pause");
        system("cls");
#else
        printf("Pressione Enter para continuar...");
        getchar();
        system("clear");
#endif
    }
}

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
        limparBuffer();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        switch (op) {
        case 1:
            // listarProdutos();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 2:
            listarClientes();
            break;
        case 3:
            // listarFuncionario();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 4:
            // listarVendas();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 5:
            // listarCategorias();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 6:
            printf("Voltando para o menu painel!\n\n");
            return;
        default:
            printf("Escolha uma opcao valida!\n\n");
        }

#ifdef _WIN32
        system("pause");
        system("cls");
#else
        printf("Pressione Enter para continuar...");
        getchar();
        system("clear");
#endif
    }
}

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
        limparBuffer();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        switch (op) {
        case 1:
            // editarVenda();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 2:
            // removerVenda();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 3:
            printf("Voltando para o menu painel!\n\n");
            return;
        default:
            printf("Escolha uma opcao valida!\n\n");
        }

#ifdef _WIN32
        system("pause");
        system("cls");
#else
        printf("Pressione Enter para continuar...");
        getchar();
        system("clear");
#endif
    }
}

void exibirRelatorio() {
    // para desenvolver
    printf("Funcionalidade não implementada ainda.\n");
}

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
        limparBuffer();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

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
            exibirRelatorio();
            break;
        case 5:
            printf("Voltando para o menu!\n\n");
            return 2;
        default:
            printf("Escolha uma opção valida!\n\n");
        }

#ifdef _WIN32
        system("pause");
        system("cls");
#else
        printf("Pressione Enter para continuar...");
        getchar();
        system("clear");
#endif
    }
}

void login() {
    printf("Login acessado! Redirecionando para o Menu Painel.\n\n");

#ifdef _WIN32
    system("pause");
    system("cls");
#else
    printf("Pressione Enter para continuar...");
    getchar();
    system("clear");
#endif

    menuPainel();
}

void menuInicial() {
    int op;

    while (1) {
        printf("------ Menu login/cadastro ------\n\n");
        printf("1- Login\n");
        printf("2- Cadastrar novo usuario\n");
        printf("3- Sair do sistema\n\n");
        printf("-> Escolha uma opcao: ");
        scanf("%d", &op);
        limparBuffer();

#ifdef _WIN32
        system("cls");
#else
        system("clear");
#endif

        switch (op) {
        case 1:
            login();
            break;
        case 2:
            // cadastrar();
            printf("Funcionalidade não implementada ainda.\n");
            break;
        case 3:
            printf("Encerrando sistema...\n\n");
            exit(0);
        default:
            printf("Opcao invalida!!\n\n");
        }

#ifdef _WIN32
        system("pause");
        system("cls");
#else
        printf("Pressione Enter para continuar...");
        getchar();
        system("clear");
#endif
    }
}

int main() {
    setlocale(LC_ALL, "portuguese");

    carregarClientesDoArquivo();
    menuInicial();

    return 0;
}