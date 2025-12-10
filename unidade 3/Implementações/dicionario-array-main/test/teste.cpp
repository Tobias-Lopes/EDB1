#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Dicionario.h"

// Teste do estado inicial do Dicionario (Construtor)
TEST_CASE("Dicionario - Estado Inicial") {
    Dicionario<std::string, std::string> dic(3);
    CHECK(dic.tamanho() == 0);
}

TEST_CASE("Dicionario - Inserir chave nova") {
    Dicionario<std::string, std::string> dic(2);

    CHECK(dic.tamanho() == 0);

    CHECK(dic.inserir("k1", "v1") == true);
    CHECK(dic.tamanho() == 1);
}

TEST_CASE("Dicionario - Inserir chave já existente atualiza valor") {
    Dicionario<std::string, std::string> dic(2);
    dic.inserir("k1", "v1");

    CHECK(dic.tamanho() == 1);

    // Inserir novamente com novo valor
    CHECK(dic.inserir("k1", "novoV1") == true);
    CHECK(dic.tamanho() == 1);  // Não aumenta

    auto retorno = dic.buscar("k1");
    CHECK(retorno.has_value());
    CHECK(retorno.value() == "novoV1");
}

TEST_CASE("Dicionario - Inserir em dicionário cheio deve lançar exceção") {
    Dicionario<std::string, std::string> dic(2);
    dic.inserir("k1", "v1");
    dic.inserir("k2", "v2");

    // Agora dicionário está cheio: inserir chave nova deve falhar
    CHECK_THROWS_AS(dic.inserir("k3", "v3"), std::overflow_error);

    // Mas atualizar chave existente não deve lançar
    CHECK_NOTHROW(dic.inserir("k1", "atualizado"));
}

TEST_CASE("Dicionario - Remover chave existente") {
    Dicionario<std::string, std::string> dic(3);
    dic.inserir("k1", "v1");
    dic.inserir("k2", "v2");

    CHECK(dic.tamanho() == 2);

    CHECK(dic.remover("k1") == true);
    CHECK(dic.tamanho() == 1);
    CHECK(dic.buscar("k1") == std::nullopt);
}

TEST_CASE("Dicionario - Remover chave inexistente") {
    Dicionario<std::string, std::string> dic(2);
    dic.inserir("a", "1");

    CHECK(dic.remover("b") == false);
    CHECK(dic.tamanho() == 1);
}

TEST_CASE("Dicionario - Remover de dicionário vazio deve lançar exceção") {
    Dicionario<std::string, std::string> dic(2);

    // Dicionário vazio: qualquer remoção lança exceção
    CHECK_THROWS_AS(dic.remover("qualquer"), std::underflow_error);
}

TEST_CASE("Dicionario - Buscar com chave presente") {
    Dicionario<std::string, std::string> dic(3);
    dic.inserir("k1", "v1");
    dic.inserir("k2", "v2");

    auto resultado1 = dic.buscar("k1");
    CHECK(resultado1.has_value());
    CHECK(resultado1.value() == "v1");

    auto resultado2 = dic.buscar("k2");
    CHECK(resultado2.has_value());
    CHECK(resultado2.value() == "v2");
}

TEST_CASE("Dicionario - Buscar com chave ausente") {
    Dicionario<std::string, std::string> dic(3);
    dic.inserir("k1", "v1");

    auto resultado = dic.buscar("inexistente");
    CHECK_FALSE(resultado.has_value());
}

TEST_CASE("Dicionario - Buscar em dicionário vazio") {
    Dicionario<std::string, std::string> dic(3);

    auto resultado = dic.buscar("qualquer");
    CHECK_FALSE(resultado.has_value());
}

TEST_CASE("Dicionario - Inserir chave e atualizar valor") {
    Dicionario<std::string, std::string> dic(2);

    // Primeira inserção da chave "k1"
    CHECK(dic.inserir("k1", "v1") == true);
    CHECK(dic.tamanho() == 1);

    // Buscar para confirmar valor inicial
    auto val1 = dic.buscar("k1");
    CHECK(val1.has_value());
    CHECK(val1.value() == "v1");

    // Inserir novamente mesma chave com novo valor
    CHECK(dic.inserir("k1", "novo_v1") == true);
    CHECK(dic.tamanho() == 1); // Tamanho não muda

    // Buscar novamente para confirmar atualização
    auto val2 = dic.buscar("k1");
    CHECK(val2.has_value());
    CHECK(val2.value() == "novo_v1");
}
