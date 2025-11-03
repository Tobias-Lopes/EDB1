//
//  Fila.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __Fila__
#define __Fila__

#include <string>
#include <sstream>
template <typename T>
class Fila
{
private:
    T* elementos;
    int capacidade;
    int quantidade;
    int inicio;
    int fim;
    
public:
    Fila(int cap)
    {
        this->capacidade = cap;
        this->quantidade = 0;
        this->inicio = 0;
        this->fim = 0;
        this->elementos = new T[cap];
    }
    
    ~Fila()
    {
        delete[] elementos;
    }
    
    int tamanho()
    {
        return this->quantidade;
    }

    T frente()
    {
        if(vazia()){
            throw std::underflow_error("Fila vazia");
        }

        return this->elementos[inicio];
    }

    void enfileirar(T elemento)
    {
        if(cheia()){
            throw std::overflow_error("Fila cheia");
        }

        this->elementos[fim] = elemento;
        this->fim = (this->fim + 1) % this->capacidade;
        this->quantidade++;
    }

    T desenfileirar()
    {
        if(vazia()){
            throw std::underflow_error("Fila vazia");
        }

        T valor = this->elementos[inicio];
        this->inicio = (this->inicio + 1) % this->capacidade;
        this->quantidade--;
        return valor;
    }

    bool cheia()
    {
        return this->quantidade == this->capacidade;
    }

    bool vazia()
    {
        return this->quantidade == 0;
    }

    std::string imprimir()
    {
        std::stringstream resultado;
        resultado << "{ ";
        int i = this->inicio;
        int count = 0;
        while (count < this->quantidade) {
            resultado << this->elementos[i] << " ";
            i = (i + 1) % this->capacidade;
            ++count;
        }
        resultado << "}";
        return resultado.str();
    }
};

#endif