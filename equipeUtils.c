typedef struct {
	char nome[TAM_NOME];
	char sigla[4];
	char pais[TAM_NOME];
} equipe;


//Protótipos

int getListaSiglasEquipe(char lista[][4]);
int isSiglaEquipeCadastrada(char *sigla);
void leValidaSiglaEquipe(char *destino);
void cadastrarEquipe();

//Implementações

int getListaSiglasEquipe(char lista[][4]){
	int qtdRegistros=0, i=0;
	char buffer[300], temp[4];
	FILE* arquivo;
	
	qtdRegistros = qtdRegistrosArquivo("database/equipes.txt");
	if(qtdRegistros>0){
		arquivo = fopen("database/equipes.txt", "r");
		for(i=0; i<qtdRegistros; i++){
			fgets(buffer, 290, arquivo);
			lista[i][0] = buffer[51];
			lista[i][1] = buffer[52];
			lista[i][2] = buffer[53];
			lista[i][3]='\0';
		}
		fclose(arquivo);
	}
	return qtdRegistros;
}

int isSiglaEquipeCadastrada(char *sigla){
	char listaSiglasEquipesCadastradas[MAX_EQUIPES][4];
	int i=0, qtdRegistros=0;
	
	qtdRegistros = getListaSiglasEquipe(listaSiglasEquipesCadastradas);
	for(i=0; i<qtdRegistros; i++){
		if(		toupper(listaSiglasEquipesCadastradas[i][0])==toupper(sigla[0]) && 
				toupper(listaSiglasEquipesCadastradas[i][1])==toupper(sigla[1]) && 
				toupper(listaSiglasEquipesCadastradas[i][2])==toupper(sigla[2]))
			{
			sigla[0]=listaSiglasEquipesCadastradas[i][0];
			sigla[1]=listaSiglasEquipesCadastradas[i][1];
			sigla[2]=listaSiglasEquipesCadastradas[i][2];
			return 1;
		}
	}
	system("pause");
	return 0;
}

void leValidaSiglaEquipe(char *destino){
	char buffer[300];
	do{
		printf("Informe a sigla da equipe:\n");
		fflush(stdin);
		scanf(" %s", buffer);
		system("cls");
		if(strlen(buffer)>3){
			printf("Sigla deve conter apenas 3 caracteres!\n");
		}
	}while(strlen(buffer)>3 || !isSiglaEquipeCadastrada(buffer));
	strcpy(destino, buffer);
}

void cadastrarEquipe(){
	equipe nova;
	leValidaNome("Informe o nome da equipe:\n", nova.nome);
	leValidaSiglaEquipe(nova.sigla);
	//pais
	printf("%s : %s", nova.nome, nova.sigla);
}
