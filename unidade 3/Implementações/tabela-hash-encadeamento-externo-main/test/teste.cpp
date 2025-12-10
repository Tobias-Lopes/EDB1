#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "TabelaHash.h"
#include "TabelaHashTestHelper.h"

TEST_CASE("TabelaHash - Inserir chave nova") {
	TabelaHash tabela;
    CHECK(tabela.tamanho() == 0);
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
	CHECK(tabela.inserir("a", "1") == true);
	CHECK(tabela.inserir("b", "2") == true);
	CHECK(tabela.tamanho() == 2);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

TEST_CASE("TabelaHash - Buscar chave existente") {
	TabelaHash tabela;
	tabela.inserir("k1", "v1");
	tabela.inserir("k2", "v2");

	std::optional<std::string> r1 = tabela.buscar("k1");
	CHECK(r1.has_value());
	CHECK(r1.value() == "v1");

	std::optional<std::string> r2 = tabela.buscar("k2");
	CHECK(r2.has_value());
	CHECK(r2.value() == "v2");

	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

TEST_CASE("TabelaHash - Buscar chave inexistente") {
	TabelaHash tabela;
	tabela.inserir("x", "1");

	std::optional<std::string> r = tabela.buscar("y");
	CHECK_FALSE(r.has_value());
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

TEST_CASE("TabelaHash - Atualizar valor de chave existente") {
	TabelaHash tabela;
	tabela.inserir("a", "1");
	CHECK(tabela.inserir("a", "novo1") == true); // valor atualizado
	CHECK(tabela.tamanho() == 1);
    
	std::optional<std::string> res = tabela.buscar("a");
	CHECK(res.has_value());
	CHECK(res.value() == "novo1");
	
    CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

TEST_CASE("TabelaHash - Remover chave existente") {
	TabelaHash tabela;
	tabela.inserir("um", "1");
	tabela.inserir("dois", "2");

	CHECK(tabela.tamanho() == 2);
	CHECK(tabela.remover("um") == true);
	CHECK(tabela.tamanho() == 1);
	CHECK_FALSE(tabela.buscar("um").has_value());

	std::optional<std::string> r = tabela.buscar("dois");
	CHECK(r.has_value());
	CHECK(r.value() == "2");

	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

TEST_CASE("TabelaHash - Remover chave inexistente") {
	TabelaHash tabela;
	tabela.inserir("a", "1");

	CHECK(tabela.tamanho() == 1);
	CHECK(tabela.remover("b") == false);
	CHECK(tabela.tamanho() == 1);
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

TEST_CASE("TabelaHash - Colisões são tratadas corretamente") {
	// Capacidade pequena para forçar colisões
	TabelaHash tabela(5);

	// Chaves produzem colisão com a função hash simples usada
	CHECK(tabela.inserir("abc", "123") == true);
	CHECK(tabela.inserir("acb", "456") == true);
	CHECK(tabela.inserir("bac", "789") == true);

	CHECK(tabela.tamanho() == 3);

	// Verifica se todas podem ser buscadas corretamente
	CHECK(tabela.buscar("abc").value() == "123");
	CHECK(tabela.buscar("acb").value() == "456");
	CHECK(tabela.buscar("bac").value() == "789");

	// Verifica que a colisão foi resolvida sem sobrescrever nenhuma
	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);

	// Remove um dos colididos e garante que os outros continuam válidos
	CHECK(tabela.remover("acb") == true);
	CHECK_FALSE(tabela.buscar("acb").has_value());
	CHECK(tabela.buscar("abc").value() == "123");
	CHECK(tabela.buscar("bac").value() == "789");

	CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
}

// TEST_CASE("Teste de Desempenho") {
//     using namespace std::chrono;

//     const int capacidade = 100003;
//     const int totalInsercoes = 180000;

//     TabelaHash tabela(capacidade);

//     auto inicio = high_resolution_clock::now();

//     for (int i = 0; i < totalInsercoes; ++i) {
//         tabela.inserir("chave" + std::to_string(i), "valor" + std::to_string(i));
//     }

//     auto fim = high_resolution_clock::now();
//     auto duracao = duration_cast<milliseconds>(fim - inicio);

//     std::cout << "Tempo para " << totalInsercoes << " inserções: "
//               << duracao.count() << " ms" << std::endl;

//     CHECK(tabela.tamanho() == totalInsercoes);
//     CHECK(tabela.checarConsistencia() == ConsistenciaStatus::OK);
// }

//
//  TesteRedimensionarEncadeamento.cpp
//

TEST_CASE("Testando TabelaHash::redimensionar com encadeamento externo")
{
    // Arrange
    TabelaHash tabela(5);

    // Inserções para garantir colisões e encadeamento
    std::vector<std::pair<std::string, std::string>> dados = {
        {"AAA", "1"},
        {"BAA", "2"},
        {"ABA", "3"},
        {"AAC", "4"},
        {"AAD", "5"},
		{"ABC", "6"},
		{"ACD", "7"},
		{"ABB", "8"},
		{"CAD", "9"},
		{"SPFC", "10"},
		{"FPCS", "11"},
		{"SAB", "12"},
    };

    for (auto& par : dados)
    {
        tabela.inserir(par.first, par.second);
    }

	auto fatorAntes = TabelaHashTestHelper::fatorCarga(tabela);

	REQUIRE( fatorAntes > TabelaHashTestHelper::cargaMax(tabela) );

    // Copia os dados para verificação posterior
    std::unordered_set<std::string> chavesInseridas;
    std::unordered_set<std::string> valoresInseridos;
    for (auto& [k, v] : dados)
    {
        chavesInseridas.insert(k);
        valoresInseridos.insert(v);
    }

    // Act
    TabelaHashTestHelper::redimensionar(tabela, 11);

    // Assert
	auto fatorDepois = TabelaHashTestHelper::fatorCarga(tabela);

	CHECK( fatorDepois < TabelaHashTestHelper::cargaMax(tabela) );
    CHECK( tabela.checarConsistencia() == ConsistenciaStatus::OK );
	CHECK( TabelaHashTestHelper::todosJaEstavam(tabela, chavesInseridas, valoresInseridos) );
	CHECK( TabelaHashTestHelper::todosAindaEstao(tabela, chavesInseridas, valoresInseridos) );
}