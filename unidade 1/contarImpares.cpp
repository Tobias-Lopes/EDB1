#include <cassert>
#include <iostream>

int contarImpares(int array[], int tamanho)
{
    // Caso base: se não há elementos, não há ímpares
    if (tamanho == 0) return 0;

    // Verifica o último elemento e soma 1 se for ímpar
    int ultimoImpar = (array [tamanho - 1] % 2 != 0) ? 1 : 0;

    // Chamada recursiva com o resto do array
    return ultimoImpar + contarImpares(array, tamanho - 1);

}

int main(void)
{
    int array1[] = {1, 3, 5, 7, 9, 11};
    int tamanho1 = sizeof(array1) / sizeof(int);

    assert( contarImpares(array1, tamanho1) == 6);

    int array2[] = {0, 10, 30, 50, 70, 90, 110, 200};
    int tamanho2 = sizeof(array2) / sizeof(int);

    assert( contarImpares(array2, tamanho2) == 0);

    int array3[] = {1, 30, 5, 70, 9, 11};
    int tamanho3 = sizeof(array3) / sizeof(int);

    assert( contarImpares(array3, tamanho3) == 4);

    std::cout << "\n!!!! Q2 - Passou em todos os testes !!!! " << std::endl;

    return 0;
}