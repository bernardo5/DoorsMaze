#ifndef FUNCOES_H_INCLUDED
#define FUNCOES_H_INCLUDED

no *novo(int numero_no, no *proximo, int peso, indices i);

void InicializaListaAdj(dados*d);

listaAdj* Cria_no(dados*d, int numero);

void InsereListaAdj(dados*d, int v, int w, int peso, indices i);

int VerificaNovaTinta(int tinta, dados*d);

void verificaAdjacencias(dados*d);

void Conta_nos(dados *d);

void resolve(dados*d, int (*less) (int, int));

#endif
