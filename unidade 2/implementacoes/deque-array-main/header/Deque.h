//
//  Deque.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __Deque__
#define __Deque__

#include <string>
#include <sstream>
#include <stdexcept>

template <typename T>
class Deque
{
private:
    T* elementos;
    int capacidade;
    int quantidade;
    int frente;
    int atras;

public:
    Deque(int cap)
    {
        this->capacidade = cap;
        this->elementos = new T[this->capacidade];
        this->quantidade = 0;
        this->frente = 0;
        this->atras = 0;
    }

    ~Deque()
    {
        delete[] this->elementos;
    }

    int tamanho() const
    {
        return this->quantidade;
    }

    bool cheia() const
    {
        return this->quantidade == this->capacidade;
    }

    bool vazia() const
    {
        return this->quantidade == 0;
    }

    void empurrarFrente(T elemento)
    {
        if(cheia()){
            throw std::overflow_error("Deque cheio.");
        }
        frente = (frente - 1 + capacidade) % capacidade;
        elementos[frente] = elemento;
        quantidade++;
    }

    void empurrarAtras(T elemento)
    {
        if(cheia()){
            throw std::overflow_error("Deque cheio.");
        }
        elementos[atras] = elemento;
        atras = (atras + 1) % capacidade;
        quantidade++;
    }

    T removerFrente()
    {
        if(vazia()){
            throw std::underflow_error("Deque vazio.");
        }

        T valor = elementos[frente];

        frente = (frente + 1) % capacidade;
        quantidade--;
        
        return valor;
    }

    T removerAtras()
    {
        if(vazia()){
            throw std::underflow_error("Deque vazio.");
        }

        atras = (atras - 1 + capacidade) % capacidade;

        T valor = elementos[atras];

        quantidade--;

        return valor;
    }

    T daFrente() const{
        if(vazia()){
            throw std::underflow_error("Deque vazio.");
        }
        return elementos[frente];
    }

    T deTras() const{
        if(vazia()){
            throw std::underflow_error("Deque vazio.");
        }
        int indice = (atras - 1 + capacidade) % capacidade;
        return elementos[indice];
    }


    std::string imprimir() const
    {
        std::stringstream resultado;
        resultado << "{ ";
        int i = this->frente;
        for (int cont = 0; cont < this->quantidade; ++cont)
        {
            resultado << this->elementos[i] << " ";
            i = (i + 1) % this->capacidade;
        }
        resultado << "}";
        return resultado.str();
    }
};

#endif