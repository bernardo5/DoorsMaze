#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "funcoes.h"
#include "filasListas.h"
#include "ficheiro.h"
#include "heap.h"


int main(int argc, char**argv){
	dados maze;
	char * ficheiroIn;
	int linhas_mat=1, Tinta=0;
	FILE*fp;
	int x, y, custo;
	/*maze.contador=0;*/
	if(argc<2){
		printf("numero de argumentos invalido\n");
		exit(-1);
	}
	ficheiroIn = argv[1];
	fp = fopen( ficheiroIn , "r");
	if ( fp == NULL ) {
		fprintf ( stderr, "ERRO! nao e possivel abrir o ficheiro: %s!\n", ficheiroIn);
		exit ( 1 );
    }
    ArmazenaInfoMatriz(fp, &maze);
    InicializaListaAdj(&maze);
    if(maze.n_portas!=0){
		lePorta(fp, &x, &y, &custo);
		CompactaLinhasBrancas(&maze, &linhas_mat, x);
		Aloca_3linhas(&maze, maze.colunas, 1);
		InicializaLinha1(&maze, -1, linhas_mat);
		InicializaLinha2(&maze,-1, linhas_mat);
		InicializaLinha3(&maze, 0, linhas_mat);
		while(linhas_mat<=maze.linhas){
			Insere3linha(&maze, &linhas_mat, fp, &x, &y, &custo);
			pinta3linha(&maze, &Tinta, linhas_mat);	
			CompactaLinhasBrancas(&maze, &linhas_mat, x);
			verificaAdjacencias(&maze);
			linhas_mat++;
			InsereLinha(&maze, linhas_mat);		
		}
		Conta_nos(&maze);
		resolve(&maze, LessNum);
		fclose(fp);
		EscreveFicheiro(&maze, ficheiroIn);
		free_linhas(&maze);
		free_listaadjacencias(&maze);
		if(maze.nos>0){
			free(maze.pai);
			free(maze.caminho);
		}
	}else{
		fclose(fp);
		maze.noChegada=1;
		EscreveFicheiro(&maze, ficheiroIn);
	}
exit(0);	
}
