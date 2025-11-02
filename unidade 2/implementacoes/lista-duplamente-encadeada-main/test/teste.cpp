#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "ListaDuplamenteEncadeada.h"
#include <stdexcept> 

const std::string v1[] = {"G", "C", "A", "D", "E", "B", "F", "I", "H", "J"};
const std::string v2[] = {"A", "G", "E", "C", "B", "F", "D", "J", "I", "H"};

TEST_CASE("inserirInicio - insere elementos no início da lista e verifica ordem final") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) {
        int tamanhoAntes = lista.tamanho();
        REQUIRE(lista.inserirInicio(s));
        REQUIRE(lista.checarConsistencia() == OK);
        REQUIRE(lista.primeiroElemento() == s);
        REQUIRE(lista.tamanho() == tamanhoAntes + 1);
    }
    REQUIRE(lista.imprimir() == "J<->H<->I<->F<->B<->E<->D<->A<->C<->G");
}

TEST_CASE("inserirFim - insere elementos no final da lista e verifica ordem final") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) {
        int tamanhoAntes = lista.tamanho();
        REQUIRE(lista.inserirFim(s));
        REQUIRE(lista.checarConsistencia() == OK);
        REQUIRE(lista.ultimoElemento() == s);
        REQUIRE(lista.tamanho() == tamanhoAntes + 1);
    }
    REQUIRE(lista.imprimir() == "G<->C<->A<->D<->E<->B<->F<->I<->H<->J");
}

TEST_CASE("elementoNaPosicao - acessa elementos pelo índice correto") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) {
        REQUIRE(lista.inserirFim(s));
    }
    for(size_t i = 0; i < 10; ++i) {
        INFO("Verificando elemento na posição " << (i+1));
        REQUIRE(lista.elementoNaPosicao(i+1) == v1[i]);
    }
}

TEST_CASE("elementoNaPosicao - falha para índice inválido (std::out_of_range)") {
    ListaDuplamenteEncadeada lista;
    
    CHECK_THROWS_AS(lista.elementoNaPosicao(1), std::out_of_range);
    
    for(auto s : v1) { 
        lista.inserirFim(s); 
    }
    CHECK_THROWS_AS(lista.elementoNaPosicao(0), std::out_of_range);
    CHECK_THROWS_AS(lista.elementoNaPosicao(11), std::out_of_range);
}

TEST_CASE("inserir - insere elementos em posições alternadas") {
    ListaDuplamenteEncadeada lista;
    REQUIRE(lista.inserir(1, v1[0]));
    for(size_t i = 1; i < 10; ++i) {
        int pos = (i % 2 == 0) ? 2 : 1;
        int tamanhoAntes = lista.tamanho();
        REQUIRE(lista.checarConsistencia() == OK);
        REQUIRE(lista.inserir(pos, v1[i]));
        REQUIRE(lista.checarConsistencia() == OK);
        CAPTURE(pos);
        CAPTURE(v1[i]);
        REQUIRE(lista.elementoNaPosicao(pos) == v1[i]);
        REQUIRE(lista.tamanho() == tamanhoAntes + 1);
    }
}

TEST_CASE("inserir - falha para posição inválida (std::out_of_range)") {
    ListaDuplamenteEncadeada lista;
    CHECK_THROWS_AS(lista.inserir(2, "X"), std::out_of_range); // lista vazia
    CHECK(lista.inserir(1, "A"));
    CHECK_THROWS_AS(lista.inserir(0, "B"), std::out_of_range); // posição 0 inválida
    CHECK_THROWS_AS(lista.inserir(-1, "B"), std::out_of_range); // posição > tamanho+1 inválida
}

TEST_CASE("removerInicio - remove elementos do início e verifica vazio final") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) lista.inserirInicio(s);

    for(int i = 0; i < 10; ++i) {
        REQUIRE(lista.checarConsistencia() == OK);
        int tamanhoAntes = lista.tamanho();
        auto removido = lista.removerInicio();
        CAPTURE(i);
        CAPTURE(removido);
        REQUIRE(removido == v1[9-i]);
        REQUIRE(lista.tamanho() == tamanhoAntes - 1);
    }

    REQUIRE(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
}

TEST_CASE("removerInicio - falha em lista vazia (std::out_of_range)") {
    ListaDuplamenteEncadeada lista;
    CHECK_THROWS_AS(lista.removerInicio(), std::out_of_range);
}

TEST_CASE("removerFim - remove elementos do final e verifica vazio final") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) { 
        lista.inserirFim(s); 
    }

    for(int i = 0; i < 10; ++i) {
        REQUIRE(lista.checarConsistencia() == OK);
        int tamanhoAntes = lista.tamanho();
        auto removido = lista.removerFim();
        CAPTURE(i);
        CAPTURE(removido);
        REQUIRE(removido == v1[9-i]);
        REQUIRE(lista.tamanho() == tamanhoAntes - 1);
    }

    REQUIRE(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
}

TEST_CASE("removerFim - falha em lista vazia (std::out_of_range)") {
    ListaDuplamenteEncadeada lista;
    CHECK_THROWS_AS(lista.removerFim(), std::out_of_range);
}

TEST_CASE("remover - falha para posição inválida (std::out_of_range)") {
    ListaDuplamenteEncadeada lista;
    CHECK_THROWS_AS(lista.remover(1), std::out_of_range); // lista vazia
    lista.inserirInicio("A");
    CHECK_THROWS_AS(lista.remover(0), std::out_of_range);
    CHECK_THROWS_AS(lista.remover(2), std::out_of_range);
}

