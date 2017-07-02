#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "filasListas.h"
#include "ficheiro.h"

/* Inicializacao das linhas para o tratamento da informacao
 * do tabuleiro */
void InicializaLinha1(dados*d, int custo, int linha_mat){
	int i;
	for(i=0; i<d->colunas; i++){
		d->linha1[i].index.x=linha_mat;
		d->linha1[i].index.y=i+1;
		d->linha1[i].custo=custo;
		d->linha1[i].tinta=0;
	}
	return;
}

void InicializaLinha2(dados*d, int custo, int linha_mat){
	int i;
	for(i=0; i<d->colunas; i++){
		d->linha2[i].index.x=linha_mat;
		d->linha2[i].index.y=i+1;
		d->linha2[i].custo=custo;
		d->linha2[i].tinta=0;
	}
	return;
}
void InicializaLinha3(dados*d, int custo, int linha_mat){
	int i;
	for(i=0; i<d->colunas; i++){
		d->linha3[i].index.x=linha_mat;
		d->linha3[i].index.y=i+1;
		d->linha3[i].custo=custo;
		d->linha3[i].tinta=0;
	}
	return;
}
/* ****************************************************************** */

/* Alocacao do espaco de memoria para as linhas  */
void Aloca_3linhas(dados*d, int colunas, int linha_mat){
	d->linha1=(celula*)malloc(colunas*sizeof(celula));
	d->linha2=(celula*)malloc(colunas*sizeof(celula));
	d->linha3=(celula*)malloc(colunas*sizeof(celula));	
	return;
}

/* Colocacao na linha 3 as informacoes da celula lida do ficheiro */
void InsereCelula(dados*d, int*x, int*y, int *custo){
	d->linha3[(*y)-1].custo=(*custo);
	d->linha3[(*y)-1].index.x=(*x);
	d->linha3[(*y)-1].index.y=(*y);
	d->linha3[(*y)-1].tinta=0;
	return;
}

/* insere todas as portas do ficheiro que pertencem a linha a analisar */
void Insere3linha(dados*d, int* linha_matriz, FILE*fp, int*x, int*y, int *custo){	
		if((*linha_matriz)==(*x)){ /* se a ultima celula lida pertencer a linha */
			InsereCelula(d, x, y, custo);
			while((lePorta(fp, x, y, custo)==3)&&((*linha_matriz)==(*x))){
				InsereCelula(d, x, y, custo);
			} /* leitura e insercao das portas da linha */
		}	/* caso contrario sabe se que a linha e branca
			 uma vez que o ficheiro esta ordenado*/		
	return;
}

/* suprime linhas brancas caso haja duas ou mais seguidas */
void CompactaLinhasBrancas(dados*d, int *linhas_mat, int x){
	if((x-(*linhas_mat))>=2){
		if(((d->ponto_chegada.x)>(*linhas_mat))&&((d->ponto_chegada.x)<x)){
				(*linhas_mat)=(d->ponto_chegada.x)-1;
			}else{
				(*linhas_mat)=x-2;
			}
	}else{
		if((x<(*linhas_mat))&&((*linhas_mat)!=(d->linhas))){
			if(((d->ponto_chegada.x)>(*linhas_mat))&&((d->ponto_chegada.x)<(d->linhas))){
				(*linhas_mat)=(d->ponto_chegada.x)-1;
			}else{
				(*linhas_mat)=(d->linhas)-1;
			}
		}
	}
	return;
}

/* troca de ponteiros para a insercao posterior de uma nova linha */
void InsereLinha(dados*d, int linha_matriz){
	celula*aux;
	/* troca dos ponteiros */
	aux=d->linha1;
	d->linha1=d->linha2;
	d->linha2=d->linha3;
	d->linha3=aux;
	
	InicializaLinha3(d, 0, linha_matriz);				
	
	return;
}

/* pinta as varias regioes de forma a identificar os nos do grafo */
void pinta3linha(dados*d, int *Tinta, int linha_mat){
	int i, tinta;
	
	for(i=0; i<d->colunas; i++){
		if(((d->linha3)[i].custo==0)){
			if((d->linha2)[i].custo==0){
				tinta=(d->linha2)[i].tinta;
				(d->linha3)[i].tinta=tinta;
			}else{
				if((i-1>=0)&&(((d->linha3)[i-1].tinta!=0))){
						tinta=(d->linha3)[i-1].tinta;
						(d->linha3)[i].tinta=tinta;	
				}else{ /* presença de um novo no */
					(*Tinta)++;
					(d->linha3)[i].tinta=(*Tinta);	
				}	
			}
		}
		if(((i+1)==d->ponto_chegada.y)&&(linha_mat==d->ponto_chegada.x))
			d->noChegada=d->linha3[i].tinta;
	}		
	return;
}

/* funcoes de libertacao da memoria alocada */
void free_linhas(dados*d){
	free(d->linha1);
	free(d->linha2);
	free(d->linha3);
	return;
}

void free_listaadjacencias(dados*d){
	listaAdj*principal, *aux;
	no*auxiliar1, *auxiliar2;
	for(principal=d->listaAdjacencias; principal!=NULL; principal=principal->proximo){
		auxiliar1=principal->adj;
		while(auxiliar1!=NULL){
			auxiliar2=auxiliar1->prox;
			free(auxiliar1);
			auxiliar1=auxiliar2;
		}
	}
	principal=d->listaAdjacencias;
	while(principal!=NULL){
			aux=principal->proximo;
			free(principal);
			principal=aux;
	}	
	return;
}
