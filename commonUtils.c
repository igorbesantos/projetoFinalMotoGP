//Prot�tipos

char leValidaOpcao(char min, char max, char *mensagem);
int isCharValido(char c);
int isNomeInvalido(char *nome);
void leValidaNome(char mensagem[], char destino[]);
int leValidaInteiro(int min, int max, char *mensagem);
int aleatorio(int min, int max);
int qtdRegistrosArquivo(char *caminhoArquivo);
int isIntNaLista(int numero, int lista[], int tamLista);
void converteCharParaInt(int *destino, char *entrada);

//Implementa��es

/* 	Objetivo: Ler e validar entrada de op��o de menu
	Entrada: Opcao (char)
	Params: Menor e maior char poss�veis
	Retorno: char opcao
*/
char leValidaOpcao(char min, char max, char *mensagem){
	char opcao;
	fflush(stdin);
	do{
		printf("%s", mensagem);
		opcao = getch();
		opcao = toupper(opcao);
		system("cls");
		if(opcao<min || opcao>max){
			printf("Opcao invalida!\n");
		}
	}while(opcao<min || opcao>max);
	return opcao;
}

/* 	Objetivo: Verificar se char � v�lido para nomea��o
	Params: Char a ser verificado
	Retorno: 0 se for v�lido OU c�digo inteiro significativo > 0 se inv�lido
*/
int isCharValido(char c){
	if(c!='\t' && c!='\n'){
		if(c==' '){
			return 1;
		}
		if((c >= 65 && c <= 90) || (c >= 97 && c <= 122)){
			return 2;
		}
	}
	return 0;
}

/* 	Objetivo: Verifica se o nome obedece �s regras de nomea��o
	Params: Nome a ser verificado
	Retorno: 0 se for v�lido OU c�digo inteiro significativo > 0 se inv�lido
*/
int isNomeInvalido(char *nome){
	int result=0, i=0, tam=0;
	tam = strlen(nome);
	if(tam==0){
		result = 4;
	}else if(nome[0]==' '){
		result = 1;
	}else if (nome[tam-1]==' '){
		result = 5;
	} else {
		for(i=0; i<tam; i++){
			if(!isCharValido(nome[i])){
				result=2;
			}
			if(i!=tam){
				if(nome[i]==' ' && nome[i+1]==' '){
					result=3;
				}
			}
		}
	}
	return result;
}

/* 	Objetivo: Ler nome v�lido
	Entrada: Nome (recebe nomes at� que um v�lido seja informado)
	Params: Mensagem que solicita digita��o do usu�rio e ponteiro para vari�vel onde ser� armazendado o nome
*/
void leValidaNome(char mensagem[], char destino[]){
	int resultado = 0;
	char nome[300];
	do{
		printf("%s", mensagem);
		fflush(stdin);
		gets(nome);
		system("cls");
		if(strlen(nome) >= TAM_NOME){
			printf("Nome muito grande!\n");
			system("pause");
			system("cls");
		}else{
			resultado = isNomeInvalido(nome);
			if(resultado==1){
				printf("Nome nao pode iniciar com espaco em branco!\n");
			} else if(resultado==2){
				printf("Nome nao pode conter numeros ou caracteres especiais!\n");
			}else if(resultado==3){
				printf("Nome deve conter apenas espacos simples!\n");
			}else if(resultado==4){
				printf("Nome nao pode ser vazio!\n");
			}else if(resultado==5){
				printf("Nome nao pode acabar com espaco em branco!\n");
			}else if(resultado){
				printf("Nome invalido!\n");
			}
		}
	}while(resultado);
	strcpy(destino, nome);
}

/*	Objetivo: Ler n�mero inteiro
	Entrada: N�mero (recebe n�meros at� que um v�lido seja informado)
	Params: Menor e maior n�meros poss�veis, e mensagem que solicita digita��o do usu�rio
	Retorno: int numero
*/
int leValidaInteiro(int min, int max, char *mensagem){
	int numero=0;
	do{
		printf("%s\n", mensagem);
		scanf("%d", &numero);
		system("cls");
		if(numero<min || numero>max){
			printf("Numero invalido!\n");
		}
	}while(numero<min || numero>max);
	fflush(stdin);
	return numero;
}

/*	Objetivo: Retornar um numero aleatorio entre min e o max
	Params: N�meros m�nimo e m�ximo poss�veis
	Retorno: N�mero aleat�rio entre min e o max
*/
int aleatorio(int min, int max){
	if(min==max){
		return min;
	}else{
		max++;
		srand((unsigned)time(NULL));
		return min + rand() % (max-min);
	}
}

int qtdRegistrosArquivo(char *caminhoArquivo){
	FILE* arquivo;
	int qtdRegistros=0;
	char c;
	
	if(arquivo = fopen(caminhoArquivo, "r")){
		if(feof(arquivo)){
			qtdRegistros=0;
		}else{
			while(!feof(arquivo)){
				c=fgetc(arquivo);
				if(c=='\n'){
					qtdRegistros++;
				}
			}	
		}
	} else {
		qtdRegistros = -1;
	}
	fclose(arquivo);
	return qtdRegistros;
}

int isIntNaLista(int numero, int lista[], int tamLista){
	int i=0;
	
	for(i=0; i<tamLista; i++){
		if(numero==lista[i]){
			return 1;
		}
	}
	return 0;
}

void converteCharParaInt(int *destino, char *entrada){
	switch(*entrada){
		case '0':
			*destino = 0;
			break;
		case '1':
			*destino = 1;
			break;
		case '2':
			*destino = 2;
			break;
		case '3':
			*destino = 3;
			break;
		case '4':
			*destino = 4;
			break;
		case '5':
			*destino = 5;
			break;
		case '6':
			*destino = 6;
			break;
		case '7':
			*destino = 7;
			break;
		case '8':
			*destino = 8;
			break;
		case '9':
			*destino = 9;
			break;
		default:
			*destino = -1;
	}
}
