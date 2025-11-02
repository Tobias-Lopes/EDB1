# Informações do Projeto

- **Instituição:** IMD
- **Disciplina:** EDB1
- **Professor:** Prof. Eiji Adachi

# Lista Duplamente Encadeada com Nós Sentinelas

Este projeto implementa uma lista duplamente encadeada utilizando **nós sentinelas de cabeça e cauda**. Esta técnica visa simplificar as operações de inserção e remoção, evitando casos especiais quando a lista está vazia ou contém apenas um elemento.

A lista armazena elementos do tipo `std::string` apenas por uma questão de simplificação, mas pode ser facilmente adaptada para outros tipos incorporando o template à classe Lista.

---

## Estrutura de Dados

A lista é formada por nós interligados, cada um contendo:

- **valor**: o dado armazenado (no caso, um `std::string`).
- **proximo**: ponteiro para o próximo nó.
- **anterior**: ponteiro para o nó anterior.

Além dos nós de dados, a lista possui **dois nós sentinelas**: `cabeca` e `cauda`.  
Esses nós **não armazenam dados relevantes** e são utilizados apenas para simplificar a lógica de inserção e remoção.

---

## Interface da Classe `ListaDuplamenteEncadeada`

```cpp
class ListaDuplamenteEncadeada {
private:
    No<std::string>* cabeca;
    No<std::string>* cauda;
    int quantidade;

public:
    ListaDuplamenteEncadeada();
    ~ListaDuplamenteEncadeada();

    bool inserirInicio(std::string s);
    bool inserirFim(std::string s);
    bool inserir(int i, std::string s);

    std::string removerInicio();
    std::string removerFim();
    std::string remover(int i);

    const std::string primeiroElemento() const;
    const std::string ultimoElemento() const;
    const std::string elementoNaPosicao(int i) const;

    int tamanho() const;
    bool vazia() const;
    int buscar(std::string s) const;
    void imprimir() const;

    StatusDaLista checarConsistencia() const;
};
```

---

## Como Funcionam as Operações

✅ **Inserções de modo geral:** Todas as inserções funcionam de modo dimilar, seguindo uma estrutura de:
- Criar o novo nó.
- Posicionar o novo nó na lista, isto é, posicionar os seus ponteiros anterior e próximo no local desejado.
- Atualizar os nós vizinhos ao novo nó.
- Incrementar a quantidade.
- Retornar `true`.

**Inserção no início**  
- Insere o novo nó **imediatamente após o nó `cabeca`**. 

**Inserção no fim**  
- Insere o novo nó **imediatamente antes do nó `cauda`**.

**Inserção em posição arbitrária**  
- Percorre a lista até a i-ésima posição.  
- Insere o novo nó **antes** do i-ésimo nó.

✅ **Remoções de modo geral:** As remoções também seguem uma estrutura similar:
- Apontar para o nó que se deseja remover.
- Atualizar os vizinhos.
- Copiar o valor do nó que se deseja remover.
- Deletar o nó.
- Decrementar a quantidade.
- Retornar o valor do nó removido.

Obs.: Copiar e retornar o valor do nó foi uma decisão tomada apenas para facilitar a implementação dos testes executáveis. Na prática, nem sempre seria necessário retornar o valor do nó removido.

**Remoção do início**  
- Remove o nó imediatamente após o nó `cabeca`.

**Remoção do fim**  
- Remove o nó imediatamente antes do nó `cauda`.

✅ **Remoção em posição arbitrária**  
- Percorre a lista até a i-ésima posição.  
- Remove o nó naquela posição.

✅ **Busca de elemento**  
- Percorre a lista e retorna a posição (1-based) do elemento encontrado.  
- Retorna -1 se não encontrar.

✅ **Impressão**  
- Imprime todos os elementos na ordem em que estão na lista.

✅ **Checagem de consistência**  
- Verifica se os ponteiros de `cabeca`, `cauda` e os encadeamentos intermediários estão corretos.

---

## Por Que Usar Nós Sentinelas?

✔️ **Elimina casos especiais** ao lidar com listas vazias ou com apenas um elemento.  
✔️ **Código mais simples e uniforme**.  
✔️ **Menos condicionais e verificações** em operações básicas.  
✔️ **Apenas dois nós extras** de memória (um de cabeça e outro de cauda).

---

## Tabela de Complexidades

| Operação                   | Complexidade |
|-----------------------------|--------------|
| Inserção no início         | O(1)         |
| Inserção no fim            | O(1)         |
| Inserção em posição i      | O(n)         |
| Remoção no início          | O(1)         |
| Remoção no fim             | O(1)         |
| Remoção em posição i       | O(n)         |
| Acesso ao primeiro         | O(1)         |
| Acesso ao último           | O(1)         |
| Acesso em posição i        | O(n)         |
| Busca de elemento          | O(n)         |

---

## 📂 **Estrutura de Diretórios**

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

## 🛠️ **Compilação e Execução Usando o Makefile**

#### 🔧 **Comandos Disponíveis:**

| Comando            | Descrição                                    |
|---------------------|----------------------------------------------|
| `make` ou `make all` | Compila o programa principal e os testes.   |
| `make run`         | Executa o programa principal (`bin/main`).   |
| `make test`        | Compila apenas os testes.                    |
| `make run-test`    | Executa os testes (`bin/test`).              |
| `make clean`       | Remove arquivos objeto e executáveis.        |

#### 📌 **Exemplos de Uso:**

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