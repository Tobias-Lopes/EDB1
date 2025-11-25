#include <iostream>
#include "Dicionario.h"

int main()
{
	int capacidade;
	std::cout << "Digite a capacidade máxima do Dicionario: ";
	std::cin >> capacidade;

	Dicionario<std::string, std::string> dic(capacidade);

	while (true)
	{
		std::cout << "\n=== MENU DICIONARIO ===\n";
		std::cout << "1. Inserir ou atualizar par (chave, valor)\n";
		std::cout << "2. Remover par pela chave\n";
		std::cout << "3. Buscar valor por chave\n";
		std::cout << "4. Imprimir todos os pares\n";
		std::cout << "5. Mostrar tamanho\n";
		std::cout << "6. Sair\n";
		std::cout << "Escolha uma opcao: ";

		int opcao;
		std::cin >> opcao;

		if (opcao == 1) {
			std::string chave, valor;
			std::cout << "Digite a chave: ";
			std::cin >> chave;
			std::cout << "Digite o valor: ";
			std::cin >> valor;

			try {
				bool resultado = dic.inserir(chave, valor);
				if (resultado) {
					std::cout << "Inserido ou atualizado com sucesso.\n";
				}
			} catch (const std::runtime_error& e) {
				std::cout << "Erro: " << e.what() << std::endl;
			}
		}
		else if (opcao == 2) {
			std::string chave;
			std::cout << "Digite a chave a remover: ";
			std::cin >> chave;

			try {
				bool resultado = dic.remover(chave);
				if (resultado) {
					std::cout << "Removido com sucesso.\n";
				}
				else {
					std::cout << "Chave nao encontrada.\n";
				}
			} catch (const std::runtime_error& e) {
				std::cout << "Erro: " << e.what() << std::endl;
			}
		}
		else if (opcao == 3) {
			std::string chave;
			std::cout << "Digite a chave para buscar: ";
			std::cin >> chave;

			std::optional<std::string> resultado = dic.buscar(chave);
			if (resultado.has_value()) {
				std::cout << "Valor encontrado: " << resultado.value() << std::endl;
			}
			else {
				std::cout << "Chave nao encontrada.\n";
			}
		}
		else if (opcao == 4) {
			dic.imprimir();
		}
		else if (opcao == 5) {
			std::cout << "Tamanho atual: " << dic.tamanho() << std::endl;
		}
		else if (opcao == 6) {
			std::cout << "Encerrando programa.\n";
			break;
		}
		else {
			std::cout << "Opcao invalida. Tente novamente.\n";
		}
	}

	return 0;
}