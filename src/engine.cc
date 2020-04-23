// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/engine.h>
#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

namespace mylibrary {

int Engine::randomColorGenerator() {
  int nr = rand() % 4 + 1;
  return nr;
}

int Engine::randomValueGenerator() {
  int nr = rand() % 14 + 1;
  return nr;
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
  dealt_card.value = randomValueGenerator();
  dealt_card.color = randomColorGenerator();
  return dealt_card;
}

void Engine::bet(int value) {
  if (value > balance) {
    return;
  }
  current_bet += value;
  balance -= value;
}
void Engine::ResetBalance() {
  balance += current_bet;
  current_bet = 0;
}
void Engine::RunHit() {
  if (player_cards.size() < 5) {
    card card = DealCards();
    player_cards.push_back(card);
  }
}
}  // namespace mylibrary
