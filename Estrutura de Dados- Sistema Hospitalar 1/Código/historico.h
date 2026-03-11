//Guilherme da Mata Garzon - NUSP 15456601
#ifndef HISTORICO_H
#define HISTORICO_H
#include"dados.h"

void init_pilha(Topo* p);
void adiciona_pilha(Topo* p);
void pop_pilha(Topo* p);
void destroy_pilha(Topo* p);
void size(Topo *p);
void print_historico(Topo *p);

#endif