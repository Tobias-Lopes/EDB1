//
//  main.cpp
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#include "../header/TabelaHash.h"

int main(void) 
{
    TabelaHash tabela;

    tabela.inserir("chave", "Valor");
    tabela.inserir("hcave", "Valor");
    tabela.inserir("cahve", "Valor");

    tabela.remover("hcave");

    tabela.imprimir();

    return 0;
}
