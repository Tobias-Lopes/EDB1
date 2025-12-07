#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TabelaHash.h"
#include <vector>

TEST_CASE("Teste de Desempenho") {
    using namespace std::chrono;

    const int capacidade = 100003;
    const int totalInsercoes = 180000;

    TabelaHash tabela(capacidade);

    std::vector<std::pair<std::string, std::string>> entradas;

    for (int i = 0; i < totalInsercoes; ++i) {
        auto chave = "chave" + std::to_string(i);
        auto valor = "valor" + std::to_string(i);
        entradas.push_back(std::make_pair(chave, valor));
    }

    auto inicio = high_resolution_clock::now();
    
    for(auto entrada : entradas)
    {
        tabela.inserir(entrada.first, entrada.second);
    }

    auto fim = high_resolution_clock::now();
    auto duracao = duration_cast<milliseconds>(fim - inicio);

    std::cout << "Tempo para " << totalInsercoes << " inserções: "
              << duracao.count() << " ms" << std::endl;

    CHECK(tabela.tamanho() == totalInsercoes);
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}