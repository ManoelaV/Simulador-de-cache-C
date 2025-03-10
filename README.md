# Cache Simulator

Este projeto implementa um simulador de cache em C, que permite a simulação de diferentes configurações de cache, incluindo número de conjuntos, tamanho do bloco, nível de associatividade e políticas de substituição.

## Estrutura do Projeto

- `src/main.c`: Ponto de entrada do simulador. Processa os argumentos da linha de comando, inicializa a cache e gerencia a leitura dos endereços do arquivo de entrada.
- `src/cache.c`: Implementação das funções relacionadas à simulação da cache, incluindo lógica de acesso, substituição e contagem de hits e misses.
- `src/cache.h`: Cabeçalho que declara as funções e estruturas utilizadas em `cache.c`.
- `src/utils.c`: Funções utilitárias para leitura de arquivos e manipulação de endereços.
- `include/utils.h`: Cabeçalho que declara as funções utilitárias disponíveis em `utils.c`.
- `tests/`: Contém arquivos binários com conjuntos de endereços para testes.
  - `bin_100.bin`: 100 endereços.
  - `bin_1000.bin`: 1000 endereços.
  - `bin_10000.bin`: 10.000 endereços.
  - `bin_186676.bin`: 186.676 endereços.
- `Makefile`: Instruções para compilar o projeto e criar executáveis.

## Instruções de Uso

Para executar o simulador, utilize a seguinte linha de comando:

```
cache_simulator <nsets> <bsize> <assoc> <substituição> <flag_saida> <arquivo_de_entrada>
```

### Parâmetros

- `<nsets>`: Número de conjuntos na cache.
- `<bsize>`: Tamanho do bloco em bytes.
- `<assoc>`: Grau de associatividade.
- `<substituição>`: Política de substituição (R para Random, F para FIFO, L para LRU).
- `<flag_saida>`: Flag que ativa o modo padrão de saída de dados.
- `<arquivo_de_entrada>`: Arquivo com os endereços para acesso à cache.

### Exemplo de Execução

Para executar o simulador com um arquivo de entrada específico, utilize o seguinte comando:

```
cache_simulator 256 4 1 R 1 tests/bin_100.bin
```

## Relatório de Saída

O simulador gera um relatório de estatísticas que inclui o número total de acessos, hits, misses (classificados em compulsórios, capacidade e conflito) e as taxas correspondentes. O formato da saída depende do valor do parâmetro `<flag_saida>`.

## Contribuições

Contribuições são bem-vindas! Sinta-se à vontade para abrir issues ou pull requests para melhorias e correções.