Autor: Guilherme da Mata Garzon

# Sistema de Gerenciamento de Pacientes (AVL + Heap)

Esse projeto é um sistema para gerenciar pacientes em hospitais e clínicas, focado na eficiência de memória e execução. Diferente do projeto anterior, baseado em estruturas lineares

O sistema foi implementado em linguagem C e utiliza **Árvores AVL** para o banco de dados dos pacientes e **Heap Mínimo** (Min-Heap) para a gestão da fila de prioridades.

## Funcionalidades Principais

* **Base de Dados de Pacientes (AVL):** - Utiliza uma Árvore Binária de Busca Balanceada (AVL) para armazenar todos os pacientes do sistema.
    - Permite a **inserção**, **busca** e **remoção** eficiente de pacientes através do ID único.
    - Permite a exibição de todos os pacientes atualmente registrados.

* **Fila de Prioridade Inteligente (Heap):** - Gerencia a fila de espera utilizando um Heap.
    - Classifica os pacientes em 5 níveis de prioridade (1. Emergência a 5. Não Urgente).
    - **Critério de Desempate:** Para pacientes com a mesma prioridade, o sistema respeita a ordem de chegada.

* **Gerenciamento de Atendimento:** - **Chamar Paciente:** Chama para consulta o paciente de maior prioridade e que chegou antes na fila.
    - **Dar Óbito:** Remove paciente do sistema se ele não estiver na fila

* **Persistência de Dados:** - Salva e carrega o estado da Árvore AVL e da Fila (Heap) em arquivos binários (`sistema.bin` e `heap.bin`), garantindo que nenhum dado seja perdido ao fechar o programa.

## Pré-requisitos

Para compilar e executar o projeto, você precisa de:
* Um compilador C.
* Ferramenta **Make** (opcional, para uso do Makefile).

## Como Compilar e Executar

O projeto pode ser compilado via terminal. Navegue até a pasta do projeto e utilize os comandos abaixo:

## Como Compilar e Executar

**1. Para compilar o programa:**

make


**2. Para executar o programa:**


make run


*ou*


./programa



**3. Para limpar os arquivos compilados (.o e executável):**


make clean



