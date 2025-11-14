//
//  ListaEncadeada.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "../header/ListaEncadeada.h"
#include "../header/No.h"
#include <iostream>
#include <string>
#include <sstream>

ListaEncadeada::ListaEncadeada()
{
    this->inicio = nullptr;
}

ListaEncadeada::~ListaEncadeada()
{
    // To-Do
}

void ListaEncadeada::inserirNoInicio(int e){auto n = new No<int>(e);if( inicio == nullptr ) inicio = n;else { n->setProximo( inicio );inicio = n;}}

int ListaEncadeada::removerTodos(int val) 
{
    No<int>* atual = getInicio();
    No<int>* anterior = nullptr;

    int removidos = 0;

    while (atual)
    {
        No<int>* proximo = atual->getProximo();
        if(atual->getValor() == val){
            if(anterior == nullptr){
                setInicio(proximo);
            } else {
                anterior->setProximo(proximo);
            }

            delete atual;
            removidos++;
        } else {
            anterior = atual;
        }

        atual = proximo;
    }

    return removidos;
}

void ListaEncadeada::setInicio(No<int>* inicio) {
    this->inicio = inicio;
}


No<int>* ListaEncadeada::getInicio()
{
    return this->inicio;
}

std::string ListaEncadeada::imprimir()
{
    std::stringstream resultado;
    
    auto no = this->getInicio();

    while(no != nullptr)
    {
        resultado << no->getValor() << "->" ;
        no = no->getProximo();
    }
    resultado << "null";

    return resultado.str();
}

