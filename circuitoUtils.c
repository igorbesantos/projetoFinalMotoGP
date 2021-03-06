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
void alterarCircuito();
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
	
	novo.menorTempo.minutos=0;
	novo.menorTempo.segundos=0;
	novo.menorTempo.milisegundos=0;
	novo.idPilotoMenorTempo=999;
	
	gravarCircuito(&novo, 1);
}

void alterarCircuito() {
	int qtdCircuitos=0, i=0, isIdCircuitoCadastrado=0, idCircuito=0;
	char opcao, msgConfirmacao[250];
	circuito listaCircuitos[MAX_CIRCUITOS];
	
	qtdCircuitos = buscaCircuitos(listaCircuitos);
	
	do{
		opcao = leValidaOpcao('0','2', "Escolha uma opcao:\n1-Ver lista de circuitos cadastrados\n2-Alterar circuito por codigo\n\n0-Voltar");
		switch(opcao){
		case '1':
			for(i=0; i<qtdCircuitos; i++){
				printf("%03d - %s\n", listaCircuitos[i].id, listaCircuitos[i].nome);
			}
			system("pause");
			system("cls");
			break;
		case '2':
			isIdCircuitoCadastrado=0;
			idCircuito = leValidaInteiro(0,999, "Informe o codigo do circuito a ser alterado: ");
			for(i=0; i<qtdCircuitos; i++){
				if(idCircuito == listaCircuitos[i].id){
					isIdCircuitoCadastrado = 1;
				}
			}
			if(isIdCircuitoCadastrado){
				if(remove("database/circuito.txt")){
					for(i=0; i<qtdCircuitos; i++){
						if(idCircuito != listaCircuitos[i].id){
							gravarCircuito(&listaCircuitos[i],0);
						}else{
							sprintf(msgConfirmacao,"Deseja alterar o circuito %s ?\n1-Sim\n2-Nao", listaCircuitos[i].nome);
							opcao = leValidaOpcao('1', '2', msgConfirmacao);
							switch(opcao){
							case '1':
								leValidaNome("Informe o novo nome do circuito:\n", listaCircuitos[i].nome);
								
								lePais(0, " ", 1, listaCircuitos[i].pais, "Informe a sigla do novo pais do circuito:\n");
								
								do{
									printf("Informe o novo tamanho (em Km) do circuito:\n");
									scanf("%f", &listaCircuitos[i].tamanho);
									system("cls");
								}while(listaCircuitos[i].tamanho<=0.0);
								
								printf("Circuito %s alterado com sucesso!\n", listaCircuitos[i].nome);
								system("pause");
								system("cls");
								break;
							case 2:
								printf("Alteracao cancelada!\n");
								system("pause");
								system("cls");
								break;
							}
							gravarCircuito(&listaCircuitos[i],0);
							opcao = '0';
						}
					}
				}else{
					printf("Nao foi possivel acessar o arquivo de circuitos!");
					system("pause");
					system("cls");
				}
			}else{
				printf("N�o foi encontrado nenhum circuito com esse codigo!\n");
				system("pause");
				system("cls");
			}
			break;
		}
	}while(opcao!='0');
}

void gravarCircuito(circuito *novo, int flagReceberFeedback){
	FILE* arquivo;
	
	if(arquivo = fopen("database/circuitos.txt", "a")){
		fprintf(arquivo, "%03d %-50s %-50s %08.2f %02d %02d %02d %03d\n",
							novo[0].id,
							novo[0].nome,
							novo[0].pais,
							novo[0].tamanho,
							novo[0].menorTempo.minutos,
							novo[0].menorTempo.segundos,
							novo[0].menorTempo.milisegundos,
							novo[0].idPilotoMenorTempo);
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
			for(j=0; j<=127; j++){
				buffer = fgetc(arquivo);
				if(j<3){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 0:
						listaCircuitos[i].id += aux*100;
						break;
					case 1:
						listaCircuitos[i].id += aux*10;
						break;
					case 2:
						listaCircuitos[i].id += aux;
						break;
					}
				}else if(j==3){
					aux=0;
				}else if(j<54){
					if(aux<3){
						if(aux==2 || j==53){
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
				}else if(j<105){
					if(aux<3){
						if(aux==2 || j==104){
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
				}else if(j==105){
					listaCircuitos[i].pais[k] = '\0';
					aux=0;
					k=0;
				}else if(j<114){
					converteCharParaFloat(&faux, buffer);
					switch(j){
					case 106:
						listaCircuitos[i].tamanho += faux*1000.0;
						break;
					case 107:
						listaCircuitos[i].tamanho += faux*100.0;
						break;
					case 109:
						listaCircuitos[i].tamanho += faux*10.0;
						break;
					case 110:
						listaCircuitos[i].tamanho += faux;
						break;
					case 112:
						listaCircuitos[i].tamanho += faux/10.0;
						break;
					case 113:
						listaCircuitos[i].tamanho += faux/100.0;
						break;
					}
				}else if(j==114){
					faux=0.0;
					if(buffer!='\n'){
						isMelhorTempoCadastrado = 1;
					}
				}else if(isMelhorTempoCadastrado){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 115:
						listaCircuitos[i].menorTempo.minutos += aux*10;
						break;
					case 116:
						listaCircuitos[i].menorTempo.minutos += aux;
						break;
					case 118:
						listaCircuitos[i].menorTempo.segundos += aux*10;
						break;
					case 119:
						listaCircuitos[i].menorTempo.segundos += aux;
						break;
					case 121:
						listaCircuitos[i].menorTempo.milisegundos += aux*10;
						break;
					case 122:
						listaCircuitos[i].menorTempo.milisegundos += aux;
						break;
					case 124:
						listaCircuitos[i].idPilotoMenorTempo=0;
						listaCircuitos[i].idPilotoMenorTempo += aux*100;
						break;
					case 125:
						listaCircuitos[i].idPilotoMenorTempo += aux*10;
						break;
					case 126:
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

