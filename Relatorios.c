#define QTD_PILOTO 100

//Prototipos
void leRelatorio1 (int opcao);
void leRelatorio2();
void leRelatorio3(int opcao);
void leRelatorio4();
void leRelatorio5();
void leRelatorio6();
void leRelatorio7();

//Funções
/*Okay
1.Consulta simples sobre todos os arquivos existentes através da sua 
	chave única ou apresentar todos os dados cadastrados
	.*/
void leRelatorio1 (int opcao){
	piloto piloto[QTD_PILOTO];
	equipe equipes[MAX_EQUIPES];
	melhorVolta melhoresVoltas[MAX_MELHORES_VOLTAS];
	circuito circuitos[MAX_CIRCUITOS];
	
	FILE *arqPilotos;
	int qtdPilotos = 0, qtdEquipes = 0, qtdCircuitos = 0, qtdMelhoresVoltas = 0, cont, idPesquisa;
	
	qtdPilotos = buscaPilotos(piloto);
	switch(opcao){
		case '1':
		//Pesquisa PILOTO
			idPesquisa = leValidaInteiro(0, 100, "Informe a Id do piloto para pesquisa: ");
			for(cont = 0; cont< qtdPilotos; cont++){
				if(idPesquisa == piloto[cont].id){
					printf("%-17s%-50s%-21s%-7s%-4s\n", "Identificacao", "Nome", "Data de Nascimento", "Sexo", "Pais");
					printf("%-17d%-50.50s%-21.11s%-7.c%-4.50s\n", piloto[cont].id, piloto[cont].nome, piloto[cont].dataNasc, piloto[cont].sexo, piloto[cont].pais);
					break;
				}
			}
			break;
		case '2':
		//Arquivo de PILOTOS
			system("cls");
			if(qtdPilotos == 0){
				printf("Arquivo pilotos.txt esta vazio!\n");
			}else{
				printf("%-17s%-50s%-21s%-7s%-4s\n", "Identificacao", "Nome", "Data de Nascimento", "Sexo", "Pais");
				for(cont = 0; cont < qtdPilotos; cont++){
					printf("%-17d%-50.50s%-21.11s%-7.c%-4.50s\n", piloto[cont].id, piloto[cont].nome, piloto[cont].dataNasc, piloto[cont].sexo, piloto[cont].pais);
					fflush(stdin);
				}
			}
			break;
		case '3':
		//Arquivo de EQUIPES
			qtdEquipes = buscaEquipes(equipes);
			if(qtdEquipes == 0){
				printf("Arquivo equipes.txt esta vazio!\n");
			}else{
				printf("%-54s%-8s%-20s\n", "Nome", "Sigla", "Pais");
				for(cont = 0; cont < qtdEquipes; cont++){
					printf("%-54s%-8s%-20s\n", equipes[cont].nome, equipes[cont].sigla, equipes[cont].pais);
				}
			}
			break;
		case '4':
		//Arquivo de CIRCUITOS
			qtdCircuitos = buscaCircuitos(circuitos);
			//printf("\n%d\n", qtdCircuitos);
			if(qtdCircuitos == 0){
				printf("Arquivo circuitos.txt esta vazio!\n");
			}else{
				printf("%-15s%-30s%-20s%-11s%-15s%-21s\n", "ID Circuito", "Nome", "Pais", "Tamanho", "Menor Tempo", "ID Piloto menor tempo");
				for(cont = 0; cont < qtdCircuitos; cont++){
					printf("%-15d%-30s%-20s%-11.2f", circuitos[cont].id, circuitos[cont].nome, circuitos[cont].pais, circuitos[cont].tamanho);
					printf("%02d:%02d:%02d%10d\n",circuitos[cont].menorTempo.minutos,
					circuitos[cont].menorTempo.segundos,
					circuitos[cont].menorTempo.milisegundos,
					circuitos[cont].idPilotoMenorTempo);
				}
			}
			break;
		case '5':
		//Arquivo de MELHORES VOLTAS
			qtdMelhoresVoltas = buscaMelhoresVoltas(melhoresVoltas);
			if(qtdMelhoresVoltas == 0){
				printf("Arquivo voltas.txt esta vazio!\n");
			}else{
				printf("%-13s%-15s%-15s%-9s\n", "ID Piloto", "ID Circuito", "Data", "Tempo");
				for(cont = 0; cont < qtdMelhoresVoltas; cont++){
					printf("%-13d%-15d%-15s%-9s\n", melhoresVoltas[cont].idPiloto, melhoresVoltas[cont].idCircuito, melhoresVoltas[cont].data, melhoresVoltas[cont].tempo);
				}
			}
			break;
	}
	system("pause");
	system("cls");
}

