// Copyright (c) 2020 [Your Name]. All rights reserved.
#ifndef FINALPROJECT_MYLIBRARY_EXAMPLE_H_
#define FINALPROJECT_MYLIBRARY_EXAMPLE_H_

#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

namespace mylibrary {
class Engine {
 public:
  
  struct card
  {
    int color, value;
  };
  std::vector<card> player_cards, dealer_cards, dealt_cards;
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
  int GetPlayerScore();
  std::string BetToString(int value);
  int randomValueGenerator();
  int randomColorGenerator();
  void RunRoundStart();
  void RunPlayerHit();
  void RunDealerHit();
  card DealCards();
  void bet(int value);
  void ResetBalance();
  int EvaluateCardValue(bool);
  void ResetRound();
  void ResetGame();
  bool IsUniqueCard(card card);
};

  

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
