/**
 * @file ListaDuplamenteEncadeada.cpp
 * @brief Implementação da classe ListaDuplamenteEncadeada com sentinelas cabeca e cauda.
 *
 * Criado por Eiji Adachi Medeiros Barbosa.
 */

#include "ListaDuplamenteEncadeada.h"
#include <sstream>
#include <stdexcept>

/**
 * @brief Construtor da lista duplamente encadeada.
 *
 * Inicializa a lista com nós sentinelas para cabeça e cauda,
 * configurando os ponteiros adequadamente e definindo a quantidade como zero.
 */
ListaDuplamenteEncadeada::ListaDuplamenteEncadeada() {
    this->cabeca = new No<std::string>("CABECA_NAO_DEVE_SER_ACESSADA");
    this->cauda = new No<std::string>("CAUDA_NAO_DEVE_SER_ACESSADA");
    
    this->cabeca->proximo = this->cauda;
    this->cabeca->anterior = nullptr;

    this->cauda->proximo = nullptr;
    this->cauda->anterior = this->cabeca;

    this->quantidade = 0;
}

/**
 * @brief Destrutor da lista.
 *
 * Libera todos os nós alocados dinamicamente, incluindo os nós sentinelas,
 * e reseta os ponteiros da lista e a quantidade para zero.
 */
ListaDuplamenteEncadeada::~ListaDuplamenteEncadeada() {
    auto aux = this->cabeca->proximo;
    while (aux != this->cauda) {
        auto tmp = aux;
        aux = aux->proximo;
        delete tmp;
    }

    delete this->cabeca;
    delete this->cauda;

	this->cabeca = nullptr;
	this->cauda = nullptr;
	this->quantidade = 0;
}

/**
 * @brief Retorna o valor do primeiro elemento da lista.
 *
 * @return Valor do primeiro elemento como std::string.
 *
 * @throws std::out_of_range Se a lista estiver vazia.
 */
const std::string ListaDuplamenteEncadeada::primeiroElemento() const {
    if (this->vazia()) {
        throw std::out_of_range("Lista vazia");
    }
    return this->cabeca->proximo->valor;
}

/**
 * @brief Retorna o valor do último elemento da lista.
 *
 * @return Valor do último elemento como std::string.
 *
 * @throws std::out_of_range Se a lista estiver vazia.
 */
const std::string ListaDuplamenteEncadeada::ultimoElemento() const {
    if (this->vazia()) {
        throw std::out_of_range("Lista vazia");
    }
    return this->cauda->anterior->valor;
}

/**
 * @brief Retorna o tamanho atual da lista.
 *
 * @return Número inteiro representando a quantidade de elementos na lista.
 */
int ListaDuplamenteEncadeada::tamanho() const {
    return this->quantidade;
}

/**
 * @brief Verifica se a lista está vazia.
 *
 * @return true Se a lista não contém elementos.
 * @return false Caso contrário.
 */
bool ListaDuplamenteEncadeada::vazia() const {
    return this->quantidade == 0;
}

/**
 * @brief Retorna o elemento na posição i da lista.
 *
 * @param i Índice da posição cujo elemento será retornado.
 * @return Elemento na posição i como std::string.
 *
 * @throws Exceção std::out_of_range indicando que o índice é inválido.
 */
const std::string ListaDuplamenteEncadeada::elementoNaPosicao(int i) const{
    if (i < 1 || i > this->quantidade) {
        throw std::out_of_range("Índice inválido");
    }
    
    int pos = 1; 
    auto aux = this->cabeca->proximo; //posicionamento inicial

    while (pos < i)
    {
        pos++;
        aux = aux->proximo; //travessia
    }

    return aux->valor;
}

/**
 * @brief Busca um elemento na lista e retorna sua posição.
 *
 * @param s Elemento a ser buscado.
 * @return Posição do elemento encontrado na lista, ou -1, caso não seja encontrado.
 */
int ListaDuplamenteEncadeada::buscar(std::string s) const {
    int pos = 1;
    auto aux = this->cabeca->proximo;

    while (aux != this->cauda) //travessia e verificação
    {
        if(aux->valor == s){
            return pos;
        } else{
            pos++;
            aux = aux->proximo;
        }
    }
    return -1;
}

/**
 * @brief Insere um elemento no início da lista.
 *
 * @param s Elemento a ser inserido.
 * @return true Se a inserção foi bem-sucedida.
 * @return false Caso contrário.
 */
