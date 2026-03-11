//Guilherme da Mata Garzon - NUSP 15456601
#ifndef DADOS_H
#define DADOS_H

#include <stdbool.h>

#define MAX 5000
//Header para centralizar as diferentes structs do código

//Struct do paciente
typedef struct paciente_{
    int ID;
    char nome[150];
}Paciente;

// Struct principal de cadastro geral do paciente
typedef struct cadastro_ {
    Paciente *paciente;
    struct cadastro_ *dir; //Nó direito para a árvore
    struct cadastro_ *esq; //Nó esquerdo para a árvore
    int altura; //Altura do nó na árvore

    int fila_check; //Check para ver se já está ou não na fila
}Cadastro;

// Struct para a árvore
typedef struct {
    Cadastro *raiz;
} AVL;

typedef struct espera_{
    Cadastro *aguardo;
    int prioridade;
    int chegada;
}Espera;

// Struct para o heap... A FAZER
typedef struct heap_{
    Espera *fila;
    int pos;
}Heap;

#endif 