/* Okay
2.Pesquisar os pilotos registrados em seu programa pelo nome. Esta
	pesquisa ocorrerá por qualquer parte do nome do piloto. No caso de
	existirem vários pilotos que satisfaçam a esta parte do nome, deverá ser
	mostrada uma tabela ordenada, alfabeticamente, com os dados cadastrados
	para cada piloto (mostrar todos seus dados cadastrais de forma tabelar com
	uma única linha de cabeçalho, devendo as colunas serem identificadas por
	extenso)
	.
*/
void leRelatorio2(){
	int qtdPilotos, cont = 0, cont2 = 0, flag = 0;
	piloto piloto[QTD_PILOTO], pilotosAux[QTD_PILOTO];
	char nomePilotoPesquisa[TAM_NOME];
	
	qtdPilotos = buscaPilotos(piloto);
	qtdPilotos = buscaPilotos(pilotosAux);

	leValidaNome("Informe o nome do Piloto para pesquisa: ", nomePilotoPesquisa);
	for(cont = 0; cont < strlen(nomePilotoPesquisa); cont++){
		nomePilotoPesquisa[cont] = toupper(nomePilotoPesquisa[cont]);
	}
	
	for(cont2= 0; cont2 < qtdPilotos; cont2++){
		for(cont= 0; cont < strlen(pilotosAux[cont2].nome); cont++){
			pilotosAux[cont2].nome[cont] = toupper(pilotosAux[cont2].nome[cont]);
		}
	}
	
	for(cont= 0; cont < qtdPilotos; cont++){
		if(strstr(pilotosAux[cont].nome, nomePilotoPesquisa)){
			flag = 1;
			break;
		}
	}
	
	if(flag == 1){
		printf("%-17s%-50s%-21s%-7s%-4s\n", "Identificacao", "Nome", "Data de Nascimento", "Sexo", "Pais");
		for(cont= 0; cont < qtdPilotos; cont++){
			if(strstr(pilotosAux[cont].nome, nomePilotoPesquisa)){
				printf("%-17d%-50.50s%-21.11s%-7.c%-4.50s\n", piloto[cont].id, piloto[cont].nome, piloto[cont].dataNasc, piloto[cont].sexo, piloto[cont].pais);
			}
		}
	}else{
		printf("Nao existe nenhum piloto com a string informada!");
	}
	system("pause");
	system("cls");
}

/* Okay
3.Relacionar todos os pilotos que realizaram voltas em um circuito
específico fornecido pelo usuário, indicando todos os dados relacionados
com a sua volta rápida realizada neste circuito. O usuário poderá também
definir, além do circuito, uma data válida e completa para fazer esta
consulta
	.*/
