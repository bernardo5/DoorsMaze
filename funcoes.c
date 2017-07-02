#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "estruturas.h"
#include "funcoes.h"
#include "filasListas.h"
#include "heap.h"

/* cria e inicializa um novo no */
no *novo(int numero_no, no *proximo, int peso, indices i){
	no*new=(no*)malloc(sizeof(struct _no));
	new->numero=numero_no;
	new->prox=proximo;
	new->peso=peso;
	new->porta=i;
	new->fim =0;
	new->lampada=0;
	return new;
}

/* Inicializacao da lista de adjacencias */
void InicializaListaAdj(dados*d){
	d->listaAdjacencias=NULL;
	return;
}

/* criacao de um novo no principal na lista de adjacencias */
listaAdj* Cria_no(dados*d, int numero){
	listaAdj*novoNo=(listaAdj*)malloc(sizeof(listaAdj));
	novoNo->adj=NULL;
	novoNo->proximo=NULL;
	novoNo->numero=numero;	
	return novoNo;
}

/* insere na lista de adjacencias uma ligacao entre nos */
void InsereListaAdj(dados*d, int v, int w, int peso, indices i){
	listaAdj*noadj;
		for(noadj=d->listaAdjacencias; (noadj!=NULL)&&(noadj->numero)!=v; noadj=noadj->proximo);
			noadj->adj=novo(w, noadj->adj, peso, i);
		
		for(noadj=d->listaAdjacencias; (noadj!=NULL)&&(noadj->numero)!=w; noadj=noadj->proximo);
		noadj->adj=novo(v, noadj->adj, peso, i);
	
	return;
}

/* verifica se o no principal em questao ja consta da lista */
int VerificaNovaTinta(int tinta, dados*d){
	int b=1;
	listaAdj*aux;
	for(aux=d->listaAdjacencias; (aux!=NULL)&&((aux->numero)!=tinta); aux=aux->proximo);
	if(aux!=NULL)b=0;
	return b;
}

