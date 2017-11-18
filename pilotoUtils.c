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
	char opcao, menu[200] = "Escolha uma opcao:\n1-Ver lista de pilotos cadastrados\n2-Alterar piloto por código";
	
	do{
		opcao = leValidaOpcao('1','2', menu);
		switch(opcao){
			case '1':
				//TODO
				break;
			case '2':
				//TODO
				break;
		}
	}while(opcao='1');
}

void excluirPiloto(){
	//TODO
}



