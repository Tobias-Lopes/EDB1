#ifndef __Fila__
#define __Fila__
#define __CHECK_INTEGRIDADE__ 1
#include <string>
#include <sstream>
#include <vector>
#include <stdexcept> // para overflow_error e underflow_error

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
    // Não altere
    Fila(int cap)
    {
        this->quantidade = 0;
        this->inicio = 0;
        this->fim = 0;
        this->capacidade = cap;
        this->elementos = new T[this->capacidade];
    }

    // Não altere
    ~Fila()
    {
        delete [] this->elementos;
    }

    int tamanho()
    {
        return this->quantidade;
    }

    T frente()
    {
        if (this->vazia())
            throw std::underflow_error("Fila vazia");
        return this->elementos[this->inicio];
    }

    void enfileirar(T elemento)
    {
        if (this->cheia())
            throw std::overflow_error("Fila cheia");

        this->elementos[this->fim] = elemento;
        this->fim = (this->fim + 1) % this->capacidade;
        this->quantidade++;
    }

    T desenfileirar()
    {
        if (this->vazia())
            throw std::underflow_error("Fila vazia");

        T valor = this->elementos[this->inicio];
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
        std::stringstream r; 
        r << "{ "; 
        for (int a = this->inicio, b = 0; b < this->quantidade; ++b, a = (a + 1) % this->capacidade)
            r << this->elementos[a] << " ";
        r << "}";
        return r.str();       
    }
};

#endif