void leRelatorio3(int opcao){
	piloto piloto[QTD_PILOTO];
	melhorVolta melhoresVoltas[MAX_MELHORES_VOLTAS];
	
	int idCircuitoPesquisa, qtdMelhoresVoltas, qtdPilotos, qtdCircuitos, flag = 0, cont = 0;
	int  dia = 0, mes = 0, ano = 0, valido = 0;
	char buffer[20], dataPesquisa[11];
	
	qtdMelhoresVoltas = buscaMelhoresVoltas(melhoresVoltas);
	qtdPilotos = buscaPilotos(piloto);
	
	switch(opcao){
		case '1':
			idCircuitoPesquisa = leValidaInteiro(0, 100, "Informe o Id do circuito para pesquisa: ");
			for(cont = 0; cont < qtdMelhoresVoltas; cont++){
				if(idCircuitoPesquisa == melhoresVoltas[cont].idCircuito){
					flag = 1;
					break;
				}else{
					flag = 0;
				}
			}
			if(flag == 1){
				printf("%-13s%-15s%-15s%-9s\n", "ID Piloto", "ID Circuito", "Data", "Tempo");
				for(cont = 0; cont < qtdMelhoresVoltas; cont++){
					if(idCircuitoPesquisa == melhoresVoltas[cont].idCircuito){
						printf("%-13d%-15d%-15s%-9s\n", melhoresVoltas[cont].idPiloto, melhoresVoltas[cont].idCircuito, melhoresVoltas[cont].data, melhoresVoltas[cont].tempo);
					}
				}
			}else{
				printf("Circuito nao registrado!\n");
			}
			break;
		case '2':
			do{
				printf("Agora, informe a data da corrida... \n");
				system("pause");
				system("cls");
				leData(buffer, 2017, 2100);
				fflush(stdin);
				interpretaDataFormatada(&dia, &mes, &ano, buffer);
				if(getDiaSemana(dia, mes, ano) == 6){
					if(ano > 2017){
						valido = 1;
					}else if(ano == 2017){
						if(mes > 6){
							valido = 1;
						}else if(mes == 6){
							if(dia >= 4){
								valido = 1;
							}
						}
					}
				}else{
					printf("Dia informado nao e domingo!\n");
				}
				if(!valido){
					printf("Data informada nao e valida! (Data minima: 04/06/2017)\n");
				}
				system("cls");
			}while(valido == 0);
			
			strcpy(dataPesquisa, buffer);
			
			for(cont = 0; cont < qtdMelhoresVoltas; cont++){
				if(strcmp(dataPesquisa, melhoresVoltas[cont].data)){
					flag = 1;
				}else{
					flag = 0;
				}
			}
			if(flag == 1){
				printf("%-13s%-15s%-15s%-9s\n", "ID Piloto", "ID Circuito", "Data", "Tempo");
				for(cont = 0; cont < qtdMelhoresVoltas; cont++){
					if(strcmp(dataPesquisa, melhoresVoltas[cont].data) == 0){
						printf("%-13d%-15d%-15s%-9s\n", melhoresVoltas[cont].idPiloto, melhoresVoltas[cont].idCircuito, melhoresVoltas[cont].data, melhoresVoltas[cont].tempo);
					}
				}
			}
			break;
	}
	
	system("pause");
	system("cls");
}

/*
4.Consultar todos os circuitos cadastrados por qualquer parte de seu
	nome que será fornecido pelo usuário ou por seu código (chave), onde todos
	os dados de cadastro dos circuitos deverão ser mostrados de maneira
	tabelar, com somente uma linha de cabeçalho. Esta consulta só poderá ser
	realizada usando recursos de alocação dinâmica (ver esclarecimentos no
	tópico PESQUISA-1 a seguir). Junto com os dados do circuito deverá ser
	apresentado o nome completo do piloto que obteve o menor tempo do
	circuito
	.
*/
void leRelatorio4(){
	
}

/*
5.Apresentar todos os pilotos de uma equipe em um período de data
	(de... até...) completa (dia/mês/ano) fornecido pelo usuário, onde será
	mostrado somente o nome e código do piloto, a data em que o piloto realizou
	volta por tal equipe e o nome do circuito onde isto ocorreu. A apresentação
	deverá estar em ordem alfabética de piloto
	.
*/
void leRelatorio5(){
	int qtdMelhoresVoltas = 0, qtdPilotos = 0, cont = 0; 
	piloto piloto[QTD_PILOTO];
	melhorVolta melhoresVoltas[MAX_MELHORES_VOLTAS];
	
	qtdMelhoresVoltas = buscaMelhoresVoltas(melhoresVoltas);
	qtdPilotos = buscaPilotos(piloto);
	
	printf("%-17s%-50s\n", "Identificacao","Nome");
	for(cont = 0; cont < qtdPilotos; cont++){
		printf("%-17d%-50s\n", piloto[cont].id,piloto[cont].nome);
	}
}

