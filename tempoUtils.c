typedef struct {
	int minutos;
	int segundos;
	int milisegundos;
} tempo;


//Protótipos

int comparaTempo (tempo t1, tempo t2);
void recuperaTempoDeString(int *min, int  *seg, int *milis, char tempoFormatado[]);


//Implementações

int comparaTempo (tempo t1, tempo t2) {
	int resposta=0;
	if(t1.minutos==t2.minutos){
		if(t1.segundos==t2.segundos){
			resposta = t1.milisegundos - t2.milisegundos;
		}else{
			resposta = t1.segundos - t2.segundos;
		}
	}else{
		resposta = t1.minutos - t2.minutos;
	}
	return resposta;
}

void recuperaTempoDeString(int *min, int  *seg, int *milis, char tempoFormatado[]){
	int i=0, aux=0;
	*min = 0;
	*seg = 0;
	*milis = 0;
	for(i=0; i<8; i++){
		converteCharParaInt(&aux, tempoFormatado[i]);
		switch(i){
		case 0:
			*min += aux*10;
			break;
		case 1:
			*min += aux;
			break;
		case 3:
			seg += aux*10;
			break;
		case 4:
			seg += aux;
			break;
		case 6:
			milis += aux*10;
			break;
		case 7:
			milis += aux;
			break;
		}
	}
}

