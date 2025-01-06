// Copyright 2024 Elis Rodrigues Borges

/**
 * \file testa_conta_palavras.cpp
 */

#include "conta_palavras.hpp"

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testa conta palavras", "[single-file]") {
	string teste1 = "input1.txt";

	REQUIRE(VerificaPalavras(teste1) == "a: 1\nEsta: 1\nEste: 1\nlinha: 1\no: 1\nsegunda: 1\ntexto: 1\né: 1\n");
}