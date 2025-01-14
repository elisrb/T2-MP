// Copyright 2024 Elis Rodrigues Borges

/**
 * \file testa_conta_palavras.cpp
 */

#include "conta_palavras.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testa conta palavras", "[single-file]") {
	string teste1 = "input1.txt";
	REQUIRE(VerificaPalavras(teste1) == L"a: 1\né: 1\nEsta: 1\nEste: 1\nlinha: 1\no: 1\nsegunda: 1\ntexto: 1\n");

	string teste2 = "input2.txt";
	REQUIRE(VerificaPalavras(teste2) == L"é: 1\nEste: 1\no: 1\nque: 1\nserá: 1\ntexto: 2\nutilizado: 1\n");

	string teste3 = "input3.txt";
	REQUIRE(VerificaPalavras(teste3) == L"de: 1\nteste: 4\ntexto: 1\n");
}
