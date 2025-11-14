#define __CHECK_INTEGRIDADE__ 1
#include "../header/Lista.h"
#include <vector>
#include <iostream>
#include <stdexcept>
#include <sstream> // pra implementar o método imprimir ​

// Implemente aqui sua solução ​
int Lista::removerTodos(const std::string& valor)
{
    No* atual = this->primeiro;
    No* anterior = nullptr;
    int removidos = 0;

    while (atual != nullptr)
    {
        No* seguinte = atual->proximo;

        if (atual->valor == valor)
        {
            // Caso 1: remover o primeiro nó
            if (anterior == nullptr)
            {
                this->primeiro = seguinte;
            }
            else
            {
                anterior->proximo = seguinte;
            }

            // se o removido era o último, atualiza o ponteiro 'ultimo'
            if (seguinte == nullptr)
            {
                this->ultimo = anterior;
            }

            delete atual;
            removidos++;
        }
        else
        {
            anterior = atual;
        }

        atual = seguinte;
    }

    this->quantidade -= removidos;
    return removidos;
}




















































// Não alterar código daqui pra baixo ​
Lista::Lista(){this->quantidade=0;this->primeiro=nullptr;this->ultimo=nullptr;}Lista::~Lista(){auto a=this->primeiro;while(a!=nullptr){auto b=a;a=a->proximo;delete b;}this->primeiro=nullptr;this->ultimo=nullptr;this->quantidade=0;}bool Lista::inserirInicio(const std::string& x){No* n=new No(x);n->proximo=this->primeiro;this->primeiro=n;if(this->quantidade==0){this->ultimo=n;}this->quantidade++;return true;}const std::string& Lista::primeiroElemento()const{if(quantidade>0){return primeiro->valor;}else{throw std::out_of_range("A lista está vazia. Não é possível acessar o primeiro elemento.");}}const std::string& Lista::ultimoElemento()const{if(quantidade>0){return ultimo->valor;}else{throw std::out_of_range("A lista está vazia. Não é possível acessar o último elemento.");}}unsigned long Lista::tamanho()const{return quantidade;}std::string Lista::imprimir()const{std::ostringstream o;o<<"{";No* p=primeiro;while(p!=nullptr){o<<p->valor;if(p->proximo!=nullptr)o<<", ";p=p->proximo;}o<<"}";return o.str();}
