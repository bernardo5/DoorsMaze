#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "ficheiro.h"

/* retira as informacoes necessarias ao tratamento do problema
* e coloca as na estrutura de dados maze */
void ArmazenaInfoMatriz(FILE*fp, dados*d){
	fscanf( fp, "%d %d", &d->linhas, &d->colunas); 
	fscanf( fp, "%d %d", &(d->ponto_chegada.x), &(d->ponto_chegada.y));
	fscanf( fp, "%d", &(d->n_portas));
	return;
}

/* Armazena a informacao de uma porta */
int lePorta(FILE*fp, int*x, int*y, int *custo){
	return fscanf( fp, "%d %d %d", &(*x), &(*y), &(*custo));
}

/* funcao recursiva auxiliar que permite imprimir as portas correspondentes
 * a solucao pela ordem correcta */
void subImprime(FILE*fp, int i, dados *d){
	no*aux;
	listaAdj*noadj;
	int a;
	int i_aux=i;
	
		a=d->noChegada-1;
		while(i_aux>0){
			for(noadj=d->listaAdjacencias; 
				noadj->numero-1!=a; 
				noadj=noadj->proximo); 
			
			for(aux=noadj->adj; 
				(aux->numero-1)!=(d->pai)[a];
					aux=aux->prox); 
			a=aux->numero-1;
			i_aux--;
		}
		if(aux->peso>0){
			fprintf(fp, "%d %d %d\n", aux->porta.x,aux->porta.y, aux->peso);
		}
		if((i-1)>0){ /* chamada recursiva da funcao */
			subImprime(fp, i-1, d);
		}	
	return;
}

void EscreveFicheiro(dados*d, char *ficheiro){
  FILE *fp;
  char *nome;
  no*aux;
  int a;
  int i=0;
  listaAdj*noadj;

  nome = (char *) malloc((strlen(ficheiro)-3 + strlen(".sol") + 1)
                         * sizeof(char));
  if (nome == NULL) {
    fprintf(stderr,
            "ERROR: allocation of output filename. Not enough memory.\n");
    exit(2);
  }
  strtok(ficheiro, ".in"); 
  strcpy(nome, ficheiro);
  strcat(nome, ".sol");

  fp = fopen(nome, "w");
   
	if(d->listaAdjacencias!=NULL){
		if(d->noChegada!=1){
			
			/* deteccao se o no do ponto de chegada se encontra na lista */
			for(noadj=d->listaAdjacencias;(noadj!=NULL)&&
				((noadj->numero)!=(d->noChegada)); noadj=noadj->proximo);
			if(noadj!=NULL){
				fprintf(fp, "%d\n", (d->caminho)[d->noChegada-1]);
				a=d->noChegada-1;
				
				/* Contagem do numero de passos a dar de forma a transmitir
				 * a informacao a rotina subimprime */
				while((d->pai)[a]!=-1){
					for(noadj=d->listaAdjacencias; noadj->numero-1!=a; noadj=noadj->proximo);
					for(aux=noadj->adj; (aux->numero-1)!=(d->pai)[a];aux=aux->prox);
					i++;
					a=aux->numero-1;
				}
				subImprime(fp, i, d);
			}else{
				fprintf(fp, "%d\n", -1);
			}
		}else{
			fprintf(fp, "%d\n", 0);
		}
	}else{ /*nao existe caminho ou o caminho e sem custo*/
		if(d->noChegada==1){/*tem a mesma tinta do ponto de partida*/
			fprintf(fp, "%d\n", 0);
		}else fprintf(fp, "%d\n", -1); /*nos diferentes e sem caminho*/
	}
  fclose(fp);

  free(nome);

  return;
}
