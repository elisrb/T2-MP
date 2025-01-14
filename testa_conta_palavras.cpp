// Copyright 2024 Elis Rodrigues Borges

/**
 * \file testa_conta_palavras.cpp
 */

#include "conta_palavras.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testa conta palavras", "[single-file]") {
	string teste1 = "input1.txt";
	REQUIRE(VerificaPalavras(teste1) == L"a: 0\né: 1\nEsta: 2\nEste: 3\nlinha: 4\no: 5\nsegunda: 6\ntexto: 7\n");

	string teste2 = "input2.txt";
	REQUIRE(VerificaPalavras(teste2) == L"é: 0\nEste: 1\no: 2\nque: 3\nserá: 4\ntexto: 5\nutilizado: 6\n");
}