# Tabela Hash - Sondagem Linear

## Descrição

Este projeto implementa uma tabela hash que armazena pares chave-valor, oferecendo operações básicas como inserção, busca e remoção de elementos. Para resolver colisões, essa implementação implementa a técnica de endereçamento aberto por sondagem linear. Nesta técnica, as colisões são resolvidas buscando-se a próxima posição na tabela de forma sequencial. 

### Executando os Testes

Este projeto inclui um conjunto de testes unitários escritos em C++ utilizando o framework Catch2. Para facilitar a execução dos testes, o projeto já contém um `Makefile` configurado. A seguir, estão as instruções para compilar e rodar os testes:

#### 1. Compilando e Executando Todos os Testes

Para compilar e executar todos os testes disponíveis no projeto, você pode utilizar o seguinte comando:

```bash
make run-test
```

Este comando irá compilar todos os testes e em seguida executá-los.

#### 2. Executando Testes Específicos

Caso você queira executar um teste específico, como o teste de inserção, busca ou remoção, utilize um dos comandos abaixo:

- **Teste do método Inserir**:
    ```bash
    make run-test-inserir
    ```
    Este comando compila e executa os testes relacionados à funcionalidade de inserção na tabela hash.

- **Teste do método Buscar**:
    ```bash
    make run-test-buscar
    ```
    Este comando compila e executa os testes relacionados à funcionalidade de busca na tabela hash.

- **Teste do método Remover**:
    ```bash
    make run-test-remover
    ```
    Este comando compila e executa os testes relacionados à funcionalidade de remoção na tabela hash.

- **Teste do método Redimensionar**:
    ```bash
    make run-test-redimensionar
    ```
    Este comando compila e executa os testes relacionados à funcionalidade de redimensionar a tabela hash.

#### 3. Limpando os Arquivos Gerados

Após executar os testes, você pode querer limpar os arquivos binários e objetos gerados. Para isso, utilize o seguinte comando:

```bash
make clean
```

Este comando remove todos os arquivos compilados, incluindo os binários dos testes e os arquivos objeto.