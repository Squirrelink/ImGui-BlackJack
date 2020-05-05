// Copyright (c) 2020 [Your Name]. All rights reserved.

#include <mylibrary/engine.h>
#include <cinder/app/App.h>
#include <cinder/gl/Shader.h>
#include <cinder/gl/Texture.h>

namespace mylibrary {

/**
 * Generates random number for color of card dealing
 * @return random number from 1-4 inclusive
 */
int Engine::RandomColorGenerator() {
  int nr = rand() % 4 + 1;
  return nr;
}

/**
 * Generates random number for Rank of card dealing
 * @return random number 2-14 inclusive
 */
int Engine::RandomValueGenerator() {
  int nr = rand() % 14 + 1;
  if (nr == 1) {
    nr += rand() % 12 + 1;
  }
  return nr;
}

/**
 * turns int values to strings
 * @param value to be turned to string
 * @return string of inputted value
 */
std::string Engine::BetToString(int value) {
  std::stringstream ss;
  ss << value;
  return ss.str();
}

/**
 * Distributes two cards each to dealer and player
 */
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

/**
 * Generates a random unique card recursively
 * @return a random card
 */
Engine::card Engine::DealCards() {
  card dealt_card;
  dealt_card.value = RandomValueGenerator();
  dealt_card.color = RandomColorGenerator();
  if (!(IsUniqueCard(dealt_card))) {
    return DealCards();
  } else {
    dealt_cards.push_back(dealt_card);
    return dealt_card;
  }
}

/**
 * Checks if card has already been dealt during the round.
 * @param card attempting to be dealt
 * @return true if card hasn't already been dealt
 */
bool Engine::IsUniqueCard(Engine::card card) {
  bool is_unique = true;
  if (dealt_cards.empty()) {
    return true;
  }
  for (int i = 0; i < dealt_cards.size(); i++) {
    if (dealt_cards[i].value == card.value &&
        dealt_cards[i].color == card.color) {
      is_unique = false;
    }
  }
  return is_unique;
}

/**
 * adds bet value to players current bet
 * @param value of bet
 */
void Engine::Bet(int value) {
  if (value > balance) {
    return;
  }
  current_bet += value;
  balance -= value;
}

/**
 * Evaluates all cards not an ace before adding ace value to total
 * @param eval_user true if user cards to evaluate, false for dealer cards
 * @return evaluated hand score
 */
int Engine::EvaluateCardValue(bool eval_user) {
  int total_score = 0;
  std::vector<int> ace_position;
  std::vector<card> card_hand;
  if (eval_user) {
    card_hand = player_cards;
  } else {
    card_hand = dealer_cards;
  }
  for (int i = 0; i < card_hand.size(); i++) {
    if (card_hand[i].value <= kRoyalCard) {
      total_score += card_hand[i].value;
    }
    if (card_hand[i].value > kRoyalCard && card_hand[i].value < kAceCard) {
      total_score += kRoyalCard;
    }
    if (card_hand[i].value == kAceCard) {
      ace_position.push_back(i);
    }
  }
  //checks for ace value after checking regular card values
  for (int i = 0; i < ace_position.size(); i++) {
    int check_ace = total_score;
    check_ace += kAceValue;
    if (check_ace > kBlackjack) {
      total_score += 1;
    } else {
      total_score += kAceValue;
    }
  }
  return total_score;
}

/**
 * Evaluates round information to determine a round winner
 * @return 1 for user win, 2 for player lose, 3 for tie.
 */
int Engine::EvaluateRound() {
  if (player_score > kBlackjack) {
    updated_balance = true;
    return kPlayerLose;
  }
  RunDealerHit();
  if (dealer_score > kBlackjack) {
    ReturnPayouts();
    return kPlayerWin;
  }
  if (player_score > dealer_score || player_score == kBlackjack) {
    ReturnPayouts();
    return kPlayerWin;
  }
  if (player_score < dealer_score || dealer_score == kBlackjack) {
    updated_balance = true;
    return kPlayerLose;
  }
  if (player_score == dealer_score) {
    ReturnTiePayout();
    return kPlayerTie;
  }
}

/**
 * Dealer AI run on player stand
 */
void Engine::RunDealerHit() {
  while (dealer_cards.size() < kMaxCards && dealer_score < kDealStand 
    && dealer_score <= player_score) {
    card card = DealCards();
    dealer_cards.push_back(card);
    dealer_score = EvaluateCardValue(false);
  }
}

/**
 * Generates a new card and adds card value to player score
 */
void Engine::RunPlayerHit() {
  if (player_cards.size() < kMaxCards && player_score < kBlackjack) {
    card card = DealCards();
    player_score += card.value;
    player_cards.push_back(card);
  }
}

/**
 * Resets round variables to to begin a new round in betting stage
 */
void Engine::ResetRound() {
  player_score = 0;
  dealer_score = 0;
  current_bet = 0;
  is_betting = true;
  is_transition = false;
  in_round = false;
  player_cards.clear();
  dealer_cards.clear();
  dealt_cards.clear();
}

/**
 * resets game on player Exit and Play Again
 */
void Engine::ResetGame() {
  ResetRound();
  balance = kStartBalance;
  in_menu = true;
  is_end_game = false;
}

/**
 * Resets balance for end of round payouts
 */
void Engine::ResetBalance() {
  balance += current_bet;
  current_bet = 0;
}

/**
 * Gives player double their current bet to balance
 */
void Engine::ReturnPayouts() {
  if (updated_balance == false) {
    balance += (2 * current_bet);
    updated_balance = true;
  }
}

/**
 * Returns current bet to player balance
 */
void Engine::ReturnTiePayout() {
  if (updated_balance == false) {
    balance += current_bet;
    updated_balance = true;
  }
}

//Setters and Getters
int Engine::GetPlayerScore() {
  return player_score;
}

void Engine::SetPlayerScore(int score) {
  player_score = score;
}

int Engine::GetDealerScore() { 
  return dealer_score;
}

void Engine::SetDealerScore(int score) {
  dealer_score = score;
}

int Engine::GetBalance() { 
  return balance;
}

int Engine::GetCurrentBet() { 
  return current_bet;
}
}
  // namespace mylibrary
