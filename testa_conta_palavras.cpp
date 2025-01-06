// Copyright 2024 Elis Rodrigues Borges

/**
 * \file testa_conta_palavras.cpp
 */

#include "conta_palavras.hpp"
#include <string>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Testa conta palavras", "[single-file]") {
	string teste1 = "input1.txt";

	REQUIRE(VerificaPalavras(teste1) == "Este é o texto Esta é a segunda linha ");
}