// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <mylibrary/engine.h>
#include <cinder/Log.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/draw.h>
#include <chrono>
#include "CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::initialize();
  engine.inMenu = true;
  engine.inGame = false;
  engine.inRound = false;
  engine.is_transition = false;
  LoadImages();
  srand(time(0));
}

void MyApp::update() {

}

void MyApp::draw() {
  cinder::gl::clear();
  ImGui::Begin("Menu");
  ImGui::SetWindowFontScale(1.8);
  
  if (engine.is_transition) {
    if (engine.player_score == 21) {
      DrawPlayerWin();
    } else if (engine.player_score > 21) {
      DrawPlayerLose();
    } else {
      if (engine.EvaluateRound() == 1) {
        DrawPlayerWin();
      }
      if (engine.EvaluateRound() == 2) {
        DrawPlayerLose();
      }
      if (engine.EvaluateRound() == 3) {
        DrawTie();
      }
    }
    DrawGameState();
    DrawPlayerCards();
    DrawNewRoundButton();
    DrawDealerCards();
    DrawScore();
    DrawDealerScore();
  }
  if (engine.inMenu) {
    MenuButton();
  }
  if (engine.inGame && engine.isBetting) {
    DrawGameState();
    DrawStartGameButtons();
  }
  if (engine.inGame && engine.inRound && !engine.is_transition) {
    engine.RunRoundStart();
    engine.player_score = engine.EvaluateCardValue();
    engine.dealer_score = engine.EvaluateDealerCardValue();
    if (engine.player_score > 21) {
      engine.is_transition = true;
    }
    if (engine.player_score == 21) {
      engine.is_transition == true;
    }
    DrawGameState();
    DrawGameButtons();
    DrawPlayerCards();
    DrawInitialDealerCards();
  }
  ImGui::End();
}


void MyApp::keyDown(KeyEvent event) { }
void MyApp::MenuButton() {
  if (ui::Button( "Start Game" )) {
    engine.inMenu = false;
    engine.inGame = true;
    engine.isBetting = true;
  }
}

void MyApp::LoadImages() {
  background_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "background.jpg" )));
  deck_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "deck.png" )));
  one_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "1.png" )));
  ten_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "10.png" )));
  hundred_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "100.png" )));
  thousand_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "1000.png" )));
  max_chip_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "max.png" )));
  card_back_Texture = cinder::gl::Texture2d::create( loadImage( loadAsset( "cardBack.png" )));
}

void MyApp::DrawGameState() {
  cinder::gl::draw(background_Texture);
  cinder::gl::draw(deck_Texture);
  std::string balText = "Balance: " + engine.BetToString(engine.balance);
  std::string betText = "Current Bet: " + engine.BetToString(engine.current_bet);
  ui::Text(balText.c_str());
  ui::Text(betText.c_str());
}

void MyApp::DrawGameButtons() {
  if (ui::Button("HIT")) {
    engine.RunPlayerHit();
  }
  if (ui::Button("STAND")) {
    engine.is_transition = true;
  }
  ui::Button("DOUBLE");
  DrawScore();
}

void MyApp::DrawStartGameButtons() {
  if (ui::Button("Place Bet")) {
    if (engine.current_bet > 0) {
      engine.isBetting = false;
      engine.inRound = true;
    }
  }
  DrawBetButtons();
}


void MyApp::DrawPlayerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  for (int i = 0; i < engine.player_cards.size(); i++) {
    const cinder::vec2 locp = {center.x, center.y + (++row) * 70};
    cinder::gl::draw(GetCardTexture(engine.player_cards[i].value,engine.player_cards[i].color), locp);
  }
}

void MyApp::DrawDealerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  for (int i = 0; i < engine.dealer_cards.size(); i++) {
    const cinder::vec2 locp = {300, 10 +(++row) * 70};
    cinder::gl::draw(GetCardTexture(engine.dealer_cards[i].value,engine.dealer_cards[i].color), locp);
  }
}

void MyApp::DrawInitialDealerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  const cinder::vec2 locp = {300, 10 +(++row) * 70};
  const cinder::vec2 locp_two = {300, 10 +(++row) * 70};
  cinder::gl::draw(card_back_Texture, locp);
  cinder::gl::draw(GetCardTexture(engine.dealer_cards[0].value,engine.dealer_cards[0].color), locp_two);
}

cinder::gl::Texture2dRef MyApp::GetCardTexture(int value, int color) {
  cinder::gl::Texture2dRef card_texture;
  card_texture = cinder::gl::Texture2d::create( loadImage( loadAsset( engine.BetToString(value) + "_" + engine.BetToString(color) + ".png")));
  return card_texture;
}
void MyApp::DrawBetButtons() {
  if (ui::Button("Reset Bet")) {
    engine.ResetBalance();
  }
  if (ui::ImageButton(one_chip_Texture,one_chip_Texture->getSize())) {
    engine.bet(1);
  }
  if (ui::ImageButton(ten_chip_Texture,ten_chip_Texture->getSize())) {
    engine.bet(10);
  }
  if (ui::ImageButton(hundred_chip_Texture,hundred_chip_Texture->getSize())) {
    engine.bet(100);
  }
  if (ui::ImageButton(thousand_chip_Texture,thousand_chip_Texture->getSize())) {
    engine.bet(1000);
  }
  if (ui::ImageButton(max_chip_Texture,max_chip_Texture->getSize())) {
    engine.bet(engine.balance);
  }
}
void MyApp::DrawPlayerLose() {
  ui::Text("You Lost");
  std::string lost_bet = "- " + engine.BetToString(engine.current_bet);
  ui::Text(lost_bet.c_str());
}

void MyApp::DrawNewRoundButton() {
  if (ui::Button("New Round")) {
    engine.ResetRound();
  }
}
void MyApp::DrawPlayerWin() {
  ui::Text("You Won");
  std::string won_bet = "+ " + engine.BetToString(engine.current_bet);
  ui::Text(won_bet.c_str());
}
void MyApp::DrawTie() {
  ui::Text("Tie! No Winner");
  std::string tie_bet = "+ " + engine.BetToString(engine.current_bet);
  ui::Text(tie_bet.c_str());
}
void MyApp::DrawScore() {
  std::string scoreText = "Current Score: " + engine.BetToString(engine.player_score);
  ui::Text(scoreText.c_str());
}
void MyApp::DrawDealerScore() {
  std::string scoreText = "Dealer Score: " + engine.BetToString(engine.dealer_score);
  ui::Text(scoreText.c_str());
}

}  // namespace myapp
