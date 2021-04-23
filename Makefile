all:
	gcc -o jogo_da_velha jogoDaVelha.c
	./jogo_da_velha
clean:
	rm jogo_da_velha