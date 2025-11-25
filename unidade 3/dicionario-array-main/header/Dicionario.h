#ifndef DICIONARIO_H
#define DICIONARIO_H

#include <utility>
#include <optional>
#include <iostream>

template<typename K, typename V>
class Dicionario
{
public:
	Dicionario(const size_t capacidade)
	{
		this->capacidade = capacidade;
		this->quantidade = 0;	
		pares = new std::pair<K, V>[this->capacidade];
	}

	~Dicionario()
	{
		delete[] pares;
	}

	bool inserir(const K& chave, const V& valor)
	{
		for(size_t i = 0; i<quantidade; i++){
			if(pares[i].first == chave){
				//atualizar
				pares[i].second = valor;
				return true;
			}
		}

		if(quantidade >= capacidade){
			throw std::overflow_error("Dicionário cheio"); //Não cabe mais
		}

		pares[quantidade] = std::make_pair(chave, valor);
		quantidade++;

		return true;
	}

	bool remover(const K& chave)
	{
		if(quantidade == 0){
			throw std::underflow_error("Dicionário vazio");
		}

		for(size_t i = 0; i<quantidade; i++){
			if(pares[i].first == chave){

				//mover o ultimo elemento para posição removida
				pares[i] = pares[quantidade - 1];

				quantidade--;
				return true;
			}
		}

		return false; // não achou
	}

	std::optional<V> buscar(const K& chave) const
	{
		for(size_t i = 0; i<quantidade; i++){
			if(pares[i].first == chave){
				return pares[i].second;
			}
		}
		return std::nullopt;
	}

	size_t tamanho() const
	{
		return quantidade;
	}

	void imprimir() const
	{
		for (size_t i = 0; i < quantidade; ++i) {
			std::cout << "(" << pares[i].first << ", " << pares[i].second << ")" << std::endl;
		}
	}
private:
	std::pair<K, V>* pares;
	size_t capacidade;
	size_t quantidade;	
};

#endif
