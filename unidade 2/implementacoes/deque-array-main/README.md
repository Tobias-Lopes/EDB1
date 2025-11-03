# Informações do Projeto

- **Instituição:** IMD  
- **Disciplina:** EDB1  
- **Professor:** Prof. Eiji Adachi  

# Deque Implementado com Array

Este projeto implementa uma estrutura de dados do tipo **Deque (Double-Ended Queue)** utilizando um **array alocado dinamicamente com comportamento circular**. O deque permite inserção e remoção de elementos tanto na extremidade frontal (front) quanto na extremidade traseira (back), seguindo as políticas **FIFO** (First-In, First-Out) e **LIFO** (Last-In, Last-Out), conforme o método chamado.

A classe é genérica e aceita qualquer tipo de dado por meio do uso de **templates**.

---

## Estrutura de Dados

O deque é composto por:

- **elementos**: ponteiro para um array do tipo `T` (tipo genérico).  
- **capacidade**: número máximo de elementos que o deque pode armazenar.  
- **quantidade**: quantidade atual de elementos no deque.  
- **frente**: índice do elemento que está na parte frontal (front).  
- **atras**: índice onde o próximo elemento será inserido na parte traseira (back).  

---

## Interface da Classe `Deque<T>`

```cpp
template <typename T>
class Deque {
private:
    T* elementos;
    int capacidade;
    int quantidade;
    int frente;
    int atras;

public:
    Deque(int cap);
    ~Deque();

    int tamanho() const;
    bool vazia() const;
    bool cheia() const;

    void empurrar_atras(T elemento);
    void empurrar_frente(T elemento);
    T remover_atras();
    T remover_frente();
    T daFrente() const;
    T deTras() const;

    std::string imprimir() const;
};
```

---

## Como Funcionam as Operações

### ✅ Empurrar no Fim (`empurrar_atras`)
1. Verifica se o deque está cheio.  
2. Insere o novo elemento na posição `atras`.  
3. Atualiza `atras` com comportamento circular.
4. Incrementa `quantidade`.  
5. Lança `std::overflow_error("Deque cheio.")` se o deque estiver cheio.

### ✅ Empurrar na Frente (`empurrar_frente`)
1. Verifica se o deque está cheio.  
2. Ajusta `frente` para a posição anterior com comportamento circular.
3. Insere o elemento em `elementos[frente]`.  
4. Incrementa `quantidade`.  
5. Lança `std::overflow_error("Deque cheio.")` se o deque estiver cheio.

### ✅ Remover do Início (`remover_frente`)
1. Verifica se o deque está vazio.  
2. Armazena o valor de `elementos[frente]` em uma variável temporária.  
3. Atualiza `frente` para a próxima posição circular.
4. Decrementa `quantidade`.  
5. Retorna o valor removido.  
6. Lança `std::underflow_error("Deque vazio.")` se o deque estiver vazio.

### ✅ Remover do Fim (`remover_atras`)
1. Verifica se o deque está vazio.  
2. Ajusta `atras` para a posição anterior com comportamento circular.
3. Armazena o valor de `elementos[atras]` em uma variável temporária.  
4. Decrementa `quantidade`.  
5. Retorna o valor removido.  
6. Lança `std::underflow_error("Deque vazio.")` se o deque estiver vazio.

### ✅ Consultar Frente (`daFrente`)
- Retorna o elemento na posição `frente`.  
- Lança `std::underflow_error("Deque vazio.")` se estiver vazio.

### ✅ Consultar Trás (`deTras`)
- Calcula a posição do último elemento inserido (índice anterior a `atras`) com comportamento circular.
- Retorna `elementos[pos]`.  
- Lança `std::underflow_error("Deque vazio.")` se estiver vazio.

### ✅ Imprimir (`imprimir`)
- Percorre o array circular a partir de `frente` até contabilizar `quantidade` elementos.  
- Monta uma `std::string` no formato `{ elem1 elem2 ... }` respeitando a ordem lógica do deque (front → back).

---

## Por Que Usar Array Circular?

- ✔️ **Aproveitamento total do espaço do array.**  
- ✔️ **Sem necessidade de mover elementos** ao inserir ou remover.  
- ✔️ **Implementação eficiente**, com tempo constante para as operações principais (exceto imprimir, que é O(n)).  

---

## Tabela de Complexidades

| Operação              | Complexidade |
|-----------------------|--------------|
| Empurrar no fim       | O(1)         |
| Empurrar na frente    | O(1)         |
| Remover do início     | O(1)         |
| Remover do fim        | O(1)         |
| Consultar frente      | O(1)         |
| Consultar trás        | O(1)         |
| Verificar vazio       | O(1)         |
| Verificar cheio       | O(1)         |
| Imprimir              | O(n)         |

---

## 📂 Estrutura de Diretórios

```
.
├── bin/        # Executáveis gerados após a compilação
├── doc/        # Documentação do projeto
├── header/     # Arquivos de cabeçalho (.h) – inclui Deque.h
├── lib/        # Bibliotecas externas (ex: doctest.h)
├── src/        # Implementação das classes (.cpp), se houver
├── test/       # Arquivos de teste (usando doctest)
├── .gitignore  # Arquivos/diretórios ignorados pelo Git
├── makefile    # Automação da compilação e execução
└── README.md   # Este arquivo
```

---

## 🛠️ Compilação e Execução Usando o Makefile

### 🔧 Comandos Disponíveis:

| Comando             | Descrição                                     |
|---------------------|-----------------------------------------------|
| `make` ou `make all`  | Compila o projeto principal e os testes.     |
| `make run`          | Executa o programa principal (`bin/main`).    |
| `make test`         | Compila apenas os testes.                     |
| `make run-test`     | Executa os testes unitários (`bin/test`).     |
| `make clean`        | Remove arquivos objeto e executáveis.         |

### 📌 Exemplos de Uso:

```bash
# Compilar todo o projeto
make

# Executar o programa principal (caso exista um main que use Deque)
make run

# Compilar e executar os testes unitários
make run-test

# Limpar arquivos de build gerados
make clean
```