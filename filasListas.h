#ifndef FILASLISTAS_H_INCLUDED
#define FILASLISTAS_H_INCLUDED

void InicializaLinha1(dados*d, int custo, int linha_mat);

void InicializaLinha2(dados*d, int custo, int linha_mat);

void InicializaLinha3(dados*d, int custo, int linha_mat);

void Aloca_3linhas(dados*d, int colunas, int linha_mat);

void InsereCelula(dados*d, int*x, int*y, int *custo);

void Insere3linha(dados*d, int *linha_matriz, FILE*fp, int*x, int*y, int *custo);

void CompactaLinhasBrancas(dados*d, int *linhas_mat, int x);

void InsereLinha(dados*d, int linha_matriz);

void pinta3linha(dados*d, int *Tinta, int linha_mat);

void free_linhas(dados*d);

void free_listaadjacencias(dados*d);

#endif