bool ListaDuplamenteEncadeada::inserirInicio(std::string s) {
    //cria um novo nó
    auto novo = new No<std::string>(s);

    //Posicionar novo nó
    novo->anterior = this->cabeca;
    novo->proximo = this->cabeca->proximo;

    //Atualizar vizinhos
    novo->anterior->proximo = novo;
    novo->proximo->anterior = novo;

    this->quantidade++;
    return true;
}

/**
 * @brief Insere um elemento no final da lista.
 *
 * @param s Elemento a ser inserido.
 * @return true Se a inserção foi bem-sucedida.
 * @return false Caso contrário.
 */
bool ListaDuplamenteEncadeada::inserirFim(std::string s) {
    //criar novo nó
    auto novo = new No<std::string>(s);

    //posicionar novo nó
    novo->proximo = cauda;
    novo->anterior = cauda->anterior;

    //atualizar vizinhos
    novo->proximo->anterior = novo;
    novo->anterior->proximo = novo;

    this->quantidade++;

    return true;
}


/**
 * @brief Insere um elemento na posição i da lista.
 *
 * @param i Posição onde o elemento será inserido.
 * @param s Elemento a ser inserido.
 * @return true Se a inserção foi bem-sucedida.
 * @return false Caso contrário.
 *
 * @throws Exceção std::out_of_range indicando que o índice é inválido.
 */
bool ListaDuplamenteEncadeada::inserir(int i, std::string s) {
    if (i < 1 || i > this->quantidade + 1) {
        throw std::out_of_range("Posição inválida");
    }

    int pos=1;
    auto aux = this->cabeca->proximo;

    while (pos < i)
    {
        pos++;
        aux = aux->proximo;
    }

    //aux aponta para o nó que atualmente ocupa a posição i

    //O novo nó deve ser inserido antes de aux

    //criar novo nó
    auto novo = new No<std::string>(s);

    //Posicionar novo nó
    novo->proximo = aux;
    novo->anterior = aux->anterior;

    //Atualizar vizinhos
    novo->proximo->anterior = novo;
    novo->anterior->proximo = novo;

    this->quantidade++;

    return true;
}

/**
 * @brief Insere um novo elemento antes de um elemento de referência.
 *
 * @param novoElemento Elemento a ser inserido.
 * @param referencia Elemento de referência antes do qual o novo elemento será inserido.
 * @return true Se a inserção foi bem-sucedida.
 * @return false Caso contrário.
 */
bool ListaDuplamenteEncadeada::inserirAntes(std::string novoElemento, std::string referencia) {
    // Se a lista estiver vazia, não há onde inserir
    if (this->vazia()) {
        return false;
    }

    auto aux = this->cabeca->proximo;

    // Procurar o nó com o valor 'referencia'
    while (aux != this->cauda && aux->valor != referencia) {
        aux = aux->proximo;
    }

    // Se chegou até a cauda, não encontrou
    if (aux == this->cauda) {
        return false;
    }

    // Inserção antes do primeiro elemento
    if (aux == this->cabeca->proximo) {
        return this->inserirInicio(novoElemento);
    }

    // Inserção normal no meio
    auto novo = new No<std::string>(novoElemento);

    novo->proximo = aux;
    novo->anterior = aux->anterior;

    aux->anterior->proximo = novo;
    aux->anterior = novo;

    this->quantidade++;

    return true;
}

/**
 * @brief Insere um elemento na lista de forma ordenada em ordem decrescente. 
 * Este método não deve admitir valores repetidos na lista.
 *
 * @param s Elemento a ser inserido.
 * @return false Caso o elemento já exista na lista.
 * @return true Caso a inserção seja bem sucedida, i.e., se o valor ainda não existia na lista e um novo nó foi criado.
 */
