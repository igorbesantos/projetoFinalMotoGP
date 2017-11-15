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

void cadastrarPiloto(){
	//TODO
	piloto novo;

	novo.id = leValidaIdPiloto();
	if(novo.id<0){
		printf("Maximo de pilotos ja cadastrados!\n");
		system("pause");
		system("cls");
		return;
	}
	leValidaNome("Informe o nome do piloto:\n", novo.nome);
	
	lePais("a", "a", "a");
	
	printf("%d : %s", novo.id, novo.nome);
	
	
	//equipe
	//dataNasc
	//sexo
	//pais

	
}

void alterarPiloto(){
	//TODO
}

void excluirPiloto(){
	//TODO
}



