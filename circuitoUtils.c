typedef struct {
	int id;
	char nome[TAM_NOME];
	char pais[TAM_NOME];
	float tamanho;
	tempo menorTempo;
	int idPilotoMenorTempo;
} circuito;

//Protótipos
void cadastrarCircuito();
int getListaCircuitos(int flagRetornarCod, int listaCod[], int flagRetornarNomes, char listaNomes[][TAM_NOME]);
void gravarCircuito(circuito *novo, int flagReceberFeedback);

//Implementações
void cadastrarCircuito(){
	int listaCod[MAX_CIRCUITOS], qtdRegistros=0;
	char placeholder[1][50];
	circuito novo;
	fflush(stdin);
	qtdRegistros = getListaCircuitos(1, listaCod, 0, placeholder);
	if(qtdRegistros<MAX_CIRCUITOS){
		do{
			novo.id = leValidaInteiro(0, 999, "Informe o codigo unico do circuito: ");
			if(isIntNaLista(novo.id, listaCod, qtdRegistros)){
				printf("Codigo ja cadastrado para outro circuito!\n");
			}
		}while(isIntNaLista(novo.id, listaCod, qtdRegistros));
		
		fflush(stdin);
		
		leValidaNome("Informe o nome do circuito:\n", novo.nome);
		
		lePais(0, " ", 1, novo.pais, "Informe a sigla do pais do circuito:\n");
		
		do{
			printf("Informe o tamanho (em Km) do circuito:\n");
			scanf("%f", &novo.tamanho);
			system("cls");
		}while(novo.tamanho<=0.0);
	}else{
		printf("Quantidade maxima de circuitos ja cadastrada!\n");
		system("pause");
		system("cls");
	}
	
	gravarCircuito(&novo, 1);
}

void gravarCircuito(circuito *novo, int flagReceberFeedback){
	FILE* arquivo;
	
	if(arquivo = fopen("database/circuitos.txt", "a")){
		fprintf(arquivo, "%03d %-50s %-50s %08.2f\n",
							novo[0].id,
							novo[0].nome,
							novo[0].pais,
							novo[0].tamanho);
		fclose(arquivo);
		if(flagReceberFeedback){
			printf("Circuito %s cadastrado com sucesso!\n", novo[0].nome);
			system("pause");
			system("cls");
		}
	}else if(flagReceberFeedback){
		printf("Nao foi possivel gravar o circuito!\n");
		system("pause");
		system("cls");
	}
}

int getListaCircuitos(int flagRetornarCod, int listaCod[], int flagRetornarNomes, char listaNomes[][TAM_NOME]){
	int qtdRegistros=0, i=0, j=0, intBuffer=0;
	char buffer[200];
	FILE* arquivo;
	printf("Carregando, aguarde...\n");
	fflush(stdin);
	qtdRegistros = qtdRegistrosArquivo("database/circuitos.txt");
	
	if(qtdRegistros>0){
		if(arquivo = fopen("database/circuitos.txt", "r")){
			for(i=0; i<qtdRegistros; i++){
				if(flagRetornarCod){
					fscanf(arquivo, "%d", &listaCod[i]);
				}else{
					fscanf(arquivo, "%d", &intBuffer);
				}
				fgetc(arquivo);
				if(flagRetornarNomes){
					j=0;
					while(j<TAM_NOME && buffer[j]!='\n'){
						listaNomes[i][j] = buffer[j];
						j++;
					}
					listaNomes[i][j]='\0';
				}
				fgets(buffer, 199, arquivo);
			}
			fclose(arquivo);
		}
	}
	system("cls");
	return qtdRegistros;
}
