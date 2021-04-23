#include "jogoDaVelha.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

int main(){
	
	iniciarJogo();

	return 0;

}

void iniciarJogo(){

	char tabuleiro[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int jogadorVez = 1, numRodadas = 0, vencedor;

	system("clear");

	do {
		
		imprimirTabuleiro(tabuleiro);

		if(jogadorVez == 1){

			jogadaBOT(tabuleiro, 1);
			sleep(1.5);

		}

		else
			realizarJogada(tabuleiro);

		vencedor = verificarVitoria(tabuleiro);

		trocarJogador(&jogadorVez);

		numRodadas++;

		system("clear");

	} while(vencedor == 0 && numRodadas < 9);

	imprimirTabuleiro(tabuleiro);

	if(vencedor == 0)
		printf("\nO jogo deu empate\n");

	else
		imprimirVitoria(vencedor);
		
}

void imprimirTabuleiro(char tabuleiro[][3]){

	printf("\n\t  \033[0;31mJOGO DA VELHA\n\n\033[0;32m"
		  "Minimax tree BOT: X\nVoce: O\n\n\t\033[0;33m"
		  "  \033[0;31m%c\033[0;33m  |  \033[0;31m%c\033[0;33m  |  \033[0;31m%c\033[0;33m   \n"
		  "\t-----|-----|-----\n\t"
		  "  \033[0;31m%c\033[0;33m  |  \033[0;31m%c\033[0;33m  |  \033[0;31m%c\033[0;33m   \n"
		  "\t-----|-----|-----\n\t"
		  "  \033[0;31m%c\033[0;33m  |  \033[0;31m%c\033[0;33m  |  \033[0;31m%c\033[0;33m   \n",
		  tabuleiro[0][0], tabuleiro[0][1], tabuleiro[0][2],
		  tabuleiro[1][0], tabuleiro[1][1], tabuleiro[1][2],
		  tabuleiro[2][0], tabuleiro[2][1], tabuleiro[2][2]);
	
}

void preencherTabuleiro(int i, int j, int jogadorVez, char tabuleiro[][3]){

	if(jogadorVez == 1)
		tabuleiro[i][j] = 'X';

	else
		tabuleiro[i][j] = 'O';

}

void realizarJogada(char tabuleiro[][3]){

	int opcao, opcaoValida;

	printf("\nSua vez: ");
	scanf("%d", &opcao);

	opcaoValida = verificarJogada(opcao, tabuleiro);

	if(!opcaoValida)
		realizarJogada(tabuleiro);

	else {
		if (opcao / 4 == 0)
			preencherTabuleiro(0, opcao - 1, 2, tabuleiro);
		else if (opcao / 7 == 0)
			preencherTabuleiro(1, opcao - 4, 2, tabuleiro);
		else if(opcao / 10 == 0)
			preencherTabuleiro(2, opcao - 7, 2, tabuleiro);
	}

}

int verificarVitoria(char tabuleiro[][3]){

	for(int i = 0; i < 3; i++)
		if(tabuleiro[i][0] == 'X' && tabuleiro[i][1] == 'X' && tabuleiro[i][2] == 'X')
			return 1;

	for(int i = 0; i < 3; i++)
		if(tabuleiro[0][i] == 'X' && tabuleiro[1][i] == 'X' && tabuleiro[2][i] == 'X')
			return 1;

	if(tabuleiro[0][0] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][2]== 'X')
		return 1;

	if(tabuleiro[0][2] == 'X' && tabuleiro[1][1] == 'X' && tabuleiro[2][0]== 'X')
		return 1;

	for(int i = 0; i < 3; i++)
		if(tabuleiro[i][0] == 'O' && tabuleiro[i][1] == 'O' && tabuleiro[i][2] == 'O')
			return -1;

	for(int i = 0; i < 3; i++)
		if(tabuleiro[0][i] == 'O' && tabuleiro[1][i] == 'O' && tabuleiro[2][i] == 'O')
			return -1;

	if(tabuleiro[0][0] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][2]== 'O')
		return -1;

	if(tabuleiro[0][2] == 'O' && tabuleiro[1][1] == 'O' && tabuleiro[2][0]== 'O')
		return -1;

	return 0;

}

int imprimirVitoria(int vencedor){

	vencedor == -1 ? printf("\nParabens, voce fez o impossivel\n") : printf("\nVencedor: Minimax tree BOT\n");

}

int verificarJogada(int opcao, char tabuleiro[][3]){

	int opcaoValida = 0;

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(opcao == tabuleiro[i][j] - '0')
				opcaoValida++;

	
	if(!opcaoValida){
		printf("\nOPCAO INVALIDA...");
		getchar();
	}
		
	return opcaoValida;

}

void jogadaBOT(char tabuleiro[][3], int jogadorVez){

	int resultado, melhorResultado, melhorI, melhorJ;

	melhorResultado = INT_MIN;

	for(int i = 0; i < 3; i++){

		for(int j = 0; j < 3; j++){

			if(verificarPosicaoVazia(tabuleiro, i, j)){

				char aux = tabuleiro[i][j];
				preencherTabuleiro(i, j, 1, tabuleiro);
				resultado = minimax(tabuleiro, 0, 0);
				tabuleiro[i][j] = aux;

				if(resultado > melhorResultado){

					melhorResultado = resultado;
					melhorI = i;
					melhorJ = j;

				}

			}

		}

	}

	preencherTabuleiro(melhorI, melhorJ, 1, tabuleiro);
		
}

int minimax(char tabuleiro[][3], int altura, int maximizando){

	int resultado = verificarVitoria(tabuleiro);
	
	if(resultado != 0)
		return resultado;

	if(verificarTabuleiroCheio(tabuleiro))
		return 0;

	if(maximizando){

		int melhorResultado = INT_MIN;

		for(int i = 0; i < 3; i++){
			
			for(int j = 0; j < 3; j++){
				
				if(verificarPosicaoVazia(tabuleiro, i, j)){

					char aux = tabuleiro[i][j];
					preencherTabuleiro(i, j, 1, tabuleiro);
					resultado = minimax(tabuleiro, altura + 1, 0);
					tabuleiro[i][j] = aux;
					melhorResultado = max(resultado, melhorResultado);
						
				}

			}

		}

		return melhorResultado;

	}

	else {

		int melhorResultado = INT_MAX;

		for(int i = 0; i < 3; i++){
			
			for(int j = 0; j < 3; j++){
				
				if(verificarPosicaoVazia(tabuleiro, i, j)){

					char aux = tabuleiro[i][j];
					preencherTabuleiro(i, j, 2, tabuleiro);
					resultado = minimax(tabuleiro, altura + 1, 1);
					tabuleiro[i][j] = aux;
					melhorResultado = min(resultado, melhorResultado);
						
				}

			}

		}

		return melhorResultado;

	}

}

int min(int a, int b){

	if(a > b)
		return b;

	return a;

}

int max(int a, int b){

	if(a > b)
		return a;

	return b;

}

void trocarJogador(int *jogador){

	if((*jogador) == 1)
		(*jogador) = 2;

	else
		(*jogador) = 1;

}

int verificarPosicaoVazia(char tabuleiro[][3], int i, int j){

	return tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O';	

}

int verificarTabuleiroCheio(char tabuleiro[][3]){

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(verificarPosicaoVazia(tabuleiro, i, j))
				return 0;

	return 1;

}