/* Verifica as ligacoes entre nos e actualiza a lista de adjacencias */
void verificaAdjacencias(dados*d){
	int i;
	listaAdj*noadj;
	indices indice;
	no*aux;
	indice.x=-3;
	indice.y=-3;
	for(i=0; i<d->colunas; i++){
		if((d->linha3)[i].custo==0){
			if(((d->linha2)[i].custo!=0)&&((d->linha2)[i].custo!=-1)&&
					((d->linha1)[i].custo==0)&&
					(((d->linha1)[i].tinta)!=((d->linha3)[i].tinta))){
				
				if(VerificaNovaTinta(d->linha3[i].tinta, d)){
					for(noadj=d->listaAdjacencias; (noadj!=NULL)&&((noadj->proximo)!=NULL); noadj=noadj->proximo);
					if(noadj!=NULL){
							noadj->proximo=Cria_no(d, (d->linha3)[i].tinta);
						}else{
							d->listaAdjacencias=Cria_no(d, (d->linha1)[i].tinta);
							d->listaAdjacencias->proximo=Cria_no(d, (d->linha3)[i].tinta);
					}
				
				}
				if(VerificaNovaTinta(d->linha1[i].tinta, d)){
					for(noadj=d->listaAdjacencias; (noadj->proximo)!=NULL; noadj=noadj->proximo);
					noadj->proximo=Cria_no(d, (d->linha1)[i].tinta);
				}
					
				
				for(noadj=d->listaAdjacencias; 
					(noadj->numero)!=((d->linha3)[i].tinta);
					 noadj=noadj->proximo);
				for(aux=noadj->adj; (aux!=NULL)&&
						(aux->numero!=(d->linha1)[i].tinta) ;aux=aux->prox);
				if(aux==NULL){
					InsereListaAdj(d, d->linha1[i].tinta, d->linha3[i].tinta, d->linha2[i].custo, d->linha2[i].index);
				}else{
					if((aux->peso)>(d->linha2)[i].custo){
						aux->peso=(d->linha2)[i].custo;
						aux->porta=(d->linha2)[i].index;
						for(noadj=d->listaAdjacencias; 
							(noadj->numero)!=((d->linha1)[i].tinta);
							 noadj=noadj->proximo);
						for(aux=noadj->adj; (aux!=NULL)&&
								(aux->numero!=(d->linha3)[i].tinta) ;aux=aux->prox);
						aux->peso=(d->linha2)[i].custo;
						aux->porta=(d->linha2)[i].index;
					}
				}
			}
			
			if((i+1<d->colunas)&&((d->linha3)[i+1].custo!=0)&&((d->linha3)[i+1].custo!=-1)&&
					(i+2<d->colunas)&&((d->linha3)[i+2].custo==0)&&
					(((d->linha3)[i+2].tinta)!=((d->linha3)[i].tinta))){
				
				if(VerificaNovaTinta(d->linha3[i+2].tinta, d)){
					for(noadj=d->listaAdjacencias; (noadj!=NULL)&&(noadj->proximo)!=NULL; noadj=noadj->proximo);
						if(noadj!=NULL){
							noadj->proximo=Cria_no(d, (d->linha3)[i+2].tinta);
						}else{
							d->listaAdjacencias=Cria_no(d, (d->linha3)[i].tinta);
							d->listaAdjacencias->proximo=Cria_no(d, (d->linha3)[i+2].tinta);
						}
					
				}
				if(VerificaNovaTinta(d->linha3[i].tinta, d)){
					for(noadj=d->listaAdjacencias; (noadj->proximo)!=NULL; noadj=noadj->proximo);
					noadj->proximo=Cria_no(d, (d->linha3)[i].tinta);
				}
				
				for(noadj=d->listaAdjacencias; 
					(noadj->numero)!=((d->linha3)[i].tinta);
					 noadj=noadj->proximo);
				for(aux=noadj->adj; (aux!=NULL)&&
						(aux->numero!=(d->linha3)[i+2].tinta) ;aux=aux->prox);
				if(aux==NULL){
					InsereListaAdj(d, d->linha3[i+2].tinta, d->linha3[i].tinta, d->linha3[i+1].custo, d->linha3[i+1].index);
				}else{
					if((aux->peso)>(d->linha3)[i+1].custo){
						aux->peso=(d->linha3)[i+1].custo;
						aux->porta=(d->linha3)[i+1].index;
						for(noadj=d->listaAdjacencias; 
							(noadj->numero)!=((d->linha3)[i+2].tinta);
							 noadj=noadj->proximo);
						for(aux=noadj->adj; (aux!=NULL)&&
								(aux->numero!=(d->linha3)[i].tinta) ;aux=aux->prox);
						aux->peso=(d->linha3)[i+1].custo;
						aux->porta=(d->linha3)[i+1].index;
					}
				}
			}
			if((i+1<d->colunas)&&(d->linha3[i].tinta!=d->linha3[i+1].tinta)
				&&(d->linha3[i+1].custo==0)){
					
				if(VerificaNovaTinta(d->linha3[i+1].tinta, d)){
					for(noadj=d->listaAdjacencias; (noadj!=NULL)&&((noadj->proximo)!=NULL); noadj=noadj->proximo);
					if(noadj!=NULL){
						noadj->proximo=Cria_no(d, (d->linha3)[i+1].tinta);
					}else{
						d->listaAdjacencias=Cria_no(d, (d->linha3)[i].tinta);
						d->listaAdjacencias->proximo=Cria_no(d, (d->linha3)[i+1].tinta);
					}
							
				}
				if(VerificaNovaTinta(d->linha3[i].tinta, d)){
					for(noadj=d->listaAdjacencias; (noadj->proximo)!=NULL; noadj=noadj->proximo);
					noadj->proximo=Cria_no(d, (d->linha3)[i].tinta);
				}
				
				for(noadj=d->listaAdjacencias; 
					(noadj->numero)!=((d->linha3)[i].tinta);
					 noadj=noadj->proximo);
				for(aux=noadj->adj; (aux!=NULL)&&
						(aux->numero!=(d->linha3)[i+1].tinta) ;aux=aux->prox);
				if(aux==NULL){
					InsereListaAdj(d, d->linha3[i+1].tinta, d->linha3[i].tinta, 0, indice);
				}else{
					aux->peso=0;
					aux->porta=indice;
					for(noadj=d->listaAdjacencias; 
						(noadj->numero)!=((d->linha3)[i+1].tinta);
						 noadj=noadj->proximo);
					for(aux=noadj->adj; (aux!=NULL)&&
							(aux->numero!=(d->linha3)[i].tinta) ;aux=aux->prox);
					aux->peso=0;
					aux->porta=indice;
				}
			}
		}
	}
	return;
}

/* conta o numero de nos apos ja toda a informacao ter sido tratada */
void Conta_nos(dados *d){
	int numeroNos=0;
	listaAdj*adj;
	for(adj=d->listaAdjacencias; adj!=NULL; adj=adj->proximo)numeroNos++;
	d->nos=numeroNos;
	return;
}


/* Algoritmo de Dijkstra */
void resolve(dados*d, int (*less) (int, int)){
	int nos, w;
	no*aux;
	Heap *h;
	listaAdj*noadj;
	if(d->nos>0){
		d->pai=(int*)malloc((d->nos)*sizeof(int));
		d->caminho=(int*)malloc((d->nos)*sizeof(int));
		
		h=NewHeap(d->nos, less);
		
		for(nos=0; nos<(d->nos);nos++){
			(d->pai)[nos]=-1;
			(d->caminho)[nos]=999999999; /* flag indicativa de custo infinito */	
			Direct_Insert(h, nos);			
		}
		(d->caminho)[0]=0;
				
		if(d->listaAdjacencias!=NULL){
			while(!HeapEmpty(h)){ 
				if((d->caminho)[nos=RemoveMax(h, d)]!=999999999){
					for(noadj=d->listaAdjacencias; noadj->numero!=nos+1; noadj=noadj->proximo);
					for(aux=noadj->adj; aux!=NULL; aux=aux->prox){
						if((d->caminho)[w=(aux->numero)-1]>((d->caminho)[nos]+(aux->peso))){
							(d->caminho)[w]=((d->caminho)[nos]+(aux->peso));
							Heapify(h, d);
							(d->pai)[w]=nos;
						}
					}
				}
			}
		}	
	FreeHeap(h);
	}

	return;	
}


