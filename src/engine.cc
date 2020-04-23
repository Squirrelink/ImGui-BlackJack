// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/engine.h>
#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>


namespace mylibrary {


int Engine::randomColorGenerator() {
  unsigned seed = time(0);
  srand(seed);
  int nr = rand() % 4 + 1;
  return nr;
}

int Engine::randomValueGenerator() {
  unsigned seed = time(0);
  srand(seed);
  int nr = rand() % 14 + 1;
  return nr;
}

std::vector<cinder::gl::Texture2dRef> Engine::LoadCards() {
  return std::vector<cinder::gl::Texture2dRef>();
}
std::string Engine::BetToString(int value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

void Engine::RunRound() {
  if (player_cards.empty()) {
    card card1 = DealCards();
    card card2 = DealCards();
    player_cards.push_back(card1);
    player_cards.push_back(card2);
  }
}


Engine::card Engine::DealCards() {
  card dealt_card;
  dealt_card.color = randomValueGenerator();
  dealt_card.value = randomColorGenerator();
  return dealt_card;
}
int Engine::GetCardValue(Engine::card card) { 
  return card.value;
}
}  // namespace mylibrary
