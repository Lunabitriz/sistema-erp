void formaPagamento(int op, int vendaIndex) {
	int op2;
	
	system("cls");
	
	printf("1- Cart�o.\n");
	printf("2- Boleto.\n");
	printf("3- Pix.\n");
	printf("4- Dinheiro.\n\n");
	printf("Informe a forma de pagamento: ");
	scanf("%d", &op);
	
	switch(op) {
		case 1:
			strcpy(venda[vendaIndex].formaPagamento, "Cart�o");
			strcpy(venda[vendaIndex].tipoOperacao, "Cart�o");
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
			printf("\nErro! Escolha uma op��o v�lida!\n\n");
	}
}

void cadastrarVenda() {
	
    char op2;
    do {
        if (qtdVendas >= MAX_VENDAS) {
            printf("Limite de cadastro de vendas atingido!!!\n\n");
            return;
        }

        fflush(stdin);
        printf("Informe a categoria do produto: ");
        fgets(venda[qtdVendas].categoriaProduto, 30, stdin);
        venda[qtdVendas].categoriaProduto[strcspn(venda[qtdVendas].categoriaProduto, "\n")] = '\0';

        printf("Informe a quantidade do produto: ");
        scanf("%d", &venda[qtdVendas].quantidade);

        printf("Informe o pre�o p/unidade do produto: ");
        scanf("%f", &venda[qtdVendas].precoUnidade);

        formaPagamento(0, qtdVendas);
        
        qtdVendas++;

        fflush(stdin);
        printf("Deseja cadastrar mais alguma venda? (S/N)\n");
        scanf("%c", &op2);

        system("cls");
    } while (op2 == 'S' || op2 == 's');
}