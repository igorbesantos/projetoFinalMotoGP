typedef struct {
	int dia;
	int mes;
	int ano;
} date;

//Protótipos
void leData(char *saidaFormatada, int anoMin, int anoMax);
void formataData(char *saidaFormatada, int dia, int mes, int ano);
void interpretaDataFormatada(int *dia, int *mes, int *ano, char *dataFormatada);
int getDiaSemana(int dia, int mes, int ano);
int comparaData(date d1, date d2);

//Implementações
int comparaData(date d1, date d2){
	int resposta=0;
	if(d1.ano==d2.ano){
		if(d1.mes==d2.mes){
			resposta = d1.dia - d2.dia;
		}else{
			resposta = d1.mes - d2.mes;
		}
	}else{
		resposta = d1.ano - d2.ano;
	}
	return resposta;
}

void leData(char *saidaFormatada, int anoMin, int anoMax){
	int ano=0, mes=0, dia=0, maxDia=0;
	
	ano = leValidaInteiro(anoMin, anoMax, "Informe o ano (AAAA):");
	
	mes = leValidaInteiro(1, 12, "Informe o mes (1 - 12):");
	
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
	
	dia = leValidaInteiro(1, maxDia, "Informe o dia:");
	
	formataData(saidaFormatada, dia, mes, ano);
}

void formataData(char *saidaFormatada, int dia, int mes, int ano){
	sprintf(saidaFormatada, "%02d/%02d/%04d",dia,mes,ano);
}

void interpretaDataFormatada(int *dia, int *mes, int *ano, char dataFormatada[]){
	int aux=0, i=0;
	*dia = 0;
	*mes = 0;
	*ano = 0;
	
	for(i=9; i>=0; i--){
		converteCharParaInt(&aux, dataFormatada[i]);
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

int getDiaSemana(int dia, int mes, int ano){
	int diferencaAnos=0, qtdDiasExtraFev=0, codigoMes=0, diaSemana=0;
	
	diferencaAnos = ano - 1900;
	qtdDiasExtraFev = diferencaAnos/4;
	if((ano%4==0) && (ano%100!=0)){
		if(mes<=2){
			qtdDiasExtraFev--;
		}
	}
	
	switch(mes){
	case 1:
	case 10:
		codigoMes=0;
		break;
	case 5:
		codigoMes=1;
		break;
	case 8:
		codigoMes=2;
		break;
	case 2:
	case 3:
	case 11:
		codigoMes=3;
		break;
	case 6:
		codigoMes=4;
		break;
	case 9:
	case 12:
		codigoMes=5;
		break;
	case 4:
	case 7:
		codigoMes=6;
		break;
	}
	
	diaSemana = (diferencaAnos + qtdDiasExtraFev + codigoMes + dia - 1)%7;
	printf("%d / %d / %d\n", dia, mes, ano);
	system("pause");
	
	//OBS: Segunda = 0 / Domingo = 6
	return diaSemana;
}

