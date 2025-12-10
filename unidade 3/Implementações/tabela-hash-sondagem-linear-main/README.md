# 📚 Informações do Projeto

- **Instituição:** IMD  
- **Disciplina:** EDB1  
- **Professor:** Prof. Eiji Adachi

---

# 📖 Tabela Hash com Sondagem Linear e Redimensionamento

Este projeto implementa uma tabela hash que armazena pares chave-valor, oferecendo operações básicas como inserção, busca e remoção de elementos. Para resolver colisões, essa implementação implementa a técnica de **endereçamento aberto por sondagem linear**. Nesta técnica, as colisões são resolvidas buscando-se a próxima posição na tabela de forma sequencial. 

---

## 📌 Objetivo da Tabela Hash

A Tabela Hash tem como objetivo fornecer:
- Inserção eficiente de pares chave/valor.
- Atualização de valor caso a chave já exista.
- Detecção e uso inteligente de posições **REMOVIDAS**.
- Redimensionamento automático da tabela conforme o fator de carga.

---

## 🗂️ Estrutura de Dados

A estrutura `TabelaHash` contém:

- `Elemento* array`: array dinâmico de estruturas com chave, valor e estado.
- `int capacidade`: tamanho do array.
- `int quantidade`: número real de elementos ativos (estado `OCUPADO`).

Cada `Elemento` possui:
- `std::string chave`
- `std::string valor`
- `Estado estado` (`LIVRE`, `OCUPADO` ou `REMOVIDO`)

---

## 🧾 Por que usar um campo estado?

Para implementar a sondagem linear corretamente, é necessário que cada posição do array tenha um indicador de estado. O campo ``estado`` do ``Elemento`` permite distinguir entre:
- LIVRE: a posição nunca foi usada (pode encerrar buscas).
- OCUPADO: há um par chave-valor válido.
- REMOVIDO: havia uma chave, mas foi removida. A posição precisa ser ignorada na busca, mas pode ser reutilizada em futuras inserções.

Sem esse campo, não seria possível diferenciar uma posição nunca usada de uma posição que foi esvaziada por uma remoção — o que afetaria a correção da busca e da inserção.

---

## ⚙️ Interface da Classe `TabelaHash`

```cpp
class TabelaHash {
public:
	TabelaHash(int capacidadeInicial = 17);
	~TabelaHash();

	bool inserir(const std::string& chave, const std::string& valor);
	bool remover(const std::string& chave);
	std::optional<std::string> buscar(const std::string& chave) const;

	int tamanho() const;
	bool vazia() const;
	bool cheia() const;
	void imprimir() const;

	ConsistenciaStatus checarConsistencia() const;
};
```

---

## ✅ Funcionamento das Operações

### 🔑 Inserção

- Usa `hash(chave)` para obter o índice base.
- Aplica **sondagem linear** para encontrar posição livre ou atualiza se a chave já existir.
- Se encontrar posição `REMOVIDA`, registra o índice para possível reutilização.
- Redimensiona a tabela caso o fator de carga ultrapasse 50%.

### 🗑️ Remoção

- Localiza a chave e marca a posição como `REMOVIDO`.
- Reduz a `quantidade` e redimensiona se o fator de carga cair abaixo de 12.5%.

### 🔍 Busca

- Aplica sondagem linear a partir do índice hashado.
- Para ao encontrar `LIVRE`, ou retorna o valor se encontrar a chave.

### ♻️ Redimensionamento

- Usado para aumentar ou diminuir dinamicamente a tabela.
- Realiza nova alocação e reinserção direta dos elementos `OCUPADO`.

---

## 📊 Tabela de Complexidades

| Operação  | Complexidade Média | Complexidade no Pior Caso |
|-----------|--------------------|----------------------------|
| Inserir   | O(1)               | O(N)                       |
| Remover   | O(1)               | O(N)                       |
| Buscar    | O(1)               | O(N)                       |
| Imprimir  | O(N)               | O(N)                       |
| Redimensionar | O(N)           | O(N)                       |

> O pior caso ocorre quando a tabela está muito cheia ou com muitos elementos `REMOVIDO`.

---

## 🧪 Sobre `std::optional`

O uso de `std::optional<std::string>` na busca permite:
- Distinguir entre valor vazio e chave inexistente;
- Um contrato mais seguro e explícito de retorno.

---

## 📂 Estrutura de Diretórios

```
.
├── bin/              # Executáveis e objetos .o/.d
├── header/           # TabelaHash.h
├── src/              # Código principal
├── test/             # Testes com doctest
├── lib/              # doctest.h e possíveis utilitários
├── makefile          # Automação de build
├── README.md         # Este arquivo
```

---

## 🛠️ Compilação e Execução com Makefile

| Comando                   | Descrição                              |
|---------------------------|------------------------------------------|
| `make`                    | Compila o projeto e os testes            |
| `make run`                | Executa o programa principal             |
| `make test`               | Compila todos os testes                  |
| `make run-test`           | Executa todos os testes                  |
| `make run-test-inserir`   | Executa o teste de inserção              |
| `make run-test-buscar`    | Executa o teste de busca                 |
| `make run-test-remover`   | Executa o teste de remoção               |
| `make run-test-redimensionar` | Executa o teste de redimensionamento |
| `make clean`              | Remove arquivos temporários e binários  |
