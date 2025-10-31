#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"


/**
 * @brief Função para contar a quantidade de dígitos ímpares.
 *
 * @param N O número natural a ser processado.
 * @return Um inteiro com a quantidade de dígitos ímpares.
 */
int contarDigitosImpares(int N) {
    if(N == 0) return 0;

    int ultimo = ((N%10) % 2 != 0) ? 1 : 0;

    return ultimo + contarDigitosImpares(N/10);
}

TEST_CASE("Contar Dígitos Pares e Ímpares - Testes") {
    auto resultado = contarDigitosImpares(0);
    CHECK(resultado == 0); 

    resultado = contarDigitosImpares(9);
    CHECK(resultado == 1); 

    resultado = contarDigitosImpares(111111);
    CHECK(resultado == 6); 

    resultado = contarDigitosImpares(24680);
    CHECK(resultado == 0); 

    resultado = contarDigitosImpares(1267774613);
    CHECK(resultado == 6); 

    resultado = contarDigitosImpares(1234567890);
    CHECK(resultado == 5); 

    resultado = contarDigitosImpares(987654321);
    CHECK(resultado == 5); 
}
