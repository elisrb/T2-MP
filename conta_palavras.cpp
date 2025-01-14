// Copyright 2024 Elis Rodrigues Borges

/**
 * \file  conta_palavras.cpp
 */

#include "conta_palavras.hpp"

/** 
 * @brief conta as ocorrências de palavras distintas do texto fornecido
 * @author Elis
 * @param  conta_palavras descreve o parâmetro
 */

#include <fstream>
#include <string>
#include <vector>
#include <codecvt>

using namespace std;

vector<wstring> split_string(string file_contents) {
    size_t pos = 0;
    string delimiter = " ";
    
    vector<wstring> tokens;
    wstring token;
    wstring_convert<codecvt_utf8<wchar_t>> converter;

    while((pos = file_contents.find(delimiter)) != string::npos) {
        token = converter.from_bytes(file_contents.substr(0, pos));
        tokens.push_back(token);
        file_contents.erase(0, pos + delimiter.length());
    }
    tokens.push_back(converter.from_bytes(file_contents));
    return tokens;
}

wchar_t remove_acento(wchar_t c) {
    if(c == L'ã' or c == L'á' or c == L'â' or c == L'à') return L'a';
    if(c == L'é' or c == L'ê') return L'e';
    if(c == L'í') return L'i';
    if(c == L'õ' or c == L'ó' or c == L'ô') return L'o';
    if(c == L'ú') return L'u';
    if(c == L'ñ') return L'n';
    return c;
}

bool comp(wstring a, wstring b) {
    wstring comp_a = L"", comp_b = L"";
    for(wchar_t i : a) {
        comp_a += remove_acento(tolower(i));
    }
    for(wchar_t i : b) {
        comp_b += remove_acento(tolower(i));
    }
    return(comp_a < comp_b);
}

wstring VerificaPalavras(string arquivo) {
    ifstream file(arquivo);
    string str;

    string file_contents;
    while(getline(file, str)) {
        file_contents += str;
        file_contents.push_back(' ');
    }
    file_contents.pop_back();
    file.close();

    vector<wstring> palavras = split_string(file_contents);

    sort(palavras.begin(), palavras.end(), comp);

    vector<wstring> palavras_contadas;
    vector<pair<int, int>> indice_numero_palavras;
    bool ja_contou;
    int index = 0;

    for(wstring palavra : palavras) {
        ja_contou = false;
        for(wstring p : palavras_contadas){
            if(p == palavra){
                ja_contou = true;
                break;
            }
        }
        if(!ja_contou){
            palavras_contadas.push_back(palavra);
            index++;
        }
    }

    wstring ans = L"";
    for(wstring i : palavras_contadas) {
        ans += i;
        ans += L": 1\n";
    }

    return(ans);
}
