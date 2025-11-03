#include <iostream>
#include "Deque.h"

void exibir_menu()
{
    std::cout << "\n===== MENU DE OPERAÇÕES NO DEQUE =====" << std::endl;
    std::cout << "1 - Inserir no início" << std::endl;
    std::cout << "2 - Inserir no fim" << std::endl;
    std::cout << "3 - Remover do início" << std::endl;
    std::cout << "4 - Remover do fim" << std::endl;
    std::cout << "5 - Ver elemento da frente" << std::endl;
    std::cout << "6 - Ver elemento de trás" << std::endl;
    std::cout << "7 - Ver tamanho" << std::endl;
    std::cout << "8 - Imprimir deque" << std::endl;
    std::cout << "0 - Sair" << std::endl;
    std::cout << "Escolha uma opção: ";
}

int main()
{
    Deque<int> deque(10);
    int opcao, valor;

    do
    {
        exibir_menu();
        std::cin >> opcao;

        switch (opcao)
        {
        case 1:
            std::cout << "Digite um valor para inserir no início: ";
            std::cin >> valor;
            try
            {
                deque.empurrarFrente(valor);
            }
            catch (const std::overflow_error &e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
            break;

        case 2:
            std::cout << "Digite um valor para inserir no fim: ";
            std::cin >> valor;
            try
            {
                deque.empurrarAtras(valor);
            }
            catch (const std::overflow_error &e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
            break;

        case 3:
            try
            {
                valor = deque.removerFrente();
                std::cout << "Removido do início: " << valor << std::endl;
            }
            catch (const std::underflow_error &e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
            break;

        case 4:
            try
            {
                valor = deque.removerAtras();
                std::cout << "Removido do fim: " << valor << std::endl;
            }
            catch (const std::underflow_error &e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
            break;

        case 5:
            try
            {
                std::cout << "Elemento na frente: " << deque.daFrente() << std::endl;
            }
            catch (const std::underflow_error &e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
            break;

        case 6:
            try
            {
                std::cout << "Elemento de trás: " << deque.deTras() << std::endl;
            }
            catch (const std::underflow_error &e)
            {
                std::cout << "Erro: " << e.what() << std::endl;
            }
            break;

        case 7:
            std::cout << "Tamanho do deque: " << deque.tamanho() << std::endl;
            break;

        case 8:
            std::cout << "Conteúdo do deque: " << deque.imprimir() << std::endl;
            break;

        case 0:
            std::cout << "Encerrando o programa." << std::endl;
            break;

        default:
            std::cout << "Opção inválida!" << std::endl;
        }
    } while (opcao != 0);

    return 0;
}