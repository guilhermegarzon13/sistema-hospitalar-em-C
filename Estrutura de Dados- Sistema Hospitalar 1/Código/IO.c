//Guilherme da Mata Garzon - NUSP 15456601
#include "IO.h"
#include "historico.h" 
#include "lista.h"     
#include "triagem.h"   
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Pre cond: Recebe um ponteiro de arquivo, que precisa ser válido
// e um ponteiro inicializado de histórico
// Pos cond: Todos os procedimentos são salvos e copiados de forma persistente(com ordem respeitada)
static void salvar_historico(FILE *fp, Topo *historico) {
    fwrite(&historico->qtd, sizeof(int), 1, fp);
    procedimento *p = historico->top;
    while (p != NULL) {
        fwrite(p->proc, sizeof(char), 100, fp);
        p = p->back;
    }
}

//Pre cond: Recebe uma pilha p e um procedimento
//Pos cond: Adiciona o procedimento ao historico(essa função só será útil localmente)
static void push_pilha(Topo* p, char* proc_hist) {
    procedimento* aux = (procedimento*)malloc(sizeof(procedimento));
    if(!aux) return;

    strcpy(aux->proc, proc_hist);

    aux->back = p->top;
    p->top = aux;
    p->qtd++;
}

// Pre cond:  Recebe um ponteiro de arquivo para ler em binário
//e um ponteiro de histórico iniciado
// Pos cond: Reimpilha-se a pilha histórico, respeitando a ordem
static void carregar_historico(FILE *fp, Topo *historico) {
    int qtd = 0;
    fread(&qtd, sizeof(int), 1, fp);

    if (qtd == 0) return;

    procedimento* temp_array = malloc(sizeof(procedimento) * qtd);
    for (int i = 0; i < qtd; i++) {
        fread(temp_array[i].proc, sizeof(char), 100, fp);
    }

    //Empilha os procedimentos
    for (int i = qtd - 1; i >= 0; i--) {
        push_pilha(historico, temp_array[i].proc);
    }
    free(temp_array);
}



// Pre cond: Lista e fila estão iniciados(não precisa ambos ter elementos, um já basta)
// Pos cond: Os dados da lista e da fila são salvos em
//"lista_pacientes.bin" e "fila_atendimento.bin", respectivamente
//Além disso, se tudo der certo, retorna true. C.C retorna false
bool SAVE(Lista *lista, Fila *fila) {
    if (!lista || !fila) return false;

    FILE *fp_lista = fopen("lista_pacientes.bin", "wb");
    if (!fp_lista) return false;

    fwrite(&lista->qtd, sizeof(int), 1, fp_lista);
    Cadastro *c = lista->primeiro;
    while (c != NULL) {
        fwrite(&c->paciente->ID, sizeof(int), 1, fp_lista);
        fwrite(c->paciente->nome, sizeof(char), 150, fp_lista); 
        salvar_historico(fp_lista, c->historico);
        c = c->back_lista;
    }
    fclose(fp_lista);

    FILE *fp_fila = fopen("fila_atendimento.bin", "wb");
    if (!fp_fila) return false;

    fwrite(&fila->qtd, sizeof(int), 1, fp_fila);
    c = fila->primeiro;
    while (c != NULL) {
        fwrite(&c->paciente->ID, sizeof(int), 1, fp_fila);
        c = c->back_fila;
    }
    fclose(fp_fila);

    return true;
}


// Pre cond: Lista e fila são ponteiros iniciados mas vazios
// Pos cond: Os dados dos ".bin" são carregados e ordenados na fila e lista da maneira correta
// respeitando ordem, tamanho, etc
bool LOAD(Lista *lista, Fila *fila) {
    if (!lista || !fila) return false;

    FILE *fp_lista = fopen("lista_pacientes.bin", "rb");
    if (fp_lista) {
        int qtd_lista = 0;
        fread(&qtd_lista, sizeof(int), 1, fp_lista);

        for (int i = 0; i < qtd_lista; i++) {
            Cadastro *c = (Cadastro*) malloc(sizeof(Cadastro));
            c->historico = (Topo*) malloc(sizeof(Topo));
            init_pilha(c->historico);
            c->paciente = (Paciente*) malloc(sizeof(Paciente));

            fread(&c->paciente->ID, sizeof(int), 1, fp_lista); 
            fread(c->paciente->nome, sizeof(char), 150, fp_lista);
            carregar_historico(fp_lista, c->historico);

            c->back_lista = NULL;
            c->back_fila = NULL;
            if (lista->primeiro == NULL) {
                lista->primeiro = c;
                lista->ultimo = c;
            } else {
                lista->ultimo->back_lista = c;
                lista->ultimo = c;
            }
            lista->qtd++;
        }
        fclose(fp_lista);
    }

    FILE *fp_fila = fopen("fila_atendimento.bin", "rb");
    if (fp_fila) {
        int qtd_fila = 0;
        fread(&qtd_fila, sizeof(int), 1, fp_fila);
        int id_procurado;

        for (int i = 0; i < qtd_fila; i++) {
            fread(&id_procurado, sizeof(int), 1, fp_fila);
            Cadastro *paciente_encontrado = get_paciente(lista, id_procurado);
            if (paciente_encontrado) {
                adiciona_fila(fila, paciente_encontrado);
            }
        }
        fclose(fp_fila);
    }
    return true;
}
