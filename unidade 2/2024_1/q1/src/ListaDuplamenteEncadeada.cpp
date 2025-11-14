/**
 * @brief Insere @p s em ordem decrescente, mantendo a ordenação.
 * @param s Elemento a ser inserido.
 * @return true se inserido com sucesso, false se já existia.
 */
bool ListaDuplamenteEncadeada::inserirOrdenado(std::string s) { 
    auto aux = this->cabeca->proximo;

    while (aux != this->cauda && aux->valor > s)
    {
        aux = aux->proximo;
    }

    if (aux != this->cauda && aux->valor == s)
    {
        return false;
    }
    
    auto novo = new No<std::string>(s);

    novo->proximo = aux;
    novo->anterior = aux->anterior;

    aux->anterior->proximo = novo;
    aux->anterior = novo;

    this->quantidade++;

    return true;
}