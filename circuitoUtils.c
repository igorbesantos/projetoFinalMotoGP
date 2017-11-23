typedef struct {
	int id;
	char nome[TAM_NOME];
	char pais[TAM_NOME];
	float tamanho;
	tempo menorTempo;
	int idPilotoMenorTempo;
} circuito;

//Prot�tipos
void cadastrarCircuito();
int getListaCircuitos(int flagRetornarCod, int listaCod[], int flagRetornarNomes, char listaNomes[][TAM_NOME]);
void gravarCircuito(circuito *novo, int flagReceberFeedback);
int buscaCircuitos(circuito listaCircuitos[]);

//Implementa��es
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

int buscaCircuitos(circuito listaCircuitos[]){
	FILE* arquivo;
	int qtdRegistros=0, i=0, j=0, k=0, aux=0;
	float faux = 0.0;
	char buffer;
	int isMelhorTempoCadastrado = 0;
	
	qtdRegistros = qtdRegistrosArquivo("database/circuitos.txt");
	
	if(arquivo = fopen("database/circuitos.txt", "rt")){
		for(i=0; i<qtdRegistros; i++){
			aux=0;
			k=0;
			listaCircuitos[i].id=0;
			listaCircuitos[i].tamanho = 0.0;
			listaCircuitos[i].menorTempo.minutos = 0;
			listaCircuitos[i].menorTempo.segundos = 0;
			listaCircuitos[i].menorTempo.milisegundos = 0;
			listaCircuitos[i].idPilotoMenorTempo = -1;
			for(j=0; j<=MAX_CIRCUITOS; j++){
				buffer = fgetc(arquivo);
				if(j<3){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 0:
						listaCircuitos[j].id += aux*100;
						break;
					case 1:
						listaCircuitos[j].id += aux*10;
						break;
					case 2:
						listaCircuitos[j].id += aux;
						break;
					}
				}else if(j==3){
					aux=0;
				}else if(j<54){
					if(aux<3){
						if(aux==2 || j==49){
							listaCircuitos[i].nome[k] = '\0';
							aux=3;
						}else{
							if(buffer==' '){
								aux++;
							}else{
								aux=0;
							}
							listaCircuitos[i].nome[k] = buffer;
							k++;
						}
					}
				}else if(j==54){
					listaCircuitos[i].nome[k] = '\0';
					aux=0;
					k=0;
				}else if(j<55){
					if(aux<3){
						if(aux==2 || j==49){
							listaCircuitos[i].pais[k] = '\0';
							aux=3;
						}else{
							if(buffer==' '){
								aux++;
							}else{
								aux=0;
							}
							listaCircuitos[i].pais[k] = buffer;
							k++;
						}
					}
				}else if(j==55){
					listaCircuitos[i].pais[k] = '\0';
					aux=0;
					k=0;
				}else if(j<64){
					converteCharParaFloat(&faux, buffer);
					switch(j){
					case 57:
						listaCircuitos[i].tamanho += faux*1000.0;
						break;
					case 58:
						listaCircuitos[i].tamanho += faux*100.0;
						break;
					case 59:
						listaCircuitos[i].tamanho += faux*10.0;
						break;
					case 60:
						listaCircuitos[i].tamanho += faux;
						break;
					case 62:
						listaCircuitos[i].tamanho += faux/10.0;
						break;
					case 63:
						listaCircuitos[i].tamanho += faux/100.0;
						break;
					}
				}else if(j==64){
					faux=0.0;
					if(buffer!='\n'){
						isMelhorTempoCadastrado = 1;
					}
				}else if(isMelhorTempoCadastrado){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 65:
						listaCircuitos[i].menorTempo.minutos += aux*10;
						break;
					case 66:
						listaCircuitos[i].menorTempo.minutos += aux;
						break;
					case 68:
						listaCircuitos[i].menorTempo.segundos += aux*10;
						break;
					case 69:
						listaCircuitos[i].menorTempo.segundos += aux;
						break;
					case 71:
						listaCircuitos[i].menorTempo.milisegundos += aux*10;
						break;
					case 72:
						listaCircuitos[i].menorTempo.milisegundos += aux;
						break;
					case 74:
						listaCircuitos[i].idPilotoMenorTempo=0;
						listaCircuitos[i].idPilotoMenorTempo += aux*100;
						break;
					case 75:
						listaCircuitos[i].idPilotoMenorTempo += aux*10;
						break;
					case 76:
						listaCircuitos[i].idPilotoMenorTempo += aux;
						break;
					}
				}
			}
		}
		fclose(arquivo);
	}
	return qtdRegistros;
}

