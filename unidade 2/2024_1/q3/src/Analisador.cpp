//
//  ListaEncadeada.cpp
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#include "../header/Analisador.h"
#include <string>
#include <stack>

using namespace std;

Analisador::Analisador()
{
}

bool Analisador::eBemFormada(std::string str)
{
    // como declarar a pilha que armazenará caracteres do tipo char
    stack<char> pilha;

    // como iterar os carecteres da string de entrada
    for(char ch : str)
    {
        if(ch == '(' || ch == '[' || ch == '{'){
            pilha.push(ch);
        } else if(ch == ')' || ch == ']' || ch == '}'){
            if(pilha.empty())
            {
                return false;
            }
            
            char aux = pilha.top();
            pilha.pop();

            if ((ch == ')' && aux != '(') ||
                (ch == ']' && aux != '[') ||
                (ch == '}' && aux != '{'))
            {
                return false;
            }

        }

    }
    
    return pilha.empty();
}
