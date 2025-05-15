#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>

struct Usuarios {
	char nome[50]; 
	char genero[50]; 
	char email[50]; 
	char senha[50]; 
	int idade;
};

struct Empresa {
	char nomeEmpresa[50]; 
	int porteEmpresa; //poupa o cliente de ter que digitar muito!
	int tempoAtuacao;
	float rendaMensal;
	float metaLucro;
};

void menuInicial() {
	int op;
	
	while(1) {
		printf("1- Login\n");
		printf("2- Cadastrar novo usuário\n");
		printf("3- Sair do sistema\n\n");
		printf("Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//login();
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
}

void menuPainel() {
	int op;
	
	while(1) {
		printf("1- Cadastrar nova venda\n");
		printf("2- Cadastrar nova categoria de produtos\n");
		printf("3- Listar vendas\n");
		printf("4- Listar categorias\n");
		printf("5- Editar venda\n");
		printf("6- Remover venda\n");
		printf("7- Acessar métricas\n");
		printf("8- Voltar ao menu\n\n");		
		printf("Escolha uma opção: ");
		scanf("%d", &op);
		
		system("cls");
		
		switch(op) {
			case 1:
				//cadastrarVenda();
				break;
			case 2:
				//cadastrarCategoria();
				break;				
			case 3:
				//listarVendas();
				break;				
			case 4:
				//listarCategorias();
				break;				
			case 5:
				//editarVenda();
				break;				
			case 6:
				//removerVenda();
				break;				
			case 7:
				//acessarRelatorio();
				break;				
			case 8:
				//return;
				break;				
			default:
				printf("Opção inválida!!\n\n");
		}
		
		system("pause");
		system("cls");
	}
}

int main() {
	setlocale(LC_ALL, "portuguese");
	
	menuInicial();
	menuPainel();
}