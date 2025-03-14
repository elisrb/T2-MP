// Copyright 2024 Elis Rodrigues Borges

/**
 * \file testa_conta_palavras.cpp
 */

#include <string>
#include "./conta_palavras.hpp"

#define CATCH_CONFIG_MAIN
#include "./catch.hpp"

TEST_CASE("Testa conta palavras", "[VerificaPalavras]") {
	string teste1 = "input1.txt";
	REQUIRE(VerificaPalavras(teste1) == L"a: 1\né: 1\nEsta: 1\nEste: 1\nlinha: 1\no: 1\nsegunda: 1\ntexto: 1\n");

	string teste2 = "input2.txt";
	REQUIRE(VerificaPalavras(teste2) == L"é: 1\nEste: 1\no: 1\nque: 1\nserá: 1\ntexto: 2\nutilizado: 1\n");

	string teste3 = "input3.txt";
	REQUIRE(VerificaPalavras(teste3) == L"de: 1\nteste: 4\ntexto: 1\n");

	string teste4 = "input4.txt";
	REQUIRE(VerificaPalavras(teste4) == L"teste: 1\nTeste: 1\nTESTE: 1\ntEsTe: 1\n");

	string teste5 = "input5.txt";
	REQUIRE(VerificaPalavras(teste5) == L"teste: 1\ntexto: 1\n");

	string teste6 = "input6.txt";
	REQUIRE(VerificaPalavras(teste6) == L"all: 3\ni: 1\nit: 1\nremember: 1\ntoo: 1\nwell: 1\n");
}

TEST_CASE("Testa leitura e separador de palavras", "[split_string]") {
	string teste1 = "input1.txt";
	REQUIRE(split_string(read_file(teste1)).size() == 8);

	string teste5 = "input5.txt";
	REQUIRE(split_string(read_file(teste5)).size() == 2);

	string teste6 = "input6.txt";
	REQUIRE(split_string(read_file(teste6)).size() == 8);
}
