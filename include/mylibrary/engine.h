// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

namespace mylibrary {
class Engine {
 private:
  struct card
  {
    int color, value;
  };
  std::vector<card> dealt_cards;
  bool IsUniqueCard(card card);
  void ReturnPayouts();
  void ReturnTiePayout();
  void RunDealerHit();
  card DealCards();
  int randomValueGenerator();
  int randomColorGenerator();
 public:
  std::vector<card> player_cards, dealer_cards;
  int player_score = 0;
  int dealer_score = 0;
  int balance = 1000;
  int current_bet = 0;
  bool inMenu;
  bool isBetting;
  bool inGame;
  bool inRound;
  bool is_transition;
  bool is_end_game;
  bool updated_balance;
  int EvaluateRound();
  std::string BetToString(int value);
  void RunRoundStart();
  void RunPlayerHit();
  void bet(int value);
  void ResetBalance();
  int EvaluateCardValue(bool);
  void ResetRound();
  void ResetGame();
  
  //Setters and Getters
  int GetPlayerScore();
  void SetPlayerScore(int score);
  int GetDealerScore();
  void  SetDealerScore(int score);
  int GetBalance();
  int GetCurrentBet();
};

  

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
