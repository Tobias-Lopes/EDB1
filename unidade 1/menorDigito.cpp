#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

int menorDigito(int N)
{
    if(N<10) return N;

    int ultimo = N%10;

    int menorResto = menorDigito(N/10);

    return (ultimo < menorResto) ? ultimo : menorResto;
}

TEST_CASE("Questão 1 - Testes da função menorDigito") 
{
    CHECK( menorDigito(0) == 0);
    CHECK( menorDigito(9) == 9);
    CHECK( menorDigito(10) == 0);
    CHECK( menorDigito(19) == 1);
    CHECK( menorDigito(879) == 7);
    CHECK( menorDigito(729) == 2);
    CHECK( menorDigito(8379) == 3);
    CHECK( menorDigito(8729) == 2);
    CHECK( menorDigito(23456178) == 1);
    CHECK( menorDigito(23145678) == 1);
}
