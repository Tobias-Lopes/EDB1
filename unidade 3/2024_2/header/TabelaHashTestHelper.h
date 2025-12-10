//
//  TabelaHashTestHelper.h
//
//  Criado por Eiji Adachi Medeiros Barbosa
//

#include "TabelaHash.h"

class TabelaHashTestHelper {
public:
    static inline size_t hash(TabelaHash& tabela, std::string chave){
        return tabela.hash(chave);
    }

    static inline std::pair<std::string, std::string>* getElementoNaPosicao(const TabelaHash& tabela, std::size_t posicao) {
        return tabela.elementos[posicao]; 
    }

    static inline void setElementoNaPosicao(TabelaHash& tabela, std::size_t posicao, std::pair<std::string, std::string>* elemento) {
        tabela.elementos[posicao] = elemento; 
    }

    static inline void setElementoNaPosicao(TabelaHash& tabela, std::size_t posicao, std::string chave, std::string valor) {
        auto elemento = new std::pair<std::string, std::string>(chave, valor);
        tabela.elementos[posicao] = elemento; 
    }

    static inline void setQuantidade(TabelaHash& tabela, std::size_t qtd){
        tabela.quantidade = qtd;
    }

    static void preencherTabela(TabelaHash& tabela, std::vector<std::pair<size_t, std::pair<std::string, std::string>*>> dados){
        for( auto e : dados ){
            auto pos = e.first;
            auto par = e.second;
            setElementoNaPosicao(tabela, pos, par);
        }
    }

    static void aumentar(TabelaHash& tabela){
        tabela.aumentar();
    }

    static bool todosPermanecem(TabelaHash& tabela, vector<pair<size_t, pair<string, string>*>> dados){
        for(auto dado : dados){
            auto elemento = dado.second;
            bool achou = false;
            for(size_t i = 0; i < tabela.tamanho; i++){
                if(tabela.elementos[i] != nullptr &&
                tabela.elementos[i] != REMOVIDO &&
                tabela.elementos[i]->first == elemento->first &&
                tabela.elementos[i]->second == elemento->second){
                    achou = true;
                    break;
                }
            }
            if(!achou){
                return false;
            }
        }

        return true;
    }

    static bool todosJaEstavam(TabelaHash& tabela, vector<pair<size_t, pair<string, string>*>> dados){
        for(size_t i = 0; i < tabela.tamanho; i++){
            if(tabela.elementos[i] != nullptr && tabela.elementos[i] != REMOVIDO){
                bool achou = false;
                for(auto dado : dados){
                    auto elemento = dado.second;

                    if(tabela.elementos[i]->first == elemento->first &&
                       tabela.elementos[i]->second == elemento->second){
                        achou = true;
                        break;
                    }
                }
                if(!achou){
                    return false;
                }
            }
        }

        return true;
    }


    static void encherTabela(TabelaHash& tabela){
        for (size_t i = 0; i < tabela.tamanho; ++i) {
            auto chave = std::to_string(i);
            auto pos = hash(tabela, chave) % tabela.tamanho;
            while(getElementoNaPosicao(tabela, pos) != nullptr){
                pos = (pos+1) % tabela.tamanho;
            }
            setElementoNaPosicao(tabela, pos, new std::pair<std::string, std::string>(chave, "VALOR_" + chave));
        }
        setQuantidade(tabela, tabela.tamanho);
    }

    static void encherTabelaComRemovido(TabelaHash& tabela){
        for (size_t i = 0; i < tabela.tamanho; ++i) {
            setElementoNaPosicao(tabela, i, REMOVIDO);
        }
        setQuantidade(tabela, 0);
    }

};
