//Guilherme da Mata Garzon - NUSP 15456601
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"dados.h"
#include"triagem.h"

//Pre cond: Recebe um ponteiro fila ainda não alocado
//Pos cond:Faz os ponteiros primeiro e ultimo apontarem pra NULL
void init_fila(Fila *f){
    f->primeiro = NULL;
    f->ultimo = NULL;
    f->qtd = 0;
}

//Pre cond:Recebe a fila e um paciente
//Pos cond: Coloca o novo paciente na última posição da fila
void adiciona_fila(Fila *f, Cadastro *k){
    k->back_fila = NULL;
    int check = buscar_fila(f,k->paciente->ID);
    if(check == 1){
      printf("Paciente já está na fila\n");
      return;
    }
    else{
    if(f->primeiro == NULL || f->ultimo == NULL){
        f->primeiro = k;
        f->ultimo = k;
        f->qtd++;
    }
    else{
        f->ultimo->back_fila = k;
        f->ultimo = k;
        f->qtd++;
    }
}
}
//Pre cond: Fila não vazia
//Pos cond: Checa se o paciente já está na fila ou não
bool buscar_fila(Fila *f, int ID){
    Cadastro *aux = f->primeiro;
    while(aux != NULL){
        if(aux->paciente->ID == ID){
            return true;
        }
        aux = aux->back_fila;
    }
    return false;
}

//Pre cond: Recebe o começo da fila
//Pos cond: Exibe o primeiro paciente e tira ele da fila, dando lugar ao próximo
void chamada(Fila *f){
    if(f->primeiro == NULL){
        printf("A fila está vazia");
        return;
    }

    Cadastro *chamado = f->primeiro;
    printf("Paciente chamado: %s (ID: %d)\n", chamado->paciente->nome, chamado->paciente->ID);

    // Remove o paciente da fila, mas NÃO libera a memória
    f->primeiro = f->primeiro->back_fila;
    if(f->primeiro == NULL){
        f->ultimo = NULL;
    }
    f->qtd--;
}

//Pre cond: Recebe o primeiro elemento da fila
//Pos cond: Mostra o tamanho da fila
void tamanho_fila(Fila *f){
    printf("O tamanho da fila é %d\n", f->qtd);
}

//Pre cond: Recebe o início da fila
//Pos cond: Mostra a fila toda. Se ela estiver vazia, avisa
void mostrar_fila(Fila *f){
    Cadastro *aux = f->primeiro;
    if(f->primeiro == NULL){
        printf("A fila está vazia\n");
    }
    while(aux != NULL){
        printf("%s (ID: %d)\n", aux->paciente->nome, aux->paciente->ID);
        aux = aux->back_fila;
    }
}