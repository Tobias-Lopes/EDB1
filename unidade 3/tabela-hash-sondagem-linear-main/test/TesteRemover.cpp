//
//  TesteRemover.cpp
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TabelaHash.h"
#include "TabelaHashTestHelper.h"

using namespace std;

// Variáveis globais reusadas pelos casos de teste
const string c1 = "CHAVE";
const string v1 = "Valor1";

const string c2 = "VECHA";
const string v2 = "Valor2";
    
const string c3 = "ECHAV";
const string v3 = "Valor3";
    

// Teste para remover um elemento existente sem colisão
TEST_CASE("Remover elemento existente sem colisão") {
    // Arrange
    TabelaHash tabela;  
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setQuantidade(tabela, 1);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act
    auto removeu = tabela.remover(c1);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    auto elemento = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);

    CHECK(removeu == true);
    CHECK(tabela.tamanho() == 0);
    CHECK(elemento.estado == Estado::REMOVIDO);
}

// Teste para remover um elemento existente com colisão
TEST_CASE("Remover elemento existente com colisão") {
    // Arrange
    TabelaHash tabela;  
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    auto pos2 = TabelaHashTestHelper::hash(tabela, c2);
    auto pos3 = TabelaHashTestHelper::hash(tabela, c3);

    REQUIRE(pos1 == pos2); // Assegurando que as chaves vão gerar colisão
    REQUIRE(pos2 == pos3); // Assegurando que as chaves vão gerar colisão

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, c2, v2);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, c3, v3);
    TabelaHashTestHelper::setQuantidade(tabela, 3);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act
    auto removeu = tabela.remover(c3);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    auto elemento1 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
    auto elemento2 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 1);
    auto elemento3 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 2);

    CHECK(removeu == true);
    CHECK(tabela.tamanho() == 2);

    REQUIRE(elemento1.estado != Estado::REMOVIDO);
    CHECK(elemento1.chave == c1);
    CHECK(elemento1.valor == v1);

    REQUIRE(elemento2.estado != Estado::REMOVIDO);
    CHECK(elemento2.chave == c2);
    CHECK(elemento2.valor == v2);

    CHECK(elemento3.estado == Estado::REMOVIDO);
}

TEST_CASE("Remover sucessivamente todos os elementos, forçando posições Estado::REMOVIDO") {
    // Arrange
    TabelaHash tabela;  
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    auto pos2 = TabelaHashTestHelper::hash(tabela, c2);
    auto pos3 = TabelaHashTestHelper::hash(tabela, c3);

    REQUIRE(pos1 == pos2); // Assegurando que as chaves vão gerar colisão
    REQUIRE(pos2 == pos3); // Assegurando que as chaves vão gerar colisão

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, c2, v2);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, c3, v3);
    TabelaHashTestHelper::setQuantidade(tabela, 3);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act
    auto removeu1 = tabela.remover(c1);
    auto removeu2 = tabela.remover(c2);
    auto removeu3 = tabela.remover(c3);

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    auto elemento1 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1);
    auto elemento2 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 1);
    auto elemento3 = TabelaHashTestHelper::getElementoNaPosicao(tabela, pos1 + 2);

    CHECK(removeu1 == true);
    CHECK(removeu2 == true);
    CHECK(removeu3 == true);
    CHECK(tabela.tamanho() == 0);
    
    CHECK(elemento1.estado == Estado::REMOVIDO);
    CHECK(elemento2.estado == Estado::REMOVIDO);
    CHECK(elemento3.estado == Estado::REMOVIDO);
}

// Teste para remover um elemento inexistente
TEST_CASE("Remover elemento inexistente") {
    // Arrange
    TabelaHash tabela;  
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    auto pos2 = TabelaHashTestHelper::hash(tabela, c2);
    auto pos3 = TabelaHashTestHelper::hash(tabela, c3);

    REQUIRE(pos1 == pos2); // Assegurando que as chaves vão gerar colisão
    REQUIRE(pos2 == pos3); // Assegurando que as chaves vão gerar colisão

    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1, c1, v1);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 1, c2, v2);
    TabelaHashTestHelper::setElementoNaPosicao(tabela, pos1 + 2, c3, v3);
    TabelaHashTestHelper::setQuantidade(tabela, 3);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);

    // Act
    auto removeu = tabela.remover("chave_qualquer");

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(removeu == false);
    CHECK(tabela.tamanho() == 3);
}

// Teste para remover um elemento inexistente em uma tabela cheia
TEST_CASE("Remover elemento inexistente numa tabela cheia") {
    // Arrange
    TabelaHash tabela;  
    auto pos1 = TabelaHashTestHelper::hash(tabela, c1);
    auto pos2 = TabelaHashTestHelper::hash(tabela, c2);
    auto pos3 = TabelaHashTestHelper::hash(tabela, c3);

    REQUIRE(pos1 == pos2); // Assegurando que as chaves vão gerar colisão
    REQUIRE(pos2 == pos3); // Assegurando que as chaves vão gerar colisão

    // Enche a tabela
    TabelaHashTestHelper::preencherTabelaComOcupado(tabela);
    REQUIRE(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    REQUIRE(tabela.cheia());

    // Act
    auto removeu = tabela.remover("chave_qualquer");

    // Assert
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
    CHECK(removeu == false);
    CHECK(tabela.cheia());
}
