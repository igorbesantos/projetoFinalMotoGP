typedef struct {
	int idPiloto;
	int idCircuito;
	char data[11];
	char tempo[9]; 
} melhorVolta;


//Protótipos
void cadastraMelhorVolta();
void gravarMelhorVolta(melhorVolta *volta, int flagReceberFeedback);

//Implementações

void cadastraMelhorVolta(){
	int listaIdPilotos[101], qtdPilotosCadastrados=0, listaIdCircuitos[MAX_CIRCUITOS]; 
	int qtdCircuitosCadastrados=0, dia=0, mes=0, ano=0, valido=0, min=0, seg=0, milis=0;
	char listaNomesCircuitos[1][TAM_NOME], buffer[20];
	melhorVolta nova;
	
	qtdPilotosCadastrados = getListaIdsPilotos(listaIdPilotos);
	
	qtdCircuitosCadastrados = getListaCircuitos(1, listaIdCircuitos, 1, listaNomesCircuitos);
	
	fflush(stdin);
	
	do{
		nova.idPiloto = leValidaInteiro(0, 101, "Informe o codigo do piloto:");
		system("cls");
		if(!isIntNaLista(nova.idPiloto, listaIdPilotos, qtdPilotosCadastrados)){
			printf("Nenhum piloto cadastrado com o codigo informado!\n");
		}
	}while(!isIntNaLista(nova.idPiloto, listaIdPilotos, qtdPilotosCadastrados));
	
	do{
		printf("Informe o codigo do circuito:\n");
		scanf("%d", nova.idCircuito);
		system("cls");
		if(!isIntNaLista(nova.idCircuito, listaIdCircuitos, qtdCircuitosCadastrados)){
			printf("Nenhum circuito cadastrado com o codigo informado!\n");
		}
	}while(!isIntNaLista(nova.idCircuito, listaIdCircuitos, qtdCircuitosCadastrados));
	
	do{
		leData(buffer, 2017, 2100);
		interpretaDataFormatada(&dia, &mes, &ano, buffer);
		if(getDiaSemana(dia,mes,ano) == 6){
			if(ano > 2017){
				valido=1;
			}else if(ano==2017){
				if(mes>6){
					valido=1;
				}else if(mes==6){
					if(dia>=4){
						valido=1;
					}
				}
			}
		}
		system("cls");
	}while(!valido);
	strcpy(nova.data, buffer);
	
	min = leValidaInteiro(1,59, "Informe os minutos do melhor tempo do piloto:\n*Volta minima 1 min.");
	
	seg = leValidaInteiro(0,59, "Informe os segundos do melhor tempo do piloto:");
	
	milis - leValidaInteiro(0,59, "Informe os milissegundos do melhor tempo do piloto:");
	
	sprintf(nova.tempo, "%2d:%2d:%2d", min, seg, milis);
	
	gravarMelhorVolta(&nova, 1);
	fflush(stdin);
}

void gravarMelhorVolta(melhorVolta *volta, int flagReceberFeedback){
	FILE* arquivo;
	
	if(arquivo = fopen("database/voltas.txt", "a")){
		fprintf(arquivo, "%3d %3d %10s %8s\n", volta[0].idPiloto, volta[0].idCircuito, volta[0].data, volta[0].tempo);
		fclose(arquivo);
		if(flagReceberFeedback){
			printf("Melhor volta cadastrada com sucesso!\n");
			system("pause");
			system("cls");
		}
	}else if(flagReceberFeedback){
		printf("Nao foi possivel gravar a melhor volta!\n");
		system("pause");
		system("cls");
	}
}

