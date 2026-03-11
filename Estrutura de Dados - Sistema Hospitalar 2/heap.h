//Guilherme da Mata Garzon - NUSP 15456601
#include"dados.h"
#ifndef HEAP_H
#define HEAP_H

void init_heap(Heap *h);
void insere_heap(Heap *h, Cadastro *k, int *Prio);
void chamada(Heap *h);
void mostrar_heap(Heap *h);
void salvar_esvaziar_heap(Heap *h, FILE *arq);
#endif
