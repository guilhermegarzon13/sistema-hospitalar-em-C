//Guilherme da Mata Garzon - NUSP 15456601
#ifndef IO_H
#define IO_H

#include "dados.h"
#include <stdbool.h>

// Salva o estado da lista de pacientes e da fila de espera em arquivos binários.
bool SAVE(Lista *lista, Fila *fila);

// Carrega o estado da lista de pacientes e da fila de espera a partir dos arquivos.
bool LOAD(Lista *lista, Fila *fila);

#endif 
