typedef struct {
	int id;
	char nome[TAM_NOME];
	char siglaEquipe[4];
	char dataNasc[11];
	char sexo;
	char pais[TAM_NOME];
} piloto;


//Protótipos

void cadastrarPiloto();
int getListaIdsPilotos(int listaIds[]);
int leValidaIdPiloto();
void alterarPiloto();
void excluirPiloto();
void gravarPiloto(piloto *novoPiloto, int flagReceberFeedback);
int buscaPilotos(piloto listaPilotos[]);
int qtdPilotosCadastrados(char siglaEquipe[]);

//Implementações

int getListaIdsPilotos(int listaIds[]){
	char buffer[300];
	int i=0, tempId=0, qtdRegistros=0;
	FILE* arquivo;
	
	qtdRegistros = qtdRegistrosArquivo("database/pilotos.txt");
	if(qtdRegistros>0){
		arquivo = fopen("database/pilotos.txt", "r");
		for(i=0; i<qtdRegistros; i++){
			fscanf(arquivo, "%d", &tempId);
			listaIds[i]=tempId;
			fgets(buffer, 290, arquivo);
		}
		fclose(arquivo);
	}
	return qtdRegistros;
}

int leValidaIdPiloto(){
	int id=0, n1=0, n2=0, n3=0, cont=0, qtdRegistros=0, listaIds[101];
	char mensagem[200], opcao;
	
	printf("Carregando, aguarde...");
	qtdRegistros = getListaIdsPilotos(listaIds);
	if(qtdRegistros<101){
		cont=0;
		do{
			n1=cont;
			cont++;
		}while(isIntNaLista(n1,listaIds, qtdRegistros));
		if(qtdRegistros<100){
			do{
				n2=cont;
				cont++;
			}while(isIntNaLista(n2,listaIds, qtdRegistros));
			if(qtdRegistros<99){
				do{
					n3=cont;
					cont++;
				}while(isIntNaLista(n3,listaIds, qtdRegistros));	
			}else{
				n3=n2;
			}
		}else{
			n2 = n1;
			n3 = n1;
		}
		
		system("cls");
		
		sprintf(mensagem, "Escolha um numero para o piloto:\nA-%d\nB-%d\nC-%d", n1, n2, n3);
		
		opcao = leValidaOpcao('A', 'C', mensagem);
		switch(opcao){
			case 'A':
				id=n1;
				break;
			case 'B':
				id=n2;
				break;
			case 'C':
				id=n3;
				break;
		}
	}else{
		id = -1;
	}
	return id;
}

void gravarPiloto(piloto *novoPiloto, int flagReceberFeedback){
	FILE* arquivo;
	
	if(arquivo = fopen("database/pilotos.txt", "a")){
		fprintf(arquivo, "%03d %-50s %3s %10s %c %-50s\n", 
							novoPiloto[0].id, 
							novoPiloto[0].nome, 
							novoPiloto[0].siglaEquipe,
							novoPiloto[0].dataNasc,
							novoPiloto[0].sexo,
							novoPiloto[0].pais);
		fclose(arquivo);
		if(flagReceberFeedback){
			printf("Piloto %s cadastrado com sucesso!\n", novoPiloto[0].nome);
			system("pause");
			system("cls");
		}
	}else if(flagReceberFeedback){
		printf("Nao foi possivel gravar o piloto!\n");
		system("pause");
		system("cls");
	}
}

void cadastrarPiloto(){
	piloto novo;

	if(!leEquipe(1, novo.siglaEquipe, 0, " ", "Informe a sigla da equipe do piloto:\n")){
		printf("Nao foi possivel cadastrar piloto pois nao existem equipes cadastradas!\n");
		system("pause");
		system("cls");
		return;
	}

	novo.id = leValidaIdPiloto();
	if(novo.id<0){
		printf("Maximo de pilotos ja cadastrados!\n");
		system("pause");
		system("cls");
		return;
	}
	leValidaNome("Informe o nome do piloto:\n", novo.nome);
	
	lePais(0, " ", 1, novo.pais, "Informe a pais do piloto: ");
	
	do{
		printf("Informe o sexo do piloto:\nM - Masculino\nF - Feminino\n");
		novo.sexo = getch();
		novo.sexo = toupper(novo.sexo);
		system("cls");
	}while(novo.sexo!='F' && novo.sexo!='M');
	
	printf("A seguir, informe a data de nascimento do piloto...\n");
	system("pause");
	system("cls");
	leData(novo.dataNasc, 1900, 2000);
	fflush(stdin);

	gravarPiloto(&novo, 1);
}

void alterarPiloto(){
	char opcao, menu[150] = "Escolha uma opcao:\n1-Ver lista de pilotos cadastrados\n2-Alterar piloto por codigo\n\n0-Voltar";
	
	do{
		opcao = leValidaOpcao('0','2', menu);
		switch(opcao){
		case '1':
			//TODO
			break;
		case '2':
			//TODO
			break;
		}
	}while(opcao!='0');
}

