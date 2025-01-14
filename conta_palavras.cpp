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

wstring_convert<codecvt_utf8<wchar_t>> converter;

string read_file(string arquivo){
    ifstream file(arquivo);
    string str;

    string file_contents;
    while(getline(file, str)) {
        file_contents += str;
        file_contents.push_back(' ');
    }
    file_contents.pop_back();
    file.close();

    return file_contents;
}

vector<wstring> split_string(string file_contents) {
    size_t pos = 0;
    string delimiter = " ";
    
    vector<wstring> tokens;
    wstring token;

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

wstring format(vector<pair<wstring, int>> palavras_contadas, vector<int> numero_palavras){
    wstring ans = L"";
    int aux;
    for(pair<wstring, int> i : palavras_contadas) {
        aux = numero_palavras[i.second];

        ans += i.first;
        ans += L": ";
        ans += converter.from_bytes(to_string(aux));
        ans += L"\n";
    }

    return ans;
}


wstring VerificaPalavras(string arquivo) {
    string file_contents = read_file(arquivo);

    vector<wstring> palavras = split_string(file_contents);

    sort(palavras.begin(), palavras.end(), comp);

    vector<pair<wstring, int>> palavras_contadas;
    vector<int> numero_palavras;
    bool ja_contou;
    int index = 0;
    int aux;

    for(wstring palavra : palavras) {
        ja_contou = false;
        for(pair<wstring, int> p : palavras_contadas){
            if(p.first == palavra){
                ja_contou = true;
                aux = p.second;
                break;
            }
        }

        if(!ja_contou){
            palavras_contadas.push_back(make_pair(palavra, index));
            numero_palavras.push_back(1);
            index++;
        }
        else
            numero_palavras[aux]++;
    }

    return(format(palavras_contadas, numero_palavras));
}
