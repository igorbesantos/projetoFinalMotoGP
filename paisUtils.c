//Protótipos

int getListaPaises(int flagRetornarSiglas, char listaSiglas[][4], int flagRetornarNomes, char listaNomes[][60]);
void lePais (int flagRetornaSigla, char *sigla, int flagRetornaNome, char *nome, char *mensagem);
void exibicaoPaises();


//Implementações

void exibicaoPaises(){
	int qtdRegistros = 0, i=0;
	char listaSiglas[250][4], listaNomes[250][60], opcao, aux, atual;
	char instrucoes[300] = "Instrucoes:\n\nUse as teclas < e > para navegas entre as letras e encontrar os paises.\n\nOu pressione a LETRA para pular direto para a mesma.\n\nPressione 0 para sair a qualquer momento.\n\nOBS: A organizacao e feita pela inicial do pais e nao da sigla.\n\n";
	qtdRegistros = getListaPaises(1, listaSiglas, 1, listaNomes);
	printf("%s", instrucoes);
	system("pause");
	system("cls");
	atual = opcao = 'a';
	fflush(stdin);
	do{	
		if(opcao=='.' || opcao=='>'){
			if(atual!='z'){
				atual++;
			}
		}else if(opcao==',' || opcao=='<'){
			if(atual!='a'){
				atual--;
			}
		}else{
			atual = opcao;
		}
		for(aux='a'; aux<='z'; aux++){
			if(aux==atual){
				printf("|%c|",toupper(aux));
			}else{
				printf(" %c ",aux);
			}
		}
		
		printf("\n\n");
		
		for(i=0; i<qtdRegistros; i++){
			if(toupper(listaNomes[i][0]) == toupper(atual)){
				printf(" %s  ( %s )\n", listaNomes[i], listaSiglas[i]);
			}
		}
		do{
			opcao = getch();
			opcao = tolower(opcao);
		}while(!((opcao>='a' && opcao<='z') || opcao==',' || opcao=='.' || opcao=='<' || opcao=='>' || opcao=='0'));
		system("cls");
	}while(opcao != '0');
}

void lePais (int flagRetornaSigla, char *sigla, int flagRetornaNome, char *nome, char *mensagem){ 
	int qtdRegistros = 0, i=0, siglaValida=0;
	char listaSiglas[250][4], listaNomes[250][60], siglaSelecionada[10], opcao;
	
	qtdRegistros = getListaPaises(1, listaSiglas, 1, listaNomes);
	do{
		opcao = leValidaOpcao('1', '2', "Selecao de pais:\n1-Consultar lista de paises\n2-Selecionar pais por sigla");
		switch(opcao){
		case '1':
			exibicaoPaises();
			break;
		case '2':
			do{
				printf("%s\n",mensagem);
				fflush(stdin);
				gets(siglaSelecionada);
				fflush(stdin);
				system("cls");
				if(strlen(siglaSelecionada)==3){
					for(i=0; i<qtdRegistros; i++){
						if(		toupper(siglaSelecionada[0])==toupper(listaSiglas[i][0]) && 
								toupper(siglaSelecionada[1])==toupper(listaSiglas[i][1]) &&
								toupper(siglaSelecionada[2])==toupper(listaSiglas[i][2])){
							siglaValida=1;
							if(flagRetornaSigla){
								strcpy(sigla, listaSiglas[i]);
							}
							if(flagRetornaNome){
								strcpy(nome, listaNomes[i]);
							}
							break;
						}
					}
				}else{
					printf("Sigla deve conter apenas 3 caracteres!\n");
					system("pause");
					system("cls");
				}
			}while(!siglaValida);
			break;
		}
	}while(!siglaValida);
}

int getListaPaises(int flagRetornarSiglas, char listaSiglas[][4], int flagRetornarNomes, char listaNomes[][60]){
	int qtdRegistros=0, i=0, j=0;
	char buffer[100], temp[4];
	FILE* arquivo;
	printf("Carregando, aguarde...\n");
	qtdRegistros = qtdRegistrosArquivo("database/paises.txt");
	if(qtdRegistros>0){
		arquivo = fopen("database/paises.txt", "r");
		for(i=0; i<qtdRegistros; i++){
			fgets(buffer, 100, arquivo);
			if(flagRetornarSiglas){
				listaSiglas[i][0] = buffer[0];
				listaSiglas[i][1] = buffer[1];
				listaSiglas[i][2] = buffer[2];
				listaSiglas[i][3]='\0';	
			}
			if(flagRetornarNomes){
				j=0;
				while(buffer[j+4] != '\n' && buffer[j+4] != '\0'){
					listaNomes[i][j]=buffer[j+4];
					j++;
				}
			}
		}
		fclose(arquivo);
	}
	system("cls");
	return qtdRegistros;
}
