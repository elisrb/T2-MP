// Copyright 2024 Elis Rodrigues Borges

/**
 * \file  conta_palavras.cpp
 */

#include "conta_palavras.hpp"

/** 
 * @brief conta as palavras do texto fornecido
 * @author Elis
 * @param  conta_palavras descreve o parâmetro
 */

#include <fstream>
#include <string>

using namespace std;

string VerificaPalavras(string arquivo) {
    ifstream file(arquivo);
    string str;
    string file_contents;
    while(getline(file, str)) {
        file_contents += str;
    }
    return(file_contents);
}
