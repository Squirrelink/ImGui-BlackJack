// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

namespace mylibrary {
const int kBlackjack = 21;
const int kPlayerWin = 1;
const int kPlayerLose = 2;
const int kPlayerTie = 3;
const int kMaxCards = 5;
const int kDealStand = 17;
const int kStartBalance = 1000;
const int kAceCard = 14;
const int kRoyalCard = 10;
const int kAceValue = 11;

class Engine {
 public:
  struct card {
    int color, value;
  };
  std::vector<card> player_cards, dealer_cards;
  bool in_menu;
  bool is_betting;
  bool in_game;
  bool in_round;
  bool is_transition;
  bool is_end_game;
  bool updated_balance;
  int EvaluateRound();
  std::string BetToString(int value);
  void RunRoundStart();
  void RunPlayerHit();
  void Bet(int value);
  int EvaluateCardValue(bool);
  void ResetRound();
  void ResetGame();
  void ResetBalance();
  //Setters and Getters
  int GetPlayerScore();
  void SetPlayerScore(int score);
  int GetDealerScore();
  void  SetDealerScore(int score);
  int GetBalance();
  int GetCurrentBet();
  
 private:
  std::vector<card> dealt_cards;
  int player_score = 0;
  int dealer_score = 0;
  int balance = kStartBalance;
  int current_bet = 0;
  bool IsUniqueCard(card card);
  void ReturnPayouts();
  void ReturnTiePayout();
  void RunDealerHit();
  int RandomValueGenerator();
  int RandomColorGenerator();
  card DealCards();
};
}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
