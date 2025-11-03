//
//  Pilha.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __Pilha__
#define __Pilha__

#include <sstream>
#include <string>
template <typename T>
class Pilha
{
private:
    T* elementos;
    int capacidade;
    int quantidade;
    
public:
    Pilha(int cap)
    {
        this->quantidade = 0;
        this->capacidade = cap;
        elementos = new T[this->capacidade];
    }
    
    ~Pilha()
    {
        delete [] elementos;
    }
    
    int tamanho() const
    {
        return this->quantidade;
    }

    bool vazia() const
    {
        return this->quantidade == 0;
    }

    bool cheia() const
    {
        return this->quantidade == this->capacidade;
    }

    T topo() const
    {
        if(vazia()){
            throw std::underflow_error("Pilha vazia");
        }
        return elementos[quantidade-1];
    }

    void empilhar(T elemento)
    {
        if(cheia()){
            throw std::overflow_error("Pilha cheia");
        }
        elementos[quantidade] = elemento;
        quantidade++;
    }

    void desempilhar()
    {
        if(vazia()){
            throw std::underflow_error("Pilha vazia");
        }
        quantidade--;
    }

    std::string imprimir() const
    {
        std::stringstream resultado;
        resultado << "{ ";
        for (int i = 0; i < tamanho(); ++i) 
        {
            resultado << elementos[i] << " ";
        }
        resultado << "}";
        return resultado.str();
    }
        
};
#endif 
