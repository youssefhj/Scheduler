sa.exe : sa.o algo.o
	gcc sa.o algo.o -o sa.exe
	
sa.o 	 : sa.c
	gcc -c sa.c
	
algo.o 	 : algo.c algo.h
	gcc -c algo.c