bool ListaDuplamenteEncadeada::inserirOrdenado(std::string s) {

    auto aux = this->cabeca->proximo;

    while (aux != this->cauda && aux->valor > s) //ordem decrescente
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

/**
 * @brief Remove o primeiro elemento da lista.
 *
 * @return Elemento removido como std::string.
 */
std::string ListaDuplamenteEncadeada::removerInicio() {

// Se a lista está vazia (cabeca->proximo é a sentinela cauda), lançar exceção
    if (this->cabeca->proximo == this->cauda || this->quantidade == 0) {
        throw std::out_of_range("Lista vazia");
    }

    // 'aux' é o primeiro nó real
    auto aux = this->cabeca->proximo;

    // Guardar valor antes de deletar
    std::string resultado = aux->valor;

    // Remover 'aux' da lista atualizando os ponteiros das sentinelas/vizinhos
    this->cabeca->proximo = aux->proximo;
    aux->proximo->anterior = this->cabeca;

    // Liberar memória e ajustar tamanho
    delete aux;
    this->quantidade--;

    return resultado;
}

/**
 * @brief Remove o último elemento da lista.
 *
 * @return Elemento removido como std::string.
 */
std::string ListaDuplamenteEncadeada::removerFim() {
    if (this->cabeca->proximo == this->cauda || this->quantidade == 0) {
        throw std::out_of_range("Lista vazia");
    }

    if(this->quantidade == 1){
        return this->removerInicio();
    }

    auto aux = this->cauda->anterior;

    std::string resultado = aux->valor;

    this->cauda->anterior = aux->anterior;
    aux->anterior->proximo = this->cauda;

    delete aux;
    this->quantidade--;

    return resultado;
}

/**
 * @brief Remove o elemento na posição i da lista.
 *
 * @param i Posição do elemento a ser removido.
 * @return Elemento removido como std::string.
 *
 * @throws Exceção std::out_of_range indicando que o índice é inválido.
 */
std::string ListaDuplamenteEncadeada::remover(int i) {
    //Validação do indice

    if(i < 1 || i > this->quantidade){
        throw std::out_of_range("índice inválido para remoção.");
    }

    int pos=1;
    auto aux = this->cabeca->proximo;

    while (pos < i)
    {
        pos++;
        aux = aux->proximo;
    }

    //aux está posicionado apontando no i-nésimo nó

    //Atualizar vizinhos
    aux->proximo->anterior = aux->anterior;
    aux->anterior->proximo = aux->proximo;
    
    auto resultado = aux->valor;

    delete aux;

    this-quantidade--;

    return resultado;
}

/**
 * @brief Imprime a lista no formato encadeado.
 *
 * @return Representação em string da lista no formato "{elemento1<->elemento2<->...}".
 */
std::string ListaDuplamenteEncadeada::imprimir() const {
    std::stringstream resultado;
    No<std::string>* n = this->cabeca->proximo;

    if (n == this->cauda) {
        return "{}";
    } else {
        resultado << n->valor;
        n = n->proximo;
    }

    for (; n != this->cauda; n = n->proximo) {
        resultado << "<->" << n->valor;
    }

    return resultado.str();
}

/**
 * @brief Verifica a consistência da lista duplamente encadeada.
 *
 * Realiza diversas checagens para garantir a integridade dos ponteiros e da estrutura da lista.
 *
 * @return StatusDaLista Código indicando o resultado da verificação.
 */
StatusDaLista ListaDuplamenteEncadeada::checarConsistencia() const {
    if (this->cabeca == nullptr) {
        return CABECA_NULA;
    } else if (this->cabeca->proximo == nullptr) {
        return CABECA_PROXIMO_NULO;
    } else if (this->cabeca->proximo->anterior != this->cabeca) {
        return ENCADEAMENTO_INCORRETO;
    } else if (this->cabeca->anterior != nullptr) {
        return CABECA_ANTERIOR;
    }

    if (this->cauda == nullptr) {
        return CAUDA_NULA;
    } else if (this->cauda->anterior == nullptr) {
        return CAUDA_ANTERIOR_NULO;
    } else if (this->cauda->anterior->proximo != this->cauda) {
        return ENCADEAMENTO_INCORRETO;
    } else if (this->cauda->proximo != nullptr) {
        return CAUDA_PROXIMO;
    }

    if (this->vazia()) {
        if (this->cabeca->proximo != this->cauda) {
            return CABECA_CAUDA;
        }
        if (this->cabeca != this->cauda->anterior) {
            return CABECA_CAUDA;
        }
    } else {
		int contagem = 0;
        for (No<std::string>* i = this->cabeca->proximo; i != this->cauda; i = i->proximo) {
			if (i->proximo == nullptr || i->anterior == nullptr) {
				return ENCADEAMENTO_INCORRETO;
			}
            if (i->proximo->anterior != i) {
                return ENCADEAMENTO_INCORRETO;
            }
            if (i->anterior->proximo != i) {
                return ENCADEAMENTO_INCORRETO;
            }
			contagem++;
        }

		if (contagem != this->quantidade) {
            return QUANTIDADE_DIFERENTE; 
        }
    }

    return OK;
}
