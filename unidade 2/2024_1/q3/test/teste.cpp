#define CATCH_CONFIG_MAIN
#include "catch_amalgamated.hpp"
#include "../header/Analisador.h"

TEST_CASE("Sequências bem formadas - Casos simples") 
{
    Analisador analisador;

    REQUIRE( analisador.eBemFormada("()") == true);
    REQUIRE( analisador.eBemFormada("[]") == true);
    REQUIRE( analisador.eBemFormada("{}") == true);
}

TEST_CASE("Sequências mal formadas - Casos simples") 
{
    Analisador analisador;

    REQUIRE( analisador.eBemFormada("(") == false);
    REQUIRE( analisador.eBemFormada("[") == false);
    REQUIRE( analisador.eBemFormada("{") == false);

    REQUIRE( analisador.eBemFormada(")") == false);
    REQUIRE( analisador.eBemFormada("]") == false);
    REQUIRE( analisador.eBemFormada("}") == false);
}

TEST_CASE("Sequências bem formadas - Casos aninhados") 
{
    Analisador analisador;

    REQUIRE( analisador.eBemFormada("(())()") == true);
    REQUIRE( analisador.eBemFormada("([]{}[])") == true);
    REQUIRE( analisador.eBemFormada("{([])}(){}({[][]{}})") == true);
}

TEST_CASE("Sequências mal formadas - Casos que sobram um caractere no fim") 
{
    Analisador analisador;

    REQUIRE( analisador.eBemFormada("()(") == false);
    REQUIRE( analisador.eBemFormada("[][") == false);
    REQUIRE( analisador.eBemFormada("{}{") == false);

    REQUIRE( analisador.eBemFormada("())") == false);
    REQUIRE( analisador.eBemFormada("[]{}(]") == false);
    REQUIRE( analisador.eBemFormada("{}(){}[]}") == false);
}

TEST_CASE("Sequências mal formadas - Casos que sobram um caractere no meio") 
{
    Analisador analisador;

    REQUIRE( analisador.eBemFormada("()({}") == false);
    REQUIRE( analisador.eBemFormada("[][{}") == false);
    REQUIRE( analisador.eBemFormada("{}{{}{}") == false);
}

TEST_CASE("Sequências mal formadas - Casos com fechamento com outro caracrtere") 
{
    Analisador analisador;

    REQUIRE( analisador.eBemFormada("(]") == false);
    REQUIRE( analisador.eBemFormada("(}") == false);
    
    REQUIRE( analisador.eBemFormada("{)") == false);
    REQUIRE( analisador.eBemFormada("{]") == false);

    REQUIRE( analisador.eBemFormada("[)") == false);
    REQUIRE( analisador.eBemFormada("[}") == false);

    REQUIRE( analisador.eBemFormada("(){]") == false);
    REQUIRE( analisador.eBemFormada("[](]{}") == false);
    REQUIRE( analisador.eBemFormada("{}(){]{}") == false);
}