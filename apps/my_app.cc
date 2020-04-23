// Copyright (c) 2020 [Your Name]. All rights reserved.

#include "my_app.h"
#include <mylibrary/engine.h>
#include <cinder/Log.h>
#include <cinder/app/App.h>
#include <cinder/gl/Texture.h>
#include <cinder/gl/wrapper.h>
#include <cinder/gl/draw.h>
#include "CinderImGui.h"

namespace myapp {

using cinder::app::KeyEvent;

MyApp::MyApp() { }

void MyApp::setup() {
  ImGui::initialize();
  inMenu = true;
  inGame = false;
  inRound = false;
  LoadImages();
  srand(time(0));
}

void MyApp::update() {

}

void MyApp::draw() {
  cinder::gl::clear();
  ImGui::Begin("Menu");
  ImGui::SetWindowFontScale(1.8);
  if (inMenu) {
    MenuButton();
  }
  if (inGame && isBetting) {
    DrawGameState();
    DrawStartGameButtons();
  }
  if (inGame && inRound) {
    engine.RunRound();
    DrawGameState();
    DrawGameButtons();
    DrawPlayerCards();
    DrawDealerCards();
  }
  ImGui::End();
}


void MyApp::keyDown(KeyEvent event) { }
void MyApp::MenuButton() {
  
  if (ui::Button( "Start Game" )) {
    inMenu = false;
    inGame = true;
    isBetting = true;
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
}
void MyApp::DrawGameState() {
  cinder::gl::draw(background_Texture);
  cinder::gl::draw(deck_Texture);
  std::string balText = "Balance: " + engine.BetToString(balance);
  std::string betText = "Current Bet: " + engine.BetToString(current_bet);
  ui::Text(balText.c_str());
  ui::Text(betText.c_str());
}

void MyApp::DrawGameButtons() {
  ui::Button("HIT");
  ui::Button("STAND");
}

void MyApp::DrawStartGameButtons() {
  if (ui::Button("Place Bet")) {
    if (current_bet > 0) {
      isBetting = false;
      inRound = true;
    }
  }
  if (ui::Button("Reset Bet")) {
    ResetBalance();
  }
  if (ui::ImageButton(one_chip_Texture,one_chip_Texture->getSize())) {
    bet(1);
  }
  if (ui::ImageButton(ten_chip_Texture,ten_chip_Texture->getSize())) {
    bet(10);
  }
  if (ui::ImageButton(hundred_chip_Texture,hundred_chip_Texture->getSize())) {
    bet(100);
  }
  if (ui::ImageButton(thousand_chip_Texture,thousand_chip_Texture->getSize())) {
    bet(1000);
  }
  if (ui::ImageButton(max_chip_Texture,max_chip_Texture->getSize())) {
    bet(balance);
  }
}


void MyApp::bet(int value) {
  if (value > balance) {
    return;
  }
  current_bet += value;
  balance -= value;
}
void MyApp::ResetBalance() {
  balance+= current_bet;
  current_bet = 0;
}
void MyApp::DrawPlayerCards() {
  size_t row = 0;
  const cinder::vec2 center = getWindowCenter();
  for (int i = 0; i < engine.player_cards.size(); i++) {
    const cinder::vec2 locp = {center.x, center.y + (++row) * 50};
    cinder::gl::draw(GetCardTexture(engine.player_cards[i].value,engine.player_cards[i].color), locp);
  }
}
void MyApp::DrawDealerCards() {
  
}
cinder::gl::Texture2dRef MyApp::GetCardTexture(int value, int color) {
  cinder::gl::Texture2dRef card_texture;
  card_texture = cinder::gl::Texture2d::create( loadImage( loadAsset( engine.BetToString(value) + "_" + engine.BetToString(color) + ".png")));
  return card_texture;
}
}  // namespace myapp
