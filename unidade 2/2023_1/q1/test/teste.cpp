#include "../lib/catch2/catch_amalgamated.hpp"
#include "../include/Expressao.h"
#include <string>

TEST_CASE("Resolver Expressão - Adição Simples") 
{
    std::vector<std::string> entrada = {"1", "0", "+"};
    
    CHECK(resolverExpressao(entrada) == 1);

    entrada = {"0", "1", "+"};
    
    CHECK(resolverExpressao(entrada) == 1);

    entrada = {"1", "1", "+"};
    
    CHECK(resolverExpressao(entrada) == 2);
}

TEST_CASE("Resolver Expressão - Subtração Simples") 
{
    std::vector<std::string> entrada = {"1", "0", "-"};
    
    CHECK(resolverExpressao(entrada) == 1);

    entrada = {"0", "1", "-"};
    
    CHECK(resolverExpressao(entrada) == -1);

    entrada = {"1", "1", "-"};
    
    CHECK(resolverExpressao(entrada) == 0);
}

TEST_CASE("Resolver Expressão - Multiplicação Simples") 
{
    std::vector<std::string> entrada = {"1", "0", "*"};
    
    CHECK(resolverExpressao(entrada) == 0);

    entrada = {"0", "1", "*"};
    
    CHECK(resolverExpressao(entrada) == 0);

    entrada = {"1", "10", "*"};
    
    CHECK(resolverExpressao(entrada) == 10);

    entrada = {"10", "1", "*"};
    
    CHECK(resolverExpressao(entrada) == 10);

    entrada = {"11", "3", "*"};
    
    CHECK(resolverExpressao(entrada) == 33);
}

TEST_CASE("Resolver Expressão - Divisão Simples") 
{
    std::vector<std::string> entrada = {"0", "2", "/"};
    
    CHECK(resolverExpressao(entrada) == 0);

    entrada = {"10", "1", "/"};
    
    CHECK(resolverExpressao(entrada) == 10);

    entrada = {"10", "10", "/"};
    
    CHECK(resolverExpressao(entrada) == 1);

    entrada = {"12", "3", "/"};
    
    CHECK(resolverExpressao(entrada) == 4);
}

TEST_CASE("Resolver Expressão - Expressões compostas") 
{
    std::vector<std::string> entrada = {"1", "2", "*", "3", "*"};
    
    CHECK(resolverExpressao(entrada) == 6);
    
    entrada = {"1", "2", "*", "3", "+", "4", "-"};
    
    CHECK(resolverExpressao(entrada) == 1);

    entrada = {"1", "3", "-", "3", "5", "-", "*"};
    
    CHECK(resolverExpressao(entrada) == 4);

    entrada = {"1", "2", "3", "*", "-", "4", "-"}; 
    CHECK(resolverExpressao(entrada) == -9);
}
