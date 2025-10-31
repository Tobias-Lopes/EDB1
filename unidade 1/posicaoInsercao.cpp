#include <iostream>
#include <cassert>

using namespace std;

int posicaoInsercao(int array[], int esquerda, int direita, int alvo) {
    if (esquerda > direita) {
        return esquerda; // caso base: posição onde o alvo deve ser inserido
    }

    int meio = (esquerda + direita) / 2;

    if (array[meio] > alvo) {
        return posicaoInsercao(array, esquerda, meio - 1, alvo);
    } else {
        return posicaoInsercao(array, meio + 1, direita, alvo);
    }
}


int main(void)
{
    cout << "\t---\tQuestão 03: Início\t---" << endl;

    int array1[] = {1, 3, 5, 7};
    int tam = sizeof(array1) / sizeof(int);

    assert( posicaoInsercao(array1, 0, tam-1, 0) == 0);
    assert( posicaoInsercao(array1, 0, tam-1, 2) == 1);
    assert( posicaoInsercao(array1, 0, tam-1, 4) == 2);
    assert( posicaoInsercao(array1, 0, tam-1, 6) == 3);
    assert( posicaoInsercao(array1, 0, tam-1, 8) == 4);

    cout << "\t---\tQuestão 03: Passou em todos os testes\t---" << endl;
    
    return 0;
}
