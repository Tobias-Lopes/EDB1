//
//  TesteInserir.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define CATCH_CONFIG_MAIN
#include "../lib/catch2/catch_amalgamated.hpp"
#include "../header/TabelaHash.h"
#include "../header/TabelaHashTestHelper.h"

using namespace std;

SCENARIO("Testando método TabelaHash::inserir", "[inserir]")
{
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

    auto novoValor = "Novo";

    REQUIRE(pos1 == pos2); // Assegurando que as chaves vão gerar colisão
    REQUIRE(pos2 == pos3); // Assegurando que as chaves vão gerar colisão


    GIVEN("Uma tabela vazia")
    {
        WHEN("Um elemento é inserido")
        {
            bool inseriu = tabela.inserir(c1, v1);

            THEN("Elemento é inserido corretamente")
            {
                auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
                REQUIRE( elemento != nullptr );
                CHECK( elemento->first == c1 );
                CHECK( elemento->second == v1 );
            }
            AND_THEN("Quantidade é incrementada")
            {
                CHECK(tabela.getQuantidade() == 1);
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK(inseriu == true);
            }
        }

        WHEN("Dois elementos que colidem são inseridos")
        {
            auto inseriu1 = tabela.inserir(c1, v1);
            auto inseriu2 = tabela.inserir(c2, v2);

            THEN("Elementos são inseridos corretamente")
            {
                auto elemento1 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
                auto elemento2 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1+1);
                
                REQUIRE( elemento1 != nullptr );
                CHECK( elemento1->first == c1 );
                CHECK( elemento1->second == v1 );

                REQUIRE( elemento2 != nullptr );
                CHECK( elemento2->first == c2 );
                CHECK( elemento2->second == v2 );
            }
            AND_THEN("Quantidade é incrementada")
            {
                CHECK(tabela.getQuantidade() == 2);
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK(inseriu1 == true);
                CHECK(inseriu2 == true);
            }
        }

        WHEN("Duas inserções com mesma chave")
        {
            auto inseriu1 = tabela.inserir(c1, v1);
            auto atualizou = tabela.inserir(c1, novoValor); // atualiza

            THEN("Valor deve ser atualizado")
            {
                auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
                
                REQUIRE( elemento != nullptr );
                CHECK( elemento->first == c1 );
                CHECK( elemento->second == novoValor );
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK(inseriu1 == true);
                CHECK(atualizou == true);
            }
        }
    }

    GIVEN("Uma tabela já cheia")
    {
        TabelaHashTestHelper::encherTabela(tabela);

        WHEN("Inserir um elemento")
        {
            bool inserir = tabela.inserir(c1, v1);

            THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna false")
            {
                CHECK(inserir == false);
            }
        }

        WHEN("Atualizar um elemento")
        {
            auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, 0);
            bool atualizou = tabela.inserir(elemento->first, novoValor);

            THEN("Valor é atualizado")
            {
                CHECK(elemento->second == novoValor);
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK(atualizou == true);
            }
        }
    }

    GIVEN("Uma tabela com algumas posições REMOVIDO")
    {
        std::vector<std::pair<size_t, std::pair<std::string, std::string>*>> dados = {
            {pos1    , new std::pair<std::string, std::string>(c1, v1)},
            {pos1 + 1, REMOVIDO},
            {pos1 + 2, REMOVIDO},
            {pos1 + 3, new std::pair<std::string, std::string>(c2, v2)}
        };
        TabelaHashTestHelper::preencherTabela(tabela, dados);

        WHEN("Um elemento é inserido")
        {
            bool inseriu = tabela.inserir(c3, v3);
            THEN("Elemento é posicionado na primeira posição REMOVIDO")
            {
                auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1+1);
                CHECK( elemento != REMOVIDO );
                CHECK( elemento->first == c3 );
                CHECK( elemento->second == v3 );
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK(inseriu == true);
            }
        }

        WHEN("Um elemento após REMOVIDO é atualizado")
        {
            bool atualizou = tabela.inserir(c2, novoValor);
            THEN("Elemento é posicionado na primeira posição REMOVIDO")
            {
                auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1+3);
                CHECK( elemento != REMOVIDO );
                CHECK( elemento->first == c2 );
                CHECK( elemento->second == novoValor );
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK( atualizou == true );
            }
        }
    }

    GIVEN("Uma tabela com todas posições REMOVIDO"){
        TabelaHashTestHelper::encherTabelaComRemovido(tabela);

        WHEN("Um elemento é inserido")
        {
            bool inseriu = tabela.inserir(c3, v3);
            THEN("Elemento é posicionado na primeira posição REMOVIDO")
            {
                auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos3);
                CHECK( elemento != REMOVIDO );
                CHECK( elemento->first == c3 );
                CHECK( elemento->second == v3 );
            }
            AND_THEN("Não possui chaves repetidas")
            {
                CHECK(tabela.invariante() == true);
            }
            AND_THEN("Função retorna true")
            {
                CHECK(inseriu == true);
            }
        }
    }
}
