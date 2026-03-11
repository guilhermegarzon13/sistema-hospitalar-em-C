//Guilherme da Mata Garzon - NUSP 15456601
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include "IO.h"
#include"dados.h"
#include"AVL.h"
#include"heap.h"

//Função auxiliar para salvar a árvore
//Pre cond: Arquivo é não vazio
//Pos cond: Recursivamente, salva informações básicas do paciente(ID e nome) da árvore em pre ordem em um arquivo binário
static void salvar_arvore_aux(Cadastro *N, FILE *arq) {
    if (N == NULL) {
        return;
    }

    fprintf(arq, "%d\n", N->paciente->ID);
    fprintf(arq, "%s\n", N->paciente->nome);

    salvar_arvore_aux(N->esq, arq);
    salvar_arvore_aux(N->dir, arq);
}

//Pre cond:...
//Pos cond: Salva o banco de fila principal(Árvore AVL) e guarda as posições e prioridades
//da fila(heap) 
void SAVE(AVL *T, Heap *h) {

    //Salva árvore
    FILE *arq_arv = fopen("sistema.bin", "w");
    if (arq_arv == NULL) {
        printf("Erro ao abrir arquivo para salvar!\n");
        return;
    }
    if (T != NULL) {
        salvar_arvore_aux(T->raiz, arq_arv);
    }
    fclose(arq_arv);

    //Salva heap
    FILE *arq_heap = fopen("heap.bin", "w");
    if(arq_heap == NULL){
        printf("Erro ao criar arquivo para salvar fila!");
    }
    else{
    salvar_esvaziar_heap(h,arq_heap);
    }
}

//Pre cond: T, h e Prio são não nulos
//Pos cond: Lê os dados dos arquivos salvos(se existirem) e os registra
//Os dados recuperados respeitam ordem da árvore, prioridades e ordens de chegada
int LOAD(AVL *T, Heap *h, int *Prio) {

    //Load na árvore
    FILE *arq1 = fopen("sistema.bin", "r");
    if (arq1 == NULL) {
        return 0;
    }

    int id,i;
    char nome[150];

    while (fscanf(arq1, "%d\n", &id) != EOF) {
        
        //Copia o nome
        fgets(nome, 150, arq1);
        nome[strcspn(nome, "\n")] = 0;


        Cadastro *novo = (Cadastro*)malloc(sizeof(Cadastro));
        novo->paciente = (Paciente*)malloc(sizeof(Paciente));
        
        novo->paciente->ID = id;
        strcpy(novo->paciente->nome, nome);
        
        novo->esq = NULL;
        novo->dir = NULL;
        novo->altura = 0;
        novo->fila_check = 0;

        //Insere na árvore o elemento recuperado
        AVL_inserir(T, novo);
    }
    fclose(arq1); //Fecha o arquivo da árvore
   
    //Load heap
    FILE *arq_heap = fopen("heap.bin", "r");
    if (arq_heap != NULL) {
        int qtd_heap;
        int prio_temp, id_temp;
        int c1=0,c2=0,c3=0,c4=0,c5=0;

        // Lê quantos itens existiam na heap
        fscanf(arq_heap, "%d", &qtd_heap);

        // Reinicia contador do heap atual
        h->pos = 0; 

        for (i = 0; i < qtd_heap; i++) {
            // Lê prioridade e ID
            fscanf(arq_heap, "%d %d", &prio_temp, &id_temp);

            // Busca o ponteiro na árvore recem carregada
            Cadastro *paciente_real = get_AVL(T, id_temp);

            //Contador para usar na ordem de chegada da fila
            if (paciente_real != NULL) {
                int indice_atual = h->pos;
                if(prio_temp == 1){
                    c1++;
                    h->fila[indice_atual].chegada = c1;
                }
                if(prio_temp == 2){
                    c2++;
                    h->fila[indice_atual].chegada = c2;
                }
                if(prio_temp == 3){
                    c3++;
                    h->fila[indice_atual].chegada = c3;
                }
                if(prio_temp == 4){
                    c4++;
                    h->fila[indice_atual].chegada = c4;
                }
                if(prio_temp == 5){
                    c5++;
                    h->fila[indice_atual].chegada = c5;
                }
                h->fila[indice_atual].prioridade = prio_temp;
                h->fila[indice_atual].aguardo = paciente_real;
                
                
                paciente_real->fila_check = 1;
                
                h->pos++;
            }
    }
    fclose(arq_heap); //Fecha o arquivo da heap
    
    //Usam os contadores para indicar qual será a posição
    //de novos pacientes
    Prio[0] = c1;
    Prio[1] = c2;
    Prio[2] = c3;
    Prio[3] = c4;
    Prio[4] = c5;
    }
    return 1;
}



