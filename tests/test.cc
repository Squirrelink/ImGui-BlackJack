// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <cinder/Rand.h>
#include <mylibrary/engine.h>

#include <catch2/catch.hpp>

TEST_CASE("Bet Tests", "[engine]") {
 mylibrary::Engine engine;
 REQUIRE(engine.GetCurrentBet() == 0);
 engine.Bet(20);
 REQUIRE(engine.GetCurrentBet() == 20);
 engine.Bet(40);
 REQUIRE(engine.GetCurrentBet() == 60);
}
TEST_CASE("Reset Balance Tests", "[engine]") {
  mylibrary::Engine engine;
  REQUIRE(engine.GetCurrentBet() == 0);
  REQUIRE(engine.GetBalance() == 1000);
  engine.Bet(20);
  REQUIRE(engine.GetCurrentBet() == 20);
  REQUIRE(engine.GetBalance() == 980);
  engine.ResetBalance();
  REQUIRE(engine.GetCurrentBet() == 0);
  REQUIRE(engine.GetBalance() == 1000);
}

TEST_CASE("Reset Round Tests", "[engine]") {
mylibrary::Engine engine;
engine.SetPlayerScore(21);
engine.SetDealerScore(13);
engine.Bet(100);
engine.is_transition == true;
engine.is_betting = false;
REQUIRE(engine.GetPlayerScore() == 21);
REQUIRE(engine.GetDealerScore() == 13);
REQUIRE(engine.GetCurrentBet() == 100);
engine.ResetRound();
REQUIRE(engine.GetPlayerScore() == 0);
REQUIRE(engine.GetDealerScore() == 0);
REQUIRE(engine.GetCurrentBet() == 0);
REQUIRE(!engine.is_transition);
REQUIRE(engine.is_betting);
}
