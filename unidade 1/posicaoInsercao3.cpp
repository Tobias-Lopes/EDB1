#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

using namespace std;

int posicaoInsercao(int array[], int esquerda, int direita, int alvo) 
{
    if(esquerda > direita) return esquerda;

    int meio = (esquerda + direita)/2;

    if(array[meio] > alvo){
        return posicaoInsercao(array, esquerda, meio - 1, alvo);
    } else {
        return posicaoInsercao(array, meio + 1, direita, alvo);
    }
}

TEST_CASE("Questão 3 - Testes da função posicaoInsercao") 
{
    int array1[] = {1, 3, 5, 7};
    int tam = sizeof(array1) / sizeof(int);

    CHECK( posicaoInsercao(array1, 0, tam-1, 0) == 0);
    CHECK( posicaoInsercao(array1, 0, tam-1, 2) == 1);
    CHECK( posicaoInsercao(array1, 0, tam-1, 4) == 2);
    CHECK( posicaoInsercao(array1, 0, tam-1, 6) == 3);
    CHECK( posicaoInsercao(array1, 0, tam-1, 8) == 4);
}