TEST_CASE("remover - remove elementos do meio até a lista ficar vazia") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) { 
        lista.inserirFim(s); 
    }

    while(lista.tamanho() > 0) {
        REQUIRE(lista.checarConsistencia() == OK);
        int tamanhoAntes = lista.tamanho();
        int indiceMeio = (tamanhoAntes / 2) + (tamanhoAntes % 2 == 0 ? 0 : 1);
        auto esperado = lista.elementoNaPosicao(indiceMeio);
        auto removido = lista.remover(indiceMeio);
        CAPTURE(indiceMeio);
        CAPTURE(esperado);
        CAPTURE(removido);
        REQUIRE(removido == esperado);
        REQUIRE(lista.tamanho() == tamanhoAntes - 1);
    }
    REQUIRE(lista.tamanho() == 0);
    REQUIRE(lista.imprimir() == "{}");
}

TEST_CASE("buscar - busca elementos existentes e inexistentes") {
    ListaDuplamenteEncadeada lista;
    for(auto s : v1) { 
        lista.inserirFim(s); 
    }

    for(int i = 0; i < 10; ++i) {
        REQUIRE(lista.checarConsistencia() == OK);
        CAPTURE(v1[i]);
        REQUIRE(lista.buscar(v1[i]) == i+1);
    }

    std::string inexistentes[] = {"0", "50", "100", "200"};
    for(auto s : inexistentes) {
        REQUIRE(lista.checarConsistencia() == OK);
        REQUIRE(lista.buscar(s) == -1);
    }
}

TEST_CASE("inserirAntes - inserir em diferentes posições e casos inválidos") {
    ListaDuplamenteEncadeada lista;

    // 1. Tentar inserirAntes numa lista vazia deve retornar false
    CHECK_FALSE(lista.inserirAntes("X", "Y"));
    REQUIRE(lista.vazia());
    REQUIRE(lista.checarConsistencia() == OK);

    // Preparar lista com 3 elementos: ["A", "B", "C"]
    CHECK(lista.inserirFim("A"));
    CHECK(lista.inserirFim("B"));
    CHECK(lista.inserirFim("C"));
    REQUIRE(lista.tamanho() == 3);
    REQUIRE(lista.imprimir() == "A<->B<->C");

    // 2. Tentar inserirAntes antes de um elemento que não existe deve retornar false
    CHECK_FALSE(lista.inserirAntes("X", "Y"));
    REQUIRE(lista.tamanho() == 3);
    REQUIRE(lista.imprimir() == "A<->B<->C");
    REQUIRE(lista.checarConsistencia() == OK);

    // 3. Inserir antes do primeiro nó ("A")
    CHECK(lista.inserirAntes("X", "A"));  // ["X", "A", "B", "C"]
    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "X<->A<->B<->C");
    REQUIRE(lista.checarConsistencia() == OK);

    // 4. Inserir antes do último nó ("C")
    CHECK(lista.inserirAntes("Y", "C"));  // ["X", "A", "B", "Y", "C"]
    REQUIRE(lista.tamanho() == 5);
    REQUIRE(lista.imprimir() == "X<->A<->B<->Y<->C");
    REQUIRE(lista.checarConsistencia() == OK);

    // 5. Inserir antes de um nó intermediário ("B")
    CHECK(lista.inserirAntes("Z", "B"));  // ["X", "A", "Z", "B", "Y", "C"]
    REQUIRE(lista.tamanho() == 6);
    REQUIRE(lista.imprimir() == "X<->A<->Z<->B<->Y<->C");
    REQUIRE(lista.checarConsistencia() == OK);

    // 6. Repetição do teste: tentar inserir antes de um elemento inexistente novamente
    CHECK_FALSE(lista.inserirAntes("Q", "W"));
    REQUIRE(lista.imprimir() == "X<->A<->Z<->B<->Y<->C");
    REQUIRE(lista.tamanho() == 6);
    REQUIRE(lista.checarConsistencia() == OK);
}

TEST_CASE("inserirOrdenado - inserir em diferentes posições") {
    ListaDuplamenteEncadeada lista;

    // 1. Inserir em lista vazia retorna true
    CHECK(lista.inserirOrdenado("M"));  // Lista: ["M"]
    REQUIRE(lista.tamanho() == 1);
    REQUIRE(lista.imprimir() == "M");
    REQUIRE(lista.primeiroElemento() == "M");
    REQUIRE(lista.ultimoElemento() == "M");
    REQUIRE(lista.checarConsistencia() == OK);

    // 2. Inserir no início da lista (valor maior) retorna true
    CHECK(lista.inserirOrdenado("Z"));  // Lista: ["Z", "M"]
    REQUIRE(lista.tamanho() == 2);
    REQUIRE(lista.imprimir() == "Z<->M");
    REQUIRE(lista.primeiroElemento() == "Z");
    REQUIRE(lista.checarConsistencia() == OK);

    // 3. Inserir no final da lista (valor menor) retorna true
    CHECK(lista.inserirOrdenado("A"));  // Lista: ["Z", "M", "A"]
    REQUIRE(lista.tamanho() == 3);
    REQUIRE(lista.imprimir() == "Z<->M<->A");
    REQUIRE(lista.ultimoElemento() == "A");
    REQUIRE(lista.checarConsistencia() == OK);

    // 4. Inserir no meio da lista retorna true
    CHECK(lista.inserirOrdenado("F"));  // Lista: ["Z", "M", "F", "A"]
    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "Z<->M<->F<->A");
    REQUIRE(lista.checarConsistencia() == OK);

    // 5. Inserir duplicata (valor já existente) retorna false e não altera a lista
    CHECK_FALSE(lista.inserirOrdenado("F"));  // Lista permanece igual
    REQUIRE(lista.tamanho() == 4);
    REQUIRE(lista.imprimir() == "Z<->M<->F<->A");
    REQUIRE(lista.checarConsistencia() == OK);
}