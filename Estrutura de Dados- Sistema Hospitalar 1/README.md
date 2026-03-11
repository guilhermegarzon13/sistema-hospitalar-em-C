Autor: Guilherme da Mata Garzon

# Sistema de Gerenciamento de Pacientes - Parte 1

Esse projeto, inicialmente pensado para ser usado somente no SUS, é um sistema simples para gerenciar pacientes, que pode ser usado em hospitais e clínicas. Feito na linguagem C, o programa usa TADs de listas, filas e pilhas para fazer suas operações principais.

## Funcionalidades Principais

* **Cadastro de Pacientes:** Adiciona novos pacientes a uma LISTA geral(sistema central).
* **Fila de Atendimento:** Gerencia uma FILA única de espera.
* **Histórico Médico:** Mantém uma PILHA com o histórico de procedimentos de cada paciente.
* **Registro de Óbito:** Remove um paciente do sistema se ele não estiver na fila.
* **Persistência de Dados:** Salva e carrega os dados de todos os pacientes registrados(incluindo histórico completo), além da lista e fila inteiras e ordenadas, em arquivos binários (`lista_pacientes.bin` e `fila_atendimento.bin`), para não perder informações após o programa sair

## Pré-requisitos

Para compilar e executar o projeto, você precisa apenas de um compilador C, como o **GCC**, e da ferramenta **Make**.

## Como Compilar e Executar

O projeto inclui um `Makefile` que facilita a compilação e execução. Para usá-lo, navegue até a pasta do projeto no seu terminal e utilize os seguintes comandos:

**1. Para compilar o programa:**
```
make
```
Isso irá gerar um arquivo executável `programa`.

**2. Para executar o programa:**
```
make run
```
*ou*
```
./programa
```

**3. Para limpar os arquivos compilados(.o e programa):**
```
make clean
```

## Estrutura do Código

* **main.c:** Contém o menu principal e sua lógica
* **lista.c / lista.h:** Define e implementa a lista simplesmente encadeada que armazena todos os pacientes cadastrados.
* **triagem.c / triagem.h:** Define e implementa a fila de atendimento dos pacientes.
* **historico.c / historico.h:** Define e implementa a pilha para o histórico de procedimentos de cada paciente.
* **IO.c / IO.h:** Define e implementa o sistema para salvar e carregar os dados.
* **dados.h:** Contém a definição de todas as structs utilizadas no projeto.
