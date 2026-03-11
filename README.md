# Sistema de Gerenciamento de Pacientes (Estruturas de Dados)

Este projeto é um sistema focado no gerenciamento de pacientes, idealizado para hospitais e clínicas. Feito na linguagem C, o programa usa TADs de listas, filas e pilhas para fazer suas operações principais.

## 🚀 A Evolução do Projeto (Otimização)
O grande diferencial deste repositório é a demonstração prática de otimização de código e melhoria de complexidade. O projeto está dividido em duas etapas:

* 📁 **`/versao_1_basica`**: A implementação inicial do sistema. Funcional, porém com estruturas de dados menos eficientes para buscas e inserções em larga escala.
* 📁 **`/versao_2_otimizada`**: A versão melhorada. Aqui, as estruturas gerais foram aprimoradas para garantir maior eficiência computacional, reduzindo o tempo de execução nas operações críticas do sistema hospitalar. No entanto, não há sistema de histórico médico, como requisitado nas especificações do projeto

## ⚙️ Funcionalidades e Estruturas
* **Listas (Cadastro Geral):** Adiciona novos pacientes ao sistema central.
* **Filas (Atendimento):** Gerencia a fila de espera respeitando a ordem de chegada/prioridade.
* **Pilhas (Histórico Médico):** Mantém o histórico de procedimentos de cada paciente.
* **Persistência de Dados (IO):** Salva e carrega os dados em arquivos binários (`.bin`), garantindo que o estado do hospital não seja perdido ao fechar o programa.

## 💻 Como Compilar e Executar
Cada versão possui seu próprio `Makefile`. Navegue até a pasta da versão desejada no terminal e execute:

**Para compilar:**
> `make`

**Para executar:**
> `make run` ou `./programa`

**Para limpar os arquivos compilados:**
> `make clean` 
