// Copyright (c) 2020 CS126SP20. All rights reserved.

#define CATCH_CONFIG_MAIN

#include <mylibrary/engine.h>
#include <catch2/catch.hpp>

const int kBlackjack = 21;
const int kPlayerWin = 1;
const int kPlayerLose = 2;
const int kPlayerTie = 3;
const int kMaxCards = 5;
const int kStartBalance = 1000;
const int kAceCard = 14;
const int kRoyalCard = 10;
const int kAceValue = 11;

// Bet Test
TEST_CASE("Bet Tests", "[engine]") {
 mylibrary::Engine engine;
 REQUIRE(engine.GetCurrentBet() == 0);
 engine.Bet(20);
 REQUIRE(engine.GetCurrentBet() == 20);
 engine.Bet(40);
 REQUIRE(engine.GetCurrentBet() == 60);
}

// Card Score Evaluation Test
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
  engine.player_cards[0].value = kAceCard;
  REQUIRE(engine.EvaluateCardValue(true) == 11);
}
TEST_CASE("Evaluate Card Ace over 21 edge", "[engine][evaluate_card][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.player_cards[0].value = kAceCard;
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

// Round Evaluator Tests
TEST_CASE("Simple Evaluate Round Player Win Test", "[engine][evaluate_round][player_win]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(19);
  engine.SetDealerScore(18);
  REQUIRE(engine.EvaluateRound() == kPlayerWin);
}
TEST_CASE("Simple Evaluate Round Player Lose Test", "[engine][evaluate_round][player_lose]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(17);
  engine.SetDealerScore(20);
  REQUIRE(engine.EvaluateRound() == kPlayerLose);
}
TEST_CASE("Simple Evaluate Round Player Tie Test", "[engine][evaluate_round][player_tie]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(17);
  engine.SetDealerScore(17);
  REQUIRE(engine.EvaluateRound() == kPlayerTie);
}
TEST_CASE("Simple Evaluate Round Player Blackjack", "[engine][evaluate_round][player_win]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(kBlackjack);
  engine.SetDealerScore(18);
  REQUIRE(engine.EvaluateRound() == kPlayerWin);
}
TEST_CASE("Simple Evaluate Round Player Tie Blackjack", "[engine][evaluate_round][player_win]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(kBlackjack);
  engine.SetDealerScore(kBlackjack);
  REQUIRE(engine.EvaluateRound() == kPlayerWin);
}
TEST_CASE("Simple Evaluate Round Dealer Blackjack", "[engine][evaluate_round][player_lose]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(20);
  engine.SetDealerScore(kBlackjack);
  REQUIRE(engine.EvaluateRound() == kPlayerLose);
}
TEST_CASE("Simple Evaluate Round Player Bust", "[engine][evaluate_round][player_lose]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(24);
  engine.SetDealerScore(kBlackjack);
  REQUIRE(engine.EvaluateRound() == kPlayerLose);
}
TEST_CASE("Simple Evaluate Round Dealer Bust", "[engine][evaluate_round][player_win]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(20);
  engine.SetDealerScore(24);
  REQUIRE(engine.EvaluateRound() == kPlayerWin);
}

// Player Hit Tests
TEST_CASE("Run Player Hit Test", "[engine][run_player_hit]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  REQUIRE(engine.player_cards.size() == 1);
  engine.RunPlayerHit();
  REQUIRE(engine.player_cards.size() == 2);
}
TEST_CASE("Run Player Hit Test Edge 5 Cards", "[engine][run_player_hit][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  engine.RunPlayerHit();
  engine.SetPlayerScore(0);
  REQUIRE(engine.player_cards.size() == kMaxCards);
  engine.RunPlayerHit();
  REQUIRE(engine.player_cards.size() == kMaxCards);
}
TEST_CASE("Run Player Hit Test Edge Player Bust", "[engine][run_player_hit][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.RunPlayerHit();
  engine.SetPlayerScore(24);
  REQUIRE(engine.player_cards.size() == 2);
  engine.RunPlayerHit();
  REQUIRE(engine.player_cards.size() == 2);
}
TEST_CASE("Run Player Hit Test Edge Player Blackjack", "[engine][run_player_hit][edge]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.RunPlayerHit();
  engine.SetPlayerScore(kBlackjack);
  REQUIRE(engine.player_cards.size() == 2);
  engine.RunPlayerHit();
  REQUIRE(engine.player_cards.size() == 2);
}

// Reset Tests
TEST_CASE("Reset Game Test", "[engine][reset]") {
  mylibrary::Engine engine;
  engine.RunPlayerHit();
  engine.RunPlayerHit();
  REQUIRE(engine.player_cards.size() == 2);
  engine.SetPlayerScore(kBlackjack);
  engine.SetDealerScore(13);
  engine.Bet(100);
  engine.in_menu = false;
  engine.is_end_game = true;
  REQUIRE(engine.GetPlayerScore() == kBlackjack);
  REQUIRE(engine.GetDealerScore() == 13);
  REQUIRE(engine.GetCurrentBet() == 100);
  REQUIRE(engine.GetBalance() == 900);
  engine.ResetGame();
  REQUIRE(engine.player_cards.size() == 0);
  REQUIRE(engine.GetPlayerScore() == 0);
  REQUIRE(engine.GetDealerScore() == 0);
  REQUIRE(engine.GetCurrentBet() == 0);
  REQUIRE(engine.GetBalance() == kStartBalance);
  REQUIRE(engine.in_menu);
  REQUIRE(!engine.is_end_game);
}
TEST_CASE("Reset Balance Tests", "[engine]") {
  mylibrary::Engine engine;
  REQUIRE(engine.GetCurrentBet() == 0);
  REQUIRE(engine.GetBalance() == kStartBalance);
  engine.Bet(20);
  REQUIRE(engine.GetCurrentBet() == 20);
  REQUIRE(engine.GetBalance() == 980);
  engine.ResetBalance();
  REQUIRE(engine.GetCurrentBet() == 0);
  REQUIRE(engine.GetBalance() == kStartBalance);
}
TEST_CASE("Reset Round Tests", "[engine]") {
  mylibrary::Engine engine;
  engine.SetPlayerScore(kBlackjack);
  engine.SetDealerScore(13);
  engine.Bet(100);
  engine.is_transition = true;
  engine.is_betting = false;
  REQUIRE(engine.GetPlayerScore() == kBlackjack);
  REQUIRE(engine.GetDealerScore() == 13);
  REQUIRE(engine.GetCurrentBet() == 100);
  engine.ResetRound();
  REQUIRE(engine.GetPlayerScore() == 0);
  REQUIRE(engine.GetDealerScore() == 0);
  REQUIRE(engine.GetCurrentBet() == 0);
  REQUIRE(!engine.is_transition);
  REQUIRE(engine.is_betting);
}