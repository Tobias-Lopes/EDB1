#include "../lib/catch2/catch_amalgamated.hpp"
#include "../include/ListaDuplamenteEncadeada.h"

TEST_CASE("Inserir ordenado") 
{
    ListaDuplamenteEncadeada lista;
    
    std::string v1[] = {"golf", "charlie", "alpha", "delta", "echo", "bravo", "fox", "india", "hotel", "juliet"};
                      
    // Neste laço, são inseridos elementos novos
    for(auto s : v1)
    {
        int tamanhoAntes = lista.tamanho();
        
        auto valorInserido = s;

        CHECK(lista.checarConsistencia() == OK);
                
        bool inseriu = lista.inserirOrdenado( valorInserido );

        CHECK(inseriu);

        CHECK(lista.checarConsistencia() == OK);
        
        REQUIRE(lista.checarOrdenacao());

        int tamanhoApos = lista.tamanho();

        CHECK(tamanhoAntes+1 == tamanhoApos);
    }
    
    std::string v2[] = {"alpha",  "golf", "echo", "charlie", "bravo", "fox", "delta", "juliet", "india", "hotel"};

    // Neste laço, são inseridos elementos que já existem e, por isso, o método retorna falso
    for(auto s : v2)
    {
        int tamanhoAntes = lista.tamanho();
        
        auto valorInserido = s;

        CHECK(lista.checarConsistencia() == OK);
                
        bool inseriu = lista.inserirOrdenado( valorInserido );

        CHECK(inseriu == false);

        CHECK(lista.checarConsistencia() == OK);
        
        REQUIRE(lista.checarOrdenacao());

        int tamanhoApos = lista.tamanho();

        CHECK(tamanhoAntes == tamanhoApos);
    }
}
