typedef struct {
	int dia;
	int mes;
	int ano;
} date;

//Protótipos
void leData(char *saidaFormatada, int anoMin, int anoMax);
void formataData(char *saidaFormatada, int dia, int mes, int ano);
void interpretaDataFormatada(int *dia, int *mes, int *ano, char *dataFormatada);

//Implementações
void leData(char *saidaFormatada, int anoMin, int anoMax){
	int ano=0, mes=0, dia=0, maxDia=0;
	
	ano = leValidaInteiro(anoMin, anoMax, "Informe o ano de nascimento do piloto (AAAA):\n");
	
	mes = leValidaInteiro(1, 12, "Informe o mes de nascimento do piloto (1 - 12):\n");
	
	switch(mes){
	case 1:
	case 3:
	case 5:
	case 7:
	case 8:
	case 10:
	case 12:
		maxDia = 31;
		break;
	case 4:
	case 6:
	case 9:
	case 11:
		maxDia = 30;
		break;
	case 2:
		if((ano%4==0) && (ano%100!=0)){
			maxDia = 29;
		}else{
			maxDia = 28;
		}
		break;
	}
	
	dia = leValidaInteiro(1, maxDia, "Informe o dia de nascimento do piloto:\n");
	
	formataData(saidaFormatada, dia, mes, ano);
}

void formataData(char *saidaFormatada, int dia, int mes, int ano){
	sprintf(saidaFormatada, "%2d/%2d/%4d",dia,mes,ano);
}

void interpretaDataFormatada(int *dia, int *mes, int *ano, char *dataFormatada){
	int aux=0, i=0;
	*dia = 0;
	*mes = 0;
	*ano = 0;
	
	for(i=9; i>=0; i--){
		converteCharParaInt(&aux,dataFormatada);
		switch(i){
			case 0:
				*dia += aux*10;
				break;
			case 1:
				*dia += aux;
				break;
			case 3:
				*mes += aux*10;
				break;
			case 4:
				*mes += aux;
				break;
			case 6:
				*ano += aux*1000;
				break;
			case 7:
				*ano += aux*100;
				break;
			case 8:
				*ano += aux*10;
				break;
			case 9:
				*ano += aux;
				break;
		}
	}
	
	
	
}


