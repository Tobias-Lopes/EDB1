# IMD0029 - EDB1 - 2024.2 - Unidade 3
# Prof. Eiji Adachi

## **LEIA ANTES DE COMEÇAR**

- Atividade individual sem consulta a pessoas ou materiais (impresso ou eletrônico).
- O valor de cada questão está indicado no enunciado.
- Mantenha celulares e outros eletrônicos desligados durante a prova.
- Desvios éticos resultarão em nota zero nesta unidade.
- Você recebeu diretórios para cada questão, cada um contendo uma assinatura de função, um arquivo ``Makefile`` e um teste executável, que pode ser executado usando o comando ``make run-test``. O teste executável não garante a total corretude da sua implementação. 
- Siga a assinatura de função fornecida; não a altere. Se necessário, crie funções auxiliares, mas mantenha a assinatura original.

### Critérios de Correção

Na correção desta atividade, serão considerados:

- **Obediência às regras** das assinaturas de função e do entregável (arquivo .zip e estrutura de diretórios), conforme especificado.
- **Ausência de erros ou warnings** na compilação do código-fonte. Use o `makefile` para compilar.
- **Execução correta dos programas**, sem falhas e produzindo os resultados esperados.
- **Atendimento aos critérios de complexidade**, se estabelecidos no enunciado.
- **Qualidade do código-fonte**: boa apresentação, organização, identação, nomes de variáveis adequados, modularização em funções, etc.

### Entregável

- O entregável deve manter a mesma estrutura de diretórios do código-fonte recebido, contendo os arquivos de solução em cada diretório de questão.
- O diretório raiz deve ter seu nome, no formato `PRIMEIRO_NOME_SOBRENOME`. Exemplo:
  ```
  JOAO_SILVA
  ├── q1
  ├── q2
  └── q3
  ```
- Compacte toda a estrutura em um arquivo `.zip` (não use `.rar`, `.tar.gz` ou outros), seguindo o mesmo padrão de nome: `PRIMEIRO_NOME_SOBRENOME.zip`.
- O `.zip` não deve conter arquivos objeto e executáveis; remova-os antes de compactar.
- Entregue o arquivo via SIGAA até o horário estabelecido. Entregas após o prazo só serão aceitas em casos excepcionais (ex.: SIGAA fora do ar).

<div style="page-break-after: always;"/>

## Questão 1 - Valor: 1.5
No contexto de Tabela Hash, o que é uma colisão?

## Questão 2 - Valor: 2.0
Explique sucintamente como é feito o tratamento de colisão por sondagem linear.

## Questão 3 - Valor 1.5
Explique o que é fator de carga e de que forma ele impacta no desempenho das operações de inserir, remover e buscar da Tabela Hash.

## Questão 4 - Valor 2.5
Implemente o método `TabelaHash::remover`. Para executar o teste desse método, você deve invocar o comando `make run-test-remover`.

## Questão 5 - Valor 2.5
Implemente o método `TabelaHash::inserir`. Para executar o teste desse método, você deve invocar o comando `make run-test-inserir`.