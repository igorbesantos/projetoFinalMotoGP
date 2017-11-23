typedef struct {
	int idPiloto;
	int idCircuito;
	char data[11];
	char tempo[9]; 
} melhorVolta;


//Protótipos
void cadastraMelhorVolta();
void gravarMelhorVolta(melhorVolta *volta, int flagReceberFeedback);
int buscaMelhoresVoltas(melhorVolta listaVoltas[]);
int qtdVoltasRealizadas(int idPiloto);
void verificaMelhorVoltaCircuito(int idCircuito, char tempoPiloto[], int idPiloto);
void excluirMelhorVolta();
void alterarMelhorVolta();

//Implementações

void cadastraMelhorVolta(){
	int listaIdPilotos[101], qtdPilotosCadastrados=0, listaIdCircuitos[MAX_CIRCUITOS]; 
	int qtdCircuitosCadastrados=0, dia=0, mes=0, ano=0, valido=0, min=0, seg=0, milis=0;
	char listaNomesCircuitos[MAX_CIRCUITOS][TAM_NOME], buffer[20];
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
		scanf("%d", &nova.idCircuito);
		system("cls");
		if(!isIntNaLista(nova.idCircuito, listaIdCircuitos, qtdCircuitosCadastrados)){
			printf("Nenhum circuito cadastrado com o codigo informado!\n");
		}
	}while(!isIntNaLista(nova.idCircuito, listaIdCircuitos, qtdCircuitosCadastrados));
	
	do{
		printf("A seguir, informe a data da corrida...\n");
		system("pause");
		system("cls");
		leData(buffer, 2017, 2100);
		fflush(stdin);
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
		}else{
			printf("Dia informado nao e domingo!\n");
		}
		if(!valido){
			printf("Data informada nao e valida! (Data minima: 04/06/2017)\n");
		}
		system("pause");
		system("cls");
	}while(!valido);
	
	strcpy(nova.data, buffer);
	
	min = leValidaInteiro(1,59, "Informe os minutos do melhor tempo do piloto (Min: 1 minuto):");
	
	seg = leValidaInteiro(0,59, "Informe os segundos do melhor tempo do piloto:");
	
	milis = leValidaInteiro(0,99, "Informe os milissegundos do melhor tempo do piloto:");
	
	sprintf(nova.tempo, "%02d:%02d:%02d", min, seg, milis);
	
	gravarMelhorVolta(&nova, 1);
	
	verificaMelhorVoltaCircuito(nova.idCircuito, nova.tempo, nova.idPiloto);
	
	fflush(stdin);
}

void gravarMelhorVolta(melhorVolta *volta, int flagReceberFeedback){
	FILE* arquivo;
	
	if(arquivo = fopen("database/voltas.txt", "a")){
		fprintf(arquivo, "%03d %03d %10s %8s\n", volta[0].idPiloto, volta[0].idCircuito, volta[0].data, volta[0].tempo);
		fclose(arquivo);
		if(flagReceberFeedback){
			printf("Melhor tempo cadastrado com sucesso!\n");
			system("pause");
			system("cls");
		}
	}else if(flagReceberFeedback){
		printf("Nao foi possivel gravar o melhor tempo!\n");
		system("pause");
		system("cls");
	}
}

int buscaMelhoresVoltas(melhorVolta listaVoltas[]){
	FILE* arquivo;
	int qtdRegistros=0, i=0, j=0, k=0, aux=0;
	char buffer;
	
	qtdRegistros = qtdRegistrosArquivo("database/voltas.txt");
	
	if(arquivo = fopen("database/voltas.txt", "rt")){
		for(i=0; i<qtdRegistros; i++){
			k=0;
			aux=0;
			listaVoltas[i].idPiloto = 0;
			listaVoltas[i].idCircuito = 0;
			for(j=0; j<=27; j++){
				buffer = fgetc(arquivo);
				if(j<3){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 0:
						listaVoltas[i].idPiloto += aux*100;
						break;
					case 1:
						listaVoltas[i].idPiloto += aux*10;
						break;
					case 2:
						listaVoltas[i].idPiloto += aux;
						aux = 0;
						break;
					}
				}else if(j<8){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 4:
						listaVoltas[i].idCircuito += aux*100;
						break;
					case 5:
						listaVoltas[i].idCircuito += aux*10;
						break;
					case 6:
						listaVoltas[i].idCircuito += aux;
						aux = 0;
						break;
					}
				}else if(j<18){
					listaVoltas[i].data[k] = buffer;
					k++;
				}else if(j==18){
					listaVoltas[i].data[k]= '\0';
					k=0;
				}else if(j<27){
					listaVoltas[i].tempo[k] = buffer;
					k++;
				}else if(j==27){
					listaVoltas[i].tempo[k] = '\0';
				}
			}
		}
		fclose(arquivo);
	}
	return qtdRegistros;
}

int qtdVoltasRealizadas(int idPiloto){
	int totalVoltas=0, voltasPiloto=0, i=0;
	melhorVolta listaVoltas[MAX_MELHORES_VOLTAS];
	
	totalVoltas = buscaMelhoresVoltas(listaVoltas);
	
	for(i=0; i<totalVoltas; i++){
		if(idPiloto == listaVoltas[i].idPiloto){
			voltasPiloto++;
		}
	}
	
	return voltasPiloto;
}

