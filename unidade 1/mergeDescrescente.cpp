#include <iostream>
#include <cassert>
#include "DadosEntrada1.h"

using namespace std;

void merge(int[], int, int, int);
void mergeSort(int[], int, int);
bool estaDecrescente(int [], int);

int main(void)
{
    cout << "\t---\tQuestão 02: Início\t---" << endl;

    int tamanho = 1000000;

    mergeSort(arrayAleatorio, 0, tamanho-1); // arrayAleatorio é definido dentro de DadosEntrada.h

    assert( estaDecrescente(arrayAleatorio, tamanho) );

    mergeSort(arrayCrescente, 0, tamanho-1); // arrayCrescente é definido dentro de DadosEntrada.h

    assert( estaDecrescente(arrayCrescente, tamanho) );
    

    cout << "\t---\tQuestão 02: Passou em todos os testes\t---" << endl;

    return 0;
}

void merge(int array[], int inicio1, int meio, int fim2)
{
    int inicio2 = meio + 1;
    int fim1 = meio;
    int i = inicio1, j = inicio2, k=0;
    int tamanho = (fim2 - inicio1) + 1;

    int* tmp = new int[tamanho];

    while(i <= fim1 && j <= fim2) {
        if(array[i] >= array[j]) {
            tmp[k] = array[i];
            ++i;
        } else {
            tmp[k] = array[j];
            ++j;
        }
        ++k;
    }

    while (i <= fim1)
    {
        tmp[k] = array[i];
        ++i;
        ++k;
    }

    while (j <= fim2){
        tmp[k] = array[j];
        ++j;
        ++k;
    }

    for (int x = inicio1, y=0; x <= fim2; ++x, ++y){
        array[x] = tmp[y];
    }
    
    delete[] tmp;
}

void mergeSort(int array[], int esquerda, int direita)
{
    if(esquerda < direita)
    {
        int meio = (esquerda + direita) / 2;
        mergeSort(array, esquerda, meio);
        mergeSort(array, meio+1, direita);
        merge(array, esquerda, meio, direita);
    }
}

/**
 * Esta é uma função auxiliar que eu criei para poder testar se sua ordenação está correta. Não altere-a.
*/
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