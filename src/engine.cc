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

void Engine::RunRoundStart() {
  if (player_cards.empty()) {
    card card1 = DealCards();
    card card2 = DealCards();
    card card3 = DealCards();
    card card4 = DealCards();
    player_score += card1.value;
    player_score += card2.value;
    player_cards.push_back(card1);
    player_cards.push_back(card2);
    dealer_cards.push_back(card3);
    dealer_cards.push_back(card4);
  }
}

Engine::card Engine::DealCards() {
  card dealt_card;
  dealt_card.value = randomValueGenerator();
  dealt_card.color = randomColorGenerator();
  dealt_cards.push_back(dealt_card);
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
void Engine::RunPlayerHit() {
  if (player_cards.size() < 5 && player_score < 21) {
    card card = DealCards();
    player_score += card.value;
    player_cards.push_back(card);
  }
}

int Engine::EvaluateCardValue() {
  int total_score = 0;
  std::vector<int> ace_position;
  for (int i = 0; i < player_cards.size(); i++) {
    if (player_cards[i].value <= 10) {
      total_score += player_cards[i].value;
    }
    if (player_cards[i].value > 10 && player_cards[i].value < 14) {
      total_score += 10;
    }
    if (player_cards[i].value == 14) {
      ace_position.push_back(i);
    }
  }
  //checks for ace value after checking regular card values
  for (int i = 0; i < ace_position.size(); i++) {
    int check_ace = total_score;
    check_ace += 11;
    if (check_ace > 21) {
      total_score += 1;
    } else {
      total_score += 11;
    }
  }
  return total_score;
}
int Engine::EvaluateRound() { 
  while (dealer_score < 17 && dealer_score < player_score) {
    RunDealerHit();
  }
  if (dealer_score > 21) {
    return 1;
  }
  
  if (player_score > dealer_score) {
    return 1;
  }
  if (player_score < dealer_score) {
    return 2;
  }
  if (player_score == dealer_score) {
    return 3;
  }
}

void Engine::ResetRound() {
  player_score = 0;
  dealer_score = 0;
  current_bet = 0;
  isBetting = true;
  is_transition = false;
  inRound = false;
  player_cards.clear();
  dealer_cards.clear();
  
}
int Engine::EvaluateDealerCardValue() {
  int total_score = 0;
  std::vector<int> ace_position;
  for (int i = 0; i < dealer_cards.size(); i++) {
    if (dealer_cards[i].value <= 10) {
      total_score += dealer_cards[i].value;
    }
    if (dealer_cards[i].value > 10 && dealer_cards[i].value < 14) {
      total_score += 10;
    }
    if (dealer_cards[i].value == 14) {
      ace_position.push_back(i);
    }
  }
  //checks for ace value after other cards have been evaluated
  for (int i = 0; i < ace_position.size(); i++) {
    int check_ace = total_score;
    check_ace += 11;
    if (check_ace > 21) {
      total_score += 1;
    } else {
      total_score += 11;
    }
  }
  return total_score;
}
void Engine::RunDealerHit() {
  if (player_cards.size() < 5) {
    card card = DealCards();
    dealer_cards.push_back(card);
    dealer_score = EvaluateDealerCardValue();
  }
}
}  // namespace mylibrary
