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
engine.is_transition = true;
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

TEST_CASE("Evaluate Card Value Sub 10 Value", "[engine][evaluate_card]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.player_cards[0].value = 7;
  
  REQUIRE(engine.EvaluateCardValue(true) == 7);
}
TEST_CASE("Evaluate Card Royal value", "[engine][evaluate_card][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  //Queen value test
  engine.player_cards[0].value = 12;
  REQUIRE(engine.EvaluateCardValue(true) == 10);
  //King value test
  engine.player_cards[0].value = 11;
  REQUIRE(engine.EvaluateCardValue(true) == 10);
  //Jack Value test
  engine.player_cards[0].value = 13;
  REQUIRE(engine.EvaluateCardValue(true) == 10);
}
TEST_CASE("Evaluate Card Ace under 21 edge", "[engine][evaluate_card][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.player_cards[0].value = 14;
  REQUIRE(engine.EvaluateCardValue(true) == 11);
}
TEST_CASE("Evaluate Card Ace over 21 edge", "[engine][evaluate_card][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.player_cards[0].value = 14;
  engine.player_cards[1].value = 8;
  REQUIRE(engine.EvaluateCardValue(true) == 19);
  engine.RunPlayerHit();
  engine.player_cards[2].value = 3;
  REQUIRE(engine.EvaluateCardValue(true) == 12);
}
TEST_CASE("Evaluate Card Hand Test", "[engine][evaluate_card]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.player_cards[0].value = 7;
  engine.player_cards[1].value = 8;
  REQUIRE(engine.EvaluateCardValue(true) == 15);
  engine.RunPlayerHit();
  engine.player_cards[2].value = 3;
  REQUIRE(engine.EvaluateCardValue(true) == 18);
}
