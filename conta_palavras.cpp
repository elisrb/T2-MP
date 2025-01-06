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

using namespace std;

string VerificaPalavras(string arquivo) {
    ifstream file(arquivo);
    string str;
    string file_contents;
    while(getline(file, str)) {
        file_contents += str;
        file_contents.push_back(' ');
    }
    file_contents.pop_back();

    vector<string> tokens;
    size_t pos = 0;
    string token;
    string delimiter = " ";
    while((pos = file_contents.find(delimiter)) != string::npos) {
        token = file_contents.substr(0, pos);
        tokens.push_back(token);
        file_contents.erase(0, pos + delimiter.length());
    }
    tokens.push_back(file_contents);

    string ans = "";
    for(string i : tokens) {
        ans += i;
        ans += '/';
    }

    return(ans);
}
