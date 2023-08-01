#include <iostream>
#include <string>
#include "read.hpp"
#include "trie.hpp"
#include "hash_table.hpp"

using namespace aria::csv;
using namespace std;

int main(void) {
  HashTable ratings(100);
  HashTable tags(100);
  vector<int> vetor;
  char *word;
  Trie trie;

  read_trt(&trie);
  cout << "Feito a Trie!" << endl;

  trie.search("Jan Oblak", vetor);

  if(vetor.empty())
    cout << "Não encontrado" << endl;
  else
    for(int player_id : vetor)
      cout << player_id << endl;


  //trie.display_trie();

  //read_hash(&ratings);

  /*
    read_hash(&tags);  Aqui usar uma hash? o arquivo deixa livre para usar qualquer estrutura de dados
    
    Observem que os dados de entrada não possuem diretamente as informações de usuários
    prontas para o retorno dessa pesquisa. Estas informações estão colocadas no arquivo
    rating.csv. Deve-se implementar uma estrutura de dados (livre) para calcular e agregar em
    pré-processamento as informações por usuário. Com essa estrutura construída, para responder
    essa pesquisa basta consultar as entradas pelo identificador do usuário e retornar a lista de
    jogadores que esse usuário revisou e suas informações adicionais.
  */


}