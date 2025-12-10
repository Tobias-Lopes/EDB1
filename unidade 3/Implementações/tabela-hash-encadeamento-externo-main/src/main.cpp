#include <iostream>
#include "TabelaHash.h"

int main()
{
	int capacidade;
	std::cout << "Digite a capacidade inicial da Tabela Hash: ";
	std::cin >> capacidade;

	TabelaHash tabela(capacidade);

	while (true)
	{
		std::cout << "\n=== MENU TABELA HASH ===\n";
		std::cout << "1. Inserir ou atualizar par (chave, valor)\n";
		std::cout << "2. Remover par pela chave\n";
		std::cout << "3. Buscar valor por chave\n";
		std::cout << "4. Imprimir todos os pares\n";
		std::cout << "5. Mostrar tamanho\n";
		std::cout << "6. Verificar consistência\n";
		std::cout << "7. Sair\n";
		std::cout << "Escolha uma opcao: ";

		int opcao;
		std::cin >> opcao;

		if (opcao == 1) {
			std::string chave, valor;
			std::cout << "Digite a chave: ";
			std::cin >> chave;
			std::cout << "Digite o valor: ";
			std::cin >> valor;

			bool resultado = tabela.inserir(chave, valor);
			if (resultado) {
				std::cout << "Inserido com sucesso.\n";
			} else {
				std::cout << "Valor atualizado com sucesso.\n";
			}
		}
		else if (opcao == 2) {
			std::string chave;
			std::cout << "Digite a chave a remover: ";
			std::cin >> chave;

			bool resultado = tabela.remover(chave);
			if (resultado) {
				std::cout << "Removido com sucesso.\n";
			}
			else {
				std::cout << "Chave nao encontrada.\n";
			}
		}
		else if (opcao == 3) {
			std::string chave;
			std::cout << "Digite a chave para buscar: ";
			std::cin >> chave;

			std::optional<std::string> resultado = tabela.buscar(chave);
			if (resultado.has_value()) {
				std::cout << "Valor encontrado: " << resultado.value() << std::endl;
			}
			else {
				std::cout << "Chave nao encontrada.\n";
			}
		}
		else if (opcao == 4) {
			tabela.imprimir();
		}
		else if (opcao == 5) {
			std::cout << "Tamanho atual: " << tabela.tamanho() << std::endl;
		}
		else if (opcao == 6) {
			ConsistenciaStatus status = tabela.checarConsistencia();
			if (status == ConsistenciaStatus::OK) {
				std::cout << "Tabela consistente.\n";
			} else {
				std::cout << "Inconsistência detectada: código " << static_cast<int>(status) << std::endl;
			}
		}
		else if (opcao == 7) {
			std::cout << "Encerrando programa.\n";
			break;
		}
		else {
			std::cout << "Opcao invalida. Tente novamente.\n";
		}
	}

	return 0;
}