void verificaMelhorVoltaCircuito(int idCircuito, char tempoPiloto[], int idPiloto){
	tempo novo;
	circuito listaCircuitos[MAX_CIRCUITOS];
	int qtdCircuitos=0, i=0, j=0;
	
	recuperaTempoDeString(&novo.minutos, &novo.segundos, &novo.milisegundos, tempoPiloto);
	
	qtdCircuitos = buscaCircuitos(listaCircuitos);
	
	for(i=0; i<qtdCircuitos; i++){
		if(idCircuito == listaCircuitos[i].id){
			if(listaCircuitos[i].idPilotoMenorTempo<0 || (comparaTempo(novo, listaCircuitos[i].menorTempo) < 0)){
				listaCircuitos[i].menorTempo.minutos = novo.minutos;
				listaCircuitos[i].menorTempo.segundos = novo.segundos;
				listaCircuitos[i].menorTempo.milisegundos = novo.milisegundos;
				listaCircuitos[i].idPilotoMenorTempo = idPiloto;
				//TODO Gravar
				remove("database/circuitos.txt");
				for(j=0; j<qtdCircuitos; j++){
					gravarCircuito(&listaCircuitos[j], 0);
				}
				break;
			}
		}
	}
}

void alterarMelhorVolta(){
	char opcao, msgConfirmacao[250];
	melhorVolta listaVoltas[MAX_MELHORES_VOLTAS];
	piloto listaPilotos[101];
	circuito listaCircuitos[MAX_CIRCUITOS];
	int qtdVoltasCadastrados=0, qtdCircuitosCadastrados, qtdPilotos=0, flagIsCadastrado=0, idPiloto=0, codCircuito=0, i=0, min=0, seg=0, milis=0;
	FILE* arquivo;
	
	qtdVoltasCadastrados = buscaMelhoresVoltas(listaVoltas);
	qtdPilotos = buscaPilotos(listaPilotos);
	qtdCircuitosCadastrados = buscaCircuitos(listaCircuitos);
	fflush(stdin);
	do{
		idPiloto = leValidaInteiro(0,100, "Informe o codigo/numero do piloto para consultar as voltas: ");
		for(i=0; i<qtdPilotos; i++){
			if(idPiloto == listaPilotos[i].id){
				flagIsCadastrado = 1;
			}
		}
	}while(!flagIsCadastrado);
	fflush(stdin);
	flagIsCadastrado=0;
	do{
		codCircuito = leValidaInteiro(0,999, "Informe o codigo do circuito para consultar as voltas: ");
		for(i=0; i<qtdCircuitosCadastrados; i++){
			if(codCircuito == listaCircuitos[i].id){
				flagIsCadastrado = 1;
			}
		}
	}while(!flagIsCadastrado);
	remove("database/voltas.txt");
	
	for(i=0; i<qtdVoltasCadastrados; i++){
		if(listaVoltas[i].idCircuito==codCircuito && listaVoltas[i].idPiloto==idPiloto){
			sprintf(msgConfirmacao, "Deseja alterar a volta de %s em %s ?\n1-Sim\n2-Nao", listaVoltas[i].tempo, listaVoltas[i].data);
			opcao = leValidaOpcao('1', '2', msgConfirmacao);
			if(opcao=='2'){
				min = leValidaInteiro(1,59, "Informe os minutos do melhor tempo do piloto (Min: 1 minuto):");
				seg = leValidaInteiro(0,59, "Informe os segundos do melhor tempo do piloto:");
				milis = leValidaInteiro(0,99, "Informe os milissegundos do melhor tempo do piloto:");
				sprintf(listaVoltas[i].tempo, "%02d:%02d:%02d", min, seg, milis);
				
				gravarMelhorVolta(&listaVoltas[i], 0);
			}
		}else{
			gravarMelhorVolta(&listaVoltas[i], 0);
		}
	}	
}

void excluirMelhorVolta(){
	char opcao, msgConfirmacao[250];
	melhorVolta listaVoltas[MAX_MELHORES_VOLTAS];
	piloto listaPilotos[101];
	circuito listaCircuitos[MAX_CIRCUITOS];
	int qtdVoltasCadastrados=0, qtdCircuitosCadastrados, qtdPilotos=0, flagIsCadastrado=0, idPiloto=0, codCircuito=0, i=0;
	FILE* arquivo;
	
	qtdVoltasCadastrados = buscaMelhoresVoltas(listaVoltas);
	qtdPilotos = buscaPilotos(listaPilotos);
	qtdCircuitosCadastrados = buscaCircuitos(listaCircuitos);
	fflush(stdin);
	do{
		idPiloto = leValidaInteiro(0,100, "Informe o codigo/numero do piloto para consultar as voltas: ");
		for(i=0; i<qtdPilotos; i++){
			if(idPiloto == listaPilotos[i].id){
				flagIsCadastrado = 1;
			}
		}
	}while(!flagIsCadastrado);
	fflush(stdin);
	flagIsCadastrado=0;
	do{
		codCircuito = leValidaInteiro(0,999, "Informe o codigo do circuito para consultar as voltas: ");
		for(i=0; i<qtdCircuitosCadastrados; i++){
			if(codCircuito == listaCircuitos[i].id){
				flagIsCadastrado = 1;
			}
		}
	}while(!flagIsCadastrado);
	remove("database/voltas.txt");
	
	for(i=0; i<qtdVoltasCadastrados; i++){
		if(listaVoltas[i].idCircuito==codCircuito && listaVoltas[i].idPiloto==idPiloto){
			sprintf(msgConfirmacao, "Deseja excluir a volta de %s em %s ?\n1-Sim\n2-Nao", listaVoltas[i].tempo, listaVoltas[i].data);
			opcao = leValidaOpcao('1', '2', msgConfirmacao);
			if(opcao=='2'){
				gravarMelhorVolta(&listaVoltas[i], 0);
			}
		}else{
			gravarMelhorVolta(&listaVoltas[i], 0);
		}
	}
	
}

