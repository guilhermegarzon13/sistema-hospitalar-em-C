//Guilherme da Mata Garzon - NUSP 15456601
#include<stdio.h>
#include<stdlib.h>
#include"dados.h"
#include "lista.h"
#include "triagem.h"
#include "historico.h"
#include"IO.h"

//Função que recoloca o '\n' para evitar problemas ao dar clear na tela
void recolocar_newline() {
    ungetc('\n', stdin);
}
//Função auxiliar que limpa o terminal, deixando o programa mais limpo
//em sua execução
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

int main(){
    Lista *l = (Lista*)malloc(sizeof(Lista));
    Fila *f= (Fila*)malloc(sizeof(Fila));
    int n;

    init_lista(l);
    init_fila(f);

    // Da load em um sistema(Se existir)
     if (LOAD(l, f)) {
        printf("Dados carregados com sucesso.\n");
    } else {
        printf("Nenhum dado encontrado! Iniciando um novo sistema.\n");
    }

    //Loop principal do código que mostra o menu e faz ações conforme a entrada digitada respectivamente
    do
    {

    printf("=====================================\n");
    printf("       SISTEMA DE ATENDIMENTO        \n");
    printf("=====================================\n\n");

    printf("1. Registrar paciente\n\n");

    printf("2. Dar óbito a um paciente\n\n");

    printf("3. Adicionar/Tirar procedimento do histórico médico de um paciente\n\n");

    printf("4. Chamar paciente à consulta\n\n");
    
    printf("5. Mostrar todos os pacientes do sistema\n\n");

    printf("6. Mostrar fila de espera\n\n");

    printf("7. Mostrar histórico de um paciente\n\n");

    printf("8. Salvar e fechar\n\n");

    printf("=====================================\n");
    printf("Digite a opcao desejada: \n");

    scanf("%d",&n);

    switch(n) {
        case 1:
          Cadastro *k = adiciona_lista(l);
          recolocar_newline();
          adiciona_fila(f,k);
          pausar_e_limpar_tela();
          break;
        case 2:
          int falecido;
          printf ("Informe o ID do falecido\n");
          scanf("%d",&falecido);
          Cadastro *j = get_paciente(l,falecido);
          if (j == NULL) {
            printf("Paciente não consta no sistema\n");
          }
          else{
            int check = obito_lista(l,f,falecido);
            if(check == 0){
              printf("ERRO:Paciente não pode falecer pois está na fila");
            }
            if(check == 1){
              printf("Paciente removido do sistema com sucesso...");
            }
          }
          pausar_e_limpar_tela();
          break;

        case 3:
          printf ("Digite o ID do paciente\n");
          int paciente_remedio;
          scanf("%d",&paciente_remedio);
          Cadastro *procurado = get_paciente(l,paciente_remedio);
          if (procurado == NULL){
            printf("Paciente não encontrado\n");
          }
          else{
            int opção;
            printf("O que fazer com paciente %s?",procurado->paciente->nome);
            printf("Digite uma das opções\n");
            printf("1. Adicionar novo procedimento\n");
            printf("2. Remover procedimento\n");
            scanf ("%d",&opção);

            switch(opção){
              case 1:
                  adiciona_pilha(procurado->historico);
                  recolocar_newline();
                  break;
              case 2:
                 pop_pilha(procurado->historico);
                 break;
        
            }  
          }
          pausar_e_limpar_tela();
          break;

        case 4:
          chamada(f);
          pausar_e_limpar_tela();
          break;
        case 5:
          mostrar_lista(l);
          pausar_e_limpar_tela();
          break;
        case 6:
          mostrar_fila(f);
          pausar_e_limpar_tela();
          break;
        case 7:
          printf("Digite o ID do paciente\n");
          int temp;
          scanf("%d",&temp);
          Cadastro *b = get_paciente(l,temp);
          if(b == NULL){
            printf("O paciente não consta no sistema \n");
          }
          else{
            printf("Historico do paciente %s: \n",b->paciente->nome);
            print_historico(b->historico);
          }
          pausar_e_limpar_tela();
          break;
        case 8:
          printf("Salvando e fechando o sistema \n");
          SAVE(l, f);
          pausar_e_limpar_tela();
           break;
        default:
          printf("Opção indisponível. Digite uma opção válida! \n");
          pausar_e_limpar_tela();
    } 
}while (n != 8);
//Da free na lista e na fila
destroy_lista(l);
free(l);
free(f);
return 0; 
}