//
//  TabelaHash.h
//
//  Created by Eiji Adachi Medeiros Barbosa
//

#ifndef TABELA_HASH_H
#define TABELA_HASH_H

#include <string>

using namespace std;

constexpr size_t TAMANHO_PADRAO = 17;
constexpr static const float CARGA_LIMITE_INFERIOR = 0.125f;
constexpr static const float CARGA_LIMITE_SUPERIOR = 0.5f;
static pair<string, string>* REMOVIDO = (pair<string, string>*)(-1);

class TabelaHash {
    friend class TabelaHashTestHelper;

private:
    pair<string, string>** elementos;
    size_t tamanho;
    size_t quantidade;

    size_t hashValue(const string&) const;
    size_t hash(const string&) const;
    void iniciar();

    float fatorDeCarga();
    void aumentar();
    void diminuir();
    void redimensionar(size_t);

public:
    TabelaHash();
    explicit TabelaHash(size_t);
    ~TabelaHash();

    pair<string, string>* buscar(const string&) const;
    bool inserir(const string& chave, const string&);
    bool remover(const string& chave);

    bool invariante() const;
    size_t getTamanho() const;
    size_t getQuantidade() const;
    bool vazia() const;
    bool cheia() const;

    void imprimir() const;
};

#endif /* TABELA_HASH_H */
