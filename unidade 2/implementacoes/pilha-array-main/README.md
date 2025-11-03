# Informacoes do Projeto

- **Instituicao:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

# Pilha Implementada com Array

Este projeto implementa uma estrutura de dados do tipo **Pilha (Stack)** utilizando um **array alocado dinamicamente**. A pilha segue a politica **LIFO (Last-In, First-Out)**, ou seja, o ultimo elemento inserido é o primeiro a ser removido.

A classe é generica e aceita qualquer tipo de dado através do uso de **templates**.

---

## Estrutura de Dados

A pilha é composta por:

- **elementos**: ponteiro para um array do tipo `T` (tipo generico).
- **capacidade**: numero maximo de elementos que a pilha pode armazenar.
- **quantidade**: quantidade atual de elementos na pilha.

---

## Interface da Classe `Pilha<T>`

```cpp
class Pilha {
private:
    T* elementos;
    int capacidade;
    int quantidade;

public:
    Pilha(int cap);
    ~Pilha();

    int tamanho() const;
    bool vazia() const;
    bool cheia() const;

    void empilhar(T elemento);
    void desempilhar();
    T topo() const;

    std::string imprimir() const;
};
```

---

## Como Funcionam as Operacoes

✅ **Empilhar**
- Verifica se a pilha está cheia.
- Insere o novo elemento na posição `quantidade`.
- Incrementa `quantidade`.
- Lança `std::overflow_error` se a pilha estiver cheia.

✅ **Desempilhar**
- Verifica se a pilha está vazia.
- Decrementa `quantidade`.
- Lança `std::underflow_error` se a pilha estiver vazia.

✅ **Topo**
- Retorna o elemento na posição `quantidade - 1`.
- Lança `std::underflow_error` se a pilha estiver vazia.

✅ **Imprimir**
- Percorre o array do primeiro ao último elemento inserido e monta uma string no formato `{ elem1 elem2 ... }`.

---

## Por Que Usar Array?

✔️ **Acesso direto aos elementos** por índice.  
✔️ **Implementação simples e eficiente** para pilhas de tamanho fixo.  
✔️ **Baixo overhead** de memória (sem ponteiros extras).

---

## Tabela de Complexidades

| Operacao         | Complexidade |
|------------------|--------------|
| Empilhar         | O(1)         |
| Desempilhar      | O(1)         |
| Consultar topo   | O(1)         |
| Verificar vazio  | O(1)         |
| Verificar cheio  | O(1)         |
| Imprimir         | O(n)         |

---

## 📂 Estrutura de Diretórios

```
.
├── bin/       # Executáveis gerados após a compilação
├── doc/       # Documentação do projeto
├── header/    # Arquivos de cabeçalho (.h)
├── lib/       # Bibliotecas externas (ex: doctest.h)
├── src/       # Implementação das classes (.cpp)
├── test/      # Arquivos de teste (usando doctest)
├── .gitignore # Arquivos/diretórios ignorados pelo Git
├── makefile   # Automação da compilação e execução
└── README.md  # Este arquivo
```

---

## 🛠️ Compilação e Execução Usando o Makefile

### 🔧 Comandos Disponíveis:

| Comando            | Descrição                                    |
|---------------------|----------------------------------------------|
| `make` ou `make all` | Compila o programa principal e os testes.   |
| `make run`         | Executa o programa principal (`bin/main`).   |
| `make test`        | Compila apenas os testes.                    |
| `make run-test`    | Executa os testes (`bin/test`).              |
| `make clean`       | Remove arquivos objeto e executáveis.        |

### 📌 Exemplos de Uso:

```bash
# Compilar o projeto
make

# Executar o programa principal
make run

# Compilar e rodar os testes
make run-test

# Limpar arquivos de build
make clean
```
