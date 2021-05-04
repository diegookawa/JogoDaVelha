all:
	gcc -o jogo_da_velha jogoDaVelha.c
	./jogo_da_velha

test1:
	gcc -o jogo_da_velha jogoDaVelha.c
	./jogo_da_velha < ./tests/test1.txt

test2:
	gcc -o jogo_da_velha jogoDaVelha.c
	./jogo_da_velha < ./tests/test2.txt
	
test3:
	gcc -o jogo_da_velha jogoDaVelha.c
	./jogo_da_velha < ./tests/test3.txt

clean:
	rm jogo_da_velha