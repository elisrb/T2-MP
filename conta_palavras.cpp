// Copyright 2024 Elis Rodrigues Borges

/**
 * \file  conta_palavras.cpp
 */

#include "./conta_palavras.hpp"

#include <fstream>
#include <string>
#include <vector>
#include <codecvt>
#include <algorithm>
#include <utility>

using namespace std;

wstring_convert<codecvt_utf8<wchar_t>> converter;

/** 
 * @brief Essa função abre um arquivo .txt e lê o conteúdo dele
 * @param  str  path do arquivo .txt a ser aberto relativa ao diretório do código-fonte
 * Assertivas de entrada:
 * - a path do arquivo deve existir
 * - o arquivo deve ser um .txt
 * - não devem existir dois arquivos com o mesmo nome
 * Assertivas de saída:
 * - string contendo todo o conteúdo do arquivo
 * - as quebras de linha são substituídas por espaços
 * @return str  o conteúdo do arquivo
 */
string read_file(string arquivo) {
    ifstream file(arquivo);
    string str;

    string file_contents;
    while (getline(file, str)) {
        file_contents += str;
        file_contents.push_back(' ');
    }
    file_contents.pop_back();
    file.close();

    return file_contents;
}

/** 
 * @brief Essa função separa as palavras de uma string por espaço
 * @param  str  string de palavras a serem separadas
 * Assertivas de entrada:
 * - string contendo várias palavras separadas apenas por espaços
 * - as palavras podem ser separadas por mais de um espaço
 * Assertivas de saída:
 * - vetor de wstring em que cada item é uma palavra do texto fornecido
 * @return vector<wstring>  lista em que cada item é uma palavra (convertida para wstring para facilitar a execução das outras funções)
 */
vector<wstring> split_string(string texto) {
    int pos = 0;
    char separador = ' ';

    vector<wstring> tokens;
    string token;

    while (pos < texto.size()) {
        token = "";
        while (pos < texto.size() && texto[pos] == separador) {
            pos++;
        }
        while (pos < texto.size() && texto[pos] != separador) {
            token += texto[pos];
            pos++;
        }
        tokens.push_back(converter.from_bytes(token));
    }

    return tokens;
}

/** 
 * @brief Essa função remove o acento dos caracteres para facilitar a comparação e ordenação
 * @param  wchar_t  caractere a ser normalizado
 * Assertivas de entrada:
 * - o caractere deve ter sido previamente convertido para wchar_t
 * - o caractere deve ser uma letra minúscula do alfabeto
 * - os caracteres acentuados considerados são: ã, á, â, à, é, ê, í, õ, ó, ô, ú e ñ
 * Assertivas de saída:
 * - um wchar_t correspondente ao original sem acento
 * @return wchar_t  caso o caractere original seja acentuado, retorna o caractere com o acento removido; caso não, retorna o mesmo caractere
 */
wchar_t remove_acento(wchar_t c) {
    if (c == L'ã' || c == L'á' || c == L'â' || c == L'à') return L'a';
    if (c == L'é' || c == L'ê') return L'e';
    if (c == L'í') return L'i';
    if (c == L'õ' || c == L'ó' || c == L'ô') return L'o';
    if (c == L'ú') return L'u';
    if (c == L'ñ') return L'n';
    return c;
}

/** 
 * @brief Essa função é um comparador para a ordenação de palavras em ordem alfabética considerando maiúsculas e minúsculas e acentuação.
 * Duas palavras com as mesmas letras (maiúsculas ou minúsculas, acentuadas ou não), aparecerão na ordem em que foram recebidas.
 * @param  wstring  duas palavras (a e b) a serem comparadas
 * Assertivas de entrada:
 * - as palavras devem ter sido previamente convertidas para wstring
 * Assertivas de saída:
 * - as palavras serão ordenadas em ordem alfabética, mantendo os caracteres originais
 * @return  bool    true se a deve vir antes de b na ordenação, false se a deve vir depois de b
 */
