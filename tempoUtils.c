typedef struct {
	int minutos;
	int segundos;
	int milisegundos;
} tempo;


//Protótipos

int comparaTempo (tempo t1, tempo t2);


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
