//Guilherme da Mata Garzon - NUSP 15456601
#include <stdio.h>
#include <stdlib.h> 
#include <stdbool.h>
#include <string.h>
#include "AVL.h"
#include "heap.h"
#include "dados.h"

//Header para funções locais(elas se usam mutuamente, necessitando de header)
static void min_heap_sobe_chegada(Heap *h, int sobe, int b);
static void min_heap_desce_chegada(Heap *h, int pai_i, int filho_i);
static void min_heap_sobe_prioridade(Heap *h, int sobe, int b);
static void min_heap_desce_prioridade(Heap *h, int i);


//Pre cond: Heap é um ponteiro não vazio 
//Pos cond: Aloca o vetor do heap e coloca seu contador no zero
void init_heap(Heap *h){
    h->fila = (Espera*)malloc(sizeof(Espera)*MAX);
    h->pos = 0;
}

//Função auxiliar que retorna o pai de i
static int pai(int i){
    return (i - 1) / 2;
}

//Função auxiliar que retorna o filho esquerdo de i
int esquerda(int i){
    return (2 * i + 1);
}

//Função auxiliar que retorna o filho direito de i
int direita(int i){
    return (2 * i + 2);
}

//Função auxiliar que troca dois elementos da heap(pai e filho)
static void heap_troca(int i, int j, Heap *h){
    Espera aux = h->fila[i];
    h->fila[i] = h->fila[j];
    h->fila[j] = aux;
}

//Função auxiliar recursiva usada para corrigir a heap subindo 
//a partir do parâmetro prioridade
static void min_heap_sobe_prioridade(Heap *h, int sobe, int b){
    if(sobe<=0){
        return;
    }
    int p1 = h->fila[sobe].prioridade;
    int p2 = h->fila[b].prioridade;
    
    if(p1 == p2){

        min_heap_sobe_chegada(h,sobe,b);
    }
    else{
        if(p1 < p2){
            heap_troca(sobe,b,h);
            min_heap_sobe_prioridade(h, b, pai(b));
        }
    }
}

//Função auxiliar recursiva usada para corrigir a heap subindo 
//a partir do parâmetro chegada
static void min_heap_sobe_chegada(Heap *h, int sobe, int b){    
    if(sobe<=0){
        return;
    }
    int e1 = h->fila[sobe].chegada;
    int e2 = h->fila[b].chegada;
    
    if(e1 < e2){
        heap_troca(sobe,b,h);
        min_heap_sobe_prioridade(h, b, pai(b));
    }
}

//Função auxiliar recursiva usada para corrigir a heap descendo
//a partir do parâmetro prioridade
static void min_heap_desce_prioridade(Heap *h, int i){
    int e = esquerda(i);
    int d = direita(i);
    
    int menor = -1;

    if (e < h->pos) {
        menor = e; 
        if (d < h->pos) {
            int p_esq = h->fila[e].prioridade;
            int p_dir = h->fila[d].prioridade;
            int c_esq = h->fila[e].chegada;
            int c_dir = h->fila[d].chegada;
            
            if (p_dir < p_esq) {
                menor = d;
            } 
            else if (p_dir == p_esq && c_dir < c_esq) {
                menor = d;
            }
        }
    }
    
    if (menor == -1) return; 
    
    int p_pai = h->fila[i].prioridade;
    int p_filho = h->fila[menor].prioridade; 

    if (p_filho < p_pai) {
        heap_troca(i, menor, h);
        min_heap_desce_prioridade(h, menor); 
    }
    //Prioridade de pai e filho é igual. Usa-se o segundo parâmetro para ordenar o min-heap
    else if (p_filho == p_pai) {
        min_heap_desce_chegada(h, i, menor);
    }
}

//Função auxiliar recursiva usada para corrigir a heap descendo
//a partir do parâmetro chegada(só é usado se as prioridades do pai e filho são iguais)
static void min_heap_desce_chegada(Heap *h, int pai_i, int filho_i){
    int c_pai = h->fila[pai_i].chegada;
    int c_filho = h->fila[filho_i].chegada;
    
    if (c_filho < c_pai) {
        heap_troca(pai_i, filho_i, h);
        //Volta a ordenar pela prioridade(depois de lidar com o caso "problemático")
        min_heap_desce_prioridade(h, filho_i);
    }
}

