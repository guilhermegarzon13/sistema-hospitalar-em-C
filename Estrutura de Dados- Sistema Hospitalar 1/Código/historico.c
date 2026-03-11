//Guilherme da Mata Garzon - NUSP 15456601
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include<string.h>
#include "dados.h"
#include "historico.h"

//Pre cond: Recebe o topo da pilha nao iniciado
//Pos cond: Inicia o topo da pilha
void init_pilha(Topo* p) {
    p->top = NULL;
    p->qtd = 0;
}

//Pre cond: Recebe o topo da pilha
//Pos cond: Após o usuário digitar o procedimento, adiciona ele na pilha
void adiciona_pilha(Topo* p) {
    procedimento* aux = (procedimento*)malloc(sizeof(procedimento));
    if (aux == NULL) {
        return;
    }
    if(p->qtd >= 10){
        printf("O histórico está cheio, remova o último procedimento se quiser prosseguir!\n");
        return;
    }
    printf("Digite o procedimento:\n");
    while(getchar() != '\n');
    fgets(aux->proc, 100, stdin);
    aux->back = p->top;
    p->top = aux;
    p->qtd++;
}

//Pre cond: Recebe o topo da pilha
//Pos cond: Print o topo da pilha e remove ele do front, dando lugar ao seu back
void pop_pilha(Topo* p) {
   if (p->top == NULL) {
    printf("Não há procedimentos pendentes\n");
} else {
    procedimento *aux = p->top;
    char *valor = aux->proc;
    p->top = aux->back;
    p->qtd--;

    printf("%s\n", valor);

    free(aux);
}

}

//Pre cond: Recebe o topo da pilha
//Pos cond: Apaga a pilha e não printa nada
void destroy_pilha(Topo *p) {
    procedimento *temp;
    while (p->top != NULL) {
        temp = p->top;
        p->top = temp->back;
        free(temp);
    }
    p->qtd = 0;
}

//Pre cond: Recebe o topo da pilha
//Pos cond: Se a pilha tiver 10 procedimentos printa que ela está cheia
//Se tiver 0, fala que está vazia
//Caso contrário, fala quantos procedimentos estão no histórico
void size(Topo *p) {
    if(p->qtd >= 10){
        printf("O histórico está cheio, já ocupando os 10 espaços \n");
        return;
    }
    else if(p->qtd == 0){
        printf("O histórico está vazio. \n");
        return;
    }
    else{
        printf("O histórico tem %d procedimentos \n", p->qtd);
    }
}
//Pre cond: Recebe o topo da pilha
//Pos cond: Mostra o histórico completo
//Se ele estiver vazio é avisado
void print_historico(Topo *p){
    int i;
    procedimento *aux = p->top;
    if(p->qtd == 0){
        printf("O histórico está vazio\n");
    }
    else{
        for(i = 0; i< p->qtd;i++){
            fputs(aux->proc, stdout);
            fputs("\n", stdout);
            aux = aux->back;
        }
    }

}