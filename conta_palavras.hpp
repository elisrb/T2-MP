// Copyright 2024 Elis Rodrigues Borges

#ifndef CONTA_PALAVRAS_HPP_
#define CONTA_PALAVRAS_HPP_

#include <string>
#include <vector>

using namespace std;

wstring VerificaPalavras(string arquivo);
vector<wstring> split_string(string file_contents);
string read_file(string arquivo);

#endif  // CONTA_PALAVRAS_HPP_
