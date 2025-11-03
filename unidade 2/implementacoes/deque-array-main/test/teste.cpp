#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "Deque.h"
#include <string>

TEST_CASE("Deque - Tamanho inicial deve ser zero") {
    Deque<int> deque(5);
    CHECK(deque.tamanho() == 0);
    CHECK(deque.vazia());
    CHECK_FALSE(deque.cheia());
}

TEST_CASE("Deque - Empurrar elementos atrás até a capacidade máxima (back)") {
    Deque<int> deque(3);
    deque.empurrarAtras(10); // frente { 10 } trás
    deque.empurrarAtras(20); // frente { 10 20 } trás
    deque.empurrarAtras(30); // frente { 10 20 30 } trás
    CHECK(deque.tamanho() == 3);
    CHECK(deque.cheia());
    CHECK(deque.daFrente() == 10);
    CHECK(deque.deTras() == 30);
}

TEST_CASE("Deque - Empurrar elementos atrás além da capacidade deve lançar exceção") {
    Deque<int> deque(2);
    deque.empurrarAtras(1);
    deque.empurrarAtras(2);
    CHECK_THROWS_AS(deque.empurrarAtras(3), std::overflow_error);
}

TEST_CASE("Deque - Empurrar elementos na frente até a capacidade máxima") {
    Deque<int> deque(3);
    deque.empurrarFrente(10); // {10}
    deque.empurrarFrente(20); // {20, 10}
    deque.empurrarFrente(30); // {30, 20, 10}
    CHECK(deque.tamanho() == 3);
    CHECK(deque.cheia());
    CHECK(deque.daFrente() == 30);
    CHECK(deque.deTras() == 10);
}

TEST_CASE("Deque - Empurrar elementos na frente além da capacidade deve lançar exceção") {
    Deque<int> deque(2);
    deque.empurrarFrente(1);
    deque.empurrarFrente(2);
    CHECK_THROWS_AS(deque.empurrarFrente(3), std::overflow_error);
}

TEST_CASE("Deque - Remover de trás e da frente na ordem correta") {
    Deque<int> deque(4);
    deque.empurrarAtras(5);    // {5}
    deque.empurrarFrente(10);  // {10, 5}
    deque.empurrarAtras(15);    // {10, 5, 15}
    deque.empurrarFrente(20);  // {20, 10, 5, 15}
    CHECK(deque.tamanho() == 4);

    // Ordem de remoção: front: 20, front: 10, back: 15, back: 5
    CHECK(deque.removerFrente() == 20);
    CHECK(deque.tamanho() == 3);
    CHECK(deque.removerFrente() == 10);
    CHECK(deque.tamanho() == 2);
    CHECK(deque.removerAtras() == 15);
    CHECK(deque.tamanho() == 1);
    CHECK(deque.removerAtras() == 5);
    CHECK(deque.vazia());
}

TEST_CASE("Deque - Remover de deque vazio deve lançar exceção") {
    Deque<int> deque(2);
    CHECK_THROWS_AS(deque.removerFrente(), std::underflow_error);
    CHECK_THROWS_AS(deque.removerAtras(), std::underflow_error);
}

TEST_CASE("Deque - Acessar frente e tras de deque vazio deve lançar exceção") {
    Deque<std::string> deque(2);
    CHECK_THROWS_AS(deque.daFrente(), std::underflow_error);
    CHECK_THROWS_AS(deque.deTras(), std::underflow_error);
}

TEST_CASE("Deque - Comportamento circular ao empurrar e remover (back e front)") {
    Deque<int> deque(3);
    deque.empurrarAtras(1);   // {1}
    deque.empurrarAtras(2);   // {1, 2}
    deque.empurrarAtras(3);   // {1, 2, 3}
    CHECK(deque.cheia());

    // Remove um do início e adiciona no fim para forçar wrap-around
    CHECK(deque.removerFrente() == 1); // {2, 3}
    deque.empurrarAtras(4);              // {2, 3, 4}

    CHECK(deque.daFrente() == 2);
    CHECK(deque.deTras() == 4);

    // Remove do fim e empurra no início para wrap-around inverso
    CHECK(deque.removerAtras() == 4);    // {2, 3}
    deque.empurrarFrente(5);           // {5, 2, 3}

    CHECK(deque.daFrente() == 5);
    CHECK(deque.deTras() == 3);

    // Esvaziar completamente
    CHECK(deque.removerFrente() == 5);
    CHECK(deque.removerFrente() == 2);
    CHECK(deque.removerFrente() == 3);
    CHECK(deque.vazia());
}

TEST_CASE("Deque - Impressão do deque deve refletir a ordem dos elementos") {
    Deque<int> deque(5);
    deque.empurrarAtras(100);     // {100}
    deque.empurrarAtras(200);     // {100, 200}
    deque.empurrarFrente(50);   // {50, 100, 200}
    deque.empurrarAtras(300);     // {50, 100, 200, 300}
    CHECK(deque.imprimir() == "{ 50 100 200 300 }");

    deque.removerFrente();      // {100, 200, 300}
    deque.empurrarFrente(25);   // {25, 100, 200, 300}
    CHECK(deque.imprimir() == "{ 25 100 200 300 }");
}

TEST_CASE("Deque - Teste com diferentes tipos (int, double, string)") {
    Deque<double> dequeD(3);
    dequeD.empurrarAtras(3.14);
    dequeD.empurrarFrente(2.71);
    CHECK(dequeD.daFrente() == doctest::Approx(2.71));
    CHECK(dequeD.deTras() == doctest::Approx(3.14));

    Deque<std::string> dequeS(3);
    dequeS.empurrarAtras("foo");
    dequeS.empurrarFrente("bar");
    CHECK(dequeS.daFrente() == "bar");
    CHECK(dequeS.deTras() == "foo");
}