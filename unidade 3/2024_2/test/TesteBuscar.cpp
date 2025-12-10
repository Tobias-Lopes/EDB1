//
//  TesteBuscar.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define CATCH_CONFIG_MAIN
#include "../lib/catch2/catch_amalgamated.hpp"
#include "../header/TabelaHash.h"
#include "../header/TabelaHashTestHelper.h"
#include <iostream>

using namespace std;

TEST_CASE("Testando busca em TabelaHash", "[buscar]") {
    // Arrange
    TabelaHash tabela;  
    auto c1 = "CHAVE";
    auto v1 = "Valor1";
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    auto c2 = "VECHA";
    auto v2 = "Valor2";
    auto pos2 = TabelaHashTestHelper::hash(tabela, c2);

    auto c3 = "ECHAV";
    auto v3 = "Valor3";
    auto pos3 = TabelaHashTestHelper::hash(tabela, c3);

    REQUIRE( pos1 == pos2 ); // Assegurando que as chaves vão gerar colisão
    REQUIRE( pos2 == pos3 ); // Assegurando que as chaves vão gerar colisão
    
    SECTION("Buscar elemento existente sem colisão") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setQuantidade(tabela, 1);

        // Act
        auto resultado = tabela.buscar(c1);

        // Assert
        REQUIRE( resultado != nullptr );
        CHECK( resultado->first == c1 );
        CHECK( resultado->second == v1 );
    }

    SECTION("Buscar elemento existente com colisão") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, new pair<string, string>(c2, v2));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, new pair<string, string>(c3, v3));
        TabelaHashTestHelper::setQuantidade(tabela, 3);

        // Act
        auto resultado1 = tabela.buscar(c1);
        auto resultado2 = tabela.buscar(c2);
        auto resultado3 = tabela.buscar(c3);

        // Assert
        REQUIRE( resultado1 != nullptr );
        CHECK( resultado1->first == c1 );
        CHECK( resultado1->second == v1 );

        REQUIRE( resultado2 != nullptr );
        CHECK( resultado2->first == c2 );
        CHECK( resultado2->second == v2 );

        REQUIRE( resultado3 != nullptr );
        CHECK( resultado3->first == c3 );
        CHECK( resultado3->second == v3 );
    }

    SECTION("Buscar elemento inexistente") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, new pair<string, string>(c2, v2));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, new pair<string, string>(c3, v3));
        TabelaHashTestHelper::setQuantidade(tabela, 3);

        // Act
        auto resultado = tabela.buscar("chave_qualquer");

        // Assert
        REQUIRE( resultado == nullptr );
    }

    SECTION("Buscar elemento inexistente numa tabela cheia") {
        // Arrange
        TabelaHashTestHelper::encherTabela(tabela);

        // Act
        auto resultado = tabela.buscar("chave_qualquer");

        // Assert
        REQUIRE( resultado == nullptr );
    }

    SECTION("Buscar elemento após posição REMOVIDO") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, REMOVIDO);
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, REMOVIDO);
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, new pair<string, string>(c3, v3));
        TabelaHashTestHelper::setQuantidade(tabela, 1);

        // Act
        auto resultado = tabela.buscar(c3);

        // Assert
        REQUIRE( resultado != nullptr );
        CHECK( resultado->first == c3 );
        CHECK( resultado->second == v3 );
    }
}
