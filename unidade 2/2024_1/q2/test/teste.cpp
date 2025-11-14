#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../header/ListaEncadeada.h"
#include <iostream>

using namespace Catch::Matchers;

TEST_CASE("Lista vazia", "RemoverTodos") 
{
    ListaEncadeada lista;

    int contagem = lista.removerTodos(7);

    std::string resultadoEsperado = "null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 0 );
}

TEST_CASE("Lista com um só elemento, mas não o removendo", "RemoverTodos") 
{
    ListaEncadeada lista;

    lista.inserirNoInicio(1);

    int contagem = lista.removerTodos(2);

    std::string resultadoEsperado = "1->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 0 );
}

TEST_CASE("Lista com um só elemento, removendo-o", "RemoverTodos") 
{
    ListaEncadeada lista;

    lista.inserirNoInicio(1);

    int contagem = lista.removerTodos(1);

    std::string resultadoEsperado = "null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 1 );
}

TEST_CASE("Lista sem elementos repetidos, removendo o primeiro", "RemoverTodos") 
{
    ListaEncadeada lista;
                        
    for(auto s : {10, 8, 6, 4}) lista.inserirNoInicio( s );

    int contagem = lista.removerTodos(4);

    std::string resultadoEsperado = "6->8->10->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 1 );
}

TEST_CASE("Lista sem elementos repetidos, removendo o último", "RemoverTodos") 
{
    ListaEncadeada lista;
                        
    for(auto s : {10, 8, 6, 4}) lista.inserirNoInicio( s );

    int contagem = lista.removerTodos(10);

    std::string resultadoEsperado = "4->6->8->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 1 );
}

TEST_CASE("Lista sem elementos repetidos, removendo do meio", "RemoverTodos") 
{
    ListaEncadeada lista;
                        
    for(auto s : {10, 8, 6, 4}) lista.inserirNoInicio( s );

    int contagem = lista.removerTodos(8);

    std::string resultadoEsperado = "4->6->10->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 1 );
}

TEST_CASE("Lista com elementos repetidos - Removendo primeiro", "RemoverTodos") 
{
    ListaEncadeada lista;
                       
    for(auto s : {10, 8, 6, 10, 6, 4, 6}) lista.inserirNoInicio( s );

    int contagem = lista.removerTodos(10);

    std::string resultadoEsperado = "6->4->6->6->8->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 2 );
}

TEST_CASE("Lista com elementos repetidos - Removendo último", "RemoverTodos") 
{
    ListaEncadeada lista; 
                       
    for(auto s : {10, 8, 6, 10, 6, 4, 6}) lista.inserirNoInicio( s );

    int contagem = lista.removerTodos(6);

    std::string resultadoEsperado = "4->10->8->10->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
    REQUIRE( contagem == 3 );
}

TEST_CASE("Lista com elementos repetidos - Removendo do meio", "RemoverTodos") 
{
    ListaEncadeada lista;
                       
    for(auto s : {10, 8, 6, 10, 6, 4, 6}) lista.inserirNoInicio( s );

    int contagem = lista.removerTodos(8);

    std::string resultadoEsperado = "6->4->6->10->6->10->null";
    std::string resultadoRecebido = lista.imprimir();

    REQUIRE( contagem == 1 );
    REQUIRE_THAT( resultadoRecebido, Equals(resultadoEsperado) );
}
