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
  std::vector<card> player_cards, dealer_cards;
  int balance = 1000;
  int current_bet = 0;
  std::string BetToString(int value);
  int randomValueGenerator();
  int randomColorGenerator();
  void RunRound();
  void RunHit();
  card DealCards();
  void bet(int value);
  void Engine::ResetBalance();
};

  

}  // namespace mylibrary


#endif // FINALPROJECT_MYLIBRARY_EXAMPLE_H_
