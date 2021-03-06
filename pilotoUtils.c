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
void trocaPilotos(piloto *p1, piloto *p2);

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
	char opcao, msgConfirmacao[250], menu[150] = "Escolha uma opcao:\n1-Ver lista de pilotos cadastrados\n2-Alterar piloto por codigo\n\n0-Voltar";
	piloto listaPilotos[101];
	piloto *pilotoPointer;
	int qtdPilotos=0, i=0, isIdPilotoCadastrado=0, idPiloto=0;
	
	qtdPilotos = buscaPilotos(listaPilotos);
	
	do{
		opcao = leValidaOpcao('0','2', menu);
		switch(opcao){
		case '1':
			for(i=0; i<qtdPilotos; i++){
				printf("%03d - %s\n", listaPilotos[i].id, listaPilotos[i].nome);
			}
			system("pause");
			system("cls");
			break;
		case '2':
			isIdPilotoCadastrado=0;
			idPiloto = leValidaInteiro(0,100, "Informe o codigo/numero do piloto a ser alterado: ");
			for(i=0; i<qtdPilotos; i++){
				if(idPiloto == listaPilotos[i].id){
					isIdPilotoCadastrado = 1;
				}
			}
			if(isIdPilotoCadastrado){
				if(remove("database/pilotos.txt") == 0){
					for(i=0; i<qtdPilotos; i++){
						if(idPiloto != listaPilotos[i].id){
							pilotoPointer = &listaPilotos[i];
							gravarPiloto(pilotoPointer, 0);
						}else{
							sprintf(msgConfirmacao,"Deseja alterar o piloto %s ?\n1-Sim\n2-Nao", listaPilotos[i].nome);
							opcao = leValidaOpcao('1', '2', msgConfirmacao);
							switch(opcao){
							case '1':
								
								leEquipe(1, listaPilotos[i].siglaEquipe, 0, " ", "Informe a nova equipe do piloto> ");
								
								leValidaNome("Informe o novo nome do piloto:\n", listaPilotos[i].nome);
								
								lePais(0, " ", 1, listaPilotos[i].pais, "Informe o novo pais do piloto: ");
								
								do{
									printf("Informe o novo sexo do piloto:\nM - Masculino\nF - Feminino\n");
									listaPilotos[i].sexo = getch();
									listaPilotos[i].sexo = toupper(listaPilotos[i].sexo);
									system("cls");
								}while(listaPilotos[i].sexo!='F' && listaPilotos[i].sexo!='M');
								
								pilotoPointer = &listaPilotos[i];
								gravarPiloto(pilotoPointer, 0);
								
								printf("Piloto %s alterado com sucesso!", listaPilotos[i].nome);
								system("pause");
								system("cls");
								break;
							case '2':
								pilotoPointer = &listaPilotos[i];
								gravarPiloto(pilotoPointer, 0);
								printf("Alteracao cancelada!\n");
								system("pause");
								system("cls");
								break;
							}
							opcao = '0';
						}
					}
				}else{
					printf("Nao foi possivel acessar o arquivo de pilotos!\n");
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

void ordenaListaPilotos(int qtdPilotos, piloto listaPilotos[]){
	int i=0, j=0, posicao=0;
	
	for(i=0; i<(qtdPilotos-1); i++){
		posicao=i;
		for(j=i+1; j<qtdPilotos; j++){
			if(strcoll(listaPilotos[i].nome, listaPilotos[j].nome)>0){
				posicao = j;
			}
		}
		if(posicao != i){
			trocaPilotos(&listaPilotos[i], &listaPilotos[j]);
		}
	}
}

void trocaPilotos(piloto *p1, piloto *p2){
	piloto t;

	strcpy(t.dataNasc, p1[0].dataNasc);
	t.id = p1[0].id;
	strcpy(t.nome, p1[0].nome);
	strcpy(t.pais, p1[0].pais);
	t.sexo = p1[0].sexo;
	strcpy(t.siglaEquipe, p1[0].siglaEquipe);
	
	strcpy(p1[0].dataNasc, p2[0].dataNasc);
	p1[0].id = p2[0].id;
	strcpy(p1[0].nome, p2[0].nome);
	strcpy(p1[0].pais, p2[0].pais);
	p1[0].sexo = p2[0].sexo;
	strcpy(p1[0].siglaEquipe, p2[0].siglaEquipe);
	
	strcpy(p2[0].dataNasc, t.dataNasc);
	p2[0].id = t.id;
	strcpy(p2[0].nome, t.nome);
	strcpy(p2[0].pais, t.pais);
	p2[0].sexo = t.sexo;
	strcpy(p2[0].siglaEquipe, t.siglaEquipe);
}
