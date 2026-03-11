//Guilherme da Mata Garzon - NUSP 15456601
#ifndef LISTA_H
#define LISTA_H
#include"dados.h"

void init_lista(Lista *l);
Cadastro *adiciona_lista(Lista *l);
int obito_lista(Lista *l,Fila *f, int ID);
Cadastro *get_paciente(Lista *l, int ID);
void mostrar_lista(Lista *l);
void destroy_lista(Lista *l);

#endif