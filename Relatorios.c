#define QTD_PILOTO 100
//#define TAM_NOME 50

/*typedef struct {
	int id;
	char nome[TAM_NOME];
	char siglaEquipe[4];
	char dataNasc[11];
	char sexo;
	char pais[TAM_NOME];
} Piloto;*/

//Prototipos
void leRelatorio1 (int opcao);

//Funções

void leRelatorio1 (int opcao){
	piloto piloto[QTD_PILOTO];
	FILE *arqPilotos;
	int qtdPilotos = 0, cont;
	
	fopen("database/pilotos.txt", "r");
	if(arqPilotos != NULL){
		printf("Arquivo aberto com sucesso!");
		
		qtdPilotos = buscaPilotos(piloto);
		
		switch(opcao){
			case '1':
			//Arquivo de PILOTOS
				printf("Pressione qualquer tecla para abrir o arquivo (PILOTOS.TXT)...");
				system("pause");
				//                               13             4             18              4       4  
				printf("%17s%50s%21s%7s%4s\n", "Identificacao", "Nome", "Data de Nascimento", "Sexo", "Pais");
				//"Identificacao    Nome                                              Data de Nascimento   Sexo   Pais"
				//     3            50                                                11                   1      20
				for(cont = 0; cont < qtdPilotos; cont++){
					printf("%-17d%50.50s%-21.11s%-7.s%4.50s\n", piloto[cont].id, piloto[cont].nome, piloto[cont].dataNasc, piloto[cont].sexo, piloto[cont].pais);
				}
	
				break;
			case '2':
			//Arquivo de EQUIPES
			
				break;
			case '3':
			//Arquivo de CIRCUITOS
			
				break;
		}
			fclose(arqPilotos);
	}else{
		printf("Nao foi possivel abrir o arquivo!");
		getch();
	}
}
