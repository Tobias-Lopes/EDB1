//
//  ListaEncadeada.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "../include/ListaEncadeada.h"
#include "../include/No.h"
#include <iostream>
#include <string>

ListaEncadeada::ListaEncadeada()
{
    this->inicio = nullptr;
    this->quantidade = 0;
}

ListaEncadeada::~ListaEncadeada()
{
    // To-Do
}

void ListaEncadeada::inserirNoInicio(std::string elemento)
{
    ++this->quantidade;
    auto novo = new No<std::string>(elemento);
    if( this->inicio == nullptr )
    {
        this->inicio = novo;
    }
    else
    {
        novo->setProximo( this->inicio );
        this->inicio = novo;
    }
}

void  ListaEncadeada::ordenar()
{
    for(auto n1 = this->getInicio(); n1->getProximo() != nullptr; n1 = n1->getProximo())
    {
        for(auto n2 = n1->getProximo(); n2 != nullptr; n2 = n2->getProximo())
        {
            if(n1->getValor() > n2->getValor())
            {
                auto aux = n1->getValor();
                n1->setValor(n2->getValor());
                n2->setValor(aux);
            }
        }    
    }
}

bool ListaEncadeada::vazia()
{
    return this->inicio == nullptr;
}

int ListaEncadeada::tamanho()
{
    return this->quantidade;
}

No<std::string>* ListaEncadeada::getInicio()
{
    return this->inicio;
}

void ListaEncadeada::imprimir()
{
    if(this->tamanho() > 0 )
    {
        auto no = this->getInicio();

        std::cout << "\t{";
        while(no != nullptr)
        {
            std::cout << no->getValor() << ", " ;
            no = no->getProximo();
        }
        std::cout << "}" << std::endl;
    }
}

bool ListaEncadeada::checarOrdenacao()
{
    if(this->tamanho() == 0 || this->tamanho() == 1)
    {
        return true;
    }

    for(auto no = this->inicio; no->getProximo() != nullptr; no = no->getProximo())
    {
        auto noProx = no->getProximo();

        if(no->getValor() > noProx->getValor())
        {
            return false;
        }
    }
    return true;
}