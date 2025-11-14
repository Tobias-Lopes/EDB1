#define CATCH_CONFIG_MAIN
#include "../lib/catch2/catch_amalgamated.hpp"
#include "../include/ListaEncadeada.h"
#include <iostream>

TEST_CASE("Ordenação da lista") 
{
    ListaEncadeada lista;
    
    std::string v1[] = {"golf", "charlie", "alpha", "delta", "echo", "bravo", "fox", "india", "hotel", "juliet",
                        "alpha", "echo", "bravo", "delta", "golf", "charlie", "juliet", "fox", "india", "hotel"};
                      
    for(auto s : v1)
    {
        lista.inserirNoInicio( s );
    }

    std::cout << "Lista antes de ordenar\n" ;
    lista.imprimir();

    lista.ordenar();

    std::cout << "Lista após ordenar\n" ;
    lista.imprimir();

    REQUIRE(lista.checarOrdenacao());
}