//Pre cond: Heap, Cadastro e Prio são não nulos e iniciados
//Pos cond: Insere o novo Cadastro no final da fila e corrige
//Conforme a prioridade associada
void insere_heap(Heap *h, Cadastro *k, int *Prio){
    if(h->pos >= MAX){
        printf("Fila cheia!");
        return;
    }
    Espera K;
    K.aguardo = k;
    printf("===================================\n\n");
    printf("Digite a prioridade do paciente:\n\n");
    printf("1. Emergência(Risco de vida)\n\n");
    printf("2. Alta Urgência(Pode evoluir para morte)\n\n");
    printf("3. Urgência(Necessita de rápido atendimento médico, mas sem riscos)\n\n");
    printf("4. Pouco Urgente(Não necessita de rápido atendimento)\n\n");
    printf("5. Não Urgente\n\n");
    printf("===================================\n\n");
    scanf("%d", &K.prioridade);
    while(K.prioridade < 1 || K.prioridade > 5){
        printf("Digite uma prioridade válida (1 a 5): ");
        scanf("%d", &K.prioridade);
    }
    Prio[K.prioridade-1]++;
    K.chegada = Prio[K.prioridade-1];
    h->fila[h->pos] = K;    
    
    int b = pai(h->pos);
    min_heap_sobe_prioridade(h, h->pos, b);
    h->pos++;
    return;
}

//Pre cond: h é um ponteiro não nulo
//Pos cond: Chama o primeiro paciente da fila, substitui-o pelo último
//e corrige o heap
void chamada(Heap *h){
    if (h->pos == 0){
        printf("A fila está vazia!");
        return;
    } 

    Espera aux = h->fila[0]; 
    aux.aguardo->fila_check = 0;
    h->fila[0] = h->fila[h->pos - 1]; 
    h->pos--; 
    
    min_heap_desce_prioridade(h, 0);
    
    printf("Paciente %s (ID: %d)", aux.aguardo->paciente->nome, aux.aguardo->paciente->ID);
}

//Pre cond: heap é um ponteiro não nulo
//Pos cond: Cria um array auxiliar exatamente igual ao original
//e usa nele as propriedades do heap para exibir os pacientes
//em ordem
void mostrar_heap(Heap *h){
    if(h->pos == 0){
        printf("Fila vazia!\n");
        return;
    }

    Heap copia;
    copia.pos = h->pos;
    copia.fila = (Espera*)malloc(sizeof(Espera) * (copia.pos+1));

    memcpy(copia.fila, h->fila, sizeof(Espera) * h->pos);

    printf("\n=== Fila de Espera (Ordem de Atendimento) ===\n");
    int ordem = 1;

    while(copia.pos > 0){
        Espera topo = copia.fila[0];
        
        printf("%d. Prioridade: %d | Chegada: %d | %s (ID: %d)\n", 
               ordem,
               topo.prioridade, 
               topo.chegada, 
               topo.aguardo->paciente->nome, 
               topo.aguardo->paciente->ID);

        copia.fila[0] = copia.fila[copia.pos - 1];
        copia.pos--;
        min_heap_desce_prioridade(&copia, 0);
        
        ordem++;
    }

    free(copia.fila);
    printf("===================================\n");
}

// Pre cond: h é heap não nulo e arquivo já foi aberto para escrita
// Pos cond: Esvazia a heap, salvando os pacientes no arquivo EM ORDEM de atendimento e prioridade(usa as propriedades
// da heap para isso)
void salvar_esvaziar_heap(Heap *h, FILE *arq) {
    fprintf(arq, "%d\n", h->pos);

    while (h->pos > 0) {
        Espera topo = h->fila[0];

        fprintf(arq, "%d %d\n", topo.prioridade, topo.aguardo->paciente->ID);

        h->fila[0] = h->fila[h->pos - 1];
        h->pos--;

        min_heap_desce_prioridade(h, 0);
    }
}
