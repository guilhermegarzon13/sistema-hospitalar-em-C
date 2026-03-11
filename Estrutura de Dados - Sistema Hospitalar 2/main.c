//Guilherme da Mata Garzon - NUSP 15456601
#include<stdio.h>
#include<stdlib.h>
#include<string.h> 
#include"dados.h"
#include "AVL.h"
#include "heap.h"
#include"IO.h"


//Função usada para limpar buffer
void limpar_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

//Função usada para limpar tela após cada ação
void pausar_e_limpar_tela() {
    printf("\n\nPressione Enter para continuar...");
    while(getchar() != '\n');
    getchar();

    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}


//Função principal
int main(){
    AVL *T = (AVL*)malloc(sizeof(AVL));
    Heap *h = (Heap*)malloc(sizeof(Heap));
    int n;

    init_AVL(T);
    init_heap(h);
    int *Prio = (int*)malloc(sizeof(int)*5);
    int w;
    for(w = 0; w<5;w++){
      Prio[w] = 0;
    }
    LOAD(T,h,Prio);
    printf("Carregando dados...");

    do
    {
    printf("=====================================\n");
    printf("       SISTEMA DE ATENDIMENTO        \n");
    printf("=====================================\n\n");

    printf("1. Registrar paciente\n\n");

    printf("2. Dar óbito a um paciente\n\n");

    printf("3. Dar alta ao paciente\n\n");
    
    printf("4. Mostrar todos os pacientes do sistema\n\n");

    printf("5. Mostrar fila de espera\n\n");

    printf("6. Buscar paciente por ID\n\n");

    printf("7. Salvar e fechar\n\n");

    printf("=====================================\n");
    printf("Digite a opcao desejada: \n");

    scanf("%d",&n);

    switch(n) {
        case 1: { 
          int id;
          printf("Digite o ID do paciente: ");
          scanf("%d", &id);
          Cadastro *k = get_AVL(T, id); // Verifica se já existe

          //Paciente encontrado
          if(k != NULL){
            if(k->fila_check == 1){
              printf("Paciente já está na fila!");
            }

            else{
              printf("Paciente já consta no sistema. Adicionando ele na fila!\n");
              insere_heap(h, k, Prio);
              k->fila_check = 1; //Marcar que entrou na fila
            }
          }

          //Paciente não encontrado
          else{
            printf("Paciente não consta no sistema. Digite seu nome para a inclusão no sistema:\n");
            
            k = (Cadastro*)malloc(sizeof(Cadastro));
            k->paciente = (Paciente*)malloc(sizeof(Paciente));
            
            k->paciente->ID = id;
            limpar_buffer();
            fgets(k->paciente->nome, 150, stdin);
            k->paciente->nome[strcspn(k->paciente->nome, "\n")] = 0;
            k->esq = NULL;
            k->dir = NULL;
            k->altura = 0; 
            k->fila_check = 1;
            AVL_inserir(T, k); 
            
            //Insere na Heap
            insere_heap(h, k,Prio);
          }
          pausar_e_limpar_tela();
          break;
        }
        case 2: {
          int falecido;
          printf ("Informe o ID do falecido\n");
          scanf("%d",&falecido);
          Cadastro *j =  get_AVL(T,falecido);
          if (j == NULL) {
            printf("Paciente não consta no sistema\n");
          }
          
          //Caso em que paciente está na fila
          else{
            if(j->fila_check == 1){
              printf("Paciente não pode ser removido pois está na fila");
            }
            //Remove paciente
            else{
            remover_AVL(T,falecido);
            printf("Paciente removido do sistema com sucesso...");
            }
          }
          pausar_e_limpar_tela();
          break;
        }

        case 3:
          chamada(h);
          pausar_e_limpar_tela();
          break;
        case 4:
          print_AVL(T);
          pausar_e_limpar_tela();
          break;
        case 5:
          mostrar_heap(h);
          pausar_e_limpar_tela();
          break;
        case 6: {
          printf("Digite o ID do paciente\n");
          int temp;
          scanf("%d",&temp);
          //Busca paciente por ID e o exibe
          Cadastro *b = get_AVL(T,temp);
          if(b == NULL){
            printf("ID não consta no sistema");
          }
          else{ 
            printf("O paciente procurado é %s (ID: %d)\n", b->paciente->nome, b->paciente->ID);
          }
          pausar_e_limpar_tela();
          break;
        }
        case 7:
          printf("Salvando e fechando o sistema \n");
          SAVE(T, h);
          pausar_e_limpar_tela();
           break;
        default:
          printf("Opção indisponível. Digite uma opção válida! \n");
          pausar_e_limpar_tela();
    } 
}while (n != 7);
//Apaga o sistema todo da RAM
destroy_arvore(T);
free(T);
free(h->fila);
free(h);
free(Prio);
return 0; 
}
