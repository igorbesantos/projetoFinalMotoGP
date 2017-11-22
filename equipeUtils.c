typedef struct {
	char nome[TAM_NOME];
	char sigla[4];
	char pais[TAM_NOME];
} equipe;


//Protótipos

int getListaSiglasEquipe(char lista[][4]);
int isSiglaEquipeCadastrada(char *sigla);
void leValidaSiglaEquipe(char *destino);
void cadastrarEquipe();
void salvarEquipe(equipe *nova);
int getListaEquipes(int flagRetornarSiglas, char listaSiglas[][4], int flagRetornarNomes, char listaNomes[][TAM_NOME]);
int leEquipe(int flagRetornaSigla, char *sigla, int flagRetornaNome, char *nome, char *mensagem);

//Implementações

int getListaSiglasEquipe(char lista[][4]){
	int qtdRegistros=0, i=0;
	char buffer[300], temp[4];
	FILE* arquivo;
	
	qtdRegistros = qtdRegistrosArquivo("database/equipes.txt");
	if(qtdRegistros>0){
		arquivo = fopen("database/equipes.txt", "r");
		for(i=0; i<qtdRegistros; i++){
			fgets(buffer, 290, arquivo);
			lista[i][0] = buffer[51];
			lista[i][1] = buffer[52];
			lista[i][2] = buffer[53];
			lista[i][3]='\0';
		}
		fclose(arquivo);
	}
	return qtdRegistros;
}

int isSiglaEquipeCadastrada(char *sigla){
	char listaSiglasEquipesCadastradas[MAX_EQUIPES][4];
	int i=0, qtdRegistros=0;
	
	qtdRegistros = getListaSiglasEquipe(listaSiglasEquipesCadastradas);
	for(i=0; i<qtdRegistros; i++){
		if(		toupper(listaSiglasEquipesCadastradas[i][0])==toupper(sigla[0]) && 
				toupper(listaSiglasEquipesCadastradas[i][1])==toupper(sigla[1]) && 
				toupper(listaSiglasEquipesCadastradas[i][2])==toupper(sigla[2]))
			{
			sigla[0]=listaSiglasEquipesCadastradas[i][0];
			sigla[1]=listaSiglasEquipesCadastradas[i][1];
			sigla[2]=listaSiglasEquipesCadastradas[i][2];
			return 1;
		}
	}
	return 0;
}

void leValidaSiglaEquipe(char *destino){
	char buffer[30];
	do{
		fflush(stdin);
		leValidaNome("Informe a sigla da equipe:\n", buffer);
		system("cls");
		if(strlen(buffer)!=3){
			printf("Sigla de equipe deve conter 3 caracteres!\n");
		}
		if(buffer[1]==' '){
			printf("Sigla não pode conter espacos em branco!\n");
		}
	}while(strlen(buffer)!=3 || buffer[1]==' ' || isSiglaEquipeCadastrada(buffer));
	strcpy(destino, buffer);
}

void cadastrarEquipe(){
	equipe nova;
	leValidaNome("Informe o nome da equipe:\n", nova.nome);
	leValidaSiglaEquipe(nova.sigla);
	lePais(0, " ", 1, nova.pais, "Informe a sigla do pais da equipe:\n");
	salvarEquipe(&nova);
}

void salvarEquipe(equipe *nova){
	FILE* arquivo;
	
	fflush(stdin);
	if(arquivo = fopen("database/equipes.txt", "a")){
		fprintf(arquivo, "%-50s %-3s %-50s\n", nova[0].nome, nova[0].sigla, nova[0].pais);
		fclose(arquivo);
		
		printf("Equipe cadastrada com sucesso!\nNome: %s\nSigla: %s\nPais: %s\n", nova[0].nome, nova[0].sigla, nova[0].pais);
	}else{
		printf("Nao foi possivel cadastrar a equipe!\n");
	}
	system("pause");
	system("cls");
}

int getListaEquipes(int flagRetornarSiglas, char listaSiglas[][4], int flagRetornarNomes, char listaNomes[][TAM_NOME]){
	FILE* arquivo;
	int qtdRegistros=0, i=0, j=0;
	char buffer[200];
	
	qtdRegistros = qtdRegistrosArquivo("database/equipes.txt");
	if(qtdRegistros>0){
		if(arquivo=fopen("database/equipes.txt", "r")){
			for(i=0; i<qtdRegistros; i++){
				fgets(buffer, 190, arquivo);
				if(flagRetornarSiglas){
					listaSiglas[i][0] = buffer[51];
					listaSiglas[i][1] = buffer[52];
					listaSiglas[i][2] = buffer[53];
					listaSiglas[i][3] = '\0';
				}
				if(flagRetornarNomes){
					for(j=0; j<(TAM_NOME-1); j++){
						listaNomes[i][j] = buffer[j];
					}
					listaNomes[i][TAM_NOME-1] = '\0';
				}
			}
			fclose(arquivo);
		}
	}
	return qtdRegistros;
}

int leEquipe(int flagRetornaSigla, char *sigla, int flagRetornaNome, char *nome, char *mensagem){
	int qtdRegistros = 0, i=0, siglaValida=0, resultado=0;
	char listaSiglas[MAX_EQUIPES][4], listaNomes[MAX_EQUIPES][TAM_NOME], siglaSelecionada[10], opcao;
	
	qtdRegistros = getListaEquipes(1, listaSiglas, 1, listaNomes);
	if(qtdRegistros>0){
		do{
			opcao = leValidaOpcao('1', '2', "Selecao de Equipes:\n1-Consultar lista de equipes\n2-Selecionar equipe por sigla");
			switch(opcao){
			case '1':
				printf("Sigla - Nome\n");
				for(i=0; i<qtdRegistros; i++){
					printf("%s   - %s\n",listaSiglas[i], listaNomes[i]);
				}
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
								siglaValida = 1;
								resultado = 1;
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
	}else{
		printf("Nenhuma equipe foi cadastrada ate o momento!");
		system("pause");
		system("cls");
	}
	return resultado;
}



