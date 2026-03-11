//Guilherme da Mata Garzon - NUSP 15456601
#ifndef TRIAGEM_H
#define TRIAGEM_H

void init_fila(Fila *f);
void adiciona_fila(Fila *f, Cadastro *k);
void chamada(Fila *f);
bool buscar_fila(Fila *f, int ID);
void tamanho_fila(Fila *f);
void mostrar_fila(Fila *f);

#endif 