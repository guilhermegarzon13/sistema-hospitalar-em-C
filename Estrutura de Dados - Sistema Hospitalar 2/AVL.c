//Guilherme da Mata Garzon - NUSP 15456601
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include "dados.h"
#include "AVL.h"

#define max(a,b) (((a) > (b)) ? (a) : (b))

//Pre cond: T é um ponteiro de árvore não nulo
//Pos cond: Raiz aponta para NULL
void init_AVL(AVL *T){
    T->raiz = NULL;
}


//Função auxiliar que retorna altura do no
static int get_altura(Cadastro *raiz){
    if(raiz == NULL){
        return -1;
    }
    else{
        return raiz->altura;
    }
}

//Função auxiliar que associa a um nó sua altura de maneira recursiva
static void set_altura(Cadastro*raiz){
    if(raiz == NULL){
        return;
    }
    else{
        raiz->altura = max(get_altura(raiz->esq),get_altura(raiz->dir)) + 1;
    }
}

//Função auxiliar que realiza uma rotação esquerda no No
static Cadastro *rot_esq(Cadastro *N){
    Cadastro *aux = N->dir;
    N->dir = aux->esq;
    aux->esq = N;
    set_altura(N);
    set_altura(aux);
    N = aux;
    return N;
}

//Função auxiliar que realiza uma rotação direita no No
static Cadastro *rot_dir(Cadastro *N){
    Cadastro *aux = N->esq;
    N->esq = aux->dir;
    aux->dir = N;
    set_altura(N);
    set_altura(aux);
    N = aux;
    return N;
}

//Função auxiliar que retorna o fator de balanceamento da árvore AVL(checar para qual dos lados ela pende)
static int get_FB(Cadastro *raiz){
    if (raiz == NULL){
        return 0;
    }
    else{
        return get_altura(raiz->dir) - get_altura(raiz->esq);
    }
}

//Função auxiliar que realiza o balanceamento do nó, realizando rotações a depender do caso
static Cadastro *balancear(Cadastro *N){
    int i = get_FB(N);
    
    if(i>1){
        int j = get_FB(N->dir);
        if (j>=0){
            N = rot_esq(N);
        }
        else{
            N->dir = rot_dir(N->dir);
            N = rot_esq(N);
        }
    }

    if(i<-1){
        int k = get_FB(N->esq);
        if (k<=0){
            N = rot_dir(N);
        }
        else {
            N->esq = rot_esq(N->esq);
            N = rot_dir(N);
        }
    }
    return N;
}


//Função auxiliar usada na remoção convencional da árvore(pega o menor nó mais a direita do nó a ser removido)
static Cadastro *remover_No_dir(Cadastro *N, Cadastro **sucessor){
    if(N->esq == NULL){
        *sucessor = N;
        if(N->dir!=NULL){
            return N->dir;
        }
        else{
            return NULL;
        }
    }
    else{
        N->esq  = remover_No_dir(N->esq, sucessor);
        set_altura(N);
        return balancear(N);
    }
}

//Função auxiliar usada na remoção convencional da árvore(pega o menor nó mais a esquerda do nó a ser removido)
static Cadastro *remover_No_esq(Cadastro *N, Cadastro **sucessor){
    if(N->dir == NULL){
        *sucessor = N;
        if(N->esq!=NULL){
            return N->esq;
        }
        else{
            return NULL;
        }
    }
    else{
        N->dir = remover_No_esq(N->dir, sucessor);
        set_altura(N);
        return balancear(N);
    }
}

//Função auxiliar recursiva que ajuda a printar a árvore em ordem(inorder)
static void print_No(Cadastro *N){
    if(N == NULL){
        return;
    }
    print_No(N->esq);
    printf("%s (ID: %d)\n", N->paciente->nome, N->paciente->ID);
    print_No(N->dir);
}

//Função auxiliar para destruir nós recursivamente em pós ordem(usado para destruir a árvore)
static void free_nodes(Cadastro *N) {
    if (N == NULL) return;
    free_nodes(N->esq);
    free_nodes(N->dir);
    free(N->paciente);
    free(N);
}

