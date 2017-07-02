#ifndef FICHEIRO_H_INCLUDED
#define FICHEIRO_H_INCLUDED

void ArmazenaInfoMatriz(FILE*fp, dados*d);

int lePorta(FILE*fp, int*x, int*y, int *custo);

void subImprime(FILE*fp, int i, dados *d);

void EscreveFicheiro(dados*d, char *ficheiro);

#endif
