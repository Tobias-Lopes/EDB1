#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "DadosEntrada4.h"
#include <vector>

using namespace std;

void merge(int arr[], int inicio1, int meio, int fim2){
    int inicio2 = meio + 1;
    int fim1 = meio;

    int i = inicio1, j = inicio2, k = 0;
    int tamanho = (fim2 - inicio1) + 1;

    int* tmp = new int[tamanho];

    while (i <= fim1 && j <= fim2)
    {
        if(arr[i] >= arr[j]){
            tmp[k] = arr[i];
            ++i;
        } else {
            tmp[k] = arr[j];
            ++j;
        }
        ++k;
    }

    while(i <= fim1){
        tmp[k] = arr[i];
        ++i;
        ++k;
    }

    while (j <= fim2)
    {
        tmp[k] = arr[j];
        ++j;
        ++k;
    }

    for (int x = inicio1, y=0; x <= fim2; ++x, ++y){
        arr[x] = tmp[y];
    }
    
    delete[] tmp;
}

void mergeSort(int arr[], int esquerda, int direita) 
{
    if(esquerda < direita){
        int meio = (esquerda + direita)/2;
        mergeSort(arr, esquerda, meio);
        mergeSort(arr, meio + 1, direita);
        merge(arr, esquerda, meio, direita);
    }
}

/**
 * Não altere o código abaixo. 
 * Sua solução deve ser implementada na função mergeSort.
*/
// Função auxiliar para verificar ordem decrescente 
bool estaDecrescente(int array[], int tamanho)
{
    for(int i = 0; i < tamanho-1; i++)
    {
        if( array[i] < array[i+1] )
        {
            return false;
        }
    }

    return true;
}

// Função auxiliar ao teste 
void CHECK_EQUALS(const vector<int>& entrada, const vector<int>& esperado) {
    vector<int> copia = entrada;
    int* arr = copia.data();
    mergeSort(arr, 0, copia.size() - 1);
    CHECK(copia == esperado);
}

//  Testes 
TEST_CASE("Casos básicos") {
    CHECK_EQUALS({}, {});
    CHECK_EQUALS({1}, {1});
    CHECK_EQUALS({2, 1}, {2, 1});
    CHECK_EQUALS({1, 2}, {2, 1});
}

TEST_CASE("Casos médios") {
    CHECK_EQUALS({3, 1, 4, 2}, {4, 3, 2, 1});
    CHECK_EQUALS({5, 3, 8, 4, 2}, {8, 5, 4, 3, 2});
    CHECK_EQUALS({10, 9, 8, 7, 6, 5}, {10, 9, 8, 7, 6, 5});
}

TEST_CASE("Casos com repetidos e negativos") {
    CHECK_EQUALS({1, 3, 3, 2, 2, 1}, {3, 3, 2, 2, 1, 1});
    CHECK_EQUALS({-3, -1, -2, 0}, {0, -1, -2, -3});
    CHECK_EQUALS({1000, -100, 500, 0, -1, 999}, {1000, 999, 500, 0, -1, -100});
}

TEST_CASE("Caso array pequeno e aleatório") 
{
    int t1 = sizeof(arrayPequeno) / sizeof(int);
    mergeSort(arrayPequeno, 0, t1 - 1);

    CHECK( estaDecrescente(arrayPequeno, t1) );
}

TEST_CASE("Caso array grande e aleatório") 
{
    int t1 = sizeof(arrayGrande) / sizeof(int);
    mergeSort(arrayGrande, 0, t1 - 1);

    CHECK( estaDecrescente(arrayGrande, t1) );
}
