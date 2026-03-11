//Guilherme da Mata Garzon - NUSP 15456601
#ifndef AVL_H
#define AVL_H

#include "dados.h"
#include <stdbool.h>

void init_AVL(AVL *T);
void destroy_arvore(AVL *T);

bool busca_AVL(AVL *T, int id);
Cadastro *get_AVL(AVL *T, int id);
void AVL_inserir(AVL *T, Cadastro *insere);
void remover_AVL(AVL *T, int id);
void print_AVL(AVL *T);

#endif