void excluirPiloto(){
	char opcao, msgConfirmacao[150], menu[150] = "Escolha uma opcao:\n1-Ver lista de pilotos cadastrados\n2-Excluir piloto por codigo\n\n0-Voltar";
	piloto listaPilotos[101];
	int qtdPilotosCadastrados=0, i=0, isIdPilotoCadastrado=0, idPiloto=0;
	FILE* arquivo;
	piloto *pilotoPointer;
	
	qtdPilotosCadastrados = buscaPilotos(listaPilotos);
	
	do{
		opcao = leValidaOpcao('0', '2', menu);
		switch(opcao){
		case '1':
			for(i=0; i<qtdPilotosCadastrados; i++){
				printf("%03d - %s\n", listaPilotos[i].id, listaPilotos[i].nome);
			}
			system("pause");
			system("cls");
			break;
		case '2':
			idPiloto = leValidaInteiro(0,100, "Informe o codigo/numero do piloto a ser excluido: ");
			for(i=0; i<qtdPilotosCadastrados; i++){
				if(idPiloto == listaPilotos[i].id){
					isIdPilotoCadastrado = 1;
				}
			}
			if(isIdPilotoCadastrado && !qtdVoltasRealizadas(idPiloto)){
				if(remove("database/pilotos.txt") == 0){
					for(i=0; i<qtdPilotosCadastrados; i++){
						if(idPiloto != listaPilotos[i].id){
							pilotoPointer = &listaPilotos[i];
							gravarPiloto(pilotoPointer, 0);
						}else{
							sprintf(msgConfirmacao,"Deseja excluir o piloto %s ?\n1-Sim\n2-Nao", listaPilotos[i].nome);
							opcao = leValidaOpcao('1', '2', msgConfirmacao);
							switch(opcao){
							case '1':
								printf("Piloto %s excluido com sucesso!", listaPilotos[i].nome);
								system("pause");
								system("cls");
								break;
							case '2':
								pilotoPointer = &listaPilotos[i];
								gravarPiloto(pilotoPointer, 0);
								printf("Exclusao cancelada!\n");
								system("pause");
								system("cls");
								break;
							}
							opcao = '0';
						}
					}
				}else{
					printf("Nao foi possivel excluir o piloto!\n");
					system("pause");
					system("cls");
				}
			}else{
				printf("Codigo/numero de piloto nao encontrado!\n");
				system("pause");
				system("cls");
			}
			break;
		}
	}while(opcao!='0');
}

int buscaPilotos(piloto listaPilotos[]){
	FILE* arquivo;
	char buffer;
	int qtdRegistros=0, i=0, j=0, k=0, aux=0;
	
	qtdRegistros = qtdRegistrosArquivo("database/pilotos.txt");
	
	if(arquivo = fopen("database/pilotos.txt", "rt")){
		for(i=0; i<qtdRegistros; i++){
			k=0;
			aux=0;
			listaPilotos[i].id = 0;
			for(j=0; j<=122; j++){
				buffer = fgetc(arquivo);
				if(j<4){
					converteCharParaInt(&aux, buffer);
					switch(j){
					case 0:
						listaPilotos[i].id += aux*100;
						break;
					case 1:
						listaPilotos[i].id += aux*10;
						break;
					case 2:
						listaPilotos[i].id += aux;
						aux = 0;
						break;
					}
				}else if(j<54){
					if(aux<3){
						if(aux==2 || j==53){
							listaPilotos[i].nome[k] = '\0';
							aux=3;
						}else{
							if(buffer==' '){
								aux++;
							}else{
								aux=0;
							}
							listaPilotos[i].nome[k] = buffer;
							k++;
						}
					}
				}else if(j==54){
					k=0;
					aux=0;
				}else if(j<58){
					listaPilotos[i].siglaEquipe[k] = buffer;
					k++;
				}else if(j==58){
					k=0;
					listaPilotos[i].siglaEquipe[3]='\0';
				}else if(j<69){
					listaPilotos[i].dataNasc[k] = buffer;
					k++;
				}else if(j==69){
					listaPilotos[i].dataNasc[11] = '\0';
					k=0;
				}else if(j==70){
					listaPilotos[i].sexo = buffer;
				}else if(j>71){
					if(aux<3){
						if(aux==2 || j==120){
							listaPilotos[i].pais[k] = '\0';
							aux=3;
						}else{
							if(buffer==' '){
								aux++;
							}else{
								aux=0;
							}
							listaPilotos[i].pais[k] = buffer;
							k++;
						}
					}
				}
			}
		}
		fclose(arquivo);
	}
	return qtdRegistros;
}

int qtdPilotosCadastrados(char siglaEquipe[]){
	int i=0, totalPilotos=0, qtdPilotosNaEquipe=0;
	piloto listaPilotos[101];
	
	totalPilotos = buscaPilotos(listaPilotos);
	
	for(i=0; i<totalPilotos; i++){
		if(isCodIgual(siglaEquipe, listaPilotos[i].siglaEquipe, 3)){
			qtdPilotosNaEquipe++;
		}
	}
	return qtdPilotosNaEquipe;
}
