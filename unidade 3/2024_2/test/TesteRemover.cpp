//
//  TesteRemover.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define CATCH_CONFIG_MAIN
#include "../lib/catch2/catch_amalgamated.hpp"
#include "../header/TabelaHash.h"
#include "../header/TabelaHashTestHelper.h"

using namespace std;

TEST_CASE("Testando remoção em TabelaHash", "[remover]") {
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

    SECTION("Remover elemento existente sem colisão") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setQuantidade(tabela, 1);

        // Act
        auto removeu = tabela.remover(c1);

        // Assert
        auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);

        CHECK( removeu == true );
        CHECK( tabela.getQuantidade() == 0 );
        CHECK( elemento == REMOVIDO );
    }

    SECTION("Remover elemento existente com colisão") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, new pair<string, string>(c2, v2));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, new pair<string, string>(c3, v3));
        TabelaHashTestHelper::setQuantidade(tabela, 3);

        // Act
        auto removeu = tabela.remover(c3);

        // Assert
        auto elemento1 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
        auto elemento2 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 1);
        auto elemento3 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 2);

        CHECK( removeu == true );
        CHECK( tabela.getQuantidade() == 2 );

        REQUIRE( elemento1 != nullptr );
        CHECK( elemento1->first == c1 );
        CHECK( elemento1->second == v1 );

        REQUIRE( elemento2 != nullptr );
        CHECK( elemento2->first == c2 );
        CHECK( elemento2->second == v2 );

        CHECK( elemento3 == REMOVIDO );
    }

    SECTION("Remover sucessivamente todos elementos, o que força passar por posição REMOVIDO") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, new pair<string, string>(c2, v2));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, new pair<string, string>(c3, v3));
        TabelaHashTestHelper::setQuantidade(tabela, 3);

        // Act
        auto removeu1 = tabela.remover(c1);
        auto removeu2 = tabela.remover(c2);
        auto removeu3 = tabela.remover(c3);

        // Assert
        auto elemento1 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
        auto elemento2 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 1);
        auto elemento3 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 2);

        CHECK( removeu1 == true );
        CHECK( removeu2 == true );
        CHECK( removeu3 == true );
        CHECK( tabela.getQuantidade() == 0 );
        
        CHECK( elemento1 == REMOVIDO );
        CHECK( elemento2 == REMOVIDO );
        CHECK( elemento3 == REMOVIDO );
    }

    SECTION("Remover elemento inexistente") {
        // Arrange
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, new pair<string, string>(c1, v1));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, new pair<string, string>(c2, v2));
        TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, new pair<string, string>(c3, v3));
        TabelaHashTestHelper::setQuantidade(tabela, 3);

        // Act
        auto removeu = tabela.remover("chave_qualquer");

        // Assert
        CHECK( removeu == false );
        CHECK( tabela.getQuantidade() == 3 );
    }

     SECTION("Remover elemento inexistente numa tabela cheia") {
        // Arrange
       TabelaHashTestHelper::encherTabela(tabela);

       // Act
        auto removeu = tabela.remover("chave_qualquer");

        // Assert
        CHECK( removeu == false );
        CHECK( tabela.getQuantidade() == tabela.getTamanho() );
    }
}
