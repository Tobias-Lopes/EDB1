//
//  TesteBuscar.cpp
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TabelaHash.h"
#include "TabelaHashTestHelper.h"
#include <iostream>

using namespace std;

// Definição global das variáveis usadas por diferentes casos de teste
const string c1 = "CHAVE";
const string v1 = "Valor1";
const string c2 = "VECHA";
const string v2 = "Valor2";
const string c3 = "ECHAV";
const string v3 = "Valor3";

// Teste para buscar um elemento existente sem colisão
TEST_CASE("Buscar elemento existente sem colisão") {
    TabelaHash tabela; 
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setQuantidade(tabela, 1);

    // Act
    auto resultado = tabela.buscar(c1);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(resultado == v1);
}

// Teste para buscar um elemento existente com colisão
TEST_CASE("Buscar elemento existente com colisão") {
    // Arrange
    TabelaHash tabela; 
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, c2, v2);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, c3, v3);
    TabelaHashTestHelper::setQuantidade(tabela, 3);

    // Act
    auto resultado1 = tabela.buscar(c1);
    auto resultado2 = tabela.buscar(c2);
    auto resultado3 = tabela.buscar(c3);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(resultado1 == v1);

    CHECK(resultado2 == v2);

    CHECK(resultado3 == v3);
}

// Teste para buscar um elemento inexistente
TEST_CASE("Buscar elemento inexistente") {
    // Arrange
    TabelaHash tabela; 
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, c2, v2);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, c3, v3);
    TabelaHashTestHelper::setQuantidade(tabela, 3);

    // Act
    auto resultado = tabela.buscar("chave_qualquer");

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    REQUIRE(resultado == std::nullopt);
}

// Teste para buscar um elemento inexistente numa tabela cheia
TEST_CASE("Buscar elemento inexistente numa tabela cheia") {
    // Arrange
    TabelaHash tabela; 
    TabelaHashTestHelper::preencherTabelaComOcupado(tabela);

    // Act
    auto resultado = tabela.buscar("chave_qualquer");

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    REQUIRE(resultado == std::nullopt);
}

// Teste para buscar um elemento após posição REMOVIDO
TEST_CASE("Buscar elemento após posição REMOVIDO") {
    // Arrange
    TabelaHash tabela; 
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    Elemento e1;
    e1.estado = Estado::REMOVIDO;

    Elemento e2;
    e2.estado = Estado::REMOVIDO;

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, e1);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, e2);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, c3, v3);
    TabelaHashTestHelper::setQuantidade(tabela, 1);

    // Act
    auto resultado = tabela.buscar(c3);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(resultado == v3);
}