//Função auxiliar usada na inserção
static Cadastro *inserir_recursivo(Cadastro *N, Cadastro *insere){
    if(N == NULL){
        return insere;
    }
    int i = insere->paciente->ID;
    if(i > N->paciente->ID){
        N->dir = inserir_recursivo(N->dir, insere);
    }
    else if(i < N->paciente->ID){
        N->esq = inserir_recursivo(N->esq, insere);
    }
    else{
        return N;
    }
    set_altura(N);
    return balancear(N);
}

//Pre cond: k é um Cadastro não nulo
//Pos cond: Insere o Cadastro na árvore(sistema)
void AVL_inserir(AVL *T, Cadastro *k) {
    if (T == NULL) return;
    T->raiz = inserir_recursivo(T->raiz, k);
}

//Função auxiliar recursiva usada na remoção
static Cadastro *remover_recursivo(Cadastro *N, int id){
    if(N == NULL){
        return NULL;
    }

    if(N->paciente->ID == id){
        if(N->dir == NULL && N->esq == NULL){
            free(N->paciente);
            free(N);
            return NULL;
        }
        if (N->dir != NULL && N->esq == NULL) {
            Cadastro *temp = N->dir;
            free(N->paciente);
            free(N);
            return temp;
        }
        if (N->dir == NULL && N->esq != NULL) {
            Cadastro *temp = N->esq;
            free(N->paciente);
            free(N);
            return temp;
        }

        if(N->dir != NULL && N->esq != NULL ){
            int i = get_FB(N);
            if (i >= 0){
                Cadastro *aux;
                N->dir = remover_No_dir(N->dir, &aux);
                aux->dir = N->dir;
                aux->esq = N->esq;
                free(N->paciente);
                free(N);
                N = aux;
                set_altura(N);
                return balancear(N);
            }
            else {
                Cadastro *aux;
                N->esq = remover_No_esq(N->esq, &aux);
                aux->esq = N->esq;
                aux->dir = N->dir;
                free(N->paciente);
                free(N);
                N = aux;
                set_altura(N);
                return balancear(N);
            }
        }
    }

    if(N->paciente->ID > id){
        N->esq = remover_recursivo(N->esq, id);
        set_altura(N);
        return balancear(N);
    }
    else {
        N->dir = remover_recursivo(N->dir, id);
        set_altura(N);
        return balancear(N);
    }
}




//Pre cond:....
//Pos cond: Checa se o ID indicado está na árvore ou não. Se estiver, retorna true
//C.C retorna false
bool busca_AVL(AVL *T, int id){
    if(T == NULL || T->raiz == NULL){
        return false;
    }
    Cadastro *aux = T->raiz;
    while(aux != NULL){
        if(aux->paciente->ID > id){
            aux = aux->esq;
        }
        else if(aux->paciente->ID < id){
            aux = aux->dir;
        }
        else{
            return true;
        }
    }
    return false;
}

//Pre cond:...
//Pos cond: Retorna o Cadastro com o dado ID. Se não encontrar, retorna NULL
Cadastro *get_AVL(AVL *T, int id){
    if(T == NULL || T->raiz == NULL){
        return NULL;
    }
    Cadastro *aux = T->raiz;
    while(aux != NULL){
        if(aux->paciente->ID > id){
            aux = aux->esq;
        }
        else if(aux->paciente->ID < id){
            aux = aux->dir;
        }
        else{
            return aux;
        }
    }
    return NULL;
}

//Pre Cond:....
//Pos Cond: Remove o Cadastro associado ao id da árvore. Se não estiver na árvore, não faz nada
void remover_AVL(AVL *T, int id) {
    if (T != NULL) {
        T->raiz = remover_recursivo(T->raiz, id);
    }
}

//Pre cond:....
//Pos cond: Printa a árvore em order(inorder). Se árvore for vazia, avisa
void print_AVL(AVL *T){
    if(T == NULL || T->raiz == NULL){
        printf("Sistema vazio!\n");
        return;
    }
    print_No(T->raiz);
}

//Pre cond:...
//Pos cond: Destroi a árvore, liberando todos os seus nós em pós ordem
void destroy_arvore(AVL *T) {
    if (T != NULL) {
        free_nodes(T->raiz);
        T->raiz = NULL;
    }
}
