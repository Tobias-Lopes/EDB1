//
//  ListaDuplamenteEncadeada.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#ifndef __ListaDuplamenteEncadeada__
#define __ListaDuplamenteEncadeada__

#include "No.h"
#include <string>

typedef enum {
    OK ,
    CABECA_NULA,
    CAUDA_NULA,
    CABECA_ANTERIOR,
    CABECA_PROXIMO_NULO,
    CAUDA_PROXIMO,
    CAUDA_ANTERIOR_NULO,
    CABECA_CAUDA,
    ENCADEAMENTO_INCORRETO,
    QUANTIDADE_DIFERENTE 
} StatusDaLista ;

class ListaDuplamenteEncadeada {
private:
    No<std::string>* cabeca;
    No<std::string>* cauda;
    int quantidade;
    
public:
    ListaDuplamenteEncadeada(void);
    ~ListaDuplamenteEncadeada(void);

    int buscar(std::string) const;
    
    bool inserirAntes( std::string, std::string );
    bool inserirInicio(std::string);
    bool inserirFim(std::string);
    bool inserir(int, std::string);
    bool inserirOrdenado(std::string);

    std::string removerInicio(void);
    std::string removerFim(void);
    std::string remover(int);

    const std::string primeiroElemento() const;
    const std::string ultimoElemento() const;
    const std::string elementoNaPosicao(int) const;
    
    StatusDaLista checarConsistencia(void) const;
    
    std::string imprimir(void) const;
    
    bool vazia(void) const;
    int tamanho(void) const;
};

#endif 
