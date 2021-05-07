#include "jogoDaVelha.h"
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>

/*	Função Principal
 *	Executa a função Iniciar
 */
int main(){
	
	iniciarJogo();
	
	return 0;

}

/*	Função Iniciar
 *	Inicia o processo do Jogo
 *	Efetua todo o processo de looping, até o jogo ser terminado.
 */
void iniciarJogo(){

	char tabuleiro[3][3] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int jogadorVez = 1, numRodadas = 0, vencedor;

	/*	Limpa a linha de comando onde será mostrada a matriz do Jogo	*/
	system("clear");
	
	/* Efetua o looping até que um vencedor exista ou um empate */
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
	/* Imprime o tabuleiro final */
	imprimirTabuleiro(tabuleiro);

	/* Caso não haja vencedor declara o empate, se não parabeniza o vencedor */
	if(vencedor == 0)
		printf("\nO jogo deu empate\n");

	else
		imprimirVitoria(vencedor);
		
}

/*	Função Imprimir
 *	Efetua a impressão da matriz do Jogo	
 */
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

/*	Função Preencher
 *	Preenche a matriz de acordo com qual jogador efetuou a jogada
 */
void preencherTabuleiro(int i, int j, int jogadorVez, char tabuleiro[][3]){

	if(jogadorVez == 1)
		tabuleiro[i][j] = 'X';

	else
		tabuleiro[i][j] = 'O';

}

/*	Função Realizar Jogada
 *	Efetua a jogada de acordo com qual jogador, verificando a disponibilidade da posição selecionada
 */
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

/*	Função Verificar Vitória
 *	Efetua verificação das possibilidades de vitória e retorna o vencedor
 *	retorna -1 para 'O' e 1 para 'X'	
 */
int verificarVitoria(char tabuleiro[][3]){
	
	for(int i = 0; i < 3; i++){
		if(tabuleiro[i][0] == tabuleiro[i][1] && tabuleiro[i][1]  == tabuleiro[i][2])
			return tabuleiro[i][0] == 'X' ? 1 : -1;
		if(tabuleiro[0][i] == tabuleiro[1][i] && tabuleiro[1][i]  == tabuleiro[2][i])
			return tabuleiro[0][i] == 'X' ? 1 : -1;
	}
	if(tabuleiro[0][0] == tabuleiro[1][1] && tabuleiro[1][1]  == tabuleiro[2][2] ||
	   tabuleiro[0][2] == tabuleiro[1][1] && tabuleiro[1][1]  == tabuleiro[2][0])
			return tabuleiro[1][1] == 'X' ? 1 : -1;
	return 0;

}

/*	Função Imprimir Vitória
 *	Imprime a mensagem para o jogador vitorioso
 */
void imprimirVitoria(int vencedor){
	vencedor == -1 ? printf("\nParabens, voce fez o impossivel\n") : printf("\nVencedor: Minimax tree BOT\n");
}

/*	Função Verificar Jogada
 *	Verifica se a jogada é valida, caso não pede novamente ao jogador para que faça a jogada
 */
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

/*	Função Jogada Bot
 *	Efetua a jogada do BOT enquanto chama a função Minimax para calcular a jogada
 */
void jogadaBOT(char tabuleiro[][3], int jogadorVez){

	int resultado, melhorResultado, melhorI, melhorJ;

	melhorResultado = INT_MIN;

	for(int i = 0; i < 3; i++){

		for(int j = 0; j < 3; j++){

			if(verificarPosicaoVazia(tabuleiro, i, j)){

				char aux = tabuleiro[i][j];
				preencherTabuleiro(i, j, 1, tabuleiro);
				resultado = minimax(tabuleiro, 0);
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
/*	Função Minimax
 *	Efetua o calculo da melhor jogada possível
 *	Retorna a melhor posição
 */
int minimax(char tabuleiro[][3], int maximizando){

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
					resultado = minimax(tabuleiro, 0);
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
					resultado = minimax(tabuleiro, 1);
					tabuleiro[i][j] = aux;
					melhorResultado = min(resultado, melhorResultado);
						
				}

			}

		}

		return melhorResultado;

	}

}

/*	Função Min
 *	Retorna o menor entre dois inteiros
 */
int min(int a, int b){

	if(a > b)
		return b;

	return a;

}

/*	Função Max
 *	Retorna o maior entre dois inteiros
 */
int max(int a, int b){

	if(a > b)
		return a;

	return b;

}

/*	Função Trocar Jogador
 *	Troca qual jogador está ativo
 */
void trocarJogador(int *jogador){

	if((*jogador) == 1)
		(*jogador) = 2;

	else
		(*jogador) = 1;

}

/*	Função Verificar Posição Vazia
 *	Retorna 0 caso esteja vazia e 1 caso não
 */
int verificarPosicaoVazia(char tabuleiro[][3], int i, int j){

	return tabuleiro[i][j] != 'X' && tabuleiro[i][j] != 'O';	

}

/*	Função Verificar Tabuleiro Cheio
 *	Retorna 0 caso esteja cheio e 1 caso não
 */
int verificarTabuleiroCheio(char tabuleiro[][3]){

	for(int i = 0; i < 3; i++)
		for(int j = 0; j < 3; j++)
			if(verificarPosicaoVazia(tabuleiro, i, j))
				return 0;

	return 1;

}