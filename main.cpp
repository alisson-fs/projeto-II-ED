/**
 * @file main.cpp
 * @authors Alisson Fabra da Silva e Eduardo Vinicius Betim.
 * @brief Código principal.
 * 
 * @copyright Copyright [2021] <Alisson Fabra da Silva, Eduardo Vinicius Betim>
 */

#include <fstream>
#include <iostream>
#include <string>

#include "./include/trie.h"

/**
 * @brief Função main, ponto de partida para a execução do programa.
 * 
 * Recebe um arquivo dic e coloca as palavras em uma árvore de prefixos e faz a 
 * busca das palavras.
 * 
 * @return Retona 0 caso não ocorra erro e -1 caso o arquivo não abra.
 */
int main() {
    using namespace std;
    using namespace structures;

    string filename;
    cin >> filename;  // Arquido de entrada.

    Trie trie;
    ifstream file(filename);
    string line;
    if (file.is_open()) {
        int next_index = 0;
        while (getline(file, line)) {
            string word_read;
            if (line[0] != '[') {
                next_index += line.length() + 1;
                continue;
            }
            for (int i = 1; i < line.length(); i++) {
				if (line[i] == ']') {
                    break;
                }
				word_read += line[i];
			}
            trie.insert(word_read, next_index, line.length());
            next_index += line.length() + 1;
        }
        file.close();
    } else {
        cout << "Arquivo não abriu.\n";
        return -1;
    }

    string word;
    pair<int, int> pair;
    while (1) {  // Leitura das palavras até encontrar "0".
        cin >> word;
        if (word.compare("0") == 0) {
            break;
        }
        pair = trie.search(word);
        string p = word;
        if (pair.first  == 0 && pair.second == 0) {
            int n = trie.count_prefix(word);
            cout << p << " is prefix of " << n << " words" << endl;
        } else if (pair.first  == -1) {
            cout << p << " is not prefix" << endl;
        } else {
            int n = trie.count_prefix(word);
            int d = pair.first;
            int c = pair.second;
            cout << p << " is prefix of " << n << " words" << endl;
            cout << p << " is at " << "(" << d << "," << c << ")" << endl;
        }
    }
    return 0;
}
