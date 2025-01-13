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

bool comp(wstring a, wstring b) {
        wstring lower_a = L"", lower_b = L"";
        wchar_t c;
        for(wchar_t i : a) {
            c = tolower(i);
            lower_a += c;
        }
        for(wchar_t i : b) {
            c = tolower(i);
            lower_b += c;
        }
        return(lower_a < lower_b);
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

    vector<wstring> tokens = split_string(file_contents);

    sort(tokens.begin(), tokens.end(), comp);

    wstring ans = L"";
    for(wstring i : tokens) {
        ans += i;
        ans += L": 1\n";
    }
    return(ans);
}
