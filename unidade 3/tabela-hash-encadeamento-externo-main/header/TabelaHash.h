#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>
#include <iostream>
#include <optional>
#include <unordered_set>

struct No {
	std::string chave;
	std::string valor;
	No* proximo;

	No(const std::string& c, const std::string& v) : chave(c), valor(v), proximo(nullptr) {}
};

enum class ConsistenciaStatus {
    OK = 0,
    PONTEIRO_INVALIDO,
    CICLO_DETECTADO,
    DESALINHAMENTO_HASH_INDICE,
    QUANTIDADE_INCORRETA,
	CHAVE_DUPLICADA
};

class TabelaHash {
friend class TabelaHashTestHelper;

private:
	No** array;
	int capacidade;
	int quantidade;

	static constexpr int CAPACIDADE_MINIMA = 17;
	static constexpr float FATOR_CARGA_MAX = 2.0f;
	static constexpr float FATOR_CARGA_MIN = 0.25f;

	unsigned int valorHash(const std::string& chave) const {
		unsigned int valorHash = 0;
		for (char c : chave) {
			// Função simples para facilitar colisões em testes
			valorHash += static_cast<unsigned int>(c);
			// Forma melhor de calcular valor hash que gera valores mais distribuídos
			// valorHash = 31 * valorHash + static_cast<unsigned int>(c);
		}
		/*
		// Algoritmo FNV-1a (Fowler–Noll–Vo hash)
		unsigned int valorHash = 2166136261u;
		for (char c : chave) {
    		valorHash ^= static_cast<unsigned int>(c);
    		valorHash *= 16777619u;
		}
		//*/
		return valorHash;
	}

	int hash(const std::string& chave) const {
		return this->valorHash(chave) % capacidade;
	}

	void redimensionar(int novaCapacidade) {
		throw std::runtime_error("Ainda não implementado.");
	}

	void aumentar() {
		redimensionar(this->capacidade*2+1);
	}

	void diminuir() {
		auto metadeCapacidade = this->capacidade / 2;
		int novaCapacidade;
		if(metadeCapacidade < CAPACIDADE_MINIMA )
		{
			novaCapacidade = CAPACIDADE_MINIMA;
		}
		else 
		{
			novaCapacidade = metadeCapacidade;
		}
		redimensionar(novaCapacidade);
	}

	float fatorCarga() const {
		return static_cast<float>(quantidade) / static_cast<float>(capacidade);
	}

public:
	TabelaHash(int cap = CAPACIDADE_MINIMA) : capacidade(cap), quantidade(0) {
		array = new No*[capacidade];

		// Inicializamos todos os ponteiros do array com nullptr para
		// saber quando uma posição está vazia		
		for (int i = 0; i < capacidade; ++i) {
			array[i] = nullptr;
		}
	}

	~TabelaHash() {
		for (int i = 0; i < capacidade; ++i) {
			No* atual = array[i];
			while (atual != nullptr) {
				No* temp = atual;
				atual = atual->proximo;
				delete temp;
			}
		}
		delete[] array;
	}

	bool inserir(const std::string& chave, const std::string& valor) {
		auto valorHash = hash(chave);

		No* atual = array[valorHash];

		while (atual != nullptr)
		{
			if(atual->chave == chave){
				atual->valor = valor;
				return true;
			}
			atual = atual->proximo;
		}
		
		//inserir no inicio
		No* novo = new No(chave, valor);
		novo->proximo = array[valorHash];
		array[valorHash] = novo;

		++quantidade;

		return true;
	}

	bool remover(const std::string& chave) {
		auto valorHash = hash(chave);

		No* atual = array[valorHash];
		No* anterior = nullptr;

		while (atual != nullptr)
		{
			if(atual->chave == chave){
				//caso seja o 1º da lista
				if(anterior == nullptr){
					array[valorHash] = atual->proximo;
				} else {
					anterior->proximo = atual->proximo;
				}

				delete atual;
				quantidade--;
				return true;
			}

			anterior = atual;
			atual = atual->proximo;
		}

		return false;
	}

	std::optional<std::string> buscar(const std::string& chave) const {
		auto valorHash = hash(chave);

		No* atual = array[valorHash];

		while (atual != nullptr)
		{
			if(atual->chave == chave){
				return atual->valor;
			}
			atual = atual->proximo;
		}
		
		return std::nullopt;
	}

	int tamanho() const {
		return quantidade;
	}

	void imprimir() const {
		for (int i = 0; i < capacidade; ++i) {
			std::cout << "[" << i << "]: ";
			No* atual = array[i];
			while (atual != nullptr) {
				std::cout << "(" << atual->chave << ", " << atual->valor << ") → ";
				atual = atual->proximo;
			}
			std::cout << "nullptr\n";
		}
	}

	ConsistenciaStatus checarConsistencia() const {
		int contadorTotal = 0;
		std::unordered_set<std::string> chavesVisitadas;

		for (int i = 0; i < capacidade; ++i) {
			if(array[i] == nullptr){
				continue;
			}

			No* lento = array[i];
			No* rapido = array[i];

			// Detecta ciclos com algoritmo do Floyd
			while (rapido != nullptr && rapido->proximo != nullptr) {
				rapido = rapido->proximo->proximo;
				lento = lento->proximo;

				if (rapido == lento) {
					return ConsistenciaStatus::CICLO_DETECTADO;
				}
			}

			No* atual = array[i];
			while (atual != nullptr) {
				// Todos pares no mesmo encadeamento devem possuir o mesmo hash
				if (hash(atual->chave) != i) {
					return ConsistenciaStatus::DESALINHAMENTO_HASH_INDICE;
				}
				// Chaves não podem se repetir
				if (chavesVisitadas.count(atual->chave)) {
					return ConsistenciaStatus::CHAVE_DUPLICADA;
				}
				chavesVisitadas.insert(atual->chave);
				contadorTotal++;
				atual = atual->proximo;
			}
		}

		if (contadorTotal != quantidade) {
			return ConsistenciaStatus::QUANTIDADE_INCORRETA;
		}

		return ConsistenciaStatus::OK;
	}
};

#endif