#include "catch_amalgamated.hpp"
#include "ListaDuplamenteEncadeada.h"

TEST_CASE("Insere elementos que ainda não existem na lista, por isso retorna true") 
{
    ListaDuplamenteEncadeada lista;
    
    std::string v1[] = {"golf", "charlie", "alpha", "delta", "echo", "bravo", "fox", "india", "hotel", "juliet"};
                      
    // Neste laço, são inseridos elementos novos
    for(auto s : v1)
    {
        int tamanhoAntes = lista.tamanho();
        
        auto valorInserido = s;

        REQUIRE(lista.checarConsistencia() == OK);
                
        bool inseriu = lista.inserirOrdenado( valorInserido );

        REQUIRE(inseriu);

        REQUIRE(lista.checarConsistencia() == OK);

        int tamanhoApos = lista.tamanho();

        REQUIRE(tamanhoAntes+1 == tamanhoApos);
    }

    REQUIRE( lista.checarOrdenacao() == true );
}

TEST_CASE("Insere elementos que já existem na lista, por isso retorna false") 
{
    ListaDuplamenteEncadeada lista;
    
    std::string v1[] = {"golf", "charlie", "alpha", "delta", "echo", "bravo", "fox", "india", "hotel", "juliet"};
                      
    // Neste laço, são inseridos elementos novos
    for(auto s : v1)
    {
        lista.inserirOrdenado( s );
    }
    
    std::string v2[] = {"alpha",  "golf", "echo", "charlie", "bravo", "fox", "delta", "juliet", "india", "hotel"};

    // Neste laço, são inseridos elementos que já existem e, por isso, o método retorna falso
    for(auto s : v2)
    {
        int tamanhoAntes = lista.tamanho();
        
        auto valorInserido = s;

        REQUIRE(lista.checarConsistencia() == OK);
                
        bool inseriu = lista.inserirOrdenado( valorInserido );

        REQUIRE(inseriu == false);

        REQUIRE(lista.checarConsistencia() == OK);

        int tamanhoApos = lista.tamanho();

        REQUIRE(tamanhoAntes == tamanhoApos);
    }

    REQUIRE(lista.checarOrdenacao());
}

