#include "palindromo.h"
#include <stack>
using namespace std;

bool ehPalindromo(string str)
{
    // pilha que armazenará caracteres do tipo char
    stack<char> pilha;

    // string auxiliar sem espaços
    string limpa = "";

    // empilha todos os caracteres, ignorando espaços
    for (char ch : str)
    {
        if (ch == ' ')
            continue;

        limpa += ch;
        pilha.push(ch);
    }

    // compara a string limpa com o conteúdo invertido na pilha
    for (char ch : limpa)
    {
        if (pilha.empty())
            return false;

        if (ch != pilha.top())
        {
            return false;
        }

        // remove o topo da pilha após comparar
        pilha.pop();
    }

    return true;
}
