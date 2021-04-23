#include <stdio.h>

void iniciarJogo();

void imprimirTabuleiro(char tabuleiro[][3]);

void preencherTabuleiro(int i, int j, int jogadorVez, char tabuleiro[][3]);

void realizarJogada(char tabuleiro[][3]);

int verificarVitoria(char tabuleiro[][3]);

int imprimirVitoria(int vencedor);

int verificarJogada(int opcao, char tabuleiro[][3]);

void jogadaBOT(char tabuleiro[][3], int jogadorVez);

int minimax(char tabuleiro[][3], int altura, int maximizando);

int min(int a, int b);

int max(int a, int b);

void trocarJogador(int *jogador);

int verificarPosicaoVazia(char tabuleiro[][3], int i, int j); 

int verificarTabuleiroCheio(char tabuleiro[][3]);