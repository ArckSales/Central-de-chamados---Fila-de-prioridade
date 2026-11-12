
# Central de Chamados — Fila de Prioridade

Projeto desenvolvido em linguagem C para gerenciamento de chamados
utilizando uma fila de prioridade implementada com lista simplesmente
encadeada e alocação dinâmica de memória.

## Estrutura do projeto

- `main.c`: menu principal e interação com o usuário.
- `fila_prioridade.h`: declaração das estruturas e protótipos.
- `fila_prioridade.c`: implementação das operações da fila.

## Regra de atendimento e análise

As prioridades são representadas por valores crescentes: normal (1), alta
(2) e crítica (3). A lista fica ordenada da maior para a menor prioridade,
então o atendimento sempre remove o primeiro chamado. Na inserção, a busca
continua enquanto a prioridade existente for maior ou igual à nova. Esse
`igual` mantém chamados de mesma prioridade na ordem em que chegaram.

Inserir em lista ordenada custa **O(n)** no pior caso, pois pode ser necessário
percorrer os chamados existentes até achar a posição. Alocar e ligar o novo nó
custa O(1). Atender custa O(1), porque remove o primeiro nó; exibir a fila custa
O(n), pois percorre todos os chamados. O espaço usado é O(n).

Para demonstrar: cadastre um chamado normal, dois críticos e um alto. Ao exibir
a fila, os críticos devem aparecer primeiro, na ordem em que foram cadastrados,
seguidos pelo alto e pelo normal. Ao escolher **2 - Atender chamado**, o primeiro
crítico deve ser atendido; escolha **3 - Exibir fila de chamados** para conferir
os restantes. As opções 2 e 3 operam sobre a fila em memória durante a execução.

## Como executar

Abra o terminal na pasta do projeto e execute os seguintes comandos:

### 1. Entrar na pasta do projeto

```bash
cd CentralDeChamados
```

### 2. Compilar o programa

```bash
gcc main.c fila_prioridade.c -o central_chamados -Wall -Wextra -std=c11
```

### 3. Executar o programa

```bash
./central_chamados
```
