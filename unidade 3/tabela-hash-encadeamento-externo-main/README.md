# 📚 Informações do Projeto

- **Instituição:** IMD  
- **Disciplina:** EDB1  
- **Professor:** Prof. Eiji Adachi

---

# 📖 Tabela Hash com Encadeamento Externo

Este projeto implementa uma **Tabela Hash** com **encadeamento externo** para resolução de colisões. A estrutura armazena pares **(chave, valor)**, com chaves únicas, e realiza inserções, buscas e remoções.

A estrutura usa um **array de ponteiros para nós encadeados**. Cada encadeamento armazena nós (`No`) com pares valor e chave dos tipos `string`, e todos os nós em um mesmo encadeamento possuem o mesmo valor de hash.

---

## 📌 Objetivo da Tabela Hash

A Tabela Hash armazena pares de chave e valor, garantindo:
- Operações com resolução de colisões por encadeamento externo.
- Atualização automática em operações de inserir se a chave já existir.

---

## 🗂️ Estrutura de Dados

A estrutura `TabelaHash` contém:

- `No** tabela`: array de ponteiros para listas encadeadas.
- `int capacidade`: número de buckets.
- `int quantidade`: total de elementos na tabela.

Cada `No` contém:
- `std::string chave`
- `std::string valor`
- `No* proximo`: para o encadeamento.

---

## ⚙️ Interface da Classe `TabelaHash`

```cpp
class TabelaHash {
public:
	TabelaHash(int cap = 17);
	~TabelaHash();

	bool inserir(const std::string& chave, const std::string& valor);
	bool remover(const std::string& chave);
	std::optional<std::string> buscar(const std::string& chave) const;

	int tamanho() const;
	void imprimir() const;

	ConsistenciaStatus checarConsistencia() const;
};
```

---

## ✅ Funcionamento das Operações

### 🔑 Inserção

- Calcula o índice com a função hash.
- Se a chave já existe na lista encadeada, atualiza o valor.
- Caso contrário, insere no início da lista.
- Incrementa `quantidade` apenas se for novo.

### 🗑️ Remoção

- Calcula o índice e percorre a lista.
- Remove o nó correspondente se existir.
- Atualiza `quantidade`.

### 🔍 Busca

- Calcula o índice e percorre a lista encadeada.
- Retorna `std::optional<std::string>` com o valor se encontrado, ou `std::nullopt` caso contrário.

### 📏 Tamanho

- Retorna `quantidade`, ou seja, total de pares armazenados.

### 🖨️ Imprimir

- Percorre todos os buckets e exibe os pares existentes.

### 🔍 Consistência

- Verifica:
  - Se há ciclos nas listas encadeadas.
  - Se cada nó está no encadeamento correto segundo a função hash.
  - Se o contador `quantidade` bate com os elementos reais.
  - Se não existem chaves repetidas.

---

## 🧪 Enum `ConsistenciaStatus`

```cpp
enum class ConsistenciaStatus {
	OK = 0,
	PONTEIRO_INVALIDO,
	CICLO_DETECTADO,
	POSICAO_INCORRETA,
	QUANTIDADE_INCORRETA,
	CHAVE_DUPLICADA
};
```

---

## 🔍 Sobre `std::optional`

- A busca retorna `std::optional<std::string>` para indicar se a chave foi encontrada.
- Evita ambiguidade ao retornar valores nulos ou padrões.

---

## 🧠 Considerações sobre Função Hash

A função hash é parte central das tabelas hash. Uma boa função hash garante que os dados sejam eficientemente distribuídos, rapidamente acessíveis e que colisões sejam minimizadas.

### 🧰 Propriedades Desejáveis de uma Função Hash

Uma boa função hash deve apresentar as seguintes características:

1. **Determinística**: para a mesma entrada, sempre deve produzir o mesmo hash.
2. **Eficiência Computacional**: deve ser rápida, mesmo em grandes volumes de dados.
3. **Boa Dispersão**: pequenas variações na entrada devem gerar grandes diferenças no hash, minimizando o número de colisões para entradas comuns.
4. **Distribuição Uniforme**: os valores hash devem ser bem distribuídos entre os índices da tabela.

---

### 🧮 Implementando Função Hash usando método da divisão
O método da divisão é uma forma simples e eficiente de converter o valor numérico obtido por uma função hash em um índice válido da tabela (entre 0 e capacidade - 1). A fórmula é:

```cpp
indice = valorHash(chave) % capacidade;
```

Ou seja, pegamos o valor hash de uma chave e calculamos o resto da divisão dele pela capacidade da tabela. Isso garante que o índice resultante esteja dentro dos limites válidos do array interno, independentemente do valor absoluto do hash.

O método da divisão é bastante usado por ser simples e eficiente de ser implementado.

---

### 🧮 Por que é interessante que a capacidade da tabela seja um **Número Primo**?

Ao criar uma tabela hash, é importante escolher a **capacidade** (tamanho do array interno) com atenção, visto que esse valor é usado no cálculo da função hash. 

O ideal é que esse valor seja um **número primo**, por dois motivos principais:

1. **Melhor Distribuição**: ao usar `indice = valorHash % capacidade`, se a capacidade for um número composto, padrões nos valores de hash podem fazer com que muitas chaves se agrupem nos mesmos índices. Números primos reduzem esse risco e tendem a distribuir as chaves de forma mais uniforme.

2. **Evita Agrupamentos Previsíveis**: quando a capacidade tem fatores comuns com os valores gerados pela função hash, pode haver colisões excessivas. Números primos dificultam esse alinhamento indesejado.

---

### 🔢 Sobre o Cálculo: `valorHash = 31 * valorHash + c`

A fórmula usada para gerar o valor hash de uma `std::string` é baseada na multiplicação acumulada:

```cpp
unsigned int valorHash = 0;
for (char c : chave) {
	valorHash = 31 * valorHash + static_cast<unsigned int>(c);
}
```

Esse padrão:
- O número **31** é pequeno, primo e permite multiplicações eficientes (`31 * x = (x << 5) - x`).
- O resultado leva em conta **ordem e valor dos caracteres**, gerando hashes únicos mesmo para strings parecidas como `"abc"` e `"acb"`.

Isso garante que:
- A ordem dos caracteres é relevante.
- Colisões são menos frequentes com chaves parecidas.

---

## 📊 Tabela de Complexidades

| Operação  | Complexidade Média |
|-----------|--------------------|
| Inserir   | O(1)               |
| Remover   | O(1)               |
| Buscar    | O(1)               |
| Imprimir  | O(N)               |
| Tamanho   | O(1)               |

> No **pior caso** (todas as chaves colidindo), as operações podem cair para O(N).

---

## 📂 Estrutura de Diretórios

```
.
├── bin/           # Executáveis
├── header/        # TabelaHash.h
├── src/           # Código fonte
├── test/          # Testes com doctest
├── lib/           # doctest.h ou outras libs
├── makefile       # Automação
├── README.md      # Este arquivo
```

---

## 🛠️ Compilação e Execução com Makefile

| Comando         | Descrição                             |
|-----------------|----------------------------------------|
| `make`          | Compila tudo                           |
| `make run`      | Executa o programa principal           |
| `make test`     | Compila os testes unitários            |
| `make run-test` | Executa os testes com doctest          |
| `make clean`    | Limpa binários e objetos gerados       |