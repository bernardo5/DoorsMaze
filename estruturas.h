#ifndef ESTRUTURAS_H_INCLUDED
#define ESTRUTURAS_H_INCLUDED

typedef struct _indices{
	int x; /* linhas na matriz */
	int y; /* colunas na matriz */
}indices;

typedef struct _celula{
	indices index;
	int custo;
	int tinta;
	struct _celula*prox;
}celula;

typedef struct _no{
	int numero;
	int peso;
	indices porta;
	int lampada;
	int fim;
	struct _no*prox;
}no;

typedef struct _listaAdj{
	int numero;
	no*adj;
	struct _listaAdj*proximo;
}listaAdj;

typedef struct _dados{
	celula*linha1;
	celula*linha2;
	celula*linha3;
	int n_portas;
	indices ponto_chegada;
	int linhas;
	int colunas;
	int nos;
	int noChegada;
	listaAdj*listaAdjacencias;
	int*pai;
	int*caminho;
}dados;

#endif 
