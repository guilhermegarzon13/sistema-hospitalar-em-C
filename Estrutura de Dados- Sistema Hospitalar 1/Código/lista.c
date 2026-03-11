//Guilherme da Mata Garzon - NUSP 15456601
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>
#include"dados.h"
#include"historico.h"
#include"triagem.h"
#include"lista.h"

//Pre cond: Recebe uma lista já alocada
//Pos cond: Faz suas componentes apontarem para o NULL e sua quantidade ser igual a zero
void init_lista(Lista *l){
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->qtd = 0;
}

//Pre cond: Recebe a lista
//Pos cond: Coloca um paciente no final da lista(não ordenada)
Cadastro *adiciona_lista(Lista *l){
    Cadastro *k = (Cadastro*)malloc(sizeof(Cadastro));
    k->back_lista = NULL;
    k->paciente = (Paciente*)malloc(sizeof(Paciente));
    printf("Digite o ID do paciente:\n ");
    scanf("%d",&k->paciente->ID);
    Cadastro *check = get_paciente(l,k->paciente->ID);
    if(check != NULL){
        free(k->paciente);
        free(k);
        printf("Paciente já consta no sistema, adicionando ele na fila...");
        return check;
    }
    else{
    printf("Paciente ainda não possui cadastro! Inserir seu nome para prosseguir:\n");
    while(getchar() != '\n'); 
    fgets(k->paciente->nome, 150, stdin);
    k->historico = (Topo*)malloc(sizeof(Topo));
    init_pilha(k->historico);
    if(l->primeiro == NULL){
        l->primeiro = k;
        l->ultimo = k;
    } else {
        l->ultimo->back_lista = k;
        l->ultimo = k;
    }
    l->qtd++;
    return k;
}
}

//Pre cond: Recebe a lista e o Id do paciente falecido
//Pos cond: Apaga o paciente do sistema(da lista) ou avisa que o sistema não tem nada
// ou avisa que o paciente não está no sistema
int obito_lista(Lista *l, Fila *f, int ID) {
    if (l->primeiro == NULL) {
        printf("Não há pacientes no sistema\n");
        return 2; // Código de erro: Sistema vazio
    }

    Cadastro *aux = NULL;
    Cadastro *aux2 = l->primeiro;

    while (aux2 != NULL && aux2->paciente->ID != ID) {
        aux = aux2;
        aux2 = aux2->back_lista;
    }

    if (aux2 == NULL) {
        printf("O paciente com ID %d não está no sistema!\n", ID);
        return 2;
    }

    if (buscar_fila(f, ID)) {
        return 0;
    }

    if (aux == NULL) {
        l->primeiro = aux2->back_lista;
        if (l->primeiro == NULL) {
            l->ultimo = NULL;
        }
    } else { 
        aux->back_lista = aux2->back_lista;
        if (aux2 == l->ultimo) {
            l->ultimo = aux;
        }
    }

    free(aux2->paciente);
    destroy_pilha(aux2->historico);
    free(aux2->historico);
    free(aux2);

    l->qtd--;
    return 1;
}

//Pre cond: Lista não vazia
//Pos cond: Checa se o paciente está na lista ou não
Cadastro *get_paciente(Lista *l, int ID){
    Cadastro *aux = l->primeiro;
    while(aux != NULL){
        if(aux->paciente->ID == ID){
            return aux;
        }
        aux = aux->back_lista;
    }
    return NULL;
}



//Pre cond: Recebe a lista
//Pos cond: Mostra a lista. Se ela estiver vazia, avisa
void mostrar_lista(Lista *l){
    Cadastro *aux = l->primeiro;
    if(l->primeiro == NULL){
        printf("O sistema está vazio\n");
    }
    while(aux != NULL){
        printf("%s (ID: %d)\n", aux->paciente->nome, aux->paciente->ID);
        aux = aux->back_lista;
    }
}

//Pre cond: Recebe uma lista
//Pos cond: Apaga todos os nós existentes no sistema, com excessão do struct
// da fila e da lista
void destroy_lista(Lista *l) {
    Cadastro *atual = l->primeiro;
    Cadastro *proximo;

    while (atual != NULL) {
        proximo = atual->back_lista;
        
        free(atual->paciente);
        destroy_pilha(atual->historico);
        free(atual->historico);
        free(atual);
        
        atual = proximo;
    }
    l->primeiro = NULL;
    l->ultimo = NULL;
    l->qtd = 0;
}
