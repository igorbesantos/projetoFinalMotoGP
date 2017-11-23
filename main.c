/* Alunos:							Matr�culas:	
	Igor Bezerra dos Santos			UC16101948
	Jo�o Henrique Braz da Silva		UC16101210
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

#define TAM_NOME 50
#define MAX_EQUIPES 50
#define MAX_CIRCUITOS 50
#define MAX_MELHORES_VOLTAS 50

#include "commonUtils.c"
#include "dateUtils.c"
#include "tempoUtils.c"
#include "paisUtils.c"
#include "equipeUtils.c"
#include "pilotoUtils.c"
#include "circuitoUtils.c"
#include "melhorVoltaUtils.c"
#include "Relatorios.c"


int main() {
//Declara��es
	//Menus
	char menu0[70] = "1-Alterar dados cadastrais\n2-Relatorios\n\n0-Encerrar programa";
	char menu1[90] = "ALTERACAO DE DADOS CADASTRAIS\n\n1-Pilotos\n2-Equipes\n3-Circuitos\n4-Voltas\n\n0-Voltar";
	char menu11[80] = "ALTERACAO DE DADOS DE PILOTOS\n\n1-Incluir\n2-Alterar\n3-Excluir\n\n0-Voltar";
	char menu12[70] = "ALTERACAO DE DADOS DE EQUIPES\n\n1-Incluir\n2-Excluir\n\n0-Voltar";
	char menu13[70] = "ALTERACAO DE DADOS DE CIRCUITOS\n\n1-Incluir\n2-Alterar\n\n0-Voltar";
	char menu14[90] = "ALTERACAO DE DADOS DE MELHOR VOLTA\n\n1-Incluir\n2-Alterar\n3-Excluir\n\n0-Voltar";
	char menu2[300] = "RELATORIOS\n\n1-Consulta em todos arquivos\n2-Pesquisar pilotos por nome\n3-Relacionar pilotos por circuito\n4-Consultar circuitos\n5-Consultar pilotos por equipe\n6-Pesquisar volta por tempo\n7-Consultar registros nao relacionados a nenhuma volta\n\n0-Voltar";
	char menuRel1[120] = "Relatorio 1\n1-Pesquisa piloto\n2-Arquivo pilotos.txt\n3-Arquivo equipes.txt\n4-Arquivo circuitos.txt\n5-Arquivo voltas.txt.";
	char menuRel2[100] = "Relatorio 3\nPesquisar melhor volta por: \n1-ID do circuito.\n2-Data.";
	char opcao;
	int encerrarPrograma = 0;
	

//Instru��es
	do{
		opcao = leValidaOpcao('0','2',menu0);
		switch(opcao){
			case '1':
				opcao = leValidaOpcao('0','4', menu1);
				switch(opcao){
					case '1':
						opcao = leValidaOpcao('0','3', menu11);
						switch(opcao){
							case '1':
								cadastrarPiloto();
								break;
							case '2':
								//TODO Alterar piloto
								alterarPiloto();
								break;
							case '3':
								excluirPiloto();
								
								break;
						}
						break;
					case '2':
						opcao = leValidaOpcao('0', '2', menu12);
						switch(opcao){
							case '1':
								cadastrarEquipe();
								break;
							case '2':
								excluirEquipe();
								break;
						}
						break;
					case '3':
						opcao = leValidaOpcao('0','2', menu13);
						switch(opcao){
							case '1':
								cadastrarCircuito();
								break;
							case '2':
								//TODO Alterar circuito
								break;
						}
						break;
					case '4':
						opcao = leValidaOpcao('0','3', menu14);
						switch(opcao){
							case '1':
								cadastraMelhorVolta();
								break;
							case '2':
								//TODO Alterar volta
								break;
							case '3':
								//TODO Excluir volta
								break;
						}
						break;
				}
				break;
			case '2':
				opcao = leValidaOpcao('0','7', menu2);
				switch(opcao){
					case '1':
						//TODO Rel1
						opcao = leValidaOpcao('1', '5', menuRel1);
						leRelatorio1(opcao);
						break;
					case '2':
						//TODO Rel2
						//Falta ordenar alfabeticamente 
						leRelatorio2();
						break;
					case '3':
						//TODO Rel3
						opcao = leValidaOpcao('1', '2', menuRel2);
						leRelatorio3(opcao);
						break;
					case '4':
						//TODO Rel4
						//Nao ensinou Aloca��o Din�mica
						break;
					case '5':
						//TODO Rel5
						//Ordenar alfabeticamente
						
						break;
					case '6':
						//TODO Rel6 OKAY
						leRelatorio6();
						break;
					case '7':
						//TODO Rel7
						leRelatorio7();
						break;
				}
				break;
			case '0':
				encerrarPrograma = 1;
		}
	}while(!encerrarPrograma);
	return 0;
}

/* 
AN�LISE DE REQUISITOS
   1.Alterar Dados cadastrais
		1.Dados cadastrais dos pilotos
			1.Inclus�o de novo piloto
			2.Altera��o/complementa��o de dados de pilotos cadastrados
			3.Exclus�o de um piloto do cadastro	
			OBS:
				*N�o permitir recadastro de piloto existente
				*Exclus�o de piloto s� � permitida se o mesmo n�o tiver realizado nenhuma volta	
				.
		2.Dados cadastrais das equipes
			1.Inclus�o de nova equipe
			2.Exclus�o de uma equipe
			OBS:
				*N�o permitir recadastro de equipe existente (mesma sigla)
				*Exclus�o de equipe s� � permitida se a mesma n�o possuir nenhum piloto cadastrado
				.
		3.Dados cadastrais dos circuitos
			1.Inclus�o de novo circuito
			2.Altera��o/complementa��a de dados de circuito cadastrado
			OBS:
				*N�o permitir recadastro de circuito j� existente
			.
		4.Dados cadastrais das voltas
			1.Inclus�o de nova melhor volta
			2.Altera��o dos dados de uma melhor volta j� cadastrada
			3.Exclus�o de melhor volta
			OBS:
				*Exclus�o deve ser feita ap�s confirma��o do usu�rio
			.
	2.Relat�rios
		1.Consulta simples sobre todos os arquivos existentes atrav�s da sua 
			chave �nica ou apresentar todos os dados cadastrados
			.
		2.Pesquisar os pilotos registrados em seu programa pelo nome. Esta
			pesquisa ocorrer� por qualquer parte do nome do piloto. No caso de
			existirem v�rios pilotos que satisfa�am a esta parte do nome, dever� ser
			mostrada uma tabela ordenada, alfabeticamente, com os dados cadastrados
			para cada piloto (mostrar todos seus dados cadastrais de forma tabelar com
			uma �nica linha de cabe�alho, devendo as colunas serem identificadas por
			extenso)
			.
		3.Relacionar todos os pilotos que realizaram voltas em um circuito
			espec�fico fornecido pelo usu�rio, indicando todos os dados relacionados
			com a sua volta r�pida realizada neste circuito. O usu�rio poder� tamb�m
			definir, al�m do circuito, uma data v�lida e completa para fazer esta
			consulta
			.
		4.Consultar todos os circuitos cadastrados por qualquer parte de seu
			nome que ser� fornecido pelo usu�rio ou por seu c�digo (chave), onde todos
			os dados de cadastro dos circuitos dever�o ser mostrados de maneira
			tabelar, com somente uma linha de cabe�alho. Esta consulta s� poder� ser
			realizada usando recursos de aloca��o din�mica (ver esclarecimentos no
			t�pico PESQUISA-1 a seguir). Junto com os dados do circuito dever� ser
			apresentado o nome completo do piloto que obteve o menor tempo do
			circuito
			.
		5.Apresentar todos os pilotos de uma equipe em um per�odo de data
			(de... at�...) completa (dia/m�s/ano) fornecido pelo usu�rio, onde ser�
			mostrado somente o nome e c�digo do piloto, a data em que o piloto realizou
			volta por tal equipe e o nome do circuito onde isto ocorreu. A apresenta��o
			dever� estar em ordem alfab�tica de piloto
			.
		6.Pesquisar todos os pilotos, equipes e circuitos que realizaram um
			tempo de volta menor ou igual ao fornecido pelo usu�rio (minutos, segundos
			e milissegundos)
			.
		7.Exibir todos os Pilotos, Equipes ou Circuitos que n�o est�o
			cadastrados em nenhuma Melhor Volta.
			.
*/
