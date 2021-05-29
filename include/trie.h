/**
 * @file trie.h
 * @authors Alisson Fabra da Silva e Eduardo Vinicius Betim.
 * @brief Código da Trie.
 * 
 * @copyright Copyright [2021] <Alisson Fabra da Silva, Eduardo Vinicius Betim>
 */

#ifndef STRUCTURES_TRIE_H
#define STRUCTURES_TRIE_H

#include <string>

#define ALPHABET_SIZE 26

/// Estruturas de dados.
namespace structures {

/// Trie
class Trie {
 public:
    /**
     * @brief Construtor de um novo Trie.
     * 
     * Na construção do Trie a posição (index) e o comprimento (length) são 
     * definidos inicialmente como 0 e as posições do vetor de nodos 
     * filhos (children) são definidos inicialmente como nulas.
     *
     * @return Trie criado.
     */
    Trie();

    /**
     * @brief Adiciona uma chave na árvore.
     *
     * @param word Palavra para ser inserida.
     * @param index Posição no dicionario da palavra a ser inserida.
     * @param length Comprimento da linha do dicionario que possui a palavra a ser
     * inserida.
     */
    void insert(std::string word, int index, int length);

    /**
     * @brief Procura uma palavra na árvore.
     *
     * @param word Palavra a ser procurada na árvore.
     *
     * @return Um par (std::pair<int, int>) que indica se a palavra pertence ao 
     * dicionário ou se é um prefixo. Caso a palavra pertença ao dicionário, o 
     * primeiro valor do par representa a posição da palavra enquanto o segundo 
     * representa o comprimeto da linha.
     */
    std::pair<int, int> search(std::string word);

	/**
     * @brief Conta o númedo de vezes que a palavra é um prefixo na árvore.
     *
     * @param word Palavra a ser procurada na árvore.
     *
     * @return Inteiro com número de vezes que a palavra é prefixo na árvore.
     */
	int count_prefix(std::string word);

	/**
     * @brief Conta o númedo de filhos.
     *
     * @return Inteiro com número de filhos.
     */
	int count_children();

	/**
     * @brief Conta o númedo de palavras a partir do nodo.
     *
     * @return Inteiro com número de palavras.
     */
	int count_words();

 private:
    Trie* children[ALPHABET_SIZE];
    int index{0}, length{0};
};

}  // namespace structures

#endif

structures::Trie::Trie() {
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		children[i] = nullptr;
	}
}

void structures::Trie::insert(std::string word, int index, int length) {
	auto current = this;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			current->children[position] = new Trie;
    	}
		current = current->children[position];
	}
	current->index = index;
	current->length = length;
}

std::pair<int, int> structures::Trie::search(std::string word) {
	std::pair<int, int> pair;
	auto current = this;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			pair.first = -1;
			pair.second = -1;
			return pair;
		}
		current = current->children[position];
	}
	if (current && current->length == 0) {
		pair.first = 0;
		pair.second = 0;
		return pair;
	}
	pair.first = current->index;
	pair.second = current->length;
	return pair;
}

int structures::Trie::count_prefix(std::string word) {
	auto current = this;
	int n_prefix = 0;
	for (int i = 0; i < word.length(); i++) {
		int position = word[i] - 'a';
		if (!current->children[position]) {
			break;
		}
		current = current->children[position];
	}
	if (current) {
		if (current->length != 0) {
			n_prefix++;
		}
		n_prefix += current->count_words();
	}
	return n_prefix;
}

int structures::Trie::count_children() {
	auto current = this;
	int n_children = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (current->children[i]) {
			n_children++;
		}
	}
	return n_children;
}

int structures::Trie::count_words() {
	int n_words = 0;
	for (int i = 0; i < ALPHABET_SIZE; i++) {
		if (children[i]) {
			if (children[i]->length != 0) {
				n_words++;
			}
			n_words += children[i]->count_words();
		}
	}
	return n_words;
}