/* Okay
6.Pesquisar todos os pilotos, equipes e circuitos que realizaram um
	tempo de volta menor ou igual ao fornecido pelo usuário (minutos, segundos
	e milissegundos)
	.
*/
void leRelatorio6(){
	int min = 0, seg = 0, milis = 0, flag = 0, cont = 0, cont2 = 0, cont3 = 0;
	int minAux = 0, segAux = 0, milisAux = 0, qtdMelhoresVoltas = 0, qtdPilotos = 0, qtdCircuitos = 0; 
	piloto piloto[QTD_PILOTO];
	melhorVolta melhoresVoltas[MAX_MELHORES_VOLTAS];
	circuito circuitos[MAX_CIRCUITOS];
	
	qtdMelhoresVoltas = buscaMelhoresVoltas(melhoresVoltas);
	qtdPilotos = buscaPilotos(piloto);
	qtdCircuitos = buscaCircuitos(circuitos);
	
	min = leValidaInteiro(1,59, "Informe os minutos do melhor tempo do piloto (Min: 1 minuto):");
	
	seg = leValidaInteiro(0,59, "Informe os segundos do melhor tempo do piloto:");
	
	milis = leValidaInteiro(0,99, "Informe os milissegundos do melhor tempo do piloto:");
	
	
	for(cont = 0; cont < qtdMelhoresVoltas; cont++){
		recuperaTempoDeString(&minAux, &segAux, &milisAux, melhoresVoltas[cont].tempo);
		if(minAux < min){
			flag = 1;
			break;
		}else if(minAux == min){
			if(segAux < seg){
				flag = 1;
				break;
			}else if(segAux == seg){
				if(milisAux <= milis){
					flag = 1;
				}else{
					flag = 0;
				}
			}
		}
	}
	
	if(flag == 1){
		printf("%-17s%-50s%-19s\n","Identificacao", "Nome do piloto", "Sigla da Equipe");
		for(cont = 0; cont < qtdMelhoresVoltas; cont++){
			recuperaTempoDeString(&minAux, &segAux, &milisAux, melhoresVoltas[cont].tempo);
			if(minAux < min){
				for(cont2 = 0; cont2 < qtdPilotos; cont2++){	
					if(melhoresVoltas[cont2].idPiloto == piloto[cont].id){
						printf("%-17d%-50s%-19s\n", piloto[cont2].id, piloto[cont2].nome, piloto[cont2].siglaEquipe);
					}
				}
			}else if(minAux == min){
				if(segAux < seg){
					for(cont2 = 0; cont2 < qtdPilotos; cont2++){	
							if(melhoresVoltas[cont2].idPiloto == piloto[cont].id){
								printf("%-17d%-50s%-19s\n", piloto[cont2].id, piloto[cont2].nome, piloto[cont2].siglaEquipe);
							}
					}
				}else if(segAux == seg){
					if(milisAux <= milis){
						for(cont2 = 0; cont2 < qtdPilotos; cont2++){	
								if(melhoresVoltas[cont2].idPiloto == piloto[cont].id){
									printf("%-17d%-50s%-19s\n", piloto[cont2].id, piloto[cont2].nome, piloto[cont2].siglaEquipe);
								}
						}
					}
				}
			}
		}
		
		
	}else{
		printf("Nao existe nenhum piloto de nenhuma equipe com o tempo menor ou igual ao informado!\n");	
	}
	system("pause");
	system("cls");	
}

/*
7.Exibir todos os Pilotos, Equipes ou Circuitos que não estão
	cadastrados em nenhuma Melhor Volta.
	.
*/
void leRelatorio7(){
	int cont = 0, cont2 = 0, aux = 0, qtdCircuitos = 0, qtdMelhoresVoltas = 0, qtdPilotos = 0, flag[QTD_PILOTO] = {0};
	piloto piloto[QTD_PILOTO], pilotoAux[QTD_PILOTO];
	melhorVolta melhoresVoltas[MAX_MELHORES_VOLTAS], melhoresVoltasAux[MAX_MELHORES_VOLTAS];
	circuito circuitos[MAX_CIRCUITOS], circuitosAux[MAX_CIRCUITOS];
	
	qtdMelhoresVoltas = buscaMelhoresVoltas(melhoresVoltas);
	qtdMelhoresVoltas = buscaMelhoresVoltas(melhoresVoltasAux);
	qtdPilotos = buscaPilotos(piloto);
	qtdPilotos = buscaPilotos(pilotoAux);
	qtdCircuitos = buscaCircuitos(circuitos);
	qtdCircuitos = buscaCircuitos(circuitosAux);
	
	for(cont = 0; cont < qtdMelhoresVoltas; cont++){
		for(cont2 = 0; cont2 < qtdPilotos; cont2++){
			if(piloto[cont2].id == melhoresVoltas[cont].idPiloto){
				pilotoAux[cont2].id = 0;
				break;
			}
		}
	}
	
	if(pilotoAux[cont2].id == 0){
		printf("%s\n\n%-50s%-13s\n","+=+=+Pilotos+=+=+", "Nome", "Identificacao");
		for(cont = 0; cont < qtdMelhoresVoltas; cont++){
			for(cont2 = 0; cont2 < qtdPilotos; cont2++){
				if(pilotoAux[cont2].id != 0){	
					printf("%-13d%-50s\n", piloto[cont2].id, piloto[cont2].nome);
				}
			}
		}
	}
	
	
	
	system("pause");
	system("cls");
}

