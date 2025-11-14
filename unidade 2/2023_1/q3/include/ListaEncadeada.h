#include <string>
#include "../include/No.h"

class ListaEncadeada
{
private:
    int quantidade;       
    No<std::string>* inicio;
    
public:
    ListaEncadeada();
    
    ~ListaEncadeada();
    
    void inserirNoInicio(std::string);

    void ordenar();

    void imprimir();
    
    bool vazia();

    bool checarOrdenacao();
    
    int tamanho();

    No<std::string>* getInicio();

    void setInicio(No<std::string>*);
};
