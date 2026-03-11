//Guilherme da Mata Garzon - NUSP 15456601
#ifndef DADOS_H
#define DADOS_H

#include <stdbool.h>

//Header para centralizar as diferentes structs do código

// Struct para um procedimento médico
typedef struct procedimento_ {
    char proc[100];
    struct procedimento_* back;
} procedimento;

// Struct para a pilha de histórico
typedef struct topo_ {
    procedimento* top;
    int qtd;
} Topo;

//Struct do paciente
typedef struct paciente_{
    int ID;
    char nome[150];
}Paciente;

// Struct principal de cadastro geral do paciente
typedef struct cadastro_ {
    Paciente *paciente;
    Topo *historico; 
    struct cadastro_ *back_lista; 
    struct cadastro_ *back_fila;
} Cadastro;

// Struct para a lista
typedef struct {
    Cadastro *primeiro;
    Cadastro *ultimo;
    int qtd;
} Lista;

// Struct para a fila 
typedef struct {
    Cadastro *primeiro;
    Cadastro *ultimo;
    int qtd;
} Fila;

#endif 