bool comp(wstring a, wstring b) {
    wstring comp_a = L"", comp_b = L"";
    for (wchar_t i : a) {
        comp_a += remove_acento(tolower(i));
    }
    for (wchar_t i : b) {
        comp_b += remove_acento(tolower(i));
    }
    return(comp_a < comp_b);
}

/** 
 * @brief Essa função formata a resposta do problema apresentado no roteiro do trabalho, estruturando a contagem das palavras.
 * @param  vector<pair<wstring, int>>, vector<int>  o primeiro vetor é composto por pairs que contêm cada palavra do texto
 * associada ao seu índice na lista da contagem de palavras, e outro vetor que é a lista da contagem de ocorrências de cada palavra
 * Assertivas de entrada:
 * - o vector<pair<wstring, int>> deve contemplar todas as palavras que foram contabilizadas
 * - os pares desse vetor são compostos por uma wstring (a palavra) e um número inteiro correspondente ao índice dessa palavra no vetor
 * o vector<int> deve conter o número correspondente à quantidade de ocorrências de cada palavra do primeiro vetor, no mesmo índice
 * Assertivas de saída:
 * - a string contém todas as palavras e o número de ocorrências, formatadas como "{palavra}: {número de ocorrências}\n", para cada palavra
 * @return wstring  a string da resposta formatada
 */
wstring format(vector<pair<wstring, int>> palavras_contadas, vector<int> numero_palavras) {
    wstring ans = L"";
    int aux;
    for (pair<wstring, int> i : palavras_contadas) {
        aux = numero_palavras[i.second];

        ans += i.first;
        ans += L": ";
        ans += converter.from_bytes(to_string(aux));
        ans += L"\n";
    }

    return ans;
}

/** 
 * @brief Essa é a função principal do código, que chama todas as outras funções. Ela conta as ocorrências de cada palavra em um arquivo .txt fornecido.
 * @param str   path do arquivo .txt a ser aberto relativa ao diretório do código-fonte
 * Assertivas de entrada:
 * - a path do arquivo deve existir
 * - o arquivo deve ser um .txt
 * - não devem existir dois arquivos com o mesmo nome
 * Assertivas de saída:
 * - a string contém todas as palavras e o número de ocorrências, formatadas como "{palavra}: {número de ocorrências}\n", para cada palavra
 * @return wstring  a string da resposta formatada
 */
wstring VerificaPalavras(string arquivo) {
    string file_contents = read_file(arquivo);  // lê o arquivo

    vector<wstring> palavras = split_string(file_contents);  // separa as palavras

    sort(palavras.begin(), palavras.end(), comp);  // ordena as palavras

    /**
     * O loop a seguir é responsável por contabilizar as ocorências de cada palavra no texto.
     * São criados dois vetores:
     * - palavras_contadas: armazena todas as palavras distintas do texto, em pares com o número correspondente ao seu índice na lista
     * (para acessar o índice de forma mais fácil ao buscar pela palavra)
     * - numero_palavras: armazena o número de ocorrências de cada palavra no texto
    */
    vector<pair<wstring, int>> palavras_contadas;
    vector<int> numero_palavras;
    bool ja_contou;
    int index = 0;  // armazena o índice atual da lista (número de palavras distintas contadas até agora)
    int aux;

    for (wstring palavra : palavras) {  // percorre as palavras lidas, separadas e ordenadas pelas funções anteriores
        ja_contou = false;
        for (pair<wstring, int> p : palavras_contadas) {
            if (p.first == palavra) {  // verifica se a palavra já foi contada
                ja_contou = true;
                aux = p.second;  // guarda o índice correspondente
                break;
            }
        }

        if (!ja_contou) {  // caso a palavra ainda não tenha sido contada
            palavras_contadas.push_back(make_pair(palavra, index));  // adiciona ela à lista
            numero_palavras.push_back(1);  // até o momento, a palavra só apareceu uma vez
            index++;  // incrementa o índice
        } else {  // caso a palavra já esteja na lista
            numero_palavras[aux]++;  // incrementa o contador de vezes em que ela aparece
        }
    }

    return(format(palavras_contadas, numero_palavras));  // formata a resposta
}
