# 📚 Informações do Projeto

- **Instituição:** IMD  
- **Disciplina:** EDB1  
- **Professor:** Prof. Eiji Adachi

---

# 📖 Dicionário Genérico (`template`) Implementado com Array e `std::pair`

Este projeto implementa um **Tipo Abstrato de Dados (TAD) Dicionário** — também chamado de **Tabela de Símbolos (Symbol Table)** ou **Mapa (Map)** — usando um **array fixo de pares `<chave, valor>`**, com tipos genéricos definidos por **template**.

A estrutura usa `std::pair` da STL para armazenar cada par e permite que o usuário escolha **quaisquer tipos de chave e valor** no momento de instanciar o Dicionário.

---

## 📌 Objetivo do Dicionário

O TAD Dicionário armazena **pares de chave e valor**, garantindo que **cada chave seja única** dentro da estrutura.

- Se a chave já existe e for inserida novamente, **o valor é atualizado**.
- Se for uma nova chave e houver espaço, o par é inserido.
- Se estiver cheio, uma exceção é lançada.

Com o uso de *templates*, **você escolhe os tipos de chave e valor** — por exemplo:
```cpp
Dicionario<std::string, double> dic1(10);
Dicionario<int, std::string> dic2(5);
```

---

## 🗂️ Estrutura de Dados

A classe `Dicionario` é definida como `template<typename K, typename V>`, onde:
- `K` é o tipo da **chave**
- `V` é o tipo do **valor**

Internamente, usa:
- Um **array fixo** de `std::pair<K, V>` para armazenar os pares.
- Um campo `capacidade` para definir o limite máximo de pares.
- Um campo `quantidade` para rastrear quantos pares estão atualmente armazenados.

---

## ⚙️ Interface da Classe `Dicionario`

```cpp
template<typename K, typename V>
class Dicionario {
private:
	std::pair<K, V>* pares;
	int capacidade;
	int quantidade;

public:
	Dicionario(const int capacidade);
	~Dicionario();

	bool inserir(const K& chave, const V& valor);
	bool remover(const K& chave);
	std::optional<V> buscar(const K& chave) const;

	int tamanho() const;
	void imprimir() const;
};
```

---

## 🔑 Por que usamos `std::optional` no método `buscar` ?

No método `buscar`, passamos uma chave e esperamos receber de volta o **valor associado a essa chave**. 
No entanto, se a chave informada **não existir no dicionário**, surge uma questão importante: *o que retornar nesse caso?* 
Retornar um valor padrão poderia confundir o usuário (pois poderia ser um valor válido) ou exigir convenções artificiais. 
Por isso, usamos o `std::optional` para indicar claramente quando há um valor associado ou não.

No C++, o tipo **`std::optional`** (C++17) é um contêiner leve que pode **conter um valor ou não conter nada**.  
É uma forma robusta e clara de sinalizar **resultados opcionais**, evitando valores mágicos como `nullptr` ou defaults arbitrários para indicar “não encontrado”.

No `buscar`:
- **Se a chave existe:** retorna o valor dentro de um `std::optional`.
- **Se a chave não existe:** retorna `std::nullopt`.

**Exemplo de uso:**
```cpp
Dicionario<std::string, double> dic(10);
dic.inserir("pi", 3.14);

auto res = dic.buscar("pi");
if (res.has_value()) {
	std::cout << "Valor: " << res.value() << std::endl;
} else {
	std::cout << "Chave não encontrada." << std::endl;
}
```

Para usar o valor retornado por buscar:
- `has_value()` verifica se o `optional` contém um valor válido.
- `value()` acessa o valor contido, se existir.

---

## ✅ Como Funcionam as Operações

### 🔑 Inserção

- Procura a chave no array.
- Se já existe, **atualiza o valor**.
- Se não existe e há espaço, adiciona um novo par.
- Se estiver cheio, **lança exceção**.

### 🗑️ Remoção

- Procura a chave.
- Se encontrar, faz `swap` com o último par para remoção eficiente (O(1)) e reduz `quantidade`.
- Se não encontrar, retorna `false`.
- Se o dicionário estiver vazio, lança exceção.

### 🔍 Busca

- Percorre o array.
- Retorna um `std::optional<V>` com o valor dentro, se encontrar.
- Caso contrário, `std::nullopt`.

No caso da busca, o retorno em caso de sucesso será algo como:

```cpp
std::optional<V> buscar(const K& chave) const {
	(...)
		if ( condição ) {
			return pares[i].second;  // <- retorna o VALOR dentro do par
		}
	}
	(...)
}
```

Perceba que no código acima é retornado `pares[i].second`, que é do tipo `V`, enquanto o tipo de retorno do método é `std::optional<V>`. Em C++, quando você faz `return pares[i].second`, o compilador vê que o tipo de retorno da função é `std::optional<V>` e ele converte automaticamente `V` em `std::optional<V>` usando o construtor de `optional`.

Se você quiser construir um `std::optional<V>` manualmente, sem delegar ao compilador essa construção, você pode fazer da seguinte forma:

```cpp
std::optional<V> temp(pares[i].second);
return temp;
```

A primeira linha acima encapsula o valor `pares[i].second` dentro de um `std::optional<v>` para deixar claro que um resultado válido existe. A linha seguinte, retorna este valor.

### 📏 Tamanho

- Retorna o número de pares armazenados.

### 🖨️ Imprimir

- Percorre o array e exibe todos os pares `(chave, valor)`.

---

## 📊 Tabela de Complexidades

| Operação  | Complexidade |
|-----------|---------------|
| Inserir   | O(N) |
| Remover   | O(N) (busca) + O(1) (swap) |
| Buscar    | O(N) |
| Imprimir  | O(N) |
| Tamanho   | O(1) |

---

## 📂 Estrutura de Diretórios

```
.
├── bin/        # Executáveis gerados
├── header/     # Cabeçalho com template (Dicionario.h)
├── src/        # (opcional) Outros .cpp auxiliares
├── test/       # Testes unitários (doctest)
├── lib/        # Bibliotecas externas (ex: doctest.h)
├── makefile    # Automação da compilação e testes
├── README.md   # Este arquivo
```

---

## 🛠️ Compilação e Execução Usando Makefile

### 🔧 Comandos

| Comando          | Descrição                                      |
|------------------|------------------------------------------------|
| `make`           | Compila tudo: principal e testes.              |
| `make run`       | Executa o programa principal.                  |
| `make test`      | Compila os testes unitários.                   |
| `make run-test`  | Executa os testes (`bin/test`).                |
| `make clean`     | Remove arquivos objeto, dependências e binários.|

### 📌 Exemplos

```bash
# Compilar tudo
make

# Executar o programa interativo
make run

# Compilar e executar os testes unitários
make run-test

# Limpar tudo
make clean
```